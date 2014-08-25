/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtSetParamFloat.h"
#include "rtSetParamFloat_tclndds.h"

int 
Tcl2Ndds_rtSetParamFloat (rtSetParamFloat nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtSetParamFloat_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtSetParamFloat.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtSetParamFloat_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->paramId   );
  sscanf  (argv[count++], "%f", &nddsObj->value     );

  return (count);	/* # args used in this struct. */
} /* rtSetParamFloatStruct */


int 
Ndds2Tcl_rtSetParamFloat (rtSetParamFloat nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->paramId   );  newValue = Tcl_SetVar2 (interp, "this", "paramId", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->value     );  newValue = Tcl_SetVar2 (interp, "this", "value", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtSetParamFloatStruct */


