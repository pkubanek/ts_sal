// cache images from another source and provide resends
// for multiple destinations.
// The history is long and sordid.  See also imageReceive, libimgtcl, nddswish


// Standard unix includes
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>			// for fchmod
#include <time.h>			// For clock ticks.
#include <signal.h>			// For sigaction

// NDDS includes
#include <NDDS.h>

// NDDS type includes
#include <ImageHeader.h>
#include <ImagePacket.h>
#include <ImageSequence.h>
#include <event.h>

// Include file for both Unix and VxWorks
#define USE_BIG_PACKETS			/* always allow biggest packets */
#include "imageNdds.h"
#include "imageTimer.h"
#include "fifo.h"

#ifndef MIN
#define MIN(x,y)	(((x) < (y)) ? (x) : (y))
#define MAX(x,y)	(((x) > (y)) ? (x) : (y))
#endif

// at T1 (1.544Mbs) and 7680byte image data, we get 25packets/sec
#define IMAGE_FIFO_SIZE	(NUM_CACHE_PACKETS/4)// size here depends on worst load

// how may image #s back we will re-request missing packets for
#define OLD_IMAGE_LIMIT	2
#define REQUEST_LIMIT	4		// min seconds between re-requests
#define RESEND_LIMIT	4		// min seconds between re-resends

// how often to look for resends to get
#define IMAGE_SCRUB_RATE 6		// every n seconds

#define SAME_PKT(a,b) ((ABS (a->headerId) == b->headerId) \
&& (a->packet_num == b->packet_num) && (a->x2 == b->x2) && (a->y2 == b->y2))

//
// Types only used in this file.
//
struct _Stats {
    int pktReceived;
    int pktResendReceived;
    int hdrReceived;
    int requestResends;
};

//
// Global variables.
//
static ImagePacket	imgInPkt;	// in from original sender
static ImageHeader	imgInHdr;	// in from original sender
static ImageSequence	imgInSeq;	// end image from original sender
static ImageSequence	imgInResend;	// resend request to original sender

static ImagePacket	imgOutPkt;	// forwarded data
static ImageHeader	imgOutHdr;	// forwarded data
static ImageSequence	imgOutSeq;	// forwarded end of image
static ImageSequence	imgOutResend;	// resend request to us

static NDDSConsumer	imgConsumer;	// asynchronous consumer
static NDDSProducer	imgResendProducer; // resend request to original sender
static NDDSProducer	imgHdrOutProducer; // fowarded headers
static NDDSProducer	imgPktOutProducer; // forwarded packets
static NDDSProducer	imgSeqOutProducer; // forward end of image

static eventStruct	saveEvent;	// for image save control
static NDDSConsumer	eventConsumer;	// polled consumer

static char emptyData[IMAGE_PACKET_BLOCK_SIZE];	// array of empty data
static int imageAbort = 0;		// abort image sends
static int fifoFulls = 0;

int debug_level = 1;			// adjustable debug level
int imageSaves = -9;			// set higher than resolutions to save

#define NUM_CACHE_HEADERS	8
					// num_cache_packets is in imageNdds.h
ImagePacket pktCache[NUM_CACHE_PACKETS]; // our packet cache
					// convert packet number to cache entry
#define PKT_GET_INDEX(n)	((n) % NUM_CACHE_PACKETS)

ImageHeader headerCache[NUM_CACHE_HEADERS]; // our image header cache
typedef struct _IMAGE {
    int imgID;				// header ID for this file (or 0)
    FILE *file;				// file to write to
    ImageHeader	header;			// pointer into headerCache
    int	lastSent;			// last packet number written
    time_t	lastScrub;		// time of last scrub
    signed char	gotPkt[1024];		/* HACK assumes <= 960 pkts/image */
} IMAGE_INFO;

typedef struct _PKT_INFO {
    time_t sent;			// time of when we sent it
    time_t resent;			// time of when we last resent it
    time_t requested;			// time last requested packet
} PKT_INFO;

static time_t	currentTime;		// current time (seconds)
static time_t	emptyTime;		// time when fifo was last emptied
static time_t	flowTime;		// when flow control last requested

IMAGE_INFO 	images [NUM_CACHE_HEADERS]; // extra image info
PKT_INFO	packets [NUM_CACHE_PACKETS]; // extra packet info

static int lastPacketRecv=0;	// Keeps track of the last packet received
static int largestImgID=-1;	// Keep track of the largest image id received.

static struct _Stats stats;

static FIFO_ID	inBox;

const float sleepTime = 0.0001;	// Seconds round trip time in seconds

//
// Local function prototypes.
//

static NDDSObjectInstance ImageSeqCB (NDDSUpdateInfo update);

#ifndef NDEBUG
int print_header (ImageHeader h);
int print_packet (ImagePacket p);
int print_sequence (ImageSequence s);
void print_image_struct (const struct Image *i);
#endif // DEBUG_PRINT

static int debugLevel=3;		// debugging for this file only
#ifdef NDEBUG
#define NddsDebug(n,s)                  /* expand to nothing */
#else
#define NddsDebug(n,s)  (((n) <= debugLevel) ?  printf s :0)
#endif

#undef ABS
#undef MAX
#define ABS(f)    ( (f) >  0  ? (f) : -(f) )
#define MAX(a,b)  ( (a) > (b) ? (a) :  (b) )

// -------------------------------------------------------------------------
// Debugging only code:

#ifndef NDEBUG
// These produce output that is more compact compared to nddsprint.
int print_header (ImageHeader h) {
    printf ("imgInHdr %d: %s %s %s\n",
	    h->headerId, h->name,  h->type,     h->date);
    printf ("imgInHdr %d: %d %d %d\n",
	    h->headerId, h->input, h->row_size, h->col_size);
    printf ("imgInHdr %d: %.2f %.2f %.2f\n",
	    h->headerId, h->x,     h->y,        h->z);
    printf ("imgInHdr %d: %.2f %.2f %.2f\n",
	    h->headerId, h->roll,  h->pitch,    h->yaw);
    printf ("imgInHdr %d: %.2f %.2f\n",
	    h->headerId, h->pan,   h->tilt);
    return 0;
}
int print_packet (ImagePacket p) {
    printf ("imgInPkt %d-%d: %d %d\n",
	    p->headerId,p->packet_num, p->row_len, p->line_data.line_data_len);
    printf ("imgInPkt %d-%d: %d,%d - %d,%d\n",
	    p->headerId,p->packet_num, p->x1, p->y1, p->x2, p->y2);
    return 0;
}
int print_sequence (ImageSequence s) {
    printf ("ImageSequence %d(%d): (%d,%d)-(%d,%d)\n",
	    s->headerId,s->sequenceType,s->x1,s->y1,s->x2,s->y2);
    return 0;
}
void print_image_struct (const IMAGE_INFO *i) {
    assert (i);
    printf ("ImageStruct: id: %d  file: %p lastSent: %d  last: %ld\n",
	    i->imgID, i->file, i->lastSent, i->lastScrub);
    return;
}
#endif // DEBUG_PRING

