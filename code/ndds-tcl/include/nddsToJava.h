#ifndef __NDDS_TO_JAVA_H__
#define __NDDS_TO_JAVA_H__

#include "bodDerivedState.h"
#include "nddsMsgNames.h"
#include "ndds/NDDS.h"

#define MAX_QUEUE_SIZE 5
#define NDDS_SUBSCRIPTION_DEADLINE 10.0f
#define NDDS_SUBSCRIPTION_MIN_SEPARATION 0.0f
#define MAX_CLIENT_MSG_LEN 1024
#define EXIT_STRING "EXIT"

typedef struct {
  int *sockfd;
  char *xdrBuff;
  XDR xdrStream;
  int *writeFlag;
} callBackParam;

#define SETUP_NDDS(_domain_) \
NddsInit(_domain_, NULL); \
NDDSSubscriber subscriber = NddsSubscriberCreate();

#define SETUP_NDDS_SUBSCRIPTION(_name_, _msgTopic_, _msgType_) \
_name_ *_name_##Msg = (_name_ *)calloc(1, sizeof(_name_)); \
_name_##NddsRegister(); \
callBackParam *_name_##Param = (callBackParam *)calloc(1, sizeof(callBackParam)); \
_name_##Param->sockfd = &newsockfd; \
_name_##Param->xdrBuff = (char *)calloc(MAX_NDDS_DATA_LENGTH, sizeof(char)); \
_name_##Param->writeFlag = &writeFlag; \
xdrmem_create(&_name_##Param->xdrStream, _name_##Param->xdrBuff, MAX_NDDS_DATA_LENGTH, XDR_ENCODE); \
NDDSSubscription _name_##Subscription = NddsSubscriptionCreate(NDDS_SUBSCRIPTION_IMMEDIATE, \
								_msgTopic_, _msgType_, \
								_name_##Msg, NDDS_SUBSCRIPTION_DEADLINE, \
								NDDS_SUBSCRIPTION_MIN_SEPARATION, \
								_name_##Callback, _name_##Param); \
NddsSubscriberSubscriptionAdd(subscriber, _name_##Subscription); 


#define NDDS_CALLBACK_BEGIN(_name_, _msgName_) \
RTIBool _name_##Callback(NDDSRecvInfo *issue) { \
  if (issue->status == NDDS_FRESH_DATA) { \
    _name_## *_name_##Msg = (_name_## *)issue->instance; \
    callBackParam *p  = (callBackParam *)issue->callBackRtnParam; \
    if(*(p->writeFlag)) { \
      int writeStatus; \
      char tmp[MAX_NDDS_NAME_LENGTH]; \
      char tmpData[MAX_NDDS_DATA_LENGTH]; \
      bzero(tmpData, MAX_NDDS_DATA_LENGTH * sizeof(char)); 
    
#define NDDS_CALLBACK_END(_name_, _msgName_) \
      sprintf(tmp, "%s\n", _msgName_); \
      if((writeStatus = write(*(p->sockfd), tmp, strlen(tmp))) < 0) { \
        fprintf(stderr, "[nddsToJava] ERROR: Write error!\n"); \
        close(*(p->sockfd)); \
        *(p->sockfd) = -1; \
      } else { \
        xdr_##_name_##(&(p->xdrStream), _name_##Msg); \
        p->xdrStream.x_ops->x_setpostn(&(p->xdrStream), 0);  /* reset stream to beginning, so \
	  						        next encoding will be made w/o an offset */  \
        if((writeStatus = write(*(p->sockfd), p->xdrBuff, MAX_NDDS_DATA_LENGTH)) < 0) { \
          fprintf(stderr, "[nddsToJava] ERROR: Write error!\n"); \
          close(*(p->sockfd)); \
          *(p->sockfd) = -1; \
        } \
        while(writeStatus < MAX_NDDS_DATA_LENGTH) { \
          writeStatus += write(*(p->sockfd), tmpData, MAX_NDDS_DATA_LENGTH - writeStatus); \
        } \
      } \
    } \
  } \
  return RTI_TRUE; \
}



#define FREE_NDDS(_name_) \
free(_name_##Msg);

#endif /* __NDDS_TO_JAVA_H__ */
