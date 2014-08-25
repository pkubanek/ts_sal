/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "specReply.h"
#include "specReply_tclndds.h"

int 
Tcl2Ndds_specReply (specReply nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (specReply_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for specReply.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,specReply_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->sensorStatus);
  sscanf  (argv[count++], "%d", &nddsObj->extendedSensorStatus);
  strcpy  (nddsObj->listFileName , argv[count++]);
  sscanf  (argv[count++], "%f", &nddsObj->deploymentCost);

  return (count);	/* # args used in this struct. */
} /* specReplyStruct */


int 
Ndds2Tcl_specReply (specReply nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->sensorStatus);  newValue = Tcl_SetVar2 (interp, "this", "sensorStatus", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->extendedSensorStatus);  newValue = Tcl_SetVar2 (interp, "this", "extendedSensorStatus", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->listFileName[i]);
    newValue = Tcl_SetVar2 (interp, "this", "listFileName", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%f", nddsObj->deploymentCost);  newValue = Tcl_SetVar2 (interp, "this", "deploymentCost", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* specReplyStruct */


