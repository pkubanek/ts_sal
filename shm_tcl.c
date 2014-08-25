#include "shmem-m3_Electrical/m3_Electrical_cache.h"
#include "shmem-mount_Alt/mount_Alt_cache.h"
#include "shmem-auxscope_TCS/auxscope_TCS_cache.h"
#include "shmem-m2_Electrical/m2_Electrical_cache.h"
#include "shmem-camera_WDS/camera_WDS_cache.h"
#include "shmem-network_Application/network_Application_cache.h"
#include "shmem-m1_Actuators/m1_Actuators_cache.h"
#include "shmem-seeing_mass_Metrology/seeing_mass_Metrology_cache.h"
#include "shmem-calibration_Metrology/calibration_Metrology_cache.h"
#include "shmem-m1_Temps/m1_Temps_cache.h"
#include "shmem-m1_Application/m1_Application_cache.h"
#include "shmem-mount_Metrology/mount_Metrology_cache.h"
#include "shmem-camera_RNA/camera_RNA_cache.h"
#include "shmem-power_Temps/power_Temps_cache.h"
#include "shmem-m2_Actuators/m2_Actuators_cache.h"
#include "shmem-enclosure_Thermal_control/enclosure_Thermal_control_cache.h"
#include "shmem-m3_Metrology/m3_Metrology_cache.h"
#include "shmem-system_Command_history/system_Command_history_cache.h"
#include "shmem-camera_T3U/camera_T3U_cache.h"
#include "shmem-tcs_kernel_TimeKeeper/tcs_kernel_TimeKeeper_cache.h"
#include "shmem-m2_Temps/m2_Temps_cache.h"
#include "shmem-auxscope_Temps/auxscope_Temps_cache.h"
#include "shmem-skycam_Application/skycam_Application_cache.h"
#include "shmem-seeing_mass_Application/seeing_mass_Application_cache.h"
#include "shmem-system_Hardware_revision_history/system_Hardware_revision_history_cache.h"
#include "shmem-system_Computer_status/system_Computer_status_cache.h"
#include "shmem-auxscope_Camera/auxscope_Camera_cache.h"
#include "shmem-camera_SCU/camera_SCU_cache.h"
#include "shmem-system_Software_revision_history/system_Software_revision_history_cache.h"
#include "shmem-m1_Surface/m1_Surface_cache.h"
#include "shmem-camera_T2S/camera_T2S_cache.h"
#include "shmem-environment_Weather/environment_Weather_cache.h"
#include "shmem-camera_FEE/camera_FEE_cache.h"
#include "shmem-mount_Electrical/mount_Electrical_cache.h"
#include "shmem-m1_Electrical/m1_Electrical_cache.h"
#include "shmem-tcs_kernel_PointingControl/tcs_kernel_PointingControl_cache.h"
#include "shmem-environment_Lightning_detector/environment_Lightning_detector_cache.h"
#include "shmem-auxscope_Application/auxscope_Application_cache.h"
#include "shmem-power_UPSs/power_UPSs_cache.h"
#include "shmem-enclosure_Azimuth/enclosure_Azimuth_cache.h"
#include "shmem-environment_Seismometer/environment_Seismometer_cache.h"
#include "shmem-camera_WFS/camera_WFS_cache.h"
#include "shmem-calibration_Electrical/calibration_Electrical_cache.h"
#include "shmem-mount_Temps/mount_Temps_cache.h"
#include "shmem-seeing_mass_Electrical/seeing_mass_Electrical_cache.h"
#include "shmem-enclosure_Metrology/enclosure_Metrology_cache.h"
#include "shmem-mount_Az/mount_Az_cache.h"
#include "shmem-tcs_kernel_FK5Target/tcs_kernel_FK5Target_cache.h"
#include "shmem-camera_FCS/camera_FCS_cache.h"
#include "shmem-environment_Temps/environment_Temps_cache.h"
#include "shmem-tcs_kernel_PointingModel/tcs_kernel_PointingModel_cache.h"
#include "shmem-enclosure_Application/enclosure_Application_cache.h"
#include "shmem-m1_Support/m1_Support_cache.h"
#include "shmem-power_Electrical/power_Electrical_cache.h"
#include "shmem-m3_Surface/m3_Surface_cache.h"
#include "shmem-camera_GS/camera_GS_cache.h"
#include "shmem-seeing_dimm_Electrical/seeing_dimm_Electrical_cache.h"
#include "shmem-camera_T4U/camera_T4U_cache.h"
#include "shmem-skycam_Electrical/skycam_Electrical_cache.h"
#include "shmem-scheduler_Application/scheduler_Application_cache.h"
#include "shmem-camera_SAS/camera_SAS_cache.h"
#include "shmem-camera_TC/camera_TC_cache.h"
#include "shmem-camera_CCS/camera_CCS_cache.h"
#include "shmem-calibration_Temps/calibration_Temps_cache.h"
#include "shmem-m2_Surface/m2_Surface_cache.h"
#include "shmem-tcs_kernel_OpticsVt/tcs_kernel_OpticsVt_cache.h"
#include "shmem-auxscope_Metrology/auxscope_Metrology_cache.h"
#include "shmem-camera_SDS/camera_SDS_cache.h"
#include "shmem-enclosure_Shutter/enclosure_Shutter_cache.h"
#include "shmem-lasercal_Electrical/lasercal_Electrical_cache.h"
#include "shmem-auxscope_Spectrometer/auxscope_Spectrometer_cache.h"
#include "shmem-environment_Electrical/environment_Electrical_cache.h"
#include "shmem-mount_Application/mount_Application_cache.h"
#include "shmem-m3_Application/m3_Application_cache.h"
#include "shmem-tcs_kernel_Target/tcs_kernel_Target_cache.h"
#include "shmem-seeing_dimm_Temps/seeing_dimm_Temps_cache.h"
#include "shmem-tcs_kernel_Site/tcs_kernel_Site_cache.h"
#include "shmem-seeing_dimm_Application/seeing_dimm_Application_cache.h"
#include "shmem-operations_Application/operations_Application_cache.h"
#include "shmem-camera_GAS/camera_GAS_cache.h"
#include "shmem-skycam_Metrology/skycam_Metrology_cache.h"
#include "shmem-tcs_kernel_TrackRefSys/tcs_kernel_TrackRefSys_cache.h"
#include "shmem-camera_VCS/camera_VCS_cache.h"
#include "shmem-lasercal_Temps/lasercal_Temps_cache.h"
#include "shmem-mount_Rotator/mount_Rotator_cache.h"
#include "shmem-calibration_Application/calibration_Application_cache.h"
#include "shmem-seeing_dimm_Metrology/seeing_dimm_Metrology_cache.h"
#include "shmem-camera_BEE/camera_BEE_cache.h"
#include "shmem-auxscope_Electrical/auxscope_Electrical_cache.h"
#include "shmem-camera_T1S/camera_T1S_cache.h"
#include "shmem-environment_Dust_monitor/environment_Dust_monitor_cache.h"
#include "shmem-tcs_kernel_DawdleFilter/tcs_kernel_DawdleFilter_cache.h"
#include "shmem-enclosure_Temps/enclosure_Temps_cache.h"
#include "shmem-environment_Video_cameras/environment_Video_cameras_cache.h"
#include "shmem-skycam_Temps/skycam_Temps_cache.h"
#include "shmem-m2_Hexapod/m2_Hexapod_cache.h"
#include "shmem-lasercal_Application/lasercal_Application_cache.h"
#include "shmem-m3_Support/m3_Support_cache.h"
#include "shmem-camera_RAS/camera_RAS_cache.h"
#include "shmem-seeing_mass_Temps/seeing_mass_Temps_cache.h"
#include "shmem-tcs_kernel_TrackingTarget/tcs_kernel_TrackingTarget_cache.h"
#include "shmem-m3_Temps/m3_Temps_cache.h"
#include "shmem-m3_Actuators/m3_Actuators_cache.h"
#include "shmem-m2_Application/m2_Application_cache.h"
#include "shmem-m1_Metrology/m1_Metrology_cache.h"
#include "shmem-enclosure_Electrical/enclosure_Electrical_cache.h"
#include "shmem-m2_Metrology/m2_Metrology_cache.h"
#include "shmem-enclosure_Vents/enclosure_Vents_cache.h"
#include "shmem-tcs_kernel_PointingLog/tcs_kernel_PointingLog_cache.h"
#include "tcl.h"

