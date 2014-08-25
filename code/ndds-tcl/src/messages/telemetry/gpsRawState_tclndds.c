/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "gpsRawState.h"
#include "gpsRawState_tclndds.h"

int 
Tcl2Ndds_gpsRawState (gpsRawState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (gpsRawState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for gpsRawState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,gpsRawState_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%lf", &nddsObj->receiveTime);
  sscanf  (argv[count++], "%lf", &nddsObj->clockOffset);
  sscanf  (argv[count++], "%u", &nddsObj->numSVSVisible);
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%u",&(nddsObj->visibleSvsPRN[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%u",&(nddsObj->svFlags1[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%u",&(nddsObj->svFlags2[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%d",&(nddsObj->svsElevation[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%d",&(nddsObj->svsAzimuth[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%d",&(nddsObj->svsL1SNR[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%d",&(nddsObj->svsL2SNR[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%lf",&(nddsObj->L1PseudoRange[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%lf",&(nddsObj->L1ContPhase[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%f",&(nddsObj->L1Doppler[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%lf",&(nddsObj->L2ContPhase[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%f",&(nddsObj->L2L1PseudoRange[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%d",&(nddsObj->issueOfDataEphem[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%d",&(nddsObj->L1Slip[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%d",&(nddsObj->L2Slip[i]));
  sscanf  (argv[count++], "%lf", &nddsObj->wgs84Latitude);
  sscanf  (argv[count++], "%lf", &nddsObj->wgs84Longitude);
  sscanf  (argv[count++], "%lf", &nddsObj->wgs84Altitude);
  sscanf  (argv[count++], "%lf", &nddsObj->positionDOP);
  sscanf  (argv[count++], "%lf", &nddsObj->latitudeRate);
  sscanf  (argv[count++], "%lf", &nddsObj->longitudeRate);
  sscanf  (argv[count++], "%lf", &nddsObj->altitudeRate);
  sscanf  (argv[count++], "%ld", &nddsObj->msecOfGPSWeek);
  sscanf  (argv[count++], "%d", &nddsObj->positionflags);
  sscanf  (argv[count++], "%u", &nddsObj->numSVSTracked);
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%u",&(nddsObj->svsChannelNumber[i]));
  for (i=0; i<10; i++)
      sscanf(argv[count++],"%u",&(nddsObj->trackedSVS_PRN[i]));
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* gpsRawStateStruct */


int 
Ndds2Tcl_gpsRawState (gpsRawState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%lf", nddsObj->receiveTime);  newValue = Tcl_SetVar2 (interp, "this", "receiveTime", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->clockOffset);  newValue = Tcl_SetVar2 (interp, "this", "clockOffset", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->numSVSVisible);  newValue = Tcl_SetVar2 (interp, "this", "numSVSVisible", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%u ", nddsObj->visibleSvsPRN[i]);
    newValue = Tcl_SetVar2 (interp, "this", "visibleSvsPRN", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%u ", nddsObj->svFlags1[i]);
    newValue = Tcl_SetVar2 (interp, "this", "svFlags1", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%u ", nddsObj->svFlags2[i]);
    newValue = Tcl_SetVar2 (interp, "this", "svFlags2", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%d ", nddsObj->svsElevation[i]);
    newValue = Tcl_SetVar2 (interp, "this", "svsElevation", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%d ", nddsObj->svsAzimuth[i]);
    newValue = Tcl_SetVar2 (interp, "this", "svsAzimuth", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%d ", nddsObj->svsL1SNR[i]);
    newValue = Tcl_SetVar2 (interp, "this", "svsL1SNR", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%d ", nddsObj->svsL2SNR[i]);
    newValue = Tcl_SetVar2 (interp, "this", "svsL2SNR", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%lf ", nddsObj->L1PseudoRange[i]);
    newValue = Tcl_SetVar2 (interp, "this", "L1PseudoRange", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%lf ", nddsObj->L1ContPhase[i]);
    newValue = Tcl_SetVar2 (interp, "this", "L1ContPhase", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%f ", nddsObj->L1Doppler[i]);
    newValue = Tcl_SetVar2 (interp, "this", "L1Doppler", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%lf ", nddsObj->L2ContPhase[i]);
    newValue = Tcl_SetVar2 (interp, "this", "L2ContPhase", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%f ", nddsObj->L2L1PseudoRange[i]);
    newValue = Tcl_SetVar2 (interp, "this", "L2L1PseudoRange", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%d ", nddsObj->issueOfDataEphem[i]);
    newValue = Tcl_SetVar2 (interp, "this", "issueOfDataEphem", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%d ", nddsObj->L1Slip[i]);
    newValue = Tcl_SetVar2 (interp, "this", "L1Slip", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%d ", nddsObj->L2Slip[i]);
    newValue = Tcl_SetVar2 (interp, "this", "L2Slip", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%lf", nddsObj->wgs84Latitude);  newValue = Tcl_SetVar2 (interp, "this", "wgs84Latitude", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->wgs84Longitude);  newValue = Tcl_SetVar2 (interp, "this", "wgs84Longitude", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->wgs84Altitude);  newValue = Tcl_SetVar2 (interp, "this", "wgs84Altitude", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->positionDOP);  newValue = Tcl_SetVar2 (interp, "this", "positionDOP", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->latitudeRate);  newValue = Tcl_SetVar2 (interp, "this", "latitudeRate", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->longitudeRate);  newValue = Tcl_SetVar2 (interp, "this", "longitudeRate", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%lf", nddsObj->altitudeRate);  newValue = Tcl_SetVar2 (interp, "this", "altitudeRate", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%ld", nddsObj->msecOfGPSWeek);  newValue = Tcl_SetVar2 (interp, "this", "msecOfGPSWeek", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->positionflags);  newValue = Tcl_SetVar2 (interp, "this", "positionflags", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->numSVSTracked);  newValue = Tcl_SetVar2 (interp, "this", "numSVSTracked", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%u ", nddsObj->svsChannelNumber[i]);
    newValue = Tcl_SetVar2 (interp, "this", "svsChannelNumber", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<10; i++) {
    sprintf (tmpStr, "%u ", nddsObj->trackedSVS_PRN[i]);
    newValue = Tcl_SetVar2 (interp, "this", "trackedSVS_PRN", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* gpsRawStateStruct */


