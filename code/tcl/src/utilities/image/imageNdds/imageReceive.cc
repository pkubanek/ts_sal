/* Rewrite Dec 1996 by Kurt Schwehr for a generic image receive without tcl/tk. */

#define DEBUG_PRINT	// Comment this out to remove debugging stucture print functions.

// Standard unix includes
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>			// For clock ticks.
#include <signal.h>			// For sigaction

#ifdef USE_TCL
#include <tk.h>		// For graphical stuff.
#endif

// NDDS includes
#include <NDDS.h>

// NDDS type includes
#include <ImageHeader.h>
#include <ImagePacket.h>
#include <ImageSequence.h>

// Include file for both Unix and VxWorks
#include "imageNdds.h"
#include "fifo.h"
extern "C" {
void sleep_us (unsigned int nusecs);	/* acually defined in libutil */
}

#ifndef OK
#define OK (1==1)
#endif

#define IMG_BUF_SIZE (1024*512)		// Num of bytes to buffer for each file.
#define NUM_IMAGES 10			// Worst case, needs same size  as # cache pkts on send side.
// fopen allows only more that 255 files to be open.

#define IMAGE_FIFO_SIZE	100		/* one second of fifo */

//
// Types only used in this file.
//
struct Stats {
    int pktReceived;
    int pktResendReceived;
    int hdrReceived;
    int requestResends;
};

struct Image {
    int imgID;
    int bitsPerPixel;
    int firstPacketNum;
    int lastPacketNum;
    ImageHeader imgHdr;
    int fileDataOffset;		// When does image data start.
    FILE *file;
};

//
// Global variables.
//
ImagePacket	imgPkt, resentImgPkt;
ImageHeader	imgHdr, resentImgHdr;	
ImageSequence	imgSeqIn, imgSeqOut;

NDDSProducer	imgSeqProducer;
NDDSConsumer	imgConsumer;

#ifdef USE_TCL
Tcl_Interp *interp;
#endif

int pktMask[NUM_CACHE_PACKETS]; // Mark which packets we have
	// received.  I'm hoping to use this to figure out when images are done.

static int largestPacketNum=0;	// Keeps track of the last packet received
static int largestImgID=-1;	// Keep track of the largest image id received.
struct Stats stats;
struct Image images[NUM_IMAGES];
static FIFO_ID	inBox;

const float sleepTime = 0.0001;	// Seconds round trip time in seconds

//
// Local function prototypes.
//

void copyHeader (ImageHeader to, const ImageHeader from);
int WritePgmBinaryHeader (FILE* file, ImageHeader hdr);
int WritePgmBinaryPacket (const struct Image *img, const ImagePacket pkt);
#ifdef USE_TCL
int QuitCallBack (ClientData cd, Tcl_Interp *ip, int argc, char *argv[]);
#endif
void sleep_us (unsigned int nusecs);	// Micro second sleep function.
int ImageCompleted (const int imgID);
void CloseImageFile (const int imgID);
void CloseStaleImageFiles (void);
static NDDSObjectInstance ImageSeqCB (NDDSUpdateInfo update);

#ifdef DEBUG_PRINT
int print_header (ImageHeader h);
int print_packet (ImagePacket p);
int print_sequence (ImageSequence s);
void print_image_struct (const struct Image *i);
#endif // DEBUG_PRINT

#ifdef 0 //NDEBUG
#define NddsDebug(n,s)                  /* expand to nothing */
#else
int debug_level=3;
#define NddsDebug(n,s)  (((n) <= debug_level) ?  printf s :0)
#endif

#undef ABS
#undef MAX
#define ABS(f)    ( (f) >  0  ? (f) : -(f) )
#define MAX(a,b)  ( (a) > (b) ? (a) :  (b) )

#define logMsg printf

/* Direct NDDS callback for header productions */
/* Now called asyncronously!!! */
NDDSObjectInstance
ImageHeaderCB (NDDSUpdateInfo update)
{
    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
	FifoSend (inBox, (char *)update->instance, IMAGE_HEADER_BLOCK_SIZE);
	break;
    case NDDS_UPDATE_OF_OLD_DATA:
    case NDDS_NO_NEW_DATA:
    case NDDS_NEVER_RECEIVED_DATA:
	return NULL;
    case NDDS_DESERIALIZATION_ERROR:
	NddsDebug (2, ("ImageHeaderHandler: data error\n"));
	break;
    default:
	NddsDebug (1, ("ImgHeaderHandler: bogus update %d\n",
		       update->updateStatus));
    }
    return NULL;
}

