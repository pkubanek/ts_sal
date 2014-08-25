/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtDrive.h"
#include "rtDrive_tclndds.h"

int 
Tcl2Ndds_rtDrive (rtDrive nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtDrive_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtDrive.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtDrive_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%f", &nddsObj->leftSteerAngle);
  sscanf  (argv[count++], "%f", &nddsObj->rightSteerAngle);
  sscanf  (argv[count++], "%f", &nddsObj->speed     );

  return (count);	/* # args used in this struct. */
} /* rtDriveStruct */


int 
Ndds2Tcl_rtDrive (rtDrive nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%f", nddsObj->leftSteerAngle);  newValue = Tcl_SetVar2 (interp, "this", "leftSteerAngle", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->rightSteerAngle);  newValue = Tcl_SetVar2 (interp, "this", "rightSteerAngle", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->speed     );  newValue = Tcl_SetVar2 (interp, "this", "speed", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtDriveStruct */


