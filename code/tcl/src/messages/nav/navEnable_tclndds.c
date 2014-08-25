/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "navEnable.h"
#include "navEnable_tclndds.h"

int 
Tcl2Ndds_navEnable (navEnable nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (navEnable_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for navEnable.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,navEnable_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->navEnableFlag = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* navEnableStruct */


int 
Ndds2Tcl_navEnable (navEnable nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->navEnableFlag);  newValue = Tcl_SetVar2 (interp, "this", "navEnableFlag", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* navEnableStruct */


