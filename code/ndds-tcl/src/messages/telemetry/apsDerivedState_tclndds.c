/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "apsDerivedState.h"
#include "apsDerivedState_tclndds.h"

int 
Tcl2Ndds_apsDerivedState (apsDerivedState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (apsDerivedState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for apsDerivedState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,apsDerivedState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->azimuth   );
  sscanf  (argv[count++], "%d", &nddsObj->elevation );
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* apsDerivedStateStruct */


int 
Ndds2Tcl_apsDerivedState (apsDerivedState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->azimuth   );  newValue = Tcl_SetVar2 (interp, "this", "azimuth", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->elevation );  newValue = Tcl_SetVar2 (interp, "this", "elevation", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* apsDerivedStateStruct */


