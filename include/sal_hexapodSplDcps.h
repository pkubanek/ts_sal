#ifndef SAL_HEXAPODSPLTYPES_H
#define SAL_HEXAPODSPLTYPES_H

#include "ccpp_sal_hexapod.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __sal_hexapod_hexapod__load (c_base base);

extern c_metaObject __hexapod_Actuators__load (c_base base);
extern const char * __hexapod_Actuators__keys (void);
extern const char * __hexapod_Actuators__name (void);
struct _hexapod_Actuators ;
extern  c_bool __hexapod_Actuators__copyIn(c_base base, struct hexapod::Actuators *from, struct _hexapod_Actuators *to);
extern  void __hexapod_Actuators__copyOut(void *_from, void *_to);
struct _hexapod_Actuators {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[18];
    c_float Calibrated[18];
};

extern c_metaObject __hexapod_Application__load (c_base base);
extern const char * __hexapod_Application__keys (void);
extern const char * __hexapod_Application__name (void);
struct _hexapod_Application ;
extern  c_bool __hexapod_Application__copyIn(c_base base, struct hexapod::Application *from, struct _hexapod_Application *to);
extern  void __hexapod_Application__copyOut(void *_from, void *_to);
struct _hexapod_Application {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_float Demand[6];
    c_float Position[6];
    c_float Error[6];
};

