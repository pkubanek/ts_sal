/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "sciPanTilt.h"
#include "sciPanTilt_tclndds.h"

int 
Tcl2Ndds_sciPanTilt (sciPanTilt nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (sciPanTilt_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for sciPanTilt.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,sciPanTilt_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%f", &nddsObj->pan       );
  sscanf  (argv[count++], "%f", &nddsObj->tilt      );
  sscanf  (argv[count++], "%d", &nddsObj->posMode   );

  return (count);	/* # args used in this struct. */
} /* sciPanTiltStruct */


int 
Ndds2Tcl_sciPanTilt (sciPanTilt nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%f", nddsObj->pan       );  newValue = Tcl_SetVar2 (interp, "this", "pan", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->tilt      );  newValue = Tcl_SetVar2 (interp, "this", "tilt", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->posMode   );  newValue = Tcl_SetVar2 (interp, "this", "posMode", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* sciPanTiltStruct */