//======================================================================
/* Direct NDDS callback for header productions */
/* Now called asyncronously!!! */
/* These just stuff them in a fifo for later sorting */
NDDSObjectInstance
ImageHeaderCB (NDDSUpdateInfo update)
{
    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
	if (FifoSend (inBox, (char *)update->instance,
		      IMAGE_HEADER_BLOCK_SIZE) < 0) {
	    printf ("FIFO FULL! dropped header.\n");
	    ++fifoFulls;
	}
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

/* Now called asyncronously!!! */
NDDSObjectInstance
ImagePacketCB (NDDSUpdateInfo update)
{
    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
	if (FifoSend (inBox, (char *)update->instance,
		      IMAGE_PACKET_BLOCK_SIZE) < 0) {
	    printf ("FIFO FULL! dropped packet\n");
	    ++fifoFulls;
	}
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

/* Now called asyncronously!!! */
// this handled both end of image from original sender and resend request to us
// either way, we stuff them in the fifo and sort it out later
static NDDSObjectInstance 
ImageSeqCB (NDDSUpdateInfo update)
{
    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
    {
	ImageSequence	s = (ImageSequence) update->instance;
	if (s->sequenceType == IMAGE_ABORT) { // mark abort request
	    if (imageAbort <= 0) imageAbort = 1;
	    else ++imageAbort;
	}
	if (FifoSend (inBox, (char *)update->instance,
		      sizeof (struct ImageSequenceStruct)) < 0) {
	    printf ("FIFO FULL! dropped sequence\n");
	    ++fifoFulls;
	}
	break;
    }
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

//======================================================================
/* Direct NDDS callback for header productions */
/* Now called asyncronously!!! */
/* These just stuff them in a fifo for later sorting */
NDDSObjectInstance
SaveEventCB (NDDSUpdateInfo update)
{
    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
    {
	event ev = (event)update->instance;
	if ((ev->dummyFiller >= 1) && (ev->dummyFiller <= 9)) {
	    imageSaves = ev->dummyFiller;
	    printf ("Enabling image saves %d\n", imageSaves);
	} else if ((ev->dummyFiller >= '1') && (ev->dummyFiller <= '9')) {
	    imageSaves = ev->dummyFiller - '0';
	    printf ("Enabling image saves %d\n", imageSaves);
	} else {
	    printf ("Disabling future image saves\n");
	    imageSaves = -1;
	}
    }
	break;
    case NDDS_UPDATE_OF_OLD_DATA:
    case NDDS_NO_NEW_DATA:
    case NDDS_NEVER_RECEIVED_DATA:
	return NULL;
    case NDDS_DESERIALIZATION_ERROR:
	NddsDebug (2, ("SaveEvent: data error\n"));
	break;
    default:
	NddsDebug (1, ("SaveEvent: bogus update %d\n",
		       update->updateStatus));
    }
    return NULL;
}

/* ask for a resend (sequence) from original sender */
void
RequestResend (int headerId, int pktNum, int pktNum2) {
    if (!imgInResend) return;		// dont ask for resends

    assert (0<=pktNum);
    imgInResend->headerId = headerId; assert (0<=headerId);
    // HACK: we reuse this message type
    // stuff requested packet start in x1, end in x1
    imgInResend->x1 = pktNum;
    imgInResend->x2 = pktNum2;		// ask for a sequence (maybe)
    imgInResend->y1 = 0;
    imgInResend->y2 = 2*fifoFulls + currentTime - emptyTime; // flow control
    imgInResend->sequenceType = PACKET_RESEND;

    printf ("Requesting %d - %d, img %d\n",
	    pktNum, pktNum2, headerId); // DEBUG
    NddsProducerSample (imgResendProducer);

    stats.requestResends++;
}

//======================================================================
// write out an image and close the file
// fill in blanks with null data as needed
void
ImageFlush (IMAGE_INFO *img)
{
    int	pSize;
    // write out outstanding data
    { // find the size of the last thing we wrote
	const pInd = PKT_GET_INDEX (img->header->first_packet
				    + img->lastSent);
	pSize = pktCache [pInd]->line_data.line_data_len;
    }
    NddsDebug (1, ("Flushing image %d ",
		   img->header->headerId));
    while ((img->lastSent + img->header->first_packet)
	   < img->header->last_packet) {
	if (img->gotPkt[img->lastSent+1] <= 0) { // write blank data
	    fwrite (emptyData, pSize, 1, img->file);
	    NddsDebug (1, ("E"));
	} else {			// write real data
	    const pInd = PKT_GET_INDEX (img->header->first_packet
					+ img->lastSent + 1);
	    ImagePacket p = pktCache [pInd];
	    fwrite (p->line_data.line_data_val,
		    p->line_data.line_data_len,
		    1, img->file);
	    NddsDebug (1, ("w"));
	}
	++img->lastSent;
    }
    fchmod (fileno (img->file), 0664);	// set group writable
    fclose (img->file);		// close old file
    NddsDebug (1, ("\n"));
}

/* This does the work when a new header arrives */
void
ImageHeaderUpdate (ImageHeader hdr)
{
    const int imgID = hdr->headerId;
    const int imgIndex = imgID % NUM_CACHE_HEADERS;	assert (0<=imgID);
    IMAGE_INFO *img = &images[imgIndex]; // image info
    ImageHeader	cHead = headerCache[imgIndex]; // header to fill in
    if (cHead->headerId == hdr->headerId) {
	printf ("Warning Sending duplicate header %d\n", hdr->headerId);
	//return;				// duplicate header, drop it
    }

    if ((img->file) && (img->lastSent >= 0)) { // close old image file
	ImageFlush (img);
    }

    lastPacketRecv = hdr->first_packet - 1; // setup next expected packet


    if (img->imgID > largestImgID) largestImgID = img->imgID; // stats
    stats.hdrReceived++;
					// pass on a copy to the world
    ImageHeaderBlockCopy (imgOutHdr, hdr);
    ImageNdds_WaitRoom();
    NddsProducerSample (imgHdrOutProducer);

    ImageHeaderBlockCopy (cHead, hdr);	// copy over new header
    img->imgID = hdr->headerId;		// setup image info
    img->lastScrub = currentTime;
    img->lastSent = -1;			// so that 0 is next to send
    img->header = cHead;
    memset (&img->gotPkt, 0, sizeof (img->gotPkt)); /* clear got pkt */

    if (img->header->resolution <= imageSaves) {
#if 0					// use local date for file name
	char	date[64];		// generate a name based on time
	GetDateString (date);
#else  // user header date for file name
	char	*date = img->header->date;
#endif
	char	*cp = date;
	for (; *cp && (*cp != ' '); ++cp); // skip first word
	if (*cp) ++cp;
	char	*name = cp;
	for (; *cp && (*cp != '\n'); ++cp) // trim newline
	    if ((*cp == ' ') || (*cp == ':')) *cp = '.'; // convert space and :

	// tack camera number, resolution, and file type onto name
	sprintf (cp, ".%c.%d.p%cm",
		 (img->header->resolution > 0)
		 ? ('a'+ img->header->resolution -1) : 'z',
		 img->header->input,
		 (img->header->type[1] == '5') ? 'g' : 'p');
	img->file = fopen (name, "w");
	if (img->file) {		// fill in a standard header
	    printf ("Opened file %s\n", name);
	    fprintf (img->file, "P%c\n", img->header->type[1]);
	    fprintf (img->file, "#headerId= %d\n", img->header->headerId);
	    fprintf (img->file, "#name= %s\n", img->header->name);
	    fprintf (img->file, "#type= %s\n", img->header->type);
	    fprintf (img->file, "#date= %s\n", img->header->date);
	    fprintf (img->file, "#input= %d\n", img->header->input);
	    fprintf (img->file, "#row_size= %d\n", img->header->row_size);
	    fprintf (img->file, "#col_size= %d\n", img->header->col_size);
	    fprintf (img->file, "#first_packet= %d\n", img->header->first_packet);
	    fprintf (img->file, "#last_packet= %d\n", img->header->last_packet);
	    fprintf (img->file, "#shutter= %d\n", img->header->shutter);
	    fprintf (img->file, "#input_gain= %g\n", img->header->input_gain);
	    fprintf (img->file, "#input_offset= %g\n", img->header->input_offset);
	    fprintf (img->file, "#pan= %g\n", img->header->pan);
	    fprintf (img->file, "#tilt= %g\n", img->header->tilt);
	    fprintf (img->file, "#x= %g\n", img->header->x);
	    fprintf (img->file, "#y= %g\n", img->header->y);
	    fprintf (img->file, "#z= %g\n", img->header->z);
	    fprintf (img->file, "#roll= %g\n", img->header->roll);
	    fprintf (img->file, "#pitch= %g\n", img->header->pitch);
	    fprintf (img->file, "#yaw= %g\n", img->header->yaw);
	    fprintf (img->file, "#resolution= %d\n", img->header->resolution);
	    fprintf (img->file, "#xDot= %g\n", img->header->xDot);
	    fprintf (img->file, "#yDot= %g\n", img->header->yDot);
	    fprintf (img->file, "#zDot= %g\n", img->header->zDot);
	    fprintf (img->file, "#rollDot= %g\n", img->header->rollDot);
	    fprintf (img->file, "#pitchDot= %g\n", img->header->pitchDot);
	    fprintf (img->file, "#yawDot= %g\n", img->header->yawDot);
	    fprintf (img->file, "%d %d\n255\n",
		     img->header->row_size, img->header->col_size);
	} else {
	    printf ("File open %s Failed!\n", name);
	}
    } else {
	img->file = NULL;
    }

    // we should check if we want to ask for resend from previous images
    return;
}

/* This does the work when a data packet arrives */
void
ImagePacketUpdate (ImagePacket pkt)
{
    const imgID = pkt->headerId;
    const imgIndex = (ABS(imgID)) % NUM_CACHE_HEADERS;
    IMAGE_INFO *img = images+imgIndex;

    const pktIndex = PKT_GET_INDEX (pkt->packet_num);
    ImagePacket	cPkt = pktCache[pktIndex]; // packet cache to fill in
    PKT_INFO	*pi = packets+pktIndex;

					// TODO check if this is redundant
    if (SAME_PKT (pkt, cPkt)
	&& ((currentTime - pi->sent) <= RESEND_LIMIT)) { // its the same
	printf ("D%d ", cPkt->packet_num);
	return;				// do nothing
    }
    pi->sent = currentTime;
    ImagePacketBlockCopy (cPkt, pkt);
    //printf ("Pkt %d -> %d. ", pkt->packet_num, pktIndex);

    if (pkt->headerId >= 0) {		// a new packet
	stats.pktReceived++;
    } else {				// got a resent packet
	cPkt->headerId = ABS (cPkt->headerId); // store positive header iD
	printf ("F%d ", cPkt->packet_num);
	stats.pktResendReceived++;
    }

					// pass on to the world
    ImagePacketBlockCopy (imgOutPkt, pkt);
    ImageNdds_WaitRoom();
    NddsProducerSample (imgPktOutProducer);
    
    if (pkt->headerId >= 0) {		// new packet, check sequence
	if (pkt->packet_num > lastPacketRecv + 1) {
	    /*printf ("Got %d Expected %d\n",
		    pkt->packet_num, lastPacketRecv + 1);*/
	    RequestResend (pkt->headerId, // ask for whole missing sequence
			   lastPacketRecv+1, pkt->packet_num-1);
	    for (int ii = lastPacketRecv+1; ii < pkt->packet_num; ++ii)
		packets[PKT_GET_INDEX (ii)].requested = currentTime;
	}
    }

    if (lastPacketRecv < pkt->packet_num) lastPacketRecv = pkt->packet_num;

    if (img->imgID == cPkt->headerId) {	// mark image status
					// packet number relative to image
	int	inum = pkt->packet_num - img->header->first_packet;
	img->gotPkt [inum] = 1;
					// see if this is in sequence
	if ((img->file) && (inum == (img->lastSent+1))) {
	    fwrite (pkt->line_data.line_data_val,
		    pkt->line_data.line_data_len,
		    1, img->file);
	    img->lastSent = inum;
	    // see if subsequent packets need to write out
	    while ((img->gotPkt[img->lastSent+1]) > 0) {
		const pInd = PKT_GET_INDEX (img->header->first_packet
					    + img->lastSent + 1);
		ImagePacket p = pktCache [pInd];
		if (p->headerId != img->imgID) { // is it really our packet
		    img->gotPkt[img->lastSent+1] = 0;
		    printf ("Shadow packet! %d\n",
			    img->header->first_packet + img->lastSent + 1);
		    break;
		}
		fwrite (p->line_data.line_data_val,
			p->line_data.line_data_len,
			1, img->file);
		if ((++img->lastSent + img->header->first_packet)
		    > img->header->last_packet)
		    break;
	    }
	}
    } // else re-request header ?
}

// Handle end of image or resend request (same packet type)
void
ImageSequenceUpdate (ImageSequence s)
{
    if (IMAGE_LAST_PACKET == s->sequenceType) {	// end of image
	//const int imgID = s->headerId;
	//const int imgIndex = ABS(imgID) % NUM_CACHE_HEADERS;

	// check for any resends that we need
					// pass on to the world
	*imgOutSeq = *s;
	ImageNdds_WaitRoom();
	NddsProducerSample (imgSeqOutProducer);
    } else if (PACKET_RESEND == s->sequenceType) {// resend request
					// packet_num is stuffed into x1
	printf ("Resent %d (%d): ", s->headerId, s->y2);
	ImageNdds_ThrottleThroughPut (s->y2*2);

	for (int i = s->x1; i <= s->x2; ++i) { // resend each one
	    const pktIndex = PKT_GET_INDEX (i);
	    PKT_INFO	*pi = packets+pktIndex;
					// find it in the cache
	    ImagePacket	cPkt = pktCache[pktIndex]; // packet cache entry
	    // either we never received it, or its too old
	    if ((cPkt->packet_num != i)
		|| ((cPkt->headerId != s->headerId)	// headers match?
		    && (cPkt->headerId != -s->headerId))) {
		printf ("not cached: %d ", i);
		if ((currentTime - pi->requested) >= REQUEST_LIMIT) {
		    *imgInResend = *s;	// pass on the resend request
		    printf ("(requesting) "); // DEBUG
		    imgInResend->x1 = imgInResend->x2 = i;
		    imgInResend->y2 = 2*fifoFulls + currentTime - emptyTime;
		    NddsProducerSample (imgResendProducer);
		    pi->requested = currentTime;
		} else {
		    printf ("<asked at %ld> ", pi->requested);
		}
		continue;
	    } 
	    if ((currentTime - pi->resent) >= RESEND_LIMIT) {
		printf ("%d, ", cPkt->packet_num);
		ImagePacketBlockCopy (imgOutPkt, cPkt);
		// NOTICE: resends have a negative headerId!!!
		imgOutPkt->headerId = -ABS(imgOutPkt->headerId);

		ImageNdds_WaitRoom();		// send it
		NddsProducerSample (imgPktOutProducer);
		pi->resent = currentTime;
	    } else printf ("<%d> ", cPkt->packet_num);
	}
	printf ("\n");
    } else if (HEADER_RESEND == s->sequenceType) {// resend header request
	const int imgID = s->headerId;
	const int imgIndex = imgID % NUM_CACHE_HEADERS;
	assert (0<=imgID);
	ImageHeader	cHead = headerCache[imgIndex]; // header to fill in
	if (imgID != cHead->headerId) {
	    printf ("Header not cached %d ", cHead->headerId);
		// figure out if we never received it and re-request
	    if ((0 == cHead->headerId)
		|| (ABS (largestImgID - s->headerId) <= OLD_IMAGE_LIMIT)) {
		*imgInResend = *s;	// pass on the resend request
		printf ("(requesting) "); // DEBUG
		imgInResend->y2 = 2*fifoFulls + currentTime - emptyTime;
		NddsProducerSample (imgResendProducer);
	    }
	    printf ("\n");
	    return;
	}
	printf ("Resending Header %d (%d)\n", imgID, s->y2);
	ImageNdds_ThrottleThroughPut (s->y2*2);
	ImageHeaderBlockCopy (imgOutHdr, cHead);
	ImageNdds_WaitRoom();
	NddsProducerSample (imgHdrOutProducer);
    } else if (IMAGE_ABORT == s->sequenceType) { // abort request
	*imgInResend = *s;

	printf ("Passing on abort img %d\n", s->headerId); // DEBUG
	imgInResend->y2 = 2*fifoFulls + currentTime - emptyTime;
	NddsProducerSample (imgResendProducer);
					// mark no resend requests
	const int imgID = s->headerId;
	const int imgIndex = imgID % NUM_CACHE_HEADERS;
	printf ("Cancelling image scrubs: ");
	for (int i=0; i < NUM_CACHE_HEADERS; ++i) {
	    if (images[imgIndex].lastScrub < 0) continue;
	    if (!images[imgIndex].file) continue;
	    printf ("%d ", s->headerId);
	    images[imgIndex].lastScrub = -1;
	}
	printf ("\n");
    } else {
	printf ("ImgSeqCB: unknown sequenceType %d\n", s->sequenceType);
    }
}

/* search and see what packets are missing */
int
ImagePacketFindMisses (IMAGE_INFO *store, int max_packet)
{
    int todo = 0;
    int	skipped = 0;
    int i;
    int first = store->header->first_packet;
    int last = MIN (max_packet, store->header->last_packet);
    signed char *cp = store->gotPkt;
    /* BUG breaks at packet num wrap */
    NddsDebug (1, ("Finding resends %d, %d - %d (%d): ",
		   store->header->headerId,
		   first, last, store->header->last_packet));
    /* TODO, group requests */
    for (i=0; i <= (last-first); ++i, ++cp) {
	if (0 == *cp) {
	    int	end = i;
	    signed char *ep = cp;

	    for (; (0 == ep[1]) && (end <= (last-first));
		 ++ep, ++end);	/* find extent of drops */
	    todo += end - i + 1;

	    RequestResend (store->header->headerId, i+first, end+first);
	    while (cp <= ep) *cp++ = -1; /* hold off on re-request */
	    i = end;		/* move to end of block */
	    cp = ep;
	    if (todo > 50) break;	// dont ask for too many at once
	} else if (*cp < 0) {	/* decay hold off */
	    *cp += 1;
	    ++skipped;
	    NddsDebug (1, ("[%d] ", i + first));
	} else if (*cp != 1) {	/* DEBUG */
	    NddsDebug (1, ("[%d, %d = %d] ", i, i+first, *cp));
	}
    }

    NddsDebug (1, ("Done (%d, %d).\n", todo, skipped));

    if ((last == store->header->last_packet) // scanned everything
	&& (0 == (todo + skipped))) {	/* no resends todo, complete! */
	store->lastScrub = -1;		/* none needed */

	if (store->file) {		// flush to file
	    // file should have been written out already
	    fclose (store->file);
	    store->file = NULL;
	    printf ("Closing Image %d\n", store->header->headerId);
	}
    } else {
	store->lastScrub = currentTime;		/* reset timeout */
    }
    return todo+skipped;
}

//======================================================================
// setup everything we listen to
int
ImgReceiveSetup (char *headers,		// name of headers to receive
		 char *packets,		// name of packets to receive
		 char *sequence,	// name of sequence packets to receive
		 char *resends,		// name of resend requests or NULL
		 char *saveName)	// name of save level events
{
    printf ("ImgReceiveSetup (%d) %s %s %s %s...\n",
	    IMAGE_PACKET_SIZE, headers, packets, sequence, resends);

    imgInHdr = ImageHeaderBlockAlloc ();
    imgInPkt = ImagePacketBlockAlloc ();

    imgInSeq  = ImageSequenceAllocate (NULL, NULL, NULL);
    if (resends && *resends)
	imgInResend = ImageSequenceAllocate (NULL, NULL, NULL);
    else
	imgInResend = NULL;

    assert (imgInPkt);
    assert (imgInHdr);
    assert (imgInSeq);
    assert (headers);
    assert (packets);
    assert (sequence);
					// fifo for incoming stuff
    printf ("\tAllocating receive fifo %d @%d\n",
	    IMAGE_FIFO_SIZE, IMAGE_PACKET_BLOCK_SIZE);
    inBox = FifoCreate (IMAGE_FIFO_SIZE, IMAGE_PACKET_BLOCK_SIZE);

    printf ("\tAllocating image headers cache %d\n", NUM_CACHE_HEADERS);
    for (int i=0; i<NUM_CACHE_HEADERS; i++) {
	headerCache[i] = ImageHeaderBlockAlloc ();
	if (NULL == headerCache[i]) {
	    printf ("Image header cache allocation failed.");
	    return ERROR;
	}
    }

    printf ("\tAllocating image packet cache %d @%d\n",
	    NUM_CACHE_PACKETS, IMAGE_PACKET_BLOCK_SIZE);
    for (int i=0; i<NUM_CACHE_PACKETS; i++) {
	pktCache[i] = ImagePacketBlockAlloc ();
	if (NULL == pktCache[i]) {
	    printf ("Image packet cache allocation failed.");
	    return ERROR;
	}
    }

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
	      imgInHdr, ImageHeaderCB, NULL);
	SUBS (imgConsumer, "ImagePacket",   packets,
	      imgInPkt, ImagePacketCB, NULL);
	SUBS (imgConsumer, "ImageSequence", sequence,
	      imgInSeq, ImageSeqCB,    NULL);

	eventConsumer = NEW_CONS ("RouterLogConsumer", NDDS_POLLED, dln, msp);
	SUBS (eventConsumer, "event", saveName,
	      &saveEvent, SaveEventCB,    NULL);
	
	if (resends && *resends) {
	    assert (imgInResend);
	    imgResendProducer = NEW_PROD ("imgResendProducer",
					  NDDS_SYNCHRONOUS,
					  per, str);
	    assert (imgResendProducer);

#ifdef NDDS_1_11Q
	    PROD(imgResendProducer,"ImageSequence", resends,
		 imgInResend,0,NULL,"resendSeq");
#else
	    PROD(imgResendProducer,"ImageSequence", resends,
		 imgInResend,0,NULL,0,NULL,"resendSeq");
#endif
	}
    }
#undef NEW_CONS
#undef NEW_PROD
#undef SUBS
#undef PROD

    return 0;
}
// setup everything we listen to
// call after ImgReceiveSetup
int
ImgSendSetup (char *headers,		// name of headers to receive
		 char *packets,		// name of packets to receive
		 char *sequence,	// name of sequence packets to receive
		 char *resends)		// name of resend requests or NULL
{
    printf ("ImgSendSetup (%d) %s %s %s %s...\n",
	    IMAGE_PACKET_SIZE, headers, packets, sequence, resends);

    imgOutHdr = ImageHeaderBlockAlloc ();
    imgOutPkt = ImagePacketBlockAlloc ();

    imgOutSeq  = ImageSequenceAllocate (NULL, NULL, NULL);
    imgOutResend = ImageSequenceAllocate (NULL, NULL, NULL);

    assert (imgOutPkt);
    assert (imgOutHdr);
    assert (imgOutSeq);
    assert (imgOutResend);
    assert (headers);
    assert (packets);
    assert (sequence);

#define NEW_CONS NddsConsumerCreate
#define NEW_PROD NddsProducerCreate
#define SUBS NddsConsumerSubscriptionAdd
#define PROD NddsProducerProductionAdd
    {
	//int result;	// Used by PROD and SUBS
	const float per = 15.0f;	// persistence
	const float str = 1.0f;		// strength

	imgHdrOutProducer = NEW_PROD ("imgHdrProducer", NDDS_SYNCHRONOUS,
				      per, str);
	assert (imgHdrOutProducer);
#ifdef NDDS_1_11Q
	PROD(imgHdrOutProducer,"ImageHeader", headers,
	     imgOutHdr,0,NULL,NULL);
#else
	PROD(imgHdrOutProducer,"ImageHeader", headers,
	     imgOutHdr,0,NULL,0,NULL,NULL);
#endif

	imgPktOutProducer = NEW_PROD ("imgPktProducer", NDDS_SYNCHRONOUS,
				      per, str);
	assert (imgPktOutProducer);
#ifdef NDDS_1_11Q
	PROD(imgPktOutProducer,"ImagePacket", packets,
	     imgOutPkt,0,NULL,NULL);
#else
	PROD(imgPktOutProducer,"ImagePacket", packets,
	     imgOutPkt,0,NULL,0,NULL,NULL);
#endif

	imgSeqOutProducer = NEW_PROD ("imgSeqProducer", NDDS_SYNCHRONOUS,
				      per, str);
	assert (imgSeqOutProducer);
#ifdef NDDS_1_11Q
	PROD(imgSeqOutProducer,"ImageSequence", sequence,
	     imgOutResend,0,NULL,NULL);
#else
	PROD(imgSeqOutProducer,"ImageSequence", sequence,
	     imgOutResend,0,NULL,0,NULL,NULL);
#endif

	SUBS (imgConsumer, "ImageSequence", resends,
	      imgOutResend, ImageSeqCB,    NULL);
    }
#undef NEW_CONS
#undef NEW_PROD
#undef SUBS
#undef PROD
    return 0;
}

