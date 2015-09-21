#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <sys/shm.h>

#include "SALTopic_lv.h"
#include "SALTopic_cache.h"

SALTopic_cache *SALTopic_ref = NULL;

int LVcomm_shmem_publish_SALTopic (SALTopic_lv **SALTopic_Ctl)
{
   int SALTopic_shmsize;
   int lshmid;
   int SALTopic_shmid = 0x10bf;
   int *toptr;

   if (SALTopic_ref == NULL) {
     SALTopic_cache *SALTopic_ref;
     SALTopic_shmsize = sizeof(struct SALTopic_cache);
     lshmid = shmget(SALTopic_shmid, SALTopic_shmsize , IPC_CREAT|0666);
     SALTopic_ref  = (SALTopic_cache *) shmat(lshmid, NULL, 0);
   }
   sprintf(SALTopic_ref->private_revCode,"SALTopic test");
   toptr = SALTopic_ref + 56;
   memcpy(SALTopic_Ctl , toptr, sizeof(SALTopic_lv));  
   SALTopic_ref->syncO++;
   return(0);
}


int LVcomm_shmem_get_SALTopic (SALTopic_lv **SALTopic_Ctl, int wait)
{
   int SALTopic_shmsize;
   int lshmid;
   int SALTopic_shmid = 0x10bf;
   int *fromptr;

   if (SALTopic_ref == NULL) {
     SALTopic_cache *SALTopic_ref;
     SALTopic_shmsize = sizeof(struct SALTopic_cache);
     lshmid = shmget(SALTopic_shmid, SALTopic_shmsize , IPC_CREAT|0666);
     SALTopic_ref  = (SALTopic_cache *) shmat(lshmid, NULL, 0);
   }
   fromptr = SALTopic_ref + 56;
   if (SALTopic_ref->syncI > 0) {
      memcpy(fromptr, SALTopic_Ctl , sizeof(SALTopic_lv));
      SALTopic_ref->syncI = SALTopic_ref->syncI - 1;
      return(0);
   }
   if (wait > 0) {
       while (wait > 0) {
          usleep(1000);
          wait = wait -1000;
          if (SALTopic_ref->syncI > 0) {
             memcpy(fromptr, SALTopic_Ctl , sizeof(SALTopic_lv));
             SALTopic_ref->syncI = SALTopic_ref->syncI - 1;
             return(0);
          }
       }
   }
   return (-1);
}


