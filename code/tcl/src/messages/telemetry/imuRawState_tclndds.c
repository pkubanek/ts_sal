/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "imuRawState.h"
#include "imuRawState_tclndds.h"

int 
Tcl2Ndds_imuRawState (imuRawState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (imuRawState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for imuRawState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,imuRawState_ArgCount);
    return (-1);
  }

  for (i=0; i<3; i++)
      sscanf(argv[count++],"%d",&(nddsObj->rotDotVolts[i]));
  for (i=0; i<3; i++)
      sscanf(argv[count++],"%d",&(nddsObj->transDotDotVolts[i]));
  sscanf  (argv[count++], "%d", &nddsObj->tempVolts );
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* imuRawStateStruct */


int 
Ndds2Tcl_imuRawState (imuRawState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  for (i=0; i<3; i++) {
    sprintf (tmpStr, "%d ", nddsObj->rotDotVolts[i]);
    newValue = Tcl_SetVar2 (interp, "this", "rotDotVolts", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<3; i++) {
    sprintf (tmpStr, "%d ", nddsObj->transDotDotVolts[i]);
    newValue = Tcl_SetVar2 (interp, "this", "transDotDotVolts", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->tempVolts );  newValue = Tcl_SetVar2 (interp, "this", "tempVolts", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* imuRawStateStruct */


