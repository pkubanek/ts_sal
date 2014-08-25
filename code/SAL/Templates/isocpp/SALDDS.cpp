
#include "common/example_utilities.h"
#include <iostream>
#include "SALData_DCPS.hpp"

//#include <chrono>
#include "SALDDS.h"

namespace lsst {
namespace org {
namespace sal {


void SALDDS::salInitialize()
{
   hasReader = false;
   hasWriter = false;
   debugLevel = 1;
   /** A dds::domain::DomainParticipant is created for the default domain. */
   dds::domain::DomainParticipant dp("SAL LSST");

   /** The Durability::Transient policy is specified as a dds::topic::qos::TopicQos
         * so that even if the subscriber does not join until after the sample is written
         * then the DDS will still retain the sample for it. The Reliability::Reliable
         * policy is also specified to guarantee delivery. */
   dds::topic::qos::TopicQos topicQos
                = dp.default_topic_qos()
                << dds::core::policy::Durability::Transient()
                << dds::core::policy::Reliability::Reliable()
                << dds::core::policy::History::KeepAll();
}

#ifdef COMPILETHISTOO
template <class t>
T SALDDS<T>::salTelemetryPub(char *topicName)
{
        /** A dds::topic::Topic is created for our sample type on the domain participant. */
        dds::topic::Topic<T> topic(dp, topic_name, topicQos);

        /** A dds::pub::Publisher is created on the domain participant. */
        std::string name = "SAL example";
        dds::pub::qos::PublisherQos pubQos
            = dp.default_publisher_qos()
                << dds::core::policy::Partition(name);
        dds::pub::Publisher pub(dp, pubQos);

        /** The dds::pub::qos::DataWriterQos is derived from the topic qos and the
         * WriterDataLifecycle::ManuallyDisposeUnregisteredInstances policy is
         * specified as an addition. This is so the publisher can optionally be run (and
         * exit) before the subscriber. It prevents the middleware default 'clean up' of
         * the topic instance after the writer deletion, this deletion implicitly performs
         * DataWriter::unregister_instance */
        dds::pub::qos::DataWriterQos dwqos = topic.qos();
        dwqos << dds::core::policy::WriterDataLifecycle::ManuallyDisposeUnregisteredInstances();

        /** A dds::pub::DataWriter is created on the Publisher & Topic with the modififed Qos. */
        dds::pub::DataWriter<T> dw(pub, T topic, dwqos);

  return topic;

}

//DataReader_var  SALDDS::salTelemetrySub(char *topicName)
template <class T>
DataReader<T> SALDDS<T>::salTelemetrySub(char *topicName)
{
       dds::topic::Topic<T> topic(dp, "SALData_SALTopic", topicQos);

        /** A dds::sub::Subscriber is created on the domain participant. */
        std::string name = "SAL example";
        dds::sub::qos::SubscriberQos subQos
            = dp.default_subscriber_qos()
                << dds::core::policy::Partition(name);
        dds::sub::Subscriber sub(dp, subQos);

        /** The dds::sub::qos::DataReaderQos are derived from the topic qos */
        dds::sub::qos::DataReaderQos drqos = topic.qos();

        /** A dds::sub::DataReader is created on the Subscriber & Topic with the DataReaderQos. */
        dds::sub::DataReader<T> dr(sub, topic, drqos);
        return dr;
}
       
void SALDDS::logError(salReturn status) 
{
   std::cout << "=== ERROR return value = " << status << std::endl; 
}

/*
using Clock = std::chrono::high_resolution_clock;
using Time_point = Clock::time_point;
using std::chrono::milliseconds;
using std::chrono::duration_cast;

salTIME SALDDS::currentTime()
{
    Time_point tp = Clock::now();   
    return (salTIME duration_cast<milliseconds>tp.count());
}
*/

salUINT SALDDS::issueCommand( SALData::SALCommand data )
{
  // create DataWriter :
  // If autodispose_unregistered_instances is set to true (default value),
  // you will have to start the subscriber before the publisher
  bool autodispose_unregistered_instances = false;
  if (!hasWriter) {
     createWriter(autodispose_unregistered_instances);
     hasWriter = true;
     sndSeqNum = 1;
  }
  DataWriter_var dwriter = getWriter();
  SALCommandDataWriter_var SALWriter = SALCommandDataWriter::_narrow(dwriter.in());
  data.private_revCode = DDS::string_dup("LSST TEST COMMAND");
  data.private_seqNum = sndSeqNum;
  if (debugLevel > 0) {
    cout << "=== [issueCommand] writing a command containing :" << endl;
    cout << " " << data.device << "." << data.property << "." << data.action << " : " << data.value << endl;
  }
  ReturnCode_t status = SALWriter->write(data, DDS::HANDLE_NIL);
  sndSeqNum++;
  checkStatus(status, "SALCommandDataWriter::write");  
  if (status != SAL__OK) {
      if (debugLevel >= SAL__LOG_ROUTINES) {
          logError(status);
      }
  }
  return (sndSeqNum-1);
}


salReturn SALDDS::checkCommand( salUINT cmdSeqNum )
{
   salReturn status = SAL__OK;
   SALResponse response;
   status = getResponse(response);
   if (status != SAL__OK) {
      if (debugLevel >= SAL__LOG_ROUTINES) {
          logError(status);
      }
   }
   return status;
}

salReturn SALDDS::getResponse(SALData::SALResponse data)
{
  SampleInfo info;
  ReturnCode_t status =  - 1;
  DataReader_var dreader = getReader();
  SALResponseDataReader_var SALReader = SALResponseDataReader::_narrow(dreader.in());
  checkHandle(SALReader.in(), "SALResponseDataReader::_narrow");
  status = SALReader->take_next_sample(data, info);
//, LENGTH_UNLIMITED,ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
  checkStatus(status, "SALResponseDataReader::take");
  if (debugLevel > 0) {
    cout << "=== [getResponse] reading a message containing :" << endl;
    cout << "    revCode  : " << data.private_seqNum << endl;
  }
  status = data.ack;
  rcvSeqNum = data.private_seqNum;
//  status = SALReader->return_loan(data, info);
//  checkStatus(status, "SALResponseDataReader::return_loan");
  return status;
}


salReturn SALDDS::cancelCommand( salUINT cmdSeqNum )
{
   salReturn status = SAL__OK;
   if (status != SAL__OK) {
      if (debugLevel >= SAL__LOG_ROUTINES) {
          logError(status);
      }
   }
   return status;
}

salReturn SALDDS::abortCommand( salUINT cmdSeqNum )
{
   salReturn status = SAL__OK;
   if (status != SAL__OK) {
      if (debugLevel >= SAL__LOG_ROUTINES) {
          logError(status);
      }
   }
   return status;
}

salReturn SALDDS::waitForCompletion( salUINT cmdSeqNum , salINT timeout )
{
   salReturn status = SAL__OK;
   salUINT countdown = timeout;
   SALResponse response;

   while (status != SAL__CMD_COMPLETE && countdown > 0) {
      status = getResponse(response);
      if (response.private_seqNum != cmdSeqNum) { 
         status = SAL__CMD_NOACK;
      }
      usleep(SAL__SLOWPOLL);
      countdown--;
   }
   if (status != SAL__CMD_COMPLETE) {
      if (debugLevel >= SAL__LOG_ROUTINES) {
          logError(status);
      }
   }
   return status;
}

salReturn SALDDS::setDebugLevel( salUINT level )
{
   debugLevel = level;
   salReturn status = SAL__OK;
   if (status != SAL__OK) {
      if (debugLevel >= SAL__LOG_ROUTINES) {
          logError(status);
      }
   }
   return status;
}

salUINT SALDDS::getDebugLevel( salUINT level )
{
   return debugLevel;
}

salUINT SALDDS::getOrigin()
{
   salReturn status = SAL__OK;
   if (status != SAL__OK) {
      if (debugLevel >= SAL__LOG_ROUTINES) {
          logError(status);
      }
   }
   return status;
}

salUINT SALDDS::getProperty(salCHAR *property, salCHAR *value)
{
   salReturn status = SAL__OK;
   strcpy(value,"UNKNOWN");
   if (status != SAL__OK) {
      if (debugLevel >= SAL__LOG_ROUTINES) {
          logError(status);
      }
   }
   return status;
}

salReturn SALDDS::setProperty(salCHAR *property, salCHAR *value)
{
   if (status != SAL__OK) {
      if (debugLevel >= SAL__LOG_ROUTINES) {
          logError(status);
      }
   }
   return status;
}
 
/* 
template <class T1, class T2>
void SALDDS::putSample(T1 data, T2 SALWriter)
{
  T1 SALInstance = data;
  SALInstance.private_revCode = DDS::string_dup("LSST TEST REVCODE");
  cout << "=== [putSample] writing a message containing :" << endl;
  cout << "    revCode  : " << SALInstance.private_revCode << endl;

  ReturnCode_t status = SALWriter->write(SALInstance, DDS::HANDLE_NIL);
  checkStatus(status, "SALTopicDataWriter::write");  
}

template <class T1, class T2, class T3>
void SALDDS::getSample(T1 data, T2 info, T3 SALReader)
{
  ReturnCode_t status =  - 1;
  status = SALReader->take(data, info, LENGTH_UNLIMITED,ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
  checkStatus(status, "SALTopicDataReader::take");
  cout << "=== [getSample] reading a message containing :" << endl;
  cout << "    revCode  : " << data.private_revCode << endl;
  status = SALReader->return_loan(data, info);
  checkStatus(status, "SALTopicDataReader::return_loan");
}
*/

salReturn SALDDS::putSample(SALData::SALTopic data)
{
  DataWriter_var dwriter = getWriter();
  SALTopicDataWriter_var SALWriter = SALTopicDataWriter::_narrow(dwriter.in());
  data.private_revCode = DDS::string_dup("LSST TEST REVCODE");
  if (debugLevel > 0) {
    cout << "=== [putSample] writing a message containing :" << endl;
    cout << "    revCode  : " << data.private_revCode << endl;
  }
  ReturnCode_t status = SALWriter->write(data, DDS::HANDLE_NIL);
  checkStatus(status, "SALTopicDataWriter::write");  
  return status;
}

salReturn SALDDS::getSample(SALData::SALTopicSeq data)
{
  SampleInfoSeq infoSeq;
  ReturnCode_t status =  - 1;
  DataReader_var dreader = getReader();
  SALTopicDataReader_var SALReader = SALTopicDataReader::_narrow(dreader.in());
  checkHandle(SALReader.in(), "SALTopicDataReader::_narrow");
  status = SALReader->take(data, infoSeq, LENGTH_UNLIMITED, ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
  checkStatus(status, "SALTopicDataReader::take");
  for (DDS::ULong j = 0; j < data.length(); j++)
  {
    cout << "=== [GetSample] message received :" << endl;
    cout << "    revCode  : " << data[j].private_revCode << endl;
  }
  status = SALReader->return_loan(data, infoSeq);
  checkStatus(status, "SALTopicDataReader::return_loan");
  return status;
}

salReturn SALDDS::getEvent(SALData::SALEvent data)
{
  SampleInfo info;
  ReturnCode_t status =  - 1;
  DataReader_var dreader = getReader();
  SALEventDataReader_var SALReader = SALEventDataReader::_narrow(dreader.in());
  checkHandle(SALReader.in(), "SALEventDataReader::_narrow");
  status = SALReader->take_next_sample(data, info);
//, LENGTH_UNLIMITED,ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
  checkStatus(status, "SALEventDataReader::take");
  if (debugLevel > 0) {
    cout << "=== [getEvent] reading a message containing :" << endl;
    cout << "    revCode  : " << data.private_revCode << endl;
  }
//  status = SALReader->return_loan(data, info);
//  checkStatus(status, "SALEventDataReader::return_loan");
  return status;
}


void SALDDS::salCommand(char *topicName)
{
  // create domain participant
  createParticipant("SAL LSST");

  //create type
  SALCommandTypeSupport_var mt = new SALCommandTypeSupport();
  registerType(mt.in());

  //create Topic
  createTopic(topicName);
}


void SALDDS::salEvent(char *topicName)
{
  // create domain participant
  createParticipant("SAL LSST");

  //create type
  SALEventTypeSupport_var mt = new SALEventTypeSupport();
  registerType(mt.in());

  //create Topic
  createTopic(topicName);
}

void SALDDS::salShutdown()
{
  if ( hasReader ) { 
     deleteReader();
     deleteSubscriber();     
  }
  if ( hasWriter ) {
     deleteWriter();
     deletePublisher();
  }
  deleteTopic();
  deleteParticipant();
}

#endif

SALDDS::~SALDDS(){

}

}
}
}

