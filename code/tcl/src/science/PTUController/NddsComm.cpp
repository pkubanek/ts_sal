#include "NDDS.h"

#include "hiResImage.h"
#include "hiResImageSelection.h"
#include "hiResImageRequest.h"
#include "hiResImageRequestRadians.h"
#include "hiResMessageNames.h"
#include <stdio.h>
#include "dbDatabaseRequest.h"
#include "dbFieldReply.h"
#include "dbIDListReply.h"
#include "dbFieldNames.h"
#include "dbMessageNames.h"

#include "posDerivedState.h"
#define  POS_DERIVED_STATE_NAME "posDerivedState"

#include "nomadNddsDomain.h"
#include "NddsComm.h"
#include "init.h"
#include "centreTarget.h"



/* Ndds consumer stuff */
NDDSProducer dbRequestProd, hiResImageProd;
dbIDListReplyStruct dbIDListMsg;
posDerivedStateStruct posDerivedStateMsg;

/* Ndds producer stuff */
dbDatabaseRequestStruct dbRequestMsg;
hiResImageStruct hiResImageMsg;

/* Write code for these three callback functions */
NDDSObjectInstance hiResImageRequestCallback (NDDSUpdateInfo req)
{
	char path[255] = "k:\\temp\\";
	char filename[255];
	hiResImageRequest msg = (hiResImageRequest)req->instance;
	printf("Received hiResImageRequest");

	if (req->updateStatus == NDDS_FRESH_DATA)
	{
		fprintf (stderr, "Got a new hiResImageRequest message.\n");
		printf ("Centering to row=%d col=%d\n", msg->row, msg->col);
		centreRowCol(msg->col, msg->row);
		sprintf (filename, "%s%s", path, "hires.ppm");
		fprintf (stderr, "Saving to file %s.\n", filename);
		savePPMImage(&Cam, 1, filename);	
		fprintf (stderr, "Done saving image to afs.\n");

		sprintf (filename, "%s%s", "/afs/cs/project/lri-7/temp/", "hires.ppm");
		strcpy (hiResImageMsg.filename, filename);
		hiResImageMsg.ptuAzimuth = 1.0;
		hiResImageMsg.ptuElevation = 1.0;
		hiResImageMsg.robot_dx = posDerivedStateMsg.posWest/100.0;
		hiResImageMsg.robot_dy = posDerivedStateMsg.posNorth/100.0;
		hiResImageMsg.robot_dz = posDerivedStateMsg.posUp/100.0;
		hiResImageMsg.robotAzimuth = posDerivedStateMsg.rotZ/100.0;
		hiResImageMsg.robotPitch = posDerivedStateMsg.rotX/100.0;
		hiResImageMsg.robotRoll = posDerivedStateMsg.rotY/100.0;
		hiResImageMsg.GPS_msecs = posDerivedStateMsg.msecs;
		hiResImageMsg.GPS_week = posDerivedStateMsg.week;

		fprintf(stderr, "Sending a hiResImage message to GUI.\n");
		NddsProducerSample (hiResImageProd);
		fprintf(stderr, "Done sending message.\n");
	}

	return req->instance;
}

NDDSObjectInstance hiResImageRequestRadiansCallback (NDDSUpdateInfo req)
{

	return req->instance;
}

NDDSObjectInstance hiResImageSelectionCallback (NDDSUpdateInfo sel)
{
	printf("Received hiResImageSelection request");

	char path[255] = "k:\\temp\\";
	char filename[255];
	hiResImageSelection msg = (hiResImageSelection)sel->instance;
	printf("Received hiResImageRequest");

	if (sel->updateStatus == NDDS_FRESH_DATA)
	{
		printf ("Centering to row=%d col=%d\n", msg->row, msg->col);
		centreRowCol(msg->col, msg->row);
		sprintf (filename, "%s%s", path, "hires.ppm");
		printf ("Saving to file %s.\n", filename);
		savePPMImage(&Cam, 1, filename);	
		
		sprintf (filename, "%s%s", "/afs/cs/project/lri-7/temp/", "hires.ppm");
		strcpy (hiResImageMsg.filename, filename);
		hiResImageMsg.ptuAzimuth = 1.0;
		hiResImageMsg.ptuElevation = 1.0;
		hiResImageMsg.robot_dx = posDerivedStateMsg.posWest/100.0;
		hiResImageMsg.robot_dy = posDerivedStateMsg.posNorth/100.0;
		hiResImageMsg.robot_dz = posDerivedStateMsg.posUp/100.0;
		hiResImageMsg.robotAzimuth = posDerivedStateMsg.rotZ/100.0;
		hiResImageMsg.robotPitch = posDerivedStateMsg.rotX/100.0;
		hiResImageMsg.robotRoll = posDerivedStateMsg.rotY/100.0;
		hiResImageMsg.GPS_msecs = posDerivedStateMsg.msecs;
		hiResImageMsg.GPS_week = posDerivedStateMsg.week;

		NddsProducerSample (dbRequestProd);
	}

	return sel->instance;
}

