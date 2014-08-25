/* -*- C++ -*-
 *	File:	imageNdds.h
 *	Date:	23 Dec 1996
 *	  By:	Kurt Schwehr (schwehr@artemis.arc.nasa.gov)
 *	 For:	NASA Ames Research Center, Intelligent Mechanisms Group
 *  Function:	See imageNdds.cc
 */

/* Tunable parameters*/

/*#define IMAGE_PACKET_SIZE 1024*/  	/* largest image packet data size*/
/*#define IMAGE_PACKET_SIZE 7680*/  	/* largest image packet data size*/
#define IMAGE_PACKET_SIZE 8032  	/* abs max image packet data size*/
#define NUM_CACHE_PACKETS	512	/* do both ends need to know this? */

/*** Externally viewable types. ***/
typedef struct _ImageNddsStatisticsType {
    int numPktSent;
    int numPktResent;
    int numPktPendingSend;
    int numPktPendingResend;
    int numImgSent;
} ImageNddsStatisticsType;

/* This should really be included from imgController.h */
typedef enum {
    PACKET_ACK,
    PACKET_RESEND,
    IMAGE_LAST_PACKET,
    IMAGE_ABORT,
    IMAGE_FINISHED_OK,
    IMAGE_FINISHED_ERROR,
    PacketSequenceEnd
} PacketSequenceEnum;

/* Anything that needs a uniq number */
typedef enum {
    ImageNddsEnumStart = 0,
    IMG_HDR,
    ImageNddsEnumEnd
} ImageNddsEnum;


#ifdef __cplusplus
extern "C" {
#endif
/*
// Function Prototypes
*/
int ImageNdds_Init (void);		/* Call this once to set everything up. */
int ImageNdds_Quit (void);		/* shutdown and clean up */
int ImageNdds_Flush (void);		/* wait for all packets to send */
int ImageNdds_Interupt (void);		/* stops all image transmission */
int ImageNdds_NewImage (int imageWidth, int imageHeight, int bitsPerPixel);

#define MORE_DATA (1==1)	/* TRUE */
#define NO_MORE_DATA (0==1)	/* FALSE */
int ImageNdds_SendData (char *imgData, int imgID, 
			int x1, int y1, int x2, int y2, int moreData);

int ImageNdds_GetStats (ImageNddsStatisticsType *statsBuf);
int ImageNdds_SetLinkThroughPut (const int bitsPerSecond);

void sleep_us (unsigned int nusecs);

#define IMAGE_HEADER_BLOCK_SIZE (sizeof(struct ImageHeaderStruct)+64+64+64)
#define IMAGE_PACKET_BLOCK_SIZE (sizeof (struct ImagePacketStruct)+IMAGE_PACKET_SIZE)
ImageHeader ImageHeaderBlockAlloc (void);
void ImageHeaderBlockFixup (ImageHeader h);

ImagePacket ImagePacketBlockAlloc (void);
void ImagePacketBlockFixup (ImagePacket h);

#ifdef __cplusplus
}
#endif
