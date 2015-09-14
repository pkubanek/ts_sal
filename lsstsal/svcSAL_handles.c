
#include <sys/shm.h>
#include <sys/time.h>
#include "svcSAL.h"
#include "svcSAL_caches.h"

int svcSAL_initialize () {

  int i;

  for (i=0;i<SAL__MAX_HANDLES;i++) {
     svcSAL_handle[i].shmid=-1;
     svcSAL_handle[i].shmsize=0;
     svcSAL_handle[i].ref=NULL;
     strcpy(svcSAL_handle[i].streamname, "NOT IN USE");
  }
  
  return SAL__OK;
}


int svcSAL_connect ( char *name ) {

  int status;
  int i;
  int used=0;
  long datasize;
  long dataid;

   status = svcSAL_shmProperties( name, &dataid, &datasize);
   if ( status != SAL__OK ) {
      return(status);
   }

   i=0;
   while (i < SAL__MAX_HANDLES && (i == used )) {
      if ( svcSAL_handle[i].shmid == dataid ) {
          return i;
      }
      if ( svcSAL_handle[i].shmid != -1 ) {
          used++;
      }
   }
   
   if (i == SAL__MAX_HANDLES) {
      return SAL__TOO_MANY_HANDLES;
   }

   svcSAL_handle[i].shmid = shmget(dataid, datasize , IPC_CREAT|0666);
   svcSAL_handle[i].shmsize = datasize;
   svcSAL_handle[i].ref  = (int *) shmat(svcSAL_handle[i].shmid, NULL, 0);
   strcpy( svcSAL_handle[i].streamname , name);

   return i;
}


