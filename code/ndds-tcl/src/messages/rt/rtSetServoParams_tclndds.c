/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtSetServoParams.h"
#include "rtSetServoParams_tclndds.h"

int 
Tcl2Ndds_rtSetServoParams (rtSetServoParams nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtSetServoParams_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtSetServoParams.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtSetServoParams_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->servoId   );
  for (i=0; i<3; i++)
      sscanf(argv[count++],"%d",&(nddsObj->gain[i]));
  sscanf  (argv[count++], "%d", &nddsObj->integrationLimit);
  sscanf  (argv[count++], "%d", &nddsObj->errorLimit);

  return (count);	/* # args used in this struct. */
} /* rtSetServoParamsStruct */


int 
Ndds2Tcl_rtSetServoParams (rtSetServoParams nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->servoId   );  newValue = Tcl_SetVar2 (interp, "this", "servoId", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<3; i++) {
    sprintf (tmpStr, "%d ", nddsObj->gain[i]);
    newValue = Tcl_SetVar2 (interp, "this", "gain", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->integrationLimit);  newValue = Tcl_SetVar2 (interp, "this", "integrationLimit", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->errorLimit);  newValue = Tcl_SetVar2 (interp, "this", "errorLimit", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtSetServoParamsStruct */


