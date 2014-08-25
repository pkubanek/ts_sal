#ifndef _NDDShandler_
#define _NDDShandler_

#include "NDDS.h"
#include "dbMessageNames.h"
#include "dbDatabaseRequest.h"
#include "dbFieldReply.h"
#include "dbIDListReply.h"
#include "dbRecordReply.h"
#include "dbNotify.h"


#define INT_ARRAY_SIZE 250
#define FLOAT_ARRAY_SIZE 250
#define CHAR_ARRAY_SIZE 1500
#define DB_CONSUMER_QUEUE_SIZE 20



#define NDDS		//uncomment when communicating via NDDS
//#define DEBUG		//uncomment for verbose output during development
//#define COUT		//uncomment to echo op. status to database console
					//when communicating via NDDS



//*************************//
//***  global externs   ***//
extern NDDSConsumer		DatabaseCons;


//*************************************//
//***  function prototypes  ***//
void FakeCallback (dbDatabaseRequest);
NDDSObjectInstance dbRequestCallback (NDDSUpdateInfo);
#ifdef NDDS
void consumerSetup(void);
void producerSetup(void);
#endif



#endif