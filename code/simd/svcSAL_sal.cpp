
#include "svcSAL.h"
#include "svcSAL_sal.h"
#include "svcSAL_validtopics.h"

        sal::sal()
	{
	}
	
	
        ~sal::sal()
	{
	}

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

	salTelemetry::salTelemetry()
	{
	}
	
	~salTelemetry::salTelemetry()
	{
	}

        svcRTN salTelemetry::salConnect(svcTID topicnumber, std::string operation)
	{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (topicnumber) :	    

	    case SAL_IID_camera_BEE_biases :
	    	salTopic = (camera_BEE_biases *)new camera_BEE_biases(operation);
		result = SAL__OK;
		break;


	    default :
		result = SAL__NOT_DEFINED;
	
	    }
	    return result;
	}
               
	svcRTN salTelemetry::reSynchronize()
	{
	}
	
	svcRTN salTelemetry::checkStatus()
	{
	}
	
	svcRTN salTelemetry::getSample (svcINT timeout)
	{
	}
	svcRTN salTelemetry::putSample ()
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcSHORT *value )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcUSHORT *value )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcINT *value )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcULONG *value )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcLONG *value )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcUINT *value )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcFLT *fvalue )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcDBL *dvalue )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcSHORT *value , svcUINT& size )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcUSHORT *value, svcUINT& size )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcINT *value , svcUINT& size )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcUINT *value, svcUINT& size )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcLONG *value , svcUINT& size )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcULONG *value, svcUINT& size )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcFLT *fvalue, svcUINT& size )
	{
	}
	svcRTN salTelemetry::getItem ( int itemId , svcDBL *dvalue, svcUINT& size)
	{
	}
        svcRTN salTelemetry::getItemStr ( int itemId , svcCHAR *textValue)
	
	svcRTN salTelemetry::setItem ( int itemId , svcSHORT *value )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcUSHORT *value )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcINT *value )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcULONG *value )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcLONG *value )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcUINT *value )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcFLT *fvalue )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcDBL *dvalue )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcSHORT *value , svcUINT& size )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcUSHORT *value, svcUINT& size )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcINT *value , svcUINT& size )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcUINT *value, svcUINT& size )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcLONG *value , svcUINT& size )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcULONG * value, svcUINT& size )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcFLT *fvalue, svcUINT& size )
	{
	}
	svcRTN salTelemetry::setItem ( int itemId , svcDBL *dvalue, svcUINT& size)
 	{
	}
        svcRTN salTelemetry::setItemStr ( int itemId , svcCHAR *textValue)
 	{
	}

        svcRTN salTelemetry::getProperty ( svcCHAR *propertyName , svcCHAR *textValue)
	{
	}
        svcRTN salTelemetry::setProperty ( svcCHAR *propertyName , svcCHAR *textValue)
	{
	}
	
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
	
        svcRTN csalCommand::cancelCommand( svcINT cmdSeqNum )
	{
	}
	
        svcRTN asalCommand::abortCommand( svcINT cmdSeqNum )
	{
	}
	
        svcRTN salCommand::waitForCompletion( svcINT cmdSeqNum , svcINT timeout )
	{
	}
	
	svcRTN salCommand::setDebugLevel( svcUINT level )
	{
	}


