
#if !defined(__SAL_INCLUDED_BASE)
#define __SAL_INCLUDED_BASE

#include <string>
using namespace std;

#include "svcSAL.h"
#include "svcSAL_validtopics.h"


class sal
{
public:
	svcTIME getCurrentTime();	
	svcINT setDebug(svcUINT level);		
	svcINT getDebug();
};

 
template <typename T>
template <class C>  
class  salTelemetry : public sal
{
public:
       	salTelemetry();	
       	~salTelemetry();	
       	svcRTN salConnect(svcTID topicnumber, std::string operation);	
	svcRTN reSynchronize();
	svcRTN checkStatus();
	svcRTN getSample (svcINT timeout);
	svcRTN putSample ();
	svcRTN getItem ( int itemId , svcSHORT *value );
        svcRTN getItemStr ( int itemId , svcCHAR *textValue);
	
	svcRTN setItem ( int itemId , svcSHORT *value );
        svcRTN setItemStr ( int itemId , svcCHAR *textValue);

        svcRTN getProperty ( svcCHAR *propertyName , svcCHAR *textValue);
        svcRTN setProperty ( svcCHAR *propertyName , svcCHAR *textValue);
	<T> *salTopic;
};

salTelemetry::salTelemetry()
	{
	}
	
~salTelemetry::salTelemetry()
	{
	}

svcRTN salTelemetry::salConnect(const C& id, std::string operation)
	{
	    svcRTN result = SAL__NOT_DEFINED;
      	    salTopic = (<C> *)new <C>(operation);
	    result = SAL__OK;
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
	    svcRTN result = SAL__NOT_DEFINED;
            result =(<C> *)salTopic->getSample(timeout);
	    return result;
            
	}
	svcRTN salTelemetry::putSample ()
	{
	    svcRTN result = SAL__NOT_DEFINED;
            result = (<C> *)salTopic->putSample();
	    return result;
	}

svcRTN salTelemetry::getItem ( int itemId , <T> *value )
	{
	    svcRTN result = SAL__NOT_DEFINED;
            result = (<C> *)salTopic->getItem ( itemId , value );
	    return result;
	}

svcRTN salTelemetry::getItem ( int itemId , <T> *value, int size )
	{
	    svcRTN result = SAL__NOT_DEFINED;
            result = (<C> *)salTopic->getItem ( itemId , value , size );
	    return result;
	}

svcRTN salTelemetry::getItemStr ( int itemId , <T> *value, svcCHAR *textValue)
	{
	    svcRTN result = SAL__NOT_DEFINED;
            result = (<C> *)salTopic->getItemStr ( itemId , value , textValue );
	    return result;
	}

svcRTN salTelemetry::setItem ( int itemId , <T> *value )
	{
	    svcRTN result = SAL__NOT_DEFINED;
            result = (<C> *)salTopic->setItem ( itemId , value );
	    return result;
	}

svcRTN salTelemetry::setItem ( int itemId , <T> *value, int size )
	{
	    svcRTN result = SAL__NOT_DEFINED;
            result = (<C> *)salTopic->setItem ( itemId , value , size );
	    return result;
	}

svcRTN salTelemetry::setItemStr ( int itemId , <T> *value, svcCHAR *textValue)
	{
	    svcRTN result = SAL__NOT_DEFINED;
            result = (<C> *)salTopic->setItemStr ( itemId , value , textValue );
	    return result;
	}



class salAlert : public sal
{
public:
        salAlert();
        ~salAlert();
        svcRTN generateAlert(svcINT severity , svcCHAR *detail);
        svcRTN catchAlerts(svcSID subsystemId , svcINT *callback());
};


class salCommand : public sal
{
public:
       salCommand(); 
       ~salCommand();
       svcRTN issueCommand(svcSID subsystemId , 
                             svcCHAR *device , 
                             svcCHAR *property , 
                             svcCHAR *action , 
                             svcCHAR *value , 
                             svcCHAR *modifiers);
        svcRTN checkCommand(svcINT cmdSeqNum);
        svcRTN cancelCommand(svcINT cmdSeqNum);
        svcRTN abortCommand(svcINT cmdSeqNum);
        svcRTN waitForCompletion(svcINT cmdSeqNum , svcINT timeout);
};


#endif


