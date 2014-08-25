/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "kvhDerivedState.h"
#include "kvhDerivedState_tclndds.h"

int 
Tcl2Ndds_kvhDerivedState (kvhDerivedState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (kvhDerivedState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for kvhDerivedState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,kvhDerivedState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->pitch     );
  sscanf  (argv[count++], "%d", &nddsObj->roll      );
  sscanf  (argv[count++], "%d", &nddsObj->magneticAzimuth);
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* kvhDerivedStateStruct */


int 
Ndds2Tcl_kvhDerivedState (kvhDerivedState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->pitch     );  newValue = Tcl_SetVar2 (interp, "this", "pitch", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->roll      );  newValue = Tcl_SetVar2 (interp, "this", "roll", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->magneticAzimuth);  newValue = Tcl_SetVar2 (interp, "this", "magneticAzimuth", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* kvhDerivedStateStruct */


