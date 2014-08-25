// Generic code for simd interface, replace TopicId
// with actual topic name, then process through INSERT_PERTOPIC
// to add data exchangers

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

// -- TopicId Include
#include <gen/ccpp_TopicId.h>

REGISTER_TOPIC_TRAITS(TopicId);

// -- SAL Include
#include "sal/svcSAL.h"
#include "sal/svcSAL_TopidId.h"

class salTopicId
{
public:


salTopicId::salTopicId()
{
     char *env;
     
	currentInstance= NULL;
        newData = SAL__NO_UPDATES;
        env = (char *) (getgenv("SAL_DEBUG_LEVEL"));
	if ( env !- NULL ) {
           sscanf(env, "%d", &debugLevel);
	}
	debugLevel = 0;
        timeOfSnd = 0.0;
        timeOfRcv = 0.0;
        haveQos = 0;
	haveDur = 0;
	haveRdr = 0;
	haveWrt = 0;
	priority = 0;
	pid = 0;
	readCount = 0;
	writeCount = 0;
	latency_budget = {1,0);
	deadline = {1,0};
	pid = getpid();
	dds::Runtime runtime();
	tqos.set_reliable();
	tqos.set_transient();
	tqos.set_latency_budget(latency_budget);
	tqos.set_deadline(deadline);
	tqos.set_priority(priority);
	dds::Topic<TopicIdType> topic("TopicId", tqos);
 }

 
svcRTN salTopicId::~salTopicId()
{
}



svcRTN salTopicId::publisher ()
{

   if (!haveWrt) {
      dds::DataWriterQos wQos(tqos);
      wQos.set_keep_last(SAL__DEFAULT_HISTORY_DEPTH);
      wQos.set_auto_dispose(SAL__DEFAULT_AUTO_DISPOSE);
      dds::DataWriter<TopicIdType> writer(topic,wQos);
      dds::DataWriter<TopicId> writer(TopicIdTopic);
      haveWrt = TRUE;
   }
  
}

svcRTN salTopicId::subscriber ()
{

   if {!haveRdr} {
      dds::DataReaderQos rQos(tqos);
      dds::DataReader<TopicIdType> reader(topic, rQos();
      haveRdr = TRUE;
   }
   
   
svcRTN salTopicId::getSample (svcInt timeout)
{
    svcRTN result;
    svcINT remaining;
    
    remaining = timeout+1;
    while (remaining >= 0) {
      result = reader.read(data,sinfo);
      if { result != DDS::RETCODE_OK ) {
         if ( result != DDS_RETCODE_TIMEOUT &&
	      result != DDS:RETCODE_NODATA ) {
            if (remaining < 0) {
	       return result;
	    }
         }
      } else {
         data.private_rcvStamp = sal::currentTime();
	 timeOfRcv = data.private_rcvStamp;
	 readCount++;
	 if (timeout == SAL__WAIT_FOR_CHANGE) {
	 } else { 
	    return SAL__OK;
	 }
      }
      remaining = remaining - 1000;
      usleep(SAL__FASTPOLL);
    }
    return SAL__TIMEOUT;
}

svcRTN salTopicId::putSample () {
    svcRTN result;
    data.private_sndStamp = sal::currentTime();
    timeOfSnd = data.private_rcvStamp;
    data.private_origin = pid;
    result = writer.write(data);
    writeCount++;
    return SAL__OK;
}

// INSERT-PERTOPIC
	svcRTN getItem ( svcIID itemId , svcSHORT &value );
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcUSHORT &value )
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcINT &value )
	{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (itemOd) {
	    
	    case SAL_IID_TopicId_number :
	    	value = data.number;
		result = SAL__OK;
		break;
		
	    case SAL_IID_TopicId_counter :
	    	value = data.counter;
		result = SAL__OK;
		break;		
		
	    }
	    return result;
	}
	
	svcRTN getItem ( svcIID itemId , svcUINT &value )
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcFLT &fvalue )
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcDBL &dvalue )
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcSHORT &value , svcINT size )
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcUSHORT &value, svcINT size )
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcINT &value , svcINT size )
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcUINT &value, svcINT size )
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcFLT &fvalue, svcINT size );
	{
	}
	
	svcRTN getItem ( svcIID itemId , svcDBL &dvalue, svcINT size)
	{
	}
	
        svcRTN getItemStr ( svcIID itemId , svcCHAR *textValue)
	{
	    svcRTN result = SAL__NOT_DEFINED;
	    
	    switch (itemid) {
	    case SAL_IID_TopicId_number :
	        sprintf(textValue,"%d",data.number);
//	        snprintf(textValue,strlen()textValue),"%d",data.number);
		result = SAL__OK;
		break;
		
	    case SAL_IID_TopicId_counter :
	        sprintf(textValue,"%d",data.counter);
		result = SAL__OK;
		break;
		
	    case SAL_IID_TopicId_vendor :
	    	strcpy(textValue,data.venndor);
		result = SAL__OK;
		break;
		
	    }
	}
	
	
	svcRTN setItem ( svcIID itemId , svcSHORT &value )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcUSHORT &value )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcINT &value )
	{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (itemOd) {
	    
	    case SAL_IID_TopicId_number :
	    	data.numnber = value;
		result = SAL__OK;
		break;
		
	    case SAL_IID_TopicId_counter :
	    	data.counter = value;
		result = SAL__OK;
		break;		
		
	    }
	    return result;
	}
	
	svcRTN setItem ( svcIID itemId , svcUINT &value )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcFLT &fvalue )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcDBL &dvalue )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcSHORT &value , svcINT size )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcUSHORT &value, svcINT size )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcINT &value , svcINT size )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcUINT &value, svcINT size )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcFLT &fvalue, svcINT size )
	{
	}
	
	svcRTN setItem ( svcIID itemId , svcDBL &dvalue, svcINT size)
	{
	}
	
        svcRTN setItemStr ( svcIID itemId , svcCHAR *textValue)
	{
	    svcRTN result = SAL__NOT_DEFINED;
	    
	    switch (itemid) {
	    case SAL_IID_TopicId_number :
	    	sscanf(textValue,"%d",&data.number);
		result = SAL__OK;
		break;
		
	    case SAL_IID_TopicId_counter :
	    	sscanf(textValue,"%d",&data.counter);
		result = SAL__OK;
		break;
		
	    case SAL_IID_TopicId_vendor :
	    	strcpy(data.vendor,textValue);
		result = SAL__OK;
		break;
		
	    }
	    
	}
	

        svcRTN getProperty ( svcCHAR *propertyName , svcCHAR *textValue)
	{
	}
	
        svcRTN setProperty ( svcCHAR *propertyName , svcCHAR *textValue)
	{
	}
	


}
