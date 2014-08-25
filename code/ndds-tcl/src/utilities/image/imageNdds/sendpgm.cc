// ----------------------------------------------------------------------------
// Code to help with develeopment
// ----------------------------------------------------------------------------

#include <assert.h>	// For debugging 

#include <stdio.h>
#include <stdlib.h>
#ifndef OK
#define OK	0
#define ERROR	(-1)
#define logMsg	printf
#endif

#include <string.h>			// strcpy()
#include <math.h>			// ceil
#include <stdio.h>			// printf
#include <unistd.h>			// sleep()
#include <sys/time.h>			// time stuff
#include <NDDS.h>			// the main NDDS stuff
#include <ImageHeader.h>
#include <ImagePacket.h>
#include <readpnm.h>			// pgm/ppm input with comments

#include "imageNdds.h"			// Our very own include file
#include "imageTimer.h"

int debug_level = 1;			// adjustable debug level

char
*ParamStrCpy (char *dest, const char *src)
{
    const char *from = src;
    char *to = dest;
    while (*from && (*from != '\n')) *to++ = *from++;
    *to = 0;				/* null terminate */
    return dest;
}

int
TestSend (char *imgBuf, int width, int height, int depth,
	  char *comments)		// where to look for fields
{
    int result, imageID;

    {
	ImageHeader im = ImageNdds_GetHeader (width, height, depth);
	if (!im) {
	    printf ("ImageNdds_GetHeader %d %d %d failed.\n",
		    width, height, depth);
	    return ERROR;
	}
	{				// parse comments and fill in here?
	    if (debug_level >= 3) 
		printf ("Read comments <%s>\n", comments);
	    const char *val;
	    val = ParamGetVal (comments, "name");
	    if (val) ParamStrCpy (im->name, val);
	    val = ParamGetVal (comments, "type"); // ???
	    if (val) ParamStrCpy (im->type, val);
	    val = ParamGetVal (comments, "date");
	    if (val) {
		ParamStrCpy (im->date, val);
	    } else {
		GetDateString (im->date);
		printf ("Setting date to <%s>\n", im->date);
	    }
	    val = ParamGetVal (comments, "input");
	    if (val) sscanf (val, "%d", &im->input);

	    val = ParamGetVal (comments, "shutter");
	    if (val) sscanf (val, "%d", &im->shutter);

	    val = ParamGetVal (comments, "input_gain");
	    if (val) sscanf (val, "%f", &im->input_gain);
	    val = ParamGetVal (comments, "input_offset");
	    if (val) sscanf (val, "%f", &im->input_offset);

	    val = ParamGetVal (comments, "pan");
	    if (val) sscanf (val, "%f", &im->pan);
	    val = ParamGetVal (comments, "tilt");
	    if (val) sscanf (val, "%f", &im->tilt);

	    val = ParamGetVal (comments, "x");
	    if (val) sscanf (val, "%f", &im->x);
	    val = ParamGetVal (comments, "y");
	    if (val) sscanf (val, "%f", &im->y);
	    val = ParamGetVal (comments, "z");
	    if (val) sscanf (val, "%f", &im->z);
	    val = ParamGetVal (comments, "roll");
	    if (val) sscanf (val, "%f", &im->roll);
	    val = ParamGetVal (comments, "pitch");
	    if (val) sscanf (val, "%f", &im->pitch);
	    val = ParamGetVal (comments, "yaw");
	    if (val) sscanf (val, "%f", &im->yaw);
	    val = ParamGetVal (comments, "xDot");
	    if (val) sscanf (val, "%f", &im->xDot);
	    val = ParamGetVal (comments, "yDot");
	    if (val) sscanf (val, "%f", &im->yDot);
	    val = ParamGetVal (comments, "zDot");
	    if (val) sscanf (val, "%f", &im->zDot);
	    val = ParamGetVal (comments, "rollDot");
	    if (val) sscanf (val, "%f", &im->rollDot);
	    val = ParamGetVal (comments, "pitchDot");
	    if (val) sscanf (val, "%f", &im->pitchDot);
	    val = ParamGetVal (comments, "yawDot");
	    if (val) sscanf (val, "%f", &im->yawDot);
	    val = ParamGetVal (comments, "resolution");
	    if (val) sscanf (val, "%d", &im->resolution);
	    else {			// try to guess resolution
		// source image is either 512x480 or 640x480
		// single frame, left-right stereo, or top-bottom stereo
		switch (height) {
		case 960: im->resolution = 1; break;
		case 480: im->resolution = (width >= 512) ? 1 : 2; break;
		case 240: im->resolution = (width >= 256) ? 2 : 4; break;
		case 120: im->resolution = (width >= 128) ? 4 : 8; break;
		default: im->resolution = 0; break; // unknown
		}
		printf ("Set %dx%d to res %d\n",
			width, height, im->resolution);
	    }
	}
	imageID = ImageNdds_SendHeader (im); // get our imageID
	if (debug_level >= 2) ImageHeaderPrint (im);
	if (imageID < 0) {
	    printf ("Header send failed!\n");
	    return ERROR;
	}
    }

#if 0
    // Try vertical columns
    char buf[1000];
    for (int x=0; x<width-1;x++) {
	for (int y=0;y<height;y++) {
	    buf[y] = imgBuf[x + y * width];
	}
	result = ImageNdds_SendData (buf, imageID,
				     x, 0, x, height - 1, MORE_DATA, depth);
	if (ERROR == result) printf ("<send ERROR.\n");
    }

    for (int y=0;y<height;y++)		// fill in last chunk
	buf[y] = imgBuf[(width-1) + y * (width)];
    result = ImageNdds_SendData (buf, imageID, // send and close image
				 width-1, 0, width-1, height - 1,
				 NO_MORE_DATA, depth);
#else
    result = ImageNdds_SendData (imgBuf, imageID,
				 0, 0, width-1, height - 1,
				 NO_MORE_DATA, depth);
#endif
    if (OK != result) printf ("send ERROR.\n");

    return OK;
}

