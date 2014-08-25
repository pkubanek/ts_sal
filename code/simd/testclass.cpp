
// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
using namespace std;

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// -- SIMD Include
#include <dds/dds.hpp>

// -- TEST Include
#include <gen/ccpp_TEST.h>

REGISTER_TOPIC_TRAITS(TEST);
std::string topic("TESTTopic");

#include "TEST.h"

SIMDTEST::SIMDTEST()
{
     char *env;
     string PubOP("publish");
     
	currentInstance= NULL;
        haveQos = 0;
	haveDur = 0;
	haveRdr = 0;
	haveWrt = 0;
	priority = 0;
	pid = 0;
	readCount = 0;
	writeCount = 0;
	deadline = {1,0};
	dds::Runtime runtime();
	tqos.set_reliable();
	tqos.set_transient();
	tqos.set_deadline(deadline);
	tqos.set_priority(priority);
        tqos.set_keep_last(SAL__DEFAULT_HISTORY_DEPTH);
        if (operation.compare(PubOP) == 0) {
           dds::DataWriter<TEST> writer(TESTTopic,wQos);
           haveWrt = TRUE;
        } else {
           dds::DataReader<TEST> reader;
           haveRdr = TRUE;
        }
}

 
SIMDTEST::~SIMDTEST()
{
}



MYRTN SIMDTEST::getSample (MYINT timeout)
{
    MYRTN result;
    MYINT remaining;
   
    result = SIMDTEST::read(dataSeq,sinfoSeq,dum1,dum2,dum3,dum4);
    return 0;
}

MYRTN SIMDTEST::putSample () {
    MYRTN result;
    result = SIMDTEST::write(data,currentInstance);
    writeCount++;
    return 0;
}

DDS::Boolean SIMDTEST::_local_is_a (const char * _id)
{
   if (strcmp (_id, SIMDTEST::_local_id) == 0) return true;

   typedef SIMDTEST NestedBase_1;

   if (NestedBase_1::_local_is_a (_id)) return true;

   return false;
}



