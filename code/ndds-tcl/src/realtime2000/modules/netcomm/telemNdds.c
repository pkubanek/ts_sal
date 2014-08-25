/* $Revision: 1.1.1.1 $ $Author: sib $ $Date: 1999/10/22 20:35:47 $ */

/****************************************************************************
 *
 * PROJECT:     Nomad
 *
 * MODULE:      Real-time controller
 *
 * FILE:        telemNdds.cc
 *
 * DESCRIPTION: TelemProducer task is spawned to collect telem information
 *  and send out NDDS messages.
 *
 * EXPORTS: TelemProducerCreate - spawns the telem producer task
 *          TelemProducerStart  - starts the timer for the telem producer
 *          TelemProducerStop   - stops the timer for the telem producer
 *          TelemProducerDelete - deletes the telem producer task
 *
 * NOTES:   Shortcut functions spc, sps, spe, and spd are for use from
 *  the VxWorks command line.
 *
 *  Timing for callback functions is built on top of the VxWorks timer
 *  library (timerLib) which is in turn built on top of the signal
 *  (sigLib) and clock (clockLib) libraries.  It provides a mechanism
 *  by which tasks signal themselves after a designated interval.
 *
 * REVISION HISTORY:
 * $Log: telemNdds.c,v $
 * Revision 1.1.1.1  1999/10/22 20:35:47  sib
 * Yet another clean start
 *
 * Revision 1.4  1999/05/25 13:49:24  sib
 * Committed files Sib edited and created in Antarctica and until 5/25/99.
 *
 * Revision 1.3  1998/07/22 18:11:46  mwagner
 * REALLY added rtEmergencySignals, rtAmpState, and rtControlState. The previous
 * revision will not work.
 *
 * Revision 1.2  1998/07/21 15:43:25  mwagner
 * Added rtAmpState, rtEmergencyControls, and rtControlState
 *
 * Revision 1.3  1998/07/16 16:28:00  mwagner
 * Removed extra NULLs from calls to NddsProducerProductionAdd, thanks to upgrading to NDDS 2.0a
 *
 * Revision 1.2  1998/05/06 22:06:43  sib
 * Upgraded for VxWorks 5.3.1.
 * Got rid of scoping problems with variable declarations inside of for
 * loops which caused the system to crash intermitently.
 * Fixed startup script for ROMmed robot code.
 * Got rid of problems with KillRobot.
 *
 * Revision 1.1.1.1  1998/05/04 16:39:14  sib
 * Initial install of realtime code for vm62 running vxWorks 5.3.
 * Taken from 98-05-04 version.
 *
 * Revision 1.1.1.1  1998/02/20 02:26:31  sib
 * Initial install of Nomad Code for Meteorite Search
 *
 * Revision 1.14  1997/07/09  21:42:10  sib
 * Atacama Changes.
 *
 * Revision 1.13  1997/05/13  14:31:36  sib
 * Working before the Run
 *
 * Revision 1.12  1997/05/05  16:05:44  sib
 * Fixed probs with consumers, producers, and gps
 *
 * Revision 1.11  1997/05/05  00:11:37  sib
 * changed from handling telem in signal to handling it in tasks
 *
 * Revision 1.10  1997/05/03  23:30:51  sib
 * Added weather stuff
 *
 * Revision 1.9  1997/05/03  22:42:08  sib
 * Added laser stuff
 *
 * Revision 1.8  1997/04/27  18:17:43  sib
 * Changed Imakefiles to include Imakefile.common with more stuff.
 *
 * Revision 1.2  1997/04/12 00:17:50  dsw
 * Added multicast NddsInit
 *
 * Revision 1.1  1997/04/03 08:55:04  dsw
 * Renamed stateProducer.[cc,h] to telemNdds.[cc,h] to match up with CMU
 * convention.  Added additional messages.  Created NO_NOMAD switch that
 * does not access shared memory and use actual data.
 *
 * Revision 1.1  1997/04/03 08:40:36  dsw
 * Renamed stateProducer.[cc,h] to telemNdds.[cc,h] to match up with CMU
 * convention.  Added additional messages.  Created NO_NOMAD switch that
 * does not access shared memory and use actual data.
 *
 * Revision 1.2  1997/04/02 04:16:03  dsw
 * Set up multiple timers running at different rates.  Each timer produces
 * a different signal.  The callback checks signal number to determine
 * which ndds producer to sample.  Tested.  Works.  Need to add more messages.
 *
 * Revision 1.1  1997/03/28 02:26:53  dsw
 * Initial check-in with messages
 *
 * Revision 1.0  1997/03/26 01:34:44  dsw
 * Added Ndds routines to produce state message when timer expires
 *
 * Revision 0.1  1996/12/31 18:31:19  dsw
 * Created timer based routine to produce state information on at a
 * regular interval.
 *
 ***************************************************************************/