int updateVariables(Tcl_Interp *interp, char *subsysid, int *shmdata_ref)
{
    char *text;

    if (strcmp(subsysid,"m3_Electrical") == 0) {
       m3_Electrical_cache *m3_Electrical_ref;
       m3_Electrical_ref = (m3_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm3_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m3_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm3_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm3_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m3_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm3_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Electrical_ref->Status);
      m3_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"mount_Alt") == 0) {
       mount_Alt_cache *mount_Alt_ref;
       mount_Alt_ref = (mount_Alt_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMmount_Alt", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &mount_Alt_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMmount_Alt", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Alt_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMmount_Alt", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &mount_Alt_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMmount_Alt", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Alt_ref->Status);
      mount_Alt_ref->syncO = 1;
    }

    if (strcmp(subsysid,"auxscope_TCS") == 0) {
       auxscope_TCS_cache *auxscope_TCS_ref;
       auxscope_TCS_ref = (auxscope_TCS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMauxscope_TCS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &auxscope_TCS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMauxscope_TCS", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_TCS_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMauxscope_TCS", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &auxscope_TCS_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMauxscope_TCS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_TCS_ref->Status);
      auxscope_TCS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m2_Electrical") == 0) {
       m2_Electrical_cache *m2_Electrical_ref;
       m2_Electrical_ref = (m2_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm2_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m2_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm2_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm2_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m2_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm2_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Electrical_ref->Status);
      m2_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_WDS") == 0) {
       camera_WDS_cache *camera_WDS_ref;
       camera_WDS_ref = (camera_WDS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_WDS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_WDS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_WDS", "Metadata", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_WDS_ref->Metadata);

      text = Tcl_GetVar2(interp, "SHMcamera_WDS", "results", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_WDS_ref->results);

      text = Tcl_GetVar2(interp, "SHMcamera_WDS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_WDS_ref->Status);
      camera_WDS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"network_Application") == 0) {
       network_Application_cache *network_Application_ref;
       network_Application_ref = (network_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMnetwork_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &network_Application_ref->syncI);
      network_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m1_Actuators") == 0) {
       m1_Actuators_cache *m1_Actuators_ref;
       m1_Actuators_ref = (m1_Actuators_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm1_Actuators", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m1_Actuators_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm1_Actuators", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Actuators_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm1_Actuators", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m1_Actuators_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm1_Actuators", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Actuators_ref->Status);
      m1_Actuators_ref->syncO = 1;
    }

    if (strcmp(subsysid,"seeing_mass_Metrology") == 0) {
       seeing_mass_Metrology_cache *seeing_mass_Metrology_ref;
       seeing_mass_Metrology_ref = (seeing_mass_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMseeing_mass_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &seeing_mass_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_mass_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_mass_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_mass_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_mass_Metrology_ref->Status);
      seeing_mass_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"calibration_Metrology") == 0) {
       calibration_Metrology_cache *calibration_Metrology_ref;
       calibration_Metrology_ref = (calibration_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcalibration_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &calibration_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcalibration_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &calibration_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcalibration_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &calibration_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcalibration_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &calibration_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMcalibration_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &calibration_Metrology_ref->Status);
      calibration_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m1_Temps") == 0) {
       m1_Temps_cache *m1_Temps_ref;
       m1_Temps_ref = (m1_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm1_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m1_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm1_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm1_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m1_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm1_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Temps_ref->Health);
      m1_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m1_Application") == 0) {
       m1_Application_cache *m1_Application_ref;
       m1_Application_ref = (m1_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm1_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m1_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm1_Application", "Demand", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m1_Application_ref->Demand);

      text = Tcl_GetVar2(interp, "SHMm1_Application", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m1_Application_ref->Position);

      text = Tcl_GetVar2(interp, "SHMm1_Application", "Error", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m1_Application_ref->Error);

      text = Tcl_GetVar2(interp, "SHMm1_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(m1_Application_ref->Status,text);
      m1_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"mount_Metrology") == 0) {
       mount_Metrology_cache *mount_Metrology_ref;
       mount_Metrology_ref = (mount_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMmount_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &mount_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMmount_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMmount_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &mount_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMmount_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMmount_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Metrology_ref->Status);
      mount_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_RNA") == 0) {
       camera_RNA_cache *camera_RNA_ref;
       camera_RNA_ref = (camera_RNA_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_RNA", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_RNA_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_RNA", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_RNA_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_RNA", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_RNA_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_RNA", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_RNA_ref->Status);
      camera_RNA_ref->syncO = 1;
    }

    if (strcmp(subsysid,"power_Temps") == 0) {
       power_Temps_cache *power_Temps_ref;
       power_Temps_ref = (power_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMpower_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &power_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMpower_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &power_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMpower_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &power_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMpower_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &power_Temps_ref->Health);
      power_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m2_Actuators") == 0) {
       m2_Actuators_cache *m2_Actuators_ref;
       m2_Actuators_ref = (m2_Actuators_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm2_Actuators", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m2_Actuators_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm2_Actuators", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Actuators_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm2_Actuators", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m2_Actuators_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm2_Actuators", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Actuators_ref->Status);
      m2_Actuators_ref->syncO = 1;
    }

    if (strcmp(subsysid,"enclosure_Thermal_control") == 0) {
       enclosure_Thermal_control_cache *enclosure_Thermal_control_ref;
       enclosure_Thermal_control_ref = (enclosure_Thermal_control_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenclosure_Thermal_control", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &enclosure_Thermal_control_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenclosure_Thermal_control", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Thermal_control_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenclosure_Thermal_control", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Thermal_control_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenclosure_Thermal_control", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Thermal_control_ref->Status);
      enclosure_Thermal_control_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m3_Metrology") == 0) {
       m3_Metrology_cache *m3_Metrology_ref;
       m3_Metrology_ref = (m3_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm3_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m3_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm3_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm3_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m3_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm3_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMm3_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Metrology_ref->Status);
      m3_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"system_Command_history") == 0) {
       system_Command_history_cache *system_Command_history_ref;
       system_Command_history_ref = (system_Command_history_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMsystem_Command_history", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &system_Command_history_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMsystem_Command_history", "Command", TCL_GLOBAL_ONLY);
      strcpy(system_Command_history_ref->Command,text);

      text = Tcl_GetVar2(interp, "SHMsystem_Command_history", "Data", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &system_Command_history_ref->Data);

      text = Tcl_GetVar2(interp, "SHMsystem_Command_history", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &system_Command_history_ref->Status);
      system_Command_history_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_T3U") == 0) {
       camera_T3U_cache *camera_T3U_ref;
       camera_T3U_ref = (camera_T3U_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_T3U", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_T3U_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_T3U", "HeaterRaw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_T3U_ref->HeaterRaw);

      text = Tcl_GetVar2(interp, "SHMcamera_T3U", "HeaterCalibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_T3U_ref->HeaterCalibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_T3U", "HeaterStatus", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_T3U_ref->HeaterStatus);
      camera_T3U_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_TimeKeeper") == 0) {
       tcs_kernel_TimeKeeper_cache *tcs_kernel_TimeKeeper_ref;
       tcs_kernel_TimeKeeper_ref = (tcs_kernel_TimeKeeper_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TimeKeeper", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_TimeKeeper_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TimeKeeper", "Tai", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TimeKeeper_ref->Tai);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TimeKeeper", "Tt", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TimeKeeper_ref->Tt);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TimeKeeper", "Cst", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TimeKeeper_ref->Cst);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TimeKeeper", "Sst", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TimeKeeper_ref->Sst);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TimeKeeper", "Dcst", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TimeKeeper_ref->Dcst);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TimeKeeper", "Dsst", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TimeKeeper_ref->Dsst);
      tcs_kernel_TimeKeeper_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m2_Temps") == 0) {
       m2_Temps_cache *m2_Temps_ref;
       m2_Temps_ref = (m2_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm2_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m2_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm2_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm2_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m2_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm2_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Temps_ref->Health);
      m2_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"auxscope_Temps") == 0) {
       auxscope_Temps_cache *auxscope_Temps_ref;
       auxscope_Temps_ref = (auxscope_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMauxscope_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &auxscope_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMauxscope_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMauxscope_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &auxscope_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMauxscope_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Temps_ref->Health);
      auxscope_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"skycam_Application") == 0) {
       skycam_Application_cache *skycam_Application_ref;
       skycam_Application_ref = (skycam_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMskycam_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &skycam_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "fitsfile", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->fitsfile,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "filter", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->filter,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "ra", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->ra,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "dec", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->dec,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "ra_2m", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->ra_2m,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "dec_2m", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->dec_2m,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "ra_4m", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->ra_4m,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "dec_4m", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->dec_4m,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "ra_wiyn", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->ra_wiyn,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "dec_wiyn", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->dec_wiyn,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "date", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->date,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "utshut", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->utshut,text);

      text = Tcl_GetVar2(interp, "SHMskycam_Application", "moonsstat", TCL_GLOBAL_ONLY);
      strcpy(skycam_Application_ref->moonsstat,text);
      skycam_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"seeing_mass_Application") == 0) {
       seeing_mass_Application_cache *seeing_mass_Application_ref;
       seeing_mass_Application_ref = (seeing_mass_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMseeing_mass_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &seeing_mass_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Application", "Demand", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_mass_Application_ref->Demand);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Application", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_mass_Application_ref->Position);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Application", "Error", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_mass_Application_ref->Error);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(seeing_mass_Application_ref->Status,text);
      seeing_mass_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"system_Hardware_revision_history") == 0) {
       system_Hardware_revision_history_cache *system_Hardware_revision_history_ref;
       system_Hardware_revision_history_ref = (system_Hardware_revision_history_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMsystem_Hardware_revision_history", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &system_Hardware_revision_history_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMsystem_Hardware_revision_history", "Component", TCL_GLOBAL_ONLY);
      strcpy(system_Hardware_revision_history_ref->Component,text);

      text = Tcl_GetVar2(interp, "SHMsystem_Hardware_revision_history", "Reason", TCL_GLOBAL_ONLY);
      strcpy(system_Hardware_revision_history_ref->Reason,text);

      text = Tcl_GetVar2(interp, "SHMsystem_Hardware_revision_history", "Version", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &system_Hardware_revision_history_ref->Version);
      system_Hardware_revision_history_ref->syncO = 1;
    }

    if (strcmp(subsysid,"system_Computer_status") == 0) {
       system_Computer_status_cache *system_Computer_status_ref;
       system_Computer_status_ref = (system_Computer_status_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMsystem_Computer_status", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &system_Computer_status_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMsystem_Computer_status", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &system_Computer_status_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMsystem_Computer_status", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &system_Computer_status_ref->Calibrated);
      system_Computer_status_ref->syncO = 1;
    }

    if (strcmp(subsysid,"auxscope_Camera") == 0) {
       auxscope_Camera_cache *auxscope_Camera_ref;
       auxscope_Camera_ref = (auxscope_Camera_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMauxscope_Camera", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &auxscope_Camera_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMauxscope_Camera", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Camera_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMauxscope_Camera", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &auxscope_Camera_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMauxscope_Camera", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Camera_ref->Status);
      auxscope_Camera_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_SCU") == 0) {
       camera_SCU_cache *camera_SCU_ref;
       camera_SCU_ref = (camera_SCU_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_SCU", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_SCU_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_SCU", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_SCU_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_SCU", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_SCU_ref->Position);

      text = Tcl_GetVar2(interp, "SHMcamera_SCU", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_SCU_ref->Status);
      camera_SCU_ref->syncO = 1;
    }

    if (strcmp(subsysid,"system_Software_revision_history") == 0) {
       system_Software_revision_history_cache *system_Software_revision_history_ref;
       system_Software_revision_history_ref = (system_Software_revision_history_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMsystem_Software_revision_history", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &system_Software_revision_history_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMsystem_Software_revision_history", "Module", TCL_GLOBAL_ONLY);
      strcpy(system_Software_revision_history_ref->Module,text);

      text = Tcl_GetVar2(interp, "SHMsystem_Software_revision_history", "Notes", TCL_GLOBAL_ONLY);
      strcpy(system_Software_revision_history_ref->Notes,text);

      text = Tcl_GetVar2(interp, "SHMsystem_Software_revision_history", "Version", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &system_Software_revision_history_ref->Version);
      system_Software_revision_history_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m1_Surface") == 0) {
       m1_Surface_cache *m1_Surface_ref;
       m1_Surface_ref = (m1_Surface_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm1_Surface", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m1_Surface_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm1_Surface", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Surface_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm1_Surface", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m1_Surface_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm1_Surface", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Surface_ref->Status);
      m1_Surface_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_T2S") == 0) {
       camera_T2S_cache *camera_T2S_ref;
       camera_T2S_ref = (camera_T2S_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_T2S", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_T2S_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_T2S", "HeaterRaw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_T2S_ref->HeaterRaw);

      text = Tcl_GetVar2(interp, "SHMcamera_T2S", "HeaterCalibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_T2S_ref->HeaterCalibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_T2S", "HeaterStatus", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_T2S_ref->HeaterStatus);
      camera_T2S_ref->syncO = 1;
    }

    if (strcmp(subsysid,"environment_Weather") == 0) {
       environment_Weather_cache *environment_Weather_ref;
       environment_Weather_ref = (environment_Weather_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenvironment_Weather", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &environment_Weather_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenvironment_Weather", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Weather_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenvironment_Weather", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &environment_Weather_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenvironment_Weather", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Weather_ref->Status);
      environment_Weather_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_FEE") == 0) {
       camera_FEE_cache *camera_FEE_ref;
       camera_FEE_ref = (camera_FEE_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_FEE", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_FEE_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_FEE", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_FEE_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_FEE", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_FEE_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_FEE", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_FEE_ref->Status);
      camera_FEE_ref->syncO = 1;
    }

    if (strcmp(subsysid,"mount_Electrical") == 0) {
       mount_Electrical_cache *mount_Electrical_ref;
       mount_Electrical_ref = (mount_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMmount_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &mount_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMmount_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMmount_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &mount_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMmount_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Electrical_ref->Status);
      mount_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m1_Electrical") == 0) {
       m1_Electrical_cache *m1_Electrical_ref;
       m1_Electrical_ref = (m1_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm1_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m1_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm1_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm1_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m1_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm1_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Electrical_ref->Status);
      m1_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_PointingControl") == 0) {
       tcs_kernel_PointingControl_cache *tcs_kernel_PointingControl_ref;
       tcs_kernel_PointingControl_ref = (tcs_kernel_PointingControl_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingControl", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_PointingControl_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingControl", "RollFilter", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingControl_ref->RollFilter,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingControl", "PitchFilter", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingControl_ref->PitchFilter,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingControl", "AGuide", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingControl_ref->AGuide);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingControl", "BGuide", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingControl_ref->BGuide);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingControl", "ALocal", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingControl_ref->ALocal);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingControl", "BLocal", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingControl_ref->BLocal);
      tcs_kernel_PointingControl_ref->syncO = 1;
    }

    if (strcmp(subsysid,"environment_Lightning_detector") == 0) {
       environment_Lightning_detector_cache *environment_Lightning_detector_ref;
       environment_Lightning_detector_ref = (environment_Lightning_detector_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenvironment_Lightning_detector", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &environment_Lightning_detector_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenvironment_Lightning_detector", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Lightning_detector_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenvironment_Lightning_detector", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &environment_Lightning_detector_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenvironment_Lightning_detector", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Lightning_detector_ref->Status);
      environment_Lightning_detector_ref->syncO = 1;
    }

    if (strcmp(subsysid,"auxscope_Application") == 0) {
       auxscope_Application_cache *auxscope_Application_ref;
       auxscope_Application_ref = (auxscope_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMauxscope_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &auxscope_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMauxscope_Application", "Demand", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &auxscope_Application_ref->Demand);

      text = Tcl_GetVar2(interp, "SHMauxscope_Application", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &auxscope_Application_ref->Position);

      text = Tcl_GetVar2(interp, "SHMauxscope_Application", "Error", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &auxscope_Application_ref->Error);

      text = Tcl_GetVar2(interp, "SHMauxscope_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(auxscope_Application_ref->Status,text);
      auxscope_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"power_UPSs") == 0) {
       power_UPSs_cache *power_UPSs_ref;
       power_UPSs_ref = (power_UPSs_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMpower_UPSs", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &power_UPSs_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMpower_UPSs", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &power_UPSs_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMpower_UPSs", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &power_UPSs_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMpower_UPSs", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &power_UPSs_ref->Status);
      power_UPSs_ref->syncO = 1;
    }

    if (strcmp(subsysid,"enclosure_Azimuth") == 0) {
       enclosure_Azimuth_cache *enclosure_Azimuth_ref;
       enclosure_Azimuth_ref = (enclosure_Azimuth_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenclosure_Azimuth", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &enclosure_Azimuth_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenclosure_Azimuth", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Azimuth_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenclosure_Azimuth", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Azimuth_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenclosure_Azimuth", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Azimuth_ref->Status);
      enclosure_Azimuth_ref->syncO = 1;
    }

    if (strcmp(subsysid,"environment_Seismometer") == 0) {
       environment_Seismometer_cache *environment_Seismometer_ref;
       environment_Seismometer_ref = (environment_Seismometer_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenvironment_Seismometer", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &environment_Seismometer_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenvironment_Seismometer", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Seismometer_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenvironment_Seismometer", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &environment_Seismometer_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenvironment_Seismometer", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Seismometer_ref->Status);
      environment_Seismometer_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_WFS") == 0) {
       camera_WFS_cache *camera_WFS_ref;
       camera_WFS_ref = (camera_WFS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_WFS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_WFS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_WFS", "Metadata", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_WFS_ref->Metadata);

      text = Tcl_GetVar2(interp, "SHMcamera_WFS", "Results", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_WFS_ref->Results);

      text = Tcl_GetVar2(interp, "SHMcamera_WFS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_WFS_ref->Status);
      camera_WFS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"calibration_Electrical") == 0) {
       calibration_Electrical_cache *calibration_Electrical_ref;
       calibration_Electrical_ref = (calibration_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcalibration_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &calibration_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcalibration_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &calibration_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcalibration_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &calibration_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcalibration_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &calibration_Electrical_ref->Status);
      calibration_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"mount_Temps") == 0) {
       mount_Temps_cache *mount_Temps_ref;
       mount_Temps_ref = (mount_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMmount_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &mount_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMmount_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMmount_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &mount_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMmount_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Temps_ref->Health);
      mount_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"seeing_mass_Electrical") == 0) {
       seeing_mass_Electrical_cache *seeing_mass_Electrical_ref;
       seeing_mass_Electrical_ref = (seeing_mass_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMseeing_mass_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &seeing_mass_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_mass_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_mass_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_mass_Electrical_ref->Status);
      seeing_mass_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"enclosure_Metrology") == 0) {
       enclosure_Metrology_cache *enclosure_Metrology_ref;
       enclosure_Metrology_ref = (enclosure_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenclosure_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &enclosure_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenclosure_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenclosure_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenclosure_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMenclosure_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Metrology_ref->Status);
      enclosure_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"mount_Az") == 0) {
       mount_Az_cache *mount_Az_ref;
       mount_Az_ref = (mount_Az_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMmount_Az", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &mount_Az_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMmount_Az", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Az_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMmount_Az", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &mount_Az_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMmount_Az", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Az_ref->Status);
      mount_Az_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_FK5Target") == 0) {
       tcs_kernel_FK5Target_cache *tcs_kernel_FK5Target_ref;
       tcs_kernel_FK5Target_ref = (tcs_kernel_FK5Target_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_FK5Target", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_FK5Target_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_FK5Target", "ra", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_FK5Target_ref->ra);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_FK5Target", "dec", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_FK5Target_ref->dec);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_FK5Target", "equinox", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_FK5Target_ref->equinox);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_FK5Target", "epoc", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_FK5Target_ref->epoc);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_FK5Target", "pmRA", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_FK5Target_ref->pmRA);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_FK5Target", "pmDec", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_FK5Target_ref->pmDec);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_FK5Target", "parallax", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_FK5Target_ref->parallax);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_FK5Target", "rv", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_FK5Target_ref->rv);
      tcs_kernel_FK5Target_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_FCS") == 0) {
       camera_FCS_cache *camera_FCS_ref;
       camera_FCS_ref = (camera_FCS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_FCS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_FCS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_FCS", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_FCS_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_FCS", "Positions", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_FCS_ref->Positions);

      text = Tcl_GetVar2(interp, "SHMcamera_FCS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_FCS_ref->Status);
      camera_FCS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"environment_Temps") == 0) {
       environment_Temps_cache *environment_Temps_ref;
       environment_Temps_ref = (environment_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenvironment_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &environment_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenvironment_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenvironment_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &environment_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenvironment_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Temps_ref->Health);
      environment_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_PointingModel") == 0) {
       tcs_kernel_PointingModel_cache *tcs_kernel_PointingModel_ref;
       tcs_kernel_PointingModel_ref = (tcs_kernel_PointingModel_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_PointingModel_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Model", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &tcs_kernel_PointingModel_ref->Model);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeffv", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingModel_ref->Coeffv);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Nterml", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &tcs_kernel_PointingModel_ref->Nterml);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Ntermx", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &tcs_kernel_PointingModel_ref->Ntermx);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Nterms", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &tcs_kernel_PointingModel_ref->Nterms);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeff1", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Coeff1,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeff2", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Coeff2,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeff3", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Coeff3,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeff4", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Coeff4,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeff5", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Coeff5,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeff6", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Coeff6,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeff7", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Coeff7,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeff8", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Coeff8,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Coeff9", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Coeff9,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Cofor1", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Cofor1,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Cofor2", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Cofor2,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Cofor3", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Cofor3,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Cofor4", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Cofor4,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Cofor5", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Cofor5,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Cofor6", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Cofor6,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Cofor7", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Cofor7,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Cofor8", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Cofor8,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingModel", "Cofor9", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_PointingModel_ref->Cofor9,text);
      tcs_kernel_PointingModel_ref->syncO = 1;
    }

    if (strcmp(subsysid,"enclosure_Application") == 0) {
       enclosure_Application_cache *enclosure_Application_ref;
       enclosure_Application_ref = (enclosure_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenclosure_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &enclosure_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenclosure_Application", "Demand", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Application_ref->Demand);

      text = Tcl_GetVar2(interp, "SHMenclosure_Application", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Application_ref->Position);

      text = Tcl_GetVar2(interp, "SHMenclosure_Application", "Error", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Application_ref->Error);

      text = Tcl_GetVar2(interp, "SHMenclosure_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(enclosure_Application_ref->Status,text);
      enclosure_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m1_Support") == 0) {
       m1_Support_cache *m1_Support_ref;
       m1_Support_ref = (m1_Support_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm1_Support", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m1_Support_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm1_Support", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Support_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm1_Support", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m1_Support_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm1_Support", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Support_ref->Status);
      m1_Support_ref->syncO = 1;
    }

    if (strcmp(subsysid,"power_Electrical") == 0) {
       power_Electrical_cache *power_Electrical_ref;
       power_Electrical_ref = (power_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMpower_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &power_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMpower_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &power_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMpower_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &power_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMpower_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &power_Electrical_ref->Status);
      power_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m3_Surface") == 0) {
       m3_Surface_cache *m3_Surface_ref;
       m3_Surface_ref = (m3_Surface_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm3_Surface", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m3_Surface_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm3_Surface", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Surface_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm3_Surface", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m3_Surface_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm3_Surface", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Surface_ref->Status);
      m3_Surface_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_GS") == 0) {
       camera_GS_cache *camera_GS_ref;
       camera_GS_ref = (camera_GS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_GS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_GS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_GS", "Profiles", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_GS_ref->Profiles);

      text = Tcl_GetVar2(interp, "SHMcamera_GS", "Fits", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_GS_ref->Fits);

      text = Tcl_GetVar2(interp, "SHMcamera_GS", "Centroids", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_GS_ref->Centroids);

      text = Tcl_GetVar2(interp, "SHMcamera_GS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_GS_ref->Status);
      camera_GS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"seeing_dimm_Electrical") == 0) {
       seeing_dimm_Electrical_cache *seeing_dimm_Electrical_ref;
       seeing_dimm_Electrical_ref = (seeing_dimm_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &seeing_dimm_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_dimm_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_dimm_Electrical_ref->Status);
      seeing_dimm_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_T4U") == 0) {
       camera_T4U_cache *camera_T4U_ref;
       camera_T4U_ref = (camera_T4U_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_T4U", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_T4U_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_T4U", "HeaterRaw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_T4U_ref->HeaterRaw);

      text = Tcl_GetVar2(interp, "SHMcamera_T4U", "HeaterCalibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_T4U_ref->HeaterCalibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_T4U", "HeaterStatus", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_T4U_ref->HeaterStatus);
      camera_T4U_ref->syncO = 1;
    }

    if (strcmp(subsysid,"skycam_Electrical") == 0) {
       skycam_Electrical_cache *skycam_Electrical_ref;
       skycam_Electrical_ref = (skycam_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMskycam_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &skycam_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMskycam_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &skycam_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMskycam_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &skycam_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMskycam_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &skycam_Electrical_ref->Status);
      skycam_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"scheduler_Application") == 0) {
       scheduler_Application_cache *scheduler_Application_ref;
       scheduler_Application_ref = (scheduler_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMscheduler_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &scheduler_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMscheduler_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(scheduler_Application_ref->Status,text);

      text = Tcl_GetVar2(interp, "SHMscheduler_Application", "data", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &scheduler_Application_ref->data);
      scheduler_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_SAS") == 0) {
       camera_SAS_cache *camera_SAS_ref;
       camera_SAS_ref = (camera_SAS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_SAS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_SAS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_SAS", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_SAS_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_SAS", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_SAS_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_SAS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_SAS_ref->Status);
      camera_SAS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_TC") == 0) {
       camera_TC_cache *camera_TC_ref;
       camera_TC_ref = (camera_TC_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_TC", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_TC_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_TC", "HeaterRaw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_TC_ref->HeaterRaw);

      text = Tcl_GetVar2(interp, "SHMcamera_TC", "HeaterCalibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_TC_ref->HeaterCalibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_TC", "HeaterStatus", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_TC_ref->HeaterStatus);
      camera_TC_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_CCS") == 0) {
       camera_CCS_cache *camera_CCS_ref;
       camera_CCS_ref = (camera_CCS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_CCS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_CCS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_CCS", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_CCS_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_CCS", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_CCS_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_CCS", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_CCS_ref->Health);
      camera_CCS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"calibration_Temps") == 0) {
       calibration_Temps_cache *calibration_Temps_ref;
       calibration_Temps_ref = (calibration_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcalibration_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &calibration_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcalibration_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &calibration_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcalibration_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &calibration_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcalibration_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &calibration_Temps_ref->Health);
      calibration_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m2_Surface") == 0) {
       m2_Surface_cache *m2_Surface_ref;
       m2_Surface_ref = (m2_Surface_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm2_Surface", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m2_Surface_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm2_Surface", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Surface_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm2_Surface", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m2_Surface_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm2_Surface", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Surface_ref->Status);
      m2_Surface_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_OpticsVt") == 0) {
       tcs_kernel_OpticsVt_cache *tcs_kernel_OpticsVt_ref;
       tcs_kernel_OpticsVt_ref = (tcs_kernel_OpticsVt_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_OpticsVt", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_OpticsVt_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_OpticsVt", "tip", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_OpticsVt_ref->tip);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_OpticsVt", "tilt", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_OpticsVt_ref->tilt);
      tcs_kernel_OpticsVt_ref->syncO = 1;
    }

    if (strcmp(subsysid,"auxscope_Metrology") == 0) {
       auxscope_Metrology_cache *auxscope_Metrology_ref;
       auxscope_Metrology_ref = (auxscope_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMauxscope_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &auxscope_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMauxscope_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMauxscope_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &auxscope_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMauxscope_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMauxscope_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Metrology_ref->Status);
      auxscope_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_SDS") == 0) {
       camera_SDS_cache *camera_SDS_ref;
       camera_SDS_ref = (camera_SDS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_SDS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_SDS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_SDS", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_SDS_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_SDS", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_SDS_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_SDS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_SDS_ref->Status);
      camera_SDS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"enclosure_Shutter") == 0) {
       enclosure_Shutter_cache *enclosure_Shutter_ref;
       enclosure_Shutter_ref = (enclosure_Shutter_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenclosure_Shutter", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &enclosure_Shutter_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenclosure_Shutter", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Shutter_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenclosure_Shutter", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Shutter_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenclosure_Shutter", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Shutter_ref->Status);
      enclosure_Shutter_ref->syncO = 1;
    }

    if (strcmp(subsysid,"lasercal_Electrical") == 0) {
       lasercal_Electrical_cache *lasercal_Electrical_ref;
       lasercal_Electrical_ref = (lasercal_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMlasercal_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &lasercal_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMlasercal_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &lasercal_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMlasercal_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &lasercal_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMlasercal_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &lasercal_Electrical_ref->Status);
      lasercal_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"auxscope_Spectrometer") == 0) {
       auxscope_Spectrometer_cache *auxscope_Spectrometer_ref;
       auxscope_Spectrometer_ref = (auxscope_Spectrometer_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMauxscope_Spectrometer", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &auxscope_Spectrometer_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMauxscope_Spectrometer", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Spectrometer_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMauxscope_Spectrometer", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &auxscope_Spectrometer_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMauxscope_Spectrometer", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Spectrometer_ref->Status);
      auxscope_Spectrometer_ref->syncO = 1;
    }

    if (strcmp(subsysid,"environment_Electrical") == 0) {
       environment_Electrical_cache *environment_Electrical_ref;
       environment_Electrical_ref = (environment_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenvironment_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &environment_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenvironment_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenvironment_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &environment_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenvironment_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Electrical_ref->Status);
      environment_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"mount_Application") == 0) {
       mount_Application_cache *mount_Application_ref;
       mount_Application_ref = (mount_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMmount_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &mount_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMmount_Application", "Demand", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &mount_Application_ref->Demand);

      text = Tcl_GetVar2(interp, "SHMmount_Application", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &mount_Application_ref->Position);

      text = Tcl_GetVar2(interp, "SHMmount_Application", "Error", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &mount_Application_ref->Error);

      text = Tcl_GetVar2(interp, "SHMmount_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(mount_Application_ref->Status,text);
      mount_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m3_Application") == 0) {
       m3_Application_cache *m3_Application_ref;
       m3_Application_ref = (m3_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm3_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m3_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm3_Application", "Demand", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m3_Application_ref->Demand);

      text = Tcl_GetVar2(interp, "SHMm3_Application", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m3_Application_ref->Position);

      text = Tcl_GetVar2(interp, "SHMm3_Application", "Error", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m3_Application_ref->Error);

      text = Tcl_GetVar2(interp, "SHMm3_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(m3_Application_ref->Status,text);
      m3_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_Target") == 0) {
       tcs_kernel_Target_cache *tcs_kernel_Target_ref;
       tcs_kernel_Target_ref = (tcs_kernel_Target_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_Target_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "site", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_Target_ref->site,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "t0", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->t0);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "az", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->az);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "el", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->el);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "azdot", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->azdot);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "eldot", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->eldot);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Wavel", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Wavel);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "XOffset", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->XOffset);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "YOffset", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->YOffset);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "OffSys", TCL_GLOBAL_ONLY);
      strcpy(tcs_kernel_Target_ref->OffSys,text);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "focalplaneX", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->focalplaneX);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "focalplaneY", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->focalplaneY);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Temp", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Temp);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Press", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Press);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Humid", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Humid);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "TLR", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->TLR);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Target", "Tai", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Target_ref->Tai);
      tcs_kernel_Target_ref->syncO = 1;
    }

    if (strcmp(subsysid,"seeing_dimm_Temps") == 0) {
       seeing_dimm_Temps_cache *seeing_dimm_Temps_ref;
       seeing_dimm_Temps_ref = (seeing_dimm_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &seeing_dimm_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_dimm_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_dimm_Temps_ref->Health);
      seeing_dimm_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_Site") == 0) {
       tcs_kernel_Site_cache *tcs_kernel_Site_ref;
       tcs_kernel_Site_ref = (tcs_kernel_Site_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_Site_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "tai", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->tai);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "delat", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->delat);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "delut", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->delut);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "ttmtat", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->ttmtat);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "elongm", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->elongm);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "latm", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->latm);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "hm", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->hm);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "xpm", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->xpm);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "ypm", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->ypm);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Delut", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Delut);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Delat", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Delat);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Ttmtai", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Ttmtai);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Elong", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Elong);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Lat", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Lat);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Uau", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Uau);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Vau", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Vau);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Ukm", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Ukm);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Vkm", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Vkm);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Diurab", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Diurab);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "T0", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->T0);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "St0", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->St0);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Tt0", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Tt0);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Ttj", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Ttj);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Amprms", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Amprms);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Aoprms", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Aoprms);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Refa", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Refa);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Refb", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Refb);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_Site", "Daz", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_Site_ref->Daz);
      tcs_kernel_Site_ref->syncO = 1;
    }

    if (strcmp(subsysid,"seeing_dimm_Application") == 0) {
       seeing_dimm_Application_cache *seeing_dimm_Application_ref;
       seeing_dimm_Application_ref = (seeing_dimm_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &seeing_dimm_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "target", TCL_GLOBAL_ONLY);
      strcpy(seeing_dimm_Application_ref->target,text);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "magnitude", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->magnitude);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "exposure", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->exposure);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "ccdtemp", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->ccdtemp);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "ambtemp", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->ambtemp);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "seeing", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->seeing);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "strehl", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->strehl);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "dx", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->dx);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "fwhm1", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->fwhm1);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "fwhm1_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->fwhm1_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "fwhm1_y", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->fwhm1_y);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "flux1", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->flux1);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "noise1_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->noise1_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "scint1_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->scint1_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "ascint1_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->ascint1_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "strehl1a_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->strehl1a_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "strehl1b_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->strehl1b_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "fwhm2", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->fwhm2);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "fwhm2_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->fwhm2_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "fwhm2_y", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->fwhm2_y);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "flux2", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->flux2);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "noise2_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->noise2_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "scint2_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->scint2_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "ascint2_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->ascint2_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "strehl2a_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->strehl2a_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "strehl2b_x", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Application_ref->strehl2b_x);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(seeing_dimm_Application_ref->Status,text);
      seeing_dimm_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"operations_Application") == 0) {
       operations_Application_cache *operations_Application_ref;
       operations_Application_ref = (operations_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMoperations_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &operations_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMoperations_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(operations_Application_ref->Status,text);

      text = Tcl_GetVar2(interp, "SHMoperations_Application", "data", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &operations_Application_ref->data);
      operations_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_GAS") == 0) {
       camera_GAS_cache *camera_GAS_ref;
       camera_GAS_ref = (camera_GAS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_GAS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_GAS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_GAS", "Metadata", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_GAS_ref->Metadata);

      text = Tcl_GetVar2(interp, "SHMcamera_GAS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_GAS_ref->Status);
      camera_GAS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"skycam_Metrology") == 0) {
       skycam_Metrology_cache *skycam_Metrology_ref;
       skycam_Metrology_ref = (skycam_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMskycam_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &skycam_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMskycam_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &skycam_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMskycam_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &skycam_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMskycam_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &skycam_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMskycam_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &skycam_Metrology_ref->Status);
      skycam_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_TrackRefSys") == 0) {
       tcs_kernel_TrackRefSys_cache *tcs_kernel_TrackRefSys_ref;
       tcs_kernel_TrackRefSys_ref = (tcs_kernel_TrackRefSys_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_TrackRefSys_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "tdbj", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->tdbj);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "amprms", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->amprms);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "ae2mt", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->ae2mt);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "hm", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->hm);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "tlat", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->tlat);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "diurab", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->diurab);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "refa", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->refa);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "refb", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->refb);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "temp", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->temp);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "press", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->press);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "humid", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->humid);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "tlr", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->tlr);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "wavel", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->wavel);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "sst", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->sst);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackRefSys", "cst", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackRefSys_ref->cst);
      tcs_kernel_TrackRefSys_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_VCS") == 0) {
       camera_VCS_cache *camera_VCS_ref;
       camera_VCS_ref = (camera_VCS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_VCS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_VCS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_VCS", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_VCS_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_VCS", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_VCS_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_VCS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_VCS_ref->Status);
      camera_VCS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"lasercal_Temps") == 0) {
       lasercal_Temps_cache *lasercal_Temps_ref;
       lasercal_Temps_ref = (lasercal_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMlasercal_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &lasercal_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMlasercal_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &lasercal_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMlasercal_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &lasercal_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMlasercal_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &lasercal_Temps_ref->Health);
      lasercal_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"mount_Rotator") == 0) {
       mount_Rotator_cache *mount_Rotator_ref;
       mount_Rotator_ref = (mount_Rotator_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMmount_Rotator", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &mount_Rotator_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMmount_Rotator", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Rotator_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMmount_Rotator", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &mount_Rotator_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMmount_Rotator", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &mount_Rotator_ref->Status);
      mount_Rotator_ref->syncO = 1;
    }

    if (strcmp(subsysid,"calibration_Application") == 0) {
       calibration_Application_cache *calibration_Application_ref;
       calibration_Application_ref = (calibration_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcalibration_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &calibration_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcalibration_Application", "Demand", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &calibration_Application_ref->Demand);

      text = Tcl_GetVar2(interp, "SHMcalibration_Application", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &calibration_Application_ref->Position);

      text = Tcl_GetVar2(interp, "SHMcalibration_Application", "Error", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &calibration_Application_ref->Error);

      text = Tcl_GetVar2(interp, "SHMcalibration_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(calibration_Application_ref->Status,text);
      calibration_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"seeing_dimm_Metrology") == 0) {
       seeing_dimm_Metrology_cache *seeing_dimm_Metrology_ref;
       seeing_dimm_Metrology_ref = (seeing_dimm_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &seeing_dimm_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_dimm_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_dimm_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_dimm_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMseeing_dimm_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_dimm_Metrology_ref->Status);
      seeing_dimm_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_BEE") == 0) {
       camera_BEE_cache *camera_BEE_ref;
       camera_BEE_ref = (camera_BEE_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_BEE", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_BEE_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_BEE", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_BEE_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_BEE", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_BEE_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_BEE", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_BEE_ref->Status);
      camera_BEE_ref->syncO = 1;
    }

    if (strcmp(subsysid,"auxscope_Electrical") == 0) {
       auxscope_Electrical_cache *auxscope_Electrical_ref;
       auxscope_Electrical_ref = (auxscope_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMauxscope_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &auxscope_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMauxscope_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMauxscope_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &auxscope_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMauxscope_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &auxscope_Electrical_ref->Status);
      auxscope_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_T1S") == 0) {
       camera_T1S_cache *camera_T1S_ref;
       camera_T1S_ref = (camera_T1S_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_T1S", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_T1S_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_T1S", "HeaterRaw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_T1S_ref->HeaterRaw);

      text = Tcl_GetVar2(interp, "SHMcamera_T1S", "HeaterCalibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_T1S_ref->HeaterCalibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_T1S", "HeaterStatus", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_T1S_ref->HeaterStatus);
      camera_T1S_ref->syncO = 1;
    }

    if (strcmp(subsysid,"environment_Dust_monitor") == 0) {
       environment_Dust_monitor_cache *environment_Dust_monitor_ref;
       environment_Dust_monitor_ref = (environment_Dust_monitor_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenvironment_Dust_monitor", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &environment_Dust_monitor_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenvironment_Dust_monitor", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Dust_monitor_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenvironment_Dust_monitor", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &environment_Dust_monitor_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenvironment_Dust_monitor", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Dust_monitor_ref->Status);
      environment_Dust_monitor_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_DawdleFilter") == 0) {
       tcs_kernel_DawdleFilter_cache *tcs_kernel_DawdleFilter_ref;
       tcs_kernel_DawdleFilter_ref = (tcs_kernel_DawdleFilter_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_DawdleFilter", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_DawdleFilter_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_DawdleFilter", "Bypass", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &tcs_kernel_DawdleFilter_ref->Bypass);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_DawdleFilter", "T", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_DawdleFilter_ref->T);
      tcs_kernel_DawdleFilter_ref->syncO = 1;
    }

    if (strcmp(subsysid,"enclosure_Temps") == 0) {
       enclosure_Temps_cache *enclosure_Temps_ref;
       enclosure_Temps_ref = (enclosure_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenclosure_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &enclosure_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenclosure_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenclosure_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenclosure_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Temps_ref->Health);
      enclosure_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"environment_Video_cameras") == 0) {
       environment_Video_cameras_cache *environment_Video_cameras_ref;
       environment_Video_cameras_ref = (environment_Video_cameras_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenvironment_Video_cameras", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &environment_Video_cameras_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenvironment_Video_cameras", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Video_cameras_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenvironment_Video_cameras", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &environment_Video_cameras_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenvironment_Video_cameras", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &environment_Video_cameras_ref->Status);
      environment_Video_cameras_ref->syncO = 1;
    }

    if (strcmp(subsysid,"skycam_Temps") == 0) {
       skycam_Temps_cache *skycam_Temps_ref;
       skycam_Temps_ref = (skycam_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMskycam_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &skycam_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMskycam_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &skycam_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMskycam_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &skycam_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMskycam_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &skycam_Temps_ref->Health);
      skycam_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m2_Hexapod") == 0) {
       m2_Hexapod_cache *m2_Hexapod_ref;
       m2_Hexapod_ref = (m2_Hexapod_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm2_Hexapod", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m2_Hexapod_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm2_Hexapod", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Hexapod_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm2_Hexapod", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m2_Hexapod_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm2_Hexapod", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Hexapod_ref->Status);
      m2_Hexapod_ref->syncO = 1;
    }

    if (strcmp(subsysid,"lasercal_Application") == 0) {
       lasercal_Application_cache *lasercal_Application_ref;
       lasercal_Application_ref = (lasercal_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMlasercal_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &lasercal_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMlasercal_Application", "Demand", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &lasercal_Application_ref->Demand);

      text = Tcl_GetVar2(interp, "SHMlasercal_Application", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &lasercal_Application_ref->Position);

      text = Tcl_GetVar2(interp, "SHMlasercal_Application", "Error", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &lasercal_Application_ref->Error);

      text = Tcl_GetVar2(interp, "SHMlasercal_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(lasercal_Application_ref->Status,text);
      lasercal_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m3_Support") == 0) {
       m3_Support_cache *m3_Support_ref;
       m3_Support_ref = (m3_Support_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm3_Support", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m3_Support_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm3_Support", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Support_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm3_Support", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m3_Support_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm3_Support", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Support_ref->Status);
      m3_Support_ref->syncO = 1;
    }

    if (strcmp(subsysid,"camera_RAS") == 0) {
       camera_RAS_cache *camera_RAS_ref;
       camera_RAS_ref = (camera_RAS_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMcamera_RAS", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &camera_RAS_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMcamera_RAS", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_RAS_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMcamera_RAS", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &camera_RAS_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMcamera_RAS", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_RAS_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMcamera_RAS", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &camera_RAS_ref->Status);
      camera_RAS_ref->syncO = 1;
    }

    if (strcmp(subsysid,"seeing_mass_Temps") == 0) {
       seeing_mass_Temps_cache *seeing_mass_Temps_ref;
       seeing_mass_Temps_ref = (seeing_mass_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMseeing_mass_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &seeing_mass_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_mass_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &seeing_mass_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMseeing_mass_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &seeing_mass_Temps_ref->Health);
      seeing_mass_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_TrackingTarget") == 0) {
       tcs_kernel_TrackingTarget_cache *tcs_kernel_TrackingTarget_ref;
       tcs_kernel_TrackingTarget_ref = (tcs_kernel_TrackingTarget_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackingTarget", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_TrackingTarget_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackingTarget", "PositionX", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackingTarget_ref->PositionX);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackingTarget", "PositionY", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackingTarget_ref->PositionY);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackingTarget", "T0", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackingTarget_ref->T0);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackingTarget", "VelocityX", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackingTarget_ref->VelocityX);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_TrackingTarget", "VelocityY", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_TrackingTarget_ref->VelocityY);
      tcs_kernel_TrackingTarget_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m3_Temps") == 0) {
       m3_Temps_cache *m3_Temps_ref;
       m3_Temps_ref = (m3_Temps_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm3_Temps", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m3_Temps_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm3_Temps", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Temps_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm3_Temps", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m3_Temps_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm3_Temps", "Health", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Temps_ref->Health);
      m3_Temps_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m3_Actuators") == 0) {
       m3_Actuators_cache *m3_Actuators_ref;
       m3_Actuators_ref = (m3_Actuators_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm3_Actuators", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m3_Actuators_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm3_Actuators", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Actuators_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm3_Actuators", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m3_Actuators_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm3_Actuators", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m3_Actuators_ref->Status);
      m3_Actuators_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m2_Application") == 0) {
       m2_Application_cache *m2_Application_ref;
       m2_Application_ref = (m2_Application_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm2_Application", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m2_Application_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm2_Application", "Demand", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m2_Application_ref->Demand);

      text = Tcl_GetVar2(interp, "SHMm2_Application", "Position", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m2_Application_ref->Position);

      text = Tcl_GetVar2(interp, "SHMm2_Application", "Error", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m2_Application_ref->Error);

      text = Tcl_GetVar2(interp, "SHMm2_Application", "Status", TCL_GLOBAL_ONLY);
      strcpy(m2_Application_ref->Status,text);
      m2_Application_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m1_Metrology") == 0) {
       m1_Metrology_cache *m1_Metrology_ref;
       m1_Metrology_ref = (m1_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm1_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m1_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm1_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm1_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m1_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm1_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMm1_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m1_Metrology_ref->Status);
      m1_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"enclosure_Electrical") == 0) {
       enclosure_Electrical_cache *enclosure_Electrical_ref;
       enclosure_Electrical_ref = (enclosure_Electrical_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenclosure_Electrical", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &enclosure_Electrical_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenclosure_Electrical", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Electrical_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenclosure_Electrical", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Electrical_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenclosure_Electrical", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Electrical_ref->Status);
      enclosure_Electrical_ref->syncO = 1;
    }

    if (strcmp(subsysid,"m2_Metrology") == 0) {
       m2_Metrology_cache *m2_Metrology_ref;
       m2_Metrology_ref = (m2_Metrology_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMm2_Metrology", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &m2_Metrology_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMm2_Metrology", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Metrology_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMm2_Metrology", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &m2_Metrology_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMm2_Metrology", "Limits", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Metrology_ref->Limits);

      text = Tcl_GetVar2(interp, "SHMm2_Metrology", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &m2_Metrology_ref->Status);
      m2_Metrology_ref->syncO = 1;
    }

    if (strcmp(subsysid,"enclosure_Vents") == 0) {
       enclosure_Vents_cache *enclosure_Vents_ref;
       enclosure_Vents_ref = (enclosure_Vents_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMenclosure_Vents", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &enclosure_Vents_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMenclosure_Vents", "Raw", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Vents_ref->Raw);

      text = Tcl_GetVar2(interp, "SHMenclosure_Vents", "Calibrated", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &enclosure_Vents_ref->Calibrated);

      text = Tcl_GetVar2(interp, "SHMenclosure_Vents", "Status", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &enclosure_Vents_ref->Status);
      enclosure_Vents_ref->syncO = 1;
    }

    if (strcmp(subsysid,"tcs_kernel_PointingLog") == 0) {
       tcs_kernel_PointingLog_cache *tcs_kernel_PointingLog_ref;
       tcs_kernel_PointingLog_ref = (tcs_kernel_PointingLog_cache *)shmdata_ref;


      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "syncI", TCL_GLOBAL_ONLY);
      sscanf(text,"%d", &tcs_kernel_PointingLog_ref->syncI);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Ra", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Ra);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Dec", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Dec);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Wavel", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Wavel);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Roll", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Roll);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Pitch", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Pitch);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Casspa", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Casspa);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Xr", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Xr);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Yr", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Yr);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Fl", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Fl);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Temp", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Temp);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Press", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Press);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Humid", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Humid);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Tlr", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Tlr);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Rcorr", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Rcorr);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Aux", TCL_GLOBAL_ONLY);
      sscanf(text,"%f", &tcs_kernel_PointingLog_ref->Aux);

      text = Tcl_GetVar2(interp, "SHMtcs_kernel_PointingLog", "Marked", TCL_GLOBAL_ONLY);
      sscanf(text,"%ld", &tcs_kernel_PointingLog_ref->Marked);
      tcs_kernel_PointingLog_ref->syncO = 1;
    }

    return TCL_OK;
}
