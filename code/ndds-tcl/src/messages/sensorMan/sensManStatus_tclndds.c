/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "sensManStatus.h"
#include "sensManStatus_tclndds.h"

int 
Tcl2Ndds_sensManStatus (sensManStatus nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (sensManStatus_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for sensManStatus.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,sensManStatus_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->sensorID  );
  sscanf  (argv[count++], "%d", &nddsObj->status    );
  sscanf  (argv[count++], "%d", &nddsObj->extendedStatus);
  sscanf  (argv[count++], "%f", &nddsObj->timeCost  );
  sscanf  (argv[count++], "%f", &nddsObj->powerCost );

  return (count);	/* # args used in this struct. */
} /* sensManStatusStruct */


int 
Ndds2Tcl_sensManStatus (sensManStatus nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->sensorID  );  newValue = Tcl_SetVar2 (interp, "this", "sensorID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->status    );  newValue = Tcl_SetVar2 (interp, "this", "status", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->extendedStatus);  newValue = Tcl_SetVar2 (interp, "this", "extendedStatus", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->timeCost  );  newValue = Tcl_SetVar2 (interp, "this", "timeCost", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->powerCost );  newValue = Tcl_SetVar2 (interp, "this", "powerCost", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* sensManStatusStruct */


