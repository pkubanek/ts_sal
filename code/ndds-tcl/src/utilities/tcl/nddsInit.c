/*
 * nddsInit.c --
 *
 *	Initialize an interpreter with Tcl-ndds.
 *	This mostly just makes a bunch of calls to Tcl_CreateCommand to
 *	create tcl commands for the various modules.
 *
 */


#include <stdlib.h>
#include <string.h>			/* for strdup */
#include <unistd.h>			/* sleep() */
#include <tk.h>
#include <NDDS.h>

#include "nddswish.h"

#define NDDS_TCL_VERSION "2.0"		/* FIX: When should this be changed? -KDS */

#define BUFLEN  256			/* length of structure buffer */
#define MSGLEN  128			/* max length of NDDS message name */
#define NUMSTR   64			/* max # of strings in a NDDS structure */

#define NDDS_POLL_TIME 50		/*milliseconds between consumer polls*/
					/* 50 uses about 2% of the CPU */

/* there should be command line args to set these */
float persistence = 1.0f;		/* seconds life for equal producers */
float strength = 10.0f;			/* relative to other producers */

int debug_level = 1;			/* variable for NDDS debug prints */

#ifndef NDEBUG
void PrintTclCmd (int argc, char **argv)
{
    if (TRACE <= debug_level)
    {
	int i;
	fprintf (stderr, " %d: ", argc);
	for (i=0; i < argc; i++) 
	    fprintf (stderr, "%s ", argv[i]);
	fprintf (stderr, "\n");
    }
    return;
}
#else
/* Nothing... */
#define PrintTclCmd(ARGC, ARGV)
#endif

typedef struct {			/* producer/consumer registry */
    int type;				/* one of our data types */
    char name[MSGLEN];			/* the name used by TCL */
    NDDSProducer producer;		/* the producer/consumer pointer */
    void *msg;				/* msg data storage area */
    NDDS_TYPE_DRIVER *typeDriver;
} TclProducerStorage, *TclProducer;

typedef struct {			/* subscription data */
    int type;				/* one of our data types */
    char	*name;			/* name of subscription */
    char	*callback;		/* command to call */
    void	*instance;		/* data instance storage */
    Tcl_Interp	*interp;		/* Tcl interpreter to use */
    NDDS_TYPE_DRIVER *typeDriver;
} TclConsumerStorage, *TclConsumerInfo;

NDDSConsumer	TaskConsumer;		/* the consumer for this task */

TclProducer producerLookup (char *name);
TclProducer producerAdd (char *name);

int NddsWishInit (Tcl_Interp *interp);
int NddsWishConnect        (ClientData notUsed, Tcl_Interp *interp, int argc, char **argv);
int NddsWishProducerCreate (ClientData notUsed, Tcl_Interp *interp, int argc, char **argv);
int NddsWishProducerSample (ClientData notUsed, Tcl_Interp *interp, int argc, char **argv);
int NddsWishConsumerCreate (ClientData notUsed, Tcl_Interp *interp, int argc, char **argv);

#define TCL_CMD_PROTO(NAME) \
	int NAME (ClientData notUsed, Tcl_Interp *interp, \
		  int argc, char **argv)

 TCL_CMD_PROTO (NddsWishVerbositySet);
 TCL_CMD_PROTO (NddsWishVerbosityDebugSet);
 TCL_CMD_PROTO (NddsWishVerbosityErrorSet);

 TCL_CMD_PROTO (NddsWishDBaseListAll);
 TCL_CMD_PROTO (NddsWishDBaseListConsumers);
 TCL_CMD_PROTO (NddsWishDBaseListInstances);
 TCL_CMD_PROTO (NddsWishDBaseListProducers);
 TCL_CMD_PROTO (NddsWishDBaseListProductionsLocal);
 TCL_CMD_PROTO (NddsWishDBaseListProductionsRemote);
 TCL_CMD_PROTO (NddsWishDBaseListSubscriptionsLocal);
 TCL_CMD_PROTO (NddsWishDBaseListSubscriptionsRemote);

#undef TCL_CMD_PROTO

int nddsDomain = 0;
int numOfProducers=0;
TclProducerStorage *Producers;

