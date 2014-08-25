/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtControlState.h"
#include "rtControlState_tclndds.h"

int 
Tcl2Ndds_rtControlState (rtControlState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtControlState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtControlState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtControlState_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->rtDrivingMode = (char)num;
  }
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->rtHeartbeatMask = (char)num;
  }
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->rtWatchdogMask = (char)num;
  }
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->rtCommand = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* rtControlStateStruct */


int 
Ndds2Tcl_rtControlState (rtControlState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->rtDrivingMode);  newValue = Tcl_SetVar2 (interp, "this", "rtDrivingMode", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rtHeartbeatMask);  newValue = Tcl_SetVar2 (interp, "this", "rtHeartbeatMask", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rtWatchdogMask);  newValue = Tcl_SetVar2 (interp, "this", "rtWatchdogMask", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rtCommand );  newValue = Tcl_SetVar2 (interp, "this", "rtCommand", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtControlStateStruct */


