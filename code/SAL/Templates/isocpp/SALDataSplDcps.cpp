#include "SALDataSplDcps.h"
#include "SALData_DCPS.hpp"

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

