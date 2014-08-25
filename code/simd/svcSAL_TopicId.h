// Template code for simd interface, replace TopicId
// with actual topic name
//  
//
//

#include <gen/ccpp_TopicId.h>

REGISTER_TOPIC_TRAITS(TopicId);

#include "svcSAL.h"

class salTopicId
{
public:
        salTopiId();
        ~salTopicId();

	svcRTN publisher ();
	svcRTN subscriber ();
	svcRTN getSample (svcINT timeout);
	svcRTN putSample ();
	svcRTN getItem ( svcIID itemId , svcSHORT &value );
	svcRTN getItem ( svcIID itemId , svcUSHORT &value );
	svcRTN getItem ( svcIID itemId , svcINT &value );
	svcRTN getItem ( svcIID itemId , svcUINT &value );
	svcRTN getItem ( svcIID itemId , svcFLT &fvalue );
	svcRTN getItem ( svcIID itemId , svcDBL &dvalue );
	svcRTN getItem ( svcIID itemId , svcSHORT &value , svcINT size );
	svcRTN getItem ( svcIID itemId , svcUSHORT &value, svcINT size );
	svcRTN getItem ( svcIID itemId , svcINT &value , svcINT size );
	svcRTN getItem ( svcIID itemId , svcUINT &value, svcINT size );
	svcRTN getItem ( svcIID itemId , svcFLT &fvalue, svcINT size );
	svcRTN getItem ( svcIID itemId , svcDBL &dvalue, svcINT size);
        svcRTN getItemStr ( svcIID itemId , svcCHAR *textValue);
	
	svcRTN setItem ( svcIID itemId , svcSHORT &value );
	svcRTN setItem ( svcIID itemId , svcUSHORT &value );
	svcRTN setItem ( svcIID itemId , svcINT &value );
	svcRTN setItem ( svcIID itemId , svcUINT &value );
	svcRTN setItem ( svcIID itemId , svcFLT &fvalue );
	svcRTN setItem ( svcIID itemId , svcDBL &dvalue );
	svcRTN setItem ( svcIID itemId , svcSHORT &value , svcINT size );
	svcRTN setItem ( svcIID itemId , svcUSHORT &value, svcINT size );
	svcRTN setItem ( svcIID itemId , svcINT &value , svcINT size );
	svcRTN setItem ( svcIID itemId , svcUINT &value, svcINT size );
	svcRTN setItem ( svcIID itemId , svcFLT &fvalue, svcINT size );
	svcRTN setItem ( svcIID itemId , svcDBL &dvalue, svcINT size);
        svcRTN setItemStr ( svcIID itemId , svcCHAR *textValue);

        svcRTN getProperty ( svcCHAR *propertyName , svcCHAR *textValue);
        svcRTN setProperty ( svcCHAR *propertyName , svcCHAR *textValue);
	
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
	TopicIdType data;
	

};

