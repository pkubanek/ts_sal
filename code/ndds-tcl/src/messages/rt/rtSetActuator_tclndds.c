/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtSetActuator.h"
#include "rtSetActuator_tclndds.h"

int 
Tcl2Ndds_rtSetActuator (rtSetActuator nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtSetActuator_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtSetActuator.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtSetActuator_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->actuatorId);
  sscanf  (argv[count++], "%f", &nddsObj->position  );
  sscanf  (argv[count++], "%f", &nddsObj->velocity  );
  sscanf  (argv[count++], "%f", &nddsObj->accel     );

  return (count);	/* # args used in this struct. */
} /* rtSetActuatorStruct */


int 
Ndds2Tcl_rtSetActuator (rtSetActuator nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->actuatorId);  newValue = Tcl_SetVar2 (interp, "this", "actuatorId", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->position  );  newValue = Tcl_SetVar2 (interp, "this", "position", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->velocity  );  newValue = Tcl_SetVar2 (interp, "this", "velocity", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->accel     );  newValue = Tcl_SetVar2 (interp, "this", "accel", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtSetActuatorStruct */


