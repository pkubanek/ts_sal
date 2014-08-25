void NddsWishRegisterAllTypes (void) {
    int new;	/* new is set to 0 if entry already existed */
    Tcl_HashEntry *hPtr;

    Tcl_InitHashTable (typeRegistry, TCL_STRING_KEYS);

/*
 *    hPtr = Tcl_CreateHashEntry (typeRegistry, "error", &new);
 *    Tcl_SetHashValue (hPtr, &errorTypeDriver);
 *    errorTypeDriver.init();
 */

/***** Common messages ******/
    
    hPtr = Tcl_CreateHashEntry (typeRegistry, "reset", &new);
    Tcl_SetHashValue (hPtr, &resetTypeDriver);
    resetTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "move", &new);
    Tcl_SetHashValue (hPtr, &moveTypeDriver);
    moveTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "event", &new);
    Tcl_SetHashValue (hPtr, &eventTypeDriver);
    eventTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "info", &new);
    Tcl_SetHashValue (hPtr, &infoTypeDriver);
    infoTypeDriver.init();

/***** Telemetry messages ******/    

    hPtr = Tcl_CreateHashEntry (typeRegistry, "apsDerivedState", &new);
    Tcl_SetHashValue (hPtr, &apsDerivedStateTypeDriver);
    apsDerivedStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "apsRawState", &new);
    Tcl_SetHashValue (hPtr, &apsRawStateTypeDriver);
    apsRawStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "arbInternalState", &new);
    Tcl_SetHashValue (hPtr, &arbInternalStateTypeDriver);
    arbInternalStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "bodDerivedState", &new);
    Tcl_SetHashValue (hPtr, &bodDerivedStateTypeDriver);
    bodDerivedStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "bodRawState", &new);
    Tcl_SetHashValue (hPtr, &bodRawStateTypeDriver);
    bodRawStateTypeDriver.init();

#if 0 /*left out pending implementation by mwm*/
    hPtr = Tcl_CreateHashEntry (typeRegistry, "epsDerivedState", &new);
    Tcl_SetHashValue (hPtr, &epsDerivedStateTypeDriver);
    epsDerivedStateTypeDriver.init();
#endif

    hPtr = Tcl_CreateHashEntry (typeRegistry, "gpsDerivedState", &new);
    Tcl_SetHashValue (hPtr, &gpsDerivedStateTypeDriver);
    gpsDerivedStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "gpsRawState", &new);
    Tcl_SetHashValue (hPtr, &gpsRawStateTypeDriver);
    gpsRawStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "imuDerivedState", &new);
    Tcl_SetHashValue (hPtr, &imuDerivedStateTypeDriver);
    imuDerivedStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "imuRawState", &new);
    Tcl_SetHashValue (hPtr, &imuRawStateTypeDriver);
    imuRawStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "kvhDerivedState", &new);
    Tcl_SetHashValue (hPtr, &kvhDerivedStateTypeDriver);
    kvhDerivedStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "lasHazardMap", &new);
    Tcl_SetHashValue (hPtr, &lasHazardMapTypeDriver);
    lasHazardMapTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "lasRawScanData", &new);
    Tcl_SetHashValue (hPtr, &lasRawScanDataTypeDriver);
    lasRawScanDataTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "morInternalState", &new);
    Tcl_SetHashValue (hPtr, &morInternalStateTypeDriver);
    morInternalStateTypeDriver.init();

/*
 *    hPtr = Tcl_CreateHashEntry (typeRegistry, "navWatchdogStatus", &new);
 *    Tcl_SetHashValue (hPtr, &navWatchdogStatusTypeDriver);
 *    navWatchdogStatusTypeDriver.init();
 */

    hPtr = Tcl_CreateHashEntry (typeRegistry, "posDerivedState", &new);
    Tcl_SetHashValue (hPtr, &posDerivedStateTypeDriver);
    posDerivedStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "posRawState", &new);
    Tcl_SetHashValue (hPtr, &posRawStateTypeDriver);
    posRawStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "steInternalState", &new);
    Tcl_SetHashValue (hPtr, &steInternalStateTypeDriver);
    steInternalStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "sysState", &new);
    Tcl_SetHashValue (hPtr, &sysStateTypeDriver);
    sysStateTypeDriver.init();

/***** Real time commands ******/
    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtChassisConfig", &new);
    Tcl_SetHashValue (hPtr, &rtChassisConfigTypeDriver);
    rtChassisConfigTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtDrive", &new);
    Tcl_SetHashValue (hPtr, &rtDriveTypeDriver);
    rtDriveTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtSetActuator", &new);
    Tcl_SetHashValue (hPtr, &rtSetActuatorTypeDriver);
    rtSetActuatorTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtSetBroadcastFreq", &new);
    Tcl_SetHashValue (hPtr, &rtSetBroadcastFreqTypeDriver);
    rtSetBroadcastFreqTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtSetParamFloat", &new);
    Tcl_SetHashValue (hPtr, &rtSetParamFloatTypeDriver);
    rtSetParamFloatTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtSetParamInt", &new);
    Tcl_SetHashValue (hPtr, &rtSetParamIntTypeDriver);
    rtSetParamIntTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtSetPosEstParams", &new);
    Tcl_SetHashValue (hPtr, &rtSetPosEstParamsTypeDriver);
    rtSetPosEstParamsTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtSetServoParams", &new);
    Tcl_SetHashValue (hPtr, &rtSetServoParamsTypeDriver);
    rtSetServoParamsTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtSignalCondition", &new);
    Tcl_SetHashValue (hPtr, &rtSignalConditionTypeDriver);
    rtSignalConditionTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtAmpState", &new);
    Tcl_SetHashValue (hPtr, &rtAmpStateTypeDriver);
    rtAmpStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtControlState", &new);
    Tcl_SetHashValue (hPtr, &rtControlStateTypeDriver);
    rtControlStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "rtEmergencySignals", &new);
    Tcl_SetHashValue (hPtr, &rtEmergencySignalsTypeDriver);
    rtEmergencySignalsTypeDriver.init();

