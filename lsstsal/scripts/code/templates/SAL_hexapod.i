%module SAL_hexapod
%{

  #include <string>
  #include <cassert>
  #include <string>
  #include <iostream>
  #include <fstream>
  #include "SAL_defines.h"
  #include "ccpp_dds_dcps.h"
  #include "ccpp_sal_hexapod.h"

  #include "CheckStatus.h"
  #include "SAL_hexapod.h"

%}

  using namespace std;

  class SAL_hexapod
  {

      bool hasReader;
      bool hasWriter;
      bool hasCommand;
      bool hasEventReader;
      bool hasEventWriter;
      bool hasProcessor;
      salUINT subsystemID;
      salUINT debugLevel;
      salUINT sndSeqNum;
      salUINT rcvSeqNum;
      salUINT rcvOrigin;
      salU64  origin;

    public:
// INSERT TYPE SUPPORT      

      salReturn putSample(hexapod::Actuators data);
      salReturn getSample(hexapod::ActuatorsSeq data);
      salReturn putSampleActuators(hexapod_ActuatorsC *data);
      salReturn getSampleActuators(hexapod_ActuatorsC *data);


      salReturn putSample(hexapod::Application data);
      salReturn getSample(hexapod::ApplicationSeq data);
      salReturn putSampleApplication(hexapod_ApplicationC *data);
      salReturn getSampleApplication(hexapod_ApplicationC *data);


      salReturn putSample(hexapod::Electrical data);
      salReturn getSample(hexapod::ElectricalSeq data);
      salReturn putSampleElectrical(hexapod_ElectricalC *data);
      salReturn getSampleElectrical(hexapod_ElectricalC *data);


      salReturn putSample(hexapod::LimitSensors data);
      salReturn getSample(hexapod::LimitSensorsSeq data);
      salReturn putSampleLimitSensors(hexapod_LimitSensorsC *data);
      salReturn getSampleLimitSensors(hexapod_LimitSensorsC *data);


      salReturn putSample(hexapod::Metrology data);
      salReturn getSample(hexapod::MetrologySeq data);
      salReturn putSampleMetrology(hexapod_MetrologyC *data);
      salReturn getSampleMetrology(hexapod_MetrologyC *data);


      salReturn putSample(hexapod::TC data);
      salReturn getSample(hexapod::TCSeq data);
      salReturn putSampleTC(hexapod_TCC *data);
      salReturn getSampleTC(hexapod_TCC *data);



      void salTypeSupport(char *topicName);
      void salTelemetryPub(char *topicName);
      void salTelemetrySub(char *topicName);
      void salEvent(char *topicName);
      salReturn getResponse(hexapod::ackcmdSeq data);
      salReturn getEvent(hexapod::logeventSeq data);
      void salShutdown();
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
      void salInitialize(salUINT aKey);
#else
      void salInitialize();
#endif
      void salCommand(char *command, char *response);
      void salProcessor(char *command, char *response);
      salUINT issueCommand( hexapod::command data);
      salReturn ackCommand( salUINT cmdSeqNum, salLONG  ack, salLONG error, char *result );
      salReturn acceptCommand( hexapod::commandSeq data);
      salReturn checkCommand( salINT cmdSeqNum );
      salReturn cancelCommand( salINT cmdSeqNum );
      salReturn abortCommand( salINT cmdSeqNum );
      salReturn waitForCompletion( salINT cmdSeqNum , salUINT timeout );
      salReturn setDebugLevel( salUINT level );
      salUINT getDebugLevel( salUINT level );
      salUINT getOrigin();
      salUINT getProperty(salCHAR *property, salCHAR *value);
      salReturn setProperty(salCHAR *property, salCHAR *value);
      void logError(salReturn status);
//      salTIME currentTime();
      salReturn logEvent( char *message, salUINT priority );
      

      ~SAL_hexapod();
  };

struct hexapod_ActuatorsC
{
   long Raw[18];
   float Calibrated[18];


  hexapod_ActuatorsC()  { std::cout << "hexapod_ActuatorsC()"  << std::endl; }
  ~hexapod_ActuatorsC() { std::cout << "~hexapod_ActuatorsC()"  << std::endl; }
};

struct hexapod_ApplicationC
{
   float Demand[6];
   float Position[6];
   float Error[6];


  hexapod_ApplicationC()  { std::cout << "hexapod_ApplicationC()"  << std::endl; }
  ~hexapod_ApplicationC() { std::cout << "~hexapod_ApplicationC()"  << std::endl; }
};

struct hexapod_ElectricalC
{
   long voltage[16];
   long error[16];
   short status[16];


  hexapod_ElectricalC()  { std::cout << "hexapod_ElectricalC()"  << std::endl; }
  ~hexapod_ElectricalC() { std::cout << "~hexapod_ElectricalC()"  << std::endl; }
};

struct hexapod_LimitSensorsC
{
   short liftoff[18];
   short limit[18];


  hexapod_LimitSensorsC()  { std::cout << "hexapod_LimitSensorsC()"  << std::endl; }
  ~hexapod_LimitSensorsC() { std::cout << "~hexapod_LimitSensorsC()"  << std::endl; }
};

struct hexapod_MetrologyC
{
   long distance[18];
   long error[18];
   short status[18];


  hexapod_MetrologyC()  { std::cout << "hexapod_MetrologyC()"  << std::endl; }
  ~hexapod_MetrologyC() { std::cout << "~hexapod_MetrologyC()"  << std::endl; }
};

struct hexapod_TCC
{
   float setpoint[16];
   float temperature[16];
   float error[16];
   short status[16];


  hexapod_TCC()  { std::cout << "hexapod_TCC()"  << std::endl; }
  ~hexapod_TCC() { std::cout << "~hexapod_TCC()"  << std::endl; }
};


struct hexapod_commandC
{
      char	device[32];
      char	property[32];
      char	action[32];
      char	value[32];
      char	modifiers[128];

      hexapod_commandC()  { std::cout << "hexapod_commandC() "  << std::endl; }
      ~hexapod_commandC()  { std::cout << "~hexapod_commandC() "  << std::endl; }
};
struct hexapod_ackcmdC
{
      long 	ack;
      long 	error;
      char	result[32];

      hexapod_ackcmdC()   { std::cout << "hexapod_ackcmdC() "  << std::endl; }
      ~hexapod_ackcmdC()  { std::cout << "~hexapod_ackcmdC() "  << std::endl; }
};
struct hexapod_logeventC
{
      char	message[128];

      hexapod_logeventC()   { std::cout << "hexapod_logeventC() "  << std::endl; }
      ~hexapod_logeventC()  { std::cout << "~hexapod_logeventC() "  << std::endl; }
};

