/* -*- C++ -*-
	File:	imageNdds.h
	Date:	23 Dec 1996
	  By:	Kurt Schwehr (schwehr@artemis.arc.nasa.gov)
	 For:	NASA Ames Research Center, Intelligent Mechanisms Group
  Function:	See imageNdds.cc
*/

/*
  Tunable parameters
*/
/* largest possible using char type (due to 4 byte packing) */
/*#define IMAGE_PACKET_SIZE 2008*/  	/* largest image packet data size*/
/* largest possible using opaque type */
/*#define IMAGE_PACKET_SIZE 8032*/  	/* abs max image packet data size*/

#ifndef PACKET_LINES			/* set default packet size */
#define PACKET_LINES 3
#endif
#if (PACKET_LINES == 1)
/* one full rows per packet.  Uses 2 ethernet packets */
#define IMAGE_PACKET_SIZE 	1920
#define NUM_CACHE_PACKETS	2048
#elif (PACKET_LINES == 2)
/* two full rows per packet.  Uses 3 ethernet packets */
#define IMAGE_PACKET_SIZE 	3840
#define NUM_CACHE_PACKETS	1024
#elif (PACKET_LINES == 3)
/* three full rows per packet.  Uses 4 ethernet packets (most efficient) */
#define IMAGE_PACKET_SIZE 	5760
#define NUM_CACHE_PACKETS	1024	/* hold 3.2 full stereo images */
#elif (PACKET_LINES == 4)
/* four full rows per packet.  Uses 6 ethernet packets */
#define IMAGE_PACKET_SIZE	7680  	/* largest image packet data size*/
#define NUM_CACHE_PACKETS	512	/* do both ends need to know this? */
#endif

/* the receiving end can have a bigger packet size than the sender */
#ifdef USE_BIG_PACKETS			/* use the smallest pratical size */
#undef IMAGE_PACKET_SIZE
#define IMAGE_PACKET_SIZE 7680  	/* largest image packet data size*/
/* but use the cache packet size defined above */
#endif
/*
  Externally viewable types.
*/
typedef struct _ImageNddsStatisticsType {
    int numPktSent;
    int numPktResent;
    int numPktPendingSend;
    int numPktPendingResend;
    int numImgSent;
} ImageNddsStatisticsType;

/* This should really be included from imgController.h */
typedef enum {
    PACKET_ACK,				/* acknowleging packet receipt */
    PACKET_RESEND,			/* request resend: from, to, header */
    IMAGE_LAST_PACKET,			/* this image is complete */
    IMAGE_ABORT,			/* this image is aborted */
    IMAGE_FINISHED_OK,
    IMAGE_FINISHED_ERROR,
    HEADER_RESEND,			/* request header resend: header */
    PacketSequenceEnd
} PacketSequenceEnum;

extern int	imageNddsAbort;		/* abort image sends */

/* Anything that needs a uniq number (used?) */
typedef enum {
    ImageNddsEnumStart = 0,
    IMG_HDR,
    ImageNddsEnumEnd
} ImageNddsEnum;


#ifdef __cplusplus
extern "C" {
#endif
/*
  Function Prototypes
*/
int					/* Call once to set everything up. */
ImageNdds_Init (const char *headName,
		const char *packName,
		const char *seqName,
		const char *resendName,
		const int reliableHeaders);
int ImageNdds_Quit (void);		/* shutdown and clean up */
int ImageNdds_Flush (void);		/* wait for all packets to send */
int ImageNdds_Interupt (void);		/* stops all image transmission */
int ImageNdds_NewImage (int imageWidth, int imageHeight, int bitsPerPixel);
ImageHeader ImageNdds_GetHeader (int width, int height, int bytesPerPixel);
int ImageNdds_SendHeader (ImageHeader imgH);

#define MORE_DATA (1==1)	/* TRUE */
#define NO_MORE_DATA (0==1)	/* FALSE */
int ImageNdds_SendData (char *imgData, int imgID, 
			int x1, int y1, int x2, int y2,
			int moreData, int bytesPerPixel);

int ImageNdds_GetStats (ImageNddsStatisticsType *statsBuf);
int ImageNdds_SetLinkThroughPut (const int bitsPerSecond);

extern int GetDateString (char *);	/* acually defined in libutil */


/* Allocate Headers or Packets as a single block to facilitate
   moves and copies (works with fifo functions in libutil) */
#define IMAGE_HEADER_BLOCK_SIZE (sizeof(struct ImageHeaderStruct)+64+64+64)
#define IMAGE_PACKET_BLOCK_SIZE (sizeof (struct ImagePacketStruct)+IMAGE_PACKET_SIZE)
ImageHeader ImageHeaderBlockAlloc (void);
void ImageHeaderBlockCopy (ImageHeader to, const ImageHeader from);
void ImageHeaderBlockFixup (ImageHeader h);

ImagePacket ImagePacketBlockAlloc (void);
void ImagePacketBlockCopy (ImagePacket to, const ImagePacket from);
void ImagePacketBlockFixup (ImagePacket h);

#ifdef __cplusplus
}
#endif