#include "registry_tclndds.h"
Tcl_HashTable  typeRegistrySpace;  /* Caller must provide space for hash table */
Tcl_HashTable *typeRegistry = &typeRegistrySpace;

/* Fix: This should probably be compiled separately and linked in. -KDS */
#include "registry_tclndds.c"

/*
 *--------------------------------------------------------------
 *
 * ndds_Init --
 *
 *	Initialize the full Tcl-Ndds package.
 *
 * Results:
 *	None
 *
 * Side effects:
 *	network related commands are bound to the interpreter.
 *
 *--------------------------------------------------------------
 */

int NddsWishInit (Tcl_Interp *interp)
{
#ifndef NDEBUG
    printf ("In ndds Tk init\n");
#endif
					/* these 3 setup calls are mandatory */

    Tcl_SetVar(interp, "Ndds_tcl_version", NDDS_TCL_VERSION, TCL_GLOBAL_ONLY);
    
    Tcl_LinkVar (interp, "Ndds_tcl_debug_level", /* let scripts set debug */
		 (char *)&debug_level, TCL_LINK_INT);

    Tcl_CreateCommand (interp, "nddsConnect", NddsWishConnect,
		       (ClientData) NULL,
		       (void (*) _ANSI_ARGS_((ClientData))) NULL);
    Tcl_CreateCommand (interp, "nddsProducerCreate", NddsWishProducerCreate,
		       (ClientData) NULL,
		       (void (*) _ANSI_ARGS_((ClientData))) NULL);
    Tcl_CreateCommand (interp, "nddsProducerSample", NddsWishProducerSample,
		       (ClientData) NULL,
		       (void (*) _ANSI_ARGS_((ClientData))) NULL);
    Tcl_CreateCommand (interp, "nddsConsumerCreate", NddsWishConsumerCreate,
		       (ClientData) NULL,
		       (void (*) _ANSI_ARGS_((ClientData))) NULL);

#define CREATE_CMD(STRING,FUNCTION) \
    Tcl_CreateCommand (interp, STRING, FUNCTION, (ClientData) NULL, \
		       (void (*) _ANSI_ARGS_((ClientData))) NULL);

    /* These commands act the same way as they do in C */
    CREATE_CMD ("NddsVerbositySet", NddsWishVerbositySet);
    CREATE_CMD ("NddsVerbosityErrorSet", NddsWishVerbosityErrorSet);
    CREATE_CMD ("NddsVerbosityDebugSet", NddsWishVerbosityDebugSet);

    CREATE_CMD ("NddsDBaseListAll", NddsWishDBaseListAll);
    CREATE_CMD ("NddsDBaseListConsumers", NddsWishDBaseListConsumers);
    CREATE_CMD ("NddsDBaseListInstances", NddsWishDBaseListInstances);
    CREATE_CMD ("NddsDBaseListProducers", NddsWishDBaseListProducers);

#ifdef NDDS_1_11Q
#else
    CREATE_CMD ("NddsDBaseListProductionsLocal", NddsWishDBaseListProductionsLocal);
    CREATE_CMD ("NddsDBaseListSubscriptionsLocal", NddsWishDBaseListSubscriptionsLocal);
#endif
    CREATE_CMD ("NddsDBaseListProductionsRemote", NddsWishDBaseListProductionsRemote);
    CREATE_CMD ("NddsDBaseListSubscriptionsRemote", NddsWishDBaseListSubscriptionsRemote);

#undef CREATE_CMD

#ifndef NDEBUG
    printf ("ndds init finished OK\n");
#endif

    return (TCL_OK);
}	


/*
 *--------------------------------------------------------------
 *
 * ndds_Connect --
 *
 *      This procedure is invoked to process the "nddsConnect" Tcl/Tk
 *      command.  Connect to the NDDS daemon.
 *
 * Results:
 *      A standard Tcl result.
 *
 *--------------------------------------------------------------
 */
 /* ARGSUSED */


void NddsWishRegisterAllTypes         (void);

 /* ARGSUSED */
int NddsWishConnect(ClientData notUsed, Tcl_Interp *interp, int argc, char **argv)
{
    /* connect module to the NDDS daemon */
    NddsDebug (1, ("NddsWishConnect: Connecting to NDDS\n"));

    {
	/* Try to help avoid more troubles with peer host lists */
	char *s;
	s = getenv ("NDDS_PEER_HOSTS");
	if (NULL == s)
	    printf ("  NDDS_PEER_HOSTS env variable does not exit.\n");
	else
	    printf ("getenv(NDDS_PEER_HOSTS): %s\n", s);
	printf ("Watch out for NDDS_PEER_HOST_LIST files!!!\n");
    }

    /* It's up to the tcl script to set verbosity now. */
    /* NddsVerbositySet(2); */
    /* NddsVerbosityErrorSet(2); */
    /* NddsVerbosityDebugSet(0); */

#ifdef NOT_MULTICAST
    fprintf(stderr, "NOT_MULTICAST!\n");
    NddsInit(nddsDomain, NULL);
#else
    {
	    NDDSMulticastInfoStorage MulticastInfo;
	    fprintf(stderr, "MULTICAST!\n");

	    /* FIX: these should not be hard coded. */
	    nddsDomain = 7401;

#ifdef NDDS_1_11Q
	    MulticastInfo.domain = 7402;
	    MulticastInfo.ttl = 5;
	    NddsDebug (2, ("NddsInit: dom=%d,  multicast dom=%d, TTL=%d\n",
			   nddsDomain, MulticastInfo.domain,
			   MulticastInfo.ttl));
#else
	    MulticastInfo.Domain = 7402;
	    MulticastInfo.TTL = 5;
	    NddsDebug (2, ("NddsInit: dom=%d,  multicast dom=%d, TTL=%d\n",
			   nddsDomain, MulticastInfo.Domain,
			   MulticastInfo.TTL));
#endif


	    fprintf (stderr,"WARNING: MULTICAST >> forced off <<\n");
	    NddsInit(nddsDomain, NULL);
	    /*    NddsInit(nddsDomain, &MulticastInfo);*/
    }
#endif
    fprintf(stderr, "Finished NDDS initialization...waiting for NDDS to get going...");
    sleep (1);				/* let NDDS get going */

    NddsWishRegisterAllTypes();	/* register types */

    fprintf(stderr, "Finished registering all NddsWish types.\n");

    return (TCL_OK);
}

/*
 *--------------------------------------------------------------
 *
 * ndds_ProducerCreate --
 *
 *      This procedure is invoked to process the "nddsProducerCreate" Tcl/Tk
 *      command.  Creates a producer and a single production.
 *
 * Results:
 *      A standard Tcl result.
 *
 * Side effects:
 *      See the user documentation.
 *
 *--------------------------------------------------------------
 */
 /* ARGSUSED */
int NddsWishProducerCreate(ClientData notUsed, Tcl_Interp *interp, int argc, char **argv)
{
    TclProducer	producer;
    NDDS_TYPE_DRIVER *typeDriver;
    int *parameters=NULL;
    int numParams;

    PrintTclCmd (argc, argv);

    if (argc < 2) {
      Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
		 "command <format [args...]>", (char *) NULL);
      return (TCL_ERROR);
    }
    argc--; argv++;			/* skip past ProducerCreate */

    producer = producerAdd (*argv);	/* create new entry */
    if (!producer) {
	Tcl_AppendResult(interp, "ERROR: name already taken:",
			 *argv, (char *) NULL);
	return (TCL_ERROR);
    }
    argc--; argv++;			/* skip past name */

    /* create producer to respond to queries */
    producer->producer = NddsProducerCreate (producer->name, NDDS_SYNCHRONOUS,
					     persistence, strength); 

    {    
      NDDSProducerPropertiesStorage prop;
      NddsProducerPropertiesGet (producer->producer, &prop);
      prop.prodRefreshPeriod = 15.0;
      prop.sendQueueSize = 100;
      NddsProducerPropertiesSet (producer->producer, &prop);
    }

    if (0==argc) return (TCL_OK);  /* No more parameters left, so we are done. */

    /* Lookup the commands info */
    {
	Tcl_HashEntry *hPtr;

	hPtr = Tcl_FindHashEntry (typeRegistry, *argv);
	if (!hPtr) {
	    printf ("NddsWishProducerCreate ERROR: did not find type %s in registry\n", *argv);
#if 0
	    return (TCL_ERROR);
#else
	    typeDriver = NULL;		/* Don't fail if not found.  Try to keep going. */
#endif
	} else {
	    typeDriver = (NDDS_TYPE_DRIVER *) Tcl_GetHashValue (hPtr);
	}
    }
    if (!typeDriver) {
	printf ("NddsWishProducerCreate: ERROR looking up type %s\n", *argv);
	return (TCL_ERROR);
    }
    producer->typeDriver = typeDriver;
    argc--; argv++;	/* Go past type name */

    /* Pull off the parameter list and store it in an array */
    numParams = argc;
    if (argc) {
	int i;
	parameters = (int *)malloc(argc * sizeof(int));
	for (i=0; argc; i++, argc--, argv++) {
	    int value, status;
	    status = Tcl_GetInt (interp, *argv, &value);
	    if (TCL_ERROR == status) {
		printf ("NddsWishProducerCreate: ERROR getting integer parameters\n");
		return (TCL_ERROR);
	    }
	    parameters[i] = value;
	}
    }

