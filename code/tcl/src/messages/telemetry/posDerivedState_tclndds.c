/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "posDerivedState.h"
#include "posDerivedState_tclndds.h"

int 
Tcl2Ndds_posDerivedState (posDerivedState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (posDerivedState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for posDerivedState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,posDerivedState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->posNorth  );
  sscanf  (argv[count++], "%d", &nddsObj->posWest   );
  sscanf  (argv[count++], "%d", &nddsObj->posUp     );
  sscanf  (argv[count++], "%d", &nddsObj->rotZ      );
  sscanf  (argv[count++], "%d", &nddsObj->rotY      );
  sscanf  (argv[count++], "%d", &nddsObj->rotX      );
  sscanf  (argv[count++], "%d", &nddsObj->posNorthDot);
  sscanf  (argv[count++], "%d", &nddsObj->posWestDot);
  sscanf  (argv[count++], "%d", &nddsObj->deltaUpDot);
  sscanf  (argv[count++], "%d", &nddsObj->rotZDot   );
  sscanf  (argv[count++], "%d", &nddsObj->rotYDot   );
  sscanf  (argv[count++], "%d", &nddsObj->rotXDot   );
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* posDerivedStateStruct */


int 
Ndds2Tcl_posDerivedState (posDerivedState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->posNorth  );  newValue = Tcl_SetVar2 (interp, "this", "posNorth", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->posWest   );  newValue = Tcl_SetVar2 (interp, "this", "posWest", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->posUp     );  newValue = Tcl_SetVar2 (interp, "this", "posUp", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rotZ      );  newValue = Tcl_SetVar2 (interp, "this", "rotZ", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rotY      );  newValue = Tcl_SetVar2 (interp, "this", "rotY", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rotX      );  newValue = Tcl_SetVar2 (interp, "this", "rotX", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->posNorthDot);  newValue = Tcl_SetVar2 (interp, "this", "posNorthDot", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->posWestDot);  newValue = Tcl_SetVar2 (interp, "this", "posWestDot", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->deltaUpDot);  newValue = Tcl_SetVar2 (interp, "this", "deltaUpDot", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rotZDot   );  newValue = Tcl_SetVar2 (interp, "this", "rotZDot", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rotYDot   );  newValue = Tcl_SetVar2 (interp, "this", "rotYDot", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rotXDot   );  newValue = Tcl_SetVar2 (interp, "this", "rotXDot", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* posDerivedStateStruct */


