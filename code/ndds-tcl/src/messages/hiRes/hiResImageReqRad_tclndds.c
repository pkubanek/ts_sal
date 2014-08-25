/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "hiResImageReqRad.h"
#include "hiResImageReqRad_tclndds.h"

int 
Tcl2Ndds_hiResImageReqRad (hiResImageReqRad nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (hiResImageReqRad_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for hiResImageReqRad.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,hiResImageReqRad_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%f", &nddsObj->relativePan);
  sscanf  (argv[count++], "%f", &nddsObj->relativeTilt);
  sscanf  (argv[count++], "%f", &nddsObj->relativeZoomFactor);

  return (count);	/* # args used in this struct. */
} /* hiResImageReqRadStruct */


int 
Ndds2Tcl_hiResImageReqRad (hiResImageReqRad nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%f", nddsObj->relativePan);  newValue = Tcl_SetVar2 (interp, "this", "relativePan", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->relativeTilt);  newValue = Tcl_SetVar2 (interp, "this", "relativeTilt", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->relativeZoomFactor);  newValue = Tcl_SetVar2 (interp, "this", "relativeZoomFactor", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* hiResImageReqRadStruct */


