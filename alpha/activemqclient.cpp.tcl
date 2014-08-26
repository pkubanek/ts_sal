set SHC(activemqshpub1.cpp) "

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include \"[set topic]_cache.h\"
#include \"svcSAL_activemq.h\"

void svcSAL_activeMQ::[set topic]_MapMessageSend() {

try {
	TestSupport testSupport(IntegrationCommon::getInstance().getOpenwireURL());
	testSupport.initialize();

std::string stringValue;

// Create CMS Object for Comms
cms::Session* session = testSupport.getSession();
cms::Topic* [set topic]_topic = session->createTopic(\"[set topic]\");
cms::MessageProducer* [set topic]_producer = session->createProducer( [set topic]_topic );
cms::MapMessage* mapMessage = session->createMapMessage();

/* Main Loop */
"

set SHC(activemqshpub2.cpp) "

delete mapMessage;
if( IntegrationCommon::debug ) \{ printf(\"Shutting Down\n\" ); \}

delete [set topic]_producer;
\}
AMQ_CATCH_RETHROW( ActiveMQException )
\}
"

set SHC(activemqshsub1.cpp) "

void svcSAL_activeMQ::MapMessageGet() {

try {
	TestSupport testSupport(IntegrationCommon::getInstance().getOpenwireURL());
	testSupport.initialize();

std::string stringValue;

// Create CMS Object for Comms
cms::Session* session = testSupport.getSession();
cms::Topic* [set topic]_topic = session->createTopic(\"[set topic]\");
cms::MessageConsumer* [set topic]_consumer = session->createConsumer( [set topic]_topic );
cms::MapMessage* mapMessage = session->createMapMessage();

int ok=1;
while (ok) \{
  cms::Message* message = [set topic]_consumer->receive( 1500 );
  if ( message != NULL ) \{
     cms::MapMessage* recvMapMessage = dynamic_cast<MapMessage*>( message );
     if ( recvMapMessage != NULL ) \{"

set SHC(activemqshsub2.cpp) "
     \}
     delete message;
  \} else \{
     ok = 0;
  \}
\}

if( IntegrationCommon::debug ) { printf(\"Shutting Down\n\" ); }

delete [set topic]_consumer;
\}
AMQ_CATCH_RETHROW( ActiveMQException )
\}
"
