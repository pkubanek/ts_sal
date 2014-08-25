/*
 * nomadNddsMessages.h
 *
 * We propose this as the place to put all Nomad message names and types.
 *
 * The types can be used in more than one message name, so the names
 * don't really belong in src/messages.  For example, a drive command
 * can be sent from UI and from NAV, have the same type, and different
 * message name.
 *
 *
 * Created: 4/16/97  (jl@cs.cmu.edu)
 *
 * $Log: nomadNddsMessages.h,v $
 * Revision 1.15  1999/06/28 12:44:53  mwagner
 * Updated for NDDS 2.1d
 *
 * Revision 1.14  99/04/09  13:21:09  sjm
 * Eliminating old NDDS messages which are no longer used. Also added
 * localhost to the NDDS_PEER_HOSTS variable defined in lri_cshrc.
 * 
 * Revision 1.13  1998/10/22 21:21:58  sjm
 * Added support for INFO NDDS messages.
 *
 * Revision 1.12  1998/10/09 14:28:54  sjm
 * Changed the name of the navSettings receive and send messages to avoid
 * receiving my own message.
 *
 * Revision 1.8  1997/06/22 22:43:23  jl
 * Added uiBridge NDDS messages
 *
 * Revision 1.7  1997/05/31 17:51:19  jl
 * Forgot to update this after a day in the run.
 *
 * Revision 1.6  1997/05/06 20:48:27  jl
 * hanged some NDDS message names.
 *
 * Revision 1.5  1997/05/06 17:01:10  mwm
 * Got rid of the old "msg" suffix.
 *
 * Revision 1.4  1997/05/01 17:51:31  jl
 * Added shorthand macros to nomadNddsMessages.h to make
 * the constant message changes less time consuming.
 *
 * Revision 1.3  1997/04/27 19:04:56  hjt
 * update from ames tree
 *
 * Revision 1.2  1997/04/17 08:48:36  jl
 * Adding support for enum in TypeMap.
 *
 * Revision 1.1  1997/04/17 06:32:10  jl
 * Added nomadNddsMessages.h
 *
 */

/* So far, mwm and jl only really know about the following messages.
 * The intent is that everyone will add the messages they know about
 * to this file, as well as adding nomadUnits to their XDR files.
 * This is the intent not the arrogant order.  Discuss.
 *
 * Also feel free to change the name of anything, but notify please.
 * Thanks.
 *
 * Most messages are expected to have a mechanical mapping from
 * NDDS type name (the name of the XDR files in src/messages) to
 * all the variables above.  It would be nice to have macros for
 * this common case rather than having to re-type everything,
 * but several attempts at this failed.  These macros, if anybody
 * wants to try them, will probably involve pasting tokens
 * via ANSI cpp # and ##.
 * 
 * 
 * (MDW 6/24/99) NOTE: The following stuff mentioning "XXXStruct" has been changed.
 * Now, a message structure is the same name as the message (no "Struct" appended 
 * at the end), and a pointer is *messageName. Hope this makes sense!
 *
 * If XXX is the NDDS type name (from src/messages/something, e.g, navMove)
 * YYY_MSG_TYPE is XXXStruct (for declarations,) YYY_MSG_TYPE_NAME
 * is "XXX" for NDDS calls, YYY_MSG_NAME is the message name
 * (usually "XXX") for NDDS calls, and YYY_MSG_TYPE_REGFN is
 * XXXNddsRegister.  These macro names may seem long, feel free
 * to suggest alternatives.
 *
 *
 */

/* 
 * Messages from NAV --> RT 
 *
 */

#include "nomadNddsDomain.h"

/* move: <speed,arc> or <angular speed> if point turn */
#define NAVRT_MOVE_CTYPE move   
#define NAVRT_MOVE_ITYPE move*
#define NAVRT_MOVE_ITYPE_NAME "move"
#define NAVRT_MOVE_NAME "rtMove"
#define NAVRT_MOVE_ITYPE_RFN moveNddsRegister
#define NAVRT_MOVE_ID 0

/* 
 * Messages from RT --> ALL (telemetry)
 *
 */

/* posDerivedState: pose speed et cetera. */
#define TELE_POSE_CTYPE posDerivedState
#define TELE_POSE_ITYPE posDerivedState*
#define TELE_POSE_ITYPE_NAME "posDerivedState"
#define TELE_POSE_NAME "posDerivedState"
#define TELE_POSE_ITYPE_RFN posDerivedStateNddsRegister
#define TELE_POSE_ID 20

