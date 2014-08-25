// Template code for simd interface, replace TopicId
// with actual topic name
//  
//
#ifndef __INCLUDED_SAL_TopicId_CLASS
#define __INCLUDED_SAL_TopicId_CLASS
//
// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// -- SIMD Include
#include <dds/dds.hpp>

#include "svcSAL.h"
#include "svcSAL_sal.h"
#include "svcSAL_TopicId_iid.h"

class salTopicId : 	public TopicIdDataReader,
			public TopicIdDataWriter,
			public TopicIdTypeSupport,
			public sal
{
public:
        salTopicId(std::string operation);
        ~salTopicId();
	DDS::Boolean _local_is_a (const char * _id);
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
	static const char * _local_id;
        svcINT newData;
	svcINT debugLevel;
        svcTIME timeOfSnd;
        svcTIME timeOfRcv;
	svcINT haveQos;
	svcINT haveDur;
	svcINT haveRdr;
	svcINT haveWrt;
	svcINT readCount;
	svcINT writeCount;
	svcINT setHistoryDepth ( svcINT depth);
	svcINT setAutoDispose ( svcBOOL state);
	svcINT setQos (svcCHAR *parameter , svcCHAR value);
	svcINT priority;
	svcINT pid;
 	DDS::SampleInfoSeq sinfoSeq;
	dds::TopicQos tqos;
	dds::SampleInfo sinfo;
	dds::TopicQos rQos;
	dds::TopicQos wQos;
	DDS::InstanceHandle_t currentInstance;
	DDS::Duration_t deadline;
	DDS::Long dum1;
	DDS::SampleStateMask dum2;
	DDS::ViewStateMask dum3;
	DDS::InstanceStateMask dum4;	
        dds::Topic<TopicId> topic;
	TopicId data;
	TopicIdSeq dataSeq;

};


#endif