#ifndef NDEBUG
    if (0 > numParams) {
	printf ("NddsWishProducerCreate ERROR: NumParams less than 0\n");
	return (TCL_ERROR);
    }
#endif

    switch (numParams) {
      case 0:
	producer->msg = typeDriver->allocate(typeDriver->type, producer->name, NULL);
	break;
      case 1:
	producer->msg = typeDriver->allocate(typeDriver->type, producer->name, (void *)parameters[0]);
	break;
      case 3:		/* CSMat special case */
#if 0
	/* CSMat N M Option  the option is as follows: */
	/* 0 for CSMAT_SEND_MINIMUM */  /* 1 for CSMAT_SEND_SIZES */
	/* 2 for CSMAT_SEND_NAME */	/* 4 for CSMAT_SEND_NAMES_AND_UNITS */
	/* 255 for CSMAT_SEND_ALL */
	{
	    int len1, len2;
	    int option;

	    len1 = parameters[0];
	    len2 = parameters[1];
	    producer->msg = CSMatAlloc ("", len1, len2);

	    option = parameters[2];
	    NddsProducerProductionAdd (producer->producer, "CSMat",
				       producer->name, producer->msg, option, 
				       NULL, 0, 
				       NULL, NULL);
	}
        if (parameters) free (parameters);
	return (TCL_OK);
#else
	printf ("NddsWishProducerCreate ERROR: NumParams indicates a CSMat.  No longer supported.\n");
	return (TCL_ERROR);
#endif

	break;		/* NOTREACHED */

      default:
	printf ("NddsWishProducerCreate ERROR: NumParams = %d not implimented\n", numParams);
	return (TCL_ERROR);
    }

#ifdef NDDS_1_11Q
    NddsProducerProductionAdd (producer->producer, typeDriver->type,
			       producer->name, producer->msg, 0, 
			       NULL, 0);
#else
    NddsProducerProductionAdd (producer->producer, typeDriver->type,
			       producer->name, producer->msg, 0, 
			       NULL, 0, 
			       NULL, NULL);
#endif
    if (parameters) free (parameters);
    return (TCL_OK);
}

/*
 *--------------------------------------------------------------
 *
 * ndds_ProducerSample -- Generate a NDDS Production
 *
 *      This procedure is invoked to process the "nddsProducerSample" Tcl/Tk
 *      command.
 *
 * Results:
 *      A standard Tcl result.
 *
 *--------------------------------------------------------------
 */
 /* ARGSUSED */
int NddsWishProducerSample (ClientData notUsed, Tcl_Interp *interp, int argc, char **argv)
{
    /* NDDS_TYPE_DRIVER *typeDriver; */
    int status;
    TclProducer producer;

    PrintTclCmd (argc, argv);

    if (argc < 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 "command <format data <format data>...>", (char *) NULL);
	return (TCL_ERROR);
    }

    argc--; argv++;
    
    /* check if message name is registered */
    if ((producer = producerLookup (*argv)) == NULL) {
	Tcl_AppendResult(interp, "message name does not exist:",
			 *argv, (char *) NULL);
	return (TCL_ERROR);
    }

    argc--; argv++;		/* Brought this increment back in for IntArrays */
    if (argc) {
        /* Don't do a conversion from Ndds to Tcl for Events when given no parameters */
        /* If this is skipped, we are just sending out a message without new data.    */
	status = producer->typeDriver->fromTcl(producer->msg, argc, argv);
#ifndef NDEBUG
	/* FIX: Add check of status */
#endif
    }

    if (NddsProducerSample (producer->producer) <= 0) {
	printf ("NddsProducerSample failed! %s\n", producer->name);
	return (TCL_ERROR);
    }

    return (TCL_OK);
}




/* Keep polling for NDDS data */
void ConsumerPollWrapper (ClientData clientData)
{
    NddsConsumerPoll ((NDDSConsumer)clientData);
					/* arrange to be called again */
    Tcl_CreateTimerHandler (NDDS_POLL_TIME,
			   ConsumerPollWrapper, TaskConsumer);
    return;
}

/*
   Handler for all NDDS Consumer callbacks.
   Creates a call to the user supplied tcl command with the following args:
   	status, name, data...
   The data type is whatever was requested by ConsumerCreate.
*/

NDDSObjectInstance CallBackWrapper (NDDSUpdateInfo update)
{
    Tcl_DString	cmd;
    NDDS_TYPE_DRIVER *typeDriver;
    int status, m;

    TclConsumerInfo	store =(TclConsumerStorage *)update->callBackRtnParam;
    Tcl_DStringInit (&cmd);
    Tcl_DStringAppendElement (&cmd, store->callback); /* command */
    NddsDebug (TRACE, ("CallBackWrapper (%s)\n", store->callback));

    switch (update->updateStatus) { /* status */
      case NDDS_NEVER_RECEIVED_DATA:
	Tcl_DStringAppendElement (&cmd, "NDDS_NEVER_RECEIVED_DATA");
	break;
      case NDDS_NO_NEW_DATA:
	Tcl_DStringAppendElement (&cmd, "NDDS_NO_NEW_DATA");
	break;
      case NDDS_UPDATE_OF_OLD_DATA:
	Tcl_DStringAppendElement (&cmd, "NDDS_UPDATE_OF_OLD_DATA");
	break;
      case NDDS_FRESH_DATA:
	Tcl_DStringAppendElement (&cmd, "NDDS_FRESH_DATA");
	break;
      default:
	printf ("CallBackWrapper: bogus update status %d\n",
		update->updateStatus);
	return (NULL);
	break;
    }
    Tcl_DStringAppendElement (&cmd, store->name); /* name */

    typeDriver = store->typeDriver;
    if (!typeDriver) {
	printf ("CallBackWrapper ERROR: no type driver found for %s\n", store->name);
	return (NULL);
    }
    /*status = typeDriver->toTcl (store->instance, &cmd);*/
    status = typeDriver->toTcl (store->instance, store->interp);
#ifndef NDEBUG
    /* FIX: Check status */
#endif

    m = Tcl_Eval(store->interp, Tcl_DStringValue (&cmd));
    if (m || (debug_level >= 3))	/* show cmd and error */
	printf ("%s -> %s\n", Tcl_DStringValue (&cmd), store->interp->result);

    Tcl_DStringFree (&cmd);
    status = Tcl_UnsetVar (store->interp, "this", TCL_LEAVE_ERR_MSG);	/* "this" => nddsdata */
    if (TCL_ERROR == status) {
	printf ("Tcl_UnsetVar `this' ERROR: %s\n",  store->interp->result);
    }

    return (NULL);
}

void TaskConsumerCreate(void);

void
TaskConsumerCreate(void)
{
    float deadline = 999999.0f;		/* max seconds between updates */
    float minSeparation = 0.0f;		/* min seconds between updates */

    TaskConsumer = NddsConsumerCreate ("Tcl/Tk", NDDS_POLLED_RELIABLE,
				       deadline, minSeparation);

    if (TaskConsumer) {
	/* start checking for data whenever idle (TK dependence) */
	Tcl_DoWhenIdle (ConsumerPollWrapper, TaskConsumer);
    }

    return;
}


