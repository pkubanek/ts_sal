#include "NDDS.h"

#include <stdio.h>
#include "NddsComm.h"

/*#include "dbDatabaseRequest.h"
#include "dbFieldReply.h"
#include "dbIDListReply.h"
#include "dbFieldNames.h"
#include "dbMessagesNames.h"
*/

#include "specTypes.h"
#include "specReply.h"
#include "specCommand.h"
#include "specMessageNames.h"

#include "nomadNddsDomain.h"
#include "SPECCON.H"

/* NDDS Producer stuff */
NDDSProducer specReplyProd;
specReplyStruct specReplyMsg;

/* Callback function for the specCommand */
NDDSObjectInstance specCommandCallback (NDDSUpdateInfo command)
{
	specCommand msg = (specCommand) command->instance;
	extern SpecCon spectrometer;

	if (command->updateStatus == NDDS_FRESH_DATA)
	{
		/* Do stuff with msg->commandType and msg->targetID */
		spectrometer.targetID=msg->targetID;
		

		switch(msg->commandType) {
		case SPEC_CMD_WHITEREF:
			if(spectrometer.optimize()) {
				if(spectrometer.doWhiteref()) {
					specReplyMsg.sensorStatus=MP_SENSOR_SUCESSFUL;
					specReplyMsg.extendedSensorStatus=SPEC_STA_NOERROR;
				}
			}
			break;
		case SPEC_CMD_DARK:
			if(spectrometer.doDark()) {
				specReplyMsg.sensorStatus=MP_SENSOR_SUCESSFUL;
				specReplyMsg.extendedSensorStatus=SPEC_STA_NOERROR;
			}
			break;
		case SPEC_CMD_SAMPLE:
			if(spectrometer.doSample()) {
				spectrometer.spectrumnum++;
				specReplyMsg.sensorStatus=MP_SENSOR_SUCESSFUL;
				specReplyMsg.extendedSensorStatus=SPEC_STA_NOERROR;
				spectrometer.updateListFile();
			}
			break;
		}

		specReplyMsg.deploymentCost = 0.0;
		sprintf(specReplyMsg.listFileName, "%s", spectrometer.listFilename);
	
		NddsProducerSample (specReplyProd);
	}

	return command->instance;
}

void consumerSetup ()
{
	NDDSConsumer cons;
	float timeout = 10000000.0; /* seconds */

	/* Create Consumer */
	cons = NddsConsumerCreate ("specCommandCons", NDDS_IMMEDIATE_RELIABLE, timeout, 0.0);

	/* Register NDDS message types */
	specCommandNddsRegister ();

	/* Subscribe messages to consumer */
	NddsConsumerSubscriptionAdd (cons, SPEC_COMMAND_NAME, SPEC_COMMAND_NAME, NULL, specCommandCallback, NULL);
}

void producerSetup ()
{
	extern NDDSProducer specReplyProd;
	extern specReplyStruct specReplyMsg;

	float persistence = 10.0;
	float strength = 10.0;

	/* Create Producers */
	specReplyProd = NddsProducerCreate ("specReplyProd", NDDS_SYNCHRONOUS, persistence, strength);
	
	/* Register NDDS message types */
	specReplyNddsRegister();

	/* Subscribe messages to producer */
	NddsProducerProductionAdd (specReplyProd, SPEC_REPLY_NAME, SPEC_REPLY_NAME, &specReplyMsg, 0, NULL, NULL);
}

void InitNddsComm ()
{
	NddsInit (NOMAD_NDDS_DOMAIN, NULL);
	consumerSetup();
	producerSetup();
}