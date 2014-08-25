/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "hiResImageSelection.h"
#include "hiResImageSelection_tclndds.h"

int 
Tcl2Ndds_hiResImageSelection (hiResImageSelection nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (hiResImageSelection_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for hiResImageSelection.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,hiResImageSelection_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->targetID  );
  sscanf  (argv[count++], "%d", &nddsObj->selectionType);
  sscanf  (argv[count++], "%d", &nddsObj->row       );
  sscanf  (argv[count++], "%d", &nddsObj->col       );

  return (count);	/* # args used in this struct. */
} /* hiResImageSelectionStruct */


int 
Ndds2Tcl_hiResImageSelection (hiResImageSelection nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->selectionType);  newValue = Tcl_SetVar2 (interp, "this", "selectionType", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->row       );  newValue = Tcl_SetVar2 (interp, "this", "row", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->col       );  newValue = Tcl_SetVar2 (interp, "this", "col", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* hiResImageSelectionStruct */


