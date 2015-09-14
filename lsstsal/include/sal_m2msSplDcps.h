#ifndef SAL_M2MSSPLTYPES_H
#define SAL_M2MSSPLTYPES_H

#include "ccpp_sal_m2ms.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __sal_m2ms_m2ms__load (c_base base);

extern c_metaObject __m2ms_Actuators__load (c_base base);
extern const char * __m2ms_Actuators__keys (void);
extern const char * __m2ms_Actuators__name (void);
struct _m2ms_Actuators ;
extern  c_bool __m2ms_Actuators__copyIn(c_base base, struct m2ms::Actuators *from, struct _m2ms_Actuators *to);
extern  void __m2ms_Actuators__copyOut(void *_from, void *_to);
struct _m2ms_Actuators {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[15];
    c_float Calibrated[31];
};

extern c_metaObject __m2ms_Application__load (c_base base);
extern const char * __m2ms_Application__keys (void);
extern const char * __m2ms_Application__name (void);
struct _m2ms_Application ;
extern  c_bool __m2ms_Application__copyIn(c_base base, struct m2ms::Application *from, struct _m2ms_Application *to);
extern  void __m2ms_Application__copyOut(void *_from, void *_to);
struct _m2ms_Application {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_float Demand[2];
    c_float Position[2];
    c_float Error[2];
};

extern c_metaObject __m2ms_Electrical__load (c_base base);
extern const char * __m2ms_Electrical__keys (void);
extern const char * __m2ms_Electrical__name (void);
struct _m2ms_Electrical ;
extern  c_bool __m2ms_Electrical__copyIn(c_base base, struct m2ms::Electrical *from, struct _m2ms_Electrical *to);
extern  void __m2ms_Electrical__copyOut(void *_from, void *_to);
struct _m2ms_Electrical {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long voltage[16];
    c_long error[16];
    c_short status[16];
};

extern c_metaObject __m2ms_LimitSensors__load (c_base base);
extern const char * __m2ms_LimitSensors__keys (void);
extern const char * __m2ms_LimitSensors__name (void);
struct _m2ms_LimitSensors ;
extern  c_bool __m2ms_LimitSensors__copyIn(c_base base, struct m2ms::LimitSensors *from, struct _m2ms_LimitSensors *to);
extern  void __m2ms_LimitSensors__copyOut(void *_from, void *_to);
struct _m2ms_LimitSensors {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_short liftoff[64];
    c_short limit[64];
};

extern c_metaObject __m2ms_Metrology__load (c_base base);
extern const char * __m2ms_Metrology__keys (void);
extern const char * __m2ms_Metrology__name (void);
struct _m2ms_Metrology ;
extern  c_bool __m2ms_Metrology__copyIn(c_base base, struct m2ms::Metrology *from, struct _m2ms_Metrology *to);
extern  void __m2ms_Metrology__copyOut(void *_from, void *_to);
struct _m2ms_Metrology {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long distance[16];
    c_long error[16];
    c_short status[16];
};

extern c_metaObject __m2ms_Surface__load (c_base base);
extern const char * __m2ms_Surface__keys (void);
extern const char * __m2ms_Surface__name (void);
struct _m2ms_Surface ;
extern  c_bool __m2ms_Surface__copyIn(c_base base, struct m2ms::Surface *from, struct _m2ms_Surface *to);
extern  void __m2ms_Surface__copyOut(void *_from, void *_to);
struct _m2ms_Surface {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[200];
    c_float Calibrated[200];
};

extern c_metaObject __m2ms_TC__load (c_base base);
extern const char * __m2ms_TC__keys (void);
extern const char * __m2ms_TC__name (void);
struct _m2ms_TC ;
extern  c_bool __m2ms_TC__copyIn(c_base base, struct m2ms::TC *from, struct _m2ms_TC *to);
extern  void __m2ms_TC__copyOut(void *_from, void *_to);
struct _m2ms_TC {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_float setpoint[16];
    c_float temperature[16];
    c_float error[16];
    c_short status[16];
};

extern c_metaObject __m2ms_command_abort__load (c_base base);
extern const char * __m2ms_command_abort__keys (void);
extern const char * __m2ms_command_abort__name (void);
struct _m2ms_command_abort ;
extern  c_bool __m2ms_command_abort__copyIn(c_base base, struct m2ms::command_abort *from, struct _m2ms_command_abort *to);
extern  void __m2ms_command_abort__copyOut(void *_from, void *_to);
struct _m2ms_command_abort {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_string device;
    c_string property;
    c_string action;
    c_string value;
};

