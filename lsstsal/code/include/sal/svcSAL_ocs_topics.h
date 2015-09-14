#include "svcSAL_ocs_activity_planning.h"
#include "svcSAL_ocs_activity_record.h"
#include "svcSAL_ocs_command_health.h"
#include "svcSAL_ocs_command_permit.h"
#include "svcSAL_ocs_database_state.h"
#include "svcSAL_ocs_operator_log.h"
#include "svcSAL_ocs_pointing_wcs.h"
#include "svcSAL_ocs_scheduler_econstraints.h"
#include "svcSAL_ocs_scheduler_iconstraints.h"
#include "svcSAL_ocs_scheduler_parameters.h"
#include "svcSAL_ocs_scheduler_program.h"
#include "svcSAL_ocs_scheduler_progress.h"
#include "svcSAL_ocs_scheduler_targets.h"
#include "svcSAL_ocs_staticanalysis.h"
#include "svcSAL_ocs_system.h"
#include "svcSAL_ocs_system_accesscontrol.h"
#include "svcSAL_ocs_system_configuration.h"
#include "svcSAL_ocs_system_networking.h"
#define SAL_IID_ocs_activity_planning 0xe32e08
#define SAL_IID_ocs_activity_record 0xd743d6
#define SAL_IID_ocs_command_health 0x53f599
#define SAL_IID_ocs_command_permit 0xc6f395
#define SAL_IID_ocs_database_state 0x4887a5
#define SAL_IID_ocs_operator_log 0x088bce
#define SAL_IID_ocs_pointing_wcs 0xad1cf1
#define SAL_IID_ocs_scheduler_econstraints 0xd3066f
#define SAL_IID_ocs_scheduler_iconstraints 0x1d0998
#define SAL_IID_ocs_scheduler_parameters 0x745e10
#define SAL_IID_ocs_scheduler_program 0x50b4e9
#define SAL_IID_ocs_scheduler_progress 0x7d0215
#define SAL_IID_ocs_scheduler_targets 0x82e3d0
#define SAL_IID_ocs_staticanalysis 0x271536
#define SAL_IID_ocs_system 0x08cd90
#define SAL_IID_ocs_system_accesscontrol 0x96a1f4
#define SAL_IID_ocs_system_configuration 0x5a86c3
#define SAL_IID_ocs_system_networking 0x16e5bf
