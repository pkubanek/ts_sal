

#include <iostream>
#include <stdlib.h>
using namespace std;

#include "shmem_tcs_kernel_Target.h"

int main (int argc, char * argv)
{
       shm_tcs_kernel_Target * pshm_tcs_kernel_Target;

       GetObject_tcs_kernel_Target(&pshm_tcs_kernel_Target);

       cout << (int)pshm_tcs_kernel_Target << "	";

       cout << "sync0 = " << pshm_tcs_kernel_Target->syncO << endl;

       pshm_tcs_kernel_Target->Handle();

       return 0;
}

#include <pthread.h>

void DoNothingCode() {
       pthread_create(NULL, NULL, NULL, NULL);
}


