/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "weatherState.h"
#include "weatherState_tclndds.h"

int 
Tcl2Ndds_weatherState (weatherState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (weatherState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for weatherState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,weatherState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->insideTemperature);
  sscanf  (argv[count++], "%d", &nddsObj->outsideTemperature);
  sscanf  (argv[count++], "%d", &nddsObj->barometer );
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->insideHumidity = (char)num;
  }
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->outsideHumidity = (char)num;
  }
  sscanf  (argv[count++], "%d", &nddsObj->DewPoint  );
  sscanf  (argv[count++], "%d", &nddsObj->rain      );
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->windSpeed = (char)num;
  }
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->windGust = (char)num;
  }
  sscanf  (argv[count++], "%d", &nddsObj->WindChill );
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->windDirection = (char)num;
  }
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->week = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* weatherStateStruct */


int 
Ndds2Tcl_weatherState (weatherState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->insideTemperature);  newValue = Tcl_SetVar2 (interp, "this", "insideTemperature", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->outsideTemperature);  newValue = Tcl_SetVar2 (interp, "this", "outsideTemperature", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->barometer );  newValue = Tcl_SetVar2 (interp, "this", "barometer", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->insideHumidity);  newValue = Tcl_SetVar2 (interp, "this", "insideHumidity", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->outsideHumidity);  newValue = Tcl_SetVar2 (interp, "this", "outsideHumidity", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->DewPoint  );  newValue = Tcl_SetVar2 (interp, "this", "DewPoint", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->rain      );  newValue = Tcl_SetVar2 (interp, "this", "rain", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->windSpeed );  newValue = Tcl_SetVar2 (interp, "this", "windSpeed", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->windGust  );  newValue = Tcl_SetVar2 (interp, "this", "windGust", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->WindChill );  newValue = Tcl_SetVar2 (interp, "this", "WindChill", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->windDirection);  newValue = Tcl_SetVar2 (interp, "this", "windDirection", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* weatherStateStruct */


