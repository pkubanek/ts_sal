

#include <sys/types.h>
#include <sys/ipc.h>

#include <sys/shm.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "shmem_tcs_kernel_Target.h"

void * shm_tcs_kernel_Target::m_shared_mem = NULL;

void * shm_tcs_kernel_Target::operator new (unsigned int size)
{
       switch (size)
       {
       case sizeof(shm_tcs_kernel_Target):
           return m_shared_mem;

       default:
           cerr << __FILE__ << ":" << __LINE__ << " Critical error in new"  << endl;
       }
}

void shm_tcs_kernel_Target::Handle() {
       cout <<  "Object type: shm_tcs_kernel_Target" <<  endl;
}


void GetObject_tcs_kernel_Target(shm_tcs_kernel_Target ** pshm_tcs_kernel_Target) {
       *pshm_tcs_kernel_Target = (shm_tcs_kernel_Target *)shm_tcs_kernel_Target::m_shared_mem;
}


class Initializer {
   public:
       int m_tcs_kernel_Target_shmid;
       Initializer();

       static Initializer m_sInitializer;
   };

   Initializer Initializer::m_sInitializer;

   Initializer::Initializer()
   {
       key_t key = 0xde92;
       size_t tcs_kernel_Target_shmsize = 132;
       bool bCreated = false;

       m_tcs_kernel_Target_shmid = shmget(key, tcs_kernel_Target_shmsize, 0666);

       if (-1 == m_tcs_kernel_Target_shmid) {

           if (ENOENT != errno) {
               cerr << __FILE__ <<  ":" <<  __LINE__ <<  " Critical error in shmget"  << endl;
               return;
           }

           m_tcs_kernel_Target_shmid = shmget(key, tcs_kernel_Target_shmsize, IPC_CREAT | 0666);

           if (-1 == m_tcs_kernel_Target_shmid) {
               cerr <<  __FILE__ <<  ":" <<  __LINE__ <<  " Critical error in shmget" << endl;
               return;
           }

           cout <<   "Created the shared memory" <<  endl;
           bCreated = true;
       }

       shm_tcs_kernel_Target::m_shared_mem = shmat(m_tcs_kernel_Target_shmid, NULL, 0);

       if (-1 == (int)shm_tcs_kernel_Target::m_shared_mem) {
           cerr <<  __FILE__ <<  ":" <<  __LINE__ <<  " Critical error in shmat" << endl;
           return;
       }

       if (bCreated) {
           // Construct objects on the shared memory
           shm_tcs_kernel_Target * pshm_tcs_kernel_Target;
           pshm_tcs_kernel_Target = new shm_tcs_kernel_Target;
           pshm_tcs_kernel_Target->syncO = 0;
       }

       return;
}

