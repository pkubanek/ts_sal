// Control pan-tilt and take images using NDDS
// Dan Christian 5/5/97
#include <unistd.h>			// close
#include <stdio.h>			// printf
#include <strings.h>			// memcpy
#include <time.h>			// For clock ticks.
#include <signal.h>			// For sigaction

#include <mv1.h>			// for MV1000 stuff
#include "scigrabber.h"			// all our stuff
#include <picservo.h>			// for scipt.h
#include "scipt.h"			// pan-tilt stuff

#include <NDDS.h>			// the main NDDS stuff
#include <ImageHeader.h>		// Ndds types specific to Images
#include <ImagePacket.h>
#include <ImageSequence.h>
#include <imageNdds.h>			// Image sending functions

//================ External defines
extern "C" {
extern void sleep_us (unsigned int nusecs);// Micro second sleep function.
}

//================ Global variables.
static PT_TYPE	*pt;			// pan-tilt reference
static int parFd;			// parallel port fd
static int quitFlag = 0;		// tell main loop to exit

#ifdef NDEBUG
int grabDebugLevel=-999;			// set default debug level
#else
int grabDebugLevel=3;			// set default debug level
#endif


/* Clean up and exit */
static void
Abort (int value)
{
    ImageNdds_Quit();			// joins all threads
    MvExit ();				// can be called multiple times
    if (value) printf ("Aborting %d.\n", value);
    if (pt) PTUnInit (pt);
    pt = NULL;
    exit (value);
}

/* Ctrl-C signal handler */
static void
QuitSigHandler (int)
{
    ++quitFlag;
    if (quitFlag > 2) {
	Abort (0);
    }
    if (quitFlag > 1) {
	printf ("Got second quit request.  Exiting!\n");
	Abort (0);
    }
}

// Initialize NDDS
int
StartNdds (void) {
#ifdef	NDDS110
    int NDDS_DOMAIN = 7400;	// Set from the startup script
    NddsInit(NDDS_DOMAIN);
#else
    int NDDS_DOMAIN = 7401;	// Set from the startup script
    NddsInit(NDDS_DOMAIN, NULL);
#endif
    printf ("NDDSInit complete\n");
    NddsVerbositySet(2);
    NddsVerbosityErrorSet (2);
    return OK;
}

int
main (int argc, char **argv)
{
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

    StartNdds ();
#if 0
    ImageNdds_Init ();			// register the type, spawn the task

    printf ("cgrab Exiting.\n");
    Abort (0);
#endif
    return 0;
}