/* For reliable Tcl/Tk consumers (from NDDS 2.0b manual). */
void tclConsumerReliableStatusRtn(NDDSConsumerReliableStatus status) {
  switch(status->event) {
  case NDDS_PRODUCER_NEW:
    fprintf(stderr," We are receiveing samples from a new producer.\n");
    break;
  case NDDS_SAMPLE_DROPPED:
    fprintf(stderr, "We lost a sample.\n");
    break;
  }
}


/*
 *--------------------------------------------------------------
 *
 * ndds_ConsumerCreate --
 *
 *      This procedure is invoked to process the "nddsConsumerCreate" Tcl/Tk
 *      command.  
 *	Create one global consumer if needed and add one subscription.
 *
 * Results:
 *      A standard Tcl result.
 *
 *--------------------------------------------------------------
 */
 /* ARGSUSED */

int NddsWishConsumerCreate(ClientData notUsed, Tcl_Interp *interp, int argc, char **argv)
{
    TclConsumerInfo	store;		/* store of data to pass to callback */
    NDDS_TYPE_DRIVER *typeDriver;
    int *parameters=NULL;
    int numParams;

    PrintTclCmd (argc, argv);

    if (argc < 4) {
      Tcl_AppendResult(interp, "too few args, usage: ", argv[0],
		 "name format handler [args...]", (char *) NULL);
      return (TCL_ERROR);
    }
    --argc; ++argv;			/* skip past ConsumerSubscriptionAdd */

    if (!TaskConsumer) {		/* Consumer for all subscriptions */
	TaskConsumerCreate();
	if (!TaskConsumer) {		/* failed to create */
	    Tcl_AppendResult(interp, "ERROR!!! could not create consumer!", (char *) NULL);
	    return (TCL_ERROR);
	}
    }

    store = (TclConsumerInfo)calloc (1, sizeof (TclConsumerStorage));
    if (!store) return (TCL_ERROR);

    store->name = strdup (*argv);	/* copy name */
    --argc; ++argv;			/* skip past data name */
    store->callback = strdup (*argv);
    --argc; ++argv;			/* skip past handler */
    store->interp = interp;

    {
	Tcl_HashEntry *hPtr;

	hPtr = Tcl_FindHashEntry (typeRegistry, *argv);
	if (!hPtr) {
	    printf ("NddsWishConsumerCreate ERROR: did not find type %s in registry\n", *argv);
	    return (TCL_ERROR);
	}
	typeDriver = (NDDS_TYPE_DRIVER *) Tcl_GetHashValue (hPtr);
    }
    store->typeDriver = typeDriver;
    --argc; ++argv;

    /* Pull off the parameter list and store it in an array */
    numParams = argc;
    if (argc) {
	int i;
	parameters = (int *)malloc(argc * sizeof(int));
	for (i=0; argc; i++, argc--, argv++) {
	    int value, status;
	    status = Tcl_GetInt (interp, *argv, &value);
	    if (TCL_ERROR == status) {
		printf ("NddsWishConsumerCreate: ERROR getting integer parameters\n");
		return (TCL_ERROR);
	    }
	    parameters[i] = value;
	}
    }

#ifndef NDEBUG
    if (0 > numParams) {
	printf ("NddsWishConsumerCreate ERROR: NumParams less than 0\n");
	return (TCL_ERROR);
    }
#endif

    switch (numParams) {
      case 0:
	store->instance = typeDriver->allocate(typeDriver->type, store->name, NULL);
	break;
      case 1:
	store->instance = typeDriver->allocate(typeDriver->type, store->name, (void *)parameters[0]);
	break;
      case 2:
	/* FIX: Special case for CSMats... would be nice not to have this be special */
	{
#if 0
	    int len1, len2;
	    len1 = parameters[0];
	    len2 = parameters[1];
	    store->instance = CSMatAlloc ("", len1, len2);
	    /* FIX: One of these two would be preferable. -KDS */
	    /* = typeDriver->allocate("", len1, len2); */
	    /* = typeDriver->allocate(typeDriver->type, store->name, (void *)parameters[0]);*/
#else
	printf ("NddsWishConsumerrCreate ERROR: NumParams indicates a CSMat.  No longer supported.\n");
	return (TCL_ERROR);
#endif

	}
	break;
      default:
	printf ("NddsWishConsumerCreate ERROR: NumParams = %d not implimented\n", numParams);
	return (TCL_ERROR);
    }

    { 
      NDDSConsumerPropertiesStorage Properties;
      NddsConsumerPropertiesGet(TaskConsumer, &Properties);
      Properties.receiveQueueSize = 100;
      Properties.subsRefreshPeriod = 15.0;
      Properties.reliableStatusRtn = tclConsumerReliableStatusRtn;
      NddsConsumerPropertiesSet(TaskConsumer, &Properties);
    }
    NddsConsumerSubscriptionAdd (TaskConsumer, typeDriver->type,
             store->name, store->instance, CallBackWrapper, store);

    if (parameters) free (parameters);
    return (TCL_OK);
}

    
TclProducer producerAdd (char *name)
{
    /* check if message name is already registered */
    if (producerLookup (name) != NULL) {
	return (NULL);
    }

    /* allocate memory for another producer */
    ++numOfProducers;
    Producers = (TclProducerStorage *)
	realloc (Producers, numOfProducers * sizeof(TclProducerStorage));

    /* copy message name */
    strncpy (Producers[numOfProducers-1].name, name, MSGLEN);
    return (Producers+(numOfProducers-1));
}

