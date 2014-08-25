/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "classifierCommand.h"
#include "classifierCommand_tclndds.h"

int 
Tcl2Ndds_classifierCommand (classifierCommand nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (classifierCommand_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for classifierCommand.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,classifierCommand_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->targetID  );
  sscanf  (argv[count++], "%d", &nddsObj->dataType  );

  return (count);	/* # args used in this struct. */
} /* classifierCommandStruct */


int 
Ndds2Tcl_classifierCommand (classifierCommand nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->dataType  );  newValue = Tcl_SetVar2 (interp, "this", "dataType", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* classifierCommandStruct */


