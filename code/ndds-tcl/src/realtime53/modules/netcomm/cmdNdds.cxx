/* $Revision: 1.5 $ $Author: sib $ $Date: 1998/07/28 19:12:12 $ */

/*
 * cmdNdds.cxx
 * 
 * Mark Sibenac
 * 97-4-15
 * Atacama Desert Trek
 * Field Robotics Center
 *
 * This file creates and deals with the consumer commands that processes and
 * computers are sending to the real-time computer. These are specific for the
 * 030 which is running the servo code.
 *
 */

#include "cmdNdds.h"

#include <taskLib.h>
#include <logLib.h>
#include <signal.h>
#include <timers.h>
#include <string.h>
#include <rebootLib.h>

#include "drivesys.h"
// MDW 6/8/99
#ifdef USE_POINT
#include "pointsys.h"
#endif
#include "sm_int.h"
#include "sm_names.h"
#include "commonFunc.h"

#define TCMDNDDS_NAME    "tCmdNdds"
#define PRIORITY_CMD_NDDS (75)

/* # MDW: Changed for NDDS upgrade work I started on 6/7/99 */
NDDSSubscriber cmdNddsSubscriber;
NDDSSubscriber moveNddsSubScriber;
static int   cmdSubscriberPID;
static int   moveTicks = -1;
timer_t      cmdNdds_timer;
struct itimerspec cmdNdds_timer_value;
int          bChassisMove;


/* # MDW: Changed for NDDS upgrade work I started on 6/7/99 */
#define NCSA(name, pointer_name, signal_num, type) \
type *pointer_name = (type *)calloc(1, sizeof(type)); \
NddsSubscriberSubscriptionAdd(cmdNddsSubscriber, \
			      NddsSubscriptionCreate(NDDS_SUBSCRIPTION_POLLED, \
						     name, name, pointer_name, \
						     CMD_NDDS_DEADLINE, \
						     CMD_NDDS_MIN_SEPARATION, \
						     cmdSubscriberCallback, \
						     (void *)signal_num));

/* # MDW: Changed for NDDS upgrade work I started on 6/7/99 */
#define NCSR(name) \
NddsSubscriberSubscriptionRemove(cmdNddsSubscriber, name);

void cmdSubscriberCreate(void)
{
  int tid;

  if ((tid = taskNameToId(TCMDNDDS_NAME)) != -1) taskDelete (tid);
  cmdSubscriberPID = taskSpawn (TCMDNDDS_NAME, PRIORITY_CMD_NDDS, VX_FP_TASK,
			      20000, (FUNCPTR)cmdSubscriberTask, 0, 0, 0, 0,
			      0, 0, 0, 0, 0, 0);
  logMsg ("Spawned the cmdSubscriberTask as tCmdNdds.\n", 1,2,3,4,5,6);
}

void cmdNddsConnect (void)
{
  /* Check for existing Subscriber */
  if(!cmdNddsSubscriber){
    /* Create Subscriber to handle normal commands */
    cmdNddsSubscriber = NddsSubscriberCreate();
    logMsg("Created %s NDDS subscriber\n",(int)CMD_NAME,0,0,0,0,0);
  }
}