/***************************************************************************
 * INCLUDES
 ***************************************************************************/
#include <vxWorks.h>
#include <taskLib.h>
#include <logLib.h>
#include <signal.h>
#include <timers.h>
#include <string.h>

#include <NDDS.h>

#include <nomadNddsDomain.h>

#include <apsDerivedState.h>
#include <apsRawState.h>
#include <bodDerivedState.h>
#include <bodRawState.h>
#include <gpsDerivedState.h>
#include <gpsRawState.h>
#include <imuDerivedState.h>
#include <imuRawState.h>
#include <kvhDerivedState.h>
#include <posDerivedState.h>
#include <posRawState.h>
#include <lasHazardMap.h>
#include <lasRawScanData.h>
#include <sysState.h>
#include <rtEmergencySignals.h>
#include <rtControlState.h>
#include <rtAmpState.h>


#include <arbInternalState.h>
#include <morInternalState.h>
#include <steInternalState.h>

#ifndef NO_NOMAD
#include <sm_int.h>
#include <sm_names.h>
#endif

#include "telemNdds.h"

/***************************************************************************
 * CONSTANTS
 ***************************************************************************/
/* Telem publisher task parameters */
const int TP_PRIORITY = 100;
const int TP_OPTIONS  = VX_FP_TASK; /* USP VX_FP_TASK if floats */
const int TP_STACK    = (20000);

/* Telem publisher ndds parameters */
const float TP_NDDS_DEADLINE    = 4000.0;
const float TP_NDDS_SEPARATION  = 1.0;
const float TP_NDDS_STRENGTH    = 1.0;
const float TP_NDDS_PERSISTENCE = 15.0;

/* Telem publisher timer periods in nanoseconds */
const int TP_UPERIOD[total_timers] = {(long)5e8,    /*nanoseconds = 2Hz */
				      (long)1e9,   /*nanoseconds = 1Hz */
				      0,
				      0,
				      0};
/* Telem publisher timer periods in seconds */
const int TP_PERIOD[total_timers] = {0,
				     0,             /*seconds = 1Hz */
				     10,            /*seconds = 0.1Hz */
				     61,            /*seconds = 0.016Hz */
				     60};           /*seconds = 0.016Hz */

/* Telem publisher signals */
const int TP_SIGNAL[total_timers] = {27,
				     28,
				     29,
				     30,
				     31};

/* Telem publisher names */
const char* TP_NAME[total_timers] = {"TelemPublisherFastest",
				     "TelemPublisherFast",
				     "TelemPublisherSlow",
				     "TelemPublisherSlowest",
				     "TelemPublisherDebug"};


/***************************************************************************
 * STATICS
 ***************************************************************************/
static void CheckFreqChange (); 

/* Id for task (context) that timers are created in. */
static int telemPublisherTaskId = NULL;

/* Array of timers, one for each rate. */
static timer_t telemPublisherTimer[total_timers];

/* Array of NDDS publishers, one for each timer rate. */
static NDDSPublisher nddsTelemPublisher[total_timers];

/* Stubs for testing when not connected to shared memory package */
#ifdef NO_NOMAD
static apsDerivedStateStruct apsDerived;
static apsRawStateStruct apsRaw;
static bodDerivedStateStruct bodDerived;
static bodRawStateStruct bodRaw;
static gpsDerivedStateStruct gpsDerived;
static gpsRawStateStruct gpsRaw;
static imuDerivedStateStruct imuDerived;
static imuRawStateStruct imuRaw;
static kvhDerivedStateStruct kvhDerived;
static posDerivedStateStruct posDerived;
static posRawStateStruct posRaw;
static lasHazardMapStruct lasHazard;
static lasRawScanDataStruct lasRawScan;
static arbInternalStateStruct arbInternal;
static morInternalStateStruct morInternal;
static steInternalStateStruct steInternal;
static rtEmergencySignalsStruct rtEmergencySignals;
static rtAmpStateStruct rtAmpState;
static rtControlStateStruct rtControlState;

