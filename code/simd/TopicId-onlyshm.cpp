// Generic code for simd interface, replace TopicId
// with actual topic name, then process through INSERT_PERTOPIC
// to add data exchangers

// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>
#include <ctime>
#include <string>
using namespace std;

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


// -- SAL Include
#include "svcSAL_TopicId-onlyshm.h"
#include "shmem_TopicId.h"
#include "svcSAL_camera_topics.h"

void salTopicId::GetObject(TopicId_cache *  pshm_TopicId) {
       pshm_TopicId = (TopicId_cache *)m_shared_mem;
}


salTopicId::salTopicId()
{
     char *env;
     string PubOP("publish");
     
	currentInstance= NULL;
        newData = SAL__NO_UPDATES;
        env = (char *) (getenv("SAL_DEBUG_LEVEL"));
	if ( env != NULL ) {
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
        lastI=0;
	deadline = 0;
	pid = getpid();
}

 
salTopicId::~salTopicId()
{
}



svcRTN salTopicId::publisher ()
{
   if ( !haveWrt ) {
      haveWrt = 1;
   }
   return SAL__OK;
}

svcRTN salTopicId::subscriber ()
{
   if ( !haveRdr ) {
      haveRdr = 1;
   }
   return SAL__OK;
}


svcRTN salTopicId::getSample (svcINT timeout)
{
    svcRTN result;
    svcINT remaining;
   
    result = SAL__TIMEOUT;
    remaining = timeout+1;
    while (remaining >= 0) {
      if (data.syncI != lastI) {
//         data.private_rcvStamp = currentTime();
	 timeOfRcv = data.private_rcvStamp;
	 readCount++;
         lastI = data.syncI;
	 return SAL__OK;
      }
      remaining = remaining - 1000;
      if (remaining < 0 && timeout != SAL__WAIT_FOR_CHANGE) {
	 return result;
      }
      usleep(SAL__FASTPOLL);
    }
    return SAL__TIMEOUT;
}

svcRTN salTopicId::putSample () {
    svcRTN result;
    result = SAL__ERR;
//    data.private_sndStamp = currentTime();
    timeOfSnd = data.private_rcvStamp;
    data.private_origin = pid;
    data.syncO = 1;
    writeCount++;
    return SAL__OK;
}

svcRTN salTopicId::getProperty ( svcCHAR *propertyName , svcCHAR *textValue)
{
    return SAL__OK;
}
	
svcRTN salTopicId::setProperty ( svcCHAR *propertyName , svcCHAR *textValue)
{
    return SAL__OK;
}
	


svcRTN salTopicId::salConnect(std::string operation)
{
       TopicId_cache *ptrshm;
       
       key_t key = 0x90a0;
       size_t TopicId_shmsize = sizeof(TopicId_cache);
       bool bCreated = false;

       m_TopicId_shmid = shmget(key, TopicId_shmsize, 0666);

       if (-1 == m_TopicId_shmid) {

           if (ENOENT != errno) {
               cerr << __FILE__ <<  ":" <<  __LINE__ <<  " Critical error in shmget"  << endl;
               return SAL__ERR;
           }

           m_TopicId_shmid = shmget(key, TopicId_shmsize, IPC_CREAT | 0666);

           if (-1 == m_TopicId_shmid) {
               cerr <<  __FILE__ <<  ":" <<  __LINE__ <<  " Critical error in shmget" << endl;
               return SAL__ERR;
           }

           cout <<   "Created the shared memory" <<  endl;
           bCreated = true;
       }

       m_shared_mem = shmat(m_TopicId_shmid, NULL, 0);

       if (-1 == (int)salTopicId::m_shared_mem) {
           cerr <<  __FILE__ <<  ":" <<  __LINE__ <<  " Critical error in shmat" << endl;
           return SAL__ERR;
       }

       if (bCreated) {
           // Construct objects on the shared memory
	   ptrshm = (TopicId_cache *)m_shared_mem;
           data.syncO = 0;
       }

       return SAL__OK;
}

svcRTN salTopicId::shmInfo() {
       cout <<  "Object type: shm_TopicId" <<  endl;
       return SAL__OK;
}

svcTIME salTopicId::getCurrentTime ()
{
//   struct timeval now1;
//   struct timezone zone;
//   gettimeofday(&now1,&zone);
//   return (svcTIME now1.tv_sec+now1.tv_usec/1000000.);
   return(0.0);
};

// INSERT PERTOPIC_METHODS


