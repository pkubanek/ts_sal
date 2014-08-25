/* $Revision: 1.1.1.1 $ $Author: sib $ $Date: 1999/10/22 20:35:46 $ */
#ifndef INCcmdNdds_h
#define INCcmdNdds_h

/*
 * cmdNdds.h
 * 
 * Mark Sibenac
 * 97-4-15
 * Atacama Desert Trek
 * Field Robotics Center
 *
 * This file creates and deals with the subscriber commands that processes and
 * computers are sending to the real-time computer. These are specific for the
 * 030 which is running the servo code.
 *
 */

#include "netndds.h"
#include "sm_pointers.h"

#ifdef __cplusplus
extern "C" {
#endif

  /*extern NDDSSubscriber cmdNddsSubscriber;*/

/* 2 Hz = 0 sec + 5e8 nsec period *
#define CMD_NDDS_PERIOD_SEC        (0)
#define CMD_NDDS_PERIOD_NSEC       (long(5e8))*/

/* 10 Hz = 0 sec + 1e8 nsec period */
#define CMD_NDDS_PERIOD_SEC        (0)
#define CMD_NDDS_PERIOD_NSEC       (long(1e8))

#define CMD_NDDS_DEADLINE 1000.0f
#define CMD_NDDS_MIN_SEPARATION 0.5f

#define CMD_NAME "cmdSubscriber"
/*#define MOVE_SUBSCRIBER_NAME "moveSubscriber"*/

typedef enum {RT_DRIVE, RT_SET_ACTUATOR, RT_SET_BROADCAST_FREQ,
	      RT_SET_PARAM_FLOAT, RT_SET_PARAM_INT, RT_SET_POS_EST_PARAMS,
	      RT_SET_SERVO_PARAMS, RT_SIGNAL_CONDITION, RT_MOVE,
	      RT_CHASSIS_CONFIG, RT_LASER, RT_AMP_STATE, RT_CONTROL_STATE} rtCmd_t;

void cmdSubscriberCreate(void);
void cmdSubscriberStart(void);
void cmdSubscriberStop(void);
void cmdSubscriberDelete(void);
int  cmdSubscriberTask ();
/* MDW: Changed for NDDS upgrade work I started on 6/7/99 */
RTIBool cmdSubscriberCallback(NDDSRecvInfo *issue);
/*NDDSObjectInstance cmdSubscriberCallback(NDDSUpdateInfo update); */
/*NDDSObjectInstance moveSubscriberCallback(NDDSUpdateInfo update);*/
void cmdNddsSubscribe(void);
void cmdNddsUnSubscribe(void);
void cmdNddsCallback();
void cmdNullFunc (void);

void ccc(void);
void ccs(void);
void cce(void);
void ccd(void);

void cmdRtSetServoParams   (rtSetServoParams *params);
void cmdRtMove             (move *cmd);
void cmdRtSignalCondition  (rtSignalCondition *cond);
void cmdRtChassisConfig    (rtChassisConfig *config);
void cmdRtSetBroadcastFreq (rtSetBroadcastFreq *msg);
void cmdRtAmpState         (rtAmpState *msg);
void cmdRtControlState     (rtControlState *msg);

void chassisMoveAllow ();
void chassisMoveDisallow ();

#ifdef __cplusplus
}
#endif

#endif /* INCcmdNdds_h */



