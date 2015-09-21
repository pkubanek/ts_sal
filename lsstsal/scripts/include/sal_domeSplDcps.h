#ifndef SAL_DOMESPLTYPES_H
#define SAL_DOMESPLTYPES_H

#include "ccpp_sal_dome.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __sal_dome_dome__load (c_base base);

extern c_metaObject __dome_Application__load (c_base base);
extern const char * __dome_Application__keys (void);
extern const char * __dome_Application__name (void);
struct _dome_Application ;
extern  c_bool __dome_Application__copyIn(c_base base, struct dome::Application *from, struct _dome_Application *to);
extern  void __dome_Application__copyOut(void *_from, void *_to);
struct _dome_Application {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_float azTarget;
    c_float azPosition;
    c_float azError;
    c_float elevTarget;
    c_float elevPosition;
    c_float elevError;
    c_float scrTarget;
    c_float scrPosition;
    c_float scrError;
    c_float lvTarget[72];
    c_float lvPosition[72];
    c_float lvError[72];
};

extern c_metaObject __dome_Azimuth__load (c_base base);
extern const char * __dome_Azimuth__keys (void);
extern const char * __dome_Azimuth__name (void);
struct _dome_Azimuth ;
extern  c_bool __dome_Azimuth__copyIn(c_base base, struct dome::Azimuth *from, struct _dome_Azimuth *to);
extern  void __dome_Azimuth__copyOut(void *_from, void *_to);
struct _dome_Azimuth {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[16];
};

extern c_metaObject __dome_Bogies__load (c_base base);
extern const char * __dome_Bogies__keys (void);
extern const char * __dome_Bogies__name (void);
struct _dome_Bogies ;
extern  c_bool __dome_Bogies__copyIn(c_base base, struct dome::Bogies *from, struct _dome_Bogies *to);
extern  void __dome_Bogies__copyOut(void *_from, void *_to);
struct _dome_Bogies {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_float torqueTarget[12];
    c_float torqueMeasured[12];
    c_float currentTarget[12];
    c_float currentMeasured[12];
    c_float rpmTarget[12];
    c_float rpmMeasured[12];
    c_float temperature[12];
    c_long status[12];
};

extern c_metaObject __dome_CapacitorBank__load (c_base base);
extern const char * __dome_CapacitorBank__keys (void);
extern const char * __dome_CapacitorBank__name (void);
struct _dome_CapacitorBank ;
extern  c_bool __dome_CapacitorBank__copyIn(c_base base, struct dome::CapacitorBank *from, struct _dome_CapacitorBank *to);
extern  void __dome_CapacitorBank__copyOut(void *_from, void *_to);
struct _dome_CapacitorBank {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_float setpoint;
    c_float temperature[10];
    c_float charge[10];
    c_float chargeRate[10];
    c_long status[10];
};

extern c_metaObject __dome_Electrical__load (c_base base);
extern const char * __dome_Electrical__keys (void);
extern const char * __dome_Electrical__name (void);
struct _dome_Electrical ;
extern  c_bool __dome_Electrical__copyIn(c_base base, struct dome::Electrical *from, struct _dome_Electrical *to);
extern  void __dome_Electrical__copyOut(void *_from, void *_to);
struct _dome_Electrical {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[32];
};

extern c_metaObject __dome_Louvers__load (c_base base);
extern const char * __dome_Louvers__keys (void);
extern const char * __dome_Louvers__name (void);
struct _dome_Louvers ;
extern  c_bool __dome_Louvers__copyIn(c_base base, struct dome::Louvers *from, struct _dome_Louvers *to);
extern  void __dome_Louvers__copyOut(void *_from, void *_to);
struct _dome_Louvers {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long raw[72];
    c_float calibrated[72];
    c_float temperature[72];
    c_float windSpeed[72];
};

