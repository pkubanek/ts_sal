/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "mpNavPlannerStatus.h"
#include "mpNavPlannerStatus_tclndds.h"

int 
Tcl2Ndds_mpNavPlannerStatus (mpNavPlannerStatus nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (mpNavPlannerStatus_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for mpNavPlannerStatus.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,mpNavPlannerStatus_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->taskMode  );
  sscanf  (argv[count++], "%d", &nddsObj->navPlannerStatus);
  sscanf  (argv[count++], "%f", &nddsObj->timeCost  );
  sscanf  (argv[count++], "%f", &nddsObj->areaCovered);
  sscanf  (argv[count++], "%f", &nddsObj->energyGen );

  return (count);	/* # args used in this struct. */
} /* mpNavPlannerStatusStruct */


int 
Ndds2Tcl_mpNavPlannerStatus (mpNavPlannerStatus nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->taskMode  );  newValue = Tcl_SetVar2 (interp, "this", "taskMode", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->navPlannerStatus);  newValue = Tcl_SetVar2 (interp, "this", "navPlannerStatus", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->timeCost  );  newValue = Tcl_SetVar2 (interp, "this", "timeCost", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->areaCovered);  newValue = Tcl_SetVar2 (interp, "this", "areaCovered", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->energyGen );  newValue = Tcl_SetVar2 (interp, "this", "energyGen", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* mpNavPlannerStatusStruct */


