/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtSignalCondition.h"
#include "rtSignalCondition_tclndds.h"

int 
Tcl2Ndds_rtSignalCondition (rtSignalCondition nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtSignalCondition_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtSignalCondition.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtSignalCondition_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->condition );

  return (count);	/* # args used in this struct. */
} /* rtSignalConditionStruct */


int 
Ndds2Tcl_rtSignalCondition (rtSignalCondition nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->condition );  newValue = Tcl_SetVar2 (interp, "this", "condition", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtSignalConditionStruct */


