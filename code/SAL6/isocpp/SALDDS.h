
namespace lsst {
namespace org {
namespace sal {

  #include <string>
  #include "SAL_defines.h"
  #include "SALData_DCPS.hpp"

  class SALDDS
  {
     dds::domain::DomainParticipant dp;
     dds::sub::Subscriber subscriber;
     dds::sub::qos::SubscriberQos subQos;
     dds::sub::Publisher publisher;
     dds::sub::qos::PublisherQos pubQos;
     dds::topic::qos::TopicQos topicQos;
     dds::sub::qos::DataReaderQos drqos;
     dds::sub::qos::DataWriterQos dwqos;
     dds::sub::DataReader<SALData::SALTopic> dr_SALTopic;
     dds::sub::DataWriter<SALData::SALTopic> dw_SALTopic;

      bool hasReader;
      bool hasWriter;
      salUINT debugLevel;
      salUINT sndSeqNum;
      salUINT rcvSeqNum;

    public:
//      DataWriter_var salTelemetryPub(char *topicName);
//      void salTelemetrySub(char *topicName);
//      void salCommand(char *topicName);
//      void salEvent(char *topicName);
//      template <class T1, class T2>
//      void putSample(T1 data, T2 writer);
//      template <class T1, class T2, class T3>
//      void getSample(T1 data, T2 info, T3 reader);
      salReturn putSample(SALData::SALTopic data);
      salReturn getSample(SALData::SALTopicSeq data);
      salReturn getResponse(SALData::SALResponse data);
      salReturn getEvent(SALData::SALEvent data);
      void salShutdown();
      void salInitialize();
      salUINT issueCommand( SALData::SALCommand data);
      salReturn checkCommand( salUINT cmdSeqNum );
      salReturn cancelCommand( salUINT cmdSeqNum );
      salReturn abortCommand( salUINT cmdSeqNum );
      salReturn waitForCompletion( salUINT cmdSeqNum , salINT timeout );
      salReturn setDebugLevel( salUINT level );
      salUINT getDebugLevel( salUINT level );
      salUINT getOrigin();
      salUINT getProperty(salCHAR *property, salCHAR *value);
      salReturn setProperty(salCHAR *property, salCHAR *value);
      void logError(salReturn status);
      salTIME currentTime();
      
      ~SALDDS();
  };

}
}
}