extern c_metaObject __dome_Metrology__load (c_base base);
extern const char * __dome_Metrology__keys (void);
extern const char * __dome_Metrology__name (void);
struct _dome_Metrology ;
extern  c_bool __dome_Metrology__copyIn(c_base base, struct dome::Metrology *from, struct _dome_Metrology *to);
extern  void __dome_Metrology__copyOut(void *_from, void *_to);
struct _dome_Metrology {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long azEncoder[4];
    c_float azCalibrated[4];
    c_long elevEncoder[4];
    c_float elevCalibrated[4];
    c_long screenEncoder[4];
    c_long shutterL[4];
    c_long shutterR[4];
};

extern c_metaObject __dome_Screen__load (c_base base);
extern const char * __dome_Screen__keys (void);
extern const char * __dome_Screen__name (void);
struct _dome_Screen ;
extern  c_bool __dome_Screen__copyIn(c_base base, struct dome::Screen *from, struct _dome_Screen *to);
extern  void __dome_Screen__copyOut(void *_from, void *_to);
struct _dome_Screen {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[16];
};

extern c_metaObject __dome_Shutter__load (c_base base);
extern const char * __dome_Shutter__keys (void);
extern const char * __dome_Shutter__name (void);
struct _dome_Shutter ;
extern  c_bool __dome_Shutter__copyIn(c_base base, struct dome::Shutter *from, struct _dome_Shutter *to);
extern  void __dome_Shutter__copyOut(void *_from, void *_to);
struct _dome_Shutter {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[16];
};

extern c_metaObject __dome_TC__load (c_base base);
extern const char * __dome_TC__keys (void);
extern const char * __dome_TC__name (void);
struct _dome_TC ;
extern  c_bool __dome_TC__copyIn(c_base base, struct dome::TC *from, struct _dome_TC *to);
extern  void __dome_TC__copyOut(void *_from, void *_to);
struct _dome_TC {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long raw[16];
    c_float calibrated[16];
    c_float setPoint[16];
    c_long status[16];
    c_float glycolFlow[4];
    c_float glycolTemperature[4];
    c_float boosterSpeed[4];
};