/* This does the work when a new header arrives */
void
ImageHeaderUpdate (ImageHeader hdr)
{
    const int imgID = hdr->headerId;
    const int imgIndex = imgID % NUM_IMAGES;	assert (0<=imgID);
    struct Image *img = &images[imgIndex];

    if (NULL != img->file) {
	if (imgID == img->imgID) {
	    printf ("Looks like we got multiple headers for img %d.  Should be okay.\n",imgID);
	    return;
	}
	printf ("Closing image file in slot %d\n", imgIndex);
	fclose (img->file);
    }

    {
	ImageHeader h;
	h = ImageHeaderBlockAlloc();
	copyHeader (h, hdr);
	//hdrMap[h->headerId] = h;
	// FIX: add code to request sending missed headers.
    }

    char fileName[256];
    sprintf (fileName, "%d.pgm", imgID);
    img->file = fopen (fileName, "w");    assert (img->file);
    setvbuf (img->file, NULL, _IOFBF, IMG_BUF_SIZE); // Set the buffering type & size for writes.

    copyHeader (img->imgHdr, hdr);

    img->fileDataOffset = WritePgmBinaryHeader (img->file, hdr);
    img->bitsPerPixel = 8;

    img->imgID = hdr->headerId;

    img->firstPacketNum = largestPacketNum + 1;	// Assume we get header before any img data.
    img->lastPacketNum = -1;			// We do not yet know.

#ifdef USE_TCL
    {	// Keep the tcl world up to date.
	char str[64];
	sprintf (str,"imgID%d",imgIndex);
	Tcl_UpdateLinkedVar (interp, str);
	sprintf (str,"firstPacketNum%d",imgIndex);
	Tcl_UpdateLinkedVar (interp, str);
	sprintf (str,"lastPacketNum%d",imgIndex);
	Tcl_UpdateLinkedVar (interp, str);
    }
#endif

    if (img->imgID > largestImgID) largestImgID = img->imgID;

    stats.hdrReceived++;
#ifdef USE_TCL
    Tcl_UpdateLinkedVar (interp, "hdrReceived");
#endif
    return;
}

/* Now called asyncronously!!! */
NDDSObjectInstance
ImagePacketCB (NDDSUpdateInfo update)
{
    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
	FifoSend (inBox, (char *)update->instance,
		  IMAGE_PACKET_BLOCK_SIZE);
	break;
    case NDDS_UPDATE_OF_OLD_DATA:
    case NDDS_NO_NEW_DATA:
    case NDDS_NEVER_RECEIVED_DATA:
	return NULL;			/* nothing to do */
    case NDDS_DESERIALIZATION_ERROR:
	NddsDebug (2, ("ImageHeaderHandler: data error\n"));
	break;
    default:
	NddsDebug (1, ("ImagePacketHandler: bogus update status %d\n",
		       update->updateStatus));
    }
    return NULL;
}

void
SendResendRequest (int headerId, int pktNum) {
    assert (0<=pktNum);
    imgSeqOut->headerId = headerId; assert (0<=headerId);
    imgSeqOut->x1 = pktNum;           // FIX: VERY ugly hack to put in pktNum in coords!
    imgSeqOut->y1 = pktNum;
    imgSeqOut->x2 = pktNum;
    imgSeqOut->y2 = pktNum;
    imgSeqOut->sequenceType = PACKET_RESEND;

    fprintf (stderr,"r%d ", pktNum);
    NddsProducerSample (imgSeqProducer);
    //pktRequestTimes[pktNum] = clock();	// Save the time of request.
    stats.requestResends++;
#ifdef USE_TCL
    Tcl_UpdateLinkedVar (interp, "requestResends");
#endif
    sleep_us ( (unsigned int)(1000000 * sleepTime) ); // Sleep to let ndds data get out.
}

