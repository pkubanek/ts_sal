// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- BOOST Include
#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>

// -- SIMD Include
#include <dds/dds.hpp>

#include "svcSAL.h"
#include "svcSAL_validtopics.h"

int main(int argc, char* argv[]) 
{
	salRTN result = 0;
	salINT iseq  =  1;
//	TopicId *top1;
	
	salInstance = (sal *)new sal();
	salpub1 = (salTelemetry *)new salTelemetry();

	sprintf ("SAL timestamp is %lf\n", salInstance->currentTime());

	result = salpub1->connect(sid_TopicId);
	if (result == SAL__OK) {
//	   top1 = (TopicId *)salpub1.salTopic;
	} else {
	   printf ("connect failed %d\n",result);
	}
	
	if (strcmp(argv[1],"publish")==0) {
   	   result = salpub1->salTopic->publisher();
//	result = top1->publisher();
	} else {
   	   result = salpub1->salTopic->subscriber);	   
//	result = top1->subscriber();
	}

        while (1) {

 	if (strcmp(argv[1],"publish")==0) {
 	  result = salpub1->salTopic->setItem(SAL_IID_TopicId_number, iseq);
	  result = salpub1->salTopic->setItem(SAL_IID_TopicId_counter, iseq);
	  result = salpub1->salTopic->setItem(SAL_IID_TopicId_vendor, "LSST SAL");	
	  result = salpub1->salTopic->putSample();
//  	  result = top1->setItem(SAL_IID_TopicId_number, iseq);
//	  result = top1->setItem(SAL_IID_TopicId_counter, iseq);
//	  result = top1->setItem(SAL_IID_TopicId_vendor, "LSST SAL");	
//	  result = top1->putSample();

   	  sleep(5);
          incr iseq 1;
	  
       } else {
	  result = salpub1->salTopic->getSample(SAL__SLOWPOLL);
 	  result = salpub1->salTopic->getItem(SAL_IID_TopicId_number, &iseq);
	  result = salpub1->salTopic->getItem(SAL_IID_TopicId_counter, &iseq);
	  result = salpub1->salTopic->getItem(SAL_IID_TopicId_vendor, &istring);	
//	  result = top1->getSample(SAL__SLOWPOLL);
//  	  result = top1->getItem(SAL_IID_TopicId_number, iseq);
//	  result = top1->getItem(SAL_IID_TopicId_counter, iseq);
//	  result = top1->getItem(SAL_IID_TopicId_vendor, "LSST SAL");	
          printf("number = %d, text = %s\n",iseq,istring);
       }
       
       
 
       }

}



