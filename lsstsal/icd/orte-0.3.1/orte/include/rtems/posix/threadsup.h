/**
 * @file rtems/posix/threadsup.h
 */

/* threadsup.h
 *
 *  $Id: threadsup.h,v 1.25 2006/01/18 14:58:04 ralf Exp $
 */

#ifndef _RTEMS_POSIX_THREADSUP_H
#define _RTEMS_POSIX_THREADSUP_H

#include <sys/signal.h>
#include <rtems/score/coresem.h>
#include <rtems/score/tqdata.h>

typedef struct {
  pthread_attr_t          Attributes;
  int                     detachstate;
  Thread_queue_Control    Join_List;
  int                     schedpolicy;
  struct sched_param      schedparam;
  int                     ss_high_priority;
  Watchdog_Control        Sporadic_timer;

  sigset_t                signals_blocked;
  sigset_t                signals_pending;

  /*
   *  POSIX Cancelability
   */
  int                     cancelability_state;
  int                     cancelability_type;
  int                     cancelation_requested;
  Chain_Control           Cancellation_Handlers;

} POSIX_API_Control;

#endif
/* end of include file */
