/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "move.h"
#include "move_tclndds.h"

int 
Tcl2Ndds_move (move nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (move_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for move.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,move_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%lf", &nddsObj->radius    );
  sscanf  (argv[count++], "%d", &nddsObj->pointTurnFlag);
  sscanf  (argv[count++], "%lf", &nddsObj->turnSpeed );
  sscanf  (argv[count++], "%lf", &nddsObj->turnDistance);
  sscanf  (argv[count++], "%lf", &nddsObj->translateSpeed);
  sscanf  (argv[count++], "%lf", &nddsObj->translateDistance);

  return (count);	/* # args used in this struct. */
} /* moveStruct */


int 
Ndds2Tcl_move (move nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%lf", nddsObj->radius    );  newValue = Tcl_SetVar2 (interp, "this", "radius", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->pointTurnFlag);  newValue = Tcl_SetVar2 (interp, "this", "pointTurnFlag", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->turnSpeed );  newValue = Tcl_SetVar2 (interp, "this", "turnSpeed", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->turnDistance);  newValue = Tcl_SetVar2 (interp, "this", "turnDistance", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->translateSpeed);  newValue = Tcl_SetVar2 (interp, "this", "translateSpeed", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->translateDistance);  newValue = Tcl_SetVar2 (interp, "this", "translateDistance", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* moveStruct */


