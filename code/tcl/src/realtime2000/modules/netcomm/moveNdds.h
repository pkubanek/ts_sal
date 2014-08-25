/* $Revision: 1.1.1.1 $ $Author: sib $ $Date: 1999/10/22 20:35:46 $ */
#ifndef INCmoveNdds_h
#define INCmoveNdds_h

/*
 * moveNdds.h
 * 
 * Mark Sibenac
 * 97-4-15
 * Atacama Desert Trek
 * Field Robotics Center
 *
 * This file creates and deals with the consumer commands that processes and
 * computers are sending to the real-time computer. These are specific for the
 * 040 which doesn't suck.
 *
 */

#include "netndds.h"
#include "sm_int.h"
#include "sm_pointers.h"

#ifdef __cplusplus
extern "C" {
#endif

  /*extern NDDSConsumer moveNddsConsumer;*/

#define TMOVENDDS_NAME    "tMoveNdds"
#define PRIORITY_MOVE_NDDS (75)

/* 10 Hz = 0 sec + 1e8 nsec period */
#define MOVE_NDDS_PERIOD_SEC        (0)
#define MOVE_NDDS_PERIOD_NSEC       ((long)(1e8))

#define MOVE_SUBSCRIBER_NAME "moveSubscriber"

#define MOVE_NAME "move"
#define RT_MOVE_NAME "rtMove"

#define EVENT_NAME       "event"
#define TIMER_EVENT_NAME "timerEvent"

#define MOVE_NDDS_DEADLINE 3.0f
#define MOVE_NDDS_MIN_SEPARATION 0.0f

void moveSubscriberCreate(void);
void moveSubscriberStart(void);
void moveSubscriberStop(void);
void moveSubscriberDelete(void);
int  moveSubscriberTask ();
RTIBool moveSubscriberCallback(NDDSRecvInfo *update);
RTIBool eventSubscriberCallback(NDDSRecvInfo *update);
void moveNddsSubscribe(void);
void moveNddsUnSubscribe(void);
void moveNddsCallback();
void moveNullFunc (void);

#ifdef __cplusplus
}
#endif

#endif /* INCmoveNdds_h */