void cmdNddsSubscribe(void)
{
  rtDriveNddsRegister();
  NCSA(RT_DRIVE_NAME, rtDriveMem, RT_DRIVE, rtDrive);

  rtSetActuatorNddsRegister();
  NCSA(RT_SET_ACTUATOR_NAME, rtSetActuatorMem, RT_SET_ACTUATOR, rtSetActuator);

  rtSetBroadcastFreqNddsRegister();
  NCSA(RT_SET_BROADCAST_FREQ_NAME, rtSetBroadcastFreqMem, RT_SET_BROADCAST_FREQ, rtSetBroadcastFreq);

  rtSetParamFloatNddsRegister();
  NCSA(RT_SET_PARAM_FLOAT_NAME, rtSetParamFloatMem, RT_SET_PARAM_FLOAT, rtSetParamFloat);

  rtSetParamIntNddsRegister();
  NCSA(RT_SET_PARAM_INT_NAME, rtSetParamIntMem, RT_SET_PARAM_INT, rtSetParamInt);

  rtSetPosEstParamsNddsRegister();
  NCSA(RT_SET_POS_EST_PARAMS_NAME, rtSetPosEstParamsMem, RT_SET_POS_EST_PARAMS, rtSetPosEstParams);

  rtSetServoParamsNddsRegister();
  NCSA(RT_SET_SERVO_PARAMS_NAME, rtSetServoParamsMem, RT_SET_SERVO_PARAMS, rtSetServoParams);

  rtSignalConditionNddsRegister();
  NCSA(RT_SIGNAL_CONDITION_NAME, rtSignalConditionMem, RT_SIGNAL_CONDITION, rtSignalCondition);

  rtLaserNddsRegister();
  NCSA(RT_LASER_NAME, rtLaserMem, RT_LASER, rtLaser);

  rtChassisConfigNddsRegister();
  NCSA(RT_CHASSIS_CONFIG_NAME, rtChassisConfigMem, RT_CHASSIS_CONFIG, rtChassisConfig);

  rtControlStateNddsRegister();
  NCSA(RT_CONTROL_STATE_NAME, rtControlStateMem, RT_CONTROL_STATE, rtControlState);

  rtAmpStateNddsRegister();
  NCSA(RT_AMP_STATE_NAME, rtAmpStateMem, RT_AMP_STATE, rtAmpState);

  logMsg("Subscribed cmdSubscriber messsages\n",0,0,0,0,0,0);
  return;
}

void cmdNddsUnSubscribe(void)
{
  if (!cmdNddsSubscriber)
    {
      NCSR(RT_DRIVE_NAME);
      NCSR(RT_SET_ACTUATOR_NAME);
      NCSR(RT_SET_BROADCAST_FREQ_NAME);
      NCSR(RT_SET_PARAM_FLOAT_NAME);
      NCSR(RT_SET_PARAM_INT_NAME);
      NCSR(RT_SET_POS_EST_PARAMS_NAME);
      NCSR(RT_SET_SERVO_PARAMS_NAME);
      NCSR(RT_SIGNAL_CONDITION_NAME);
      NddsSubscriberSubscriptionRemove(cmdNddsSubscriber, RT_MOVE_NAME);
      NCSR(RT_LASER_NAME);
      NCSR(RT_CHASSIS_CONFIG_NAME);
      NCSR(RT_EMERGENCY_SIGNALS_NAME);
      NCSR(RT_AMP_STATE_NAME);
      NCSR(RT_CONTROL_STATE_NAME);

      logMsg("UnSubscribed cmdSubscriber messsages\n",0,0,0,0,0,0);
    }

  return;
}

int cmdSubscriberTask()
{
  sigset_t sigmask;

  bChassisMove = 0; /* disallow stowing and deploying */

  /* Register NDDS messages */
  cmdNddsConnect();

  /* Subscribe messages */
  cmdNddsSubscribe();

  /* Create timer and setup NDDS has been created */
  cmdSubscriberStart();


  while (1)
    {
      sigemptyset(&sigmask);
      sigsuspend(&sigmask);
      cmdNddsCallback();
    }
}

void cmdSubscriberStart(void)
{
  extern timer_t    cmdNdds_timer;
  struct sigaction action = {{NULL},0x0,0};
  struct itimerspec itime = {{0,0},{1,0}};
  struct sigevent evp = {0,{NULL},NULL};
  
  action.sa_handler = (VOIDFUNCPTR)cmdNullFunc;
  evp.sigev_signo = 29;
  /* Create the timer */
  if (timer_create(CLOCK_REALTIME, &evp, &cmdNdds_timer)==ERROR){
    logMsg("ERROR:Could not create cmdNdds timer\n",0,0,0,0,0,0);
  } else {
    /* Connect the cmdNdds callback to the timer */
    if (sigaction(29, &action, NULL) != OK) {
      logMsg("ERROR:Could not connect cmdNdds to timer\n",
	     0,0,0,0,0,0);
    } else {
      logMsg("Connected SIG_ALARM to cmdNdds timer\n", 1,2,3,4,5,6);
    }
  }

  /* Set the timer for typical rate */
  itime.it_interval.tv_sec  = (time_t)CMD_NDDS_PERIOD_SEC;
  itime.it_interval.tv_nsec = CMD_NDDS_PERIOD_NSEC;
  if (timer_settime(cmdNdds_timer,NULL,&itime,NULL)==ERROR){
    logMsg("ERROR:Could not set period for cmdNdds timer\n", 1,2,3,4,5,6);
  } else {
    logMsg("Set cmdNdds timer\n", 1,2,3,4,5,6);
  }
}

