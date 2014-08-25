

/*
  To Add a new entry, copy one block and change the
  names to the new type.  Eventually this will be 
  an automatically generated file.
 */


/***** Common messages ******/

/*
 *#include "error.h"
 *#include "error_tclndds.h"
 *NDDS_TYPE_DRIVER errorMsgTypeDriver = {
 *        "error", 
 *        (NDDS_REGISTER_HANDLER)  errorMsgNddsRegister, 
 *        (NDDS_ALLOCATE_HANDLER)  errorMsgAllocate, 
 *        (NDDS_FREE_HANDLER)      errorMsgFree, 
 *        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_errorMsg, 
 *        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_errorMsg, 
 *        NULL, 
 *        NULL 
 *}; 
 */

#include "reset.h"
#include "reset_tclndds.h"
NDDS_TYPE_DRIVER resetTypeDriver = {
        "reset", 
        (NDDS_REGISTER_HANDLER)  resetNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  resetAllocate, 
        (NDDS_FREE_HANDLER)      resetFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_reset , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_reset , 
        NULL, 
        NULL 
}; 

#include "move.h"
#include "move_tclndds.h"
NDDS_TYPE_DRIVER moveTypeDriver = {
        "move", 
        (NDDS_REGISTER_HANDLER)  moveNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  moveAllocate, 
        (NDDS_FREE_HANDLER)      moveFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_move , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_move , 
        NULL, 
        NULL 
}; 

#include "info.h"
#include "info_tclndds.h"
NDDS_TYPE_DRIVER infoTypeDriver = {
        "info", 
        (NDDS_REGISTER_HANDLER)  infoNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  infoAllocate, 
        (NDDS_FREE_HANDLER)      infoFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_info , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_info , 
        NULL, 
        NULL 
}; 



/***** Telemetry messages ******/

#include "apsDerivedState.h"
#include "apsDerivedState_tclndds.h"
NDDS_TYPE_DRIVER apsDerivedStateTypeDriver = {
        "apsDerivedState", 
        (NDDS_REGISTER_HANDLER)  apsDerivedStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  apsDerivedStateAllocate, 
        (NDDS_FREE_HANDLER)      apsDerivedStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_apsDerivedState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_apsDerivedState , 
        NULL, 
        NULL 
}; 

#include "apsRawState.h"
#include "apsRawState_tclndds.h"
NDDS_TYPE_DRIVER apsRawStateTypeDriver = {
        "apsRawState", 
        (NDDS_REGISTER_HANDLER)  apsRawStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  apsRawStateAllocate, 
        (NDDS_FREE_HANDLER)      apsRawStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_apsRawState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_apsRawState , 
        NULL, 
        NULL 
}; 

#include "arbInternalState.h"
#include "arbInternalState_tclndds.h"
NDDS_TYPE_DRIVER arbInternalStateTypeDriver = {
        "arbInternalState", 
        (NDDS_REGISTER_HANDLER)  arbInternalStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  arbInternalStateAllocate, 
        (NDDS_FREE_HANDLER)      arbInternalStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_arbInternalState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_arbInternalState , 
        NULL, 
        NULL 
}; 

#include "bodDerivedState.h"
#include "bodDerivedState_tclndds.h"
NDDS_TYPE_DRIVER bodDerivedStateTypeDriver = {
        "bodDerivedState", 
        (NDDS_REGISTER_HANDLER)  bodDerivedStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  bodDerivedStateAllocate, 
        (NDDS_FREE_HANDLER)      bodDerivedStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_bodDerivedState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_bodDerivedState , 
        NULL, 
        NULL 
}; 

#include "bodRawState.h"
#include "bodRawState_tclndds.h"
NDDS_TYPE_DRIVER bodRawStateTypeDriver = {
        "bodRawState", 
        (NDDS_REGISTER_HANDLER)  bodRawStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  bodRawStateAllocate, 
        (NDDS_FREE_HANDLER)      bodRawStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_bodRawState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_bodRawState , 
        NULL, 
        NULL 
}; 

#if 0
#include "epsDerivedState.h"
#include "epsDerivedState_tclndds.h"
NDDS_TYPE_DRIVER epsDerivedStateTypeDriver = {
        "epsDerivedState", 
        (NDDS_REGISTER_HANDLER)  epsDerivedStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  epsDerivedStateAllocate, 
        (NDDS_FREE_HANDLER)      epsDerivedStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_epsDerivedState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_epsDerivedState , 
        NULL, 
        NULL 
}; 
#endif

#include "event.h"
#include "event_tclndds.h"
NDDS_TYPE_DRIVER eventTypeDriver = {
	"event", 
	(NDDS_REGISTER_HANDLER)  eventNddsRegister, 
	(NDDS_ALLOCATE_HANDLER)  eventAllocate, 
	(NDDS_FREE_HANDLER)      eventFree, 
	(NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_event, 
	(NDDS_TO_TCL_HANDLER)    Ndds2Tcl_event, 
	NULL, 
	NULL 
};


#include "gpsDerivedState.h"
#include "gpsDerivedState_tclndds.h"
NDDS_TYPE_DRIVER gpsDerivedStateTypeDriver = {
        "gpsDerivedState", 
        (NDDS_REGISTER_HANDLER)  gpsDerivedStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  gpsDerivedStateAllocate, 
        (NDDS_FREE_HANDLER)      gpsDerivedStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_gpsDerivedState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_gpsDerivedState , 
        NULL, 
        NULL 
}; 


#include "gpsRawState.h"
#include "gpsRawState_tclndds.h"
NDDS_TYPE_DRIVER gpsRawStateTypeDriver = {
        "gpsRawState", 
        (NDDS_REGISTER_HANDLER)  gpsRawStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  gpsRawStateAllocate, 
        (NDDS_FREE_HANDLER)      gpsRawStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_gpsRawState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_gpsRawState , 
        NULL, 
        NULL 
}; 

#include "imuDerivedState.h"
#include "imuDerivedState_tclndds.h"
NDDS_TYPE_DRIVER imuDerivedStateTypeDriver = {
        "imuDerivedState", 
        (NDDS_REGISTER_HANDLER)  imuDerivedStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  imuDerivedStateAllocate, 
        (NDDS_FREE_HANDLER)      imuDerivedStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_imuDerivedState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_imuDerivedState , 
        NULL, 
        NULL 
}; 

#include "imuRawState.h"
#include "imuRawState_tclndds.h"
NDDS_TYPE_DRIVER imuRawStateTypeDriver = {
        "imuRawState", 
        (NDDS_REGISTER_HANDLER)  imuRawStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  imuRawStateAllocate, 
        (NDDS_FREE_HANDLER)      imuRawStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_imuRawState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_imuRawState , 
        NULL, 
        NULL 
}; 


#include "kvhDerivedState.h"
#include "kvhDerivedState_tclndds.h"
NDDS_TYPE_DRIVER kvhDerivedStateTypeDriver = {
        "kvhDerivedState",
        (NDDS_REGISTER_HANDLER)  kvhDerivedStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  kvhDerivedStateAllocate, 
        (NDDS_FREE_HANDLER)      kvhDerivedStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_kvhDerivedState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_kvhDerivedState , 
        NULL, 
        NULL 
}; 

#include "lasHazardMap.h"
#include "lasHazardMap_tclndds.h"
NDDS_TYPE_DRIVER lasHazardMapTypeDriver = {
        "lasHazardMap", 
        (NDDS_REGISTER_HANDLER)  lasHazardMapNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  lasHazardMapAllocate, 
        (NDDS_FREE_HANDLER)      lasHazardMapFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_lasHazardMap , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_lasHazardMap , 
        NULL, 
        NULL 
}; 

#include "lasRawScanData.h"
#include "lasRawScanData_tclndds.h"
NDDS_TYPE_DRIVER lasRawScanDataTypeDriver = {
        "lasRawScanData", 
        (NDDS_REGISTER_HANDLER)  lasRawScanDataNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  lasRawScanDataAllocate, 
        (NDDS_FREE_HANDLER)      lasRawScanDataFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_lasRawScanData , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_lasRawScanData , 
        NULL, 
        NULL 
}; 


#include "morInternalState.h"
#include "morInternalState_tclndds.h"
NDDS_TYPE_DRIVER morInternalStateTypeDriver = {
        "morInternalState", 
        (NDDS_REGISTER_HANDLER)  morInternalStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  morInternalStateAllocate, 
        (NDDS_FREE_HANDLER)      morInternalStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_morInternalState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_morInternalState , 
        NULL, 
        NULL 
}; 

/*
 *#include "navWatchdogStatus.h"
 *#include "navWatchdogStatus_tclndds.h"
 *NDDS_TYPE_DRIVER navWatchdogStatusTypeDriver = {
 *        "navWatchdogStatus", 
 *        (NDDS_REGISTER_HANDLER)  navWatchdogStatusNddsRegister, 
 *        (NDDS_ALLOCATE_HANDLER)  navWatchdogStatusAllocate, 
 *        (NDDS_FREE_HANDLER)      navWatchdogStatusFree, 
 *        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_navWatchdogStatus , 
 *        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_navWatchdogStatus , 
 *        NULL, 
 *        NULL 
 *}; 
 */

#include "posDerivedState.h"
#include "posDerivedState_tclndds.h"
NDDS_TYPE_DRIVER posDerivedStateTypeDriver = {
        "posDerivedState", 
        (NDDS_REGISTER_HANDLER)  posDerivedStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  posDerivedStateAllocate, 
        (NDDS_FREE_HANDLER)      posDerivedStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_posDerivedState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_posDerivedState , 
        NULL, 
        NULL 
}; 

#include "posRawState.h"
#include "posRawState_tclndds.h"
NDDS_TYPE_DRIVER posRawStateTypeDriver = {
        "posRawState", 
        (NDDS_REGISTER_HANDLER)  posRawStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  posRawStateAllocate, 
        (NDDS_FREE_HANDLER)      posRawStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_posRawState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_posRawState , 
        NULL, 
        NULL 
}; 


#include "steInternalState.h"
#include "steInternalState_tclndds.h"
NDDS_TYPE_DRIVER steInternalStateTypeDriver = {
        "steInternalState", 
        (NDDS_REGISTER_HANDLER)  steInternalStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  steInternalStateAllocate, 
        (NDDS_FREE_HANDLER)      steInternalStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_steInternalState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_steInternalState , 
        NULL, 
        NULL 
}; 


#include "sysState.h"
#include "sysState_tclndds.h"
NDDS_TYPE_DRIVER sysStateTypeDriver = {
        "sysState", 
        (NDDS_REGISTER_HANDLER)  sysStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  sysStateAllocate, 
        (NDDS_FREE_HANDLER)      sysStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_sysState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_sysState , 
        NULL, 
        NULL 
}; 



/***** Real-time messages *****/

#include "rtChassisConfig.h"
#include "rtChassisConfig_tclndds.h"
NDDS_TYPE_DRIVER rtChassisConfigTypeDriver = {
        "rtChassisConfig", 
        (NDDS_REGISTER_HANDLER)  rtChassisConfigNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtChassisConfigAllocate, 
        (NDDS_FREE_HANDLER)      rtChassisConfigFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtChassisConfig , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtChassisConfig , 
        NULL, 
        NULL 
}; 

#include "rtDrive.h"
#include "rtDrive_tclndds.h"
NDDS_TYPE_DRIVER rtDriveTypeDriver = {
        "rtDrive", 
        (NDDS_REGISTER_HANDLER)  rtDriveNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtDriveAllocate, 
        (NDDS_FREE_HANDLER)      rtDriveFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtDrive , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtDrive , 
        NULL, 
        NULL 
}; 

#include "rtSetActuator.h"
#include "rtSetActuator_tclndds.h"
NDDS_TYPE_DRIVER rtSetActuatorTypeDriver = {
        "rtSetActuator", 
        (NDDS_REGISTER_HANDLER)  rtSetActuatorNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtSetActuatorAllocate, 
        (NDDS_FREE_HANDLER)      rtSetActuatorFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtSetActuator , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtSetActuator , 
        NULL, 
        NULL 
}; 

#include "rtSetBroadcastFreq.h"
#include "rtSetBroadcastFreq_tclndds.h"
NDDS_TYPE_DRIVER rtSetBroadcastFreqTypeDriver = {
        "rtSetBroadcastFreq", 
        (NDDS_REGISTER_HANDLER)  rtSetBroadcastFreqNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtSetBroadcastFreqAllocate, 
        (NDDS_FREE_HANDLER)      rtSetBroadcastFreqFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtSetBroadcastFreq , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtSetBroadcastFreq , 
        NULL, 
        NULL 
}; 

#include "rtSetParamFloat.h"
#include "rtSetParamFloat_tclndds.h"
NDDS_TYPE_DRIVER rtSetParamFloatTypeDriver = {
        "rtSetParamFloat", 
        (NDDS_REGISTER_HANDLER)  rtSetParamFloatNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtSetParamFloatAllocate, 
        (NDDS_FREE_HANDLER)      rtSetParamFloatFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtSetParamFloat , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtSetParamFloat , 
        NULL, 
        NULL 
}; 

#include "rtSetParamInt.h"
#include "rtSetParamInt_tclndds.h"
NDDS_TYPE_DRIVER rtSetParamIntTypeDriver = {
        "rtSetParamInt", 
        (NDDS_REGISTER_HANDLER)  rtSetParamIntNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtSetParamIntAllocate, 
        (NDDS_FREE_HANDLER)      rtSetParamIntFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtSetParamInt , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtSetParamInt , 
        NULL, 
        NULL 
}; 

#include "rtSetPosEstParams.h"
#include "rtSetPosEstParams_tclndds.h"
NDDS_TYPE_DRIVER rtSetPosEstParamsTypeDriver = {
        "rtSetPosEstParams", 
        (NDDS_REGISTER_HANDLER)  rtSetPosEstParamsNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtSetPosEstParamsAllocate, 
        (NDDS_FREE_HANDLER)      rtSetPosEstParamsFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtSetPosEstParams , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtSetPosEstParams , 
        NULL, 
        NULL 
}; 

#include "rtSetServoParams.h"
#include "rtSetServoParams_tclndds.h"
NDDS_TYPE_DRIVER rtSetServoParamsTypeDriver = {
        "rtSetServoParams", 
        (NDDS_REGISTER_HANDLER)  rtSetServoParamsNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtSetServoParamsAllocate, 
        (NDDS_FREE_HANDLER)      rtSetServoParamsFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtSetServoParams , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtSetServoParams , 
        NULL, 
        NULL 
}; 

#include "rtSignalCondition.h"
#include "rtSignalCondition_tclndds.h"
NDDS_TYPE_DRIVER rtSignalConditionTypeDriver = {
        "rtSignalCondition", 
        (NDDS_REGISTER_HANDLER)  rtSignalConditionNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtSignalConditionAllocate, 
        (NDDS_FREE_HANDLER)      rtSignalConditionFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtSignalCondition , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtSignalCondition , 
        NULL, 
        NULL 
}; 

#include "rtAmpState.h"
#include "rtAmpState_tclndds.h"
NDDS_TYPE_DRIVER rtAmpStateTypeDriver = {
        "rtAmpState", 
        (NDDS_REGISTER_HANDLER)  rtAmpStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtAmpStateAllocate, 
        (NDDS_FREE_HANDLER)      rtAmpStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtAmpState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtAmpState , 
        NULL, 
        NULL 
}; 

#include "rtControlState.h"
#include "rtControlState_tclndds.h"
NDDS_TYPE_DRIVER rtControlStateTypeDriver = {
        "rtControlState", 
        (NDDS_REGISTER_HANDLER)  rtControlStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtControlStateAllocate, 
        (NDDS_FREE_HANDLER)      rtControlStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtControlState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtControlState , 
        NULL, 
        NULL 
}; 

#include "rtEmergencySignals.h"
#include "rtEmergencySignals_tclndds.h"
NDDS_TYPE_DRIVER rtEmergencySignalsTypeDriver = {
        "rtEmergencySignals", 
        (NDDS_REGISTER_HANDLER)  rtEmergencySignalsNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  rtEmergencySignalsAllocate, 
        (NDDS_FREE_HANDLER)      rtEmergencySignalsFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_rtEmergencySignals , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_rtEmergencySignals , 
        NULL, 
        NULL 
}; 

/***** SAS messages *****/

/* hiRes (pan/tilt camera) messages */

#include "hiResImage.h"
#include "hiResImage_tclndds.h"
NDDS_TYPE_DRIVER hiResImageTypeDriver = {
        "hiResImage", 
        (NDDS_REGISTER_HANDLER)  hiResImageNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  hiResImageAllocate, 
        (NDDS_FREE_HANDLER)      hiResImageFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_hiResImage , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_hiResImage , 
        NULL, 
        NULL 
}; 

#include "hiResImageRequest.h"
#include "hiResImageRequest_tclndds.h"
NDDS_TYPE_DRIVER hiResImageRequestTypeDriver = {
        "hiResImageRequest", 
        (NDDS_REGISTER_HANDLER)  hiResImageRequestNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  hiResImageRequestAllocate, 
        (NDDS_FREE_HANDLER)      hiResImageRequestFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_hiResImageRequest , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_hiResImageRequest , 
        NULL, 
        NULL 
}; 

#include "hiResImageSelection.h"
#include "hiResImageSelection_tclndds.h"
NDDS_TYPE_DRIVER hiResImageSelectionTypeDriver = {
        "hiResImageSelection", 
        (NDDS_REGISTER_HANDLER)  hiResImageSelectionNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  hiResImageSelectionAllocate, 
        (NDDS_FREE_HANDLER)      hiResImageSelectionFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_hiResImageSelection , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_hiResImageSelection , 
        NULL, 
        NULL 
}; 

/* spectrometer messages */

#include "specCommand.h"
#include "specCommand_tclndds.h"
NDDS_TYPE_DRIVER specCommandTypeDriver = {
        "specCommand", 
        (NDDS_REGISTER_HANDLER)  specCommandNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  specCommandAllocate, 
        (NDDS_FREE_HANDLER)      specCommandFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_specCommand , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_specCommand , 
        NULL, 
        NULL 
}; 

#include "specReply.h"
#include "specReply_tclndds.h"
NDDS_TYPE_DRIVER specReplyTypeDriver = {
        "specReply", 
        (NDDS_REGISTER_HANDLER)  specReplyNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  specReplyAllocate, 
        (NDDS_FREE_HANDLER)      specReplyFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_specReply , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_specReply , 
        NULL, 
        NULL 
}; 

/* panoramic messages */

#include "panoramicImage.h"
#include "panoramicImage_tclndds.h"
NDDS_TYPE_DRIVER panoramicImageTypeDriver = {
        "panoramicImage", 
        (NDDS_REGISTER_HANDLER)  panoramicImageNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  panoramicImageAllocate, 
        (NDDS_FREE_HANDLER)      panoramicImageFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_panoramicImage , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_panoramicImage , 
        NULL, 
        NULL 
}; 

#include "panoramicImageReq.h"
#include "panoramicImageReq_tclndds.h"
NDDS_TYPE_DRIVER panoramicImageReqTypeDriver = {
        "panoramicImageReq", 
        (NDDS_REGISTER_HANDLER)  panoramicImageReqNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  panoramicImageReqAllocate, 
        (NDDS_FREE_HANDLER)      panoramicImageReqFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_panoramicImageReq , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_panoramicImageReq , 
        NULL, 
        NULL 
}; 


/* database messages */

#include "dbDatabaseRequest.h"
#include "dbDatabaseRequest_tclndds.h"
NDDS_TYPE_DRIVER dbDatabaseRequestTypeDriver = {
        "dbDatabaseRequest", 
        (NDDS_REGISTER_HANDLER)  dbDatabaseRequestNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  dbDatabaseRequestAllocate, 
        (NDDS_FREE_HANDLER)      dbDatabaseRequestFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_dbDatabaseRequest , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_dbDatabaseRequest , 
        NULL, 
        NULL 
}; 

#include "dbFieldReply.h"
#include "dbFieldReply_tclndds.h"
NDDS_TYPE_DRIVER dbFieldReplyTypeDriver = {
        "dbFieldReply", 
        (NDDS_REGISTER_HANDLER)  dbFieldReplyNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  dbFieldReplyAllocate, 
        (NDDS_FREE_HANDLER)      dbFieldReplyFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_dbFieldReply , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_dbFieldReply , 
        NULL, 
        NULL 
}; 

#include "dbIDListReply.h"
#include "dbIDListReply_tclndds.h"
NDDS_TYPE_DRIVER dbIDListReplyTypeDriver = {
        "dbIDListReply", 
        (NDDS_REGISTER_HANDLER)  dbIDListReplyNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  dbIDListReplyAllocate, 
        (NDDS_FREE_HANDLER)      dbIDListReplyFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_dbIDListReply , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_dbIDListReply , 
        NULL, 
        NULL 
}; 

#include "dbNotify.h"
#include "dbNotify_tclndds.h"
NDDS_TYPE_DRIVER dbNotifyTypeDriver = {
        "dbNotify", 
        (NDDS_REGISTER_HANDLER)  dbNotifyNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  dbNotifyAllocate, 
        (NDDS_FREE_HANDLER)      dbNotifyFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_dbNotify , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_dbNotify , 
        NULL, 
        NULL 
}; 

#include "dbRecordReply.h"
#include "dbRecordReply_tclndds.h"
NDDS_TYPE_DRIVER dbRecordReplyTypeDriver = {
        "dbRecordReply", 
        (NDDS_REGISTER_HANDLER)  dbRecordReplyNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  dbRecordReplyAllocate, 
        (NDDS_FREE_HANDLER)      dbRecordReplyFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_dbRecordReply , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_dbRecordReply , 
        NULL, 
        NULL 
}; 

/* mission planner messages */

#include "mpUpdateSettings.h"
#include "mpUpdateSettings_tclndds.h"
NDDS_TYPE_DRIVER mpUpdateSettingsTypeDriver = {
        "mpUpdateSettings", 
        (NDDS_REGISTER_HANDLER)  mpUpdateSettingsNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  mpUpdateSettingsAllocate, 
        (NDDS_FREE_HANDLER)      mpUpdateSettingsFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_mpUpdateSettings , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_mpUpdateSettings , 
        NULL, 
        NULL 
}; 

#include "mpSensorStatus.h"
#include "mpSensorStatus_tclndds.h"
NDDS_TYPE_DRIVER mpSensorStatusTypeDriver = {
        "mpSensorStatus", 
        (NDDS_REGISTER_HANDLER)  mpSensorStatusNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  mpSensorStatusAllocate, 
        (NDDS_FREE_HANDLER)      mpSensorStatusFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_mpSensorStatus , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_mpSensorStatus , 
        NULL, 
        NULL 
}; 

#include "mpNavPlannerStatus.h"
#include "mpNavPlannerStatus_tclndds.h"
NDDS_TYPE_DRIVER mpNavPlannerStatusTypeDriver = {
        "mpNavPlannerStatus", 
        (NDDS_REGISTER_HANDLER)  mpNavPlannerStatusNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  mpNavPlannerStatusAllocate, 
        (NDDS_FREE_HANDLER)      mpNavPlannerStatusFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_mpNavPlannerStatus , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_mpNavPlannerStatus , 
        NULL, 
        NULL 
}; 


/***** Nav commands *****/

#include "navSettings.h"
#include "navSettings_tclndds.h"
NDDS_TYPE_DRIVER navSettingsTypeDriver = {
        "navSettings", 
        (NDDS_REGISTER_HANDLER)  navSettingsNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  navSettingsAllocate, 
        (NDDS_FREE_HANDLER)      navSettingsFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_navSettings , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_navSettings , 
        NULL, 
        NULL 
}; 

#include "navEnable.h"
#include "navEnable_tclndds.h"
NDDS_TYPE_DRIVER navEnableTypeDriver = {
        "navEnable", 
        (NDDS_REGISTER_HANDLER)  navEnableNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  navEnableAllocate, 
        (NDDS_FREE_HANDLER)      navEnableFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_navEnable , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_navEnable , 
        NULL, 
        NULL 
}; 

#include "navHeading.h"
#include "navHeading_tclndds.h"
NDDS_TYPE_DRIVER navHeadingTypeDriver = {
        "navHeading", 
        (NDDS_REGISTER_HANDLER)  navHeadingNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  navHeadingAllocate, 
        (NDDS_FREE_HANDLER)      navHeadingFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_navHeading , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_navHeading , 
        NULL, 
        NULL 
}; 


#include "navPath.h"
#include "navPath_tclndds.h"
NDDS_TYPE_DRIVER navPathTypeDriver = {
        "navPath", 
        (NDDS_REGISTER_HANDLER)  navPathNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  navPathAllocate, 
        (NDDS_FREE_HANDLER)      navPathFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_navPath , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_navPath , 
        NULL, 
        NULL 
};
 

/*
 *#include "navTurn.h"
 *#include "navTurn_tclndds.h"
 *NDDS_TYPE_DRIVER navTurnTypeDriver = {
 *        "navTurn", 
 *        (NDDS_REGISTER_HANDLER)  navTurnNddsRegister, 
 *        (NDDS_ALLOCATE_HANDLER)  navTurnAllocate, 
 *        (NDDS_FREE_HANDLER)      navTurnFree, 
 *        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_navTurn , 
 *        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_navTurn , 
 *        NULL, 
 *        NULL 
 *}; 
 */



/***** Science messages *****/

#include "weatherState.h"
#include "weatherState_tclndds.h"
NDDS_TYPE_DRIVER weatherStateTypeDriver = {
        "weatherState", 
        (NDDS_REGISTER_HANDLER)  weatherStateNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  weatherStateAllocate, 
        (NDDS_FREE_HANDLER)      weatherStateFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_weatherState , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_weatherState , 
        NULL, 
        NULL 
};

#include "sciControl.h"
#include "sciControl_tclndds.h"
NDDS_TYPE_DRIVER sciControlTypeDriver = {
        "sciControl", 
        (NDDS_REGISTER_HANDLER)  sciControlNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  sciControlAllocate, 
        (NDDS_FREE_HANDLER)      sciControlFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_sciControl , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_sciControl , 
        NULL, 
        NULL 
};

#include "sciMosaic.h"
#include "sciMosaic_tclndds.h"
NDDS_TYPE_DRIVER sciMosaicTypeDriver = {
        "sciMosaic", 
        (NDDS_REGISTER_HANDLER)  sciMosaicNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  sciMosaicAllocate, 
        (NDDS_FREE_HANDLER)      sciMosaicFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_sciMosaic , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_sciMosaic , 
        NULL, 
        NULL 
};

#include "sciPanTilt.h"
#include "sciPanTilt_tclndds.h"
NDDS_TYPE_DRIVER sciPanTiltTypeDriver = {
        "sciPanTilt", 
        (NDDS_REGISTER_HANDLER)  sciPanTiltNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  sciPanTiltAllocate, 
        (NDDS_FREE_HANDLER)      sciPanTiltFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_sciPanTilt , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_sciPanTilt , 
        NULL, 
        NULL 
};

#include "sciSequence.h"
#include "sciSequence_tclndds.h"
NDDS_TYPE_DRIVER sciSequenceTypeDriver = {
        "sciSequence", 
        (NDDS_REGISTER_HANDLER)  sciSequenceNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  sciSequenceAllocate, 
        (NDDS_FREE_HANDLER)      sciSequenceFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_sciSequence , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_sciSequence , 
        NULL, 
        NULL 
};

#include "sciSnap.h"
#include "sciSnap_tclndds.h"
NDDS_TYPE_DRIVER sciSnapTypeDriver = {
        "sciSnap", 
        (NDDS_REGISTER_HANDLER)  sciSnapNddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  sciSnapAllocate, 
        (NDDS_FREE_HANDLER)      sciSnapFree, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_sciSnap , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_sciSnap , 
        NULL, 
        NULL 
};

#if 0 /*********  BLANK TEMPLATE *********/

#include ".h"
#include "_tclndds.h"
NDDS_TYPE_DRIVER TypeDriver = {
        "", 
        (NDDS_REGISTER_HANDLER)  NddsRegister, 
        (NDDS_ALLOCATE_HANDLER)  Allocate, 
        (NDDS_FREE_HANDLER)      Free, 
        (NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_ , 
        (NDDS_TO_TCL_HANDLER)    Ndds2Tcl_ , 
        NULL, 
        NULL 
}; 
#endif

