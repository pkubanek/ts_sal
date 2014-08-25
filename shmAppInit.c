 
#include "tcl.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "svcSAL.h"

extern int updateVariables(Tcl_Interp *interp, char *subsysid, int *shmdata_ref);
extern int readVariables(Tcl_Interp *interp, char *subsysid, int *shmdata_ref);


int svcSAL_writeshm (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[]);
int svcSAL_readshm  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[]);
int svcSAL_sendcommand (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[]);
int svcSAL_sendresponse  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[]);


int lshmid=-1;
int cmdshmid=-1;
int respshmid=-1;
int shmcmd_size=SAL__COMMAND_SIZE;
int shmresp_size=SAL__RESPONSE_SIZE;
svcSAL_command  *shmcmd_ref;
svcSAL_response *shmresp_ref;


int shmAppInit(Tcl_Interp *interp)
{
  /* Initialize the new commands */
 
    Tcl_CreateCommand ( interp, "writeshm",(Tcl_CmdProc *) svcSAL_writeshm, NULL,NULL);
    Tcl_CreateCommand ( interp, "readshm", (Tcl_CmdProc *) svcSAL_readshm,  NULL,NULL);
    Tcl_CreateCommand ( interp, "sendcmd", (Tcl_CmdProc *) svcSAL_sendcommand, NULL,NULL);
    Tcl_CreateCommand ( interp, "sendack", (Tcl_CmdProc *) svcSAL_sendresponse,  NULL,NULL);

  return TCL_OK;
}

int svcSAL_writeshm  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[])
{
    unsigned int shmid;
    unsigned int shmdata_size;
    int *shmdata_ref;
    char topic[128];

   /* Check number of arguments provided and return an error if necessary */
   if (argc < 4) {
      Tcl_AppendResult(interp, "wrong # args: should be \"",argv[0]," topic shmid size\"", (char *)NULL);
      return TCL_ERROR;
   }

    strcpy(topic,argv[1]);
    sscanf (argv[2], "%x", &shmid);
    sscanf (argv[3], "%d", &shmdata_size);
    if (lshmid == -1) {
       lshmid = shmget(shmid, shmdata_size , IPC_CREAT|0666);
       shmdata_ref  = (int *) shmat(lshmid, NULL, 0);
    }
    updateVariables(interp, topic, (int *)shmdata_ref);

    return TCL_OK;
}

int svcSAL_readshm  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[])
{
    unsigned int shmid;
    unsigned int shmdata_size;
    int *shmdata_ref;
    char topic[128];



   /* Check number of arguments provided and return an error if necessary */
   if (argc < 4) {
      Tcl_AppendResult(interp, "wrong # args: should be \"",argv[0]," topic shmid size\"", (char *)NULL);
      return TCL_ERROR;
   }

    strcpy(topic,argv[1]);
    sscanf (argv[2], "%x", &shmid);
    sscanf (argv[3], "%d", &shmdata_size);
    if (lshmid == -1) {
       lshmid = shmget(shmid, shmdata_size , IPC_CREAT|0666);
       shmdata_ref  = (int *) shmat(lshmid, NULL, 0);
    }
    readVariables(interp, topic, (int *)shmdata_ref);

    return TCL_OK;
}

int svcSAL_sendcommand  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[])
{
    unsigned int shmid;
    unsigned int shmdata_size;
    svcSAL_command *shmdata_ref;
    char topic[128];
    char device[16];
    char operation[16];
    char value[16];
    char modifiers[128];

   /* Check number of arguments provided and return an error if necessary */
   if (argc < 5) {
      Tcl_AppendResult(interp, "wrong # args: should be \"",argv[0]," subsystem shmid size device op val mod\"", (char *)NULL);
      return TCL_ERROR;
   }

    strcpy(topic,argv[1]);
    sscanf (argv[2], "%x", &shmid);
    sscanf (argv[3], "%d", &shmdata_size);
    strcpy(device,argv[4]);
    if (argc > 5) {
      strcpy(operation,argv[5]);
    }
    if (argc > 6) {
      strcpy(value,argv[6]);
    }
    if (argc > 7) {
      strcpy(modifiers,argv[7]);
    }
    if (cmdshmid == -1) {
       cmdshmid = shmget(shmid, shmdata_size , IPC_CREAT|0666);
       shmdata_ref  = (int *) shmat(cmdshmid, NULL, 0);
    }

    strcpy(shmdata_ref->device,device);
    if (argc > 5) {
      strcpy(shmdata_ref->operation,operation);
    } else {
      strcpy(shmdata_ref->operation,NULL);
    }
    if (argc > 6) {
      strcpy(shmdata_ref->value,value);
    } else {
      strcpy(shmdata_ref->value,NULL);
    }
    if (argc > 7) {
      strcpy(shmdata_ref->modifiers,modifiers);
    } else {
      strcpy(shmdata_ref->modifiers,NULL);
    }
    shmdata_ref->cmdID++;
    shmdata_ref->syncO = 1;
}


int svcSAL_sendresponse  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[])
{
    unsigned int shmid;
    unsigned int shmdata_size;
    svcSAL_command *shmdata_ref;
    char type[16];
    char value[128];
    int  cmdID;

   /* Check number of arguments provided and return an error if necessary */
   if (argc < 5) {
      Tcl_AppendResult(interp, "wrong # args: should be \"",argv[0]," subsystem shmid size cmdId type value\"", (char *)NULL);
      return TCL_ERROR;
   }

    strcpy(topic,argv[1]);
    sscanf (argv[2], "%x", &shmid);
    sscanf (argv[3], "%d", &shmdata_size);
    sscanf(cmdID,"%d",argv[4]);
    strcpy(type,argv[5]);
    strcpy(value,argv[6]);
    if (respshmid == -1) {
       respshmid = shmget(shmid, shmdata_size , IPC_CREAT|0666);
       shmdata_ref  = (int *) shmat(respshmid, NULL, 0);
    }

    if ( strcmp(type,"ack") == 0 ) {
       strcpy(shmdata_ref->ack,value);
    }
    if ( strcmp(type,"error") == 0 ) {
       strcpy(shmdata_ref->error,value);
    }
    if ( strcmp(type,"result") == 0 ) {
       strcpy(shmdata_ref->result,value);
    }
    if ( strcmp(type,"timeout") == 0 ) {
       sscanf(value,"%d",&shmdata_ref->timeout);
    }
    if ( strcmp(type,"repeat") == 0 ) {
       sscanf(value,"%d",&shmdata_ref->repeat);
    }
    shmdata_ref->cmdID = cmdID;
    shmdata_ref->syncO = 1;
}






