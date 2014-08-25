/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "navPath.h"
#include "navPath_tclndds.h"

int 
Tcl2Ndds_navPath (navPath nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (navPath_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for navPath.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,navPath_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->number    );
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%f",&(nddsObj->waypoint[i]));

  return (count);	/* # args used in this struct. */
} /* navPathStruct */


int 
Ndds2Tcl_navPath (navPath nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->number    );  newValue = Tcl_SetVar2 (interp, "this", "number", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%f ", nddsObj->waypoint[i]);
    newValue = Tcl_SetVar2 (interp, "this", "waypoint", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }

  return (1==1);	/* Return TRUE for now. */
} /* navPathStruct */