/***** SAS commands *****/
    
    /* hiRes (pan/tilt) commands */

    hPtr = Tcl_CreateHashEntry (typeRegistry, "hiResImage", &new);
    Tcl_SetHashValue (hPtr, &hiResImageTypeDriver);
    hiResImageTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "hiResImageRequest", &new);
    Tcl_SetHashValue (hPtr, &hiResImageRequestTypeDriver);
    hiResImageRequestTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "hiResImageSelection", &new);
    Tcl_SetHashValue (hPtr, &hiResImageSelectionTypeDriver);
    hiResImageSelectionTypeDriver.init();
    
    /* spectrometer commands */

    hPtr = Tcl_CreateHashEntry (typeRegistry, "specCommand", &new);
    Tcl_SetHashValue (hPtr, &specCommandTypeDriver);
    specCommandTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "specReply", &new);
    Tcl_SetHashValue (hPtr, &specReplyTypeDriver);
    specReplyTypeDriver.init();

    /* panoramic commands */

    hPtr = Tcl_CreateHashEntry (typeRegistry, "panoramicImage", &new);
    Tcl_SetHashValue (hPtr, &panoramicImageTypeDriver);
    panoramicImageTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "panoramicImageReq", &new);
    Tcl_SetHashValue (hPtr, &panoramicImageReqTypeDriver);
    panoramicImageReqTypeDriver.init();    

    /* database commands */

    hPtr = Tcl_CreateHashEntry (typeRegistry, "dbDatabaseRequest", &new);
    Tcl_SetHashValue (hPtr, &dbDatabaseRequestTypeDriver);
    dbDatabaseRequestTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "dbFieldReply", &new);
    Tcl_SetHashValue (hPtr, &dbFieldReplyTypeDriver);
    dbFieldReplyTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "dbIDListReply", &new);
    Tcl_SetHashValue (hPtr, &dbIDListReplyTypeDriver);
    dbIDListReplyTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "dbNotify", &new);
    Tcl_SetHashValue (hPtr, &dbNotifyTypeDriver);
    dbNotifyTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "dbRecordReply", &new);
    Tcl_SetHashValue (hPtr, &dbRecordReplyTypeDriver);
    dbRecordReplyTypeDriver.init();

    /* mission planner commands */

    hPtr = Tcl_CreateHashEntry (typeRegistry, "mpUpdateSettings", &new);
    Tcl_SetHashValue (hPtr, &mpUpdateSettingsTypeDriver);
    mpUpdateSettingsTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "mpSensorStatus", &new);
    Tcl_SetHashValue (hPtr, &mpSensorStatusTypeDriver);
    mpSensorStatusTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "mpNavPlannerStatus", &new);
    Tcl_SetHashValue (hPtr, &mpNavPlannerStatusTypeDriver);
    mpNavPlannerStatusTypeDriver.init();


/***** Nav commands *****/
    
    hPtr = Tcl_CreateHashEntry (typeRegistry, "navEnable", &new);
    Tcl_SetHashValue (hPtr, &navEnableTypeDriver);
    navEnableTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "navHeading", &new);
    Tcl_SetHashValue (hPtr, &navHeadingTypeDriver);
    navHeadingTypeDriver.init();


    hPtr = Tcl_CreateHashEntry (typeRegistry, "navPath", &new);
    Tcl_SetHashValue (hPtr, &navPathTypeDriver);
    navPathTypeDriver.init();
 
    hPtr = Tcl_CreateHashEntry (typeRegistry, "navSettings", &new);
    Tcl_SetHashValue (hPtr, &navSettingsTypeDriver);
    navSettingsTypeDriver.init();

/*
 *    hPtr = Tcl_CreateHashEntry (typeRegistry, "navTurn", &new);
 *    Tcl_SetHashValue (hPtr, &navTurnTypeDriver);
 *    navTurnTypeDriver.init();
 */


/***** Science messages *****/    

    hPtr = Tcl_CreateHashEntry (typeRegistry, "weatherState", &new);
    Tcl_SetHashValue (hPtr, &weatherStateTypeDriver);
    weatherStateTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "sciControl", &new);
    Tcl_SetHashValue (hPtr, &sciControlTypeDriver);
    sciControlTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "sciMosaic", &new);
    Tcl_SetHashValue (hPtr, &sciMosaicTypeDriver);
    sciMosaicTypeDriver.init();

    hPtr = Tcl_CreateHashEntry (typeRegistry, "sciPanTilt", &new);
    Tcl_SetHashValue (hPtr, &sciPanTiltTypeDriver);
    sciPanTiltTypeDriver.init();    

    hPtr = Tcl_CreateHashEntry (typeRegistry, "sciSequence", &new);
    Tcl_SetHashValue (hPtr, &sciSequenceTypeDriver);
    sciSequenceTypeDriver.init();
    
    hPtr = Tcl_CreateHashEntry (typeRegistry, "sciSnap", &new);
    Tcl_SetHashValue (hPtr, &sciSnapTypeDriver);
    sciSnapTypeDriver.init();

#if 0   /***** BLANK TEMPLATE *****/

    hPtr = Tcl_CreateHashEntry (typeRegistry, "", &new);
    Tcl_SetHashValue (hPtr, &TypeDriver);
    TypeDriver.init();
#endif

    printf ("\n");

    return;
}