/* bodyDerivedState: wheel speed etc */
#define TELE_BODY_CTYPE bodDerivedState
#define TELE_BODY_ITYPE bodDerivedState*
#define TELE_BODY_ITYPE_NAME "bodDerivedState"
#define TELE_BODY_NAME "bodDerivedState"
#define TELE_BODY_ITYPE_RFN bodDerivedStateNddsRegister
#define TELE_BODY_ID 22

/* sysState, a single flag that says alive or killed */
#define TELE_STATE_CTYPE sysState
#define TELE_STATE_ITYPE sysState*
#define TELE_STATE_ITYPE_NAME "sysState"
#define TELE_STATE_NAME "sysState"
#define TELE_STATE_ITYPE_RFN sysStateNddsRegister
#define TELE_STATE_ID 23

/*
 *
 * UI --> NAV,RT messages
 *
 */

/* navEnable, a flag that enables or disables NAV steering
 * With nav Disabled, UI controls rt without voting
 */
#define UIALL_NAVENABLE_CTYPE navEnable
#define UIALL_NAVENABLE_ITYPE navEnable*
#define UIALL_NAVENABLE_ITYPE_NAME "navEnable"
#define UIALL_NAVENABLE_NAME "navEnable"
#define UIALL_NAVENABLE_ITYPE_RFN navEnableNddsRegister
#define UIALL_NAVENABLE_ID 30

/* Note that this message appears to only go to rt (per its name)
 * but it is also consumed by nav
 */
#define UIALL_DRASTIC_CTYPE rtSignalCondition
#define UIALL_DRASTIC_ITYPE rtSignalCondition*
#define UIALL_DRASTIC_ITYPE_NAME "rtSignalCondition"
#define UIALL_DRASTIC_NAME "rtSignalCondition"
#define UIALL_DRASTIC_ITYPE_RFN rtSignalConditionNddsRegister
#define UIALL_DRASTIC_ID 32

/* 
 *  UI --> NAV messages
 *
 */

/* navHeading -- feeds D* arbiter module, heading, range, speed */
#define UINAV_HEADING_CTYPE navHeading   
#define UINAV_HEADING_ITYPE navHeading*
#define UINAV_HEADING_ITYPE_NAME "navHeading"
#define UINAV_HEADING_NAME "navHeading"
#define UINAV_HEADING_ITYPE_RFN navHeadingNddsRegister
#define UINAV_HEADING_ID 50

/* move: <speed,arc> or <angular speed> if point turn */
#define UINAV_MOVE_CTYPE move   
#define UINAV_MOVE_ITYPE move*
#define UINAV_MOVE_ITYPE_NAME "move"
#define UINAV_MOVE_NAME "navMove"
#define UINAV_MOVE_ITYPE_RFN moveNddsRegister
#define UINAV_MOVE_ID 51

/*Message from new interface to nav to enable/disable the modules connected
  to arbiter. I am not positive, but I think all the UI messages listed
  above this point are no longer used - sjm (Sept 9, 1998)*/
#define UINAV_NAV_SETTINGS_CTYPE navSettings
#define UINAV_NAV_SETTINGS_ITYPE navSettings*
#define UINAV_NAV_SETTINGS_ITYPE_NAME "navSettings"
#define UINAV_NAV_SETTINGS_NAME "navSettings"
#define UINAV_NAV_SETTINGS_ITYPE_RFN navSettingsNddsRegister
#define UINAV_NAV_SETTINGS_ID 52

#define UINAV_CMD_NAV_SETTINGS_CTYPE navSettings
#define UINAV_CMD_NAV_SETTINGS_ITYPE navSettings*
#define UINAV_CMD_NAV_SETTINGS_ITYPE_NAME "navSettings"
#define UINAV_CMD_NAV_SETTINGS_NAME "navCmdSettings"
#define UINAV_CMD_NAV_SETTINGS_ITYPE_RFN navSettingsNddsRegister
#define UINAV_CMD_NAV_SETTINGS_ID 53

/*infomation message from nav system. Sends out low resolution version
  of the morphin goodness map*/
#define NAV_INFO_MSG_CTYPE info
#define NAV_INFO_MSG_ITYPE info*
#define NAV_INFO_MSG_ITYPE_NAME "info"
#define NAV_INFO_MSG_NAME "info"
#define NAV_INFO_MSG_ITYPE_RFN infoNddsRegister
#define NAV_INFO_MSG_ID 54


/* Please fill in */


