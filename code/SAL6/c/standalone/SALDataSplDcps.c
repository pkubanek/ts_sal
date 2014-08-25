#if defined (__cplusplus)
extern "C" {
#endif

#include "SALDataSplDcps.h"
#include "SALDataDcps.h"

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

/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 197 */
#include <v_kernel.h>
#include <v_topic.h>
#include <string.h>
#include <os_report.h>

/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 271 */
c_bool
__SALData_SALTopic__copyIn(c_base base, void *_from, void *_to)
{
    c_bool result = TRUE;

    SALData_SALTopic *from = (SALData_SALTopic *)_from;
    struct _SALData_SALTopic *to = (struct _SALData_SALTopic *)_to;
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 549 */
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 356 */
#ifdef OSPL_BOUNDS_CHECK
    if (from->private_revCode) {
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 361 */
        if (((unsigned int)strlen(from->private_revCode)) <= 32) {
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
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 549 */
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 350 */
    to->private_sndStamp = (c_double)from->private_sndStamp;
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 549 */
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 350 */
    to->private_rcvStamp = (c_double)from->private_rcvStamp;
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 549 */
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 350 */
    to->private_origin = (c_long)from->private_origin;
/* Code generated in file: /home/dds/OvernightTests/ExtraToday/ospli/tags/OSPL_V6_3_0-Commercial/ubuntu1204/x86.linux2.6-release-inner/build/src/tools/idlpp/code/idl_genCorbaCCopyin.c at line: 303 */
    return result;
}

#include <dds_dcps_private.h>

void
__SALData_SALTopic__copyOut(void *_from, void *_to)
{
    struct _SALData_SALTopic *from = (struct _SALData_SALTopic *)_from;
    SALData_SALTopic *to = (SALData_SALTopic *)_to;
    DDS_string_replace (from->private_revCode, &to->private_revCode);
    to->private_sndStamp = (DDS_double)from->private_sndStamp;
    to->private_rcvStamp = (DDS_double)from->private_rcvStamp;
    to->private_origin = (DDS_long)from->private_origin;
}

#include <dds_dcps_private.h>

SALData_SALTopic *SALData_SALTopic__alloc (void)
{
    DDS_boolean SALData_SALTopic__free (void *object);

    return (SALData_SALTopic *)DDS__malloc (SALData_SALTopic__free, 0, sizeof(SALData_SALTopic));
}

DDS_boolean SALData_SALTopic__free (void *object)
{
    SALData_SALTopic *o = (SALData_SALTopic *)object;

    DDS_string_clean (&o->private_revCode);
    return TRUE;
}

const char * SALData_SALTopic_metaDescriptor[] = {"<MetaData version=\"1.0.0\"><Module name=\"SALData\"><Struct name=\"SALTopic\"><Member name=\"private_revCode\">",
"<String length=\"32\"/></Member><Member name=\"private_sndStamp\"><Double/></Member><Member name=\"private_rcvStamp\">",
"<Double/></Member><Member name=\"private_origin\"><Long/></Member></Struct></Module></MetaData>"};
const c_ulong  SALData_SALTopic_metaDescriptorArrLength = 3;
#if defined (__cplusplus)
}
#endif
