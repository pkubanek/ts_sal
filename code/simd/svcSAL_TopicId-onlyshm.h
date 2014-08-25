// Template code for simd interface, replace TopicId
// with actual topic name
//  
//
#ifndef __INCLUDED_SAL_TopicId_SHMCLASS
#define __INCLUDED_SAL_TopicId_SHMCLASS
//
// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


#include "svcSAL.h"
#include "svcSAL_TopicId_iid.h"
#include "TopicId_cache.h"


	
class salTopicId : 	public sal

{
public:
        salTopicId();
        ~salTopicId();
       	svcRTN salTelemetry();	
       	svcRTN salConnect(svcTID topicnumber, std::string operation);	
        virtual void Handle();
        void GetObject( camera_TC_zone1_cache *pshm);
	svcRTN reSynchronize();
	svcRTN publisher ();
	svcRTN subscriber ();
	svcRTN getSample (svcINT timeout);
	svcRTN putSample ();
        svcRTN shmInfo ();
	svcTIME getCurrentTime();	
	svcINT setDebug(svcUINT level);		
	svcINT getDebug();
	svcRTN getItem ( svcIID itemId , svcSHORT &value );
	svcRTN getItem ( svcIID itemId , svcUSHORT &value );
	svcRTN getItem ( svcIID itemId , svcINT &value );
	svcRTN getItem ( svcIID itemId , svcUINT &value );
	svcRTN getItem ( svcIID itemId , svcLONG &value );
	svcRTN getItem ( svcIID itemId , svcFLT &fvalue );
	svcRTN getItem ( svcIID itemId , svcULONG &value );
	svcRTN getItem ( svcIID itemId , svcDBL &dvalue );
	svcRTN getItem ( svcIID itemId , svcSHORT value[] , svcINT size );
	svcRTN getItem ( svcIID itemId , svcUSHORT value[], svcINT size );
	svcRTN getItem ( svcIID itemId , svcINT value[] , svcINT size );
	svcRTN getItem ( svcIID itemId , svcUINT value[], svcINT size );
	svcRTN getItem ( svcIID itemId , svcLONG value[] , svcINT size );
	svcRTN getItem ( svcIID itemId , svcULONG value[] , svcINT size );
	svcRTN getItem ( svcIID itemId , svcFLT fvalue[], svcINT size );
	svcRTN getItem ( svcIID itemId , svcDBL dvalue[], svcINT size);
        svcRTN getItemStr ( svcIID itemId , svcCHAR *textValue);
	
	svcRTN setItem ( svcIID itemId , svcSHORT &value );
	svcRTN setItem ( svcIID itemId , svcUSHORT &value );
	svcRTN setItem ( svcIID itemId , svcINT &value );
	svcRTN setItem ( svcIID itemId , svcUINT &value );
	svcRTN setItem ( svcIID itemId , svcLONG &value );
	svcRTN setItem ( svcIID itemId , svcULONG &value );
	svcRTN setItem ( svcIID itemId , svcFLT &fvalue );
	svcRTN setItem ( svcIID itemId , svcDBL &dvalue );
	svcRTN setItem ( svcIID itemId , svcSHORT value[] , svcINT size );
	svcRTN setItem ( svcIID itemId , svcUSHORT value[], svcINT size );
	svcRTN setItem ( svcIID itemId , svcINT value[] , svcINT size );
	svcRTN setItem ( svcIID itemId , svcUINT value[], svcINT size );
	svcRTN setItem ( svcIID itemId , svcLONG value[] , svcINT size );
	svcRTN setItem ( svcIID itemId , svcULONG value[] , svcINT size );
	svcRTN setItem ( svcIID itemId , svcFLT fvalue[], svcINT size );
	svcRTN setItem ( svcIID itemId , svcDBL dvalue[], svcINT size);
        svcRTN setItemStr ( svcIID itemId , svcCHAR *textValue);

        svcRTN getProperty ( svcCHAR *propertyName , svcCHAR *textValue);
        svcRTN setProperty ( svcCHAR *propertyName , svcCHAR *textValue);
	
private:
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
	svcINT lastI;
	svcINT priority;
	svcINT pid;
	TopicId data;
        svcINT m_TopicId_shmid;
        TopicId_cache *m_shared_mem;
        TopicId_cache *data;

};


#endif
