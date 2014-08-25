/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "arbInternalState.h"
#include "arbInternalState_tclndds.h"

int 
Tcl2Ndds_arbInternalState (arbInternalState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (arbInternalState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for arbInternalState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,arbInternalState_ArgCount);
    return (-1);
  }

  for (i=0; i<14; i++)
      sscanf(argv[count++],"%f",&(nddsObj->moduleSteers[i]));
  for (i=0; i<2; i++)
      sscanf(argv[count++],"%f",&(nddsObj->computedSteer[i]));
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* arbInternalStateStruct */


int 
Ndds2Tcl_arbInternalState (arbInternalState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  for (i=0; i<14; i++) {
    sprintf (tmpStr, "%f ", nddsObj->moduleSteers[i]);
    newValue = Tcl_SetVar2 (interp, "this", "moduleSteers", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<2; i++) {
    sprintf (tmpStr, "%f ", nddsObj->computedSteer[i]);
    newValue = Tcl_SetVar2 (interp, "this", "computedSteer", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* arbInternalStateStruct */


