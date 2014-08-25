#ifndef SALDATASPLTYPES_H
#define SALDATASPLTYPES_H

#include "SALDataDcps.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __SALData_SALData__load (c_base base);

extern c_metaObject __SALData_SALTopic__load (c_base base);
extern const char * __SALData_SALTopic__keys (void);
extern const char * __SALData_SALTopic__name (void);
struct _SALData_SALTopic ;
extern  c_bool __SALData_SALTopic__copyIn(c_base base, void *from, void *to);
extern  void __SALData_SALTopic__copyOut(void *_from, void *_to);
struct _SALData_SALTopic {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
};

#endif
