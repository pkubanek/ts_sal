
#include "svcSAL.h"
svcSAL_cachehandle svcSAL_handle[SAL__MAX_HANDLES];

int main(int argc, char *argv[])
{
    int processed = 0;
    int timeout = 100; /* 100 msec max commanding rate */
    int cmd_count = 0; /* infinite loop */
    int salHandle;
    int status;

    char subsystem[SAL__MAX_NAMESIZE];
    svcSAL_command  *shmcmd_ref;
    svcSAL_response *shmresp_ref;
    int (*commandCallback)(char *subsystem, 
                           svcSAL_command  *shmcmd_ref, 
                           svcSAL_response *shmresp_ref);
    if (argc < 2) {
        printf("SAL command processor : No Subsystem name specified\n");
        exit(0);
    }
    strcpy(subsystem,argv[1]);
    if (argc >= 3) {
        cmd_count = atoi(argv[2]);
    }

    svcSAL_initialize();
    printf("SAL command processor : Initializing\n");

    commandCallback = svcSAL_test_commandCallback;

    printf("SAL command processor : Ready\n");
    while ( (cmd_count == 0) || (processed < cmd_count) ) {
       status = svcSAL_receiveCommand (subsystem, 
                              timeout, 
                              commandCallback );
       if (status == SAL__OK) {
         printf("SAL command processor :%d - %s command\n",
                                processed,subsystem);
         processed++;
       }
    }

    exit(0);

}

