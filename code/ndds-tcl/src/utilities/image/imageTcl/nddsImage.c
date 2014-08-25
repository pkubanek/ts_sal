/* handle ndds ImageHeader and ImagePacket messages and display in a photo
   Dan Christian 2-96

   Adding support for panoramas.  9-96 Kurt Schwehr
   Adding image sequence packets. 17Oct1996 Kurt Schwehr
*/

#if 0
#define DEBUG_PRINT
#endif

#include <assert.h>

#include <tk.h>
#include <NDDS.h>
#include <strings.h>

#include <ImageHeader.h>
#include <ImageHeader_tclndds.h>	/* for Ndds2Tcl conversion */
#include <ImagePacket.h>
#include <ImageSequence.h>

#define USE_BIG_PACKETS			/* always allow biggest packets */
#include <imageNdds.h>			/* get retransmit request enums */

#include <fifo.h>			/* get asyncronous fifos */

extern int debug_level;			/* NDDS-Tcl debugging level */

#ifdef NDEBUG
#define NddsDebug(n,s)			/* expand to nothing */
#else
#define NddsDebug(n,s)	(((n) <= debug_level) ?  printf s :0)
#endif

#ifndef MIN
#define MIN(x,y)	(((x) < (y)) ? (x) : (y))
#define MAX(x,y)	(((x) > (y)) ? (x) : (y))
#endif

#ifdef DEBUG_PRINT
static int print_header (ImageHeader h);
static int print_packet (ImagePacket p);
static int print_sequence (ImageSequence s);
#endif

char *nddsImageHeader;			/* all image header args */
static  NDDSConsumer	imageConsumer;	/* immediate mode consumer */
static	Tcl_HashTable nddsImageTable;	/* table of images in use */

/* all the info to consume and update the display */
typedef struct _NDDS_IMAGE {
    char	*headerName;		/* name of imageHeader production */
    char	*packetName;		/* name of imagePacket production */
    Tk_PhotoHandle	handle;			/* handle to display object */
    int		width, height;		/* current display width and height */
    int		minWidth;		/* min width to expand image to */
    ImageHeader	header;			/* image header storage area */
    ImageHeader	headerIn;		/* new image header storage */
    ImagePacket	packet;			/* image packer storage area */
    ImageSequence sequence;		/* for requesting retrans or acking */
    NDDSProducer sequenceProducer;	/* sequenc producer */

    Tcl_Interp	*interp;		/* Tcl interpreter to use */
    char	*newImageCB;		/* command to call on image complete */
    char	*callback;		/* command to call on image complete */
    int		flags;			/* various bit flags */
    int		headerId;		/* Unique header ID # */
    FIFO_ID	inBox;			/* FIFO for async updates */
    int		lastPnum;		/* highest packet receive so far */
    int		scanCnt;		/* ticks since resend scan done */
    int		lastCnt;		/* tick since last packet arrived */
    signed char	gotPkt[1024];		/* HACK assumes <= 960 pkts/image */
} NDDS_IMAGE;

#define IMAGE_FIFO_SIZE	100		/* one second of fifo */

#define	IMAGE_FOLD	0x01		/* fold stereo to colored&interlaced */
#define	DO_ACKS		0x02		/* generate packet acks */
#define	DO_RESENDS	0x04		/* ask for packet resends */
#define GET_MULTICAST	0x08		/* get images multi-cast */

NDDSObjectInstance ImageFinishedCB (NDDSUpdateInfo update);

