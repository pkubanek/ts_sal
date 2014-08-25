//	iTimer.cc
//	interval timer functions for metered data output

#include <sys/time.h>
#include <signal.h>
#include <stdio.h>

#include "imageTimer.h"

// delay in 60ths of a second (rounds down!)
int imageLinkDelay = 666666;
int imageLinkBPS = 0;			// BPS on link to allow
int imageThrottle = 4;			// throttle down ratio in 4th

static	int timerExpired =  0;		// timer increments this N/sec

// handle periodic timer.  Just give a simple flag
static void
TimerTick (int)
{
    ++timerExpired;
}

// setup a periodic timer interupt
// sleep resets this timer!
int
ImageNddsSetupTimer (int throttle)	// slow down factor (*4)
{
    struct sigaction act;
    sigemptyset (&act.sa_mask);		// no special masking
    act.sa_flags = 0;			// reuse handler each time
    act.sa_handler = TimerTick;		// handler
    if (throttle <= 0) throttle = 1;
    if (sigaction (SIGALRM, &act, NULL) < 0) {
	printf ("ImageNdds_SendPkts: Error: could not set SIGALRM!\n");
	return -1;
    }
    // create an interval timer
    struct itimerval loopTime;
    loopTime.it_value.tv_sec = 0;	// initial delay
    loopTime.it_value.tv_usec = (imageLinkDelay * throttle) / 4;
    loopTime.it_interval.tv_sec = 0; // interval delay
    loopTime.it_interval.tv_usec = (imageLinkDelay * throttle) / 4;
    timerExpired = 0;
    if (setitimer (ITIMER_REAL, &loopTime, NULL) < 0) {
	printf ("ImageNdds_SendPkts: Error: could not set i-timer!\n");
	return -1;
    }
    return 0;
}

// Send the throttle speed for the link
// Assumes that a packet is not split at the IP layer
// Assumes packets are full
int
ImageNdds_SetLinkThroughPut (const int bitsPerSecond, const int packetSize) {

    const int bitsIP  = 8*20;		// Bits used by the IP header
    const int bitsUDP = 8*10;		// Bits used by the UDP header
    const int bitsNDDS = 8*20;		// Bits used by the NDDS header
    const int bitsImgOverhead = 8*8;	// Bytes for the XDR file, no data;
    const int bitsImgData = 8*packetSize;
    const int bitsPerPacket = bitsImgData + bitsImgOverhead
	+ bitsNDDS + bitsUDP + bitsIP;
    const int ticksPerSec = 1000000;	// Unix just use usec
    // We round down (truncate), because system timing tends to round up delays
    // compensate for average packet fill???
    imageLinkDelay = (int)(bitsPerPacket * (float)ticksPerSec / bitsPerSecond);
    if (imageLinkDelay <= 0)		// no faster than tick rate
	imageLinkDelay = 1;

					// store real BPS
    int bps = (int)((float)bitsPerPacket*ticksPerSec/imageLinkDelay);
    printf ("ImageNdds: packet loop %d ticks @ %d/sec, %d bits, %d bps (%d)\n",
	    imageLinkDelay, ticksPerSec, bitsPerPacket, bitsPerSecond,
	    bps);

    if (imageLinkBPS != bps) {
	imageLinkBPS = bps;
	imageThrottle = 4;
	ImageNddsSetupTimer(imageThrottle); // fire up timer at new rate
    }

    return imageLinkDelay;
}

int
ImageNdds_ThrottleThroughPut (int n) // (*4) 8 = 1/2 rate, 12 = 1/3 rate...
{
    if (n <= 4) n = 4;		// never go faster than link
    if (n == imageThrottle) return 0;
    if (n < imageThrottle) n = (n + imageThrottle) / 2;	// slow decay

					// fire up timer at new rate
    printf ("{T%d} ", n);
    return ImageNddsSetupTimer(imageThrottle = n); 
}

	
void
ImageNdds_WaitRoom (void)
{
    int i;
    for (i=99; !timerExpired && i; --i) {
	sleep_us (imageLinkDelay);
    }
    if (!timerExpired) {
	printf ("ImageNdds_WaitRoom timed out!\n");
	ImageNddsSetupTimer (imageThrottle); // restart timer
    }
    timerExpired = 0;
}

/* since the timer interrupts things all the time, use it to delay */
void
ImageNdds_WaitUsec (int usec)
{
    int n = usec / imageLinkDelay;
    if (n <= 0) n = 1;
    for (; n; --n) {
	timerExpired = 0;
	for (int i=5; !timerExpired && i; --i) {
	    sleep_us (imageLinkDelay);
	}
    }
}
