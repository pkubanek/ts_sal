#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "ndds/NDDS.h"
#include "javaToNdds.h"
#include "nddsMsgNames.h"
#include "SAS_ServiceNames.h"

/* Needed defintions */ 
#include "sensorDef.h"
#include "targetAcqDef.h"

/* Include NDDS message header files */
#include "targetAcqMsgs.h"
#include "sensorMsgs.h"
#include "move.h"

int flushInBuffer(int readStatus, int sockfd) {
  char tmpBuff[MAX_NDDS_DATA_LENGTH];
  int readStatusTmp;
  int count = 0;

  /* TBD: This is a hack! fix it! */
  while((readStatus < MAX_NDDS_DATA_LENGTH) && (count < MAX_NDDS_DATA_LENGTH)) {
    if(readStatusTmp = read(sockfd, tmpBuff, MAX_NDDS_DATA_LENGTH) != MAX_NDDS_DATA_LENGTH-readStatus) {
      readStatus += readStatusTmp;
      count++;
    }
  }

  if(readStatus != MAX_NDDS_DATA_LENGTH) {
    return(0); 
  } else {
    return(1);
  }
}

void targetAcqRequestCmd(XDR xdrStream, targetAcqRequest *request, targetAcqReply *reply,
		      NDDSClient client, NDDSClientReplyStatus clientStatus) {
  xdr_targetAcqRequest(&xdrStream, request);
  fprintf(stderr, "[javaToNdds] Got targetAcqRequest: ");
  fprintf(stderr, "%d\n ", request->driverNum); 

  /* Check for server */
  if(NddsClientServerWait(client, 2.0, 5, 1) == RTI_FALSE) { 
    fprintf(stderr, "[javaToNdds] ERROR: targetAcqRequest server missing!\n");
  } else {
    clientStatus = NddsClientCallAndWait(client, reply, request,
					 NDDS_CLIENT_MIN_WAIT_TIME, NDDS_CLIENT_MAX_WAIT_TIME);
    if(clientStatus == NDDS_CLIENT_RECV_REPLY) {
      if(reply->status != TARGET_ACQ_SUBMITTED_REQ) {
	// Failure condition.
	fprintf(stderr, "[javaToNdds] ERROR: Target acq submission failed! Returned %d\n", reply->status);
      }
    } else {
      // Sensor did not respond to NDDS message
      fprintf(stderr, "[javaToNdds] ERROR: Target acq did not respond to request!\n");
    }
  }
}

void sensorRequestCmd(XDR xdrStream, sensorRequest *request, sensorReply *reply,
		   NDDSClient client, NDDSClientReplyStatus clientStatus) {
  xdr_sensorRequest(&xdrStream, request);
  fprintf(stderr, "[javaToNdds] Got sensorRequest: ");
  fprintf(stderr, "%s ", request->sensorID); 
  fprintf(stderr, "%d\n", request->function);
  
  /* Check for server */
  if(NddsClientServerWait(client, 2.0, 5, 1) == RTI_FALSE) { 
    fprintf(stderr, "[javaToNdds] ERROR: hiResSensor server missing!\n");
  } else {
    clientStatus = NddsClientCallAndWait(client, reply, request,
					 NDDS_CLIENT_MIN_WAIT_TIME, NDDS_CLIENT_MAX_WAIT_TIME);
    if(clientStatus == NDDS_CLIENT_RECV_REPLY) {
      if(reply->status != SENSOR_OK) {
	// Failure condition.
	fprintf(stderr, "[javaToNdds] ERROR: hiResSensor failed! Returned %d\n", reply->status);
      }
    } else {
      // Sensor did not respond to NDDS message
      fprintf(stderr, "[javaToNdds] ERROR: hiResSensor did not respond to request!\n");
    }
  }
}

void moveCmd(XDR xdrStream, move *cmd, NDDSPublication pub) {
  xdr_move(&xdrStream, cmd);
  fprintf(stderr, "NOTE: the translateSpeed is undergoing a hack to get it from cm/s (NomadGUI format) to m/s (everyone else's format!) \n");
  cmd->translateSpeed /= 100.0f; /* TBD: THIS IS A HACK!!! ALL OTHERS SEND SPEEDS AS m/s, THIS IS CONVERTING
				    FROM cm/s! */
  movePrint(cmd);

  /* Publish it */
  NddsPublicationSend(pub);
}

