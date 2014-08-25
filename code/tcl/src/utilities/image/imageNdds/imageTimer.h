/* -*- C++ -*-
	File:	itimer.h
	Date:	22 May 1997
	  By:	Kurt Schwehr (schwehr@artemis.arc.nasa.gov)
	 For:	NASA Ames Research Center, Intelligent Mechanisms Group
	 interval timer based functions
*/

extern int imageLinkDelay;		/* usec of delay */

/* interface to this for internal use */
int ImageNdds_SetLinkThroughPut (const int bitsPerSecond,
				 const int packetSize);

#ifdef __cplusplus
extern "C" {
#endif

void ImageNdds_WaitRoom (void);		/* wait to be ready to send */
void ImageNdds_WaitUsec (int usec);	/* use timer to wait approx usec */

void sleep_us (unsigned int nusecs);	/* acually defined in libutil */
int ImageNdds_ThrottleThroughPut (int n); /* (*4) 8 = 1/2 rate, 12 = 1/3...*/

#ifdef __cplusplus
}
#endif
