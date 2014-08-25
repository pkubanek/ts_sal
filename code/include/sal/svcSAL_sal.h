
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
	svcRTN getItem ( int itemId , svcUSHORT *value );
	svcRTN getItem ( int itemId , svcINT *value );
	svcRTN getItem ( int itemId , svcULONG *value );
	svcRTN getItem ( int itemId , svcLONG *value );
	svcRTN getItem ( int itemId , svcUINT *value );
	svcRTN getItem ( int itemId , svcFLT *fvalue );
	svcRTN getItem ( int itemId , svcDBL *dvalue );
	svcRTN getItem ( int itemId , svcSHORT *value , svcUINT& size );
	svcRTN getItem ( int itemId , svcUSHORT *value, svcUINT& size );
	svcRTN getItem ( int itemId , svcINT *value , svcUINT& size );
	svcRTN getItem ( int itemId , svcUINT *value, svcUINT& size );
	svcRTN getItem ( int itemId , svcLONG *value , svcUINT& size );
	svcRTN getItem ( int itemId , svcULONG *value, svcUINT& size );
	svcRTN getItem ( int itemId , svcFLT *fvalue, svcUINT& size );
	svcRTN getItem ( int itemId , svcDBL *dvalue, svcUINT& size);
        svcRTN getItemStr ( int itemId , svcCHAR *textValue);
	
	svcRTN setItem ( int itemId , svcSHORT *value );
	svcRTN setItem ( int itemId , svcUSHORT *value );
	svcRTN setItem ( int itemId , svcINT *value );
	svcRTN setItem ( int itemId , svcULONG *value );
	svcRTN setItem ( int itemId , svcLONG *value );
	svcRTN setItem ( int itemId , svcUINT *value );
	svcRTN setItem ( int itemId , svcFLT *fvalue );
	svcRTN setItem ( int itemId , svcDBL *dvalue );
	svcRTN setItem ( int itemId , svcSHORT *value , svcUINT& size );
	svcRTN setItem ( int itemId , svcUSHORT *value, svcUINT& size );
	svcRTN setItem ( int itemId , svcINT *value , svcUINT& size );
	svcRTN setItem ( int itemId , svcUINT *value, svcUINT& size );
	svcRTN setItem ( int itemId , svcLONG *value , svcUINT& size );
	svcRTN setItem ( int itemId , svcULONG * value, svcUINT& size );
	svcRTN setItem ( int itemId , svcFLT *fvalue, svcUINT& size );
	svcRTN setItem ( int itemId , svcDBL *dvalue, svcUINT& size);
        svcRTN setItemStr ( int itemId , svcCHAR *textValue);

        svcRTN getProperty ( svcCHAR *propertyName , svcCHAR *textValue);
        svcRTN setProperty ( svcCHAR *propertyName , svcCHAR *textValue);
	void *salTopic;
};


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