void cmdNullFunc (void)
{
  return;
}

void cmdSubscriberStop(void)
{
/*  taskSuspend(cmdConsumerPID);*/
  timer_cancel(cmdNdds_timer);
}

void cmdSubscriberDelete(void)
{
  int tid;

/*  taskDelete(cmdConsumerPID); */
  timer_delete(cmdNdds_timer);
  cmdNddsUnSubscribe();
  if ((tid = taskNameToId(TCMDNDDS_NAME)) != -1) taskDelete (tid);
}

void cmdNddsCallback ()
{
  NddsSubscriberPoll(cmdNddsSubscriber);
}

RTIBool cmdSubscriberCallback(NDDSRecvInfo *update)
{
  if (update->status == NDDS_FRESH_DATA)
    {
      switch ((rtCmd_t)update->callBackRtnParam)
	{
	  case RT_DRIVE : 
	    logMsg("rtDrive not implemented\n", 1, 2, 3, 4, 5, 6); 
	    put_rtDrive((rtDrive *) update->instance);
	    rtDrivePrint((rtDrive *) update->instance);
	    break;
	  case RT_SET_ACTUATOR : 
	    logMsg("rtSetActuator not implemented\n", 1, 2, 3, 4, 5, 6); 
	    put_rtSetActuator((rtSetActuator *) update->instance);
	    rtSetActuatorPrint((rtSetActuator *) update->instance);
	    break;
	  case RT_SET_BROADCAST_FREQ : 
	    put_rtSetBroadcastFreq((rtSetBroadcastFreq *) update->instance);
	    rtSetBroadcastFreqPrint((rtSetBroadcastFreq *) update->instance);
	    cmdRtSetBroadcastFreq((rtSetBroadcastFreq *) update->instance);
	    break;
	  case RT_SET_PARAM_FLOAT : 
	    logMsg("rtSetParamFloat not implemented\n", 1, 2, 3, 4, 5, 6);
	    put_rtSetParamFloat((rtSetParamFloat *) update->instance);
	    rtSetParamFloatPrint((rtSetParamFloat *) update->instance);
	    break;
	  case RT_SET_PARAM_INT : 
	    logMsg("rtSetParamInt not implemented\n", 1, 2, 3, 4, 5, 6);
	    put_rtSetParamInt((rtSetParamInt *) update->instance);
	    rtSetParamIntPrint((rtSetParamInt *) update->instance);
	    break;	
	  case RT_SET_POS_EST_PARAMS : 
	    logMsg("rtSetPosEstParams not implemented\n", 1, 2, 3, 4, 5, 6);
	    put_rtSetPosEstParams((rtSetPosEstParams *) update->instance);
	    rtSetPosEstParamsPrint((rtSetPosEstParams *) update->instance);
	    break;	
	  case RT_SET_SERVO_PARAMS : 
	    rtSetServoParamsPrint((rtSetServoParams *) update->instance);
	    put_rtSetServoParams((rtSetServoParams *) update->instance);
	    cmdRtSetServoParams((rtSetServoParams *) update->instance);
	    break;	
	  case RT_SIGNAL_CONDITION : 
	    rtSignalConditionPrint((rtSignalCondition *) update->instance);
	    put_rtSignalCondition((rtSignalCondition *) update->instance);
	    cmdRtSignalCondition ((rtSignalCondition *) update->instance);
	    break;	
	  case RT_CHASSIS_CONFIG : 
       	    rtChassisConfigPrint((rtChassisConfig *) update->instance);
	    put_rtChassisConfig((rtChassisConfig *) update->instance);
	    cmdRtChassisConfig ((rtChassisConfig *) update->instance);
	    break;	
  	  case RT_AMP_STATE:
	    put_rtAmpState((rtAmpState *) update->instance);
	    //	    rtAmpStatePrint((rtAmpState *) update->instance);
	    cmdRtAmpState((rtAmpState *) update->instance);
	    break;
	  case RT_CONTROL_STATE:
	    put_rtControlState((rtControlState *) update->instance);
	    cmdRtControlState((rtControlState *) update->instance);
	    break;
	  case RT_LASER : 
	    logMsg("rtLaser not implemented\n", 1, 2, 3, 4, 5, 6);
	    put_rtLaser ((rtLaser *) update->instance);
	    rtLaserPrint((rtLaser *) update->instance);
	    break;	
	  case RT_MOVE : 
	    put_move ((move *) update->instance);
	    cmdRtMove((move *) update->instance);
	    break;
	  default:
	    logMsg("received an unknown cmd message in the cmdSubscriber (type=%d)"
		   ".\n", (int)update->callBackRtnParam, 2,3,4,5,6);
	  }
    } else if (update->status == NDDS_NO_NEW_DATA ||
	       update->status == NDDS_NEVER_RECEIVED_DATA) {
      // nothing
    } else {
      printf ("Subscriber status=%d type=%s topic=%s\n", 
	      (int)update->status, update->publicationType, update->publicationTopic);
    }
  return RTI_TRUE;
}

