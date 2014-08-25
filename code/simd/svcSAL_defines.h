

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
 
typedef unsigned int 	svcUINT;   
typedef int 		svcINT;  
typedef unsigned short 	svcUSHORT;
typedef short 		svcSHORT;
typedef float 		svcFLT;
typedef double 		svcDBL;
typedef double 		svcTIME;
typedef unsigned char 	svcUCHAR;
typedef char 		svcCHAR;
typedef char[32]	svcNAME;
typedef int		svcIID
typedef int		svcSID
typedef int		svcTID

#define SAL_PID_HISTORY_DEPTH	20001
#define SAL_PID_AUTO_DISPOSE	20002
#define SAL_PID_LATENCY_BUDGET	20003
#define SAL_PID_DEADLINE	20004
#define SAL_PID_PRIORITY	20005
#define SAL_PID_SAMPLE_AGE	20006
#define SAL_PID_READ_COUNTER	20007
#define SAL_PID_WRITTEN_COUNTER	20008


#define SAL__DEFAULT_HISTORY_DEPTH	100
#define SAL__DEFAULT_AUTO_DISPOSE	TRUE


#define SAL__FASTPOLL			1000
#define SAL__SLOWPOLL			1000000

// Generic return codes
#define SAL__OK   		 0
#define SAL__ERR 		-1
#define SAL__ILLEGAL_REVCODE 	-2
#define SAL__TOO_MANY_HANDLES   -3
#define SAL__NOT_DEFINED        -4

// Timeout return codes
#define SAL__TIMEOUT            -5
#define SAL__SIGNAL_INTERRUPT   -6

// getSample timeout specifiers (+ve is a time in microseconds)
#define SAL__WAIT_FOR_NEXT_UPDATE -10000
#define SAL__WAIT_FOR_CHANGE      -10001


// telemetry stream update types
#define SAL__NO_UPDATES		-100
#define SAL__WAITING_FOR_NEXT 	100
#define SAL__GOT_UPDATE 	101
#define SAL__SYNC_IN    	102
#define SAL__SYNC_OUT   	103
#define SAL__SYNC_SET   	104
#define SAL__SYNC_CLEAR 	105
#define SAL__SYNC_READ  	106

// generateAlert types
#define SAL__WARN_ALERT   	200
#define SAL__ERROR_ALERT  	201
#define SAL__ABORT_ALERT 	-200

// issueCommand/getResponse return codes
#define SAL__CMD_ACK        	300
#define SAL__CMD_INPROGRESS 	301
#define SAL__CMD_STALLED    	302
#define SAL__CMD_COMPLETE   	303
#define SAL__CMD_NOPERM    	-300
#define SAL__CMD_NOACK     	-301
#define SAL__CMD_FAILED    	-302
#define SAL__CMD_ABORTED   	-303
#define SAL__CMD_TIMEOUT   	-304

#define svcDebugOutputString(__X__) fprintf(stderr,__X__)
#define SAL__MAX_DBGMSG_SIZE   1024
#define SAL__MAX_HANDLES       128
#define SAL__MAX_NAMESIZE      128