/*******************************************************************
* producerLookup: lookup specific producer from TclProducerStorage database
* and return pointer to producer
*
*******************************************************************/
TclProducer producerLookup (char *name)
{
  extern TclProducerStorage *Producers;
  int i;

  for (i=0;i<numOfProducers;i++) {
    if (!strncmp (name, Producers[i].name, MSGLEN))
      return &(Producers[i]);
  }
  return (NULL);
}


/*
 *--------------------------------------------------------------
 *
 * NddsWishDBaseListAll --
 *
 *      This procedure is for the "nddsDBaseListAll" Tcl/Tk command.  
 *	It dumps all of the ndds database to stdout.
 *
 * Results:
 *      A standard Tcl result.
 *
 *--------------------------------------------------------------
 */
 /* ARGSUSED */

int NddsWishDBaseListAll (ClientData notUsed, Tcl_Interp *interp, int argc, char **argv)
{

    PrintTclCmd (argc, argv);

    if (argc > 1) {
      Tcl_AppendResult(interp, "too many args, usage: ", argv[0], (char*)NULL);
      return (TCL_ERROR);
    }

    NddsDBaseListAll ();	/* No parameters, no returns. */

    return (TCL_OK);
}

/*
 *--------------------------------------------------------------
 *
 * NddsWishVerbositySet 
 *
 *
 *--------------------------------------------------------------
 */
