#ifndef SALDATADCPS_H
#define SALDATADCPS_H

#include <dds_dcps.h>


#ifndef _SALData_SALTopic_defined
#define _SALData_SALTopic_defined
#ifdef __cplusplus
struct SALData_SALTopic;
#else /* __cplusplus */
typedef struct SALData_SALTopic SALData_SALTopic;
#endif /* __cplusplus */
#endif /* _SALData_SALTopic_defined */
 SALData_SALTopic *SALData_SALTopic__alloc (void);

struct SALData_SALTopic {
    DDS_string private_revCode;
    DDS_double private_sndStamp;
    DDS_double private_rcvStamp;
    DDS_long private_origin;
};

#endif
