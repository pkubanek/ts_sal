/* $Revision: 1.3 $ $Author: sib $ $Date: 1998/09/23 15:02:24 $ */

/*
 * nddsSock.c
 * 
 * Mark Sibenac
 * 98-10-8
 * Atacama Desert Trek
 * Field Robotics Center
 *
 */

#include <vxWorks.h>
#include <sysLib.h>
#include <vme.h>
#include <taskLib.h>
#include <logLib.h>
#include <signal.h>
#include <timers.h>

#include "connectAtPort.h"
#include "sm_int.h"

int moveDebug = 0;

/* This function is called first to set up the timer and spawn the consumer task*/
void nddsSockCreate(void)
{
  int tid;

  if ((tid = taskNameToId(TMOVENDDS_NAME)) != -1) taskDelete (tid);
  taskSpawn (TMOVENDDS_NAME, PRIORITY_MOVE_NDDS,
	       VX_SUPERVISOR_MODE | VX_DEALLOC_STACK | VX_FP_TASK | VX_STDIO,
	       20000, (FUNCPTR)nddsSockTask, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  logMsg ("Spawned the nddsSockTask as tNddsSock.\n", 1,2,3,4,5,6);
}

void nddsSockConnect (void)
{
  wd_command = 0; /* reset watchdog */

}

void nddsSockSubscribe(void)
{
}

int nddsSockTask()
{
#ifdef USE_SIGS
  sigset_t sigmask;
#else
  int ticks;
#endif

  /* Register NDDS messages */
  nddsSockConnect();

  taskDelay(1);

  /* Subscribe messages */
  nddsSockSubscribe();

#ifdef USE_SIGS
  /* Create timer and setup NDDS has been created */
  nddsSockStart();

  while (1)
    {
      sigemptyset(&sigmask);
      sigsuspend(&sigmask);
      nddsSockCallback();
    }
#else /* USE_SIGS */
  ticks = MOVE_NDDS_PERIOD_SEC * sysClkRateGet();
  ticks += (int)((double)MOVE_NDDS_PERIOD_NSEC / 1e9 *  (double)sysClkRateGet());

  while (1)
    {
      nddsSockCallback();
      taskDelay(ticks);
    }
#endif /* USE_SIGS */
}

void nddsSockStart(void)
{
  extern timer_t    nddsSock_timer;
  struct sigaction  action = {{NULL},0x0,0};
  struct itimerspec itime = {{0,0},{1,0}};
  
  /* Set the signal handler */
    action.sa_handler = (VOIDFUNCPTR)moveNullFunc;

  /* Create the timer */
  if (timer_create(CLOCK_REALTIME, 0, &nddsSock_timer)==ERROR){
    logMsg("ERROR:Could not create nddsSock timer\n",0,0,0,0,0,0);
  } else {
    /* Connect the nddsSock callback to the timer */
    if (sigaction(SIGALRM, &action, NULL) != OK) {
      logMsg("ERROR:Could not connect nddsSock to timer\n", 0,0,0,0,0,0);
    } else {
      logMsg("Connected SIG_ALARM to nddsSock timer\n", 1,2,3,4,5,6);
    }
  }

  /* Set the timer for typical rate */
  itime.it_interval.tv_sec  = (time_t)MOVE_NDDS_PERIOD_SEC;
  itime.it_interval.tv_nsec = MOVE_NDDS_PERIOD_NSEC;

  if (timer_settime(nddsSock_timer,NULL,&itime,NULL)==ERROR){
    logMsg("ERROR:Could not set period for nddsSock timer\n", 1,2,3,4,5,6);
  } else {
    logMsg("Set nddsSock timer\n", 1,2,3,4,5,6);
  }

 /* Start Watchdog */
/*  enableWatchdog();*/
/*  retriggerWatchdog();*/
}

void moveNullFunc (void)
{
  return;
}

void nddsSockStop(void)
{
/*  disableWatchdog();*/
  timer_cancel(nddsSock_timer);
}

void nddsSockDelete(void)
{
  int tid;

/*  disableWatchdog();*/
  timer_cancel(nddsSock_timer);
  timer_delete(nddsSock_timer);
  nddsSockUnSubscribe();
  if ((tid = taskNameToId(TnddsSock_NAME)) != -1) taskDelete (tid);
}

void nddsSockCallback ()
{
  NDDSConsumer mnc;
  moveStruct a_move = {0.0, 0, 0.0, 0.0, 0.0, 0.0};

/*  retriggerWatchdog();*/
/*  TASKLOCK(); */

  mnc = NddsConsumerGetByName(MOVE_CONSUMER_NAME);
/*  NddsConsumerPoll(mnc);*/

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

NDDSObjectInstance nddsSockCallback(NDDSUpdateInfo update)
{
  static int num=0;
  double translateTicks;
  extern int moveTicks;
  move a_move;
  rtWDStruct sm_watchdog;

/* Take out to actually use watchdog */
/*      get_rtWD (&sm_watchdog);
      semGive(sm_watchdog.semSignal);*/

  if (update->updateStatus == NDDS_FRESH_DATA)
    {
      get_rtWD (&sm_watchdog);
      semGive(sm_watchdog.semSignal);

      if (moveDebug)
	logMsg("Got a new move command #%d\n", num++, 2,3,4,5,6);
      put_move ((move) update->instance);
      a_move = (move)update->instance;
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
    } else if ((update->updateStatus == NDDS_NEVER_RECEIVED_DATA) || 
	       (update->updateStatus == NDDS_NO_NEW_DATA)) {
      /*logMsg("Missed a move command.\n", 1,2,3,4,5,6); */
      wd_command = 1;
    }
  return update->instance;
}

NDDSObjectInstance eventConsumerCallback(NDDSUpdateInfo update)
{
  rtWDStruct sm_watchdog;

  if (update->updateStatus == NDDS_FRESH_DATA)
    {
      get_rtWD (&sm_watchdog);
      semGive(sm_watchdog.semSignal);
    } else if ((update->updateStatus == NDDS_NEVER_RECEIVED_DATA) || 
	       (update->updateStatus == NDDS_NO_NEW_DATA)) {
      if (wd_command == 1) /* missed a move */
	{
	  logMsg("Missed a timerEvent message.\n", 1,2,3,4,5,6);
	  wd_command = 2;
	}
    }
  return update->instance;
}

void nddsSockUnSubscribe(void)
{
  NDDSConsumer nddsSock;

  if ((nddsSock = NddsConsumerGetByName("nddsSock")))
    {
      NddsConsumerSubscriptionRemove(nddsSock, MOVE_NAME, RT_MOVE_NAME);
      NddsConsumerSubscriptionRemove(nddsSock, EVENT_NAME, TIMER_EVENT_NAME);

      logMsg("UnSubscribed nddsSock messsages\n",0,0,0,0,0,0);
    }

  return;
}

void stopRobot (void)
{
  moveStruct a_move = {0.0, 0, 0.0, 0.0, 0.0, 0.0};

  printf("Stopping robot now.\n");
  put_move (&a_move);
}

void moveRobot (int speed_cm_sec, int rad_m)
{
  moveStruct a_move = {0.0, 0, 0.0, 0.0, 0.0, 0.0};

  printf("Moving robot at %d cm/s at %d m radius.\n", speed_cm_sec, rad_m);
  a_move.radius = (double)rad_m;
  a_move.translateSpeed = ((double)speed_cm_sec)/100.0;

  put_move (&a_move);
}
