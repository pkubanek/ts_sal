/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "sensManRequest.h"
#include "sensManRequest_tclndds.h"

int 
Tcl2Ndds_sensManRequest (sensManRequest nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (sensManRequest_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for sensManRequest.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,sensManRequest_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->mode      );
  sscanf  (argv[count++], "%d", &nddsObj->sensorID  );
  sscanf  (argv[count++], "%d", &nddsObj->targetID  );

  return (count);	/* # args used in this struct. */
} /* sensManRequestStruct */


int 
Ndds2Tcl_sensManRequest (sensManRequest nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->mode      );  newValue = Tcl_SetVar2 (interp, "this", "mode", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->sensorID  );  newValue = Tcl_SetVar2 (interp, "this", "sensorID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* sensManRequestStruct */