extern c_metaObject __hexapod_Electrical__load (c_base base);
extern const char * __hexapod_Electrical__keys (void);
extern const char * __hexapod_Electrical__name (void);
struct _hexapod_Electrical ;
extern  c_bool __hexapod_Electrical__copyIn(c_base base, struct hexapod::Electrical *from, struct _hexapod_Electrical *to);
extern  void __hexapod_Electrical__copyOut(void *_from, void *_to);
struct _hexapod_Electrical {
    c_short hexapodID;
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

extern c_metaObject __hexapod_LimitSensors__load (c_base base);
extern const char * __hexapod_LimitSensors__keys (void);
extern const char * __hexapod_LimitSensors__name (void);
struct _hexapod_LimitSensors ;
extern  c_bool __hexapod_LimitSensors__copyIn(c_base base, struct hexapod::LimitSensors *from, struct _hexapod_LimitSensors *to);
extern  void __hexapod_LimitSensors__copyOut(void *_from, void *_to);
struct _hexapod_LimitSensors {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_short liftoff[18];
    c_short limit[18];
};

extern c_metaObject __hexapod_Metrology__load (c_base base);
extern const char * __hexapod_Metrology__keys (void);
extern const char * __hexapod_Metrology__name (void);
struct _hexapod_Metrology ;
extern  c_bool __hexapod_Metrology__copyIn(c_base base, struct hexapod::Metrology *from, struct _hexapod_Metrology *to);
extern  void __hexapod_Metrology__copyOut(void *_from, void *_to);
struct _hexapod_Metrology {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long distance[18];
    c_long error[18];
    c_short status[18];
};

extern c_metaObject __hexapod_TC__load (c_base base);
extern const char * __hexapod_TC__keys (void);
extern const char * __hexapod_TC__name (void);
struct _hexapod_TC ;
extern  c_bool __hexapod_TC__copyIn(c_base base, struct hexapod::TC *from, struct _hexapod_TC *to);
extern  void __hexapod_TC__copyOut(void *_from, void *_to);
struct _hexapod_TC {
    c_short hexapodID;
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

extern c_metaObject __hexapod_command_configureAcceleration__load (c_base base);
extern const char * __hexapod_command_configureAcceleration__keys (void);
extern const char * __hexapod_command_configureAcceleration__name (void);
struct _hexapod_command_configureAcceleration ;
extern  c_bool __hexapod_command_configureAcceleration__copyIn(c_base base, struct hexapod::command_configureAcceleration *from, struct _hexapod_command_configureAcceleration *to);
extern  void __hexapod_command_configureAcceleration__copyOut(void *_from, void *_to);
struct _hexapod_command_configureAcceleration {
    c_short hexapodID;
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
    c_double xmin;
    c_double xmax;
    c_double ymin;
    c_double ymax;
    c_double zmin;
    c_double zmax;
    c_double umin;
    c_double umax;
    c_double vmin;
    c_double vmax;
    c_double wmin;
    c_double wmax;
};

extern c_metaObject __hexapod_command_configureLimits__load (c_base base);
extern const char * __hexapod_command_configureLimits__keys (void);
extern const char * __hexapod_command_configureLimits__name (void);
struct _hexapod_command_configureLimits ;
extern  c_bool __hexapod_command_configureLimits__copyIn(c_base base, struct hexapod::command_configureLimits *from, struct _hexapod_command_configureLimits *to);
extern  void __hexapod_command_configureLimits__copyOut(void *_from, void *_to);
struct _hexapod_command_configureLimits {
    c_short hexapodID;
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
    c_long xmin;
    c_long xmax;
    c_long ymin;
    c_long ymax;
    c_long zmin;
    c_long zmax;
    c_long umin;
    c_long umax;
    c_long vmin;
    c_long vmax;
    c_long wmin;
    c_long wmax;
};

extern c_metaObject __hexapod_command_configureLut__load (c_base base);
extern const char * __hexapod_command_configureLut__keys (void);
extern const char * __hexapod_command_configureLut__name (void);
struct _hexapod_command_configureLut ;
extern  c_bool __hexapod_command_configureLut__copyIn(c_base base, struct hexapod::command_configureLut *from, struct _hexapod_command_configureLut *to);
extern  void __hexapod_command_configureLut__copyOut(void *_from, void *_to);
struct _hexapod_command_configureLut {
    c_short hexapodID;
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
    c_double xlut[90];
    c_double ylut[90];
    c_double zlut[90];
    c_double ulut[90];
    c_double vlut[90];
    c_double wlut[90];
};

extern c_metaObject __hexapod_command_configurePosition__load (c_base base);
extern const char * __hexapod_command_configurePosition__keys (void);
extern const char * __hexapod_command_configurePosition__name (void);
struct _hexapod_command_configurePosition ;
extern  c_bool __hexapod_command_configurePosition__copyIn(c_base base, struct hexapod::command_configurePosition *from, struct _hexapod_command_configurePosition *to);
extern  void __hexapod_command_configurePosition__copyOut(void *_from, void *_to);
struct _hexapod_command_configurePosition {
    c_short hexapodID;
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
    c_double x;
    c_double y;
    c_double z;
    c_double u;
    c_double v;
    c_double w;
    c_bool sync;
};

extern c_metaObject __hexapod_command_configureVelocity__load (c_base base);
extern const char * __hexapod_command_configureVelocity__keys (void);
extern const char * __hexapod_command_configureVelocity__name (void);
struct _hexapod_command_configureVelocity ;
extern  c_bool __hexapod_command_configureVelocity__copyIn(c_base base, struct hexapod::command_configureVelocity *from, struct _hexapod_command_configureVelocity *to);
extern  void __hexapod_command_configureVelocity__copyOut(void *_from, void *_to);
struct _hexapod_command_configureVelocity {
    c_short hexapodID;
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
    c_double xmin;
    c_double xmax;
    c_double ymin;
    c_double ymax;
    c_double zmin;
    c_double zmax;
    c_double umin;
    c_double umax;
    c_double vmin;
    c_double vmax;
    c_double wmin;
    c_double wmax;
};

extern c_metaObject __hexapod_command_move__load (c_base base);
extern const char * __hexapod_command_move__keys (void);
extern const char * __hexapod_command_move__name (void);
struct _hexapod_command_move ;
extern  c_bool __hexapod_command_move__copyIn(c_base base, struct hexapod::command_move *from, struct _hexapod_command_move *to);
extern  void __hexapod_command_move__copyOut(void *_from, void *_to);
struct _hexapod_command_move {
    c_short hexapodID;
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
    c_double angle;
};

extern c_metaObject __hexapod_command_offset__load (c_base base);
extern const char * __hexapod_command_offset__keys (void);
extern const char * __hexapod_command_offset__name (void);
struct _hexapod_command_offset ;
extern  c_bool __hexapod_command_offset__copyIn(c_base base, struct hexapod::command_offset *from, struct _hexapod_command_offset *to);
extern  void __hexapod_command_offset__copyOut(void *_from, void *_to);
struct _hexapod_command_offset {
    c_short hexapodID;
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
    c_double x;
    c_double y;
    c_double z;
    c_double u;
    c_double v;
    c_double w;
    c_bool sync;
};

extern c_metaObject __hexapod_command_pivot__load (c_base base);
extern const char * __hexapod_command_pivot__keys (void);
extern const char * __hexapod_command_pivot__name (void);
struct _hexapod_command_pivot ;
extern  c_bool __hexapod_command_pivot__copyIn(c_base base, struct hexapod::command_pivot *from, struct _hexapod_command_pivot *to);
extern  void __hexapod_command_pivot__copyOut(void *_from, void *_to);
struct _hexapod_command_pivot {
    c_short hexapodID;
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
    c_double x;
    c_double y;
    c_double z;
};

extern c_metaObject __hexapod_command_stop__load (c_base base);
extern const char * __hexapod_command_stop__keys (void);
extern const char * __hexapod_command_stop__name (void);
struct _hexapod_command_stop ;
extern  c_bool __hexapod_command_stop__copyIn(c_base base, struct hexapod::command_stop *from, struct _hexapod_command_stop *to);
extern  void __hexapod_command_stop__copyOut(void *_from, void *_to);
struct _hexapod_command_stop {
    c_short hexapodID;
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

extern c_metaObject __hexapod_command_test__load (c_base base);
extern const char * __hexapod_command_test__keys (void);
extern const char * __hexapod_command_test__name (void);
struct _hexapod_command_test ;
extern  c_bool __hexapod_command_test__copyIn(c_base base, struct hexapod::command_test *from, struct _hexapod_command_test *to);
extern  void __hexapod_command_test__copyOut(void *_from, void *_to);
struct _hexapod_command_test {
    c_short hexapodID;
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

extern c_metaObject __hexapod_logevent_error__load (c_base base);
extern const char * __hexapod_logevent_error__keys (void);
extern const char * __hexapod_logevent_error__name (void);
struct _hexapod_logevent_error ;
extern  c_bool __hexapod_logevent_error__copyIn(c_base base, struct hexapod::logevent_error *from, struct _hexapod_logevent_error *to);
extern  void __hexapod_logevent_error__copyOut(void *_from, void *_to);
struct _hexapod_logevent_error {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __hexapod_logevent_interlock__load (c_base base);
extern const char * __hexapod_logevent_interlock__keys (void);
extern const char * __hexapod_logevent_interlock__name (void);
struct _hexapod_logevent_interlock ;
extern  c_bool __hexapod_logevent_interlock__copyIn(c_base base, struct hexapod::logevent_interlock *from, struct _hexapod_logevent_interlock *to);
extern  void __hexapod_logevent_interlock__copyOut(void *_from, void *_to);
struct _hexapod_logevent_interlock {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string detail;
};

extern c_metaObject __hexapod_logevent_limit__load (c_base base);
extern const char * __hexapod_logevent_limit__keys (void);
extern const char * __hexapod_logevent_limit__name (void);
struct _hexapod_logevent_limit ;
extern  c_bool __hexapod_logevent_limit__copyIn(c_base base, struct hexapod::logevent_limit *from, struct _hexapod_logevent_limit *to);
extern  void __hexapod_logevent_limit__copyOut(void *_from, void *_to);
struct _hexapod_logevent_limit {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string axis;
    c_string limit;
    c_string type;
};

extern c_metaObject __hexapod_logevent_slewOK__load (c_base base);
extern const char * __hexapod_logevent_slewOK__keys (void);
extern const char * __hexapod_logevent_slewOK__name (void);
struct _hexapod_logevent_slewOK ;
extern  c_bool __hexapod_logevent_slewOK__copyIn(c_base base, struct hexapod::logevent_slewOK *from, struct _hexapod_logevent_slewOK *to);
extern  void __hexapod_logevent_slewOK__copyOut(void *_from, void *_to);
struct _hexapod_logevent_slewOK {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __hexapod_logevent_temp__load (c_base base);
extern const char * __hexapod_logevent_temp__keys (void);
extern const char * __hexapod_logevent_temp__name (void);
struct _hexapod_logevent_temp ;
extern  c_bool __hexapod_logevent_temp__copyIn(c_base base, struct hexapod::logevent_temp *from, struct _hexapod_logevent_temp *to);
extern  void __hexapod_logevent_temp__copyOut(void *_from, void *_to);
struct _hexapod_logevent_temp {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string axis;
    c_string device;
    c_long severity;
};

extern c_metaObject __hexapod_logevent_trackLost__load (c_base base);
extern const char * __hexapod_logevent_trackLost__keys (void);
extern const char * __hexapod_logevent_trackLost__name (void);
struct _hexapod_logevent_trackLost ;
extern  c_bool __hexapod_logevent_trackLost__copyIn(c_base base, struct hexapod::logevent_trackLost *from, struct _hexapod_logevent_trackLost *to);
extern  void __hexapod_logevent_trackLost__copyOut(void *_from, void *_to);
struct _hexapod_logevent_trackLost {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __hexapod_logevent_tracking__load (c_base base);
extern const char * __hexapod_logevent_tracking__keys (void);
extern const char * __hexapod_logevent_tracking__name (void);
struct _hexapod_logevent_tracking ;
extern  c_bool __hexapod_logevent_tracking__copyIn(c_base base, struct hexapod::logevent_tracking *from, struct _hexapod_logevent_tracking *to);
extern  void __hexapod_logevent_tracking__copyOut(void *_from, void *_to);
struct _hexapod_logevent_tracking {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __hexapod_command__load (c_base base);
extern const char * __hexapod_command__keys (void);
extern const char * __hexapod_command__name (void);
struct _hexapod_command ;
extern  c_bool __hexapod_command__copyIn(c_base base, struct hexapod::command *from, struct _hexapod_command *to);
extern  void __hexapod_command__copyOut(void *_from, void *_to);
struct _hexapod_command {
    c_short hexapodID;
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

extern c_metaObject __hexapod_ackcmd__load (c_base base);
extern const char * __hexapod_ackcmd__keys (void);
extern const char * __hexapod_ackcmd__name (void);
struct _hexapod_ackcmd ;
extern  c_bool __hexapod_ackcmd__copyIn(c_base base, struct hexapod::ackcmd *from, struct _hexapod_ackcmd *to);
extern  void __hexapod_ackcmd__copyOut(void *_from, void *_to);
struct _hexapod_ackcmd {
    c_short hexapodID;
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

extern c_metaObject __hexapod_logevent__load (c_base base);
extern const char * __hexapod_logevent__keys (void);
extern const char * __hexapod_logevent__name (void);
struct _hexapod_logevent ;
extern  c_bool __hexapod_logevent__copyIn(c_base base, struct hexapod::logevent *from, struct _hexapod_logevent *to);
extern  void __hexapod_logevent__copyOut(void *_from, void *_to);
struct _hexapod_logevent {
    c_short hexapodID;
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
    c_long private_host;
    c_string message;
};

#endif
