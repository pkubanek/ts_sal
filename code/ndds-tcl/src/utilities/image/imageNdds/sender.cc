//	File:	imageNdds.cc
//	Date:	23 Dec 1996
//	  By:	Kurt Schwehr (schwehr@artemis.arc.nasa.gov)
//	 For:	NASA Ames Research Center, Intelligent Mechanisms Group
//  Function:	Provide image transfer via NDDS.
//
//  This is a rewrite from Dan Christian's vipNdds.cc.  The goal is to extract
//  the dependencies on the VIP framegrabber and to impliment the new image 
//  transfer algorithm using a streaming send with requests for retransmits.

//	Dan Christian May 1997	-- Removed thread code, many algorithm changes

#include <sys/time.h>
#include <signal.h>

#include <assert.h>	// For debugging 

#include <string.h>	// strcpy(), memset()
#include <math.h>	// ceil
#include <stdio.h>	// printf

#include <NDDS.h>			// the main NDDS stuff

#include <ImageHeader.h>		// Ndds types specific to Images
#include <ImagePacket.h>
#include <ImageSequence.h>
#include "imageNdds.h"
#include "imageTimer.h"
#include "fifo.h"			// FIFO for resend requests

//
// Global variable not exported outside of this file.
//
static ImageHeader	imgHdr;		// we fill this in for each NDDS send
static ImagePacket	imgPkt;		// we fill this in for each NDDS send
static ImageSequence	imgSeqOut;
static ImageSequence	imgInSeq;	// end image from original sender

// Note image headers are sent using NDDS reliable mode, and aren't cached
static NDDSProducer	imgHdrProducer;
static NDDSProducer	imgPktProducer;
static NDDSProducer	imgSeqProducer;
static NDDSConsumer	resendConsumer;	// asynchronous consumer
static int reliableHeaders = 0;

// Global variables
int	imageNddsAbort = 0;		// abort image sends
ImageNddsStatisticsType stats;		// track of what types of pkts sent

#define RESEND_FIFO_SIZE	100	// size of resend request fifo
static FIFO_ID	inBox;

extern int debug_level;			/* variable for NDDS debugging */
#ifdef NDEBUG
#define NddsDebug(n,s)			/* expand to nothing */
#else
#define NddsDebug(n,s)	(((n) <= debug_level) ?  printf s :0)
#endif

//
// Private function prototypes.
//
static int ImageNdds_SendPkt (char *imgData, int imgID, int pktID,
		      int x1, int y1, int x2, int y2,
				 int bytesPerPixel);

#ifdef NDDS_2_0
static bool SampleStatusRtn ( char * status, NDDSObjectInstance inst,
		       void *userParameter, void *);
#else
static void SampleStatusRtn ( NDDSSampleStatus status, NDDSObjectInstance inst,
		       void *userParameter);
#endif

static int ImageNdds_SendNarrowData (char *imgData, int imgID,
			      int x1, int y1, int x2, int y2, int moreData,
				 int bytesPerPixel);
static int ImageNdds_SendWideData   (char *imgData, int imgID,
			      int x1, int y1, int x2, int y2, int moreData,
				 int bytesPerPixel);

