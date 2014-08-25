/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "epsDerivedState.h"
#include "epsDerivedState_tclndds.h"

int 
Tcl2Ndds_epsDerivedState (epsDerivedState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (epsDerivedState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for epsDerivedState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,epsDerivedState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%u", &nddsObj->genFuel   );
  sscanf  (argv[count++], "%u", &nddsObj->upsCharge );
  sscanf  (argv[count++], "%ld", &nddsObj->upsLastTrigger);
  sscanf  (argv[count++], "%ld", &nddsObj->upsStateMask);
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* epsDerivedStateStruct */


int 
Ndds2Tcl_epsDerivedState (epsDerivedState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%u", nddsObj->genFuel   );  newValue = Tcl_SetVar2 (interp, "this", "genFuel", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->upsCharge );  newValue = Tcl_SetVar2 (interp, "this", "upsCharge", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%ld", nddsObj->upsLastTrigger);  newValue = Tcl_SetVar2 (interp, "this", "upsLastTrigger", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%ld", nddsObj->upsStateMask);  newValue = Tcl_SetVar2 (interp, "this", "upsStateMask", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* epsDerivedStateStruct */