/* This does the work when a new header arrives */
void
ImagePacketUpdate (ImagePacket pkt)
{
    static int started = FALSE;
    const imgID = pkt->headerId;
    const imgIndex = (ABS(imgID)) % NUM_IMAGES;

    if (!started) {			// initialize 
	char str[64];
	started = TRUE;
	largestPacketNum = ABS(pkt->packet_num) - 1;
	printf ("Initializing largestPacketNum to %d\n", largestPacketNum);
	for (int i=0; i<NUM_IMAGES; i++) {
	    if (0 != images[i].firstPacketNum) {
		images[i].firstPacketNum = ABS(pkt->packet_num);
		sprintf (str, "firstPacketNum%d",i);
#ifdef USE_TCL
		Tcl_UpdateLinkedVar (interp, str);
#endif
	    }
	}
    }

    if (pkt->headerId >= 0) {		// a new packet
	stats.pktReceived++;
#ifdef USE_TCL
	Tcl_UpdateLinkedVar (interp, "pktReceived");
#endif
    } else {				// a resent packet
	stats.pktResendReceived++;
#ifdef USE_TCL
	Tcl_UpdateLinkedVar (interp, "pktResendReceived");
#endif
    }

					// set a bit saying packet was received
    pktMask[ (ABS(pkt->packet_num)) % NUM_CACHE_PACKETS] = ABS(pkt->packet_num);

    if (pkt->headerId >= 0) {		// new packet, check sequence
	if (pkt->packet_num > largestPacketNum + 1) {
	    printf ("Got %d Expected %d\n",
		    pkt->packet_num, largestPacketNum + 1);
	    for (int i=largestPacketNum+1; i < pkt->packet_num; i++)
		SendResendRequest (pkt->headerId, i);
#ifdef TEST_RESENDS
	} else if (7 == (stats.pktReceived & 0x1f)) { // DEBUG: ask anyway!
	    fprintf (stderr, "B");
	    SendResendRequest (pkt->headerId, pkt->packet_num);
#endif
	}
    }

    if (largestPacketNum < pkt->packet_num) {
	largestPacketNum = pkt->packet_num;
#ifdef USE_TCL
	Tcl_UpdateLinkedVar (interp, "lastPacketNum");
#endif
    }

    if (NULL != images[imgIndex].file) { // output it to the file
	WritePgmBinaryPacket (&images[imgIndex], pkt);
	if ( ImageCompleted (ABS(pkt->headerId)) )
	    CloseImageFile (ABS(pkt->headerId));
    } else {				// only print this once
	static int lastErrorImgID = -1;

	if (ABS(imgID) != lastErrorImgID)
	    printf ("ERROR: null image file for image %d [%d]!\n",
		    imgID, imgIndex);
	lastErrorImgID = ABS(imgID);
    }

    CloseStaleImageFiles();
}


//Close all files that are too old to be in the senders cache.
void
CloseStaleImageFiles (void) {
    const int pktLimit = largestPacketNum - NUM_CACHE_PACKETS;
    int i;
    for (i=0;i<NUM_IMAGES;i++) {
	struct Image *img = &images[i];
	if ((img->imgID > 0) &&
	    (img->lastPacketNum > 0) && 
	    (img->lastPacketNum < pktLimit) )
	{
	    CloseImageFile (images[i].imgID);
	}

    }
    return;
}

// Returns true if we can figure out that an image has been completely received.
int
ImageCompleted (const int imgID) {
    const int imgFileIndex=ABS(imgID) % NUM_IMAGES;
    const struct Image *img = &images[imgFileIndex];

    if (img->lastPacketNum < 0) return FALSE;	// Have not gotten the lastPacketNum yet.
    if (img->lastPacketNum > largestPacketNum) return FALSE;
    if (img->lastPacketNum < largestPacketNum - NUM_CACHE_PACKETS) {
	printf ("imgLast(%d) < %d - last (%d) + NUM_CAHCE (%d)\n",
		img->lastPacketNum,
		largestPacketNum + NUM_CACHE_PACKETS,
		largestPacketNum, NUM_CACHE_PACKETS
		);
	return TRUE;  // The image can't be in the senders cache anymore, so force done.
    }

    const int oldestCachePkt = largestPacketNum - NUM_CACHE_PACKETS;
    int startPkt = MAX(oldestCachePkt,img->firstPacketNum);

    startPkt = MAX(0,startPkt);

    for (int pkt=startPkt; pkt<=largestPacketNum; pkt++) {
	int cacheIndex = pkt % NUM_CACHE_PACKETS;
	if (pkt != pktMask[cacheIndex]) return FALSE;
    }

    printf ("imgLastPktNum=%d    ",img->lastPacketNum);
    printf ("Image %d is done> startPkt=%d  largestPkt=%d  oldestCachePkt=%d\n",
	    imgID, startPkt, largestPacketNum, oldestCachePkt);

    return TRUE;	// It's all there, so life is good.
}

