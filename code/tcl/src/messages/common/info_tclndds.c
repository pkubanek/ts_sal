/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "info.h"
#include "info_tclndds.h"

int 
Tcl2Ndds_info (info nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (info_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for info.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,info_ArgCount);
    return (-1);
  }

  strcpy  (nddsObj->message    , argv[count++]);
  strcpy  (nddsObj->source     , argv[count++]);
  sscanf  (argv[count++], "%d", &nddsObj->verbosity );
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* infoStruct */


int 
Ndds2Tcl_info (info nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  for (i=0; i<1000; i++) {
    sprintf (tmpStr, "%d ", nddsObj->message[i]);
    newValue = Tcl_SetVar2 (interp, "this", "message", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<100; i++) {
    sprintf (tmpStr, "%d ", nddsObj->source[i]);
    newValue = Tcl_SetVar2 (interp, "this", "source", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->verbosity );  newValue = Tcl_SetVar2 (interp, "this", "verbosity", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* infoStruct */