/* Now called asyncronously!!! */
// this handled both end of image from original sender and resend request to us
// either way, we stuff them in the fifo and sort it out later
static NDDSObjectInstance 
ImageSeqCB (NDDSUpdateInfo update)
{
    if (!inBox) return NULL;		// no resend requests
    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA: {
	ImageSequence	s = (ImageSequence) update->instance;
	if (s->sequenceType == IMAGE_ABORT) { // mark abort request
	    if (imageNddsAbort <= 0) imageNddsAbort = 1;
	    else ++imageNddsAbort;
	} else if (FifoSend (inBox, (char *)update->instance,
			     sizeof (struct ImageSequenceStruct)) < 0)
	    printf ("Fifo Full! dropped sequence\n");
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

// ----------------------------------------------------------------------------
// Functions avaiable for external use
// ----------------------------------------------------------------------------

// Ndds must be running before calling.
// TODO should be able to pass in production names
int
ImageNdds_Init (const char *headName,
		const char *packName,
		const char *seqName,
		const char *resendName,
		const int rel) {
    printf ("ImageNdds_Init: %s %s %s reliable %d\n",
	    headName, packName, seqName, rel);

    // the strings here tell how big to make buffer fields, NOT!
    imgHdr	= ImageHeaderBlockAlloc ();// our alloc which makes room
    imgPkt 	= ImagePacketBlockAlloc ();
    imgSeqOut	= ImageSequenceAllocate (NULL, NULL, NULL);
    imgInSeq	= ImageSequenceAllocate (NULL, NULL, NULL);

    ImageHeaderNddsRegister();
    ImagePacketNddsRegister();
    ImageSequenceNddsRegister();

#define NEW_CONS NddsConsumerCreate
#define NEW_PROD NddsProducerCreate
#define SUBS result = NddsConsumerSubscriptionAdd
#define PROD result = NddsProducerProductionAdd
    {
	void *result;	// Used by PROD and SUBS - FIX: add error checking.
	const float per = 15.0f;	// persistence
	const float str = 1.0f;		// strength

	imgHdrProducer= NEW_PROD("imgHdrProducer", NDDS_SYNCHRONOUS, per, str);
	assert (imgHdrProducer);
	imgPktProducer= NEW_PROD("imgPktProducer", NDDS_SYNCHRONOUS, per, str);
	assert (imgPktProducer);
	imgSeqProducer= NEW_PROD("imgSeqProducer", NDDS_SYNCHRONOUS, per, str);
	assert (imgSeqProducer);

	if (rel) {
	    reliableHeaders = 1;
	    printf ("Using reliableHeaders\n");
#ifdef NDDS_1_11Q
	    /* FIX: not sure these are the correct args. */
	    PROD(imgHdrProducer,"ImageHeader",  headName,
		 imgHdr,0,(NDDSSampleBeforeRtn)SampleStatusRtn,(void*)IMG_HDR);
#else
	    PROD(imgHdrProducer,"ImageHeader",  headName,
		 imgHdr,0,NULL,0,SampleStatusRtn,(void*)IMG_HDR);
#endif
	} else {
#ifdef NDDS_1_11Q
	    PROD(imgHdrProducer,"ImageHeader",  headName,
		 imgHdr,0,NULL,(void*)"imgHdr");
#else
	    PROD(imgHdrProducer,"ImageHeader",  headName,
		 imgHdr,0,NULL,0,NULL,(void*)"imgHdr");
#endif
	}

	assert (result);
#ifdef NDDS_1_11Q
	PROD(imgPktProducer,"ImagePacket",  packName,
	     imgPkt,0,NULL,NULL);
	assert (result);
	PROD(imgSeqProducer,"ImageSequence", seqName,
	     imgSeqOut,0,NULL,(void*)"imgSeq");
	assert (result);
#else
	PROD(imgPktProducer,"ImagePacket",  packName,
	     imgPkt,0,NULL,0,NULL,NULL);
	assert (result);
	PROD(imgSeqProducer,"ImageSequence", seqName,
	     imgSeqOut,0,NULL,0,NULL,(void*)"imgSeq");
	assert (result);
#endif
	if (resendName && *resendName) {
	    // fifo for incoming stuff
	    printf ("\tAllocating resend request fifo %d %d\n",
		    RESEND_FIFO_SIZE, IMAGE_PACKET_BLOCK_SIZE);
	    inBox = FifoCreate (RESEND_FIFO_SIZE,
				sizeof (struct ImageSequenceStruct));
	    resendConsumer = NEW_CONS ("ImageResendConsumer",
				       NDDS_IMMEDIATE, 0.0, 0.0);
	    SUBS (resendConsumer, "ImageSequence", resendName,
		  imgInSeq, ImageSeqCB,    NULL);
	}
    }
#undef NEW_CONS
#undef NEW_PROD
#undef SUBS
#undef PROD

    ImageNdds_SetLinkThroughPut (500000, IMAGE_PACKET_BLOCK_SIZE); // set an initial link throughput

    return 0;
} // ImageNdds_Init

// Public interface to timer setup
int
ImageNdds_SetLinkThroughPut (const int bitsPerSecond)
{
    return ImageNdds_SetLinkThroughPut (bitsPerSecond,
					IMAGE_PACKET_BLOCK_SIZE);
}

// Wait until all packets have been sent at least once
int
ImageNdds_Flush (void) {

    return 0;
}

// Shut down task and clean up
int
ImageNdds_Quit (void) {
					// clean up all that other stuff
    return 0;
}

//
// Drop everything.  Skip all packets waiting to be sent.  Dequeue all resends
//
int
ImageNdds_Interrupt (void) {
    printf ("FIX: ImageNdds_Interupt not yet tested.\n");
    printf ("Interrupt transmission of images.\n");
    return 0;
}

					// make -imageID be negative
static int imageID=1;			// ID unique to each header
static int headerStatus = -1;		// reliable header flag
static int packetID=1;			// ID unique to each packet.

// Get a imageHeader ready, user will fill in details
// This uses a static header store.  Only one header can be setup at a time!
ImageHeader
ImageNdds_GetHeader (int width, int height, int bytesPerPixel)
{
    int depth = 0;
    switch (bytesPerPixel) {
    case 1: strcpy (imgHdr->type, "P5"); depth = 1; break;
    case 3: strcpy (imgHdr->type, "P6"); depth = 3; break;
					// turns into 3byte/pixel
    case 4: strcpy (imgHdr->type, "P6"); depth = 3; break;
    default:
	printf ("ImageNdds_NewImage: Error! unsupported bytesPerPixel %d\n",
		bytesPerPixel);
	return NULL;
    }

    imgHdr->row_size = width;	// in pixels
    imgHdr->col_size = height;

    int numPkts;
    if ((width*depth) <= IMAGE_PACKET_SIZE) { // narrow mode
	const int rowsPerPkt = IMAGE_PACKET_SIZE/(width*depth);
	assert (IMAGE_PACKET_SIZE>=width * depth * rowsPerPkt);
	numPkts = (height+rowsPerPkt-1) / rowsPerPkt;
    } else {				// wide mode
	const int pktsPerRow = (width*depth+IMAGE_PACKET_SIZE-1)
	    /IMAGE_PACKET_SIZE;
	numPkts = height*pktsPerRow;
    }
	

    imgHdr->headerId = imageID++;
    imgHdr->first_packet = 0;
    imgHdr->last_packet = numPkts-1;

    // these should be filled in properly by the caller, defaults for now
    imgHdr->input = 0;
    strcpy (imgHdr->name, "single 1 of 1 Test-site");
    strcpy (imgHdr->date, "Thu May 01 06:06:06.04 1997");

    imgHdr->x	= -1;	imgHdr->y = -1;		imgHdr->z = -1;
    imgHdr->roll = -1;	imgHdr->pitch = -1;	imgHdr->yaw = -1;
    imgHdr->pan	= -0.666;		// + left, radians
    imgHdr->tilt = -0.666;		// + up, radians
    imgHdr->input_gain = 1.0;
    imgHdr->input_offset = 0.0;
    imgHdr->shutter = 0;
    imgHdr->resolution = 0;

    return imgHdr;
}

/* handle bookkeeping and send header setup above */
// RETURNS:	an ID number for the image.
int
ImageNdds_SendHeader (ImageHeader imgH)
{
    if (!imgH) return -1;

    imgH->first_packet += packetID;
    imgH->last_packet += packetID;

    headerStatus = -1;			// initialize reliable send stuff

    ImageNdds_WaitRoom();
    NddsProducerSample (imgHdrProducer);

    ++stats.numImgSent;
    if (!reliableHeaders) {		// double send unreliable headers???
	/*ImageNdds_WaitRoom();
	NddsProducerSample (imgHdrProducer);*/

    } else {
	int kk;
	for (kk=99; kk; --kk) {		// timeout value???
	    if (-1 != headerStatus) break; // acked
	    sleep_us(imageLinkDelay);	// give it a little time to get out
	    //	    NddsProducerFlush (imgHdrProducer); // force reliable check
	    // above line taken out since command is no longer supported
	}
	if (headerStatus < 0) {		// no ack
	    printf ("Giving up waiting on reliable header!\n");
	    return -imgH->headerId;
	}
    }

    printf ("Sent header %d <%s> %d %d\n", imgH->headerId, imgH->type,
	    imgH->row_size, imgH->col_size);
    return imgH->headerId;
}

//################################################################
// Simple version of GetHeader, SendHeader
// fills in defaults for all fields
// RETURNS:	an ID number for the image.
int
ImageNdds_NewImage (int width, int height, int bytesPerPixel) {
    ImageHeader imgH= ImageNdds_GetHeader (width, height, bytesPerPixel);
    if (!imgH) return -1;

    return ImageNdds_SendHeader (imgH);
}

// Send a region of image data
int
ImageNdds_SendData (char *imgData, int imgID,
		    int x1, int y1, int x2, int y2,
		    int moreData, int bytesPerPixel) {
    assert (x2>=x1);  assert (y2>=y1);
    const int depth  = (bytesPerPixel == 4) ? 3 : bytesPerPixel; // dest depth
    const int width  = x2 - x1 + 1;	assert (width>0);
    int result;

    if ((width*depth) <= IMAGE_PACKET_SIZE)
	result=ImageNdds_SendNarrowData(imgData, imgID,
					x1,y1,x2,y2,
					moreData, bytesPerPixel);
    else result = ImageNdds_SendWideData (imgData, imgID,
					  x1,y1,x2,y2,
					  moreData, bytesPerPixel);
    if (result < 0)
	printf ("ImageNdds_SendData ERROR: %d (%d,%d)-(%d,%d)\n",
		imgID,x1,y1,x2,y2);
    return result;
}

// Send block of data with width <= IMAGE_PACKET_SIZE
static int
ImageNdds_SendNarrowData (char *imgData, int imgID,
			  int x1, int y1, int x2, int y2,
			  int moreData, int bytesPerPixel) {
    const int width  = x2 - x1 + 1;	assert (width>0);
    const int height = y2 - y1 + 1;	assert (height>0);
    const int depth  = (bytesPerPixel == 4) ? 3 : bytesPerPixel; // dest depth
    const int rowsPerPkt = IMAGE_PACKET_SIZE/(width*depth);
    const int bytesPerPkt = width * bytesPerPixel * rowsPerPkt;	// src bytes
    assert (IMAGE_PACKET_SIZE>=width * depth * rowsPerPkt);
    const int numPkts = (height+rowsPerPkt-1) / rowsPerPkt;
    assert (rowsPerPkt>0);
    int yStart = y1;
    int yEnd   = y1 + rowsPerPkt - 1;
    assert (numPkts>0);
    const int	firstPkt = packetID;
    const int	lastPkt = firstPkt + numPkts;

    int pktNum;
    int lastPktNum;
    char *dp = imgData;
    char *chunk;

    printf ("Sending %d %d %d %d rowsPerPkt %d bytesPerPkt %d num %d depth %d %d\n",
	    x1, y1, x2, y2, rowsPerPkt, bytesPerPkt, numPkts,
	    bytesPerPixel, depth);
    // Send all but last packet.
    for (pktNum = 0; pktNum < numPkts-1; pktNum++) {
	while (inBox && (FifoPeek (inBox, &chunk) > 0)) { // clear resend fifo
	    ImageSequence s = (ImageSequence) chunk;
	    if (s->headerId == imgID) {
		if (HEADER_RESEND == s->sequenceType) { // header request?
		    ImageNdds_ThrottleThroughPut (s->y2*2);
		    ImageNdds_WaitRoom();
		    NddsProducerSample (imgHdrProducer);
		    printf ("Header\n");
		} else if (PACKET_RESEND == s->sequenceType) {
		    int p;
		    ImageNdds_ThrottleThroughPut (s->y2*2);
		    for (p = s->x1; p <= s->x2; ++p) {
			if ((p >= firstPkt) && (p <= lastPkt)) {
			    dp = imgData + (p - firstPkt) * bytesPerPkt;
			    yStart = y1 + (p - firstPkt) * rowsPerPkt;
			    yEnd = yStart + rowsPerPkt - 1;
			    // rebuild packet
			    ImageNdds_SendPkt (dp, -imgID, p,
					       x1, yStart, x2, yEnd,
					       bytesPerPixel);
			    printf ("R %d, ", p);
			} else {
			    // resend it (negate headerID)
			    printf ("Ignore %d, ", p);

			}
		    printf ("img %d (%d)\n", s->headerId, s->y2);
		    }
		} else {
		    printf ("Unknown resend request type %d\n",
				s->sequenceType);
		}
	    } else {
		ImageNdds_ThrottleThroughPut (s->y2*2);
		printf ("OLD: Ignoring  %d - %d img %d (%d)\n",
			s->x1, s->x2, s->headerId, s->y2);
	    }
	    FifoReceive (inBox, NULL, 9999); // remove it from fifo
	}
	dp = imgData + pktNum * bytesPerPkt;
	yStart = y1 + pktNum * rowsPerPkt;
	yEnd = yStart + rowsPerPkt - 1;
	ImageNdds_SendPkt (dp, imgID, packetID++,
			   x1, yStart, x2, yEnd, bytesPerPixel);
    }

    // Handle last packet differently.  The packet may not be full.
    {
	dp = imgData + pktNum * bytesPerPkt;
	yStart = y1 + pktNum * rowsPerPkt;
	yEnd = y2;	assert (yStart<=yEnd);
	lastPktNum = ImageNdds_SendPkt (dp, imgID, packetID++,
					x1, yStart, x2, yEnd,
				       bytesPerPixel);
    }

    if (!moreData) {
	/*printf ("End of image %d.  Sending sequence: LAST_PACKET = %d\n",
		imgID, lastPktNum, 0);*/
	imgSeqOut->headerId = imgID;
	imgSeqOut->x1 = lastPktNum;	// FIX: imgSeqOut->x1 = x1;
	imgSeqOut->y1 = yStart;
	imgSeqOut->x2 = x2;
	imgSeqOut->y2 = yEnd;
	imgSeqOut->sequenceType = IMAGE_LAST_PACKET;
	ImageNdds_WaitRoom();
	NddsProducerSample (imgSeqProducer);
    }
    ImageNdds_WaitUsec(500000);		// last chance for resends
    while (inBox && (FifoPeek (inBox, &chunk) > 0)) { // clear resend fifo
	ImageSequence s = (ImageSequence) chunk;
	if (s->headerId == imgID) {
	    if (HEADER_RESEND == s->sequenceType) { // header request?
		ImageNdds_ThrottleThroughPut (s->y2*2);
		ImageNdds_WaitRoom();
		NddsProducerSample (imgHdrProducer);
		printf ("Header\n");
	    } else if (PACKET_RESEND == s->sequenceType) {
		int p;
		ImageNdds_ThrottleThroughPut (s->y2*2);
		for (p = s->x1; p <= s->x2; ++p) {
		    if ((p >= firstPkt) && (p <= lastPkt)) {
			dp = imgData + (p - firstPkt) * bytesPerPkt;
			yStart = y1 + (p - firstPkt) * rowsPerPkt;
			yEnd = yStart + rowsPerPkt - 1;
			// rebuild packet
			ImageNdds_SendPkt (dp, -imgID, p,
					   x1, yStart, x2, yEnd,
					   bytesPerPixel);
			printf ("R %d, ", p);
		    } else {
			// resend it (negate headerID)
			printf ("Ignore %d, ", p);
		    }
		    printf ("img %d (%d)\n", s->headerId, s->y2);
		}
	    } else {
		printf ("Unknown resend request type %d\n",
			s->sequenceType);
	    }
	} else {
	    ImageNdds_ThrottleThroughPut (s->y2*2); // throttle anyway
	    printf ("OLD: Ignoring %d - %d img %d (%d)\n",
		    s->x1, s->x2, s->headerId, s->y2);
	}
	FifoReceive (inBox, NULL, 9999); // remove it from fifo
    }
    return 0;
}

// Send data with width > IMAGE_PACKET_SIZE
static int
ImageNdds_SendWideData (char *imgData, int imgID,
			int x1, int y1, int x2, int y2,
			int moreData, int bytesPerPixel) {
    printf (" ImageNdds_SendWideData %d %d %d %d %d\n", imgID,x1,y1,x2,y2);
    const int width  = x2 - x1 + 1;	assert (width>0);
    const int height = y2 - y1 + 1;	assert (height>0);
    const int depth  = (bytesPerPixel == 4) ? 3 : bytesPerPixel; // dest depth

    int pktsPerRow = (width*depth+IMAGE_PACKET_SIZE-1)/IMAGE_PACKET_SIZE;
    const int bytesPerPkt  = IMAGE_PACKET_SIZE;
    assert (IMAGE_PACKET_SIZE>=bytesPerPkt);
    const int bytesEdgePkt = (width*depth) % IMAGE_PACKET_SIZE;
    assert (IMAGE_PACKET_SIZE>=bytesEdgePkt);

    const int numRows = y2 - y1 + 1;    assert (0 != numRows);
    assert (0 < numRows);

    /*printf ("w=%d h=%d ppr=%d bep=%d numRows=%d\n",
	    width, height, pktsPerRow, bytesEdgePkt, numRows);*/

    int lastPktNum=0;
    char *lineData = imgData+y1*width;

    // Loop for each line.  FIX: this can be heavily optimised!
    for (int y=y1; y<=y2; y++, lineData += width) {

	//fprintf (stderr,"\ty=%d: ",y);
	// All packets accept the last one, which probably is a partial.
	for (int pkt=0; pkt<pktsPerRow-1; pkt++) {
	    const int lineOffset = pkt * IMAGE_PACKET_SIZE;
	    const int xStart = x1 + lineOffset;
	    assert (lineOffset == x1 + pkt * IMAGE_PACKET_SIZE);
	    const int xEnd   = xStart + IMAGE_PACKET_SIZE - 1;
	    //fprintf (stderr," -- lo=%d xS=%d xE=%d", lineOffset, xStart, xEnd);
	    lastPktNum = ImageNdds_SendPkt (lineData+lineOffset,
					   imgID, packetID++,
					   xStart, y, xEnd, y, bytesPerPixel);
	}

	// Last packet on a line
	const int lineOffset = (pktsPerRow-1) * IMAGE_PACKET_SIZE;
	const int xStart = x1 + lineOffset;
	const int xEnd = xStart + bytesEdgePkt - 1;
	//fprintf (stderr," -l- lo=%d xS=%d xE=%d\n", lineOffset, xStart, xEnd);
	assert (xEnd == x2);
	assert (xEnd >= xStart);
	lastPktNum = ImageNdds_SendPkt (&lineData[lineOffset],
					imgID, packetID++,
				       xStart, y, xEnd, y, bytesPerPixel);
    }

    if (!moreData) {
	printf ("End of image %d.  Sending sequence: LAST_PACKET = %d\n",
		imgID, lastPktNum);
	imgSeqOut->headerId = imgID;
	// FIX: imgSeqOut->x1 = x1 + (pktsPerRow-1) * IMAGE_PACKET_SIZE;
	imgSeqOut->x1 = lastPktNum;
	imgSeqOut->y1 = y2;
	imgSeqOut->x2 = x2;
	imgSeqOut->y2 = y2;
	imgSeqOut->sequenceType = IMAGE_LAST_PACKET;
	ImageNdds_WaitRoom();
	NddsProducerSample (imgSeqProducer);

	printf ("Q2 ");
    }
    {					// clear resend fifo
	char *chunk;
	while (inBox && (FifoPeek (inBox, &chunk) > 0)) {
	    ImageSequence s = (ImageSequence) chunk;
	    printf ("Ignoring resend request %d - %d img %d\n",
		    s->x1, s->x2, s->headerId);
	    FifoReceive (inBox, NULL, 9999); // remove it from fifo
	}
    }
    return 0;
}


// Get a pointer to our statistics
int
ImageNdds_GetStats (ImageNddsStatisticsType *statsBuf) {
    if (NULL == statsBuf) {
	printf("ImageNdds_GetStats: null stats pointer.\n");
	return -1;
    }
    *statsBuf = stats;
    return 0;
}

// ----------------------------------------------------------------------------
// Local functions
// -------------------------------------------------------------------------

// Callback from reliable header send
#ifdef NDDS_2_0
  static bool
  SampleStatusRtn ( char * status, NDDSObjectInstance inst,
	  	    void *userParameter, void * ) {
#else
  static void
  SampleStatusRtn ( NDDSSampleStatus status, NDDSObjectInstance inst,
		    void *userParameter ) {
#endif

    switch (*status) {

#ifdef NDDS_2_0
    // no definition available.
#else
    case NDDS_PENDING_ORPHAN:
 #ifdef NDDS_1_11Q
    // no definition available.
 #else
    case NDDS_NO_SUBSCRIBERS:
 #endif
	printf ("SampleStatusRtn no one is listening!\n");
	headerStatus = -2;
	return;
#endif
#ifdef NDDS_2_0
    // no definition available.
#else
    case NDDS_PRODUCTION_NOT_ACKED:	// no ack yet
	return;
#endif
    case NDDS_BEFORERTN_VETOED:
#ifdef NDDS_1_11Q
    // no definition available.
#else
    case NDDS_PENDING_PRODUCTION:
#endif
#ifdef NDDS_2_0
    // no definition available.
#else
    case NDDS_STRONGER_PRODUCER:
    case NDDS_ATTEMPT_TO_PRODUCE:
	printf ("SampleStatusRtn got error status of some sort. %d\n", status);
	headerStatus = -2;
	return;
#endif

#ifdef NDDS_2_0
    // no definition available.
#else
    case NDDS_MAX_RETRIES_EXCEEDED:
	printf ("SampleStatusRtn message timed out!\n");
	headerStatus = -2;
	return;
#endif

#ifdef NDDS_2_0
    // no definition available.
#else
    case NDDS_SAMPLE_SUCCEEDED:	// Not very exciting, but it means progress.
    case NDDS_PRODUCTION_ACKED:
	//printf ("Acked ok - %d\n", (int)userParameter);
	if (IMG_HDR == (int)userParameter) {
	    ImageHeader hdr = (ImageHeader)inst;
	    //printf ("\tHeader ID = %d\n", hdr->headerId);
	    //printf ("\tImage Header Acked.  Giving semaphore.\n");
	    headerStatus = hdr->headerId;
	}
	break;
#endif
    default:
	printf ("Unknown sample status.\n");
	return;
    }

    // So what?  Nothing to do.
    return;
}

// Fill in an image packet and send it
// It should already be size to fit in one packet
// It will convert 4byte/pixel data to 3byte/pixel if needed
// returns the ID of the packet sent or
// a value less than 0 to indicate an error.
// Pass in a negative imgID for resends
static int
ImageNdds_SendPkt (char *imgData,
		  int imgID, int pktID,
		  int x1, int y1, int x2, int y2,
		  int depth)
{
    assert (imgData);
    assert (y2>=y1);
    assert (x2>=x1);

    ImagePacket pkt = imgPkt;

    if (depth != 1)
	pkt->row_len = ((x2-x1) + 1) * 3; // bytes per row
    else
	pkt->row_len = ((x2-x1) + 1);
    pkt->packet_num = pktID;
    pkt->headerId = imgID;
    pkt->x1 = x1;	pkt->y1 = y1;
    pkt->x2 = x2;	pkt->y2 = y2;

    const size_t size = pkt->row_len*(y2-y1+1);
    assert(size>0);
    assert(size<=IMAGE_PACKET_SIZE);

    if (depth != 4)
	memcpy (pkt->line_data.line_data_val, imgData, size);
    else {				// convert to 3 bytes / pixel
	char *from = imgData, *to = pkt->line_data.line_data_val;
	int	i;
	for (i=size; i > 0; i -= 3) { // i is destination size
	    // HACK convert BGR to RGB
	    *to++ = from[2];
	    *to++ = from[1];
	    *to++ = from[0];
	    from += 4;
	}
    }
    // NDDS uses this to know how much data to actually ship
    pkt->line_data.line_data_len = (u_int)size;

    ImageNdds_WaitRoom();
    NddsProducerSample (imgPktProducer);
    if (pkt->headerId > 0) ++stats.numPktSent;
    else ++stats.numPktResent;

    if (pkt->packet_num < 0) {
	printf ("packetID wrapped.  This is untested.\n");}

    return pkt->packet_num;
}
