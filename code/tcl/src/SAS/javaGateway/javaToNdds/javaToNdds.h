#ifndef __JAVA_TO_NDDS_H__
#define __JAVA_TO_NDDS_H__

#define MAX_QUEUE_SIZE 5
#define NDDS_PUBLISHER_PERSISTANCE 15.0f
#define NDDS_PUBLISHER_STRENGTH 10.0f
#define NDDS_CLIENT_MIN_WAIT_TIME 2.0f
#define NDDS_CLIENT_MAX_WAIT_TIME 120.0f

#define SETUP_NDDS_PUBLISHER(_name_, _msgName_) \
_name_ *_name_##Msg = (_name_ *)calloc(1, sizeof(_name_)); \
_name_##NddsRegister(); \
NDDSPublication _name_##_Publication = NddsPublicationCreate(_msgName_, _name_##PublicationType, \
							      _name_##Msg, \
							      NDDS_PUBLISHER_PERSISTANCE, NDDS_PUBLISHER_STRENGTH); 

#define SETUP_NDDS_CLIENT(_request_, _reply_, _serviceName_) \
_reply_ *_reply_##Msg = (_reply_ *)calloc(1, sizeof(_reply_)); \
_request_ *_request_##Msg = (_request_ *)calloc(1, sizeof(_request_)); \
_reply_##NddsRegister(); \
_request_##NddsRegister(); \
NDDSClient _serviceName_##_Client = NddsClientCreate(_serviceName_, _reply_##PublicationType, \
                                                      _request_##PublicationType); \
NDDSClientReplyStatus _serviceName_##_ClientStatus; 

/* This macro sets up clients for dynamic servers like sensor drivers
   (the _serviceName_ must be a string in NddsClientCreate) */
#define SETUP_NDDS_DYNAMIC_CLIENT(_request_, _reply_, _serviceName_) \
_reply_ *_reply_##Msg = (_reply_ *)calloc(1, sizeof(_reply_)); \
_request_ *_request_##Msg = (_request_ *)calloc(1, sizeof(_request_)); \
_reply_##NddsRegister(); \
_request_##NddsRegister(); \
NDDSClient _serviceName_##_Client = NddsClientCreate(#_serviceName_, _reply_##PublicationType, \
                                                      _request_##PublicationType); \
NDDSClientReplyStatus _serviceName_##_ClientStatus; 

#define FREE_NDDS(_name_) \
free(_name_##Msg);

#endif /* __JAVA_TO_NDDS_H__ */
