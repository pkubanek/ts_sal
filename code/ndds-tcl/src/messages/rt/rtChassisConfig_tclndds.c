/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtChassisConfig.h"
#include "rtChassisConfig_tclndds.h"

int 
Tcl2Ndds_rtChassisConfig (rtChassisConfig nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtChassisConfig_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtChassisConfig.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtChassisConfig_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->rtChassisConfigFlag = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* rtChassisConfigStruct */


int 
Ndds2Tcl_rtChassisConfig (rtChassisConfig nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->rtChassisConfigFlag);  newValue = Tcl_SetVar2 (interp, "this", "rtChassisConfigFlag", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtChassisConfigStruct */


