/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtAmpState.h"
#include "rtAmpState_tclndds.h"

int 
Tcl2Ndds_rtAmpState (rtAmpState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtAmpState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtAmpState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtAmpState_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->rtAmpEnables = (char)num;
  }
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->rtAmpFaults = (char)num;
  }
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->rtCommand = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* rtAmpStateStruct */


int 
Ndds2Tcl_rtAmpState (rtAmpState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->rtAmpEnables);  newValue = Tcl_SetVar2 (interp, "this", "rtAmpEnables", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rtAmpFaults);  newValue = Tcl_SetVar2 (interp, "this", "rtAmpFaults", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rtCommand );  newValue = Tcl_SetVar2 (interp, "this", "rtCommand", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtAmpStateStruct */


