#ifndef SAL_MOUNTSPLTYPES_H
#define SAL_MOUNTSPLTYPES_H

#include "ccpp_sal_mount.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __sal_mount_mount__load (c_base base);

extern c_metaObject __mount_Alt__load (c_base base);
extern const char * __mount_Alt__keys (void);
extern const char * __mount_Alt__name (void);
struct _mount_Alt ;
extern  c_bool __mount_Alt__copyIn(c_base base, struct mount::Alt *from, struct _mount_Alt *to);
extern  void __mount_Alt__copyOut(void *_from, void *_to);
struct _mount_Alt {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[32];
};

extern c_metaObject __mount_Application__load (c_base base);
extern const char * __mount_Application__keys (void);
extern const char * __mount_Application__name (void);
struct _mount_Application ;
extern  c_bool __mount_Application__copyIn(c_base base, struct mount::Application *from, struct _mount_Application *to);
extern  void __mount_Application__copyOut(void *_from, void *_to);
struct _mount_Application {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_float Demand[4];
    c_float Position[4];
    c_float Error[4];
    c_string Status;
};

extern c_metaObject __mount_Az__load (c_base base);
extern const char * __mount_Az__keys (void);
extern const char * __mount_Az__name (void);
struct _mount_Az ;
extern  c_bool __mount_Az__copyIn(c_base base, struct mount::Az *from, struct _mount_Az *to);
extern  void __mount_Az__copyOut(void *_from, void *_to);
struct _mount_Az {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[32];
};

extern c_metaObject __mount_Electrical__load (c_base base);
extern const char * __mount_Electrical__keys (void);
extern const char * __mount_Electrical__name (void);
struct _mount_Electrical ;
extern  c_bool __mount_Electrical__copyIn(c_base base, struct mount::Electrical *from, struct _mount_Electrical *to);
extern  void __mount_Electrical__copyOut(void *_from, void *_to);
struct _mount_Electrical {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[32];
};

extern c_metaObject __mount_Metrology__load (c_base base);
extern const char * __mount_Metrology__keys (void);
extern const char * __mount_Metrology__name (void);
struct _mount_Metrology ;
extern  c_bool __mount_Metrology__copyIn(c_base base, struct mount::Metrology *from, struct _mount_Metrology *to);
extern  void __mount_Metrology__copyOut(void *_from, void *_to);
struct _mount_Metrology {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[16];
};

extern c_metaObject __mount_Rotator__load (c_base base);
extern const char * __mount_Rotator__keys (void);
extern const char * __mount_Rotator__name (void);
struct _mount_Rotator ;
extern  c_bool __mount_Rotator__copyIn(c_base base, struct mount::Rotator *from, struct _mount_Rotator *to);
extern  void __mount_Rotator__copyOut(void *_from, void *_to);
struct _mount_Rotator {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[32];
};

extern c_metaObject __mount_TC__load (c_base base);
extern const char * __mount_TC__keys (void);
extern const char * __mount_TC__name (void);
struct _mount_TC ;
extern  c_bool __mount_TC__copyIn(c_base base, struct mount::TC *from, struct _mount_TC *to);
extern  void __mount_TC__copyOut(void *_from, void *_to);
struct _mount_TC {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long Raw[16];
    c_float Calibrated[16];
};

extern c_metaObject __mount_command_configure__load (c_base base);
extern const char * __mount_command_configure__keys (void);
extern const char * __mount_command_configure__name (void);
struct _mount_command_configure ;
extern  c_bool __mount_command_configure__copyIn(c_base base, struct mount::command_configure *from, struct _mount_command_configure *to);
extern  void __mount_command_configure__copyOut(void *_from, void *_to);
struct _mount_command_configure {
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

extern c_metaObject __mount_command_moveCamWrap__load (c_base base);
extern const char * __mount_command_moveCamWrap__keys (void);
extern const char * __mount_command_moveCamWrap__name (void);
struct _mount_command_moveCamWrap ;
extern  c_bool __mount_command_moveCamWrap__copyIn(c_base base, struct mount::command_moveCamWrap *from, struct _mount_command_moveCamWrap *to);
extern  void __mount_command_moveCamWrap__copyOut(void *_from, void *_to);
struct _mount_command_moveCamWrap {
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

extern c_metaObject __mount_command_moveMirrorCover__load (c_base base);
extern const char * __mount_command_moveMirrorCover__keys (void);
extern const char * __mount_command_moveMirrorCover__name (void);
struct _mount_command_moveMirrorCover ;
extern  c_bool __mount_command_moveMirrorCover__copyIn(c_base base, struct mount::command_moveMirrorCover *from, struct _mount_command_moveMirrorCover *to);
extern  void __mount_command_moveMirrorCover__copyOut(void *_from, void *_to);
struct _mount_command_moveMirrorCover {
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
    c_string position;
};

extern c_metaObject __mount_command_moveToTarget__load (c_base base);
extern const char * __mount_command_moveToTarget__keys (void);
extern const char * __mount_command_moveToTarget__name (void);
struct _mount_command_moveToTarget ;
extern  c_bool __mount_command_moveToTarget__copyIn(c_base base, struct mount::command_moveToTarget *from, struct _mount_command_moveToTarget *to);
extern  void __mount_command_moveToTarget__copyOut(void *_from, void *_to);
struct _mount_command_moveToTarget {
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

extern c_metaObject __mount_command_test__load (c_base base);
extern const char * __mount_command_test__keys (void);
extern const char * __mount_command_test__name (void);
struct _mount_command_test ;
extern  c_bool __mount_command_test__copyIn(c_base base, struct mount::command_test *from, struct _mount_command_test *to);
extern  void __mount_command_test__copyOut(void *_from, void *_to);
struct _mount_command_test {
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

extern c_metaObject __mount_logevent_accLimit__load (c_base base);
extern const char * __mount_logevent_accLimit__keys (void);
extern const char * __mount_logevent_accLimit__name (void);
struct _mount_logevent_accLimit ;
extern  c_bool __mount_logevent_accLimit__copyIn(c_base base, struct mount::logevent_accLimit *from, struct _mount_logevent_accLimit *to);
extern  void __mount_logevent_accLimit__copyOut(void *_from, void *_to);
struct _mount_logevent_accLimit {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __mount_logevent_altLimit__load (c_base base);
extern const char * __mount_logevent_altLimit__keys (void);
extern const char * __mount_logevent_altLimit__name (void);
struct _mount_logevent_altLimit ;
extern  c_bool __mount_logevent_altLimit__copyIn(c_base base, struct mount::logevent_altLimit *from, struct _mount_logevent_altLimit *to);
extern  void __mount_logevent_altLimit__copyOut(void *_from, void *_to);
struct _mount_logevent_altLimit {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string type;
};

extern c_metaObject __mount_logevent_interlock__load (c_base base);
extern const char * __mount_logevent_interlock__keys (void);
extern const char * __mount_logevent_interlock__name (void);
struct _mount_logevent_interlock ;
extern  c_bool __mount_logevent_interlock__copyIn(c_base base, struct mount::logevent_interlock *from, struct _mount_logevent_interlock *to);
extern  void __mount_logevent_interlock__copyOut(void *_from, void *_to);
struct _mount_logevent_interlock {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
    c_string detail;
};

extern c_metaObject __mount_logevent_powerError__load (c_base base);
extern const char * __mount_logevent_powerError__keys (void);
extern const char * __mount_logevent_powerError__name (void);
struct _mount_logevent_powerError ;
extern  c_bool __mount_logevent_powerError__copyIn(c_base base, struct mount::logevent_powerError *from, struct _mount_logevent_powerError *to);
extern  void __mount_logevent_powerError__copyOut(void *_from, void *_to);
struct _mount_logevent_powerError {
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

extern c_metaObject __mount_logevent_slewError__load (c_base base);
extern const char * __mount_logevent_slewError__keys (void);
extern const char * __mount_logevent_slewError__name (void);
struct _mount_logevent_slewError ;
extern  c_bool __mount_logevent_slewError__copyIn(c_base base, struct mount::logevent_slewError *from, struct _mount_logevent_slewError *to);
extern  void __mount_logevent_slewError__copyOut(void *_from, void *_to);
struct _mount_logevent_slewError {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __mount_logevent_slewOK__load (c_base base);
extern const char * __mount_logevent_slewOK__keys (void);
extern const char * __mount_logevent_slewOK__name (void);
struct _mount_logevent_slewOK ;
extern  c_bool __mount_logevent_slewOK__copyIn(c_base base, struct mount::logevent_slewOK *from, struct _mount_logevent_slewOK *to);
extern  void __mount_logevent_slewOK__copyOut(void *_from, void *_to);
struct _mount_logevent_slewOK {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __mount_logevent_slewReady__load (c_base base);
extern const char * __mount_logevent_slewReady__keys (void);
extern const char * __mount_logevent_slewReady__name (void);
struct _mount_logevent_slewReady ;
extern  c_bool __mount_logevent_slewReady__copyIn(c_base base, struct mount::logevent_slewReady *from, struct _mount_logevent_slewReady *to);
extern  void __mount_logevent_slewReady__copyOut(void *_from, void *_to);
struct _mount_logevent_slewReady {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __mount_logevent_tempError__load (c_base base);
extern const char * __mount_logevent_tempError__keys (void);
extern const char * __mount_logevent_tempError__name (void);
struct _mount_logevent_tempError ;
extern  c_bool __mount_logevent_tempError__copyIn(c_base base, struct mount::logevent_tempError *from, struct _mount_logevent_tempError *to);
extern  void __mount_logevent_tempError__copyOut(void *_from, void *_to);
struct _mount_logevent_tempError {
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

extern c_metaObject __mount_logevent_trackLost__load (c_base base);
extern const char * __mount_logevent_trackLost__keys (void);
extern const char * __mount_logevent_trackLost__name (void);
struct _mount_logevent_trackLost ;
extern  c_bool __mount_logevent_trackLost__copyIn(c_base base, struct mount::logevent_trackLost *from, struct _mount_logevent_trackLost *to);
extern  void __mount_logevent_trackLost__copyOut(void *_from, void *_to);
struct _mount_logevent_trackLost {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __mount_logevent_tracking__load (c_base base);
extern const char * __mount_logevent_tracking__keys (void);
extern const char * __mount_logevent_tracking__name (void);
struct _mount_logevent_tracking ;
extern  c_bool __mount_logevent_tracking__copyIn(c_base base, struct mount::logevent_tracking *from, struct _mount_logevent_tracking *to);
extern  void __mount_logevent_tracking__copyOut(void *_from, void *_to);
struct _mount_logevent_tracking {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __mount_logevent_velLimit__load (c_base base);
extern const char * __mount_logevent_velLimit__keys (void);
extern const char * __mount_logevent_velLimit__name (void);
struct _mount_logevent_velLimit ;
extern  c_bool __mount_logevent_velLimit__copyIn(c_base base, struct mount::logevent_velLimit *from, struct _mount_logevent_velLimit *to);
extern  void __mount_logevent_velLimit__copyOut(void *_from, void *_to);
struct _mount_logevent_velLimit {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_seqNum;
    c_long private_origin;
    c_long private_host;
    c_long priority;
};

extern c_metaObject __mount_command__load (c_base base);
extern const char * __mount_command__keys (void);
extern const char * __mount_command__name (void);
struct _mount_command ;
extern  c_bool __mount_command__copyIn(c_base base, struct mount::command *from, struct _mount_command *to);
extern  void __mount_command__copyOut(void *_from, void *_to);
struct _mount_command {
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

extern c_metaObject __mount_ackcmd__load (c_base base);
extern const char * __mount_ackcmd__keys (void);
extern const char * __mount_ackcmd__name (void);
struct _mount_ackcmd ;
extern  c_bool __mount_ackcmd__copyIn(c_base base, struct mount::ackcmd *from, struct _mount_ackcmd *to);
extern  void __mount_ackcmd__copyOut(void *_from, void *_to);
struct _mount_ackcmd {
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

extern c_metaObject __mount_logevent__load (c_base base);
extern const char * __mount_logevent__keys (void);
extern const char * __mount_logevent__name (void);
struct _mount_logevent ;
extern  c_bool __mount_logevent__copyIn(c_base base, struct mount::logevent *from, struct _mount_logevent *to);
extern  void __mount_logevent__copyOut(void *_from, void *_to);
struct _mount_logevent {
    c_string private_revCode;
    c_double private_sndStamp;
    c_double private_rcvStamp;
    c_long private_origin;
    c_long private_host;
    c_string message;
};

#endif