/* Direct NDDS callback for header productions */
/* Now called asyncronously!!! */
NDDSObjectInstance
ImageHeaderHandler (NDDSUpdateInfo update)
{
    NDDS_IMAGE	*store = (NDDS_IMAGE *)update->callBackRtnParam;

    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
	if (FifoSend (store->inBox, (char *)store->headerIn,
		  IMAGE_HEADER_BLOCK_SIZE) < 0)
	    NddsDebug (1, ("FULL-header lost!  "));
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

int
ImageDoCallback (NDDS_IMAGE *store, char *callback)
{
    Tcl_DString	cmd;
    int	status, m;
	    
    Tcl_DStringInit (&cmd);
    Tcl_DStringAppend (&cmd, callback, -1); /* command */
    /* setup "this" with header info */
    status = Ndds2Tcl_ImageHeader (store->header, store->interp);
    m = Tcl_Eval(store->interp, Tcl_DStringValue (&cmd));
    if (m || (debug_level >= 2)) /* show cmd and error */
	printf ("%s -> %s\n",
		Tcl_DStringValue (&cmd), store->interp->result);
    Tcl_DStringFree (&cmd);
    /* clear "this" */
    status = Tcl_UnsetVar (store->interp, "this", TCL_LEAVE_ERR_MSG);
    if (TCL_ERROR == status) {
	NddsDebug (0, ("Tcl_UnsetVar `this' ERROR: %s\n",
		       store->interp->result));
    }
    return m;
}

/* This does the work when a new header arrives */
void
ImageHeaderUpdate (NDDS_IMAGE *store, ImageHeader header)
{
    /* clean up last image, if not already done */
    if (store->callback && store->header->headerId
	&& (store->lastPnum > store->header->first_packet)) {
	int i, todo = 0;
	char *cp = store->gotPkt;
					/* BUG breaks at packet num wrap */
	for (i=0;
	     i <= (store->header->last_packet - store->header->first_packet);
	     ++i, ++cp)
	    if (*cp <= 0) ++todo;
	if (todo) {
	    NddsDebug (1, ("Calling callback on last image.\n"));
	    ImageDoCallback (store, store->callback);
	}
    }
    
					/* copy head to working store */
    ImageHeaderBlockCopy (store->header, store->headerIn);
    memset (store->gotPkt, 0, sizeof (store->gotPkt)); /* clear got pkt */
    store->scanCnt = 0;
    store->lastPnum = store->header->first_packet-1; /* initialize */

    if (nddsImageHeader) {		/* store header info for TCL */
	sprintf (nddsImageHeader,
		 "%s %s %s %d %d %d %f %f %f %f %f %f %f %f",
		 header->name, 	      header->type,     header->date,
		 header->input,
		 header->row_size,    header->col_size,
		 header->x, 	      header->y,        header->z,
		 header->roll,        header->pitch,    header->yaw,
		 header->pan,         header->tilt);
	NddsDebug (3, ("ImageHeader: <%s>\n", nddsImageHeader));
    }
		 
    if ((header->row_size != store->width)
	|| (header->col_size != store->height)) { /* resize */
	store->width = header->row_size;
	store->height = header->col_size;
	if (store->minWidth) {		/* expanded display */
					/* always round up */
	    int	scale = (store->minWidth + store->width - 1) / store->width;
	    if (scale <= 0) scale = 1;
	    if ((store->flags & IMAGE_FOLD) && /* HACK! */
		((header->input == 3) || (header->input == 6))) {
		Tk_PhotoSetSize (store->handle,
			      scale * store->width/2, scale * store->height);
	    } else {
		Tk_PhotoSetSize (store->handle,
			      scale * store->width, scale * store->height);
	    }
	} else {
	    if ((store->flags & IMAGE_FOLD) &&
		((header->input == 3) || (header->input == 6))) {
		Tk_PhotoSetSize (store->handle, store->width/2, store->height);
	    } else {
		Tk_PhotoSetSize (store->handle, store->width, store->height);
	    }
	}
    }

    /* call handler to check new nddsImageHeader */
    if (store->newImageCB) {		/* check new image callback */
	ImageDoCallback (store, store->newImageCB);	
    } else {
	NddsDebug (3, ("ImageHeaderHandler: store->newImageCB is null.\n"));
    }
    NddsDebug (2, ("Got ImageHeader[%d] %s %d x %d first %d last %d\n",
		   header->headerId, header->type,
		   header->row_size, header->col_size,
		   header->first_packet, header->last_packet));
}

/* Now called asyncronously!!! */
NDDSObjectInstance
ImagePacketHandler (NDDSUpdateInfo update)
{
    NDDS_IMAGE	*store = (NDDS_IMAGE *)update->callBackRtnParam;

    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
	if (FifoSend (store->inBox, (char *)store->packet,
		  IMAGE_PACKET_BLOCK_SIZE) < 0)
	    NddsDebug (1, ("FULL-packet lost!  "));
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

/* search and see what packets are missing */
int
ImagePacketFindMisses (NDDS_IMAGE *store, int max_packet)
{
    int todo = 0;
    int	skipped = 0;
    int first = store->header->first_packet;
    int last = MIN (max_packet, store->header->last_packet);
    if (store->sequence && (store->flags & DO_RESENDS)) {
	int i;
	signed char *cp = store->gotPkt;
	/* BUG breaks at packet num wrap */
	NddsDebug (3, ("Finding resends %d, %d - %d (%d): ",
		       store->header->headerId,
		       first, last, store->header->last_packet));
					/* TODO, group requests */
	for (i=0; i <= (last-first); ++i, ++cp) {
	    if (0 == *cp) {
		ImageSequence s = store->sequence;
		int	end = i;
		signed char *ep = cp;

		for (; (0 == ep[1]) && (end <= (last-first));
		     ++ep, ++end);	/* find extent of drops */
		todo += end - i + 1;

		s->headerId = store->header->headerId;
		s->x1 = i+first;	/* request range of misses */
		s->x2 = end+first;
		s->y1 = s->y2 = 0;
		s->sequenceType = PACKET_RESEND;
		NddsProducerSample (store->sequenceProducer);
		NddsDebug (3, ("%d ", s->x1));
		while (cp <= ep) *cp++ = -1; /* hold off on re-request */
		i = end;		/* move to end of block */
		cp = ep;
		if (todo > 50) break;	/* only ask for so many at a time */
	    } else if (*cp < 0) {	/* decay hold off */
		*cp += 1;
		++skipped;
	    } else if (*cp != 1) {	/* DEBUG */
		NddsDebug (3, ("[%d, %d = %d] ", i, i+first, *cp));
	    }
	}
    }
    NddsDebug (3, ("Done (%d, %d).\n", todo, skipped));

    if ((last == store->header->last_packet)
	&& (0 == (todo + skipped))) {	/* no resends todo, complete! */
	store->scanCnt = -1;	/* none needed */

	if (store->callback) {		/* check completion callback */
	    ImageDoCallback (store, store->callback);
	}
    } else {
	store->scanCnt = 0;		/* reset timeout */
    }
    return todo+skipped;
}

/* This does the work when a new header arrives */
void
ImagePacketUpdate (NDDS_IMAGE *store, ImagePacket packet)
{
    Tk_PhotoImageBlock	block;
    int		scale = 1;
    int		resend = 0;
    ImageHeader header = store->header;

    if (packet->headerId < 0) {		/* resends have negative header */
	packet->headerId = -packet->headerId;
	NddsDebug (4, ("Got resend\n"));
	++resend;
    }

    if (packet->headerId != header->headerId) { /* missed the header */
	NddsDebug (1, ("Error! headerId mismatch: packet %d != header %d!\n",
		    packet->headerId, header->headerId) );
	if (packet->headerId > header->headerId) { /* see if newer header */
	    static	int lastAsked, times;
	    if (lastAsked != packet->headerId) {
		ImageSequence s = store->sequence;
		lastAsked = packet->headerId;
		times = 9;		/* how often to re-request */
		s->sequenceType = HEADER_RESEND;
		s->headerId = store->header->headerId;
		s->x1 = s->y1 = s->x2 = s->y2 = packet->headerId;
		NddsProducerSample (store->sequenceProducer);
		NddsDebug (2, ("Requested header resend %d\n",
			       packet->headerId));
	    } else {
		if (--times <= 0) lastAsked = 0;
	    }
	}
	goto ackAndExit;		/* exit, ACK if needed */
    }

    /* this should have been trapped by the headerId */
    if (packet->packet_num < header->first_packet) { /* old packet */
	goto ackAndExit;
    }

    /* mark as received */
    store->gotPkt [packet->packet_num - header->first_packet] = 1;
    if (store->sequence && (store->flags & DO_RESENDS)) {
	if (store->lastPnum == -1) {	/* new image, no omission possible */
	    store->lastPnum = packet->packet_num;
	} else if (packet->packet_num > (store->lastPnum +1)) { /* missed packets */
	    int i;
	    NddsDebug (3, ("Expected %d got %d\n",
			   store->lastPnum+1, packet->packet_num));
	    for (i=store->lastPnum+1; i < packet->packet_num; i++) {
		store->gotPkt [i] = -1;	/* hold off re-request */
#if 0
		ImageSequence s = store->sequence;

		s->headerId = store->header->headerId;
		s->x1 = s->y1 = s->x2 = s->y2 = i;
		s->sequenceType = PACKET_RESEND;
		/*print_sequence (s);*/
		NddsProducerSample (s->sequenceProducer);
#endif
	    }
	    {				/* request packet(s) */
		ImageSequence s = store->sequence;

		s->headerId = store->header->headerId;
		s->x1 = store->lastPnum+1;
		s->x2 = packet->packet_num-1;
		s->sequenceType = PACKET_RESEND;
		/*print_sequence (s);*/
		NddsProducerSample (store->sequenceProducer);
		NddsDebug (2, ("Requesting %d - %d, img %d\n",
			       s->x1, s->x2, s->headerId));
	    }
	    store->lastPnum = packet->packet_num;
	} else if (packet->packet_num > store->lastPnum) { /* update */
	    store->lastPnum = packet->packet_num;
	}
    }
	    
	
					/* update a section */
    block.width  = (packet->x2 - packet->x1) + 1;
    block.height = (packet->y2 - packet->y1) + 1;
    block.pixelPtr = packet->line_data.line_data_val;

    if (block.width == packet->row_len) { /* 1 byte/pixel */
	block.pitch  = block.width;		

	block.pixelSize = 1;
	if ((store->flags & IMAGE_FOLD) &&
	    ((header->input == 3) || (header->input == 6))) {
	    /* fold stereo images together */
	    block.offset[0] = block.width/2; /* red is right */
	    block.offset[1] = block.offset[2] = 0; /* green/blue is left */
	    block.width /= 2;		/* resize to half */
	} else {				/* RGB are always the same */
	    block.offset[0] = block.offset[1] = block.offset[2] = 0;
	}
    } else {
	if ((block.width*3) != packet->row_len) {
	    NddsDebug (2, ("Got a bad depth %d %d\n",
			   block.width, packet->row_len));
	    goto ackAndExit;
	}
	block.pitch  = block.width*3;		

	block.pixelSize = 3;
	block.offset[0] = 0;
	block.offset[1] = 1;
	block.offset[2] = 2;
    }
    if (store->minWidth) {	/* figure expansion, always round up */
	scale = (store->minWidth + store->width - 1) / store->width;
	if (scale <= 0) scale = 1;
    }

    NddsDebug (3, ("Updating %d x%d +%d +%d\n",	block.width, block.height,
		   packet->x2, packet->y2) );

    if (scale > 1) {
	Tk_PhotoPutZoomedBlock ( store->handle, &block,/* draw it */
				 scale * packet->x1, scale * packet->y1,
				 scale * block.width, scale * block.height,
				 scale, scale, 1, 1);
    } else {				/* scale 1:1 */
	Tk_PhotoPutBlock (store->handle, &block,/* draw it */
			  packet->x1, packet->y1,
			  block.width, block.height);
    }

    if ((packet->y2 >= store->header->col_size - 1 ) /* end of image */
	&& (packet->x2 >= store->header->row_size - 1 )) {
	ImagePacketFindMisses (store, store->header->last_packet);
    } else if (!resend) {		/* create a progress line */
	char	*cp = block.pixelPtr;
	int	ii;
	block.pixelSize = 1;
	block.offset[0] = block.offset[1] = block.offset[2] = 0;
	if (block.width >= block.height) { /* horizontal chunks */
	    for (ii=0; ii < block.width; ++ii) *cp++ = (ii & 16) ? 255 : 0;
	    Tk_PhotoPutBlock (store->handle, &block,/* draw it */
			      scale * packet->x1,
			      scale * (packet->y1+block.height),
			      block.width, 1);
	} else {
	    for (ii=0; ii < block.height; ++ii) *cp++ = (ii & 16) ? 255 : 0;
	    Tk_PhotoPutBlock (store->handle, &block,/* draw it */
			      scale * (packet->x1+block.width),
			      scale * packet->y1,
			      1, block.height);
	}
    }
	

  ackAndExit:
    if (store->sequence && (store->flags & DO_ACKS)) {
	ImageSequence s = store->sequence;
	ImagePacket   p = packet;

	s->headerId = store->header->headerId;
	s->x1 = p->x1;  s->y1 = p->y1;  s->x2 = p->x2;  s->y2 = p->y2;
	s->sequenceType = PACKET_ACK;
	/*print_sequence (s);*/
	NddsProducerSample (store->sequenceProducer);
    } else
	NddsDebug (4, ("Did not ack packet: Ack packet is null\n"));

}

/* Now called asyncronously!!! */
NDDSObjectInstance 
ImageFinishedCB (NDDSUpdateInfo update)
{
    NDDS_IMAGE	*store = (NDDS_IMAGE *)update->callBackRtnParam;
    switch (update->updateStatus) { /* status */
    case NDDS_FRESH_DATA:
	if (FifoSend (store->inBox, (char *)update->instance,
		  sizeof (struct ImageSequenceStruct)) < 0)
	    NddsDebug (1, ("FULL-EndMsg lost!  "));
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

/* This does the work when an image is completed */
void
ImageSequenceUpdate (NDDS_IMAGE *store, ImageSequence s)
{
    if (! store->callback) {
	NddsDebug (3, ("ImageFinishedCB: No tcl callback registerd\n"));
	return;
    }

    if (store->sequence && (store->flags & DO_RESENDS)) {
	ImagePacketFindMisses (store, store->header->last_packet);
    }
}


#define NDDS_IMAGE_POLL_TIME	50	/*  milliseconds */

/* should adjust these to the round trip delay */
#define NDDS_IMAGE_RESCAN_TIMEOUT	50 /* loop cnt (1/3 round trip) */
#define NDDS_IMAGE_IDLE_TIMEOUT	20	/* poll loops, less than RESCAN */

/* Handle data brought in asyncronously */
static void
NddsImagePoll (ClientData clientData)
{
    int	len;
    char *chunk;
    NDDS_IMAGE	*store = (NDDS_IMAGE *)clientData;

    for (;;) {				/* handle all new data */
	len = FifoPeek (store->inBox, &chunk);
	if (len == IMAGE_HEADER_BLOCK_SIZE) {
	    ImageHeader h = (ImageHeader)chunk;
	    ImageHeaderBlockFixup (h);	/* muck with the data pointer */
	    ImageHeaderUpdate (store, h);
	    FifoReceive (store->inBox, NULL, 9999); /* free FIFO entry */
	    store->lastCnt = 0;
	} else if (len == IMAGE_PACKET_BLOCK_SIZE) {
	    ImagePacket p = (ImagePacket)chunk;
	    ImagePacketBlockFixup (p);	/* muck with the data pointer */
	    ImagePacketUpdate (store, p);
	    FifoReceive (store->inBox, NULL, 9999); /* free FIFO entry */
	    store->lastCnt = 0;
	} else if (len == sizeof (struct ImageSequenceStruct)) {
	    ImageSequence s = (ImageSequence)chunk;
	    ImageSequenceUpdate (store, s);
	    FifoReceive (store->inBox, NULL, 9999); /* free FIFO entry */
	    store->lastCnt = 0;
	} else if (len > 0) {
	    NddsDebug (1, ("NddsImagePoll: Bogus sized message! %d\n",
			   len));
	    FifoReceive (store->inBox, NULL, 9999); /* free FIFO entry */
	    store->lastCnt = 0;
	} else
	    ++store->lastCnt;
	    break;				/* no new data */
    }
    if (store->scanCnt >= 0) ++store->scanCnt; /* increment */
    if (store->scanCnt > NDDS_IMAGE_RESCAN_TIMEOUT) {
					/* try to catch missing end of image */
	if ((store->header->last_packet - store->lastPnum) < 5) {
	    ImagePacketFindMisses (store, store->header->last_packet);
	} else {
	    ImagePacketFindMisses (store, store->lastPnum);
	}
    } else if ((store->scanCnt > 0)	/* things are quiet, check up */
	       && (store->lastCnt == NDDS_IMAGE_IDLE_TIMEOUT)) {
					/* try to catch missing end of image */
	if ((store->header->last_packet - store->lastPnum) < 5) {
	    ImagePacketFindMisses (store, store->header->last_packet);
	} else {
	    ImagePacketFindMisses (store, store->lastPnum);
	}
    }
					/* arrange to be called again */
    Tcl_CreateTimerHandler (NDDS_IMAGE_POLL_TIME,
			   NddsImagePoll, store);
    return;
}

#define SUBSCRIBE NddsConsumerSubscriptionAdd
#define PRODUCTION NddsProducerProductionAdd

/* Tcl command hander for ndds_image */
int
NddsImage (ClientData notUsed,
	    Tcl_Interp *interp,		/* Current interpreter. */
	    int argc,			/* Number of arguments. */
	    char **argv)		/* Argument strings. */
{
    /*int result;*/
    NDDS_IMAGE	*store;
    char	*photoName;
    if (argc < 4) {
	Tcl_AppendResult(interp, "too few args, usage: ", argv[0],
			 "Photo_Id Header_Packet_Name Image_Packet_Name ",
			 "[-width n] [-newimage callback] ",
			 "[-complete callback] [-fold]  [-multicast] ",
			 "[-resends] [-acks] [ack/resend_name]",
			 (char *) NULL);
	return TCL_ERROR;
    }

    ImageHeaderNddsRegister();		/* register NDDS types */
    ImagePacketNddsRegister();
    ImageSequenceNddsRegister();

    store = (NDDS_IMAGE *)calloc (1, sizeof (NDDS_IMAGE));
    if (!store) return TCL_ERROR;

    photoName = argv[1];
    store->handle = Tk_FindPhoto (argv[1]); /* find photo handle */
    if (!store->handle) {
	Tcl_AppendResult (interp, "photo not found: ", argv[1], NULL);
	free (store);
	return TCL_ERROR;
    }
    store->headerName = strdup (argv[2]);
    store->packetName = strdup (argv[3]);
    store->interp = interp;
    store->scanCnt = -1;		/* mark nothing to do yet */
    if (!nddsImageTable.buckets) {	/* initailize image table */
	Tcl_InitHashTable (&nddsImageTable, TCL_STRING_KEYS);
    }
    {					/* insert into table of images */
	int wasNew=0;
	Tcl_HashEntry	*entry;
	entry = Tcl_CreateHashEntry (&nddsImageTable, argv[1], &wasNew);
	if (entry) {
	    Tcl_SetHashValue (entry, store);
	    /*printf ("Made hash <%s> %p %p %d\n",
	      argv[1], entry, store, wasNew);*/
	} else {
	    printf ("Warning! Failed to make hash entry for <%s>\n", argv[1]);
	}
    }
    NddsDebug (1, ("Consuming %s and %s for %s\n",
		   store->headerName, store->packetName, argv[1]));
    store->headerIn = ImageHeaderBlockAlloc(); /* newest on */
    store->header = ImageHeaderBlockAlloc(); /* one we are using */
    if (!store->header || !store->headerIn) {
	Tcl_AppendResult (interp, "Couldnt allocate header store", NULL);
	free (store->headerName);
	free (store->packetName);
	free (store);
	return TCL_ERROR;
    }
    store->packet = ImagePacketBlockAlloc ();
    if (!store->packet) {
	Tcl_AppendResult (interp, "Couldnt allocate packet store", NULL);
					/* should free header */
	free (store->header);
	free (store->headerIn);
	free (store->headerName);
	free (store->packetName);
	free (store);
	return TCL_ERROR;
    }

    argc -= 4;				/* skip to optional args */
    argv += 4;

    /* FIX: should we have a free routine for return TCL_ERROR cases? */
    while (argc > 0) {
	if (!strncmp (*argv, "-width", 4)) { /* option minimum width */
	    --argc, ++argv;
	    if (argc <= 0) {
		Tcl_AppendResult(interp, "Argument expected for: ", *argv,
				 NULL);
		return TCL_ERROR;
	    }
	    store->minWidth = atoi (*argv);
	    if (store->minWidth < 0) store->minWidth = 0; /* negative */
	    if (store->minWidth > 4096) store->minWidth = 0; /* too big */
	} else if (!strncmp (*argv, "-newimage", 5)) { /* new image callback */
	    --argc, ++argv;
	    if (argc <= 0) {
		Tcl_AppendResult(interp, "Argument expected for: ", *argv,
				 NULL);
		return TCL_ERROR;
	    }
	    store->newImageCB = strdup (*argv); /* command to call */
	    NddsDebug (1, ("Setting new image callback to '%s'\n",
			store->newImageCB));
	} else if (!strncmp (*argv, "-complete", 5)) { /* complete callback */
	    --argc, ++argv;
	    if (argc <= 0) {
		Tcl_AppendResult(interp, "Argument expected for: ", *argv,
				 NULL);
		return TCL_ERROR;
	    }
	    store->callback = strdup (*argv); /* command to call */
	    NddsDebug (1, ("Setting image complete callback to '%s'\n",
			store->callback));

	} else if (!strncmp (*argv, "-fold", 5)) { /* fold mode */
	    store->flags |= IMAGE_FOLD;
	    NddsDebug (1, ("Folding stereo images\n"));

	} else if (!strncmp (*argv, "-multi", 6)) { /* multicast mode */
	    store->flags |= GET_MULTICAST;
	    NddsDebug (1, ("Receiving multi-cast\n"));
	} else if (!strcmp (*argv, "") ) { /* causes trouble if not caught */
	    NddsDebug (0, ("nddsImage: empty string in command. (fold?)\n"));

	} else if (!strcmp (*argv, "-resends")) { /* do resend requests */
	    store->flags |= DO_RESENDS;
	    NddsDebug (1, ("Asking for packet resends\n"));
	} else if (!strcmp (*argv, "-acks")) { /* ack each packet */
	    store->flags |= DO_ACKS;
	    NddsDebug (1, ("Asking for packet acks\n"));
	} else {			/* optional ack/resend name */
	    char	newName[64];
	    store->sequence = ImageSequenceAllocate (NULL, NULL, NULL);
	    if (!store->sequence) {
		Tcl_AppendResult (interp,
				  "Couldnt allocate sequencepacket store",
				  NULL);
		return TCL_ERROR;
	    }
	    NddsDebug (1, ("Creating sequenceProducer production %s\n",
			   *argv));
	    sprintf (newName, "seqProd%s", photoName); /* must be unique */
	    store->sequenceProducer =
		NddsProducerCreate (newName, NDDS_SYNCHRONOUS, 3.0f, 1.0f);
#ifdef NDDS_1_11Q
	    PRODUCTION (store->sequenceProducer,"ImageSequence",
			*argv, store->sequence,
			0, NULL, NULL);
#else
	    PRODUCTION (store->sequenceProducer,"ImageSequence",
			*argv, store->sequence,
			0, NULL, 0, NULL, NULL);
#endif

	    /* compatibility, if no resends, then enable acks here */
	    if (!(store->flags & DO_RESENDS)) {
		store->flags |= DO_ACKS;
		NddsDebug (1, ("Asking for packet acks\n"));
	    }
	}
	--argc, ++argv;
    }

    store->inBox = FifoCreate (IMAGE_FIFO_SIZE, IMAGE_PACKET_BLOCK_SIZE);
    if (!store->inBox) {
	Tcl_AppendResult(interp,
			 "ERROR!!! could not create inBox!",
			 (char *) NULL);
	return TCL_ERROR;
    }
    if (!imageConsumer) {		/* create immediate mode consumer */
					/* create the input queue */
					/* create immediate mode consumer */
	imageConsumer = NddsConsumerCreate ("TclImage", NDDS_IMMEDIATE,
					    0.0, 0.0);
	if (!imageConsumer) {		/* failed to create */
	    Tcl_AppendResult(interp,
			     "ERROR!!! could not create image consumer!",
			     (char *) NULL);
	    return TCL_ERROR;
	}
	if (store->flags & GET_MULTICAST) {
#if 0
	    if (!NddsConsumerMulticastAddressSet(imageConsumer,
						 "225.100.5.4")) {
		printf ("NddsConsumerMulticastAddressSet: failed\n");
		printf ("incorrect multicast address\n");
		store->flags &= ~GET_MULTICAST;	/* turn off flag */
	    }
#else
	    printf ("Ignoring -multicast flag\n");
	    store->flags &= ~GET_MULTICAST;	/* turn off flag */
#endif
	}
    }


    {
	ImageSequence finished = ImageSequenceAllocate (NULL, NULL, NULL);
	SUBSCRIBE (imageConsumer, "ImageSequence","ImageFinished",
		   finished, ImageFinishedCB, store);
    }
	
    SUBSCRIBE (imageConsumer,"ImageHeader",store->headerName, store->headerIn,
	       			 ImageHeaderHandler, store);
    SUBSCRIBE (imageConsumer, "ImagePacket", store->packetName, store->packet,
				 ImagePacketHandler, store);
    /* BUG: Timer for every image object! */
    Tcl_CreateTimerHandler (NDDS_IMAGE_POLL_TIME,
			    NddsImagePoll, store);

    return TCL_OK;
}
#undef SUBSCRIBE
#undef PRODUCTION

/* Tcl command hander for ndds_image_abort */
int
NddsImageAbort (ClientData notUsed,
	    Tcl_Interp *interp,		/* Current interpreter. */
	    int argc,			/* Number of arguments. */
	    char **argv)		/* Argument strings. */
{
    NDDS_IMAGE	*store;
    Tcl_HashEntry	*entry;
    ImageSequence s = store->sequence;

    if (argc < 2) {
	Tcl_AppendResult(interp, "too few args, usage: ", argv[0],
			 "Photo_Id", (char *) NULL);
	return TCL_ERROR;
    }
    if (!nddsImageTable.buckets) {
	Tcl_AppendResult (interp, "No photos found: ", NULL);
	return TCL_ERROR;
    }
    /*printf ("Looking for <%s>\n", argv[1]);*/
    entry = Tcl_FindHashEntry (&nddsImageTable, argv[1]);
    if (!entry) {
	Tcl_AppendResult (interp, "photo not found: ", argv[1], NULL);
	return TCL_ERROR;
    }
    store = (NDDS_IMAGE *)Tcl_GetHashValue (entry);
    s = store->sequence;
    if (!s || !store->sequenceProducer) {
	Tcl_AppendResult (interp, "ndds image doesnt have a sequence packet: ",
			  argv[1], NULL);
	return TCL_ERROR;
    }

    s->headerId = store->header->headerId;
    s->x1 = s->x2 = store->lastCnt;	/* this is ignored */
    s->y1 = s->y2 = 0;
    s->sequenceType = IMAGE_ABORT;
    NddsProducerSample (store->sequenceProducer);
    return TCL_OK;
}

#ifdef DEBUG_PRINT
static int print_header (ImageHeader h) {
    printf ("ImageHeader %d: %s %s %s\n",       h->headerId, h->name,  h->type,     h->date);
    printf ("ImageHeader %d: %d %d %d %d\n",    h->headerId, h->input, h->row_size, h->col_size, h->packet_size);
    printf ("ImageHeader %d: %.2f %.2f %.2f\n", h->headerId, h->x,     h->y,        h->z);
    printf ("ImageHeader %d: %.2f %.2f %.2f\n", h->headerId, h->roll,  h->pitch,    h->yaw);
    printf ("ImageHeader %d: %.2f %.2f %.2f\n", h->headerId, h->pan,   h->tilt,     h->panMax);
    return TCL_OK;
}

static int print_packet (ImagePacket p) {
    printf ("ImagePacket %d-%d: %d %d\n",        p->headerId,p->packet_num, p->row_len, p->line_data.line_data_len);
    printf ("ImagePacket %d-%d: %d,%d - %d,%d\n",p->headerId,p->packet_num, p->x1, p->y1, p->x2, p->y2);
    return TCL_OK;
}

static int print_sequence (ImageSequence s) {
    char* type;
    switch (s->sequenceType) {
    case PACKET_ACK:    type = "Ack";    break;
    case PACKET_RESEND: type = "Resend"; break;
    default:            type = "Unknown";
    }
    printf ("ImageSequence %d(%d-%s): (%d,%d)-(%d,%d)\n",
	    s->headerId, s->sequenceType, type,
	    s->x1, s->y1, s->x2, s->y2);
    return TCL_OK;
}

#endif