// Initialize general NDDS stuff
int
StartNdds (int NDDS_DOMAIN, int multi) {
#ifdef	NDDS110
    NddsInit(NDDS_DOMAIN);
#else
    if (multi) {
	NDDSMulticastInfoStorage mdom;
#ifdef NDDS_1_11Q
	mdom.domain = 7402;
	mdom.ttl = 5;
	printf ("Enabling multi-cast %d %d\n", mdom.domain, mdom.ttl);
#else
	mdom.Domain = 7402;
	mdom.TTL = 5;
	printf ("Enabling multi-cast %d %d\n", mdom.Domain, mdom.TTL);
#endif
	NddsInit(NDDS_DOMAIN, &mdom);
    } else {
	NddsInit(NDDS_DOMAIN, NULL);
    }
#endif
    printf ("NDDSInit complete %d\n", NDDS_DOMAIN);
    NddsVerbositySet ((debug_level >= 3) ? 2 : 1);
    NddsVerbosityErrorSet ((debug_level >= 3) ? 2 : 1);
    sleep_us (500000);			// let NDDS get going

    ImageHeaderNddsRegister();
    ImagePacketNddsRegister();
    ImageSequenceNddsRegister();
    eventNddsRegister();		// for save control from nddswish
    return OK;
}

int quitFlag = 0;

