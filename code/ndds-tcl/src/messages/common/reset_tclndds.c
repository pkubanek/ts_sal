/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "reset.h"
#include "reset_tclndds.h"

int 
Tcl2Ndds_reset (reset nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (reset_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for reset.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,reset_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->resetFlag = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* resetStruct */


int 
Ndds2Tcl_reset (reset nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->resetFlag );  newValue = Tcl_SetVar2 (interp, "this", "resetFlag", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* resetStruct */