extern c_metaObject __m2ms_command_configure__load (c_base base);
extern const char * __m2ms_command_configure__keys (void);
extern const char * __m2ms_command_configure__name (void);
struct _m2ms_command_configure ;
extern  c_bool __m2ms_command_configure__copyIn(c_base base, struct m2ms::command_configure *from, struct _m2ms_command_configure *to);
extern  void __m2ms_command_configure__copyOut(void *_from, void *_to);
struct _m2ms_command_configure {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_string device;
    c_string property;
    c_string action;
    c_string value;
    c_string spec_id;
};

extern c_metaObject __m2ms_command_status__load (c_base base);
extern const char * __m2ms_command_status__keys (void);
extern const char * __m2ms_command_status__name (void);
struct _m2ms_command_status ;
extern  c_bool __m2ms_command_status__copyIn(c_base base, struct m2ms::command_status *from, struct _m2ms_command_status *to);
extern  void __m2ms_command_status__copyOut(void *_from, void *_to);
struct _m2ms_command_status {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_string device;
    c_string property;
    c_string action;
    c_string value;
};

extern c_metaObject __m2ms_command_stop__load (c_base base);
extern const char * __m2ms_command_stop__keys (void);
extern const char * __m2ms_command_stop__name (void);
struct _m2ms_command_stop ;
extern  c_bool __m2ms_command_stop__copyIn(c_base base, struct m2ms::command_stop *from, struct _m2ms_command_stop *to);
extern  void __m2ms_command_stop__copyOut(void *_from, void *_to);
struct _m2ms_command_stop {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_string device;
    c_string property;
    c_string action;
    c_string value;
};

extern c_metaObject __m2ms_command_target__load (c_base base);
extern const char * __m2ms_command_target__keys (void);
extern const char * __m2ms_command_target__name (void);
struct _m2ms_command_target ;
extern  c_bool __m2ms_command_target__copyIn(c_base base, struct m2ms::command_target *from, struct _m2ms_command_target *to);
extern  void __m2ms_command_target__copyOut(void *_from, void *_to);
struct _m2ms_command_target {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_string device;
    c_string property;
    c_string action;
    c_string value;
    c_double azimuth;
    c_double elevation;
};

extern c_metaObject __m2ms_command_update__load (c_base base);
extern const char * __m2ms_command_update__keys (void);
extern const char * __m2ms_command_update__name (void);
struct _m2ms_command_update ;
extern  c_bool __m2ms_command_update__copyIn(c_base base, struct m2ms::command_update *from, struct _m2ms_command_update *to);
extern  void __m2ms_command_update__copyOut(void *_from, void *_to);
struct _m2ms_command_update {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_string device;
    c_string property;
    c_string action;
    c_string value;
    c_string lut_id;
};

extern c_metaObject __m2ms_logevent_interlock__load (c_base base);
extern const char * __m2ms_logevent_interlock__keys (void);
extern const char * __m2ms_logevent_interlock__name (void);
struct _m2ms_logevent_interlock ;
extern  c_bool __m2ms_logevent_interlock__copyIn(c_base base, struct m2ms::logevent_interlock *from, struct _m2ms_logevent_interlock *to);
extern  void __m2ms_logevent_interlock__copyOut(void *_from, void *_to);
struct _m2ms_logevent_interlock {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string detail;
};

extern c_metaObject __m2ms_logevent_limitError__load (c_base base);
extern const char * __m2ms_logevent_limitError__keys (void);
extern const char * __m2ms_logevent_limitError__name (void);
struct _m2ms_logevent_limitError ;
extern  c_bool __m2ms_logevent_limitError__copyIn(c_base base, struct m2ms::logevent_limitError *from, struct _m2ms_logevent_limitError *to);
extern  void __m2ms_logevent_limitError__copyOut(void *_from, void *_to);
struct _m2ms_logevent_limitError {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string limit;
    c_string type;
};