/*---------------------------------------------------------------------*/
/* This is ugly.  You have been warned (jl@cs.cmu.edu)
 *
 * Shorthand for common Ndds crud.
 *
 * Assume each data item to be produced has its own producer.
 * Perhaps not reasonable, but OK in some places.
 * Also assuming some arbitrary values for persistance and strength.
 * This is probably OK since I don't think we have multiple senders
 * of anything (we do for move messages but we give them different
 * names)
 *
 * Assume each incoming message has its own consumer.  Assume some
 * arbitrary values for deadline and min_separation.
 *
 * I use this as follows:
 *
 * Somewhere in the top-level of a C file, I specify allthe messages
 * I want to produce by typing, e.g:
 *
 * DECLARE_OUTPUT_ITEM(NAVRT_MOVE, var1Name);
 *
 * and the messages I want to receive by typing, e.g:
 *
 * DECLARE_INPUT_ITEM(TELE_POSE, var2Name);
 *
 * Then, inside some initialization function, I type, e.g:
 * 
 * INIT_OUTPUT_ITEM(NAVRT_MOVE, var1Name);
 * INIT_INPUT_ITEM(TELE_POSE, var2Name);
 * 
 * and so on for each message I hear or send.
 *
 * Then, again at the top level:
 *
 * INPUT_HANDLERS_BEGIN  -- No semi-colon! 
 * HANDLER_BEGIN(TELE_POSE, var3Name);
 * {
 *    Stuff that access var3Name (declared automatically to be of type 
 *    TELE_POSE_ITYPE == *TELE_POSE_CTYPE
 * }
 * HANDLER_END;
 * <Other handlers>
 * INPUT_HANDLERS_END   -- No semi-colon! 
 *
 * I SAID IT WAS UGLY.  Feel free to not use it, but please don't take it out.
 * (jl@cs.cmu.edu)
 */

#define GLOBAL_HANDLER Ndds_Subscribe
#define GLOBAL_SUBSCRIBER GlobalNddsSubscriber
#define GLOBAL_SUBSCRIBER_NAME "GlobalNddsSubscriber"


#define INIT_NDDS() \
     NddsInit(NOMAD_NDDS_DOMAIN, NULL);\
     GLOBAL_SUBSCRIBER = NddsSubscriberCreate();\
     
#define DECLARE_NDDS_OUTPUT(Name, Var) \
     Name##_CTYPE Var; \
     NDDSPublisher Name##_Publisher; \
     NDDSPublication Name##_Publication

#define INIT_NDDS_OUTPUT(Name, Var) do {\
     Name##_ITYPE_RFN();\
     Name##_Publisher = NddsPublisherCreate(NDDS_PUBLISHER_ASYNCHRONOUS);\
     Name##_Publication = NddsPublicationCreate(Name##_NAME, Name##_ITYPE_NAME, &(Var), 15.0, 1.0);\
     NddsPublisherPublicationAdd(Name##_Publisher, Name##_Publication); \
     } while (0)

#define NDDS_OUTPUT(Name) NddsPublisherSend(Name##_Publisher)

#define DECLARE_NDDS_INPUT(Name, Var) \
     Name##_CTYPE Var; \
     NDDSSubscription Name##_Subscription; 

/* Should put a bunch of subscribers together for lower overhead? */     
#define INIT_NDDS_INPUT(Name, Var) do {\
     Name##_ITYPE_RFN();\
     Name##_Subscription = NddsSubscriptionCreate(NDDS_SUBSCRIPTION_POLLED, \
						  Name##_NAME, Name##_ITYPE_NAME, \
						  GLOBAL_SUBSCRIBER, 1000, 0.0, \
						  (void *)GLOBAL_HANDLER, \
						  (void *) Name##_ID);\
     if (!NddsSubscriberSubscriptionAdd(GLOBAL_SUBSCRIBER,  \
					Name##_Subscription)) { \
	fprintf(stderr, "NDDS Subscription add for %s failed\n", Name##_ITYPE_NAME);\
     }\
   } while (0)

#define NDDS_INPUT() NddsSubscriberPoll(GLOBAL_SUBSCRIBER)

#define NDDS_HANDLERS_BEGIN \
RTIBool GLOBAL_HANDLER (NDDSRecvInfo *u)\
{\
  if (!((u)->instance) || \
      (((u)->status != NDDS_FRESH_DATA) && \
       ((u)->status != NDDS_UPDATE_OF_OLD_DATA))) {\
        return (RTI_FALSE);\
  }\
  switch (((int) (u)->callBackRtnParam)) {

#define HANDLER_BEGIN(Name, Var) \
  case Name##_ID: {\
    Name##_ITYPE Var = (Name##_ITYPE) ((u)->instance);

#define HANDLER_END } break;

#define NDDS_HANDLERS_END } return (RTI_TRUE);}

#define DECLARE_NDDS() \
      RTIBool GLOBAL_HANDLER (NDDSRecvInfo *);\
      NDDSSubscriber GLOBAL_SUBSCRIBER;

