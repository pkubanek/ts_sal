/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "dbRecordReply.h"
#include "dbRecordReply_tclndds.h"

int 
Tcl2Ndds_dbRecordReply (dbRecordReply nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (dbRecordReply_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for dbRecordReply.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,dbRecordReply_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->replyStatus);
  sscanf  (argv[count++], "%d", &nddsObj->replyDestination);
  sscanf  (argv[count++], "%d", &nddsObj->targetID  );
  for (i=0; i<3; i++)
      sscanf(argv[count++],"%f",&(nddsObj->GPS_Position[i]));
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->currentlyTracked = (char)num;
  }
  strcpy  (nddsObj->templateImage , argv[count++]);
  strcpy  (nddsObj->hiResImage , argv[count++]);
  strcpy  (nddsObj->metalDetectorData , argv[count++]);
  strcpy  (nddsObj->magnetometerData , argv[count++]);
  strcpy  (nddsObj->radarData  , argv[count++]);
  strcpy  (nddsObj->classifierOutputData , argv[count++]);
  strcpy  (nddsObj->spectrometerData , argv[count++]);
  strcpy  (nddsObj->spectralFeaturesData , argv[count++]);
  for (i=0; i<2; i++)
      sscanf(argv[count++],"%d",&(nddsObj->hiResImageTargetCoord[i]));
  for (i=0; i<2; i++)
      sscanf(argv[count++],"%f",&(nddsObj->hiResImageScalingFactor[i]));
  sscanf  (argv[count++], "%d", &nddsObj->objSize   );
  sscanf  (argv[count++], "%d", &nddsObj->objColor  );
  sscanf  (argv[count++], "%d", &nddsObj->objTexture);
  sscanf  (argv[count++], "%d", &nddsObj->objSpectralFeatures);
  sscanf  (argv[count++], "%f", &nddsObj->classRisk );
  for (i=0; i<5; i++)
      sscanf(argv[count++],"%f",&(nddsObj->classEstInfoGain[i]));
  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->classActive = (char)num;
  }
  for (i=0; i<128; i++)
      sscanf(argv[count++],"%f",&(nddsObj->classMemberProb[i]));

  return (count);	/* # args used in this struct. */
} /* dbRecordReplyStruct */


int 
Ndds2Tcl_dbRecordReply (dbRecordReply nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->replyStatus);  newValue = Tcl_SetVar2 (interp, "this", "replyStatus", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->replyDestination);  newValue = Tcl_SetVar2 (interp, "this", "replyDestination", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<3; i++) {
    sprintf (tmpStr, "%f ", nddsObj->GPS_Position[i]);
    newValue = Tcl_SetVar2 (interp, "this", "GPS_Position", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->currentlyTracked);  newValue = Tcl_SetVar2 (interp, "this", "currentlyTracked", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->templateImage[i]);
    newValue = Tcl_SetVar2 (interp, "this", "templateImage", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->hiResImage[i]);
    newValue = Tcl_SetVar2 (interp, "this", "hiResImage", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->metalDetectorData[i]);
    newValue = Tcl_SetVar2 (interp, "this", "metalDetectorData", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->magnetometerData[i]);
    newValue = Tcl_SetVar2 (interp, "this", "magnetometerData", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->radarData[i]);
    newValue = Tcl_SetVar2 (interp, "this", "radarData", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->classifierOutputData[i]);
    newValue = Tcl_SetVar2 (interp, "this", "classifierOutputData", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->spectrometerData[i]);
    newValue = Tcl_SetVar2 (interp, "this", "spectrometerData", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%d ", nddsObj->spectralFeaturesData[i]);
    newValue = Tcl_SetVar2 (interp, "this", "spectralFeaturesData", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<2; i++) {
    sprintf (tmpStr, "%d ", nddsObj->hiResImageTargetCoord[i]);
    newValue = Tcl_SetVar2 (interp, "this", "hiResImageTargetCoord", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<2; i++) {
    sprintf (tmpStr, "%f ", nddsObj->hiResImageScalingFactor[i]);
    newValue = Tcl_SetVar2 (interp, "this", "hiResImageScalingFactor", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->objSize   );  newValue = Tcl_SetVar2 (interp, "this", "objSize", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->objColor  );  newValue = Tcl_SetVar2 (interp, "this", "objColor", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->objTexture);  newValue = Tcl_SetVar2 (interp, "this", "objTexture", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->objSpectralFeatures);  newValue = Tcl_SetVar2 (interp, "this", "objSpectralFeatures", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->classRisk );  newValue = Tcl_SetVar2 (interp, "this", "classRisk", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<5; i++) {
    sprintf (tmpStr, "%f ", nddsObj->classEstInfoGain[i]);
    newValue = Tcl_SetVar2 (interp, "this", "classEstInfoGain", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->classActive);  newValue = Tcl_SetVar2 (interp, "this", "classActive", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<128; i++) {
    sprintf (tmpStr, "%f ", nddsObj->classMemberProb[i]);
    newValue = Tcl_SetVar2 (interp, "this", "classMemberProb", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }

  return (1==1);	/* Return TRUE for now. */
} /* dbRecordReplyStruct */


