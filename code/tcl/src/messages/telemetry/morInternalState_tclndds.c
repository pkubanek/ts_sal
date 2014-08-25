/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "morInternalState.h"
#include "morInternalState_tclndds.h"

int 
Tcl2Ndds_morInternalState (morInternalState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (morInternalState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for morInternalState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,morInternalState_ArgCount);
    return (-1);
  }

  for (i=0; i<2; i++)
      sscanf(argv[count++],"%f",&(nddsObj->morphinSteer[i]));
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* morInternalStateStruct */


int 
Ndds2Tcl_morInternalState (morInternalState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  for (i=0; i<2; i++) {
    sprintf (tmpStr, "%f ", nddsObj->morphinSteer[i]);
    newValue = Tcl_SetVar2 (interp, "this", "morphinSteer", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* morInternalStateStruct */


