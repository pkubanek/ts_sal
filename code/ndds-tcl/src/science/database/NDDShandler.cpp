#include "Database.h"
#include "NDDShandler.h"
#include "Interface.h"
#include "dbTypes.h"
#include "dbFieldNames.h"
#include "dbFunctionNames.h"
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "nomadNddsDomain.h"


//*******************************//
//***   global declarations   ***//
NDDSProducer		fieldReplyProd, listReplyProd;
NDDSProducer		recordReplyProd, notifyProd;
NDDSConsumer		DatabaseCons;
dbFieldReplyStruct	fieldReply;
dbIDListReplyStruct	listReply;
dbRecordReplyStruct	recordReply;
dbNotifyStruct		notify;



/***********************************************************************
function:	dbRequestCallback
created:	12 AUG 98
author:		Lenny Delligatti

description:

Parameters: 
Globals:
I/O:
Limitations:

Change History:

  date   name		description
--------------------------------------------------------------------
8/12/98	 Lenny		Created	-- skeleton 
8/29/98  Lenny      Modified for NDDS
***********************************************************************/
NDDSObjectInstance dbRequestCallback (NDDSUpdateInfo dbUpdate) {
  dbDatabaseRequest request;
  int	status;
  int	length;

  //extract request message from update packet
  request = (dbDatabaseRequest) dbUpdate->instance;

  //check that data received has not been seen already
  if (dbUpdate->updateStatus == NDDS_FRESH_DATA) {
	//initializing replyStatus fields
	fieldReply.replyStatus = DB_OK;
	listReply.replyStatus = DB_OK;
	recordReply.replyStatus = DB_OK;

	//switch on requested function to be performed by database
	switch (request->function) {
	  case INSERT_FUNCTION:
		  listReply.replyDestination = request->requestSource;
		  listReply.replyStatus = DB_OK;
		  *(listReply.targetIDs) = db.insert();
		  listReply.numTargetIDs = 1;
		  NddsProducerSample(listReplyProd);
	    break;

	  case GET_FIELD_FUNCTION:
		  fieldReply.replyDestination = request->requestSource;
		  fieldReply.targetID = request->targetID;
		  fieldReply.fieldName = request->fieldName;
		  switch (request->fieldName) {
			case TARGET_ID_FIELD:
			case HI_RES_IMAGE_TARGET_COORD_FIELD:
				fieldReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(fieldReply.int_len),(char *)fieldReply.int_data);
		      break;
			
			case GPS_POSITION_FIELD:
			case CLASS_RISK_FIELD:
			case CLASS_EST_INFO_GAIN_FIELD:
			case CLASS_MEMBER_PROB_FIELD:
			case HI_RES_IMAGE_SCALING_FACTOR_FIELD:
				fieldReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(fieldReply.float_len),(char *)fieldReply.float_data);
			  break;

			case CURRENTLY_TRACKED_FIELD:
			case TEMPLATE_IMAGE_FIELD:
			case HI_RES_IMAGE_FIELD:
			case METAL_DETECTOR_DATA_FIELD:
			case MAGNETOMETER_DATA_FIELD:
			case RADAR_DATA_FIELD:
			case CLASSIFIER_OUTPUT_DATA_FIELD:
			case SPECTROMETER_DATA_FIELD:
			case CLASS_ACTIVE_FIELD:
				fieldReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(fieldReply.char_len),fieldReply.char_data);
				if (fieldReply.replyStatus == DB_DEFAULT_FIELD_DATA)
					 *(fieldReply.char_data) = DB_CHAR_DEFAULT_DATA;
			  break;

			default: fieldReply.replyStatus = DB_INVALID_FIELD_NAME;
		  }//end of switch statement

		  NddsProducerSample(fieldReplyProd);
		  #ifdef COUT
		  print_reply_message(fieldReply);  //send off reply message
		  #endif
		break;

	  case GET_RECORD_FUNCTION:
		  recordReply.replyStatus = DB_OK;
		  recordReply.replyDestination = request->requestSource;
		  recordReply.targetID = request->targetID;

		  //fill up data fields of reply message
		  if ((status = db.lookup(request->targetID,GPS_POSITION_FIELD,&length,(char *)recordReply.GPS_Position)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CURRENTLY_TRACKED_FIELD,&length,(char *)&(recordReply.currentlyTracked))) != DB_OK) 
			        recordReply.replyStatus = status;

		  if ((status = db.lookup(request->targetID,TEMPLATE_IMAGE_FIELD,&length,(char *)recordReply.templateImage)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(recordReply.templateImage) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,HI_RES_IMAGE_FIELD,&length,(char *)recordReply.hiResImage)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(recordReply.hiResImage) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,METAL_DETECTOR_DATA_FIELD,&length,(char *)recordReply.metalDetectorData)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(recordReply.metalDetectorData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,MAGNETOMETER_DATA_FIELD,&length,(char *)recordReply.magnetometerData)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(recordReply.magnetometerData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,RADAR_DATA_FIELD,&length,(char *)recordReply.radarData)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(recordReply.radarData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,CLASSIFIER_OUTPUT_DATA_FIELD,&length,(char *)recordReply.classifierOutputData)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(recordReply.classifierOutputData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,SPECTROMETER_DATA_FIELD,&length,(char *)recordReply.spectrometerData)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(recordReply.spectrometerData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,HI_RES_IMAGE_TARGET_COORD_FIELD,&length,(char *)recordReply.hiResImageTargetCoord)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,HI_RES_IMAGE_SCALING_FACTOR_FIELD,&length,(char *)recordReply.hiResImageScalingFactor)) != DB_OK)
			        recordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CLASS_RISK_FIELD,&length,(char *)&(recordReply.classRisk))) != DB_OK) 
			        recordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CLASS_EST_INFO_GAIN_FIELD,&length,(char *)recordReply.classEstInfoGain)) != DB_OK) 
			        recordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CLASS_ACTIVE_FIELD,&length,(char *)&(recordReply.classActive))) != DB_OK) 
			        recordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CLASS_MEMBER_PROB_FIELD,&length,(char *)recordReply.classMemberProb)) != DB_OK)
			        recordReply.replyStatus = status;

		  NddsProducerSample(recordReplyProd);
		  #ifdef COUT
		  print_record_message(recordReply);
		  #endif
		break;  

	  case PUT_FIELD_FUNCTION:
		  //prepare a notify message for the classifier
		  notify.targetID = request->targetID;
		  notify.fieldName = request->fieldName;

		  //prepare a fieldReply message for the updating client
		  fieldReply.replyDestination = request->requestSource;
		  fieldReply.targetID = request->targetID;
		  fieldReply.fieldName = request->fieldName;
		  memcpy(fieldReply.int_data, request->int_data, INT_ARRAY_SIZE);
		  fieldReply.int_len = request->int_len;
		  memcpy(fieldReply.float_data, request->float_data, FLOAT_ARRAY_SIZE);
		  fieldReply.float_len = request->float_len;
		  memcpy(fieldReply.char_data, request->char_data, CHAR_ARRAY_SIZE);
		  fieldReply.char_len = request->char_len;

		  switch (request->fieldName) {
			case TARGET_ID_FIELD:
			case HI_RES_IMAGE_TARGET_COORD_FIELD:
				fieldReply.replyStatus = 
				     db.update(request->targetID,request->fieldName,request->int_len,(char *)request->int_data);
		      break;
			
			case GPS_POSITION_FIELD:
			case CLASS_RISK_FIELD:
			case CLASS_EST_INFO_GAIN_FIELD:
			case CLASS_MEMBER_PROB_FIELD:
			case HI_RES_IMAGE_SCALING_FACTOR_FIELD:
				fieldReply.replyStatus = 
				     db.update(request->targetID,request->fieldName,request->float_len,(char *)request->float_data);
			  break;

			case CURRENTLY_TRACKED_FIELD:
			case TEMPLATE_IMAGE_FIELD:
			case HI_RES_IMAGE_FIELD:
			case METAL_DETECTOR_DATA_FIELD:
			case MAGNETOMETER_DATA_FIELD:
			case RADAR_DATA_FIELD:
			case CLASSIFIER_OUTPUT_DATA_FIELD:
			case SPECTROMETER_DATA_FIELD:
			case CLASS_ACTIVE_FIELD:
				fieldReply.replyStatus = 
					db.update(request->targetID,request->fieldName,request->char_len,request->char_data);
			  break;

			default: fieldReply.replyStatus = DB_INVALID_FIELD_NAME;
		  }//end of switch statement

		  NddsProducerSample(notifyProd);
		  NddsProducerSample(fieldReplyProd);
		  #ifdef COUT
		  print_reply_message(fieldReply);  //send off reply message
		  #endif
		break;

	  //first lookup up search value using ID as search key		
	  case SEARCH_ID_FUNCTION:
		  switch (request->fieldName) {
			case HI_RES_IMAGE_TARGET_COORD_FIELD:
				listReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(request->int_len),(char *)request->int_data);
		      break;
			
			case GPS_POSITION_FIELD:
				listReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(request->float_len),(char *)request->float_data);
			  break;

			case CURRENTLY_TRACKED_FIELD:
			case CLASS_ACTIVE_FIELD:
				listReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(request->char_len),request->char_data);
			  break;

			default: listReply.replyStatus = DB_INVALID_FIELD_NAME;
		  }//end of switch statement

	  //use search value provided in message to perform appropriate search
	  case SEARCH_FUNCTION:
		  listReply.replyDestination = request->requestSource;
		  if (listReply.replyStatus == DB_OK) {
		    switch (request->fieldName) {
		      case GPS_POSITION_FIELD:
			  	  listReply.replyStatus =
				  	  db.search(request->fieldName,(char *)(request->float_data),request->numResults,listReply.targetIDs,&(listReply.numTargetIDs));		  
			    break;

			  case CURRENTLY_TRACKED_FIELD:
			  case CLASS_ACTIVE_FIELD:
				  listReply.replyStatus =
					  db.search(request->fieldName,request->char_data,request->numResults,listReply.targetIDs,&(listReply.numTargetIDs));		  
			    break;

			  default:  listReply.replyStatus = DB_INVALID_FIELD_NAME;
			}//end of switch statement
		  }//end of if statement 

		  NddsProducerSample(listReplyProd);
		  #ifdef COUT
		  print_list_message(listReply);
		  #endif
		break;

	  case SAVE_FUNCTION:
		  listReply.replyDestination = request->requestSource;
		  listReply.replyStatus = db.save();
		  NddsProducerSample(listReplyProd);
		break;

	  case LOAD_FUNCTION:
		  listReply.replyDestination = request->requestSource;
		  listReply.replyStatus = db.load();
		  NddsProducerSample(listReplyProd);
		break;

	  default:  cout << "** Callback:  Illegal function! **\n";
	}//end of switch statement
  }//end of if statement

  //old data has been received
  else cout << "**  Error:  Old data has been received!  **\n";

  return dbUpdate->instance;
}//end of function dbRequestCallback




