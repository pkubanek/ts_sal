/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "navSettings.h"
#include "navSettings_tclndds.h"

int 
Tcl2Ndds_navSettings (navSettings nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (navSettings_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for navSettings.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,navSettings_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->data      );
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->command = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* navSettingsStruct */


int 
Ndds2Tcl_navSettings (navSettings nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->data      );  newValue = Tcl_SetVar2 (interp, "this", "data", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->command   );  newValue = Tcl_SetVar2 (interp, "this", "command", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* navSettingsStruct */