extern c_metaObject __dome_command_closeShutter__load (c_base base);
extern const char * __dome_command_closeShutter__keys (void);
extern const char * __dome_command_closeShutter__name (void);
struct _dome_command_closeShutter ;
extern  c_bool __dome_command_closeShutter__copyIn(c_base base, struct dome::command_closeShutter *from, struct _dome_command_closeShutter *to);
extern  void __dome_command_closeShutter__copyOut(void *_from, void *_to);
struct _dome_command_closeShutter {
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

extern c_metaObject __dome_command_louvers__load (c_base base);
extern const char * __dome_command_louvers__keys (void);
extern const char * __dome_command_louvers__name (void);
struct _dome_command_louvers ;
extern  c_bool __dome_command_louvers__copyIn(c_base base, struct dome::command_louvers *from, struct _dome_command_louvers *to);
extern  void __dome_command_louvers__copyOut(void *_from, void *_to);
struct _dome_command_louvers {
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
    c_double angle[72];
};

extern c_metaObject __dome_command_movetoCal__load (c_base base);
extern const char * __dome_command_movetoCal__keys (void);
extern const char * __dome_command_movetoCal__name (void);
struct _dome_command_movetoCal ;
extern  c_bool __dome_command_movetoCal__copyIn(c_base base, struct dome::command_movetoCal *from, struct _dome_command_movetoCal *to);
extern  void __dome_command_movetoCal__copyOut(void *_from, void *_to);
struct _dome_command_movetoCal {
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

extern c_metaObject __dome_command_openShutter__load (c_base base);
extern const char * __dome_command_openShutter__keys (void);
extern const char * __dome_command_openShutter__name (void);
struct _dome_command_openShutter ;
extern  c_bool __dome_command_openShutter__copyIn(c_base base, struct dome::command_openShutter *from, struct _dome_command_openShutter *to);
extern  void __dome_command_openShutter__copyOut(void *_from, void *_to);
struct _dome_command_openShutter {
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

extern c_metaObject __dome_command_park__load (c_base base);
extern const char * __dome_command_park__keys (void);
extern const char * __dome_command_park__name (void);
struct _dome_command_park ;
extern  c_bool __dome_command_park__copyIn(c_base base, struct dome::command_park *from, struct _dome_command_park *to);
extern  void __dome_command_park__copyOut(void *_from, void *_to);
struct _dome_command_park {
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

extern c_metaObject __dome_command_target__load (c_base base);
extern const char * __dome_command_target__keys (void);
extern const char * __dome_command_target__name (void);
struct _dome_command_target ;
extern  c_bool __dome_command_target__copyIn(c_base base, struct dome::command_target *from, struct _dome_command_target *to);
extern  void __dome_command_target__copyOut(void *_from, void *_to);
struct _dome_command_target {
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
    c_string azimuth;
    c_string elevation;
};

extern c_metaObject __dome_command_test__load (c_base base);
extern const char * __dome_command_test__keys (void);
extern const char * __dome_command_test__name (void);
struct _dome_command_test ;
extern  c_bool __dome_command_test__copyIn(c_base base, struct dome::command_test *from, struct _dome_command_test *to);
extern  void __dome_command_test__copyOut(void *_from, void *_to);
struct _dome_command_test {
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

extern c_metaObject __dome_command_track__load (c_base base);
extern const char * __dome_command_track__keys (void);
extern const char * __dome_command_track__name (void);
struct _dome_command_track ;
extern  c_bool __dome_command_track__copyIn(c_base base, struct dome::command_track *from, struct _dome_command_track *to);
extern  void __dome_command_track__copyOut(void *_from, void *_to);
struct _dome_command_track {
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

extern c_metaObject __dome_logevent_AccLimit__load (c_base base);
extern const char * __dome_logevent_AccLimit__keys (void);
extern const char * __dome_logevent_AccLimit__name (void);
struct _dome_logevent_AccLimit ;
extern  c_bool __dome_logevent_AccLimit__copyIn(c_base base, struct dome::logevent_AccLimit *from, struct _dome_logevent_AccLimit *to);
extern  void __dome_logevent_AccLimit__copyOut(void *_from, void *_to);
struct _dome_logevent_AccLimit {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_VelLimit__load (c_base base);
extern const char * __dome_logevent_VelLimit__keys (void);
extern const char * __dome_logevent_VelLimit__name (void);
struct _dome_logevent_VelLimit ;
extern  c_bool __dome_logevent_VelLimit__copyIn(c_base base, struct dome::logevent_VelLimit *from, struct _dome_logevent_VelLimit *to);
extern  void __dome_logevent_VelLimit__copyOut(void *_from, void *_to);
struct _dome_logevent_VelLimit {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_crawlLost__load (c_base base);
extern const char * __dome_logevent_crawlLost__keys (void);
extern const char * __dome_logevent_crawlLost__name (void);
struct _dome_logevent_crawlLost ;
extern  c_bool __dome_logevent_crawlLost__copyIn(c_base base, struct dome::logevent_crawlLost *from, struct _dome_logevent_crawlLost *to);
extern  void __dome_logevent_crawlLost__copyOut(void *_from, void *_to);
struct _dome_logevent_crawlLost {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_crawling__load (c_base base);
extern const char * __dome_logevent_crawling__keys (void);
extern const char * __dome_logevent_crawling__name (void);
struct _dome_logevent_crawling ;
extern  c_bool __dome_logevent_crawling__copyIn(c_base base, struct dome::logevent_crawling *from, struct _dome_logevent_crawling *to);
extern  void __dome_logevent_crawling__copyOut(void *_from, void *_to);
struct _dome_logevent_crawling {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_interlock__load (c_base base);
extern const char * __dome_logevent_interlock__keys (void);
extern const char * __dome_logevent_interlock__name (void);
struct _dome_logevent_interlock ;
extern  c_bool __dome_logevent_interlock__copyIn(c_base base, struct dome::logevent_interlock *from, struct _dome_logevent_interlock *to);
extern  void __dome_logevent_interlock__copyOut(void *_from, void *_to);
struct _dome_logevent_interlock {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string detail;
};

extern c_metaObject __dome_logevent_jerkLimit__load (c_base base);
extern const char * __dome_logevent_jerkLimit__keys (void);
extern const char * __dome_logevent_jerkLimit__name (void);
struct _dome_logevent_jerkLimit ;
extern  c_bool __dome_logevent_jerkLimit__copyIn(c_base base, struct dome::logevent_jerkLimit *from, struct _dome_logevent_jerkLimit *to);
extern  void __dome_logevent_jerkLimit__copyOut(void *_from, void *_to);
struct _dome_logevent_jerkLimit {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_lldvError__load (c_base base);
extern const char * __dome_logevent_lldvError__keys (void);
extern const char * __dome_logevent_lldvError__name (void);
struct _dome_logevent_lldvError ;
extern  c_bool __dome_logevent_lldvError__copyIn(c_base base, struct dome::logevent_lldvError *from, struct _dome_logevent_lldvError *to);
extern  void __dome_logevent_lldvError__copyOut(void *_from, void *_to);
struct _dome_logevent_lldvError {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_lldvOK__load (c_base base);
extern const char * __dome_logevent_lldvOK__keys (void);
extern const char * __dome_logevent_lldvOK__name (void);
struct _dome_logevent_lldvOK ;
extern  c_bool __dome_logevent_lldvOK__copyIn(c_base base, struct dome::logevent_lldvOK *from, struct _dome_logevent_lldvOK *to);
extern  void __dome_logevent_lldvOK__copyOut(void *_from, void *_to);
struct _dome_logevent_lldvOK {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_posLimit__load (c_base base);
extern const char * __dome_logevent_posLimit__keys (void);
extern const char * __dome_logevent_posLimit__name (void);
struct _dome_logevent_posLimit ;
extern  c_bool __dome_logevent_posLimit__copyIn(c_base base, struct dome::logevent_posLimit *from, struct _dome_logevent_posLimit *to);
extern  void __dome_logevent_posLimit__copyOut(void *_from, void *_to);
struct _dome_logevent_posLimit {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string device;
    c_string limit;
    c_string type;
};

extern c_metaObject __dome_logevent_powerError__load (c_base base);
extern const char * __dome_logevent_powerError__keys (void);
extern const char * __dome_logevent_powerError__name (void);
struct _dome_logevent_powerError ;
extern  c_bool __dome_logevent_powerError__copyIn(c_base base, struct dome::logevent_powerError *from, struct _dome_logevent_powerError *to);
extern  void __dome_logevent_powerError__copyOut(void *_from, void *_to);
struct _dome_logevent_powerError {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string device;
    c_long severity;
};

extern c_metaObject __dome_logevent_screenLimit__load (c_base base);
extern const char * __dome_logevent_screenLimit__keys (void);
extern const char * __dome_logevent_screenLimit__name (void);
struct _dome_logevent_screenLimit ;
extern  c_bool __dome_logevent_screenLimit__copyIn(c_base base, struct dome::logevent_screenLimit *from, struct _dome_logevent_screenLimit *to);
extern  void __dome_logevent_screenLimit__copyOut(void *_from, void *_to);
struct _dome_logevent_screenLimit {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_slewError__load (c_base base);
extern const char * __dome_logevent_slewError__keys (void);
extern const char * __dome_logevent_slewError__name (void);
struct _dome_logevent_slewError ;
extern  c_bool __dome_logevent_slewError__copyIn(c_base base, struct dome::logevent_slewError *from, struct _dome_logevent_slewError *to);
extern  void __dome_logevent_slewError__copyOut(void *_from, void *_to);
struct _dome_logevent_slewError {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_slewOK__load (c_base base);
extern const char * __dome_logevent_slewOK__keys (void);
extern const char * __dome_logevent_slewOK__name (void);
struct _dome_logevent_slewOK ;
extern  c_bool __dome_logevent_slewOK__copyIn(c_base base, struct dome::logevent_slewOK *from, struct _dome_logevent_slewOK *to);
extern  void __dome_logevent_slewOK__copyOut(void *_from, void *_to);
struct _dome_logevent_slewOK {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_slewReady__load (c_base base);
extern const char * __dome_logevent_slewReady__keys (void);
extern const char * __dome_logevent_slewReady__name (void);
struct _dome_logevent_slewReady ;
extern  c_bool __dome_logevent_slewReady__copyIn(c_base base, struct dome::logevent_slewReady *from, struct _dome_logevent_slewReady *to);
extern  void __dome_logevent_slewReady__copyOut(void *_from, void *_to);
struct _dome_logevent_slewReady {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_tempError__load (c_base base);
extern const char * __dome_logevent_tempError__keys (void);
extern const char * __dome_logevent_tempError__name (void);
struct _dome_logevent_tempError ;
extern  c_bool __dome_logevent_tempError__copyIn(c_base base, struct dome::logevent_tempError *from, struct _dome_logevent_tempError *to);
extern  void __dome_logevent_tempError__copyOut(void *_from, void *_to);
struct _dome_logevent_tempError {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string device;
    c_long severity;
};

extern c_metaObject __dome_logevent_trackLost__load (c_base base);
extern const char * __dome_logevent_trackLost__keys (void);
extern const char * __dome_logevent_trackLost__name (void);
struct _dome_logevent_trackLost ;
extern  c_bool __dome_logevent_trackLost__copyIn(c_base base, struct dome::logevent_trackLost *from, struct _dome_logevent_trackLost *to);
extern  void __dome_logevent_trackLost__copyOut(void *_from, void *_to);
struct _dome_logevent_trackLost {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_logevent_tracking__load (c_base base);
extern const char * __dome_logevent_tracking__keys (void);
extern const char * __dome_logevent_tracking__name (void);
struct _dome_logevent_tracking ;
extern  c_bool __dome_logevent_tracking__copyIn(c_base base, struct dome::logevent_tracking *from, struct _dome_logevent_tracking *to);
extern  void __dome_logevent_tracking__copyOut(void *_from, void *_to);
struct _dome_logevent_tracking {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __dome_command__load (c_base base);
extern const char * __dome_command__keys (void);
extern const char * __dome_command__name (void);
struct _dome_command ;
extern  c_bool __dome_command__copyIn(c_base base, struct dome::command *from, struct _dome_command *to);
extern  void __dome_command__copyOut(void *_from, void *_to);
struct _dome_command {
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

extern c_metaObject __dome_ackcmd__load (c_base base);
extern const char * __dome_ackcmd__keys (void);
extern const char * __dome_ackcmd__name (void);
struct _dome_ackcmd ;
extern  c_bool __dome_ackcmd__copyIn(c_base base, struct dome::ackcmd *from, struct _dome_ackcmd *to);
extern  void __dome_ackcmd__copyOut(void *_from, void *_to);
struct _dome_ackcmd {
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

extern c_metaObject __dome_logevent__load (c_base base);
extern const char * __dome_logevent__keys (void);
extern const char * __dome_logevent__name (void);
struct _dome_logevent ;
extern  c_bool __dome_logevent__copyIn(c_base base, struct dome::logevent *from, struct _dome_logevent *to);
extern  void __dome_logevent__copyOut(void *_from, void *_to);
struct _dome_logevent {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
    c_long private_host;
    c_string message;
};

#endif
