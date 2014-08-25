

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/time.h>
#include "svcSAL.h"

int lshmid=-1;
int shmdata_size=-1;
int *shmdata_ref;

int svcSAL_receiveDatastream (char *subsystem, 
                             int timeout, 
                             int (*datastreamCallback)(char *subsystem, 
                                  int *shmdata_ref ) ) {

   int shmid;
   int dataid;
   int status;
   int salHandle;
   svcSAL_tlmhdr_cache *shmdata_ref;
   struct timeval now1,now2;
   struct timezone zone;
   struct shmid_ds shmInfo;

   salHandle = svcSAL_connect (subsystem );
   if ( salHandle == 0 ) {
      return(SAL__NOT_DEFINED);
   }

   shmdata_ref  = (svcSAL_tlmhdr_cache *) svcSAL_handle[salHandle].ref;

   gettimeofday(&now1, &zone);
   while (shmdata_ref->syncI == 0) {
      svcSAL_sleep(1);
      if (timeout > 0) {
        gettimeofday(&now1, &zone);
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