void
CloseImageFile (const int imgID) {
    assert (0<=imgID);
    const imgIndex = imgID % NUM_IMAGES;
    struct Image *img = &images[imgIndex];

    printf ("Closing file for imgID %d\n",imgID);

    if (img->imgID != imgID) {
	printf ("ERROR: tried to close imgID %d, but found imgID %d\n",imgID,img->imgID);
	return;
    }

    if (NULL == img->file)
	printf ("ERROR: No file open for imgID %d\n",imgID);
    

    img->imgID = -1;
    img->bitsPerPixel = -1;
    img->firstPacketNum = -1;
    img->lastPacketNum = -1;
    img->fileDataOffset = -1;

    fclose (img->file);
    img->file = NULL;

#ifdef USE_TCL
    {	// Keep the tcl world up to date.
	char str[64];
	sprintf (str,"imgID%d",imgIndex);		Tcl_UpdateLinkedVar (interp, str);
	sprintf (str,"firstPacketNum%d",imgIndex);	Tcl_UpdateLinkedVar (interp, str);
	sprintf (str,"lastPacketNum%d",imgIndex);	Tcl_UpdateLinkedVar (interp, str);
    }
#endif

    return;
}

/* Now called asyncronously!!! */
NDDSObjectInstance 
ImageSeqCB (NDDSUpdateInfo update)
{
    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
	FifoSend (inBox, (char *)update->instance,
		  sizeof (struct ImageSequenceStruct));
	break;
    case NDDS_UPDATE_OF_OLD_DATA:
    case NDDS_NO_NEW_DATA:
    case NDDS_NEVER_RECEIVED_DATA:
	break;
    case NDDS_DESERIALIZATION_ERROR:
	NddsDebug (2, ("ImageHeaderHandler: data error\n"));
	break;
    default:
	NddsDebug (1, ("ImageFinishedHandler: bogus update %d\n",
		       update->updateStatus));
    }

    return NULL;
}

/* This does the work when a end of image arrives */
void
ImageSequenceUpdate (ImageSequence s)
{

    if (IMAGE_LAST_PACKET == s->sequenceType) {
	const int imgID = s->headerId;
	const int imgIndex = ABS(imgID) % NUM_IMAGES;

	images[imgIndex].lastPacketNum = s->x1;	// FIX: nasty hack.

	char str[64];
	sprintf (str,"lastPacketNum%d",imgIndex);
#ifdef USE_TCL
	Tcl_UpdateLinkedVar (interp, str);
#endif
    } else printf ("ImgSeqCB: unkown sequenceType %d\n", s->sequenceType);
}

int
ImgReceiveSetup (char *headers,		// name of headers to receive
		 char *packets,		// name of packets to receive
		 char *sequence,	// name of sequence packets to receive
		 char *resends)		// name of resend requests or NULL
{
    for (int i=0; i<NUM_IMAGES; i++) {
	images[i].imgHdr = ImageHeaderBlockAlloc ();
    }

    imgHdr = ImageHeaderBlockAlloc ();
    imgPkt = ImagePacketBlockAlloc ();

    imgSeqIn  = ImageSequenceAllocate (NULL, NULL, NULL);
    imgSeqOut = ImageSequenceAllocate (NULL, NULL, NULL);

    assert (imgPkt);
    assert (imgHdr);
    assert (imgSeqIn);
    assert (imgSeqOut);
    assert (headers);
    assert (packets);
    assert (sequence);

    inBox = FifoCreate (IMAGE_FIFO_SIZE, IMAGE_PACKET_BLOCK_SIZE);
    ImageHeaderNddsRegister();
    ImagePacketNddsRegister();
    ImageSequenceNddsRegister();

#define NEW_CONS NddsConsumerCreate
#define NEW_PROD NddsProducerCreate
#define SUBS NddsConsumerSubscriptionAdd
#define PROD NddsProducerProductionAdd
    {
	//int result;	// Used by PROD and SUBS
	const float dln = 1000000.0f;	// deadline
	const float msp = 0.0f;		// minimum separation
	const float per = 15.0f;	// persistence
	const float str = 1.0f;		// strength

	imgConsumer = NEW_CONS ("ImageConsumer", NDDS_IMMEDIATE, dln, msp);

	SUBS (imgConsumer, "ImageHeader",   headers,
	      imgHdr, ImageHeaderCB, NULL);
	SUBS (imgConsumer, "ImagePacket",   packets,
	      imgPkt, ImagePacketCB, NULL);
	SUBS (imgConsumer, "ImageSequence", sequence,
	      imgSeqIn, ImageSeqCB,    NULL);

	if (resends) {
	    imgSeqProducer = NEW_PROD ("imgSeqProducer", NDDS_SYNCHRONOUS,
				       per, str);
	    assert (imgSeqProducer);

	    PROD(imgSeqProducer,"ImageSequence", resends,
		 imgSeqOut,0,NULL,"resendSeq");
	}
    }
#undef NEW_CONS
#undef NEW_PROD
#undef SUBS
#undef PROD

    return OK;
}