static apsDerivedStateStruct* p_apsDerived = &apsDerived;
static apsRawStateStruct* p_apsRaw         = &apsRaw;
static bodDerivedStateStruct* p_bodDerived = &bodDerived;
static bodRawStateStruct* p_bodRaw         = &bodRaw;
static gpsDerivedStateStruct* p_gpsDerived = &gpsDerived;
static gpsRawStateStruct* p_gpsRaw         = &gpsRaw;
static imuDerivedStateStruct* p_imuDerived = &imuDerived;
static imuRawStateStruct* p_imuRaw         = &imuRaw;
static kvhDerivedStateStruct* p_kvhDerived = &kvhDerived;
static posDerivedStateStruct* p_posDerived = &posDerived;
static posRawStateStruct* p_posRaw         = &posRaw;
static lasHazardMapStruct* p_lasHazard     = &lasHazard;
static lasRawScanDataStruct* p_lasRawScan     = &lasRawScan;
static arbInternalStateStruct* p_arbInternal = &arbInternal;
static morInternalStateStruct* p_morInternal = &morInternal;
static steInternalStateStruct* p_steInternal = &steInternal;
static rtControlStateStruct* p_rtControlState = &rtControlState;
static rtAmpStateStruct* p_rtAmpState = &rtAmpState;
static rtEmergencySignalsStruct* p_rtEmergencySignals = &rtEmergencySignals;

static const char* APS_DERIVED_NAME = "apsDerivedState";
static const char* APS_RAW_NAME     = "apsRawState";
static const char* BOD_DERIVED_NAME = "bodDerivedState";
static const char* BOD_RAW_NAME     = "bodRawState";
static const char* GPS_DERIVED_NAME = "gpsDerivedState";
static const char* GPS_RAW_NAME     = "gpsRawState";
static const char* IMU_DERIVED_NAME = "imuDerivedState";
static const char* IMU_RAW_NAME     = "imuRawState";
static const char* KVH_DERIVED_NAME = "kvhDerivedState";
static const char* POS_DERIVED_NAME = "posDerivedState";
static const char* POS_RAW_NAME     = "posRawState";
static const char* LAS_HAZARD_NAME  = "lasHazardMap";
static const char* LAS_RAW_SCAN_NAME     = "lasRawScan";
static const char* ARB_INTERNAL_NAME = "arbInternalState";
static const char* MOR_INTERNAL_NAME = "morInternalState";
static const char* STE_INTERNAL_NAME = "steInternalState";
static const char* RT_EMERGENCY_SIGNALS_NAME = "rtEmergencySignals";
static const char* RT_AMP_STATE_NAME = "rtAmpState";
static const char* RT_CONTROL_STATE_NAME = "rtControlState";
#endif




/***************************************************************************
 *
 * FUNCTION:    TelemInitialize
 * DESCRIPTION: Initialize state data structures
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Static data structures are zeroed.
 * DESIGN:
 * NOTES:       Many more data structures to add.
 *
 ***************************************************************************/
