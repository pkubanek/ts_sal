#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <errno.h>
#include "nddsToJava.h"
#include "ndds/NDDS.h"
#include "nddsMsgNames.h"

#include "bodDerivedState.h"
#include "posDerivedState.h"
#include "weatherState.h"
#include "rtControlState.h"
#include "rtAmpState.h"
#include "kvhDerivedState.h"
#include "telemetryMsgs.h"

extern int errno;

NDDS_CALLBACK_BEGIN(bodDerivedState, BOD_DERIVED_STATE_MSG_NAME) 
NDDS_CALLBACK_END(bodDerivedState, BOD_DERIVED_STATE_MSG_NAME) 
NDDS_CALLBACK_BEGIN(posDerivedState, POS_DERIVED_STATE_MSG_NAME) 
NDDS_CALLBACK_END(posDerivedState, POS_DERIVED_STATE_MSG_NAME) 
NDDS_CALLBACK_BEGIN(weatherState, WEATHER_STATE_MSG_NAME) 
NDDS_CALLBACK_END(weatherState, WEATHER_STATE_MSG_NAME) 
NDDS_CALLBACK_BEGIN(rtControlState, RT_CONTROL_STATE_MSG_NAME) 
NDDS_CALLBACK_END(rtControlState, RT_CONTROL_STATE_MSG_NAME) 
NDDS_CALLBACK_BEGIN(rtAmpState, RT_AMP_STATE_MSG_NAME) 
NDDS_CALLBACK_END(rtAmpState, RT_AMP_STATE_MSG_NAME) 
NDDS_CALLBACK_BEGIN(kvhDerivedState, KVH_DERIVED_STATE_MSG_NAME) 
NDDS_CALLBACK_END(kvhDerivedState, KVH_DERIVED_STATE_MSG_NAME) 
NDDS_CALLBACK_BEGIN(hiResDerivedState, HI_RES_DERIVED_STATE_MSG_NAME) 
NDDS_CALLBACK_END(hiResDerivedState, HI_RES_DERIVED_STATE_MSG_NAME) 

int main(int argc, char *argv[]) {
  int sockfd, newsockfd, childPid, readStatus, writeStatus, writeFlag;
  unsigned int clientLen;
  struct sockaddr_in clientAddr, servAddr;

  if(argc != 4) {
    fprintf(stderr, "Usage: nddsToJava nddsDomain ipAddress port\n");
    fprintf(stderr, "\tnddsDomain is the local NDDS domain number,\n");
    fprintf(stderr, "\tipAddress is the local host's IP address,\n");
    fprintf(stderr, "\tport is the local host's connection port.\n");
    return(-1);
  }

  fprintf(stderr, "[nddsToJava] Starting up...");

  /* Open a TCP socket (an internet stream socket) */
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "[nddsToJava] ERROR: Can't open stream socket!\n");
    return(-1);
  }

  /* Bind our local address so the client can send us stuff */
  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons((unsigned short)atoi(argv[3]));

  if(bind(sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
    fprintf(stderr, "[nddsToJava] ERROR: Can't bind local address!\n");
    return(-1);
  }

  writeFlag = 0; // Disable ndds callback routines from writing to a socket, since it's not yet accepted a socket.
    
  SETUP_NDDS(atoi(argv[1]));
  
  SETUP_NDDS_SUBSCRIPTION(bodDerivedState, BOD_DERIVED_STATE_MSG_NAME, BOD_DERIVED_STATE_MSG_NAME);
  SETUP_NDDS_SUBSCRIPTION(posDerivedState, POS_DERIVED_STATE_MSG_NAME, POS_DERIVED_STATE_MSG_NAME);
  SETUP_NDDS_SUBSCRIPTION(weatherState, WEATHER_STATE_MSG_NAME, WEATHER_STATE_MSG_NAME);
  SETUP_NDDS_SUBSCRIPTION(rtControlState, RT_CONTROL_STATE_MSG_NAME, RT_CONTROL_STATE_MSG_NAME);
  SETUP_NDDS_SUBSCRIPTION(rtAmpState, RT_AMP_STATE_MSG_NAME, RT_AMP_STATE_MSG_NAME);
  SETUP_NDDS_SUBSCRIPTION(kvhDerivedState, KVH_DERIVED_STATE_MSG_NAME, KVH_DERIVED_STATE_MSG_NAME);
  SETUP_NDDS_SUBSCRIPTION(hiResDerivedState, HI_RES_DERIVED_STATE_MSG_NAME, HI_RES_DERIVED_STATE_MSG_NAME);

  listen(sockfd, MAX_QUEUE_SIZE);
  
  fprintf(stderr, "waiting for connections.\n");

  clientLen = sizeof(clientAddr);

  char tmpBuff[MAX_CLIENT_MSG_LEN];

  while(1) {
    newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);
    
    if(newsockfd < 0) {
      fprintf(stderr, "[nddsToJava] ERROR: Accept error!\n");
      return(-1);
    }
    
    fprintf(stderr, "[nddsToJava] Accepted socket, sending out telemetry...\n");

    writeFlag = 1; // Ready to start sending out telemetry
    
    while(1) {
      NddsUtilitySleep(0.01);
      
      if(read(newsockfd, tmpBuff, MAX_CLIENT_MSG_LEN) > 0) {
	if(strcmp(tmpBuff, EXIT_STRING) == 0) {
	  close(newsockfd);
	  writeFlag = 0;
	  fprintf(stderr, "[nddsToJava] Closed socket!\n");
	  break;
	}
      }
    }
  }

  return(-1);
}


