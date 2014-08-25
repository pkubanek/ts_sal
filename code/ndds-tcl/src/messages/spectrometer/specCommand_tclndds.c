/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "specCommand.h"
#include "specCommand_tclndds.h"

int 
Tcl2Ndds_specCommand (specCommand nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (specCommand_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for specCommand.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,specCommand_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->commandType);
  sscanf  (argv[count++], "%d", &nddsObj->targetID  );

  return (count);	/* # args used in this struct. */
} /* specCommandStruct */


int 
Ndds2Tcl_specCommand (specCommand nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->commandType);  newValue = Tcl_SetVar2 (interp, "this", "commandType", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* specCommandStruct */