/***********************************************************************
function:	FakeCallback
created:	29 AUG 98
author:		Lenny Delligatti

description:

Parameters: 
Globals:
I/O:
Limitations:

Change History:

  date   name		description
--------------------------------------------------------------------
8/12/98	 Lenny		Created

***********************************************************************/
void FakeCallback (dbDatabaseRequest request) {
  dbFieldReplyStruct	fakeFieldReply;
  dbIDListReplyStruct	fakeListReply;
  dbRecordReplyStruct	fakeRecordReply;
  int	status;
  int	length;


	//initializing replyStatus fields
	fakeFieldReply.replyStatus = DB_OK;
	fakeListReply.replyStatus = DB_OK;
	fakeRecordReply.replyStatus = DB_OK;

	switch (request->function) {
	  case INSERT_FUNCTION:
		  fakeListReply.replyDestination = request->requestSource;
		  fakeListReply.replyStatus = DB_OK;
		  *(fakeListReply.targetIDs) = db.insert();
		  fakeListReply.numTargetIDs = 1;
		  print_list_message(fakeListReply);
	    break;

	  case GET_FIELD_FUNCTION:
		  fakeFieldReply.replyDestination = request->requestSource;
		  fakeFieldReply.targetID = request->targetID;
		  fakeFieldReply.fieldName = request->fieldName;
		  switch (request->fieldName) {
			case TARGET_ID_FIELD:
			case HI_RES_IMAGE_TARGET_COORD_FIELD:
				fakeFieldReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(fakeFieldReply.int_len),(char *)fakeFieldReply.int_data);
		      break;
			
			case GPS_POSITION_FIELD:
			case CLASS_RISK_FIELD:
			case CLASS_EST_INFO_GAIN_FIELD:
			case CLASS_MEMBER_PROB_FIELD:
			case HI_RES_IMAGE_SCALING_FACTOR_FIELD:
				fakeFieldReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(fakeFieldReply.float_len),(char *)fakeFieldReply.float_data);
			  break;

			case CURRENTLY_TRACKED_FIELD:
			case TEMPLATE_IMAGE_FIELD:
			case HI_RES_IMAGE_FIELD:
			case METAL_DETECTOR_DATA_FIELD:
			case MAGNETOMETER_DATA_FIELD:
			case RADAR_DATA_FIELD:
			case CLASSIFIER_OUTPUT_DATA_FIELD:
			case SPECTROMETER_DATA_FIELD:
			case CLASS_ACTIVE_FIELD:
				fakeFieldReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(fakeFieldReply.char_len),fakeFieldReply.char_data);
				if (fakeFieldReply.replyStatus == DB_DEFAULT_FIELD_DATA)
					 *(fakeFieldReply.char_data) = DB_CHAR_DEFAULT_DATA;
			  break;

			default: fakeFieldReply.replyStatus = DB_INVALID_FIELD_NAME;
		  }//end of switch statement

		  print_reply_message(fakeFieldReply);  //send off reply message
		break;

	  case GET_RECORD_FUNCTION:
		  fakeRecordReply.replyStatus = DB_OK;
		  fakeRecordReply.replyDestination = request->requestSource;
		  fakeRecordReply.targetID = request->targetID;

		  //fill up data fields of reply message
		  if ((status = db.lookup(request->targetID,GPS_POSITION_FIELD,&length,(char *)fakeRecordReply.GPS_Position)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CURRENTLY_TRACKED_FIELD,&length,(char *)&(fakeRecordReply.currentlyTracked))) != DB_OK) 
			        fakeRecordReply.replyStatus = status;

		  if ((status = db.lookup(request->targetID,TEMPLATE_IMAGE_FIELD,&length,(char *)fakeRecordReply.templateImage)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(fakeRecordReply.templateImage) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,HI_RES_IMAGE_FIELD,&length,(char *)fakeRecordReply.hiResImage)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(fakeRecordReply.hiResImage) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,METAL_DETECTOR_DATA_FIELD,&length,(char *)fakeRecordReply.metalDetectorData)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(fakeRecordReply.metalDetectorData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,MAGNETOMETER_DATA_FIELD,&length,(char *)fakeRecordReply.magnetometerData)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(fakeRecordReply.magnetometerData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,RADAR_DATA_FIELD,&length,(char *)fakeRecordReply.radarData)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(fakeRecordReply.radarData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,CLASSIFIER_OUTPUT_DATA_FIELD,&length,(char *)fakeRecordReply.classifierOutputData)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(fakeRecordReply.classifierOutputData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,SPECTROMETER_DATA_FIELD,&length,(char *)fakeRecordReply.spectrometerData)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if (status == DB_DEFAULT_FIELD_DATA)  *(fakeRecordReply.spectrometerData) = DB_CHAR_DEFAULT_DATA;

		  if ((status = db.lookup(request->targetID,HI_RES_IMAGE_TARGET_COORD_FIELD,&length,(char *)fakeRecordReply.hiResImageTargetCoord)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,HI_RES_IMAGE_SCALING_FACTOR_FIELD,&length,(char *)fakeRecordReply.hiResImageScalingFactor)) != DB_OK)
					fakeRecordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CLASS_RISK_FIELD,&length,(char *)&(fakeRecordReply.classRisk))) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CLASS_EST_INFO_GAIN_FIELD,&length,(char *)fakeRecordReply.classEstInfoGain)) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CLASS_ACTIVE_FIELD,&length,(char *)&(fakeRecordReply.classActive))) != DB_OK) 
			        fakeRecordReply.replyStatus = status;
		  if ((status = db.lookup(request->targetID,CLASS_MEMBER_PROB_FIELD,&length,(char *)fakeRecordReply.classMemberProb)) != DB_OK)
			        fakeRecordReply.replyStatus = status;
		  print_record_message(fakeRecordReply);
		break;  

	  case PUT_FIELD_FUNCTION:
		  //prepare notify message for classifier
		  notify.targetID = request->targetID;
		  notify.fieldName = request->fieldName;

		  //prepare a fakeFieldReply message for the updating client
		  fakeFieldReply.replyDestination = request->requestSource;
		  fakeFieldReply.targetID = request->targetID;
		  fakeFieldReply.fieldName = request->fieldName;
		  memcpy(fakeFieldReply.int_data, request->int_data, INT_ARRAY_SIZE);
		  fakeFieldReply.int_len = request->int_len;
		  memcpy(fakeFieldReply.float_data, request->float_data, FLOAT_ARRAY_SIZE);
		  fakeFieldReply.float_len = request->float_len;
		  memcpy(fakeFieldReply.char_data, request->char_data, CHAR_ARRAY_SIZE);
		  fakeFieldReply.char_len = request->char_len;

		  switch (request->fieldName) {
			case TARGET_ID_FIELD:
			case HI_RES_IMAGE_TARGET_COORD_FIELD:
				fakeFieldReply.replyStatus = 
				     db.update(request->targetID,request->fieldName,request->int_len,(char *)request->int_data);
		      break;
			
			case GPS_POSITION_FIELD:
			case CLASS_RISK_FIELD:
			case CLASS_EST_INFO_GAIN_FIELD:
			case CLASS_MEMBER_PROB_FIELD:
			case HI_RES_IMAGE_SCALING_FACTOR_FIELD:
				fakeFieldReply.replyStatus = 
				     db.update(request->targetID,request->fieldName,request->float_len,(char *)request->float_data);
			  break;

			case CURRENTLY_TRACKED_FIELD:
			case TEMPLATE_IMAGE_FIELD:
			case HI_RES_IMAGE_FIELD:
			case METAL_DETECTOR_DATA_FIELD:
			case MAGNETOMETER_DATA_FIELD:
			case RADAR_DATA_FIELD:
			case CLASSIFIER_OUTPUT_DATA_FIELD:
			case SPECTROMETER_DATA_FIELD:
			case CLASS_ACTIVE_FIELD:
				fakeFieldReply.replyStatus = 
					db.update(request->targetID,request->fieldName,request->char_len,request->char_data);
			  break;

			default: fakeFieldReply.replyStatus = DB_INVALID_FIELD_NAME;
		  }//end of switch statement

		  if (fakeFieldReply.replyStatus == DB_OK) NddsProducerSample(notifyProd);
		  print_reply_message(fakeFieldReply);  //send off reply message
		break;

	  //first lookup up search value using ID as search key		
	  case SEARCH_ID_FUNCTION:
		  switch (request->fieldName) {
			case HI_RES_IMAGE_TARGET_COORD_FIELD:
				fakeListReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(request->int_len),(char *)request->int_data);
		      break;
			
			case GPS_POSITION_FIELD:
				fakeListReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(request->float_len),(char *)request->float_data);
			  break;

			case CURRENTLY_TRACKED_FIELD:
			case CLASS_ACTIVE_FIELD:
				fakeListReply.replyStatus = 
				     db.lookup(request->targetID,request->fieldName,&(request->char_len),request->char_data);
			  break;

			default: fakeListReply.replyStatus = DB_INVALID_FIELD_NAME;
		  }//end of switch statement

	  //use search value provided in message to perform appropriate search
	  case SEARCH_FUNCTION:
		  fakeListReply.replyDestination = request->requestSource;
		  if (fakeListReply.replyStatus == DB_OK) {
		    switch (request->fieldName) {
		      case GPS_POSITION_FIELD:
			  	  fakeListReply.replyStatus =
				  	  db.search(request->fieldName,(char *)(request->float_data),request->numResults,fakeListReply.targetIDs,&(fakeListReply.numTargetIDs));		  
			    break;

			  case CURRENTLY_TRACKED_FIELD:
			  case CLASS_ACTIVE_FIELD:
				  fakeListReply.replyStatus =
					  db.search(request->fieldName,request->char_data,request->numResults,fakeListReply.targetIDs,&(fakeListReply.numTargetIDs));		  
			    break;

			  default:  fakeListReply.replyStatus = DB_INVALID_FIELD_NAME;
			}//end of switch statement
		  }//end of if statement 

		  print_list_message(fakeListReply);
		break;

	  case SAVE_FUNCTION:
		  fakeListReply.replyDestination = request->requestSource;
		  fakeListReply.replyStatus = db.save();
		  switch(fakeListReply.replyStatus) {
			case DB_OK:  cout << "** Database saved! **\n";
				break;							  
			case DB_FILE_ERROR:  cout << "** Error in creating save file! **\n";
				break;
			default:  cout << "** Unknown error during save! **\n";				
		  }//end of switch statement
		break;

	  case LOAD_FUNCTION:
		  fakeListReply.replyDestination = request->requestSource;
		  fakeListReply.replyStatus = db.load();
		  switch(fakeListReply.replyStatus) {
			case DB_OK:  cout << "** Database loaded! **\n";
				break;							  
			case DB_FILE_ERROR:  cout << "** Error in accessing save file! **\n";
				break;
			case DB_OLD_SAVE_FILE:  
				cout <<"** Load failed:  Database changed since last save! **\n";
				break;
			default:  cout << "** Unknown error during save! **\n";				
		  }//end of switch statement
		break;

	  default:  cout << "** Callback:  Illegal function! **\n";
	}//end of switch statement
}//end of function FakeCallback



