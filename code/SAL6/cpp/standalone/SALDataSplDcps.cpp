#include "SALDataSplDcps.h"
#include "ccpp_SALData.h"

const char *
__SALData_SALTopic__name(void)
{
    return (const char*)"SALData::SALTopic";
}

const char *
__SALData_SALTopic__keys(void)
{
    return (const char*)"";
}

const char *
__SALData_SALCommand__name(void)
{
    return (const char*)"SALData::SALCommand";
}

const char *
__SALData_SALCommand__keys(void)
{
    return (const char*)"";
}

const char *
__SALData_SALResponse__name(void)
{
    return (const char*)"SALData::SALResponse";
}

const char *
__SALData_SALResponse__keys(void)
{
    return (const char*)"";
}

const char *
__SALData_SALEvent__name(void)
{
    return (const char*)"SALData::SALEvent";
}

const char *
__SALData_SALEvent__keys(void)
{
    return (const char*)"";
}

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

c_bool
__SALData_SALTopic__copyIn(
    c_base base,
    struct ::SALData::SALTopic *from,
    struct _SALData_SALTopic *to)
{
    c_bool result = TRUE;

#ifdef OSPL_BOUNDS_CHECK
    if(from->private_revCode){
        if(((unsigned int)strlen(from->private_revCode)) <= 32){
            to->private_revCode = c_stringNew(base, from->private_revCode);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALTopic.private_revCode' of type 'C_STRING<32>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALTopic.private_revCode' of type 'C_STRING<32>' is out of range.");
        result = FALSE;
    }
#else
    to->private_revCode = c_stringNew(base, from->private_revCode);
#endif
    to->private_sndStamp = (c_double)from->private_sndStamp;
    to->private_rcvStamp = (c_double)from->private_rcvStamp;
    to->private_origin = (c_long)from->private_origin;
    return result;
}

c_bool
__SALData_SALCommand__copyIn(
    c_base base,
    struct ::SALData::SALCommand *from,
    struct _SALData_SALCommand *to)
{
    c_bool result = TRUE;

#ifdef OSPL_BOUNDS_CHECK
    if(from->private_revCode){
        if(((unsigned int)strlen(from->private_revCode)) <= 32){
            to->private_revCode = c_stringNew(base, from->private_revCode);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.private_revCode' of type 'C_STRING<32>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.private_revCode' of type 'C_STRING<32>' is out of range.");
        result = FALSE;
    }
#else
    to->private_revCode = c_stringNew(base, from->private_revCode);
#endif
    to->private_sndStamp = (c_double)from->private_sndStamp;
    to->private_rcvStamp = (c_double)from->private_rcvStamp;
    to->private_origin = (c_long)from->private_origin;
    to->private_seqNum = (c_long)from->private_seqNum;
#ifdef OSPL_BOUNDS_CHECK
    if(from->device){
        if(((unsigned int)strlen(from->device)) <= 32){
            to->device = c_stringNew(base, from->device);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.device' of type 'C_STRING<32>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.device' of type 'C_STRING<32>' is out of range.");
        result = FALSE;
    }
#else
    to->device = c_stringNew(base, from->device);
#endif
#ifdef OSPL_BOUNDS_CHECK
    if(from->property){
        if(((unsigned int)strlen(from->property)) <= 32){
            to->property = c_stringNew(base, from->property);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.property' of type 'C_STRING<32>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.property' of type 'C_STRING<32>' is out of range.");
        result = FALSE;
    }
#else
    to->property = c_stringNew(base, from->property);
#endif
#ifdef OSPL_BOUNDS_CHECK
    if(from->action){
        if(((unsigned int)strlen(from->action)) <= 32){
            to->action = c_stringNew(base, from->action);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.action' of type 'C_STRING<32>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.action' of type 'C_STRING<32>' is out of range.");
        result = FALSE;
    }
#else
    to->action = c_stringNew(base, from->action);
#endif
#ifdef OSPL_BOUNDS_CHECK
    if(from->value){
        if(((unsigned int)strlen(from->value)) <= 32){
            to->value = c_stringNew(base, from->value);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.value' of type 'C_STRING<32>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.value' of type 'C_STRING<32>' is out of range.");
        result = FALSE;
    }
#else
    to->value = c_stringNew(base, from->value);
#endif
#ifdef OSPL_BOUNDS_CHECK
    if(from->modifiers){
        if(((unsigned int)strlen(from->modifiers)) <= 128){
            to->modifiers = c_stringNew(base, from->modifiers);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.modifiers' of type 'C_STRING<128>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALCommand.modifiers' of type 'C_STRING<128>' is out of range.");
        result = FALSE;
    }
#else
    to->modifiers = c_stringNew(base, from->modifiers);
#endif
    return result;
}

c_bool
__SALData_SALResponse__copyIn(
    c_base base,
    struct ::SALData::SALResponse *from,
    struct _SALData_SALResponse *to)
{
    c_bool result = TRUE;

#ifdef OSPL_BOUNDS_CHECK
    if(from->private_revCode){
        if(((unsigned int)strlen(from->private_revCode)) <= 32){
            to->private_revCode = c_stringNew(base, from->private_revCode);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALResponse.private_revCode' of type 'C_STRING<32>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALResponse.private_revCode' of type 'C_STRING<32>' is out of range.");
        result = FALSE;
    }
#else
    to->private_revCode = c_stringNew(base, from->private_revCode);
#endif
    to->private_sndStamp = (c_double)from->private_sndStamp;
    to->private_rcvStamp = (c_double)from->private_rcvStamp;
    to->private_origin = (c_long)from->private_origin;
    to->private_seqNum = (c_long)from->private_seqNum;
    to->ack = (c_long)from->ack;
    to->error = (c_long)from->error;
#ifdef OSPL_BOUNDS_CHECK
    if(from->result){
        if(((unsigned int)strlen(from->result)) <= 32){
            to->result = c_stringNew(base, from->result);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALResponse.result' of type 'C_STRING<32>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALResponse.result' of type 'C_STRING<32>' is out of range.");
        result = FALSE;
    }
#else
    to->result = c_stringNew(base, from->result);
#endif
    return result;
}

c_bool
__SALData_SALEvent__copyIn(
    c_base base,
    struct ::SALData::SALEvent *from,
    struct _SALData_SALEvent *to)
{
    c_bool result = TRUE;

#ifdef OSPL_BOUNDS_CHECK
    if(from->private_revCode){
        if(((unsigned int)strlen(from->private_revCode)) <= 32){
            to->private_revCode = c_stringNew(base, from->private_revCode);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALEvent.private_revCode' of type 'C_STRING<32>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALEvent.private_revCode' of type 'C_STRING<32>' is out of range.");
        result = FALSE;
    }
#else
    to->private_revCode = c_stringNew(base, from->private_revCode);
#endif
    to->private_sndStamp = (c_double)from->private_sndStamp;
    to->private_rcvStamp = (c_double)from->private_rcvStamp;
    to->private_origin = (c_long)from->private_origin;
#ifdef OSPL_BOUNDS_CHECK
    if(from->message){
        if(((unsigned int)strlen(from->message)) <= 128){
            to->message = c_stringNew(base, from->message);
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALEvent.message' of type 'C_STRING<128>' is out of range.");
            result = FALSE;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'SALData::SALEvent.message' of type 'C_STRING<128>' is out of range.");
        result = FALSE;
    }
#else
    to->message = c_stringNew(base, from->message);
#endif
    return result;
}

void
__SALData_SALTopic__copyOut(
    void *_from,
    void *_to)
{
    struct _SALData_SALTopic *from = (struct _SALData_SALTopic *)_from;
    struct ::SALData::SALTopic *to = (struct ::SALData::SALTopic *)_to;
    to->private_revCode = CORBA::string_dup(from->private_revCode);
    to->private_sndStamp = (::DDS::Double)from->private_sndStamp;
    to->private_rcvStamp = (::DDS::Double)from->private_rcvStamp;
    to->private_origin = (::DDS::Long)from->private_origin;
}

void
__SALData_SALCommand__copyOut(
    void *_from,
    void *_to)
{
    struct _SALData_SALCommand *from = (struct _SALData_SALCommand *)_from;
    struct ::SALData::SALCommand *to = (struct ::SALData::SALCommand *)_to;
    to->private_revCode = CORBA::string_dup(from->private_revCode);
    to->private_sndStamp = (::DDS::Double)from->private_sndStamp;
    to->private_rcvStamp = (::DDS::Double)from->private_rcvStamp;
    to->private_origin = (::DDS::Long)from->private_origin;
    to->private_seqNum = (::DDS::Long)from->private_seqNum;
    to->device = CORBA::string_dup(from->device);
    to->property = CORBA::string_dup(from->property);
    to->action = CORBA::string_dup(from->action);
    to->value = CORBA::string_dup(from->value);
    to->modifiers = CORBA::string_dup(from->modifiers);
}

void
__SALData_SALResponse__copyOut(
    void *_from,
    void *_to)
{
    struct _SALData_SALResponse *from = (struct _SALData_SALResponse *)_from;
    struct ::SALData::SALResponse *to = (struct ::SALData::SALResponse *)_to;
    to->private_revCode = CORBA::string_dup(from->private_revCode);
    to->private_sndStamp = (::DDS::Double)from->private_sndStamp;
    to->private_rcvStamp = (::DDS::Double)from->private_rcvStamp;
    to->private_origin = (::DDS::Long)from->private_origin;
    to->private_seqNum = (::DDS::Long)from->private_seqNum;
    to->ack = (::DDS::Long)from->ack;
    to->error = (::DDS::Long)from->error;
    to->result = CORBA::string_dup(from->result);
}

void
__SALData_SALEvent__copyOut(
    void *_from,
    void *_to)
{
    struct _SALData_SALEvent *from = (struct _SALData_SALEvent *)_from;
    struct ::SALData::SALEvent *to = (struct ::SALData::SALEvent *)_to;
    to->private_revCode = CORBA::string_dup(from->private_revCode);
    to->private_sndStamp = (::DDS::Double)from->private_sndStamp;
    to->private_rcvStamp = (::DDS::Double)from->private_rcvStamp;
    to->private_origin = (::DDS::Long)from->private_origin;
    to->message = CORBA::string_dup(from->message);
}

