// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
using namespace std;

// -- BOOST Include
//#include <boost/shared_ptr.hpp>
//#include <boost/program_options.hpp>

// -- SIMD Include
//#include <dds/dds.hpp>

#include "svcSAL_sal.h"

int main(int argc, char* argv[]) 
{
        std::string op(argv[1]);
	svcRTN result = 0;
	svcUINT idim = 202;
        salTelemetry *salHandle;
	svcLONG reset[201];
	svcLONG operate[201];
	svcLONG substrate[201];
	svcLONG *preset=&reset[0];
	svcLONG *poperate=&operate[0];
	svcLONG *psubstrate=&substrate[0];

	salHandle = (salTelemetry *)new salTelemetry();
	printf ("SAL timestamp is %lf\n", salHandle->getCurrentTime());
	result = salHandle->salConnect(SAL_SID_camera_BEE_biases,op);

	if (result != SAL__OK) {
	   printf ("Topic initialization failed %d\n",result);
           exit(1);
	}
	
        while (1) {

 	if (strcmp(argv[1],"publish")==0) {
          for (svcUINT i=1;i<idim;i++) {
              reset[i]=i;
              operate[i]=i;
              substrate[i]=i;
          }
  	  result = salHandle->setItem(SAL_IID_camera_BEE_biases_reset, preset, idim);
	  result = salHandle->setItem(SAL_IID_camera_BEE_biases_operate, poperate, idim);
	  result = salHandle->setItem(SAL_IID_camera_BEE_biases_substrate, psubstrate, idim);	
	  result = salHandle->putSample();
	
   	  sleep(5);
	  
       } else {
	  result = salHandle->getSample(SAL__SLOWPOLL);
  	  result = salHandle->getItem(SAL_IID_camera_BEE_biases_reset, preset,idim);
	  result = salHandle->getItem(SAL_IID_camera_BEE_biases_operate, poperate,idim);
	  result = salHandle->getItem(SAL_IID_camera_BEE_biases_substrate, psubstrate,idim);	
          printf("data = %ld, %ld , %ld\n",reset[0],operate[100],substrate[200]);
       }
              
 
       }

}