// Normally ndds is started elsewhere (like the main rover init function)
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
    NddsVerbositySet ((debug_level >= 2) ? 2 : 1);
    NddsVerbosityErrorSet ((debug_level >= 2) ? 2 : 1);
    return OK;
}

void pStats (void) {
    extern ImageNddsStatisticsType stats; // track of what types of pkts sent
    ImageNddsStatisticsType statsBuf;
    ImageNdds_GetStats (&statsBuf);
    
    printf ("stats: Sent %d Resent %d Pend %d RePend %d ImgSent %d\n",
	    stats.numPktSent,
	    stats.numPktResent,
	    stats.numPktPendingSend,
	    stats.numPktPendingResend,
	    stats.numImgSent);
    return;
}

void
usage (void)
{
    printf ("Usage: sendpnm [speed] [-unreliable] [-domain num] [-multicast] \n");
    printf ("\t[-initial name] [-header name] [-packet name] [-sequence name]\n");
    printf ("\t[-resend_sequence name] [-Help] [-Debug level] [-Sleep sec] files*\n");
    printf ("Ex: sendpnm 1544000 -r -i img Nov*.pgm...\n");
    exit (2);
}

#ifndef VXWORKS
int
main (int argc, char **argv)
{
    int speed = 500000;
    int	reliable = 1;
    int domain = 7401;
    int	multicast = 0;
    int wait = 1;
    char *prefix = "img";
    char *hName = "Header";
    char *pName = "Packet";
    char *sName = "Seq";
    char *rName = "ResendSeq";
    char headBuff[64], packBuff[64], seqBuff[64], rSeqBuff[64];

    if (argc <= 1) usage ();

    ++argv; --argc;			// skip program name
    while (argc) {			// get initial arguments
	if ((**argv >= '0') && (**argv <= '9')) {
	    speed =  atoi (*argv);	// set speed
	} else if ('-' == (*argv)[0]) {	// argument
	    switch ((*argv)[1]) {
	    case 'H':			// help
		usage();		// never returns
	    case 'u':			// not reliable
		reliable = 0;
		break;
	    case 'm':			// use multi-cast
		printf ("Multicast not supported yet\n");
		multicast = 1;
		break;
	    case 'D':			// debug level
		++argv; --argc;
		if (!argc) usage();
		debug_level = atoi (*argv);
		break;
	    case 'S':			// sleep time
		++argv; --argc;
		if (!argc) usage();
		wait = atoi (*argv);
		break;
	    case 'd':			// domain
		++argv; --argc;
		if (!argc) usage();
		domain = atoi (*argv);
		break;
	    case 'i':			// message name prefix
		++argv; --argc;
		if (!argc) usage();
		prefix = *argv;
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
    StartNdds (domain, multicast);
    strcpy (headBuff, prefix); strcat (headBuff, hName);
    strcpy (packBuff, prefix); strcat (packBuff, pName);
    strcpy (seqBuff, prefix); strcat (seqBuff, sName);
    if (*rName) { strcpy (rSeqBuff, prefix); strcat (rSeqBuff, rName);
    } else rSeqBuff[0] = 0;
    sleep_us (500000);			// let NDDS get going
					// register the type, spawn the task
    ImageNdds_Init (headBuff, packBuff, seqBuff, rSeqBuff, reliable);
    ImageNdds_SetLinkThroughPut (speed, IMAGE_PACKET_BLOCK_SIZE);

    printf ("Sendpgm started (%d)\n", IMAGE_PACKET_SIZE);
    while (argc--) {			// handle files
	int width, height, maxGrayVal, depth=-666;
	char	commentBuff[512];	// image file comments
	char *imgBuf;
	FILE *fin = fopen (*argv, "r");
	if (!fin) {
	    printf ("Couldn't open %s for reading.\n", *argv);
	    argv++;
	    continue;
	}
	int type = PnmReadHeader (fin, &width, &height, &maxGrayVal,
				  commentBuff, sizeof (commentBuff));
	if ((type != '5') && (type != '6')) {
	    printf ("Error reading header on %s\n", *argv);
	    argv++;
	    fclose (fin);
	    continue;
	}
	if (type == '5') depth = 1;
	if (type == '6') depth = 3;
	imgBuf = (char *) malloc ( width * height * depth );
	if (!imgBuf) {
	    logMsg("Malloc failed on %s.\n", *argv);
	    argv++;
	    fclose (fin);
	    continue;
	}
	if (fread (imgBuf, width*depth, height, fin) <= 0) {
	    printf ("Error reading %s\n", *argv);
	    fclose (fin);
	    continue;
	}
		
	fclose (fin);
	// Send an actual image test

	printf ("\nSending %s %d x %d %d\n",
		*argv, width, height, depth);
	argv++;
	struct timeval	start, end;
	gettimeofday (&start, NULL);
	TestSend (imgBuf, width, height, depth, commentBuff);
	ImageNdds_Flush();		// wait for it to get out
	gettimeofday (&end, NULL);
	pStats ();
	double transTime = end.tv_sec + end.tv_usec / 1000000.0
	    - start.tv_sec + start.tv_usec / 1000000.0;
	printf ("Sent %d bytes in %f sec, %f bps\n",
		width*height*depth, transTime,
		8.0*width*height*depth / transTime);
	free (imgBuf);
	ImageNdds_WaitUsec (wait * 1000000); // let image propogate though
    }
    sleep (1);				// let pending resends happen
    ImageNdds_Quit();
    pStats ();
    printf ("sendpgm exiting.\n");
    return 0;
}
#endif
