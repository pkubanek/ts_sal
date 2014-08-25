/////////////////////////////////////////////////////////////
//
// svcSAL.h:  Interface file for the svcSAL class.
//
// Copyright (c) 2006 NOAO.
//
/////////////////////////////////////////////////////////////


#if !defined(svcSAL__INCLUDED_)
#define svcSAL__INCLUDED_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "svcSAL_defines.h"


typedef struct svcSAL_command
{
    int     cppDummy;
    int     syncI;
    int     syncO;
    char    private_revCode[32];
    double  private_sndStamp;
    double  private_rcvStamp;
    int     private_seqNum;
    int     private_origin;
    long    cmdID;
    char    device[16];
    char    property[16];
    char    action[16];
    char    value[16];
    char    modifiers[128];
} svcSAL_command;
 
typedef struct svcSAL_response
{
    int      cppDummy;
    int      syncI;
    int      syncO;
    char     private_revCode[32];
    double   private_sndStamp;
    double   private_rcvStamp;
    int      private_seqNum;
    int      private_origin;
    long     cmdID;
    char     ack[16];
    char     error[16];
    long     timeout;
    short    repeat;
    short    submits;
    char     result[64];
} svcSAL_response;

typedef struct svcSAL_tlmhdr_cache {
    int      cppDummy;
    int      syncI;
    int      syncO;
    char     private_revCode[32];
    double   private_sndStamp;
    double   private_rcvStamp;
    int      private_seqNum;
    int      private_origin;
} svcSAL_tlmhdr_cache;

typedef struct svcSAL_cachehandle {
    char     streamname[128];
    int	     dataid;
    long     shmid;
    size_t   shmsize;
    svcSAL_tlmhdr_cache      *ref;
} svcSAL_cachehandle;

/* svcSAL_cachehandle svcSAL_handle[SAL__MAX_HANDLES]; */


#define SAL__COMMAND_SIZE sizeof(svcSAL_command)
#define SAL__RESPONSE_SIZE sizeof(svcSAL_response)

/*     
  int (*commandCallback)(char *subsystem, svcSAL_command *shmcmd_ref, svcSAL_response *shmresp_ref ) = NULL;
  int (*datastreamCallback)(char *subsystem, int *shmdata_ref ) = NULL;
*/

#ifdef SAL_SHM

int svcSAL_initialize ();
int svcSAL_connect ( char *name );
int svcSAL_connect1 ( char *name, svcSAL_cachehandle *handle );
int svcSAL_accessSync ( int handle , int direction, int optype );
int svcSAL_accessPrivate ( int handle , char *operation, char *revCode , 
                           long *sndStamp, long *rcvStamp,
                           long *seqNum  , long *origin );
int svcSAL_test_datastreamCallback (char *subsystem, int *shmdata_ref );
int svcSAL_test_commandCallback (char *subsystem, 
                                 svcSAL_command *shmcmd_ref, 
                                 svcSAL_response *shmresp_ref);
int svcSAL_test_responseCallback (char *subsystem, 
                                 svcSAL_command *shmcmd_ref, 
                                 svcSAL_response *shmresp_ref);
int svcSAL_sleep(unsigned long milisec) ; 
int svcSAL_nsleep(unsigned long nanosec) ; 
long svcSAL_timestamp();  
int svcSAL_shmProperties ( char *subsys, char *attribute );

#endif
 

#endif


