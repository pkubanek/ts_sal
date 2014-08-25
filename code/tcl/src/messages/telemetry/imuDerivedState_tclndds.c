/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "imuDerivedState.h"
#include "imuDerivedState_tclndds.h"

int 
Tcl2Ndds_imuDerivedState (imuDerivedState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (imuDerivedState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for imuDerivedState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,imuDerivedState_ArgCount);
    return (-1);
  }

  for (i=0; i<3; i++)
      sscanf(argv[count++],"%f",&(nddsObj->rotDot[i]));
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* imuDerivedStateStruct */


int 
Ndds2Tcl_imuDerivedState (imuDerivedState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  for (i=0; i<3; i++) {
    sprintf (tmpStr, "%f ", nddsObj->rotDot[i]);
    newValue = Tcl_SetVar2 (interp, "this", "rotDot", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* imuDerivedStateStruct */


