/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "bodDerivedState.h"
#include "bodDerivedState_tclndds.h"

int 
Tcl2Ndds_bodDerivedState (bodDerivedState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (bodDerivedState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for bodDerivedState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,bodDerivedState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%u", &nddsObj->actLeftSteerDist);
  sscanf  (argv[count++], "%u", &nddsObj->actRightSteerDist);
  for (i=0; i<4; i++)
      sscanf(argv[count++],"%d",&(nddsObj->actWheelVelocity[i]));
  for (i=0; i<2; i++)
      sscanf(argv[count++],"%d",&(nddsObj->servoState[i]));
  for (i=0; i<2; i++)
      sscanf(argv[count++],"%d",&(nddsObj->brakeState[i]));
  for (i=0; i<4; i++)
      sscanf(argv[count++],"%d",&(nddsObj->actWheelCurrent[i]));
  sscanf  (argv[count++], "%d", &nddsObj->actLeftSteerCurrent);
  sscanf  (argv[count++], "%d", &nddsObj->actRightSteerCurrent);
  sscanf  (argv[count++], "%d", &nddsObj->bogieAngle);
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* bodDerivedStateStruct */


int 
Ndds2Tcl_bodDerivedState (bodDerivedState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%u", nddsObj->actLeftSteerDist);  newValue = Tcl_SetVar2 (interp, "this", "actLeftSteerDist", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->actRightSteerDist);  newValue = Tcl_SetVar2 (interp, "this", "actRightSteerDist", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<4; i++) {
    sprintf (tmpStr, "%d ", nddsObj->actWheelVelocity[i]);
    newValue = Tcl_SetVar2 (interp, "this", "actWheelVelocity", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<2; i++) {
    sprintf (tmpStr, "%d ", nddsObj->servoState[i]);
    newValue = Tcl_SetVar2 (interp, "this", "servoState", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<2; i++) {
    sprintf (tmpStr, "%d ", nddsObj->brakeState[i]);
    newValue = Tcl_SetVar2 (interp, "this", "brakeState", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<4; i++) {
    sprintf (tmpStr, "%d ", nddsObj->actWheelCurrent[i]);
    newValue = Tcl_SetVar2 (interp, "this", "actWheelCurrent", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->actLeftSteerCurrent);  newValue = Tcl_SetVar2 (interp, "this", "actLeftSteerCurrent", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->actRightSteerCurrent);  newValue = Tcl_SetVar2 (interp, "this", "actRightSteerCurrent", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->bogieAngle);  newValue = Tcl_SetVar2 (interp, "this", "bogieAngle", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* bodDerivedStateStruct */


