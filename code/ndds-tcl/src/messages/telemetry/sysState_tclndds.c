/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "sysState.h"
#include "sysState_tclndds.h"

int 
Tcl2Ndds_sysState (sysState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (sysState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for sysState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,sysState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%u", &nddsObj->sysStateFlag);
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* sysStateStruct */


int 
Ndds2Tcl_sysState (sysState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%u", nddsObj->sysStateFlag);  newValue = Tcl_SetVar2 (interp, "this", "sysStateFlag", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* sysStateStruct */


