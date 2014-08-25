/* $Revision: 1.3 $ $Author: nomad $ $Date: 1997/05/04 23:18:52 $ */

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
 * $Log: telemNdds.cc,v $
// Revision 1.3  1997/05/04  23:18:52  nomad
// Added telemProducerAdjust to change timer period on the fly
//
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

#include <arbInternalState.h>
#include <morInternalState.h>
#include <steInternalState.h>

#ifndef NO_NOMAD
#include <modules/sm/sm_pointers.h>
#include <modules/sm/sm_names.h>
#endif

#include "telemNdds.h"

/***************************************************************************
 * STATICS
 ***************************************************************************/
// Id for task (context) that timers are created in.
static int telemProducerTaskId = NULL;

// Array of timers, one for each rate.
static timer_t telemProducerTimer[total_timers];

// Array of NDDS producers, one for each timer rate.
static NDDSProducer nddsTelemProducer[total_timers];

// Stubs for testing when not connected to shared memory package
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
  memset(p_apsDerived,0,sizeof(apsDerivedStateStruct));
  memset(p_apsRaw,0,sizeof(apsRawStateStruct));
  memset(p_bodDerived,0,sizeof(bodDerivedStateStruct));
  memset(p_bodRaw,0,sizeof(bodRawStateStruct));
  memset(p_gpsDerived,0,sizeof(gpsDerivedStateStruct));
  memset(p_gpsRaw,0,sizeof(gpsRawStateStruct));
  memset(p_imuDerived,0,sizeof(imuDerivedStateStruct));
  memset(p_imuRaw,0,sizeof(imuRawStateStruct));
  memset(p_kvhDerived,0,sizeof(kvhDerivedStateStruct));
  memset(p_posDerived,0,sizeof(posDerivedStateStruct));
  memset(p_posRaw,0,sizeof(posRawStateStruct));
  memset(p_lasHazard,0,sizeof(lasHazardMapStruct));
  memset(p_lasRawScan,0,sizeof(lasRawScanDataStruct));
  memset(p_arbInternal,0,sizeof(arbInternalStateStruct));
  memset(p_morInternal,0,sizeof(morInternalStateStruct));
  memset(p_steInternal,0,sizeof(steInternalStateStruct));

  //  logMsg("Initialized TelemProducer state\n",0,0,0,0,0,0);
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemNddsConnect
 * DESCRIPTION: Create NDDS producer and then subscribe messages
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Variable nddsTelemProducer is modified
 * DESIGN: 
 * NOTES: 
 *
 ***************************************************************************/
