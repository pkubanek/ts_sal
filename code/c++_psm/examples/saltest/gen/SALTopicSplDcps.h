#ifndef SALTOPICSPLTYPES_H
#define SALTOPICSPLTYPES_H

#include "ccpp_SALTopic.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __SALTopic_org__load (c_base base);

extern c_metaObject __SALTopic_org_lsst__load (c_base base);

extern c_metaObject __SALTopic_org_lsst_sal__load (c_base base);

extern c_metaObject __org_lsst_sal_SALTopicType__load (c_base base);
extern const char * __org_lsst_sal_SALTopicType__keys (void);
extern const char * __org_lsst_sal_SALTopicType__name (void);
struct _org_lsst_sal_SALTopicType ;
extern  c_bool __org_lsst_sal_SALTopicType__copyIn(c_base base, struct org::lsst::sal::SALTopicType *from, struct _org_lsst_sal_SALTopicType *to);
extern  void __org_lsst_sal_SALTopicType__copyOut(void *_from, void *_to);
struct _org_lsst_sal_SALTopicType {
    c_string private_revCode;
};

#endif
