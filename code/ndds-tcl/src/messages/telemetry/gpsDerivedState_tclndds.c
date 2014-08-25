/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "gpsDerivedState.h"
#include "gpsDerivedState_tclndds.h"

int 
Tcl2Ndds_gpsDerivedState (gpsDerivedState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (gpsDerivedState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for gpsDerivedState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,gpsDerivedState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%ld", &nddsObj->msecOfGPSWeek);
  sscanf  (argv[count++], "%d", &nddsObj->GPSWeek   );
  sscanf  (argv[count++], "%u", &nddsObj->numSVSTracked);
  sscanf  (argv[count++], "%u", &nddsObj->numSVSVisible);
  sscanf  (argv[count++], "%lf", &nddsObj->userDatumNorthOrX);
  sscanf  (argv[count++], "%lf", &nddsObj->userDatumEastOrY);
  sscanf  (argv[count++], "%lf", &nddsObj->userDatumUporZ);
  sscanf  (argv[count++], "%u", &nddsObj->velocityFlags);
  sscanf  (argv[count++], "%f", &nddsObj->horizVelocity);
  sscanf  (argv[count++], "%f", &nddsObj->heading   );
  sscanf  (argv[count++], "%f", &nddsObj->positionRMSError);
  sscanf  (argv[count++], "%lf", &nddsObj->positionDOP);
  sscanf  (argv[count++], "%f", &nddsObj->sigmaEast );
  sscanf  (argv[count++], "%f", &nddsObj->sigmaNorth);
  sscanf  (argv[count++], "%f", &nddsObj->eastNorthCovar);
  sscanf  (argv[count++], "%f", &nddsObj->sigmaUp   );
  sscanf  (argv[count++], "%f", &nddsObj->sigmaOrientation);
  sscanf  (argv[count++], "%f", &nddsObj->unitVariance);
  sscanf  (argv[count++], "%d", &nddsObj->numEpochs );
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* gpsDerivedStateStruct */


int 
Ndds2Tcl_gpsDerivedState (gpsDerivedState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%ld", nddsObj->msecOfGPSWeek);  newValue = Tcl_SetVar2 (interp, "this", "msecOfGPSWeek", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->GPSWeek   );  newValue = Tcl_SetVar2 (interp, "this", "GPSWeek", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->numSVSTracked);  newValue = Tcl_SetVar2 (interp, "this", "numSVSTracked", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->numSVSVisible);  newValue = Tcl_SetVar2 (interp, "this", "numSVSVisible", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->userDatumNorthOrX);  newValue = Tcl_SetVar2 (interp, "this", "userDatumNorthOrX", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->userDatumEastOrY);  newValue = Tcl_SetVar2 (interp, "this", "userDatumEastOrY", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->userDatumUporZ);  newValue = Tcl_SetVar2 (interp, "this", "userDatumUporZ", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->velocityFlags);  newValue = Tcl_SetVar2 (interp, "this", "velocityFlags", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->horizVelocity);  newValue = Tcl_SetVar2 (interp, "this", "horizVelocity", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->heading   );  newValue = Tcl_SetVar2 (interp, "this", "heading", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->positionRMSError);  newValue = Tcl_SetVar2 (interp, "this", "positionRMSError", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->positionDOP);  newValue = Tcl_SetVar2 (interp, "this", "positionDOP", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->sigmaEast );  newValue = Tcl_SetVar2 (interp, "this", "sigmaEast", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->sigmaNorth);  newValue = Tcl_SetVar2 (interp, "this", "sigmaNorth", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->eastNorthCovar);  newValue = Tcl_SetVar2 (interp, "this", "eastNorthCovar", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->sigmaUp   );  newValue = Tcl_SetVar2 (interp, "this", "sigmaUp", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->sigmaOrientation);  newValue = Tcl_SetVar2 (interp, "this", "sigmaOrientation", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->unitVariance);  newValue = Tcl_SetVar2 (interp, "this", "unitVariance", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->numEpochs );  newValue = Tcl_SetVar2 (interp, "this", "numEpochs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* gpsDerivedStateStruct */