/* Ctrl-C signal handler */
static void
QuitSigHandler (int)
{
    if (quitFlag > 2) {
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
    ++quitFlag;
}

//======================================================================
void
usage (void)
{
    printf ("Usage: imageroute [speed] [-domain num] [-multi] \n");
    printf ("\t[-in prefix] [-out prefix]\n");
    printf ("\t[-header name] [-packet name] [-sequence name]\n");
    printf ("\t[-resend_sequence name] [-Help] [-Debug level] [-Save level] files*\n");
    printf ("Ex: imageroute 1544000 -i imgR -o img\n");
    exit (2);
}

int
main (int argc, char **argv)
{
    int speed = 600000;
    int domain = 7401;
    int	multicast = 0;
    char *inPrefix = "imgR";
    char *outPrefix = "img";
    char *hName = "Header";
    char *pName = "Packet";
    char *sName = "Seq";
    char *rName = "ResendSeq";
    char *eName = "routerLog";
    char headBuff[64], packBuff[64], seqBuff[64], rSeqBuff[64];
    char saveBuff[64];

    time (&currentTime);		// update time
    emptyTime = currentTime;

    ++argv; --argc;			// skip program name
    while (argc) {			// get initial arguments
	if ((**argv >= '0') && (**argv <= '9')) {
	    speed =  atoi (*argv);	// set speed
	} else if ('-' == (*argv)[0]) {	// argument
	    switch ((*argv)[1]) {
	    case 'H':			// help
		usage();		// never returns
	    case 'm':			// use multi-cast
		printf ("Multicast supported yet???\n");
		++multicast;
		break;
	    case 'D':			// debug level
		++argv; --argc;
		if (!argc) usage();
		debug_level = atoi (*argv);
		break;
	    case 'S':			// saves level
		++argv; --argc;
		if (!argc) usage();
		imageSaves = atoi (*argv);
		break;
	    case 'd':			// domain
		++argv; --argc;
		if (!argc) usage();
		domain = atoi (*argv);
		break;
	    case 'i':			// incoming message name prefix
		++argv; --argc;
		if (!argc) usage();
		inPrefix = *argv;
		break;
	    case 'o':			// outgoing message name prefix
		++argv; --argc;
		if (!argc) usage();
		outPrefix = *argv;
		break;
	    case 'h':			// header name
		++argv; --argc;
		if (!argc) usage();
		hName = *argv;
		break;
	    case 'p':			// packet name
		++argv; --argc;
		if (!argc) usage();
		pName = *argv;
		break;
	    case 's':			// sequence name
		++argv; --argc;
		if (!argc) usage();
		sName = *argv;
		break;
	    case 'r':			// resend sequence name
		++argv; --argc;
		if (!argc) usage();
		rName = *argv;
		break;
	    default:
		printf ("Ignored switch %s. Use -H for help\n", *argv);
	    }
	} else
	    break;

	++argv; --argc;
    }
    if (!strcmp (inPrefix, outPrefix)) {
	printf ("inPrefix and outPrefix cannot be the same!\n");
	usage();
    }
    if (StartNdds (domain, multicast) < 0) {
	printf ("NDDS connect failed!\n");
	exit (2);
    }
					// setup data reception
    strcpy (headBuff, inPrefix); strcat (headBuff, hName);
    strcpy (packBuff, inPrefix); strcat (packBuff, pName);
    strcpy (seqBuff, inPrefix); strcat (seqBuff, sName);
    strcpy (saveBuff, outPrefix); strcat (saveBuff, eName);
    if (*rName) { strcpy (rSeqBuff, inPrefix); strcat (rSeqBuff, rName);
    } else rSeqBuff[0] = 0;
    ImgReceiveSetup (headBuff, packBuff, seqBuff, rSeqBuff, saveBuff);
					// setup forwarding reception
    strcpy (headBuff, outPrefix); strcat (headBuff, hName);
    strcpy (packBuff, outPrefix); strcat (packBuff, pName);
    strcpy (seqBuff, outPrefix); strcat (seqBuff, sName);
    if (*rName) { strcpy (rSeqBuff, outPrefix); strcat (rSeqBuff, rName);
    } else rSeqBuff[0] = 0;
    ImgSendSetup (headBuff, packBuff, seqBuff, rSeqBuff);

    sleep_us (300000);			// let NDDS get setup
    ImageNdds_SetLinkThroughPut (speed, IMAGE_PACKET_BLOCK_SIZE);

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

    time (&currentTime);	// update time

    // everthing comes in at signal level and is place in a fifo
    // figure out what type of message we have from the size
    // the figure out what to do with the message
    printf ("Entering polling loop. Ctrl-C to exit\n");
    while (!quitFlag) {
					// dont call sleep() it resets itimer
	sleep_us (1000000);		// signals will knock us out of this
	NddsConsumerPoll (eventConsumer); // check for those save events
	for (;;) {
	    char *chunk;
	    time (&currentTime);	// update time
	    int len = FifoPeek (inBox, &chunk);
	    if (len == IMAGE_HEADER_BLOCK_SIZE) { // header: cache and pass
		ImageHeader h = (ImageHeader)chunk;
		ImageHeaderBlockFixup (h);	/* clean up the data pointers*/
		ImageHeaderUpdate (h);
		FifoReceive (inBox, NULL, 9999); /* free FIFO entry */
	    } else if (len == IMAGE_PACKET_BLOCK_SIZE) { // cache and pass
		ImagePacket p = (ImagePacket)chunk;
		ImagePacketBlockFixup (p);	/* clean up the data pointers*/
		ImagePacketUpdate (p);
		FifoReceive (inBox, NULL, 9999); /* free FIFO entry */
	    } else if (len == sizeof (struct ImageSequenceStruct)) {
		// this could be end of image or a resend request
		ImageSequence s = (ImageSequence)chunk;
		ImageSequenceUpdate (s);
		FifoReceive (inBox, NULL, 9999); /* free FIFO entry */
	    } else if (len > 0) {	// OOPS should never get here
		printf ("NddsImagePoll: Received message of odd size! %d\n",
			len);
		FifoReceive (inBox, NULL, 9999); /* free FIFO entry */
	    } else {
		emptyTime = currentTime; // fifo is empty
		if (fifoFulls > 0) --fifoFulls;	// decay fulls
		break;				/* no new data */
	    }
					// do we need flow control
	    if ((fifoFulls || ((currentTime - emptyTime) >= 2))
		&& ((currentTime - flowTime) >= 3)) { // re-request rate
		flowTime = currentTime;
		RequestResend (0, 0, 0); // request dummy resend to get flow
	    }
	}
	// look for old missing packets to requested again.
	for (int i=0; i < NUM_CACHE_HEADERS; ++i) {
	    if (!images[i].header) continue; // never received
	    if (!images[i].file) continue; // no open file
	    if (images[i].lastScrub < 0) continue; // done
	    if ((currentTime - images[i].lastScrub) >= IMAGE_SCRUB_RATE) {
					// TODO jump to ends
		ImagePacketFindMisses (images+i, lastPacketRecv);
	    }
	}
    }
    printf ("\nimageReceive quiting.\n");
    // Write out any outstanding images
    for (int i=0; i < NUM_CACHE_HEADERS; ++i) {
	if (!images[i].header) continue; // never received
	if (!images[i].file) continue;	// no open file
	ImageFlush (images+i);
    }

    // with NDDS on Linux, we hang on exit() trying to flush buffers.
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
    printf ("Calling Exit.\n");
    return 0;
}
