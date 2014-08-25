

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/time.h>
#include "svcSAL.h"

extern svcSAL_cachehandle svcSAL_handle[SAL__MAX_HANDLES];

int shmdata_size=-1;
int *shmdata_ref;
int (*datastreamCallback)(char *subsystem, void *shmdata_ref );

int svcSAL_receiveDatastream (char *subsystem, 
                             int timeout, 
                             int (*datastreamCallback)(char *subsystem, 
                                  void *shmdata_ref ) ) {

   int status;
   int salHandle;
   svcSAL_tlmhdr_cache *shmdata_ref;
   struct timeval now1,now2;
   struct timezone zone;

   salHandle = svcSAL_connect (subsystem );
   if ( salHandle == 0 ) {
      return(SAL__NOT_DEFINED);
   }

   shmdata_ref  = (svcSAL_tlmhdr_cache *) svcSAL_handle[salHandle].ref;

   gettimeofday(&now1, &zone);
   while (shmdata_ref->syncI == 0) {
      svcSAL_sleep(1);
      if (timeout > 0) {
        gettimeofday(&now2, &zone);
        if ((now2.tv_sec - now1.tv_sec) > timeout) {
           return SAL__TIMEOUT;
        }
      }
   }

   printf("%s data received",subsystem);
   status = SAL__OK;
 
   if ( datastreamCallback != NULL ) {
      status = (*datastreamCallback)(subsystem, &shmdata_ref) ;
   }

   return status;
}