void ccc(void) { cmdSubscriberCreate(); }
void ccs(void) { cmdSubscriberStart(); }
void cce(void) { cmdSubscriberStop(); }
void ccd(void) { cmdSubscriberDelete(); }

void cmdRtSetServoParams(rtSetServoParams *params)
{
  if (params->servoId <= MOTOR_STEER_R) // drivesys object
    { 
      Cdrive *motor = drivesys->GetDrivePtr(params->servoId);
      motor->m_pid.SetKp(params->gain[0]);
      motor->m_pid.SetKi(params->gain[1]);
      motor->m_pid.SetKd(params->gain[2]);
      motor->m_pid.SetILimit(params->integrationLimit);
      motor->m_pid.SetMaxPosErr(params->errorLimit);
    }
  else if (params->servoId <= MOTOR_POINT_ELEVATION)
    {
// MDW 6/8/99
#ifdef USE_POINT
      Cpoint *motor = pointsys->GetPointPtr(params->servoId);
      motor->m_pid.SetKp(params->gain[0]);
      motor->m_pid.SetKi(params->gain[1]);
      motor->m_pid.SetKd(params->gain[2]);
      motor->m_pid.SetILimit(params->integrationLimit);
      motor->m_pid.SetMaxPosErr(params->errorLimit);
#endif
    }
  else if (params->servoId == 10) // Wheel Motors
    {
      Cdrive *motor;
      int i;
      for (i=MOTOR_DRIVE_FL; i<=MOTOR_DRIVE_BR; i++)
	{
	  motor = drivesys->GetDrivePtr(i);
	  motor->m_pid.SetKp(params->gain[0]);
	  motor->m_pid.SetKi(params->gain[1]);
	  motor->m_pid.SetKd(params->gain[2]);
	  motor->m_pid.SetILimit(params->integrationLimit);
	  motor->m_pid.SetMaxPosErr(params->errorLimit);
	}
    }
  else if (params->servoId == 20) // Steering Motors
    {
      Cdrive *motor;
      int i;
      for (i=MOTOR_STEER_L; i<=MOTOR_STEER_R; i++)
	{
	  motor = drivesys->GetDrivePtr(i);
	  motor->m_pid.SetKp(params->gain[0]);
	  motor->m_pid.SetKi(params->gain[1]);
	  motor->m_pid.SetKd(params->gain[2]);
	  motor->m_pid.SetILimit(params->integrationLimit);
	  motor->m_pid.SetMaxPosErr(params->errorLimit);
	}
    }
}

void cmdRtMove(move *cmd)
{
  // the printf is now in the drivesys module in UpdateSteerin
/*  printf("radius: %f, trSpeed: %f, trDist: %f, point: %d, tuDist: %f, "
	 "tuSpeed: %f\n", cmd->radius, cmd->translateSpeed, cmd->translateDistance,
	 cmd->pointTurnFlag, cmd->turnDistance, cmd->turnSpeed);*/
//  movePrint(cmd);
  
}

void cmdRtSignalCondition (rtSignalCondition *cond)
{
  switch (cond->condition)
    {
      case MY_MIND_IS_GOING : logMsg("Take a break...\n", 1,2,3,4,5,6); break;
      case RESET_POS_EST : break;
      case RESET_KVH : break;
      case RESET_GPS : break;
      case REBOOT_NT : break;
      case REBOOT_RT : sysAuxClkDisable(); break;
      case REBOOT_LINUX : break;
      case SAFE_ROBOT : break;
      case SHUTDOWN_COLD : break;
      case SHUTDOWN_HOT : break;
      case PANIC_STOP : drivesys->ServosDisable(); break;
      case OH_SHIT : drivesys->ServosDisable(); break;
    }
}

