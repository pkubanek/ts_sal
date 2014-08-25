/* $Revision: 1.1 $ $Author: mwagner $ $Date: 1999/07/23 19:16:59 $ */

/*
 * moveNdds.c
 * 
 * Mark Sibenac
 * 97-4-15
 * Atacama Desert Trek
 * Field Robotics Center
 *
 * This file creates and deals with the consumer commands that processes and
 * computers are sending to the real-time computer.
 */

#include <vxWorks.h>
#include <sysLib.h>
#include <vme.h>
#include <taskLib.h>
#include <logLib.h>
#include <signal.h>
#include <timers.h>

#include "moveNdds.h"
#include "event.h"

NDDSSubscriber moveNddsSubscriber;
int   moveSubscriberPID;
int   moveTicks = -1;
timer_t moveNdds_timer;
int   wd_command=0;
int   moveDebug = 1;
int missed_timer_event = 1;

move   rtMoveCB;
event  timerEventCB;

extern void enableWatchdog ();
extern void disableWatchdog ();
extern void retriggerWatchdog ();

/* This function is called first to set up the timer and spawn the subscriber task*/
void moveSubscriberCreate(void)
{
  int tid;

  if ((tid = taskNameToId(TMOVENDDS_NAME)) != -1) taskDelete (tid);
  moveSubscriberPID = taskSpawn (TMOVENDDS_NAME, PRIORITY_MOVE_NDDS,
	       VX_SUPERVISOR_MODE | VX_DEALLOC_STACK | VX_FP_TASK | VX_STDIO,
	       20000, (FUNCPTR)moveSubscriberTask, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  logMsg ("Spawned the moveSubscriberTask as tMoveNdds.\n", 1,2,3,4,5,6);
}

void moveNddsConnect (void)
{
  wd_command = 0; /* reset watchdog */

  moveNddsRegister();
  eventNddsRegister();

  /* Check for existing Subscriber */
  if(!moveNddsSubscriber){
    /* Create Subscriber to handle normal commands */
    moveNddsSubscriber = NddsSubscriberCreate();
    logMsg("Created %s NDDS Subscriber\n",(int)MOVE_SUBSCRIBER_NAME,0,0,0,0,0);
  }
}

void moveNddsSubscribe(void)
{
  NddsSubscriberSubscriptionAdd(moveNddsSubscriber, 
				NddsSubscriptionCreate(NDDS_SUBSCRIPTION_POLLED,
						       RT_MOVE_NAME, MOVE_NAME, NULL,
						       MOVE_NDDS_DEADLINE,
						       MOVE_NDDS_MIN_SEPARATION,
						       moveSubscriberCallback, NULL));
  logMsg("Subscribed moveSubscriber messsages\n",0,0,0,0,0,0);
  return;
}

int moveSubscriberTask()
{
#ifdef USE_SIGS
  sigset_t sigmask;
#else
  int ticks;
#endif

  /* Register NDDS messages */
  moveNddsConnect();

  taskDelay(1);

  /* Subscribe messages */
  moveNddsSubscribe();

#ifdef USE_SIGS
  /* Create timer and setup NDDS has been created */
  moveSubscriberStart();

  while (1)
    {
      sigemptyset(&sigmask);
      sigsuspend(&sigmask);
      moveNddsCallback();
    }
#else /* USE_SIGS */
  ticks = MOVE_NDDS_PERIOD_SEC * sysClkRateGet();
  ticks += (int)((double)MOVE_NDDS_PERIOD_NSEC / 1e9 *  (double)sysClkRateGet());

  while (1)
    {
      moveNddsCallback();
      taskDelay(ticks);
    }
#endif /* USE_SIGS */
}

void moveSubscriberStart(void)
{
  extern timer_t    moveNdds_timer;
  struct sigaction  action = {{NULL},0x0,0};
  struct itimerspec itime = {{0,0},{1,0}};
  
  /* Set the signal handler */
    action.sa_handler = (VOIDFUNCPTR)moveNullFunc;

  /* Create the timer */
  if (timer_create(CLOCK_REALTIME, 0, &moveNdds_timer)==ERROR){
    logMsg("ERROR:Could not create moveNdds timer\n",0,0,0,0,0,0);
  } else {
    /* Connect the moveNdds callback to the timer */
    if (sigaction(SIGALRM, &action, NULL) != OK) {
      logMsg("ERROR:Could not connect moveNdds to timer\n", 0,0,0,0,0,0);
    } else {
      logMsg("Connected SIG_ALARM to moveNdds timer\n", 1,2,3,4,5,6);
    }
  }

  /* Set the timer for typical rate */
  itime.it_interval.tv_sec  = (time_t)MOVE_NDDS_PERIOD_SEC;
  itime.it_interval.tv_nsec = MOVE_NDDS_PERIOD_NSEC;

  if (timer_settime(moveNdds_timer,NULL,&itime,NULL)==ERROR){
    logMsg("ERROR:Could not set period for moveNdds timer\n", 1,2,3,4,5,6);
  } else {
    logMsg("Set moveNdds timer\n", 1,2,3,4,5,6);
  }

 /* Start Watchdog */
/*  enableWatchdog();*/
/*  retriggerWatchdog();*/
}

void moveNullFunc (void)
{
  return;
}

void moveSubscriberStop(void)
{
/*  disableWatchdog();*/
  timer_cancel(moveNdds_timer);
}

void moveSubscriberDelete(void)
{
  int tid;

/*  disableWatchdog();*/
  timer_cancel(moveNdds_timer);
  timer_delete(moveNdds_timer);
  moveNddsUnSubscribe();
  if ((tid = taskNameToId(TMOVENDDS_NAME)) != -1) taskDelete (tid);
}

void moveNddsCallback ()
{
  move a_move = {0.0, 0, 0.0, 0.0, 0.0, 0.0};

/*  retriggerWatchdog();*/
/*  TASKLOCK(); */

  NddsSubscriberPoll(moveNddsSubscriber);

  if (moveTicks != -1) {
    if (moveTicks == 0) {
      put_move(&a_move);
      moveTicks = -1;
    } else {
      moveTicks--;
    }
  }
  if (wd_command == 2)
    {
      wd_command = 0;
/*      put_move(&a_move);*/
    }
/*  TASKUNLOCK(); */
}

#define DEFAULT_TIMEOUT (120*10)
#define ROBOT_POINT_RADIUS (1.5)

RTIBool moveSubscriberCallback(NDDSRecvInfo *update)
{
  static int num=0;
  double translateTicks;
  extern int moveTicks;
  move *a_move;
  rtWDStruct sm_watchdog;

  /* Take out to actually use watchdog */
  get_rtWD (&sm_watchdog);
  semGive(sm_watchdog.semSignal);

  if (update->status == NDDS_FRESH_DATA)
    {
      /*      get_rtWD (&sm_watchdog);  Put in to use watchdog
 *	semGive(sm_watchdog.semSignal); */
      
      if (moveDebug)
	logMsg("Got a new move command #%d\n", num++, 2,3,4,5,6);
      put_move ((move *) update->instance);
      a_move = (move *)update->instance;
      moveTicks = DEFAULT_TIMEOUT;
      if (a_move->pointTurnFlag)
	{
	  if (a_move->turnDistance != 0.0 && a_move->turnSpeed != 0.0)
	    {
	      moveTicks =
		(a_move->turnDistance/a_move->turnSpeed/ROBOT_POINT_RADIUS) * 10.0;
	    } else {
	      moveTicks = DEFAULT_TIMEOUT;
	    }
	} else { /* not a point turn */
	  if (a_move->translateDistance != 0.0 && a_move->translateSpeed != 0.0) {
	    translateTicks =
	      ((a_move->translateDistance)/(a_move->translateSpeed))*10.0;
	  } else {
	    translateTicks = DEFAULT_TIMEOUT;
	  }
	  if (a_move->radius == 9999.0) {
	    moveTicks = translateTicks;
	  } else {
	    moveTicks = (int)(translateTicks);
	  }
	}
    } else if ((update->status == NDDS_NEVER_RECEIVED_DATA) || 
	       (update->status == NDDS_NO_NEW_DATA)) {
      /*logMsg("Missed a move command.\n", 1,2,3,4,5,6); */
      wd_command = 1;
    }
  return RTI_TRUE;
}

RTIBool eventSubscriberCallback(NDDSRecvInfo *update)
{
  rtWDStruct sm_watchdog;

  if (update->status == NDDS_FRESH_DATA)
    {
      get_rtWD (&sm_watchdog);
      semGive(sm_watchdog.semSignal);
      if (missed_timer_event)
	{
	  logMsg ("Got timerEvent back.\n", 1,2,3,4,5,6);
	  missed_timer_event = 0;
	}
    } else if ((update->status == NDDS_NEVER_RECEIVED_DATA) || 
	       (update->status == NDDS_NO_NEW_DATA)) {
      if (wd_command == 1) /* missed a move */
	{
	  if (!missed_timer_event)
	    {
	      logMsg("Missed a timerEvent message.\n", 1,2,3,4,5,6);
	      missed_timer_event = 1;
	    }
	  wd_command = 2;
	}
    }
  return RTI_TRUE;
}

void moveNddsUnSubscribe(void)
{
  if (moveNddsSubscriber) 
    {
      NddsSubscriberSubscriptionRemove(moveNddsSubscriber, RT_MOVE_NAME);
      NddsSubscriberSubscriptionRemove(moveNddsSubscriber, TIMER_EVENT_NAME);

      logMsg("UnSubscribed moveSubscriber messsages\n",0,0,0,0,0,0);
    }

  return;
}

void stopRobot (void)
{
  move a_move = {0.0, 0, 0.0, 0.0, 0.0, 0.0};

  printf("Stopping robot now.\n");
  put_move (&a_move);
}

void moveRobot (int speed_cm_sec, int rad_m)
{
  move a_move = {0.0, 0, 0.0, 0.0, 0.0, 0.0};

  printf("Moving robot at %d cm/s at %d m radius.\n", speed_cm_sec, rad_m);
  a_move.radius = (double)rad_m;
  a_move.translateSpeed = speed_cm_sec / 100.0;

  put_move (&a_move);
}
