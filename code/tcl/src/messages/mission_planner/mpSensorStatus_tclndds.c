/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "mpSensorStatus.h"
#include "mpSensorStatus_tclndds.h"

int 
Tcl2Ndds_mpSensorStatus (mpSensorStatus nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (mpSensorStatus_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for mpSensorStatus.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,mpSensorStatus_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->sensorID  );
  sscanf  (argv[count++], "%d", &nddsObj->sensorStatus);
  sscanf  (argv[count++], "%d", &nddsObj->extendedSensorStatus);
  sscanf  (argv[count++], "%f", &nddsObj->timeCost  );
  sscanf  (argv[count++], "%f", &nddsObj->powerCost );

  return (count);	/* # args used in this struct. */
} /* mpSensorStatusStruct */


int 
Ndds2Tcl_mpSensorStatus (mpSensorStatus nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->sensorID  );  newValue = Tcl_SetVar2 (interp, "this", "sensorID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->sensorStatus);  newValue = Tcl_SetVar2 (interp, "this", "sensorStatus", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->extendedSensorStatus);  newValue = Tcl_SetVar2 (interp, "this", "extendedSensorStatus", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->timeCost  );  newValue = Tcl_SetVar2 (interp, "this", "timeCost", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->powerCost );  newValue = Tcl_SetVar2 (interp, "this", "powerCost", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* mpSensorStatusStruct */