//
//  Write the Intelligent Mechanisms Group's standard PGM file header.
//
int
WritePgmBinaryHeader (FILE* file, ImageHeader hdr) {
    int bytes=0;		// Number of bytes written to file.

    assert (file);
    assert (hdr);

    bytes += fprintf (file, "P5\n");	// PGM binary magic number.

    bytes += fprintf (file, "# IMG_STD_TYPE = 1\n");	// Mark this file as the IM groups comment format
    bytes += fprintf (file, "# IMAGE_TYPE = %s\n", hdr->name);
    // type (P5) written above.
    bytes += fprintf (file, "# ROVER_DATE = %s\n", hdr->date);
    bytes += fprintf (file, "# CAMERA = %d\n", hdr->input);
    bytes += fprintf (file, "# ROV_DEAD_REC_POS = %f %f %f\n", hdr->x, hdr->y, hdr->z);
    bytes += fprintf (file, "# ROV_COMPASS_ORIENT = %f %f %f\n", hdr->roll, hdr->pitch, hdr->yaw);
    bytes += fprintf (file, "# TILT = %f\n", hdr->tilt);
    bytes += fprintf (file, "# PAN_MIN = %f\n", hdr->pan);

    bytes += fprintf (file, "%d %d\n", hdr->row_size, hdr->col_size);
    bytes += fprintf (file, "%d\n", 255);	// Not yet passed through header.

    assert (bytes > 0);
    printf ("  Done writting image header: %d bytes\n", bytes);
    return bytes;
}

int
WritePgmBinaryPacket (const struct Image *img, const ImagePacket pkt) {
    assert (img);
    assert (img->file);
    const ImageHeader hdr = img->imgHdr;
    const int width = pkt->x2 - pkt->x1 + 1;

    int y, row;
    for (y=pkt->y1, row=0; y <= pkt->y2; y++, row++) {

	const int imgOffset = (y * hdr->row_size) + pkt->x1;
	const int fileOffset = img->fileDataOffset + /* bytesPerPixel * */ imgOffset;
	static int oldOffset = 0;
	const int dataOffset = row * width;
	/*unsigned*/ char *data = pkt->line_data.line_data_val + dataOffset;

	if (fileOffset != oldOffset) {
	    fseek (img->file, fileOffset, SEEK_SET);
	}
	int numWritten = fwrite (data, sizeof (char), width, img->file);
	oldOffset = fileOffset + numWritten;
	assert (width == numWritten);
    }
    //fflush (img->file);	// FIX: don't want to always do this!
    return OK;
}

void
copyHeader (ImageHeader to, const ImageHeader from) {
    *to = *from;	// Structure copy.
    to->name = strdup(from->name);	// Handle all the strings.
    to->type = strdup(from->type);
    to->date = strdup(from->date);
    return;
}

void
StartNdds (void) {
#ifdef	NDDS110
    int NDDS_DOMAIN = 7400;	// Set from the startup script
    NddsInit(NDDS_DOMAIN);
#else
    int NDDS_DOMAIN = 7401;	// Set from the startup script
    NddsInit(NDDS_DOMAIN, NULL);
#endif
    NddsVerbositySet(2);
    NddsVerbosityErrorSet (2);
    return;
}

