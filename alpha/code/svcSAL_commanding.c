

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/time.h>
#include "svcSAL.h"

extern svcSAL_cachehandle svcSAL_handle[SAL__MAX_HANDLES];

int cmdshmid=-1;
int respshmid=-1;
int pingshmid=-1;
int shmcmd_size=SAL__COMMAND_SIZE;
int shmresp_size=SAL__RESPONSE_SIZE;
svcSAL_command  *shmcmd_ref;
svcSAL_response *shmresp_ref;

int svcSAL_receiveCommand (char *subsystem, 
                           int timeout, 
                           int (*commandCallback)(char *subsystem, 
                                 svcSAL_command  *shmcmd_ref, 
                                 svcSAL_response *shmresp_ref ) ) {

   int status;
   int cmdHandle;
   int respHandle;
   int pingHandle;
   svcSAL_command  *shmcmd_ref;
   svcSAL_response *shmresp_ref;
   struct timeval now1,now2;
   struct timezone zone;
   char cmdstream[64];
   char respstream[64];
   char pingstream[64];

   sprintf(cmdstream,"%s_command",subsystem);
   sprintf(respstream,"%s_response",subsystem);

   cmdHandle = svcSAL_connect (cmdstream);
   if ( cmdHandle == 0 ) {
      return(SAL__NOT_DEFINED);
   }
   respHandle = svcSAL_connect (respstream);
   if ( respHandle == 0 ) {
      return(SAL__NOT_DEFINED);
   }

   shmcmd_ref  = (svcSAL_command *) svcSAL_handle[cmdHandle].ref;
   shmresp_ref  = (svcSAL_response *) svcSAL_handle[respHandle].ref;

   gettimeofday(&now1, &zone);
   while (shmcmd_ref->syncI == 0) {
      svcSAL_sleep(1);
      if (timeout > 0) {
        gettimeofday(&now2, &zone);
        if ((now2.tv_sec - now1.tv_sec) > timeout) {
           return SAL__TIMEOUT;
        }
      }
   }

   printf("%s command received : %d %s.%s %s %s",subsystem,
             shmcmd_ref->cmdID,
             shmcmd_ref->device,
             shmcmd_ref->property,
             shmcmd_ref->action,
             shmcmd_ref->value,
             shmcmd_ref->modifiers);

   shmresp_ref->cmdID = shmcmd_ref->cmdID;
   strcpy(shmresp_ref->ack,"SAL OK");
   shmcmd_ref->syncI = 0;
   status = SAL__OK;

   if ( strcmp(shmcmd_ref->property,"ping" ) == 0 ) {
      sprintf(pingstream,"%s_%s",subsystem,shmcmd_ref->device);
      pingHandle = svcSAL_connect (pingstream);
      if ( pingHandle == 0 ) {
         return(SAL__NOT_DEFINED);
      }
      svcSAL_accessSync(pingHandle, SAL__SYNC_OUT, SAL__SYNC_SET);
      return SAL__OK;
   }

   if ( commandCallback != NULL ) {
      status = (*commandCallback)(subsystem, (svcSAL_command *)&shmcmd_ref, (svcSAL_response  *)&shmresp_ref ) ;
   }
   shmresp_ref->syncO = 1;

   return status;
}


int svcSAL_test_commandCallback (char *subsystem, svcSAL_command *shmcmd_ref, svcSAL_response *shmresp_ref ) {
   printf("%s command received : %d %s.%s %s %s",subsystem,
             shmcmd_ref->cmdID,
             shmcmd_ref->device,
             shmcmd_ref->property,
             shmcmd_ref->action,
             shmcmd_ref->value,
             shmcmd_ref->modifiers);
   strcpy(shmresp_ref->ack,"Received");
   return SAL__OK;
}







