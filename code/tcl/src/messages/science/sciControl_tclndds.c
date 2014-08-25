/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "sciControl.h"
#include "sciControl_tclndds.h"

int 
Tcl2Ndds_sciControl (sciControl nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (sciControl_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for sciControl.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,sciControl_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->camera    );
  sscanf  (argv[count++], "%d", &nddsObj->delay     );
  strcpy  (nddsObj->buttons    , argv[count++]);

  return (count);	/* # args used in this struct. */
} /* sciControlStruct */


int 
Ndds2Tcl_sciControl (sciControl nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->camera    );  newValue = Tcl_SetVar2 (interp, "this", "camera", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->delay     );  newValue = Tcl_SetVar2 (interp, "this", "delay", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<16; i++) {
    sprintf (tmpStr, "%d ", nddsObj->buttons[i]);
    newValue = Tcl_SetVar2 (interp, "this", "buttons", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }

  return (1==1);	/* Return TRUE for now. */
} /* sciControlStruct */


