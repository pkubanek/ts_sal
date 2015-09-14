

#include "svcSAL.h"
#include "svcSAL_caches.h"

int svcSAL_shmProperties ( char *subsys, int *streamid, int *size ) {

  streamid = 0;
  size = 0;


  if (strcmp("system_Computer_status",subsys) == 0 ) {
     *streamid = 0x1473;
     *size = sizeof(system_Computer_status_cache);
  }

  if (strcmp("system_Software_revision_history",subsys) == 0 ) {
     *streamid = 0xaeb3;
     *size = sizeof(system_Software_revision_history_cache);
  }

  if (strcmp("system_Hardware_revision_history",subsys) == 0 ) {
     *streamid = 0x0248;
     *size = sizeof(system_Hardware_revision_history_cache);
  }

  if (strcmp("system_Command_history",subsys) == 0 ) {
     *streamid = 0x601c;
     *size = sizeof(system_Command_history_cache);
  }

  if (strcmp("m1m3_TC",subsys) == 0 ) {
     *streamid = 0xd5e3;
     *size = sizeof(m1m3_TC_cache);
  }

  if (strcmp("m1m3_Electrical",subsys) == 0 ) {
     *streamid = 0xb02c;
     *size = sizeof(m1m3_Electrical_cache);
  }

  if (strcmp("m1m3_Metrology",subsys) == 0 ) {
     *streamid = 0x64ec;
     *size = sizeof(m1m3_Metrology_cache);
  }

  if (strcmp("m1m3_Application",subsys) == 0 ) {
     *streamid = 0x43e1;
     *size = sizeof(m1m3_Application_cache);
  }

  if (strcmp("m1m3_Support",subsys) == 0 ) {
     *streamid = 0x8be7;
     *size = sizeof(m1m3_Support_cache);
  }

  if (strcmp("m1m3_Actuators",subsys) == 0 ) {
     *streamid = 0x9843;
     *size = sizeof(m1m3_Actuators_cache);
  }

  if (strcmp("m1m3_Surface",subsys) == 0 ) {
     *streamid = 0xea1b;
     *size = sizeof(m1m3_Surface_cache);
  }

  if (strcmp("m2_TC",subsys) == 0 ) {
     *streamid = 0xd893;
     *size = sizeof(m2_TC_cache);
  }

  if (strcmp("m2_Electrical",subsys) == 0 ) {
     *streamid = 0xb6f3;
     *size = sizeof(m2_Electrical_cache);
  }

  if (strcmp("m2_Metrology",subsys) == 0 ) {
     *streamid = 0x07ba;
     *size = sizeof(m2_Metrology_cache);
  }

  if (strcmp("m2_Application",subsys) == 0 ) {
     *streamid = 0xf2c0;
     *size = sizeof(m2_Application_cache);
  }

  if (strcmp("m2_Hexapod",subsys) == 0 ) {
     *streamid = 0x1b96;
     *size = sizeof(m2_Hexapod_cache);
  }

  if (strcmp("m2_Actuators",subsys) == 0 ) {
     *streamid = 0xebca;
     *size = sizeof(m2_Actuators_cache);
  }

  if (strcmp("m2_Surface",subsys) == 0 ) {
     *streamid = 0xeeb6;
     *size = sizeof(m2_Surface_cache);
  }

  if (strcmp("mount_TC",subsys) == 0 ) {
     *streamid = 0x7fc9;
     *size = sizeof(mount_TC_cache);
  }

  if (strcmp("mount_Electrical",subsys) == 0 ) {
     *streamid = 0x64d7;
     *size = sizeof(mount_Electrical_cache);
  }

  if (strcmp("mount_Metrology",subsys) == 0 ) {
     *streamid = 0xb159;
     *size = sizeof(mount_Metrology_cache);
  }

  if (strcmp("mount_Application",subsys) == 0 ) {
     *streamid = 0x0cbb;
     *size = sizeof(mount_Application_cache);
  }

  if (strcmp("mount_Alt",subsys) == 0 ) {
     *streamid = 0xa465;
     *size = sizeof(mount_Alt_cache);
  }

  if (strcmp("mount_Az",subsys) == 0 ) {
     *streamid = 0xfff5;
     *size = sizeof(mount_Az_cache);
  }

  if (strcmp("mount_Rotator",subsys) == 0 ) {
     *streamid = 0x9e2a;
     *size = sizeof(mount_Rotator_cache);
  }

  if (strcmp("power_TC",subsys) == 0 ) {
     *streamid = 0x31b4;
     *size = sizeof(power_TC_cache);
  }

  if (strcmp("power_Electrical",subsys) == 0 ) {
     *streamid = 0xfc67;
     *size = sizeof(power_Electrical_cache);
  }

  if (strcmp("power_UPSs",subsys) == 0 ) {
     *streamid = 0xddd2;
     *size = sizeof(power_UPSs_cache);
  }

  if (strcmp("calibration_TC",subsys) == 0 ) {
     *streamid = 0x3a7d;
     *size = sizeof(calibration_TC_cache);
  }

  if (strcmp("calibration_Electrical",subsys) == 0 ) {
     *streamid = 0x7cea;
     *size = sizeof(calibration_Electrical_cache);
  }

  if (strcmp("calibration_Metrology",subsys) == 0 ) {
     *streamid = 0x0638;
     *size = sizeof(calibration_Metrology_cache);
  }

  if (strcmp("calibration_Application",subsys) == 0 ) {
     *streamid = 0x0132;
     *size = sizeof(calibration_Application_cache);
  }

  if (strcmp("enclosure_TC",subsys) == 0 ) {
     *streamid = 0x52e1;
     *size = sizeof(enclosure_TC_cache);
  }

  if (strcmp("enclosure_Electrical",subsys) == 0 ) {
     *streamid = 0x6e8a;
     *size = sizeof(enclosure_Electrical_cache);
  }

  if (strcmp("enclosure_Metrology",subsys) == 0 ) {
     *streamid = 0x49e9;
     *size = sizeof(enclosure_Metrology_cache);
  }

  if (strcmp("enclosure_Application",subsys) == 0 ) {
     *streamid = 0x69df;
     *size = sizeof(enclosure_Application_cache);
  }

  if (strcmp("enclosure_Azimuth",subsys) == 0 ) {
     *streamid = 0xa5db;
     *size = sizeof(enclosure_Azimuth_cache);
  }

  if (strcmp("enclosure_Shutter",subsys) == 0 ) {
     *streamid = 0x5cc2;
     *size = sizeof(enclosure_Shutter_cache);
  }

  if (strcmp("enclosure_Vents",subsys) == 0 ) {
     *streamid = 0x9389;
     *size = sizeof(enclosure_Vents_cache);
  }

  if (strcmp("enclosure_Thermal_control",subsys) == 0 ) {
     *streamid = 0xf088;
     *size = sizeof(enclosure_Thermal_control_cache);
  }

  if (strcmp("scheduler_Application",subsys) == 0 ) {
     *streamid = 0x8a9d;
     *size = sizeof(scheduler_Application_cache);
  }

  if (strcmp("operations_Application",subsys) == 0 ) {
     *streamid = 0x7a58;
     *size = sizeof(operations_Application_cache);
  }

  if (strcmp("auxscope_TC",subsys) == 0 ) {
     *streamid = 0xadb7;
     *size = sizeof(auxscope_TC_cache);
  }

  if (strcmp("auxscope_Electrical",subsys) == 0 ) {
     *streamid = 0x5a17;
     *size = sizeof(auxscope_Electrical_cache);
  }

  if (strcmp("auxscope_Metrology",subsys) == 0 ) {
     *streamid = 0x8d62;
     *size = sizeof(auxscope_Metrology_cache);
  }

  if (strcmp("auxscope_Application",subsys) == 0 ) {
     *streamid = 0x2749;
     *size = sizeof(auxscope_Application_cache);
  }

  if (strcmp("auxscope_TCS",subsys) == 0 ) {
     *streamid = 0xfbca;
     *size = sizeof(auxscope_TCS_cache);
  }

  if (strcmp("auxscope_Spectrometer",subsys) == 0 ) {
     *streamid = 0x1d2f;
     *size = sizeof(auxscope_Spectrometer_cache);
  }

  if (strcmp("auxscope_Camera",subsys) == 0 ) {
     *streamid = 0x2344;
     *size = sizeof(auxscope_Camera_cache);
  }

  if (strcmp("lasercal_TC",subsys) == 0 ) {
     *streamid = 0x2733;
     *size = sizeof(lasercal_TC_cache);
  }

  if (strcmp("lasercal_Electrical",subsys) == 0 ) {
     *streamid = 0x39f7;
     *size = sizeof(lasercal_Electrical_cache);
  }

  if (strcmp("lasercal_Application",subsys) == 0 ) {
     *streamid = 0xdfc4;
     *size = sizeof(lasercal_Application_cache);
  }

  if (strcmp("seeing_dimm_TC",subsys) == 0 ) {
     *streamid = 0xbaf1;
     *size = sizeof(seeing_dimm_TC_cache);
  }

  if (strcmp("seeing_dimm_Electrical",subsys) == 0 ) {
     *streamid = 0xbd69;
     *size = sizeof(seeing_dimm_Electrical_cache);
  }

  if (strcmp("seeing_dimm_Metrology",subsys) == 0 ) {
     *streamid = 0x5c3f;
     *size = sizeof(seeing_dimm_Metrology_cache);
  }

  if (strcmp("seeing_dimm_Application",subsys) == 0 ) {
     *streamid = 0x306d;
     *size = sizeof(seeing_dimm_Application_cache);
  }

  if (strcmp("seeing_mass_TC",subsys) == 0 ) {
     *streamid = 0xf794;
     *size = sizeof(seeing_mass_TC_cache);
  }

  if (strcmp("seeing_mass_Electrical",subsys) == 0 ) {
     *streamid = 0x1de3;
     *size = sizeof(seeing_mass_Electrical_cache);
  }

  if (strcmp("seeing_mass_Metrology",subsys) == 0 ) {
     *streamid = 0x9677;
     *size = sizeof(seeing_mass_Metrology_cache);
  }

  if (strcmp("seeing_mass_Application",subsys) == 0 ) {
     *streamid = 0x6342;
     *size = sizeof(seeing_mass_Application_cache);
  }

  if (strcmp("skycam_TC",subsys) == 0 ) {
     *streamid = 0xafed;
     *size = sizeof(skycam_TC_cache);
  }

  if (strcmp("skycam_Electrical",subsys) == 0 ) {
     *streamid = 0x5dec;
     *size = sizeof(skycam_Electrical_cache);
  }

  if (strcmp("skycam_Metrology",subsys) == 0 ) {
     *streamid = 0x72e2;
     *size = sizeof(skycam_Metrology_cache);
  }

  if (strcmp("skycam_Application",subsys) == 0 ) {
     *streamid = 0xac74;
     *size = sizeof(skycam_Application_cache);
  }

  if (strcmp("environment_TC",subsys) == 0 ) {
     *streamid = 0x843d;
     *size = sizeof(environment_TC_cache);
  }

  if (strcmp("environment_Electrical",subsys) == 0 ) {
     *streamid = 0x13ba;
     *size = sizeof(environment_Electrical_cache);
  }

  if (strcmp("environment_Weather",subsys) == 0 ) {
     *streamid = 0x2898;
     *size = sizeof(environment_Weather_cache);
  }

  if (strcmp("environment_Dust_monitor",subsys) == 0 ) {
     *streamid = 0xb449;
     *size = sizeof(environment_Dust_monitor_cache);
  }

  if (strcmp("environment_Lightning_detector",subsys) == 0 ) {
     *streamid = 0xae27;
     *size = sizeof(environment_Lightning_detector_cache);
  }

  if (strcmp("environment_Seismometer",subsys) == 0 ) {
     *streamid = 0x9c47;
     *size = sizeof(environment_Seismometer_cache);
  }

  if (strcmp("environment_Video_cameras",subsys) == 0 ) {
     *streamid = 0x2884;
     *size = sizeof(environment_Video_cameras_cache);
  }

  if (strcmp("network_Application",subsys) == 0 ) {
     *streamid = 0xad08;
     *size = sizeof(network_Application_cache);
  }

  if (strcmp("tcs_kernel_TrackRefSys",subsys) == 0 ) {
     *streamid = 0x8bfe;
     *size = sizeof(tcs_kernel_TrackRefSys_cache);
  }

  if (strcmp("tcs_kernel_Target",subsys) == 0 ) {
     *streamid = 0xde92;
     *size = sizeof(tcs_kernel_Target_cache);
  }

  if (strcmp("tcs_kernel_DawdleFilter",subsys) == 0 ) {
     *streamid = 0x8be7;
     *size = sizeof(tcs_kernel_DawdleFilter_cache);
  }

  if (strcmp("tcs_kernel_FK5Target",subsys) == 0 ) {
     *streamid = 0x10bf;
     *size = sizeof(tcs_kernel_FK5Target_cache);
  }

  if (strcmp("tcs_kernel_OpticsVt",subsys) == 0 ) {
     *streamid = 0x3e96;
     *size = sizeof(tcs_kernel_OpticsVt_cache);
  }

  if (strcmp("tcs_kernel_PointingControl",subsys) == 0 ) {
     *streamid = 0x4927;
     *size = sizeof(tcs_kernel_PointingControl_cache);
  }

  if (strcmp("tcs_kernel_PointingLog",subsys) == 0 ) {
     *streamid = 0x6a2d;
     *size = sizeof(tcs_kernel_PointingLog_cache);
  }

  if (strcmp("tcs_kernel_PointingModel",subsys) == 0 ) {
     *streamid = 0x7986;
     *size = sizeof(tcs_kernel_PointingModel_cache);
  }

  if (strcmp("tcs_kernel_Site",subsys) == 0 ) {
     *streamid = 0xbd38;
     *size = sizeof(tcs_kernel_Site_cache);
  }

  if (strcmp("tcs_kernel_TimeKeeper",subsys) == 0 ) {
     *streamid = 0xaf51;
     *size = sizeof(tcs_kernel_TimeKeeper_cache);
  }

  if (strcmp("tcs_kernel_TrackingTarget",subsys) == 0 ) {
     *streamid = 0xc491;
     *size = sizeof(tcs_kernel_TrackingTarget_cache);
  }

  if (strcmp("camera_BEE_biases",subsys) == 0 ) {
     *streamid = 0xeff6;
     *size = sizeof(camera_BEE_biases_cache);
  }

  if (strcmp("camera_BEE_clocks",subsys) == 0 ) {
     *streamid = 0x52af;
     *size = sizeof(camera_BEE_clocks_cache);
  }

  if (strcmp("camera_BEE_thermal",subsys) == 0 ) {
     *streamid = 0x05d7;
     *size = sizeof(camera_BEE_thermal_cache);
  }

  if (strcmp("camera_CALSYS",subsys) == 0 ) {
     *streamid = 0xe711;
     *size = sizeof(camera_CALSYS_cache);
  }

  if (strcmp("camera_CCS",subsys) == 0 ) {
     *streamid = 0xf843;
     *size = sizeof(camera_CCS_cache);
  }

  if (strcmp("camera_FCS",subsys) == 0 ) {
     *streamid = 0xcfd1;
     *size = sizeof(camera_FCS_cache);
  }

  if (strcmp("camera_GAS",subsys) == 0 ) {
     *streamid = 0x969c;
     *size = sizeof(camera_GAS_cache);
  }

  if (strcmp("camera_LASERCAL",subsys) == 0 ) {
     *streamid = 0xfe4e;
     *size = sizeof(camera_LASERCAL_cache);
  }

  if (strcmp("camera_PWR",subsys) == 0 ) {
     *streamid = 0x7a2a;
     *size = sizeof(camera_PWR_cache);
  }

  if (strcmp("camera_QA_measured",subsys) == 0 ) {
     *streamid = 0x6536;
     *size = sizeof(camera_QA_measured_cache);
  }

  if (strcmp("camera_SCS",subsys) == 0 ) {
     *streamid = 0xb3ff;
     *size = sizeof(camera_SCS_cache);
  }

  if (strcmp("camera_SDS_amplifiers",subsys) == 0 ) {
     *streamid = 0xb93b;
     *size = sizeof(camera_SDS_amplifiers_cache);
  }

  if (strcmp("camera_SDS",subsys) == 0 ) {
     *streamid = 0xdf73;
     *size = sizeof(camera_SDS_cache);
  }

  if (strcmp("camera_TC_control",subsys) == 0 ) {
     *streamid = 0xa82c;
     *size = sizeof(camera_TC_control_cache);
  }

  if (strcmp("camera_TCM",subsys) == 0 ) {
     *streamid = 0x68d7;
     *size = sizeof(camera_TCM_cache);
  }

  if (strcmp("camera_TC_zone1",subsys) == 0 ) {
     *streamid = 0x90a0;
     *size = sizeof(camera_TC_zone1_cache);
  }

  if (strcmp("camera_TC_zone2",subsys) == 0 ) {
     *streamid = 0xa6fd;
     *size = sizeof(camera_TC_zone2_cache);
  }

  if (strcmp("camera_TC_zone3",subsys) == 0 ) {
     *streamid = 0x7a3a;
     *size = sizeof(camera_TC_zone3_cache);
  }

  if (strcmp("camera_TC_zone4",subsys) == 0 ) {
     *streamid = 0xba3c;
     *size = sizeof(camera_TC_zone4_cache);
  }

  if (strcmp("camera_TC_zone5",subsys) == 0 ) {
     *streamid = 0x2668;
     *size = sizeof(camera_TC_zone5_cache);
  }

  if (strcmp("camera_TC_zone6",subsys) == 0 ) {
     *streamid = 0xf361;
     *size = sizeof(camera_TC_zone6_cache);
  }

  if (strcmp("camera_UTIL",subsys) == 0 ) {
     *streamid = 0xb9a6;
     *size = sizeof(camera_UTIL_cache);
  }

  if (strcmp("camera_VCS",subsys) == 0 ) {
     *streamid = 0x329c;
     *size = sizeof(camera_VCS_cache);
  }

  if (strcmp("camera_WDS_wfsRaft",subsys) == 0 ) {
     *streamid = 0xcfaf;
     *size = sizeof(camera_WDS_wfsRaft_cache);
  }

  if (strcmp("auxscope_command",subsys) == 0 ) {
     *streamid = 0x9123;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("auxscope_response",subsys) == 0 ) {
     *streamid = 0xa070;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("calibration_command",subsys) == 0 ) {
     *streamid = 0x3720;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("calibration_response",subsys) == 0 ) {
     *streamid = 0xafec;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("camera_command",subsys) == 0 ) {
     *streamid = 0x716b;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("camera_response",subsys) == 0 ) {
     *streamid = 0xfd44;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("enclosure_command",subsys) == 0 ) {
     *streamid = 0x6ee7;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("enclosure_response",subsys) == 0 ) {
     *streamid = 0x8a68;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("environment_command",subsys) == 0 ) {
     *streamid = 0x861a;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("environment_response",subsys) == 0 ) {
     *streamid = 0xe3f4;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("lasercal_command",subsys) == 0 ) {
     *streamid = 0xc2e7;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("lasercal_response",subsys) == 0 ) {
     *streamid = 0xfb5d;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("m1m3_command",subsys) == 0 ) {
     *streamid = 0xc0c4;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("m1m3_response",subsys) == 0 ) {
     *streamid = 0x2401;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("m2_command",subsys) == 0 ) {
     *streamid = 0xd6a5;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("m2_response",subsys) == 0 ) {
     *streamid = 0x86b5;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("mount_command",subsys) == 0 ) {
     *streamid = 0x83c4;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("mount_response",subsys) == 0 ) {
     *streamid = 0x3362;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("network_command",subsys) == 0 ) {
     *streamid = 0xd170;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("network_response",subsys) == 0 ) {
     *streamid = 0x5f3e;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("operations_command",subsys) == 0 ) {
     *streamid = 0x8154;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("operations_response",subsys) == 0 ) {
     *streamid = 0x611a;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("power_command",subsys) == 0 ) {
     *streamid = 0x70db;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("power_response",subsys) == 0 ) {
     *streamid = 0xb7e0;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("scheduler_command",subsys) == 0 ) {
     *streamid = 0x3e87;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("scheduler_response",subsys) == 0 ) {
     *streamid = 0xff89;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("seeing_dimm_command",subsys) == 0 ) {
     *streamid = 0x7f20;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("seeing_dimm_response",subsys) == 0 ) {
     *streamid = 0x2c0a;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("seeing_mass_command",subsys) == 0 ) {
     *streamid = 0x7456;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("seeing_mass_response",subsys) == 0 ) {
     *streamid = 0x1ab1;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("skycam_command",subsys) == 0 ) {
     *streamid = 0xf3d1;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("skycam_response",subsys) == 0 ) {
     *streamid = 0xb4e2;
     *size = sizeof(svcSAL_response);
  }

  if (strcmp("tcs_command",subsys) == 0 ) {
     *streamid = 0x0a28;
     *size = sizeof(svcSAL_command);
  }

  if (strcmp("tcs_response",subsys) == 0 ) {
     *streamid = 0x6be9;
     *size = sizeof(svcSAL_response);
  }

  if (streamid == 0) {
     return SAL__ERR;
  }
  return SAL__OK;
}

