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

#include "TEST.h"

class SIMDTEST : public TESTDataReader,
		 public TESTDataWriter,
		 public TESTTypeSupport
{
public:
        SIMDTEST(std::string operation);
        ~SIMDTEST();
	DDS::Boolean _local_is_a (const char * _id);
	MYRTN publisher ();
	MYRTN subscriber ();
	MYRTN getSample (MYINT timeout);
	MYRTN putSample ();
	
private:
	static const char * _local_id;
	MYINT haveQos;
	MYINT haveDur;
	MYINT haveRdr;
	MYINT haveWrt;
	MYINT readCount;
	MYINT writeCount;
	MYINT priority;
	MYINT pid;
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
        dds::Topic<TEST> topic;
	TEST data;
	TESTSeq dataSeq;

};


#endif