int main(int argc, char *argv[]) {
  unsigned int clientLen;
  int sockfd, newsockfd, readStatus;
  char msgName[MAX_NDDS_NAME_LENGTH];
  struct sockaddr_in clientAddr, servAddr;
  XDR xdrStream;
  char xdrBuff[MAX_NDDS_DATA_LENGTH];
  int readStatus2;
  char tmp2[MAX_NDDS_DATA_LENGTH];
  
  if(argc != 4) {
    fprintf(stderr, "Usage: javaToNdds nddsDomain ipAddress port\n");
    fprintf(stderr, "\t nddsDomain is the local NDDS domain number,\n");
    fprintf(stderr, "\t ipAddress is the local host's IP address,\n");
    fprintf(stderr, "\t port is the local host's connection port.\n");
    return(-1);
  }
  
  /* Initialize NDDS */
  NddsInit(atoi(argv[1]), NULL);

  /* Setup NDDS messages */
  SETUP_NDDS_CLIENT(targetAcqRequest, targetAcqReply, TARGET_ACQ_SERVICE);
  SETUP_NDDS_DYNAMIC_CLIENT(sensorRequest, sensorReply, hiResSensor);
  SETUP_NDDS_PUBLISHER(move, MOVE_MSG_NAME);

  /* Setup XDR decoding stream */
  xdrmem_create(&xdrStream, xdrBuff, MAX_NDDS_DATA_LENGTH, XDR_DECODE);
  
  /* Open a TCP socket (an internet stream socket) */
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "[javaToNdds] ERROR: Can't open stream socket!\n");
    return(-1);
  }

  /* Bind our local address so the client can send us stuff */
  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons((unsigned short)atoi(argv[3]));

  if(bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    fprintf(stderr, "[javaToNdds] ERROR: Can't bind local address!\n");
    return(-1);
  }
    
  listen(sockfd, MAX_QUEUE_SIZE);
  
  fprintf(stderr, "[javaToNdds] Listening for connections...\n");
  
  for(;;) {

    clientLen = sizeof(clientAddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);

    if(newsockfd < 0) {
      fprintf(stderr, "[javaToNdds] ERROR: Socket accept error!\n");
      return(-1);
    }

    while((readStatus = read(newsockfd, msgName, MAX_NDDS_NAME_LENGTH)) > 0) {
      
      /* We now have a message name, check which one it is */
      if(strcmp(msgName, TARGET_ACQ_REQUEST_MSG_NAME) == 0) {
	if((readStatus = read(newsockfd, xdrBuff, MAX_NDDS_DATA_LENGTH)) > 0) {
	  targetAcqRequestCmd(xdrStream, targetAcqRequestMsg, targetAcqReplyMsg, TARGET_ACQ_SERVICE_Client, TARGET_ACQ_SERVICE_ClientStatus);
	} else {
	  fprintf(stderr, "[javaToNdds] ERROR: Could not decode XDR!\n");
	}

	if(!flushInBuffer(readStatus, newsockfd)) {
	  fprintf(stderr, "[javaToNdds] ERROR: Could not read entire data buffer!\n");
	  return(-1);
	} 
      } else if(strcmp(msgName, SENSOR_REQUEST_MSG_NAME) == 0) {
	if((readStatus = read(newsockfd, xdrBuff, MAX_NDDS_DATA_LENGTH)) > 0) {
	  sensorRequestCmd(xdrStream, sensorRequestMsg, sensorReplyMsg, hiResSensor_Client, hiResSensor_ClientStatus);
	} else {
	  fprintf(stderr, "[javaToNdds] ERROR: Could not decode XDR!\n");
	}

	if(!flushInBuffer(readStatus, newsockfd)) {
	  fprintf(stderr, "[javaToNdds] ERROR: Could not read entire data buffer!\n");
	  return(-1);
	} 
      } else if(strcmp(msgName, MOVE_MSG_NAME) == 0) {
	if((readStatus = read(newsockfd, xdrBuff, MAX_NDDS_DATA_LENGTH)) > 0) {
	  moveCmd(xdrStream, moveMsg, move_Publication);
	} else {
	  fprintf(stderr, "[javaToNdds] ERROR: Could not decode XDR!\n");
	}

	if(!flushInBuffer(readStatus, newsockfd)) {
	  fprintf(stderr, "[javaToNdds] ERROR: Could not read entire data buffer!\n");
	  return(-1);
	} 
      } else {
	fprintf(stderr, "[javaToNdds] ERROR: Did not recognize message name %s!\n", msgName);
	read(newsockfd, tmp2, MAX_NDDS_DATA_LENGTH);
	read(newsockfd, tmp2, MAX_NDDS_DATA_LENGTH);
      }
      
      bzero(xdrBuff, sizeof(xdrBuff));      
      bzero(msgName, sizeof(msgName));

      /* TBD: Figure out why this is needed. This may be a hack! */
      xdrmem_create(&xdrStream, xdrBuff, MAX_NDDS_DATA_LENGTH, XDR_DECODE);
    }
    
    close(newsockfd);
    
  }

  /* Free NDDS messages */
  FREE_NDDS(targetAcqRequest);
  FREE_NDDS(sensorRequest);

  return(-1);
}

