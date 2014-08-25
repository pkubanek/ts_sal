/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "navPlanUpdateSet.h"
#include "navPlanUpdateSet_tclndds.h"

int 
Tcl2Ndds_navPlanUpdateSet (navPlanUpdateSet nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (navPlanUpdateSet_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for navPlanUpdateSet.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,navPlanUpdateSet_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->taskMode  );
  sscanf  (argv[count++], "%f", &nddsObj->minTurningRadius);
  sscanf  (argv[count++], "%f", &nddsObj->cameraFOV );
  sscanf  (argv[count++], "%f", &nddsObj->rowWidth  );
  sscanf  (argv[count++], "%f", &nddsObj->speed     );
  sscanf  (argv[count++], "%d", &nddsObj->planningMode);
  sscanf  (argv[count++], "%d", &nddsObj->startNewPattern);
  sscanf  (argv[count++], "%d", &nddsObj->patternType);
  sscanf  (argv[count++], "%d", &nddsObj->useAbsGPSCoord);
  for (i=0; i<20; i++)
      sscanf(argv[count++],"%f",&(nddsObj->coords_dx[i]));
  for (i=0; i<20; i++)
      sscanf(argv[count++],"%f",&(nddsObj->coords_dy[i]));
  for (i=0; i<20; i++)
      sscanf(argv[count++],"%f",&(nddsObj->coords_dz[i]));
  sscanf  (argv[count++], "%d", &nddsObj->numCoords );
  sscanf  (argv[count++], "%f", &nddsObj->startyaw  );
  sscanf  (argv[count++], "%f", &nddsObj->startroll );
  sscanf  (argv[count++], "%f", &nddsObj->startdate );
  sscanf  (argv[count++], "%f", &nddsObj->relFarmingLength);
  sscanf  (argv[count++], "%f", &nddsObj->relFarmingWidth);
  sscanf  (argv[count++], "%f", &nddsObj->spiralMaxRadius);
  sscanf  (argv[count++], "%d", &nddsObj->spiralClockWise);
  sscanf  (argv[count++], "%f", &nddsObj->sunFollowingRowLength);
  sscanf  (argv[count++], "%f", &nddsObj->waypointOrientation);
  sscanf  (argv[count++], "%f", &nddsObj->waypointTolerance);
  sscanf  (argv[count++], "%d", &nddsObj->targetID  );
  sscanf  (argv[count++], "%d", &nddsObj->sensorID  );
  sscanf  (argv[count++], "%d", &nddsObj->planNewPlan);
  strcpy  (nddsObj->manplan    , argv[count++]);

  return (count);	/* # args used in this struct. */
} /* navPlanUpdateSetStruct */


int 
Ndds2Tcl_navPlanUpdateSet (navPlanUpdateSet nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->taskMode  );  newValue = Tcl_SetVar2 (interp, "this", "taskMode", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->minTurningRadius);  newValue = Tcl_SetVar2 (interp, "this", "minTurningRadius", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->cameraFOV );  newValue = Tcl_SetVar2 (interp, "this", "cameraFOV", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->rowWidth  );  newValue = Tcl_SetVar2 (interp, "this", "rowWidth", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->speed     );  newValue = Tcl_SetVar2 (interp, "this", "speed", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->planningMode);  newValue = Tcl_SetVar2 (interp, "this", "planningMode", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->startNewPattern);  newValue = Tcl_SetVar2 (interp, "this", "startNewPattern", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->patternType);  newValue = Tcl_SetVar2 (interp, "this", "patternType", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->useAbsGPSCoord);  newValue = Tcl_SetVar2 (interp, "this", "useAbsGPSCoord", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<20; i++) {
    sprintf (tmpStr, "%f ", nddsObj->coords_dx[i]);
    newValue = Tcl_SetVar2 (interp, "this", "coords_dx", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<20; i++) {
    sprintf (tmpStr, "%f ", nddsObj->coords_dy[i]);
    newValue = Tcl_SetVar2 (interp, "this", "coords_dy", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<20; i++) {
    sprintf (tmpStr, "%f ", nddsObj->coords_dz[i]);
    newValue = Tcl_SetVar2 (interp, "this", "coords_dz", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->numCoords );  newValue = Tcl_SetVar2 (interp, "this", "numCoords", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->startyaw  );  newValue = Tcl_SetVar2 (interp, "this", "startyaw", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->startroll );  newValue = Tcl_SetVar2 (interp, "this", "startroll", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->startdate );  newValue = Tcl_SetVar2 (interp, "this", "startdate", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->relFarmingLength);  newValue = Tcl_SetVar2 (interp, "this", "relFarmingLength", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->relFarmingWidth);  newValue = Tcl_SetVar2 (interp, "this", "relFarmingWidth", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->spiralMaxRadius);  newValue = Tcl_SetVar2 (interp, "this", "spiralMaxRadius", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->spiralClockWise);  newValue = Tcl_SetVar2 (interp, "this", "spiralClockWise", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->sunFollowingRowLength);  newValue = Tcl_SetVar2 (interp, "this", "sunFollowingRowLength", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->waypointOrientation);  newValue = Tcl_SetVar2 (interp, "this", "waypointOrientation", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->waypointTolerance);  newValue = Tcl_SetVar2 (interp, "this", "waypointTolerance", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->sensorID  );  newValue = Tcl_SetVar2 (interp, "this", "sensorID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->planNewPlan);  newValue = Tcl_SetVar2 (interp, "this", "planNewPlan", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<40; i++) {
    sprintf (tmpStr, "%d ", nddsObj->manplan[i]);
    newValue = Tcl_SetVar2 (interp, "this", "manplan", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }

  return (1==1);	/* Return TRUE for now. */
} /* navPlanUpdateSetStruct */


