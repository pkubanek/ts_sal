/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "sciSequence.h"
#include "sciSequence_tclndds.h"

int 
Tcl2Ndds_sciSequence (sciSequence nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (sciSequence_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for sciSequence.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,sciSequence_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->camera    );
  sscanf  (argv[count++], "%d", &nddsObj->resolution);
  sscanf  (argv[count++], "%d", &nddsObj->x         );
  sscanf  (argv[count++], "%d", &nddsObj->y         );
  sscanf  (argv[count++], "%d", &nddsObj->width     );
  sscanf  (argv[count++], "%d", &nddsObj->height    );
  sscanf  (argv[count++], "%d", &nddsObj->count     );
  sscanf  (argv[count++], "%f", &nddsObj->delay     );

  return (count);	/* # args used in this struct. */
} /* sciSequenceStruct */


int 
Ndds2Tcl_sciSequence (sciSequence nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->camera    );  newValue = Tcl_SetVar2 (interp, "this", "camera", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->resolution);  newValue = Tcl_SetVar2 (interp, "this", "resolution", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->x         );  newValue = Tcl_SetVar2 (interp, "this", "x", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->y         );  newValue = Tcl_SetVar2 (interp, "this", "y", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->width     );  newValue = Tcl_SetVar2 (interp, "this", "width", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->height    );  newValue = Tcl_SetVar2 (interp, "this", "height", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->count     );  newValue = Tcl_SetVar2 (interp, "this", "count", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->delay     );  newValue = Tcl_SetVar2 (interp, "this", "delay", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* sciSequenceStruct */