NDDSObjectInstance dbFieldReplyCallback (NDDSUpdateInfo db)
{
	return db->instance;
}

NDDSObjectInstance dbIDListReplyCallback (NDDSUpdateInfo db)
{
	return db->instance;
}

NDDSObjectInstance posDerivedStateCallback (NDDSUpdateInfo pds)
{
	return pds->instance;
}


void consumerSetup ()
{
	NDDSConsumer cons, consPoll;
	float idListReply_timeout = 60.0; /* seconds */
	extern posDerivedStateStruct posDerivedStateMsg;
	extern dbIDListReplyStruct dbIDListMsg;

	/* Create Consumer */
	cons = NddsConsumerCreate("HiResCons", NDDS_IMMEDIATE_RELIABLE, 1000000.0, 0.0);
	consPoll = NddsConsumerCreate("HiResConsPoll", NDDS_POLLED_RELIABLE, idListReply_timeout, 0.0);

	printf("Setting up consumers...");
	/* Register Messages */
	hiResImageRequestNddsRegister ();
//	hiResImageRequestRadiansNddsRegister ();
	hiResImageSelectionNddsRegister ();
	dbFieldReplyNddsRegister ();
	dbIDListReplyNddsRegister ();
	posDerivedStateNddsRegister ();

	/* Subscribe Messages to Consumer */
	NddsConsumerSubscriptionAdd (cons, HI_RES_IMAGE_REQUEST_NAME, HI_RES_IMAGE_REQUEST_NAME, NULL, hiResImageRequestCallback, NULL);
//	NddsConsumerSubscriptionAdd (cons, HI_RES_IMAGE_REQUEST_RADIANS_NAME, HI_RES_IMAGE_REQUEST_RADIANS_NAME, NULL, hiResImageRequestRadiansCallback, NULL);
	NddsConsumerSubscriptionAdd (cons, HI_RES_IMAGE_SELECTION_NAME, HI_RES_IMAGE_SELECTION_NAME, NULL, hiResImageSelectionCallback, NULL);
	NddsConsumerSubscriptionAdd (cons, DB_FIELD_REPLY_NAME, DB_FIELD_REPLY_NAME, NULL, dbFieldReplyCallback, NULL);
	NddsConsumerSubscriptionAdd (cons, POS_DERIVED_STATE_NAME, POS_DERIVED_STATE_NAME, &posDerivedStateMsg, posDerivedStateCallback, NULL);
	NddsConsumerSubscriptionAdd (consPoll, DB_ID_LIST_REPLY_NAME, DB_ID_LIST_REPLY_NAME, &dbIDListMsg, dbIDListReplyCallback, NULL);
}

void producerSetup ()
{
	extern NDDSProducer dbRequestProd, hiResImageProd;
	extern dbDatabaseRequestStruct dbRequestMsg;
	extern hiResImageStruct hiResImageMsg;

	float persistence = 10.0;
	float strength = 10.0;

	/* Create Producers */
	dbRequestProd = NddsProducerCreate ("dbRequestProd", NDDS_SYNCHRONOUS, persistence, strength);
	hiResImageProd = NddsProducerCreate ("HiResImageProd", NDDS_SYNCHRONOUS, persistence, strength);

	/* Register NDDS message types */
	dbDatabaseRequestNddsRegister ();
	hiResImageNddsRegister ();

	/* Subscribe messages to producers */
	NddsProducerProductionAdd (dbRequestProd, DB_DATABASE_REQUEST_NAME, DB_DATABASE_REQUEST_NAME, &dbRequestMsg, 0, NULL, NULL);
	NddsProducerProductionAdd (hiResImageProd, HI_RES_IMAGE_NAME, HI_RES_IMAGE_NAME, &hiResImageMsg, 0, NULL, NULL);
}

void InitNddsComm ()
{
	NddsInit (NOMAD_NDDS_DOMAIN, NULL);
	consumerSetup ();
	producerSetup ();
}
