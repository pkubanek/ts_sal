set SHC(genericshclient.cpp) "

#include <iostream>
#include <stdlib.h>
using namespace std;

#include \"shmem_[set subsys].h\"

int main (int argc, char ** argv[])
\{
       shm_[set subsys] * pshm_[set subsys];

       GetObject_[set subsys](&pshm_[set subsys]);

       cout << (int)pshm_[set subsys] << \"\t\";

       cout << \"sync0 = \" << pshm_[set subsys]->syncO << endl;

       pshm_[set subsys]->Handle();

       return 0;
\}

#include <pthread.h>

void DoNothingCode() \{
       pthread_create(NULL, NULL, NULL, NULL);
\}

"
