/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "bodRawState.h"
#include "bodRawState_tclndds.h"

int 
Tcl2Ndds_bodRawState (bodRawState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (bodRawState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for bodRawState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,bodRawState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->actLeftSteerCnts);
  sscanf  (argv[count++], "%d", &nddsObj->cmdLeftSteerCnts);
  sscanf  (argv[count++], "%d", &nddsObj->actRightSteerCnts);
  sscanf  (argv[count++], "%d", &nddsObj->cmdRightSteerCnts);
  for (i=0; i<4; i++)
      sscanf(argv[count++],"%d",&(nddsObj->wheelCnts[i]));
  for (i=0; i<4; i++)
      sscanf(argv[count++],"%d",&(nddsObj->actWheelVelocity[i]));
  for (i=0; i<4; i++)
      sscanf(argv[count++],"%d",&(nddsObj->cmdWheelVelocity[i]));
  for (i=0; i<4; i++)
      sscanf(argv[count++],"%d",&(nddsObj->actWheelCurrents[i]));
  for (i=0; i<4; i++)
      sscanf(argv[count++],"%d",&(nddsObj->cmdWheelCurrents[i]));
  sscanf  (argv[count++], "%d", &nddsObj->actRightSteerCurrent);
  sscanf  (argv[count++], "%d", &nddsObj->cmdRightSteerCurrent);
  sscanf  (argv[count++], "%d", &nddsObj->actLeftSteerCurrent);
  sscanf  (argv[count++], "%d", &nddsObj->cmdLeftSteerCurrent);
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* bodRawStateStruct */


int 
Ndds2Tcl_bodRawState (bodRawState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->actLeftSteerCnts);  newValue = Tcl_SetVar2 (interp, "this", "actLeftSteerCnts", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->cmdLeftSteerCnts);  newValue = Tcl_SetVar2 (interp, "this", "cmdLeftSteerCnts", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->actRightSteerCnts);  newValue = Tcl_SetVar2 (interp, "this", "actRightSteerCnts", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->cmdRightSteerCnts);  newValue = Tcl_SetVar2 (interp, "this", "cmdRightSteerCnts", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<4; i++) {
    sprintf (tmpStr, "%d ", nddsObj->wheelCnts[i]);
    newValue = Tcl_SetVar2 (interp, "this", "wheelCnts", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<4; i++) {
    sprintf (tmpStr, "%d ", nddsObj->actWheelVelocity[i]);
    newValue = Tcl_SetVar2 (interp, "this", "actWheelVelocity", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<4; i++) {
    sprintf (tmpStr, "%d ", nddsObj->cmdWheelVelocity[i]);
    newValue = Tcl_SetVar2 (interp, "this", "cmdWheelVelocity", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<4; i++) {
    sprintf (tmpStr, "%d ", nddsObj->actWheelCurrents[i]);
    newValue = Tcl_SetVar2 (interp, "this", "actWheelCurrents", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<4; i++) {
    sprintf (tmpStr, "%d ", nddsObj->cmdWheelCurrents[i]);
    newValue = Tcl_SetVar2 (interp, "this", "cmdWheelCurrents", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->actRightSteerCurrent);  newValue = Tcl_SetVar2 (interp, "this", "actRightSteerCurrent", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->cmdRightSteerCurrent);  newValue = Tcl_SetVar2 (interp, "this", "cmdRightSteerCurrent", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->actLeftSteerCurrent);  newValue = Tcl_SetVar2 (interp, "this", "actLeftSteerCurrent", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->cmdLeftSteerCurrent);  newValue = Tcl_SetVar2 (interp, "this", "cmdLeftSteerCurrent", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* bodRawStateStruct */


