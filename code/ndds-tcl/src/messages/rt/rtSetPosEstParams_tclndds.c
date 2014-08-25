/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtSetPosEstParams.h"
#include "rtSetPosEstParams_tclndds.h"

int 
Tcl2Ndds_rtSetPosEstParams (rtSetPosEstParams nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtSetPosEstParams_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtSetPosEstParams.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtSetPosEstParams_ArgCount);
    return (-1);
  }

  for (i=0; i<3; i++)
      sscanf(argv[count++],"%d",&(nddsObj->gain[i]));

  return (count);	/* # args used in this struct. */
} /* rtSetPosEstParamsStruct */


int 
Ndds2Tcl_rtSetPosEstParams (rtSetPosEstParams nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  for (i=0; i<3; i++) {
    sprintf (tmpStr, "%d ", nddsObj->gain[i]);
    newValue = Tcl_SetVar2 (interp, "this", "gain", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }

  return (1==1);	/* Return TRUE for now. */
} /* rtSetPosEstParamsStruct */