/* ARGSUSED */
int NddsWishVerbositySet(
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;
    int newVerbosity;
    char result[10];
    PrintTclCmd (argc, argv);

    if (argc != 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 "number\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[1]);
    newVerbosity = NddsVerbositySet (verbosity);

    /* Return the new verbosity */
    sprintf (result, "%d", newVerbosity);
    Tcl_AppendResult (interp, result, (char *)NULL);

    NddsDebug (TRACE+1,("%d = NddsVerbositySet(%d);\n",
			newVerbosity,verbosity));
    
    return (TCL_OK);
}


/*
 *--------------------------------------------------------------
 *
 * NddsWishVerbosityErrorSet 
 *
 *
 *--------------------------------------------------------------
 */
/* ARGSUSED */
int NddsWishVerbosityErrorSet(
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;
    int newVerbosity;
    char result[10];

    PrintTclCmd (argc, argv);

    if (argc != 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 "number\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[1]);
    newVerbosity = NddsVerbosityErrorSet (verbosity);

    /* Return the new verbosity */
    sprintf (result, "%d", newVerbosity);
    Tcl_AppendResult (interp, result, (char *)NULL);

    NddsDebug (TRACE+1,("%d = NddsVerbosityErrorSet(%d);\n",
			newVerbosity,verbosity));
    
    return (TCL_OK);
}



/*
 *--------------------------------------------------------------
 *
 * NddsWishVerbosityDebugSet 
 *
 *
 *--------------------------------------------------------------
 */
/* ARGSUSED */
int NddsWishVerbosityDebugSet(
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;
    int newVerbosity;
    char result[10];

    PrintTclCmd (argc, argv);

    if (argc != 2) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 " verbosity\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[1]);
    newVerbosity = NddsVerbosityDebugSet (verbosity);

    /* Return the new verbosity */
    sprintf (result, "%d", newVerbosity);
    Tcl_AppendResult (interp, result, (char *)NULL);

    NddsDebug (TRACE+1,("%d = NddsVerbosityDebugSet(%d);\n",
			newVerbosity,verbosity));
    
    return (TCL_OK);
}


/*
 *--------------------------------------------------------------
 *
 * NddsWishDBaseListConsumers
 *
 *
 *--------------------------------------------------------------
 */
/* ARGSUSED */
int NddsWishDBaseListConsumers (
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;

    PrintTclCmd (argc, argv);

    if (argc != 4) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 " consTempl nameTempl verbosity\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[3]);

    NddsDBaseListConsumers (argv[1], argv[2], verbosity);

    return (TCL_OK);
}


/*
 *--------------------------------------------------------------
 *
 * NddsWishDBaseListInstances
 *
 *--------------------------------------------------------------
 */
/* ARGSUSED */
int NddsWishDBaseListInstances (
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;

    PrintTclCmd (argc, argv);

    if (argc != 4) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 " typeTemplate nameTemplate verbosity\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[3]);

    NddsDBaseListInstances (argv[1], argv[2], verbosity);

    return (TCL_OK);
}


/*
 *--------------------------------------------------------------
 *
 * NddsWishDBaseListProducers
 *
 *--------------------------------------------------------------
 */
/* ARGSUSED */
int NddsWishDBaseListProducers (
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;

    PrintTclCmd (argc, argv);

    if (argc != 4) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 " prodTempl nameTempl verbosity\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[3]);

    NddsDBaseListProducers (argv[1], argv[2], verbosity);

    return (TCL_OK);
}




/*
 *--------------------------------------------------------------
 *
 * NddsWishDBaseListProductionsLocal
 *
 *--------------------------------------------------------------
 */

#ifdef NDDS_1_11Q

#else
/* ARGSUSED */
int NddsWishDBaseListProductionsLocal (
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;

    PrintTclCmd (argc, argv);

    if (argc != 4) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 " typeTempl nameTempl verbosity\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[3]);

    NddsDBaseListProductionsLocal (argv[1], argv[2], verbosity);

    return (TCL_OK);
}
#endif



/*
 *--------------------------------------------------------------
 *
 * NddsWishDBaseListProductionsRemote
 *
 *--------------------------------------------------------------
 */
/* ARGSUSED */
int NddsWishDBaseListProductionsRemote (
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;

    PrintTclCmd (argc, argv);

    if (argc != 4) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 "typeName nameTempl verbosity\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[3]);

    NddsDBaseListProductionsRemote (argv[1], argv[2], verbosity);

    return (TCL_OK);
}



/*
 *--------------------------------------------------------------
 *
 * NddsWishDBaseListSubscriptionsLocal
 *
 *--------------------------------------------------------------
 */

#ifdef NDDS_1_11Q

#else
/* ARGSUSED */
int NddsWishDBaseListSubscriptionsLocal (
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;

    PrintTclCmd (argc, argv);

    if (argc != 3) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 "nameTempl verbosity\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[2]);

    NddsDBaseListSubscriptionsLocal (argv[1], verbosity);

    return (TCL_OK);
}
#endif




/*
 *--------------------------------------------------------------
 *
 * NddsWishDBaseListSubscriptionsRemote
 *
 *--------------------------------------------------------------
 */
/* ARGSUSED */
int NddsWishDBaseListSubscriptionsRemote (
    ClientData notUsed,
    Tcl_Interp *interp,
    int argc,
    char **argv)
{
    int verbosity;

    PrintTclCmd (argc, argv);

    if (argc != 4) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", argv[0],
			 "hostTempl nameTempl verbosity\"",
			 (char *) NULL);
	return (TCL_ERROR);
    }

    verbosity = atoi (argv[3]);

    NddsDBaseListSubscriptionsRemote (argv[1], argv[2], verbosity);

    return (TCL_OK);
}

