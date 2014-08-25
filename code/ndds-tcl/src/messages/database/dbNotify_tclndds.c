/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "dbNotify.h"
#include "dbNotify_tclndds.h"

int 
Tcl2Ndds_dbNotify (dbNotify nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (dbNotify_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for dbNotify.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,dbNotify_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->targetID  );
  sscanf  (argv[count++], "%d", &nddsObj->fieldName );

  return (count);	/* # args used in this struct. */
} /* dbNotifyStruct */


int 
Ndds2Tcl_dbNotify (dbNotify nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->fieldName );  newValue = Tcl_SetVar2 (interp, "this", "fieldName", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* dbNotifyStruct */


