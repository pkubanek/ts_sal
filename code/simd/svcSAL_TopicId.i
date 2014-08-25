%module svcSAL_TopicId

%include "typemaps.i"
%include "carrays.i"

%array_class(unsigned short, uShortArray);

%{

#include "svcSAL.h"

class salTopicId
{
public:
        salTopiId();
        ~salTopicId();

	svcRTN checkStatus ();
	svcRTN getSample (svcINT timeout);
	svcRTN putSample ();
	svcRTN getItem ( svcNAME *item , svcSHORT &value );
	svcRTN getItem ( svcNAME *item , svcUSHORT &value );
	svcRTN getItem ( svcNAME *item , svcINT &value );
	svcRTN getItem ( svcNAME *item , svcUINT &value );
	svcRTN getItem ( svcNAME *item , svcFLT &fvalue );
	svcRTN getItem ( svcNAME *item , svcDBL &dvalue );
	svcRTN getItem ( svcNAME *item , svcSHORT &value , svcINT size );
	svcRTN getItem ( svcNAME *item , svcUSHORT &value, svcINT size );
	svcRTN getItem ( svcNAME *item , svcINT &value , svcINT size );
	svcRTN getItem ( svcNAME *item , svcUINT &value, svcINT size );
	svcRTN getItem ( svcNAME *item , svcFLT &fvalue, svcINT size );
	svcRTN getItem ( svcNAME *item , svcDBL &dvalue, svcINT size);
        svcRTN getItem ( svcNAME *itemName , svcCHAR *textValue);
	
	svcRTN putItem ( svcNAME *item , svcSHORT &value );
	svcRTN putItem ( svcNAME *item , svcUSHORT &value );
	svcRTN putItem ( svcNAME *item , svcINT &value );
	svcRTN putItem ( svcNAME *item , svcUINT &value );
	svcRTN putItem ( svcNAME *item , svcFLT &fvalue );
	svcRTN putItem ( svcNAME *item , svcDBL &dvalue );
	svcRTN putItem ( svcNAME *item , svcSHORT &value , svcINT size );
	svcRTN putItem ( svcNAME *item , svcUSHORT &value, svcINT size );
	svcRTN putItem ( svcNAME *item , svcINT &value , svcINT size );
	svcRTN purItem ( svcNAME *item , svcUINT &value, svcINT size );
	svcRTN putItem ( svcNAME *item , svcFLT &fvalue, svcINT size );
	svcRTN putItem ( svcNAME *item , svcDBL &dvalue, svcINT size);
        svcRTN putItem ( svcNAME *itemName , svcCHAR *textValue);

        svcRTN getProperty ( svcNAME *propertyName , svcCHAR *textValue);
        svcRTN setProperty ( svcNAME *propertyName , svcCHAR *textValue);
	
private:
	void *currentInstance= NULL;
        svcINT newData = SAL__NO_UPDATES;
	svtINT debugLevel;
        svcTIME timeOfSnd;
        svcTIME timeOfRcv;
	svcINT haveDur;
	svcINT haveRdr;
	svcINT haveWrt;
	svcINT readCount;
	svcINT writeCount;
	svcINT setHistoryDepth ( svcInt depth);
	svcINT setAutoDispose ( svcBool state);
	svcINT setQos (svcCHAR *parameter , svcCHAR value);
	svcINT priority;
	svcINT pid;
	dds::TopicQos tqos;
	dds::SampleInfo sinfo;
	dds::DataWriterQos wQos(dds::TopicQos Qos);
	dds::DataReaderQos rQos(dds::TopicQos Qos);
	dds::Duration latency_budget;
	dds::deadline;
	TopicId data;
	

};

%}
