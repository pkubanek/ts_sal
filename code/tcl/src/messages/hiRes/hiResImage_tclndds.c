/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "hiResImage.h"
#include "hiResImage_tclndds.h"

int 
Tcl2Ndds_hiResImage (hiResImage nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (hiResImage_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for hiResImage.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,hiResImage_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->targetID  );
  strcpy  (nddsObj->filename   , argv[count++]);
  sscanf  (argv[count++], "%f", &nddsObj->ptuAzimuth);
  sscanf  (argv[count++], "%f", &nddsObj->ptuElevation);
  sscanf  (argv[count++], "%f", &nddsObj->robot_dx  );
  sscanf  (argv[count++], "%f", &nddsObj->robot_dy  );
  sscanf  (argv[count++], "%f", &nddsObj->robot_dz  );
  sscanf  (argv[count++], "%f", &nddsObj->robotAzimuth);
  sscanf  (argv[count++], "%f", &nddsObj->robotPitch);
  sscanf  (argv[count++], "%f", &nddsObj->robotRoll );
  sscanf  (argv[count++], "%d", &nddsObj->GPS_msecs );
  sscanf  (argv[count++], "%d", &nddsObj->GPS_week  );

  return (count);	/* # args used in this struct. */
} /* hiResImageStruct */


int 
Ndds2Tcl_hiResImage (hiResImage nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->filename[i]);
    newValue = Tcl_SetVar2 (interp, "this", "filename", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%f", nddsObj->ptuAzimuth);  newValue = Tcl_SetVar2 (interp, "this", "ptuAzimuth", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->ptuElevation);  newValue = Tcl_SetVar2 (interp, "this", "ptuElevation", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->robot_dx  );  newValue = Tcl_SetVar2 (interp, "this", "robot_dx", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->robot_dy  );  newValue = Tcl_SetVar2 (interp, "this", "robot_dy", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->robot_dz  );  newValue = Tcl_SetVar2 (interp, "this", "robot_dz", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->robotAzimuth);  newValue = Tcl_SetVar2 (interp, "this", "robotAzimuth", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->robotPitch);  newValue = Tcl_SetVar2 (interp, "this", "robotPitch", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->robotRoll );  newValue = Tcl_SetVar2 (interp, "this", "robotRoll", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->GPS_msecs );  newValue = Tcl_SetVar2 (interp, "this", "GPS_msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->GPS_week  );  newValue = Tcl_SetVar2 (interp, "this", "GPS_week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* hiResImageStruct */


