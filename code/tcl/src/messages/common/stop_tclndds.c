/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "stop.h"
#include "stop_tclndds.h"

int 
Tcl2Ndds_stop (stop nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (stop_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for stop.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,stop_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->stopFlag = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* stopStruct */


int 
Ndds2Tcl_stop (stop nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->stopFlag  );  newValue = Tcl_SetVar2 (interp, "this", "stopFlag", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* stopStruct */


