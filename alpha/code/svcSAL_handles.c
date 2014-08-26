
#include <sys/shm.h>
#include <sys/time.h>
#include "svcSAL.h"
#include "svcSAL_caches.h"

int svcSAL_used_handles=0;
svcSAL_cachehandle svcSAL_handle[SAL__MAX_HANDLES];


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
  int datasize;
  int dataid;

   status = svcSAL_shmProperties( name, &dataid, &datasize);
   if ( status != SAL__OK ) {
      return(status);
   }
printf("%s id=%x size=%d",name,dataid,datasize);

   i=0;
   while (i < SAL__MAX_HANDLES && (i <= svcSAL_used_handles )) {
      if ( svcSAL_handle[i].shmid == dataid ) {
          return i;
      }
      if ( svcSAL_handle[i].shmid != -1 ) {
          svcSAL_used_handles++;
      }
      i++;
   }
   
   if (i == SAL__MAX_HANDLES) {
      return SAL__TOO_MANY_HANDLES;
   }

   svcSAL_handle[i].shmid = shmget(dataid, datasize , IPC_CREAT|0666);
   svcSAL_handle[i].shmsize = datasize;
   svcSAL_handle[i].ref  = shmat(svcSAL_handle[i].shmid, NULL, 0);
   strcpy( svcSAL_handle[i].streamname , name);
   svcSAL_used_handles = i;

   return i;
}


int svcSAL_connect1 ( char *name , svcSAL_cachehandle *svcSAL_handle1) {

  int status;
  int datasize;
  int dataid;

   status = svcSAL_shmProperties( name, &dataid, &datasize);
   if ( status != SAL__OK ) {
      return(status);
   }
printf("Connect 1 %s id=%x size=%d",name,dataid,datasize);

   svcSAL_handle1->shmid = shmget(dataid, datasize , IPC_CREAT|0666);
   svcSAL_handle1->shmsize = datasize;
   svcSAL_handle1->ref  = shmat(svcSAL_handle1->shmid, NULL, 0);
   strcpy( svcSAL_handle1->streamname , name);

   return(SAL__OK);
}


