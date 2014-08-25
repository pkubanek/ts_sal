/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtSetParamInt.h"
#include "rtSetParamInt_tclndds.h"

int 
Tcl2Ndds_rtSetParamInt (rtSetParamInt nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtSetParamInt_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtSetParamInt.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtSetParamInt_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->paramId   );
  sscanf  (argv[count++], "%d", &nddsObj->value     );

  return (count);	/* # args used in this struct. */
} /* rtSetParamIntStruct */


int 
Ndds2Tcl_rtSetParamInt (rtSetParamInt nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->paramId   );  newValue = Tcl_SetVar2 (interp, "this", "paramId", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->value     );  newValue = Tcl_SetVar2 (interp, "this", "value", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtSetParamIntStruct */


