
#include "svcSAL.h"
#include "svcSAL_validtopics.h"

class sal
{
public:
        sal::sal()
	{
	   dds::Runtime runtime("LSST");
	}
	
	
        ~sal::sal();

	svcTIME sal::currentTime ()
	{
            struct timeval now;
	    struct timezone zone;
	    gettimeofday(&now,&zone);
	    return (svcTIME now.tv_sec+now.tv_usec/1000000.);
	}
	
	svcINT sal::setDebug( level )
	{
	    debugLevel = level;
	}
		
	svcINT sal::getDebug( )
	{
	    return debugLevel;
	}


private:		
	debugLevel;
	
}


class salTelemetry
{
public:
        salTelemetry::salTelemetry();
        
	~salTelemetry::salTelemetry();
	
	svcRTN salTelemetry::setDebug( svcUINT level )
	{
	    debugLevel = level;
	}
	
		
	svcINT sal::getDebug( )
	{
	    return debugLevel;
	}

	svcRTN salTelemetry::connect( svcTID topicnumber)
	{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (topicnumber) {
	    
	    case SAL_SID_TopicId :
	    	salTopic = (TopicId *)new TopicId();
		result = SAL__OK;
		break;
		
	    case SAL_SID_OtherId :
	    	salTopic = (OtherId *)new OtherId();
		result = SAL__OK;
		break;
		
	    }
	    return result;
	}
        
	svcRTN salTelemetry::reSynchronize()
	{
	}
	
	svcRTN salTelemetry::checkStatus()
	{
	}
	
	
	void *salTopic = NULL;

	
};

class salAlert
{
public:
        salAlert::salAlert()
	{
	}
	
        ~alAlert::salAlert()
	{
	}
	
        svcRTN alAlert::generateAlert( svcINT severity , svcCHAR *details )
	{
	}
	
        svcRTN alAlert::catchAlerts( svcSID subsystemId , svcINT *callback()){
	}
	
};


class salCommand
{
public:
       salCommand::salCommand()
       {
       }
        
        ~salCommand::salCommand()
	{
	}
	
        svcRTN salCommand::issueCommand( svcSID subsystemId , 
                             svcCHAR *device , 
                             svcCHAR *property , 
                             svcCHAR *action , 
                             svcCHAR *value , 
                             svcCHAR *modifiers)
	{
	}
			     
        svcRTN salCommand::checkCommand( svcINT cmdSeqNum )
	{
	}
	
        svcRTN csalCommand::ancelCommand( svcINT cmdSeqNum )
	{
	}
	
        svcRTN asalCommand::bortCommand( svcINT cmdSeqNum )
	{
	}
	
        svcRTN salCommand::waitForCompletion( svcINT cmdSeqNum , svcINT timeout )
	{
	}
	
	svcRTN salCommand::setDebugLevel( svcUINT level )
	{
	}

};