#ifdef NDDS
void consumerSetup(void) {

  // create consumer 
  DatabaseCons = NddsConsumerCreate("DatabaseCons", NDDS_IMMEDIATE_RELIABLE, 1000000.0, 0.0);


  /*  uncomment this section when setting up consumer for polling

  NDDSConsumerPropertiesStorage properties;
  //set consumer receive queue size to 20 messages
  NddsConsumerPropertiesGet(DatabaseCons, &properties);
  properties.receiveQueueSize = DB_CONSUMER_QUEUE_SIZE;
  NddsConsumerPropertiesSet(DatabaseCons, &properties); */


  // register message 
  dbDatabaseRequestNddsRegister();

  // subscribe message to consumer 
  NddsConsumerSubscriptionAdd(DatabaseCons, DB_DATABASE_REQUEST_NAME,
	  DB_DATABASE_REQUEST_NAME, NULL, dbRequestCallback, NULL);
}//end of consumerSetup function


void producerSetup(void) {
  float persistence = 10.0;
  float strength = 10.0;

  // create producers 
  fieldReplyProd = NddsProducerCreate("fieldReply", NDDS_SYNCHRONOUS, persistence, strength);
  listReplyProd = NddsProducerCreate("listReply", NDDS_SYNCHRONOUS, persistence, strength);
  recordReplyProd = NddsProducerCreate("recordReply", NDDS_SYNCHRONOUS, persistence, strength);
  notifyProd = NddsProducerCreate("notify", NDDS_SYNCHRONOUS, persistence, strength);

  // register NDDS message types 
  dbIDListReplyNddsRegister();
  dbFieldReplyNddsRegister();
  dbRecordReplyNddsRegister();
  dbNotifyNddsRegister();

  // subscribe NDDS messages to producers 
  NddsProducerProductionAdd(fieldReplyProd, DB_FIELD_REPLY_NAME, DB_FIELD_REPLY_NAME, &fieldReply, 0, NULL, NULL);
  NddsProducerProductionAdd(listReplyProd, DB_ID_LIST_REPLY_NAME, DB_ID_LIST_REPLY_NAME, &listReply, 0, NULL, NULL);
  NddsProducerProductionAdd(recordReplyProd, DB_RECORD_REPLY_NAME, DB_RECORD_REPLY_NAME, &recordReply, 0, NULL, NULL);
  NddsProducerProductionAdd(notifyProd, DB_NOTIFY_NAME, DB_NOTIFY_NAME, &notify, 0, NULL, NULL);
}//end of producerSetup function

#endif


