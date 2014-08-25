// -*- C++ -*-
//	File:	imageNddsP.h
//	Date:	23 Dec 1996
//	  By:	Kurt Schwehr (schwehr@artemis.arc.nasa.gov)
//	 For:	NASA Ames Research Center, Intelligent Mechanisms Group
//  Function:	See imageNdds.cc

#include "imageNdds.h"

#ifdef VXWORKS // From VxWorks includes
#define MUTEX_CREATE(s) s = semBCreate (SEM_Q_FIFO, SEM_FULL)
#define MUTEX_LOCK(s,t) semTake ((s), (t))
#define MUTEX_UNLOCK(s) semGive ((s))

#else  // Unix Posix threads version of VxWorks stuff

#define logMsg	printf
#define SEM_ID pthread_mutex_t
#define SEM_EMPTY	0
#define SEM_FULL	1
#define NO_WAIT		0
#define WAIT_FOREVER	(-1)
					// always starts FULL
#define MUTEX_CREATE(s) pthread_mutex_init (&(s), (const pthread_mutexattr_t *)NULL)
#define MUTEX_LOCK(s,t) pthread_mutex_lock (&(s))
#define MUTEX_UNLOCK(s) pthread_mutex_unlock (&(s))
#define taskDelay(n)	sleep_us((n)*4096)
#endif
