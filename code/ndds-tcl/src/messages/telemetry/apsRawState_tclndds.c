/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "apsRawState.h"
#include "apsRawState_tclndds.h"

int 
Tcl2Ndds_apsRawState (apsRawState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (apsRawState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for apsRawState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,apsRawState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->azimuthCnts);
  sscanf  (argv[count++], "%d", &nddsObj->elevCnts  );
  sscanf  (argv[count++], "%d", &nddsObj->elevCmd   );
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* apsRawStateStruct */


int 
Ndds2Tcl_apsRawState (apsRawState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->azimuthCnts);  newValue = Tcl_SetVar2 (interp, "this", "azimuthCnts", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->elevCnts  );  newValue = Tcl_SetVar2 (interp, "this", "elevCnts", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->elevCmd   );  newValue = Tcl_SetVar2 (interp, "this", "elevCmd", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* apsRawStateStruct */


