
/*
 * uibNdds.c
 *
 * Listens to Ndds and passes info to the "Switch."
 *
 * $Source: /afs/cs/project/lri-7/Master/src/nav/uiBridge/uibNdds.c,v $
 * $Revision: 1.1.1.1 $
 * $Date: 1997/06/26 03:43:56 $
 * $Author: jl $
 *
 * $Log: uibNdds.c,v $
 * Revision 1.1.1.1  1997/06/26 03:43:56  jl
 * Interface between UI/NDDS and Nav/TCA
 *
 *
 */


#include "commonDefs.h"
#include "commonTypes.h"
#include "logging.h"

#include "tca/devUtils.h"
#include "tca/stdinDev.h"

#include "NDDS.h"
#include "nomadNddsDomain.h"
#include "move.h"
#include "navEnable.h"
#include "rtSignalCondition.h"
#include "navHeading.h"

#include "nomadNddsMessages.h"

/* This should probably not be hardwired  */
#define NDDS_POLL_PERIOD 200    /* msecs. */

DECLARE_NDDS();
/*DECLARE_NDDS_OUTPUT(NAVUI_ARCS, ArbiterArcs);*/
DECLARE_NDDS_INPUT(UINAV_MOVE, uiMoveCmd);
DECLARE_NDDS_INPUT(UINAV_HEADING, uiHeadingCmd);
DECLARE_NDDS_INPUT(UIALL_DRASTIC, uiDrasticCmd);
DECLARE_NDDS_INPUT(UIALL_NAVENABLE, uiEnable);

DEV_PTR ndds_dev = NULL;
int ndds_inited = 0;

void init_NddsVars(void)
{

}


static void ProcessNdds(Pointer callback_data, Pointer client_data)
{
  NDDS_INPUT();
  /*  NDDS_OUTPUT(NAVUI_ARCS); */
}

  
void uiBridge_initNdds(void)
{
  struct timeval poll_period;
  
  poll_period.tv_usec = (NDDS_POLL_PERIOD % 1000) * 1000;
  poll_period.tv_sec = (NDDS_POLL_PERIOD / 1000);

  if (!ndds_inited) {
    init_NddsVars();

    INIT_NDDS();

    /*  INIT_NDDS_OUTPUT(NAVUI_ARCS, ArbiterArcs);*/
    INIT_NDDS_INPUT(UINAV_MOVE, uiMoveCmd);
    INIT_NDDS_INPUT(UINAV_HEADING, uiHeadingCmd);
    INIT_NDDS_INPUT(UIALL_DRASTIC, uiDrasticCmd);
    INIT_NDDS_INPUT(UIALL_NAVENABLE, uiEnable);

    ndds_dev = devCreateDev("ui-ndds", DEV_LISTENING, NOT_LISTENING, NULL);
    /* Here we should do error checking, but I'd have to go looking
     * through teh devUtils sources right now to find out what the return
     * values are, and it is not doe in the older parts of the system
     * anyway -- e.g CTR (jl)
     */
    /* Why bother connecting? */
    devConnectDev(ndds_dev, 0);
    ndds_inited = 1;
  }  

  devStartPolling(ndds_dev, &poll_period, ProcessNdds, NULL);

}
   

void uiBridge_finNdds(void)
{
  devStopPolling(ndds_dev);
}  



NDDS_HANDLERS_BEGIN

HANDLER_BEGIN(UINAV_MOVE, newUiMove) {
  ProcessUserMove(newUiMove);
}
HANDLER_END

HANDLER_BEGIN(UINAV_HEADING, newUiHeading) {
  ProcessUserHeading(newUiHeading);
}
HANDLER_END

HANDLER_BEGIN(UIALL_DRASTIC, signal) {
  if (signal->condition == 10) { /* 10 == PANIC_STOP */
    NavStop();
    send_emergency_stop();
  }
  else {
    NavContinue();
    send_emergency_resume();
  }
}
HANDLER_END

HANDLER_BEGIN(UIALL_NAVENABLE, status) {
  if (status->navEnableFlag) {
    if (!NavEnabledP()) {
      NavContinue();
    }
  }
  else {
    if (NavEnabledP()) {
      NavStop();
    }
  }
}
HANDLER_END

NDDS_HANDLERS_END

