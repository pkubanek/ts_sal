 
#include "tcl.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "svcSAL.h"

extern svcSAL_cachehandle svcSAL_handle[SAL__MAX_HANDLES];

extern int updateVariables(Tcl_Interp *interp, char *subsysid, int *shmdata_ref);
extern int readVariables(Tcl_Interp *interp, char *subsysid, int *shmdata_ref);


int svcSAL_writeshm (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[]);
int svcSAL_readshm  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[]);
int svcSAL_sendcommand (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[]);
int svcSAL_sendresponse  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[]);



int shmAppInit(Tcl_Interp *interp)
{
  /* Initialize the new commands */
 
    Tcl_CreateCommand ( interp, "writeshm",(Tcl_CmdProc *) svcSAL_writeshm, NULL,NULL);
    Tcl_CreateCommand ( interp, "readshm", (Tcl_CmdProc *) svcSAL_readshm,  NULL,NULL);
    Tcl_CreateCommand ( interp, "sendcmd", (Tcl_CmdProc *) svcSAL_sendcommand, NULL,NULL);
    Tcl_CreateCommand ( interp, "sendack", (Tcl_CmdProc *) svcSAL_sendresponse,  NULL,NULL);
    svcSAL_initialize();

    return TCL_OK;
}

int svcSAL_writeshm  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[])
{
    int salHandle;
    char topic[128];
    svcSAL_tlmhdr_cache *shmdata_ref;

   /* Check number of arguments provided and return an error if necessary */
   if (argc < 2) {
      Tcl_AppendResult(interp, "wrong # args: should be \"",argv[0]," topic\"", (char *)NULL);
      return TCL_ERROR;
   }

    strcpy(topic,argv[1]);
    salHandle = svcSAL_connect (topic);
    if ( salHandle == 0 ) {
      return(TCL_ERROR);
    }

    shmdata_ref  = (svcSAL_tlmhdr_cache *) svcSAL_handle[salHandle].ref;
    updateVariables(interp, topic, (int *)shmdata_ref);

    return TCL_OK;
}

int svcSAL_readshm  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[])
{
    int salHandle;
    char topic[128];
    svcSAL_tlmhdr_cache *shmdata_ref;

   /* Check number of arguments provided and return an error if necessary */
   if (argc < 2) {
      Tcl_AppendResult(interp, "wrong # args: should be \"",argv[0]," topic\"", (char *)NULL);
      return TCL_ERROR;
   }

    strcpy(topic,argv[1]);

    salHandle = svcSAL_connect (topic);
    if ( salHandle == 0 ) {
      return(TCL_ERROR);
    }
    shmdata_ref  = (svcSAL_tlmhdr_cache *) svcSAL_handle[salHandle].ref;
    readVariables(interp, topic, (int *)shmdata_ref);

    return TCL_OK;
}

int svcSAL_sendcommand  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[])
{
    svcSAL_command *shmdata_ref;
    int  salHandle;
    char topic[128];
    char device[16];
    char property[16];
    char action[16];
    char value[16];
    char modifiers[128];

   /* Check number of arguments provided and return an error if necessary */
   if (argc < 4) {
      Tcl_AppendResult(interp, "wrong # args: should be \"",argv[0]," subsystem device prop act val mod\"", (char *)NULL);
      return TCL_ERROR;
   }

    sprintf(topic,"%s_command",argv[1]);
    strcpy(device,argv[2]);
    if (argc > 3) {
      strcpy(property,argv[3]);
    }
    if (argc > 4) {
      strcpy(action,argv[4]);
    }
    if (argc > 5) {
      strcpy(value,argv[5]);
    }
    if (argc > 6) {
      strcpy(modifiers,argv[6]);
    }

    salHandle = svcSAL_connect (topic);
    if ( salHandle == 0 ) {
      return(TCL_ERROR);
    }
    shmdata_ref  = (svcSAL_command *) svcSAL_handle[salHandle].ref;

    strcpy(shmdata_ref->device,device);
    if (argc > 5) {
      strcpy(shmdata_ref->property,property);
    } else {
      strcpy(shmdata_ref->property,NULL);
    }
    if (argc > 6) {
      strcpy(shmdata_ref->action,action);
    } else {
      strcpy(shmdata_ref->action,NULL);
    }
    if (argc > 7) {
      strcpy(shmdata_ref->value,value);
    } else {
      strcpy(shmdata_ref->value,NULL);
    }
    if (argc > 8) {
      strcpy(shmdata_ref->modifiers,modifiers);
    } else {
      strcpy(shmdata_ref->modifiers,NULL);
    }
    shmdata_ref->cmdID++;
    shmdata_ref->syncO = 1;
    return TCL_OK;
}


int svcSAL_sendresponse  (ClientData dummy, Tcl_Interp *interp, int argc, char *argv[])
{
    svcSAL_response *shmdata_ref;
    int salHandle;
    char type[16];
    char value[128];
    char subsystem[128];
    int  cmdID;

   /* Check number of arguments provided and return an error if necessary */
   if (argc < 3) {
      Tcl_AppendResult(interp, "wrong # args: should be \"",argv[0]," subsystem cmdId type value\"", (char *)NULL);
      return TCL_ERROR;
   }

    sprintf(subsystem,"%s_response",argv[1]);
    sscanf (argv[2], "%d", &cmdID);
    strcpy(type,argv[3]);
    strcpy(value,argv[4]);

    salHandle = svcSAL_connect (subsystem);
    if ( salHandle == 0 ) {
      return(TCL_ERROR);
    }
    shmdata_ref  = (svcSAL_response *) svcSAL_handle[salHandle].ref;

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
    return TCL_OK;
}