#ifdef USE_TCL
void
StartTclTk (void) {
    static int argc=0;
    static char *argv[2]={"blah", "Blah"};

    interp = Tcl_CreateInterp();

    Tcl_CreateCommand (interp, "quit", QuitCallBack, NULL, NULL);

    if (Tcl_Init(interp) == TCL_ERROR) {
	printf ("Tcl_Init failed: %s\n", interp->result);
	exit(EXIT_FAILURE);
    }
  
    if (Tk_Init(interp) == TCL_ERROR) {
	printf ("Tk_Init failed: %s\n", interp->result);
	exit(EXIT_FAILURE);
    }
  
    Tcl_LinkVar (interp, "argc", (char *)&argc, TCL_LINK_INT);
    Tcl_LinkVar (interp, "argv", (char *)&argv[0], TCL_LINK_STRING);

    int linkType = TCL_LINK_INT | TCL_LINK_READ_ONLY;
    Tcl_LinkVar(interp,"pktReceived",(char*)&stats.pktReceived,linkType);
    Tcl_LinkVar(interp,"pktResendReceived",(char*)&stats.pktResendReceived,linkType);
    Tcl_LinkVar(interp,"hdrReceived", 	(char*)&stats.hdrReceived,linkType);
    Tcl_LinkVar(interp,"requestResends",(char *)&stats.requestResends,linkType);

    Tcl_LinkVar(interp,"lastPacketNum",(char *)&largestPacketNum,linkType);

    {
	int i; char str[64];
	for (i=0; i<NUM_IMAGES; i++) {
	    sprintf (str, "imgID%d", i);
	    Tcl_LinkVar(interp,str,(char *)&images[i].imgID,linkType);
	    sprintf (str, "firstPacketNum%d", i);
	    Tcl_LinkVar(interp,str,(char *)&images[i].firstPacketNum,linkType);
	    sprintf (str, "lastPacketNum%d", i);
	    Tcl_LinkVar(interp,str,(char *)&images[i].lastPacketNum,linkType);
	}
    }

    char file[256];
    strcpy (file, "imageReceive.tk");
    if (Tcl_EvalFile (interp, file) == TCL_ERROR) {
	printf ("Tcl_EvalFile failed: %s\n", interp->result);
	exit(EXIT_FAILURE);
    }
    return;
}
#endif

// -------------------------------------------------------------------------
// Debugging only code:

#ifdef DEBUG_PRINT
// These produce output that is more compact compared to nddsprint.
int print_header (ImageHeader h) {
    logMsg ("ImgHdr %d: %s %s %s\n",       h->headerId, h->name,  h->type,     h->date);
    logMsg ("ImgHdr %d: %d %d %d\n",    h->headerId, h->input, h->row_size, h->col_size);
    logMsg ("ImgHdr %d: %.2f %.2f %.2f\n", h->headerId, h->x,     h->y,        h->z);
    logMsg ("ImgHdr %d: %.2f %.2f %.2f\n", h->headerId, h->roll,  h->pitch,    h->yaw);
    logMsg ("ImgHdr %d: %.2f %.2f\n", h->headerId, h->pan,   h->tilt);
    return OK;
}
int print_packet (ImagePacket p) {
    logMsg ("ImgPkt %d-%d: %d %d\n", p->headerId,p->packet_num, p->row_len, p->line_data.line_data_len);
    logMsg ("ImgPkt %d-%d: %d,%d - %d,%d\n",p->headerId,p->packet_num, p->x1, p->y1, p->x2, p->y2);
    return OK;
}
int print_sequence (ImageSequence s) {
    logMsg ("ImageSequence %d(%d): (%d,%d)-(%d,%d)\n",s->headerId,s->sequenceType,s->x1,s->y1,s->x2,s->y2);
    return OK;
}
void print_image_struct (const struct Image *i) {
    assert (i);
    printf ("ImageStruct: id:%d    bpp:%d    lpn:%d   fdo:%d\n",
	    i->imgID, i->bitsPerPixel, i->lastPacketNum, i->fileDataOffset);
    return;
}
#endif // DEBUG_PRING

// -------------------------------------------------------------------------
// Tk User interface code.

int quitFlag = FALSE;

