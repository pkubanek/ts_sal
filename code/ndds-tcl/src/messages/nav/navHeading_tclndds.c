/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "navHeading.h"
#include "navHeading_tclndds.h"

int 
Tcl2Ndds_navHeading (navHeading nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (navHeading_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for navHeading.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,navHeading_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%f", &nddsObj->heading   );
  sscanf  (argv[count++], "%f", &nddsObj->range     );
  sscanf  (argv[count++], "%f", &nddsObj->speed     );

  return (count);	/* # args used in this struct. */
} /* navHeadingStruct */


int 
Ndds2Tcl_navHeading (navHeading nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%f", nddsObj->heading   );  newValue = Tcl_SetVar2 (interp, "this", "heading", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->range     );  newValue = Tcl_SetVar2 (interp, "this", "range", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->speed     );  newValue = Tcl_SetVar2 (interp, "this", "speed", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* navHeadingStruct */


