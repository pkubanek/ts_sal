/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "lasRawScanData.h"
#include "lasRawScanData_tclndds.h"

int 
Tcl2Ndds_lasRawScanData (lasRawScanData nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (lasRawScanData_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for lasRawScanData.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,lasRawScanData_ArgCount);
    return (-1);
  }

  for (i=0; i<361; i++)
      sscanf(argv[count++],"%u",&(nddsObj->scanMap[i]));
  sscanf  (argv[count++], "%u", &nddsObj->resolution);
  sscanf  (argv[count++], "%u", &nddsObj->sampleRate);
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* lasRawScanDataStruct */


int 
Ndds2Tcl_lasRawScanData (lasRawScanData nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  for (i=0; i<361; i++) {
    sprintf (tmpStr, "%u ", nddsObj->scanMap[i]);
    newValue = Tcl_SetVar2 (interp, "this", "scanMap", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%u", nddsObj->resolution);  newValue = Tcl_SetVar2 (interp, "this", "resolution", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->sampleRate);  newValue = Tcl_SetVar2 (interp, "this", "sampleRate", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* lasRawScanDataStruct */


