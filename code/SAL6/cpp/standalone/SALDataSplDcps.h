#ifndef SALDATASPLTYPES_H
#define SALDATASPLTYPES_H

#include "ccpp_SALData.h"

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
extern  c_bool __SALData_SALTopic__copyIn(c_base base, struct SALData::SALTopic *from, struct _SALData_SALTopic *to);
extern  void __SALData_SALTopic__copyOut(void *_from, void *_to);
struct _SALData_SALTopic {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
};

extern c_metaObject __SALData_SALCommand__load (c_base base);
extern const char * __SALData_SALCommand__keys (void);
extern const char * __SALData_SALCommand__name (void);
struct _SALData_SALCommand ;
extern  c_bool __SALData_SALCommand__copyIn(c_base base, struct SALData::SALCommand *from, struct _SALData_SALCommand *to);
extern  void __SALData_SALCommand__copyOut(void *_from, void *_to);
struct _SALData_SALCommand {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
    c_long private_seqNum;
    c_string device;
    c_string property;
    c_string action;
    c_string value;
    c_string modifiers;
};

extern c_metaObject __SALData_SALResponse__load (c_base base);
extern const char * __SALData_SALResponse__keys (void);
extern const char * __SALData_SALResponse__name (void);
struct _SALData_SALResponse ;
extern  c_bool __SALData_SALResponse__copyIn(c_base base, struct SALData::SALResponse *from, struct _SALData_SALResponse *to);
extern  void __SALData_SALResponse__copyOut(void *_from, void *_to);
struct _SALData_SALResponse {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
    c_long private_seqNum;
    c_long ack;
    c_long error;
    c_string result;
};

extern c_metaObject __SALData_SALEvent__load (c_base base);
extern const char * __SALData_SALEvent__keys (void);
extern const char * __SALData_SALEvent__name (void);
struct _SALData_SALEvent ;
extern  c_bool __SALData_SALEvent__copyIn(c_base base, struct SALData::SALEvent *from, struct _SALData_SALEvent *to);
extern  void __SALData_SALEvent__copyOut(void *_from, void *_to);
struct _SALData_SALEvent {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
    c_string message;
};

#endif
