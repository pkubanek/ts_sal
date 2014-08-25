#include "SALTopicSplDcps.h"
#include "ccpp_SALTopic.h"

const char *
__org_lsst_sal_SALTopicType__name(void)
{
    return (const char*)"org::lsst::sal::SALTopicType";
}

const char *
__org_lsst_sal_SALTopicType__keys(void)
{
    return (const char*)"";
}

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

c_bool
__org_lsst_sal_SALTopicType__copyIn(
    c_base base,
    struct ::org::lsst::sal::SALTopicType *from,
    struct _org_lsst_sal_SALTopicType *to)
{
    c_bool result = TRUE;

#ifdef OSPL_BOUNDS_CHECK
    if(from->private_revCode){
        to->private_revCode = c_stringNew(base, from->private_revCode);
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'org::lsst::sal::SALTopicType.private_revCode' of type 'c_string' is out of range.");
        result = FALSE;
    }
#else
    to->private_revCode = c_stringNew(base, from->private_revCode);
#endif
    return result;
}

void
__org_lsst_sal_SALTopicType__copyOut(
    void *_from,
    void *_to)
{
    struct _org_lsst_sal_SALTopicType *from = (struct _org_lsst_sal_SALTopicType *)_from;
    struct ::org::lsst::sal::SALTopicType *to = (struct ::org::lsst::sal::SALTopicType *)_to;
    to->private_revCode = CORBA::string_dup(from->private_revCode);
}