#ifdef USE_TCL
int
QuitCallBack (ClientData cd, Tcl_Interp *ip, int argc, char *argv[])
{
    cd = NULL;		// Not used.
    assert (ip);	// Not used.
    argc = 0;		// Not used.
    argv = NULL;	// Not used.
    printf ("Quiting...\n");
    quitFlag = TRUE;
    return TCL_OK;
}
#endif

/* Ctrl-C signal handler */
static void
QuitSigHandler (int)
{
    if (quitFlag == TRUE) {
	printf ("Got second quit request.  Exiting!\n");
					// remove this signal handler first
#ifndef __sun				// SysV version
	{				// setup clean exit on Ctrl-C
	    struct sigaction act;
	    sigemptyset (&act.sa_mask);
	    act.sa_handler = SIG_DFL;	// default handler
	    sigaction (SIGINT, &act, NULL); // un-trap Ctrl-C
	}
#else
	signal (SIGINT, SIG_DFL);
#endif
	exit (0);
    }
    quitFlag = TRUE;
}

// -------------------------------------------------------------------------

int
main (int argc, char **argv)
{
    char	*head = "imgHeader";
    char	*pack = "imgPacket";
    char	*seq =  "imgSeq";
    char	*res =  "imgResendSeq";

    if (argc > 0) printf ("Starting %s.\n", argv[0]);

#ifndef __sun				// SysV version
    {					// setup clean exit on Ctrl-C
	struct sigaction act;
	memset (&act, 0, sizeof (act));	// clear everything
	act.sa_handler = QuitSigHandler; // handler
	act.sa_flags = SA_RESTART;	// reuse handler each time
	sigaction (SIGINT, &act, NULL);	// trap Ctrl-C
    }
#else
    signal (SIGINT, QuitSigHandler);
#endif
#ifdef USE_TCL
    printf ("Starting TclTk...\n");
    StartTclTk();
#endif
    printf ("Starting Ndds...\n");
    StartNdds();
    printf ("ImgReceiveSetup (%d) %s %s %s %s...\n",
	    IMAGE_PACKET_SIZE, head, pack, seq, res);
    ImgReceiveSetup(head, pack, seq, res);
#ifdef USE_TCL
    while (1 == Tcl_DoOneEvent (TCL_DONT_WAIT)); // don't want to wait in here.
#endif

    printf ("Entering polling loop. Ctrl-C to exit\n");
    while (!quitFlag) {
	sleep_us (1);	// Sleep minimum time to force reschedule.  Keeps load down.
	for (;;) {
	    char *chunk;
	    int len = FifoPeek (inBox, &chunk);
	    if (len == IMAGE_HEADER_BLOCK_SIZE) {
		ImageHeader h = (ImageHeader)chunk;
		ImageHeaderBlockFixup (h);	/* muck with the data pointer*/
		ImageHeaderUpdate (h);
		FifoReceive (inBox, NULL, 9999); /* free FIFO entry */
	    } else if (len == IMAGE_PACKET_BLOCK_SIZE) {
		ImagePacket p = (ImagePacket)chunk;
		ImagePacketBlockFixup (p);	/* muck with the data pointer*/
		ImagePacketUpdate (p);
		FifoReceive (inBox, NULL, 9999); /* free FIFO entry */
	    } else if (len == sizeof (struct ImageSequenceStruct)) {
		ImageSequence s = (ImageSequence)chunk;
		ImageSequenceUpdate (s);
		FifoReceive (inBox, NULL, 9999); /* free FIFO entry */
	    } else if (len > 0) {
		printf ("NddsImagePoll: Received message of odd size! %d\n",
			len);
		FifoReceive (inBox, NULL, 9999); /* free FIFO entry */
	    } else
		break;				/* no new data */
	}
#ifdef USE_TCL
	Tcl_DoOneEvent (TCL_DONT_WAIT); // don't want to wait in here.
#endif
	// FIX: look for old missing packets to requested again.
    }
    // remove this signal handler first
#ifndef __sun				// SysV version
    {				// setup clean exit on Ctrl-C
	struct sigaction act;
	sigemptyset (&act.sa_mask);
	act.sa_handler = SIG_DFL;	// default handler
	sigaction (SIGINT, &act, NULL); // un-trap Ctrl-C
    }
#else
    signal (SIGINT, SIG_DFL);
#endif
    printf ("\nimageReceive Exiting.\n");
    return 0;
}
