/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "event.h"
#include "event_tclndds.h"

int 
Tcl2Ndds_event (event nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (event_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for event.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,event_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->dummyFiller = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* eventStruct */


int 
Ndds2Tcl_event (event nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->dummyFiller);  newValue = Tcl_SetVar2 (interp, "this", "dummyFiller", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* eventStruct */