static void TelemInitialize(void)
{
  memset(p_apsDerived,0,sizeof(apsDerivedState));
  memset(p_apsRaw,0,sizeof(apsRawState));
  memset(p_bodDerived,0,sizeof(bodDerivedState));
  memset(p_bodRaw,0,sizeof(bodRawState));
  memset(p_gpsDerived,0,sizeof(gpsDerivedState));
  memset(p_gpsRaw,0,sizeof(gpsRawState));
  memset(p_imuDerived,0,sizeof(imuDerivedState));
  memset(p_imuRaw,0,sizeof(imuRawState));
  memset(p_kvhDerived,0,sizeof(kvhDerivedState));
  memset(p_posDerived,0,sizeof(posDerivedState));
  memset(p_posRaw,0,sizeof(posRawState));
  memset(p_lasHazardMap,0,sizeof(lasHazardMap));
  memset(p_lasRawScan,0,sizeof(lasRawScanData));
/*  memset(p_arbInternal,0,sizeof(arbInternalState));*/
/*  memset(p_morInternal,0,sizeof(morInternalState));*/
  memset(p_steInternal,0,sizeof(steInternalState));
  memset(p_rtEmergencySignals,0,sizeof(rtEmergencySignals));
  memset(p_rtAmpState,0,sizeof(rtAmpState));
  memset(p_rtControlState,0,sizeof(rtControlState));

  /*  logMsg("Initialized TelemPublisher state\n",0,0,0,0,0,0); */
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemNddsConnect
 * DESCRIPTION: Create NDDS publisher and then subscribe messages
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Variable nddsTelemPublisher is modified
 * DESIGN: 
 * NOTES: 
 *
 ***************************************************************************/
static void TelemNddsConnect(void)
{
  extern NDDSPublisher nddsTelemPublisher[total_timers];
  int i;

  for(i = 0; i < total_timers; i++){
    
    /* Check for existing publisher */
    if(!nddsTelemPublisher[i]){
      /* Create publisher to handle normal commands */
      nddsTelemPublisher[i] = NddsPublisherCreate(NDDS_PUBLISHER_SYNCHRONOUS);
    }
    logMsg("Created %s NDDS publisher\n",(int)TP_NAME[i],0,0,0,0,0);
  }
  return;
}



/***************************************************************************
 *
 * FUNCTION:    TelemNddsSubscribe
 * DESCRIPTION: Subscribe to Nomad telemetry messages
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Messages are registered to publisher
 * DESIGN:      Call autogenerated register code, and then add subscription
 *              to an nddsTelemPublisher of the appropriate speed
 * NOTES:       See "NddsPublisherProductionAdd" man page for arguments
 *
 ***************************************************************************/
static void TelemNddsSubscribe(void)
{
  extern NDDSPublisher nddsTelemPublisher[total_timers];

  /*Subscribe fastest publishers, currently 10Hz */
  bodDerivedStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[fastest],
			      NddsPublicationCreate(BOD_DERIVED_NAME, 
						    BOD_DERIVED_NAME,
						    p_bodDerived,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  posDerivedStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[fastest],
			      NddsPublicationCreate(POS_DERIVED_NAME, 
						    POS_DERIVED_NAME,
						    p_posDerived,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));
			    
  
  /*Subscribe fast publishers, currently 1Hz */
  apsDerivedStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[fast],
			      NddsPublicationCreate(APS_DERIVED_NAME, 
						    APS_DERIVED_NAME,
						    p_apsDerived,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));
			    
  kvhDerivedStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[fast],
			      NddsPublicationCreate(KVH_DERIVED_NAME, 
						    KVH_DERIVED_NAME,
						    p_kvhDerived,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));
			    
  gpsDerivedStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[fast],
			      NddsPublicationCreate(GPS_DERIVED_NAME, 
						    GPS_DERIVED_NAME,
						    p_gpsDerived,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));
			    
  weatherStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[fast],
			      NddsPublicationCreate(WEATHER_STATE_NAME, 
						    WEATHER_STATE_NAME,
						    p_weatherState,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));
			    
  bodRawStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[fast],
			      NddsPublicationCreate(BOD_RAW_NAME, 
						    BOD_RAW_NAME,
						    p_bodRaw,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));
			    

  /*Subscribe slow publishers, currently 0.1Hz */

  steInternalStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[slow],
			      NddsPublicationCreate(STE_INTERNAL_NAME, 
						    STE_INTERNAL_NAME,
						    p_steInternal,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  sysStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[slow],
			      NddsPublicationCreate(SYS_STATE_NAME, 
						    SYS_STATE_NAME,
						    p_sysState,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  rtEmergencySignalsNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[slow],
			      NddsPublicationCreate(RT_EMERGENCY_SIGNALS_NAME, 
						    RT_EMERGENCY_SIGNALS_NAME,
						    p_rtEmergencySignals,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  rtAmpStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[slow],
			      NddsPublicationCreate(RT_AMP_STATE_NAME, 
						    RT_AMP_STATE_NAME,
						    p_rtAmpState,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  rtControlStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[slow],
			      NddsPublicationCreate(RT_CONTROL_STATE_NAME, 
						    RT_CONTROL_STATE_NAME,
						    p_rtControlState,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  /*Subscribe slowest publishers, currently once per minute */

  imuDerivedStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[slowest],
			      NddsPublicationCreate(IMU_DERIVED_NAME, 
						    IMU_DERIVED_NAME,
						    p_imuDerived,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));


  /*Subscribe debug publishers, currently once per minute */
  apsRawStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[debug],
			      NddsPublicationCreate(APS_RAW_NAME, 
						    APS_RAW_NAME,
						    p_apsRaw,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  gpsRawStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[debug],
			      NddsPublicationCreate(GPS_RAW_NAME, 
						    GPS_RAW_NAME,
						    p_gpsRaw,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  imuRawStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[debug],
			      NddsPublicationCreate(IMU_RAW_NAME,
						    IMU_RAW_NAME,
						    p_imuRaw,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  posRawStateNddsRegister();
  NddsPublisherPublicationAdd(nddsTelemPublisher[debug],
			      NddsPublicationCreate(POS_RAW_NAME, 
						    POS_RAW_NAME,
						    p_posRaw,
						    TP_NDDS_PERSISTENCE, 
						    TP_NDDS_STRENGTH));

  logMsg("Subscribed all TelemPublisher messsages\n",0,0,0,0,0,0);
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemPublisherCallback
 * DESCRIPTION: Runs when timer expires and sends robot telem messages
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  None
 * DESIGN: 
 * NOTES:       Can't do array reference in a switch, bummer.
 *
 ***************************************************************************/
void TelemPublisherCallback(int sigNum)
{
  if (sigNum == TP_SIGNAL[fastest]){
    /*    logMsg("Callback signal %d to fastest timer\n",sigNum,0,0,0,0,0); */
    NddsPublisherSend(nddsTelemPublisher[fastest]);
  } else if (sigNum == TP_SIGNAL[fast]) {
    /*    logMsg("Callback signal %d to fast timer\n",sigNum,0,0,0,0,0); */
    NddsPublisherSend(nddsTelemPublisher[fast]);
    CheckFreqChange();
  } else if (sigNum == TP_SIGNAL[slow]) {
    /*    logMsg("Callback signal %d to slow timer\n",sigNum,0,0,0,0,0); */
    NddsPublisherSend(nddsTelemPublisher[slow]);
  } else if (sigNum == TP_SIGNAL[slowest]) {
    /*    logMsg("Callback signal %d to slowest timer\n",sigNum,0,0,0,0,0); */
    NddsPublisherSend(nddsTelemPublisher[slowest]);
  } else if (sigNum == TP_SIGNAL[debug]) {
    /*logMsg("Callback signal %d to debug timer\n",sigNum,0,0,0,0,0);*/
    NddsPublisherSend(nddsTelemPublisher[debug]);
  } else {
    logMsg("WARNING:Handling unknown timer\n",0,0,0,0,0,0);
    return;
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemPublisherTask
 * DESCRIPTION: Spawned (by TelemPublisherCreate) to init and host the timer
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  None
 * DESIGN:      Sets up timer and Ndds, and then update state information.
 * NOTES:       This task must stay alive for the timer to stay alive and
 *  the callback to keep working.  The telem publisher task does not have
 *  to be task that starts the timer but it does have to be something that
 *  does not die--for example the position estimation routine.
 *
 *  This may be a good place to do (or call) the sample collection routines
 *  that NDDS will then transmit each time the timer expires.  Right now,
 *  this task sleeps by doing a sigsuspend--which co-incidentally causes it
 *  to wake up at the same frequency the timer is set to.  This does not
 *  have to be the case, the loop could collect sensor data a different
 *  rate and use sleep to pause on each cycle.  Turn down the priority to
 *  make sure everyone else gets to run.
 *
 ***************************************************************************/
void TelemPublisherTask(void)
{
sigset_t sigmask;
int retSignal;

  /* Initialize telemetry messages */
  TelemInitialize();

  /* Register NDDS messages */
  TelemNddsConnect();

  /* Subscribe messages */
  TelemNddsSubscribe();

  /* Create timer and setup NDDS has been created */
  TelemPublisherStart();

  /* NOTE: This sigsuspend loop can be replaced by any loop function */
  /* for example the telem estimator that never exits.  Alternatively, */
  /* The previous function calls could be made from some other */
  /* task. */

  /* Set sigmask to empty set */
  sigfillset(&sigmask);
  while(TRUE){
    /* Suspend until signal (timer expire) arrives */
    retSignal = sigtimedwait(&sigmask, NULL, NULL);
    if (retSignal > 0) TelemPublisherCallback(retSignal);
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemPublisherCreate
 * DESCRIPTION: Spawns the TelemPublisher task as independent process
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Spawns a task, modifies variable telemPublisherTaskId
 * DESIGN: 
 * NOTES:
 *
 ***************************************************************************/
void TelemPublisherCreate(void)
{
  extern int telemPublisherTaskId;

  /* Spawn task if it does not exist */
  if(!telemPublisherTaskId) {
    if((telemPublisherTaskId = taskSpawn("tTelem",
					 TP_PRIORITY,
					 TP_OPTIONS,
					 TP_STACK,
					 (FUNCPTR)TelemPublisherTask,
					 0,0,0,0,0,0,0,0,0,0))==ERROR){
      logMsg("ERROR:Could not spawn TelemPublisher task\n",0,0,0,0,0,0);
    }
  } else {
    logMsg("WARNING:Did not spawn TelemPublisher task, which exists\n",
	   0,0,0,0,0,0);
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemPublisherStart
 * DESCRIPTION: Creates a timer, connects it to the telemetry publisher task,
 *              sets the time, and starts it running
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Creates timer, modifies variable telemPublisherTimer
 * DESIGN: 
 * NOTES: Timer is currently using SIGALRM.  This is a bad idea if more
 *  than one timer will be used (likely).  Should organize alarms so that
 *  they don't ring each other.
 *
 *  1,000,000,000 nanoseconds is 1 second (or 1 Hz)
 *
 ***************************************************************************/

static void nullHandler()
{
}

void TelemPublisherStart(void)
{
  extern timer_t telemPublisherTimer[total_timers];

  struct sigevent evp = {0,{NULL},NULL};
  struct sigaction action = {{NULL},0x0,0};
  struct itimerspec itime = {{0,0},{1,0}};
  int i;

  /* Set the signal handler */
  action.sa_handler = (VOIDFUNCPTR)nullHandler;

  /* Set up the timers */
  for(i = 0; i < total_timers; i++){

    if(!telemPublisherTimer[i]){
      /* Define the signal event */
      evp.sigev_signo = TP_SIGNAL[i];
    
      /* Create the timer */
      if (timer_create(CLOCK_REALTIME,
		       &evp,
		       &telemPublisherTimer[i])==ERROR){
	logMsg("ERROR:Could not create TelemPublisher timer\n",0,0,0,0,0,0);
      } else {
	/* Connect the telemPublisher callback to the timer */
	if (sigaction(TP_SIGNAL[i], &action, NULL) != OK) {
	  logMsg("ERROR:Could not connect TelemPublisher to timer\n",
		 0,0,0,0,0,0);
	} else {
	  logMsg("Connected signal %d to %s timer\n",
		 TP_SIGNAL[i],(int)TP_NAME[i],0,0,0,0);
	}
      }
      /*      timer_show(telemPublisherTimer[i]); */
    }

    if(telemPublisherTimer[i]){
      /* Set the timer for 1/10th of a second */
      itime.it_interval.tv_sec  = (time_t)TP_PERIOD[i];
      itime.it_interval.tv_nsec = TP_UPERIOD[i];
      if (timer_settime(telemPublisherTimer[i],NULL,&itime,NULL)==ERROR){
	logMsg("ERROR:Could not set period for %s timer\n",
	       (int)TP_NAME[i],0,0,0,0,0);
      } else {
	logMsg("Set %s timer\n",(int)TP_NAME[i],0,0,0,0,0);
      }
    }
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemPublisherStop
 * DESCRIPTION: Stops the telem Publisher process from sending messages
 * INPUTS:
 * OUTPUTS: 
 * EXCEPTIONS: 
 * DESIGN: 
 * NOTES: 
 *
 ***************************************************************************/
void TelemPublisherStop(void)
{
  extern timer_t telemPublisherTimer[total_timers];
  int i;

  for(i = 0; i < total_timers; i++){

    if(telemPublisherTimer[i]) {
      /* Cancel the timer */
      if (timer_cancel(telemPublisherTimer[i])==ERROR){
	logMsg("ERROR:Could not cancel %s timer\n",(int)TP_NAME[i],0,0,0,0,0);
      } else {
	logMsg("Stopped %s timer\n",(int)TP_NAME[i],0,0,0,0,0);
      }
    } else {
      logMsg("WARNING:Did not cancel (NULL) %s timer\n",
	     (int)TP_NAME[i],0,0,0,0,0);
    }
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemPublisherDelete
 * DESCRIPTION: Delete the timer and telem publisher task
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Modifies variables telemPublisherTimer and telemPublisherTaskId
 * DESIGN: 
 * NOTES: 
 *
 ***************************************************************************/
void TelemPublisherDelete(void)
{
  extern timer_t telemPublisherTimer[total_timers];
  extern int telemPublisherTaskId;
  int i;

  for(i = 0; i < total_timers; i++){
    if(telemPublisherTimer[i]) {
      /* Delete the timer */
      if (timer_delete(telemPublisherTimer[i])==ERROR){
	logMsg("ERROR:Could not delete %s timer\n",(int)TP_NAME[i],0,0,0,0,0);
      } else {
	telemPublisherTimer[i] = NULL;
      }
    } else {
      logMsg("ERROR:Did not delete (NULL) %s timer\n",
	     (int)TP_NAME[i],0,0,0,0,0);
    }
  }

  if(telemPublisherTaskId){
    if(taskDelete(telemPublisherTaskId)==ERROR){
      logMsg("ERROR:Could not delete TelemPublisher task",0,0,0,0,0,0);
    } else {
      telemPublisherTaskId = NULL;
    }
  } else {
    logMsg("ERROR:Did not delete (NULL) TelemPublisher task\n",0,0,0,0,0,0);
  }

  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemPublisherAdjust
 * DESCRIPTION: Adjust the timer interval
 * INPUTS:      timer   is a TP_TIMER_INDEX one of:
 *                      fastest, fast, slow, slowest, debug
 *              period  is the timer interval in seconds 0 if less
 *                      than one second)
 *              nperiod is the timer interval in nanoseconds
 * OUTPUTS:     None
 * EXCEPTIONS:  Adjusts the timer
 * DESIGN: 
 * NOTES:
 *  1,000,000,000 nanoseconds is 1 second (or 1 Hz)
 *
 ***************************************************************************/
void TelemPublisherAdjust(TP_TIMER_INDEX timer,
			 time_t period,
			 time_t nperiod)
{
  extern timer_t telemPublisherTimer[total_timers];
  struct itimerspec itime = {{0,0},{1,0}};
  
  if(telemPublisherTimer[timer]){
    itime.it_interval.tv_sec = (time_t)period;
    itime.it_interval.tv_nsec = (time_t)nperiod;
    if (timer_settime(telemPublisherTimer[timer],NULL,&itime,NULL)==ERROR){
      logMsg("ERROR:Could not set period (%dsec %dnsec) for %s timer\n",
	     period,nperiod,(int)TP_NAME[timer],0,0,0);
    } else {
	logMsg("Set period (%dsec %dnsec) for %s timer\n",
	     period,nperiod,(int)TP_NAME[timer],0,0,0);
    }
  }
  return;
}


/***************************************************************************
 *
 *  FUNCTION:    CheckFreqChange
 *  DESCRIPTION: Checks the semaphore in rtSetBroadcastFreq2 in SM to see if a
 *  frequency change message came in. The cmdNdds process on the 030 receives
 *  the message and passes thru SM with a "given" semaphore.
 *  INPUTS:      None
 *  OUTPUTS:     None
 *  EXCEPTIONS:  Changes frequency of one of the publishers
 *  DESIGN: 
 *  NOTES: 
 *
 ***************************************************************************/
void CheckFreqChange () 
{
  rtSetBroadcastFreq2Struct Freq2;

  get_rtSetBroadcastFreq2 (&Freq2);

  if (semTake(Freq2.semSignal, NO_WAIT) == OK)
    {
      time_t period;
      time_t nperiod;
      
      period = (time_t)(1.0/Freq2.freq);
      nperiod = (time_t)(1.0e9/Freq2.freq - period*1.0e9);
      TelemPublisherAdjust (Freq2.sourceId, period, nperiod);
    }
}


/***************************************************************************
 *
 *  FUNCTION:    SHORTCUTS
 *  DESCRIPTION: Shortcuts for console window operation
 *  INPUTS:      None
 *  OUTPUTS:     None
 *  EXCEPTIONS:  None
 *  DESIGN: 
 *  NOTES: 
 *
 ***************************************************************************/
void tpc(void) { TelemPublisherCreate(); }
void tps(void) { TelemPublisherStart(); }
void tpe(void) { TelemPublisherStop(); }
void tpd(void) { TelemPublisherDelete(); }
void tpa(TP_TIMER_INDEX timer,time_t period,time_t nperiod)
{
  TelemPublisherAdjust(timer,period,nperiod);
}