void cmdRtChassisConfig (rtChassisConfig *config)
{
  switch (config->rtChassisConfigFlag)
    {
      case 5 : // STOWED
        logMsg ("cmdRtChassisConfig() stowing chassis!!\n", 1,2,3,4,5,6);
	if (bChassisMove)
	  drivesys->SetSteeringRadius(RADIUS_STOWED);
        break;
      case 2 : // DEPLOYED
        logMsg ("cmdRtChassisConfig() deploying chassis!!\n", 1,2,3,4,5,6);
	if (bChassisMove)
	  drivesys->SetSteeringRadius(RADIUS_DEPLOY);
        break;
      default : 
	logMsg ("cmdRtChassisConfig() ERROR!!! configuration flag=%d not "
		"implemented\n", config->rtChassisConfigFlag, 2,3,4,5,6);
        break;
    }
}

void cmdRtSetBroadcastFreq (rtSetBroadcastFreq *msg)
{
  rtSetBroadcastFreq2Struct Freq2;

  get_rtSetBroadcastFreq2 (&Freq2); /* get value of SEMID */
  Freq2.sourceId = msg->sourceId;
  Freq2.freq = msg->freq;
  put_rtSetBroadcastFreq2 (&Freq2); /* save values of sourceID and freq */
  semGive (Freq2.semSignal);
}

void chassisMoveAllow ()
{
  printf ("Allowing chassis configs from NDDS messages.\n");
  bChassisMove = 1; /* allow chassis changes */
}

void chassisMoveDisallow ()
{
  printf ("Disallowing chassis configs from NDDS messages.\n");
  bChassisMove = 0; /* disallow chassis changes */
}

void cmdRtControlState (rtControlState *msg)
{
  if(msg->rtCommand == 1) {
    // It's an actual command to change the robot's state.
    // Set driving mode
    logMsg("Changing to drive mode %d.\n", msg->rtDrivingMode, 2,3,4,5,6);
    drivesys->ChangeMode((DRIVING_MODE_t)msg->rtDrivingMode);
    
    // Set heartbeat and watchdog masks...
  }
}

void cmdRtAmpState (rtAmpState *msg)
{
  const int L_STEER_AMP_MASK = 0x20;
  const int R_STEER_AMP_MASK = 0x10;
  const int FL_WHEEL_AMP_MASK = 0x08;
  const int FR_WHEEL_AMP_MASK = 0x04;
  const int BL_WHEEL_AMP_MASK = 0x02;
  const int BR_WHEEL_AMP_MASK = 0x01;

  if(msg->rtCommand == 1) {
    // It's an actual command to change the robot's state.
    logMsg("Changing to amp mode 0x%x.\n", msg->rtAmpEnables, 2,3,4,5,6);

    // Set amp enables.
    if(msg->rtAmpEnables & L_STEER_AMP_MASK == L_STEER_AMP_MASK) {
      drivesys->pLeft->ChangeState(SERVOING);
    } else {
      drivesys->pLeft->ChangeState(INHIBITED);
    }
    if(msg->rtAmpEnables & R_STEER_AMP_MASK == R_STEER_AMP_MASK) {
      drivesys->pRight->ChangeState(SERVOING);
    } else {
      drivesys->pRight->ChangeState(INHIBITED);
    }
    if(msg->rtAmpEnables & FL_WHEEL_AMP_MASK == FL_WHEEL_AMP_MASK) {
      drivesys->pFL->ChangeState(SERVOING);
    } else {
      drivesys->pFL->ChangeState(INHIBITED);
    }
    if(msg->rtAmpEnables & FR_WHEEL_AMP_MASK == FR_WHEEL_AMP_MASK) {
      drivesys->pFR->ChangeState(SERVOING);
    } else {
      drivesys->pFR->ChangeState(INHIBITED);
    }
    if(msg->rtAmpEnables & BL_WHEEL_AMP_MASK == BL_WHEEL_AMP_MASK) {
      drivesys->pBL->ChangeState(SERVOING);
    } else {
      drivesys->pBL->ChangeState(INHIBITED);
    }
    if(msg->rtAmpEnables & BR_WHEEL_AMP_MASK == BR_WHEEL_AMP_MASK) {
      drivesys->pBR->ChangeState(SERVOING);
    } else {
      drivesys->pBR->ChangeState(INHIBITED);
    }
  }
}