static void TelemNddsConnect(void)
{
  extern NDDSProducer nddsTelemProducer[];

  for(int i = 0; i < total_timers; i++){
    
    // Check for existing producer
    nddsTelemProducer[i] = NddsProducerGetByName(TP_NAME[i]);
    if(!nddsTelemProducer[i]){
      /* Create producer to handle normal commands */
      nddsTelemProducer[i] = NddsProducerCreate(TP_NAME[i],
						NDDS_SYNCHRONOUS,
						TP_NDDS_PERSISTENCE,
						TP_NDDS_STRENGTH);
    }
    logMsg("Created %s NDDS producer\n",(int)TP_NAME[i],0,0,0,0,0);
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemNddsSubscribe
 * DESCRIPTION: Subscribe to Nomad telemetry messages
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Messages are registered to producer
 * DESIGN:      Call autogenerated register code, and then add subscription
 *              to an nddsTelemProducer of the appropriate speed
 * NOTES:       See "NddsProducerProductionAdd" man page for arguments
 *
 ***************************************************************************/
static void TelemNddsSubscribe(void)
{
  extern NDDSProducer nddsTelemProducer[];

  //Subscribe fastest producers, currently 10Hz
  bodDerivedStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[fastest],
			    BOD_DERIVED_NAME, BOD_DERIVED_NAME,
			    p_bodDerived,0,NULL,NULL,NULL,NULL);

  imuDerivedStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[fastest],
			    IMU_DERIVED_NAME, IMU_DERIVED_NAME,
			    p_imuDerived,0,NULL,NULL,NULL,NULL);

  posDerivedStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[fastest],
			    POS_DERIVED_NAME, POS_DERIVED_NAME,
			    p_posDerived,0,NULL,NULL,NULL,NULL);
  
  //Subscribe fast producers, currently 1Hz
  apsDerivedStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[fast],
			    APS_DERIVED_NAME, APS_DERIVED_NAME,
			    p_apsDerived,0,NULL,NULL,NULL,NULL);

  kvhDerivedStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[fast],
			    KVH_DERIVED_NAME, KVH_DERIVED_NAME,
			    p_kvhDerived,0,NULL,NULL,NULL,NULL);

  gpsDerivedStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[fast],
			    GPS_DERIVED_NAME, GPS_DERIVED_NAME,
			    p_gpsDerived,0,NULL,NULL,NULL,NULL);

  //Subscribe slow producers, currently 0.1Hz
  arbInternalStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[slow],
			    ARB_INTERNAL_NAME, ARB_INTERNAL_NAME,
			    p_arbInternal,0,NULL,NULL,NULL,NULL);

  morInternalStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[slow],
			    MOR_INTERNAL_NAME, MOR_INTERNAL_NAME,
			    p_morInternal,0,NULL,NULL,NULL,NULL);

  steInternalStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[slow],
			    STE_INTERNAL_NAME, STE_INTERNAL_NAME,
			    p_steInternal,0,NULL,NULL,NULL,NULL);

  //Subscribe slowest producers, currently once per minute
  lasHazardMapNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[slowest],
			    LAS_HAZARD_NAME, LAS_HAZARD_NAME,
			    p_lasHazard,0,NULL,NULL,NULL,NULL);

  lasRawScanDataNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[slowest],
			    LAS_RAW_SCAN_NAME, LAS_RAW_SCAN_NAME,
			    p_lasRawScan,0,NULL,NULL,NULL,NULL);

  //Subscribe debug producers, currently once per minute
  apsRawStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[debug],
			    APS_RAW_NAME, APS_RAW_NAME,
			    p_apsRaw,0,NULL,NULL,NULL,NULL);

  bodRawStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[debug],
			    BOD_RAW_NAME, BOD_RAW_NAME,
			    p_bodRaw,0,NULL,NULL,NULL,NULL);


  gpsRawStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[debug],
			    GPS_RAW_NAME, GPS_RAW_NAME,
			    p_gpsRaw,0,NULL,NULL,NULL,NULL);

  imuRawStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[debug],
			    IMU_RAW_NAME, IMU_RAW_NAME,
			    p_imuRaw,0,NULL,NULL,NULL,NULL);

  posRawStateNddsRegister();
  NddsProducerProductionAdd(nddsTelemProducer[debug],
			    POS_RAW_NAME, POS_RAW_NAME,
			    p_posRaw,0,NULL,NULL,NULL,NULL);

  logMsg("Subscribed all TelemProducer messsages\n",0,0,0,0,0,0);
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemProducerCallback
 * DESCRIPTION: Runs when timer expires and sends robot telem messages
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  None
 * DESIGN: 
 * NOTES:       Can't do array reference in a switch, bummer.
 *
 ***************************************************************************/