extern c_metaObject __m2ms_logevent_targetDone__load (c_base base);
extern const char * __m2ms_logevent_targetDone__keys (void);
extern const char * __m2ms_logevent_targetDone__name (void);
struct _m2ms_logevent_targetDone ;
extern  c_bool __m2ms_logevent_targetDone__copyIn(c_base base, struct m2ms::logevent_targetDone *from, struct _m2ms_logevent_targetDone *to);
extern  void __m2ms_logevent_targetDone__copyOut(void *_from, void *_to);
struct _m2ms_logevent_targetDone {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __m2ms_logevent_targetError__load (c_base base);
extern const char * __m2ms_logevent_targetError__keys (void);
extern const char * __m2ms_logevent_targetError__name (void);
struct _m2ms_logevent_targetError ;
extern  c_bool __m2ms_logevent_targetError__copyIn(c_base base, struct m2ms::logevent_targetError *from, struct _m2ms_logevent_targetError *to);
extern  void __m2ms_logevent_targetError__copyOut(void *_from, void *_to);
struct _m2ms_logevent_targetError {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __m2ms_logevent_tempError__load (c_base base);
extern const char * __m2ms_logevent_tempError__keys (void);
extern const char * __m2ms_logevent_tempError__name (void);
struct _m2ms_logevent_tempError ;
extern  c_bool __m2ms_logevent_tempError__copyIn(c_base base, struct m2ms::logevent_tempError *from, struct _m2ms_logevent_tempError *to);
extern  void __m2ms_logevent_tempError__copyOut(void *_from, void *_to);
struct _m2ms_logevent_tempError {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string device;
    c_long severity;
    c_double temp;
};

extern c_metaObject __m2ms_logevent_updateDone__load (c_base base);
extern const char * __m2ms_logevent_updateDone__keys (void);
extern const char * __m2ms_logevent_updateDone__name (void);
struct _m2ms_logevent_updateDone ;
extern  c_bool __m2ms_logevent_updateDone__copyIn(c_base base, struct m2ms::logevent_updateDone *from, struct _m2ms_logevent_updateDone *to);
extern  void __m2ms_logevent_updateDone__copyOut(void *_from, void *_to);
struct _m2ms_logevent_updateDone {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __m2ms_logevent_updateError__load (c_base base);
extern const char * __m2ms_logevent_updateError__keys (void);
extern const char * __m2ms_logevent_updateError__name (void);
struct _m2ms_logevent_updateError ;
extern  c_bool __m2ms_logevent_updateError__copyIn(c_base base, struct m2ms::logevent_updateError *from, struct _m2ms_logevent_updateError *to);
extern  void __m2ms_logevent_updateError__copyOut(void *_from, void *_to);
struct _m2ms_logevent_updateError {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __m2ms_command__load (c_base base);
extern const char * __m2ms_command__keys (void);
extern const char * __m2ms_command__name (void);
struct _m2ms_command ;
extern  c_bool __m2ms_command__copyIn(c_base base, struct m2ms::command *from, struct _m2ms_command *to);
extern  void __m2ms_command__copyOut(void *_from, void *_to);
struct _m2ms_command {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
    c_long private_host;
    c_long private_seqNum;
    c_string device;
    c_string property;
    c_string action;
    c_string value;
    c_string modifiers;
};

extern c_metaObject __m2ms_ackcmd__load (c_base base);
extern const char * __m2ms_ackcmd__keys (void);
extern const char * __m2ms_ackcmd__name (void);
struct _m2ms_ackcmd ;
extern  c_bool __m2ms_ackcmd__copyIn(c_base base, struct m2ms::ackcmd *from, struct _m2ms_ackcmd *to);
extern  void __m2ms_ackcmd__copyOut(void *_from, void *_to);
struct _m2ms_ackcmd {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
    c_long private_host;
    c_long private_seqNum;
    c_long ack;
    c_long error;
    c_string result;
};

extern c_metaObject __m2ms_logevent__load (c_base base);
extern const char * __m2ms_logevent__keys (void);
extern const char * __m2ms_logevent__name (void);
struct _m2ms_logevent ;
extern  c_bool __m2ms_logevent__copyIn(c_base base, struct m2ms::logevent *from, struct _m2ms_logevent *to);
extern  void __m2ms_logevent__copyOut(void *_from, void *_to);
struct _m2ms_logevent {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
    c_long private_host;
    c_string message;
};

#endif
