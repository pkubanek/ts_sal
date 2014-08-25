/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "navPlanStatus.h"
#include "navPlanStatus_tclndds.h"

int 
Tcl2Ndds_navPlanStatus (navPlanStatus nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (navPlanStatus_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for navPlanStatus.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,navPlanStatus_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->taskMode  );
  sscanf  (argv[count++], "%d", &nddsObj->status    );
  sscanf  (argv[count++], "%f", &nddsObj->timeCost  );
  sscanf  (argv[count++], "%f", &nddsObj->areaCovered);
  sscanf  (argv[count++], "%f", &nddsObj->energyGen );

  return (count);	/* # args used in this struct. */
} /* navPlanStatusStruct */


int 
Ndds2Tcl_navPlanStatus (navPlanStatus nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->taskMode  );  newValue = Tcl_SetVar2 (interp, "this", "taskMode", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->status    );  newValue = Tcl_SetVar2 (interp, "this", "status", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->timeCost  );  newValue = Tcl_SetVar2 (interp, "this", "timeCost", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->areaCovered);  newValue = Tcl_SetVar2 (interp, "this", "areaCovered", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->energyGen );  newValue = Tcl_SetVar2 (interp, "this", "energyGen", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* navPlanStatusStruct */


