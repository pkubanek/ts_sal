/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtLaser.h"
#include "rtLaser_tclndds.h"

int 
Tcl2Ndds_rtLaser (rtLaser nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtLaser_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtLaser.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtLaser_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->laserIgnore = (char)num;
  }
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->hazardDetected = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* rtLaserStruct */


int 
Ndds2Tcl_rtLaser (rtLaser nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->laserIgnore);  newValue = Tcl_SetVar2 (interp, "this", "laserIgnore", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->hazardDetected);  newValue = Tcl_SetVar2 (interp, "this", "hazardDetected", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtLaserStruct */


