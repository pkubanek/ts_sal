/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "hiResImageRequest.h"
#include "hiResImageRequest_tclndds.h"

int 
Tcl2Ndds_hiResImageRequest (hiResImageRequest nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (hiResImageRequest_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for hiResImageRequest.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,hiResImageRequest_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->targetID  );
  sscanf  (argv[count++], "%d", &nddsObj->row       );
  sscanf  (argv[count++], "%d", &nddsObj->col       );
  sscanf  (argv[count++], "%f", &nddsObj->relativeZoomFactor);
  sscanf  (argv[count++], "%f", &nddsObj->focus     );

  return (count);	/* # args used in this struct. */
} /* hiResImageRequestStruct */


int 
Ndds2Tcl_hiResImageRequest (hiResImageRequest nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->row       );  newValue = Tcl_SetVar2 (interp, "this", "row", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->col       );  newValue = Tcl_SetVar2 (interp, "this", "col", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->relativeZoomFactor);  newValue = Tcl_SetVar2 (interp, "this", "relativeZoomFactor", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->focus     );  newValue = Tcl_SetVar2 (interp, "this", "focus", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* hiResImageRequestStruct */


