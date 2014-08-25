/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "sciSnap.h"
#include "sciSnap_tclndds.h"

int 
Tcl2Ndds_sciSnap (sciSnap nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (sciSnap_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for sciSnap.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,sciSnap_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->camera    );
  sscanf  (argv[count++], "%d", &nddsObj->resolution);
  sscanf  (argv[count++], "%d", &nddsObj->x         );
  sscanf  (argv[count++], "%d", &nddsObj->y         );
  sscanf  (argv[count++], "%d", &nddsObj->width     );
  sscanf  (argv[count++], "%d", &nddsObj->height    );

  return (count);	/* # args used in this struct. */
} /* sciSnapStruct */


int 
Ndds2Tcl_sciSnap (sciSnap nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->camera    );  newValue = Tcl_SetVar2 (interp, "this", "camera", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->resolution);  newValue = Tcl_SetVar2 (interp, "this", "resolution", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->x         );  newValue = Tcl_SetVar2 (interp, "this", "x", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->y         );  newValue = Tcl_SetVar2 (interp, "this", "y", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->width     );  newValue = Tcl_SetVar2 (interp, "this", "width", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->height    );  newValue = Tcl_SetVar2 (interp, "this", "height", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* sciSnapStruct */