void TelemProducerCallback(int sigNum)
{
  if (sigNum == TP_SIGNAL[fastest]){
    //    logMsg("Callback signal %d to fastest timer\n",sigNum,0,0,0,0,0);
    NddsProducerSample(nddsTelemProducer[fastest]);
  } else if (sigNum == TP_SIGNAL[fast]) {
    //    logMsg("Callback signal %d to fast timer\n",sigNum,0,0,0,0,0);
    NddsProducerSample(nddsTelemProducer[fast]);
  } else if (sigNum == TP_SIGNAL[slow]) {
    //    logMsg("Callback signal %d to slow timer\n",sigNum,0,0,0,0,0);
    NddsProducerSample(nddsTelemProducer[slow]);
  } else if (sigNum == TP_SIGNAL[slowest]) {
    //    logMsg("Callback signal %d to slowest timer\n",sigNum,0,0,0,0,0);
    NddsProducerSample(nddsTelemProducer[slowest]);
  } else if (sigNum == TP_SIGNAL[debug]) {
    //    logMsg("Callback signal %d to debug timer\n",sigNum,0,0,0,0,0);
    NddsProducerSample(nddsTelemProducer[slowest]);
  } else {
    logMsg("WARNING:Handling unknown timer\n",0,0,0,0,0,0);
    return;
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemProducerTask
 * DESCRIPTION: Spawned (by TelemProducerCreate) to init and host the timer
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  None
 * DESIGN:      Sets up timer and Ndds, and then update state information.
 * NOTES:       This task must stay alive for the timer to stay alive and
 *  the callback to keep working.  The telem producer task does not have
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
void TelemProducerTask(void)
{
  // Initialize telemetry messages
  TelemInitialize();

  // Register NDDS messages
  TelemNddsConnect();

  // Subscribe messages
  TelemNddsSubscribe();

  // Create timer and setup NDDS has been created
  TelemProducerStart();

  // NOTE: This sigsuspend loop can be replaced by any loop function
  // for example the telem estimator that never exits.  Alternatively,
  // The previous function calls could be made from some other
  // task.

  // Set sigmask to empty set
  sigset_t sigmask;
  sigemptyset(&sigmask);
  while(TRUE){
    // Suspend until signal (timer expire) arrives
    sigsuspend(&sigmask);
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemProducerCreate
 * DESCRIPTION: Spawns the TelemProducer task as independent process
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Spawns a task, modifies variable telemProducerTaskId
 * DESIGN: 
 * NOTES:
 *
 ***************************************************************************/
void TelemProducerCreate(void)
{
  extern int telemProducerTaskId;

  // Initialize NDDS
  NddsInit(NOMAD_NDDS_DOMAIN, NULL);
  NddsVerbositySet(2);
  NddsVerbosityErrorSet (2);
  
  // Spawn task if it does not exist
  if(!telemProducerTaskId) {
    if((telemProducerTaskId = taskSpawn("tTelem",
					 TP_PRIORITY,
					 TP_OPTIONS,
					 TP_STACK,
					 (FUNCPTR)TelemProducerTask,
					 0,0,0,0,0,0,0,0,0,0))==ERROR){
      logMsg("ERROR:Could not spawn TelemProducer task\n",0,0,0,0,0,0);
    }
  } else {
    logMsg("WARNING:Did not spawn TelemProducer task, which exists\n",
	   0,0,0,0,0,0);
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemProducerStart
 * DESCRIPTION: Creates a timer, connects it to the telemetry producer task,
 *              sets the time, and starts it running
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Creates timer, modifies variable telemProducerTimer
 * DESIGN: 
 * NOTES: Timer is currently using SIGALRM.  This is a bad idea if more
 *  than one timer will be used (likely).  Should organize alarms so that
 *  they don't ring each other.
 *
 *  1,000,000,000 nanoseconds is 1 second (or 1 Hz)
 *
 ***************************************************************************/
void TelemProducerStart(void)
{
  extern timer_t telemProducerTimer[];

  struct sigevent evp = {0,{NULL},NULL};
  struct sigaction action = {{NULL},0x0,0};
  struct itimerspec itime = {{0,0},{1,0}};
  
  // Set the signal handler
  action.sa_handler = (VOIDFUNCPTR)TelemProducerCallback;

  // Set up the timers
  for(int i = 0; i < total_timers; i++){

    if(!telemProducerTimer[i]){
      // Define the signal event
      evp.sigev_signo = TP_SIGNAL[i];
    
      // Create the timer
      if (timer_create(CLOCK_REALTIME,
		       &evp,
		       &telemProducerTimer[i])==ERROR){
	logMsg("ERROR:Could not create TelemProducer timer\n",0,0,0,0,0,0);
      } else {
	// Connect the telemProducer callback to the timer
	if (sigaction(TP_SIGNAL[i], &action, NULL) != OK) {
	  logMsg("ERROR:Could not connect TelemProducer to timer\n",
		 0,0,0,0,0,0);
	} else {
	  logMsg("Connected signal %d to %s timer\n",
		 TP_SIGNAL[i],(int)TP_NAME[i],0,0,0,0);
	}
      }
      //      timer_show(telemProducerTimer[i]);
    }

    if(telemProducerTimer[i]){
      itime.it_interval.tv_sec  = (time_t)TP_PERIOD[i];
      itime.it_interval.tv_nsec = (time_t)TP_UPERIOD[i];
      if (timer_settime(telemProducerTimer[i],NULL,&itime,NULL)==ERROR){
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
 * FUNCTION:    TelemProducerStop
 * DESCRIPTION: Stops the telem Producer process from sending messages
 * INPUTS:
 * OUTPUTS: 
 * EXCEPTIONS: 
 * DESIGN: 
 * NOTES: 
 *
 ***************************************************************************/
void TelemProducerStop(void)
{
  extern timer_t telemProducerTimer[];

  for(int i = 0; i < total_timers; i++){

    if(telemProducerTimer[i]) {
      // Cancel the timer
      if (timer_cancel(telemProducerTimer[i])==ERROR){
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
 * FUNCTION:    TelemProducerDelete
 * DESCRIPTION: Delete the timer and telem producer task
 * INPUTS:      None
 * OUTPUTS:     None
 * EXCEPTIONS:  Modifies variables telemProducerTimer and telemProducerTaskId
 * DESIGN: 
 * NOTES: 
 *
 ***************************************************************************/
void TelemProducerDelete(void)
{
  extern timer_t telemProducerTimer[];
  extern int telemProducerTaskId;

  for(int i = 0; i < total_timers; i++){
    if(telemProducerTimer[i]) {
      // Delete the timer
      if (timer_delete(telemProducerTimer[i])==ERROR){
	logMsg("ERROR:Could not delete %s timer\n",(int)TP_NAME[i],0,0,0,0,0);
      } else {
	telemProducerTimer[i] = NULL;
      }
    } else {
      logMsg("ERROR:Did not delete (NULL) %s timer\n",
	     (int)TP_NAME[i],0,0,0,0,0);
    }
  }

  if(telemProducerTaskId){
    if(taskDelete(telemProducerTaskId)==ERROR){
      logMsg("ERROR:Could not delete TelemProducer task",0,0,0,0,0,0);
    } else {
      telemProducerTaskId = NULL;
    }
  } else {
    logMsg("ERROR:Did not delete (NULL) TelemProducer task\n",0,0,0,0,0,0);
  }
  return;
}




/***************************************************************************
 *
 * FUNCTION:    TelemProducerAdjust
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
void TelemProducerAdjust(TP_TIMER_INDEX timer,
			 time_t period,
			 time_t nperiod)
{
  extern timer_t telemProducerTimer[];
  struct itimerspec itime = {{0,0},{1,0}};
  
  if(telemProducerTimer[timer]){
    itime.it_interval.tv_sec = (time_t)period;
    itime.it_interval.tv_nsec = (time_t)nperiod;
    if (timer_settime(telemProducerTimer[timer],NULL,&itime,NULL)==ERROR){
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
 *  FUNCTION:    SHORTCUTS
 *  DESCRIPTION: Shortcuts for console window operation
 *  INPUTS:      None
 *  OUTPUTS:     None
 *  EXCEPTIONS:  None
 *  DESIGN: 
 *  NOTES: 
 *
 ***************************************************************************/
void tpc(void) { TelemProducerCreate(); }
void tps(void) { TelemProducerStart(); }
void tpe(void) { TelemProducerStop(); }
void tpd(void) { TelemProducerDelete(); }

void tpa(TP_TIMER_INDEX timer,time_t period,time_t nperiod) {
  TelemProducerAdjust(timer,period,nperiod);
}
		      
  






