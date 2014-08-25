/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "navReset.h"
#include "navReset_tclndds.h"

int 
Tcl2Ndds_navReset (navReset nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (navReset_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for navReset.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,navReset_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->navResetFlag = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* navResetStruct */


int 
Ndds2Tcl_navReset (navReset nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->navResetFlag);  newValue = Tcl_SetVar2 (interp, "this", "navResetFlag", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* navResetStruct */


