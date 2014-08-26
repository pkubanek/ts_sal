
/* Sample datastream reader , intended to be called automatically
   from svcSAL_receiveDatastream on arrival of new data.
   Remove cases for non-applicable datastreams and add 
   stream dependent processing code.
 */

#include "svcSAL.h"
#include "svcSAL_caches.h"

int svcSAL_test_datastreamCallback (char *subsystem, int *shmdata_ref ) {
   printf("%s command received",subsystem);


   if (strcmp("system_Computer_status",subsystem) == 0 ) {
     system_Computer_status_cache *system_Computer_status_ref;
     system_Computer_status_ref = (system_Computer_status_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     system_Computer_status_ref->syncI = 0;
   }



   if (strcmp("system_Software_revision_history",subsystem) == 0 ) {
     system_Software_revision_history_cache *system_Software_revision_history_ref;
     system_Software_revision_history_ref = (system_Software_revision_history_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     system_Software_revision_history_ref->syncI = 0;
   }



   if (strcmp("system_Hardware_revision_history",subsystem) == 0 ) {
     system_Hardware_revision_history_cache *system_Hardware_revision_history_ref;
     system_Hardware_revision_history_ref = (system_Hardware_revision_history_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     system_Hardware_revision_history_ref->syncI = 0;
   }



   if (strcmp("system_Command_history",subsystem) == 0 ) {
     system_Command_history_cache *system_Command_history_ref;
     system_Command_history_ref = (system_Command_history_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     system_Command_history_ref->syncI = 0;
   }



   if (strcmp("m1m3_TC",subsystem) == 0 ) {
     m1m3_TC_cache *m1m3_TC_ref;
     m1m3_TC_ref = (m1m3_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m1m3_TC_ref->syncI = 0;
   }



   if (strcmp("m1m3_Electrical",subsystem) == 0 ) {
     m1m3_Electrical_cache *m1m3_Electrical_ref;
     m1m3_Electrical_ref = (m1m3_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m1m3_Electrical_ref->syncI = 0;
   }



   if (strcmp("m1m3_Metrology",subsystem) == 0 ) {
     m1m3_Metrology_cache *m1m3_Metrology_ref;
     m1m3_Metrology_ref = (m1m3_Metrology_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m1m3_Metrology_ref->syncI = 0;
   }



   if (strcmp("m1m3_Application",subsystem) == 0 ) {
     m1m3_Application_cache *m1m3_Application_ref;
     m1m3_Application_ref = (m1m3_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m1m3_Application_ref->syncI = 0;
   }



   if (strcmp("m1m3_Support",subsystem) == 0 ) {
     m1m3_Support_cache *m1m3_Support_ref;
     m1m3_Support_ref = (m1m3_Support_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m1m3_Support_ref->syncI = 0;
   }



   if (strcmp("m1m3_Actuators",subsystem) == 0 ) {
     m1m3_Actuators_cache *m1m3_Actuators_ref;
     m1m3_Actuators_ref = (m1m3_Actuators_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m1m3_Actuators_ref->syncI = 0;
   }



   if (strcmp("m1m3_Surface",subsystem) == 0 ) {
     m1m3_Surface_cache *m1m3_Surface_ref;
     m1m3_Surface_ref = (m1m3_Surface_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m1m3_Surface_ref->syncI = 0;
   }



   if (strcmp("m2_TC",subsystem) == 0 ) {
     m2_TC_cache *m2_TC_ref;
     m2_TC_ref = (m2_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m2_TC_ref->syncI = 0;
   }



   if (strcmp("m2_Electrical",subsystem) == 0 ) {
     m2_Electrical_cache *m2_Electrical_ref;
     m2_Electrical_ref = (m2_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m2_Electrical_ref->syncI = 0;
   }



   if (strcmp("m2_Metrology",subsystem) == 0 ) {
     m2_Metrology_cache *m2_Metrology_ref;
     m2_Metrology_ref = (m2_Metrology_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m2_Metrology_ref->syncI = 0;
   }



   if (strcmp("m2_Application",subsystem) == 0 ) {
     m2_Application_cache *m2_Application_ref;
     m2_Application_ref = (m2_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m2_Application_ref->syncI = 0;
   }



   if (strcmp("m2_Hexapod",subsystem) == 0 ) {
     m2_Hexapod_cache *m2_Hexapod_ref;
     m2_Hexapod_ref = (m2_Hexapod_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m2_Hexapod_ref->syncI = 0;
   }



   if (strcmp("m2_Actuators",subsystem) == 0 ) {
     m2_Actuators_cache *m2_Actuators_ref;
     m2_Actuators_ref = (m2_Actuators_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m2_Actuators_ref->syncI = 0;
   }



   if (strcmp("m2_Surface",subsystem) == 0 ) {
     m2_Surface_cache *m2_Surface_ref;
     m2_Surface_ref = (m2_Surface_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     m2_Surface_ref->syncI = 0;
   }



   if (strcmp("mount_TC",subsystem) == 0 ) {
     mount_TC_cache *mount_TC_ref;
     mount_TC_ref = (mount_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     mount_TC_ref->syncI = 0;
   }



   if (strcmp("mount_Electrical",subsystem) == 0 ) {
     mount_Electrical_cache *mount_Electrical_ref;
     mount_Electrical_ref = (mount_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     mount_Electrical_ref->syncI = 0;
   }



   if (strcmp("mount_Metrology",subsystem) == 0 ) {
     mount_Metrology_cache *mount_Metrology_ref;
     mount_Metrology_ref = (mount_Metrology_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     mount_Metrology_ref->syncI = 0;
   }



   if (strcmp("mount_Application",subsystem) == 0 ) {
     mount_Application_cache *mount_Application_ref;
     mount_Application_ref = (mount_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     mount_Application_ref->syncI = 0;
   }



   if (strcmp("mount_Alt",subsystem) == 0 ) {
     mount_Alt_cache *mount_Alt_ref;
     mount_Alt_ref = (mount_Alt_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     mount_Alt_ref->syncI = 0;
   }



   if (strcmp("mount_Az",subsystem) == 0 ) {
     mount_Az_cache *mount_Az_ref;
     mount_Az_ref = (mount_Az_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     mount_Az_ref->syncI = 0;
   }



   if (strcmp("mount_Rotator",subsystem) == 0 ) {
     mount_Rotator_cache *mount_Rotator_ref;
     mount_Rotator_ref = (mount_Rotator_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     mount_Rotator_ref->syncI = 0;
   }



   if (strcmp("power_TC",subsystem) == 0 ) {
     power_TC_cache *power_TC_ref;
     power_TC_ref = (power_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     power_TC_ref->syncI = 0;
   }



   if (strcmp("power_Electrical",subsystem) == 0 ) {
     power_Electrical_cache *power_Electrical_ref;
     power_Electrical_ref = (power_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     power_Electrical_ref->syncI = 0;
   }



   if (strcmp("power_UPSs",subsystem) == 0 ) {
     power_UPSs_cache *power_UPSs_ref;
     power_UPSs_ref = (power_UPSs_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     power_UPSs_ref->syncI = 0;
   }



   if (strcmp("calibration_TC",subsystem) == 0 ) {
     calibration_TC_cache *calibration_TC_ref;
     calibration_TC_ref = (calibration_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     calibration_TC_ref->syncI = 0;
   }



   if (strcmp("calibration_Electrical",subsystem) == 0 ) {
     calibration_Electrical_cache *calibration_Electrical_ref;
     calibration_Electrical_ref = (calibration_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     calibration_Electrical_ref->syncI = 0;
   }



   if (strcmp("calibration_Metrology",subsystem) == 0 ) {
     calibration_Metrology_cache *calibration_Metrology_ref;
     calibration_Metrology_ref = (calibration_Metrology_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     calibration_Metrology_ref->syncI = 0;
   }



   if (strcmp("calibration_Application",subsystem) == 0 ) {
     calibration_Application_cache *calibration_Application_ref;
     calibration_Application_ref = (calibration_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     calibration_Application_ref->syncI = 0;
   }



   if (strcmp("enclosure_TC",subsystem) == 0 ) {
     enclosure_TC_cache *enclosure_TC_ref;
     enclosure_TC_ref = (enclosure_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     enclosure_TC_ref->syncI = 0;
   }



   if (strcmp("enclosure_Electrical",subsystem) == 0 ) {
     enclosure_Electrical_cache *enclosure_Electrical_ref;
     enclosure_Electrical_ref = (enclosure_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     enclosure_Electrical_ref->syncI = 0;
   }



   if (strcmp("enclosure_Metrology",subsystem) == 0 ) {
     enclosure_Metrology_cache *enclosure_Metrology_ref;
     enclosure_Metrology_ref = (enclosure_Metrology_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     enclosure_Metrology_ref->syncI = 0;
   }



   if (strcmp("enclosure_Application",subsystem) == 0 ) {
     enclosure_Application_cache *enclosure_Application_ref;
     enclosure_Application_ref = (enclosure_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     enclosure_Application_ref->syncI = 0;
   }



   if (strcmp("enclosure_Azimuth",subsystem) == 0 ) {
     enclosure_Azimuth_cache *enclosure_Azimuth_ref;
     enclosure_Azimuth_ref = (enclosure_Azimuth_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     enclosure_Azimuth_ref->syncI = 0;
   }



   if (strcmp("enclosure_Shutter",subsystem) == 0 ) {
     enclosure_Shutter_cache *enclosure_Shutter_ref;
     enclosure_Shutter_ref = (enclosure_Shutter_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     enclosure_Shutter_ref->syncI = 0;
   }



   if (strcmp("enclosure_Vents",subsystem) == 0 ) {
     enclosure_Vents_cache *enclosure_Vents_ref;
     enclosure_Vents_ref = (enclosure_Vents_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     enclosure_Vents_ref->syncI = 0;
   }



   if (strcmp("enclosure_Thermal_control",subsystem) == 0 ) {
     enclosure_Thermal_control_cache *enclosure_Thermal_control_ref;
     enclosure_Thermal_control_ref = (enclosure_Thermal_control_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     enclosure_Thermal_control_ref->syncI = 0;
   }



   if (strcmp("scheduler_Application",subsystem) == 0 ) {
     scheduler_Application_cache *scheduler_Application_ref;
     scheduler_Application_ref = (scheduler_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     scheduler_Application_ref->syncI = 0;
   }



   if (strcmp("operations_Application",subsystem) == 0 ) {
     operations_Application_cache *operations_Application_ref;
     operations_Application_ref = (operations_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     operations_Application_ref->syncI = 0;
   }



   if (strcmp("auxscope_TC",subsystem) == 0 ) {
     auxscope_TC_cache *auxscope_TC_ref;
     auxscope_TC_ref = (auxscope_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     auxscope_TC_ref->syncI = 0;
   }



   if (strcmp("auxscope_Electrical",subsystem) == 0 ) {
     auxscope_Electrical_cache *auxscope_Electrical_ref;
     auxscope_Electrical_ref = (auxscope_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     auxscope_Electrical_ref->syncI = 0;
   }



   if (strcmp("auxscope_Metrology",subsystem) == 0 ) {
     auxscope_Metrology_cache *auxscope_Metrology_ref;
     auxscope_Metrology_ref = (auxscope_Metrology_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     auxscope_Metrology_ref->syncI = 0;
   }



   if (strcmp("auxscope_Application",subsystem) == 0 ) {
     auxscope_Application_cache *auxscope_Application_ref;
     auxscope_Application_ref = (auxscope_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     auxscope_Application_ref->syncI = 0;
   }



   if (strcmp("auxscope_TCS",subsystem) == 0 ) {
     auxscope_TCS_cache *auxscope_TCS_ref;
     auxscope_TCS_ref = (auxscope_TCS_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     auxscope_TCS_ref->syncI = 0;
   }



   if (strcmp("auxscope_Spectrometer",subsystem) == 0 ) {
     auxscope_Spectrometer_cache *auxscope_Spectrometer_ref;
     auxscope_Spectrometer_ref = (auxscope_Spectrometer_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     auxscope_Spectrometer_ref->syncI = 0;
   }



   if (strcmp("auxscope_Camera",subsystem) == 0 ) {
     auxscope_Camera_cache *auxscope_Camera_ref;
     auxscope_Camera_ref = (auxscope_Camera_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     auxscope_Camera_ref->syncI = 0;
   }



   if (strcmp("lasercal_TC",subsystem) == 0 ) {
     lasercal_TC_cache *lasercal_TC_ref;
     lasercal_TC_ref = (lasercal_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     lasercal_TC_ref->syncI = 0;
   }



   if (strcmp("lasercal_Electrical",subsystem) == 0 ) {
     lasercal_Electrical_cache *lasercal_Electrical_ref;
     lasercal_Electrical_ref = (lasercal_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     lasercal_Electrical_ref->syncI = 0;
   }



   if (strcmp("lasercal_Application",subsystem) == 0 ) {
     lasercal_Application_cache *lasercal_Application_ref;
     lasercal_Application_ref = (lasercal_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     lasercal_Application_ref->syncI = 0;
   }



   if (strcmp("seeing_dimm_TC",subsystem) == 0 ) {
     seeing_dimm_TC_cache *seeing_dimm_TC_ref;
     seeing_dimm_TC_ref = (seeing_dimm_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     seeing_dimm_TC_ref->syncI = 0;
   }



   if (strcmp("seeing_dimm_Electrical",subsystem) == 0 ) {
     seeing_dimm_Electrical_cache *seeing_dimm_Electrical_ref;
     seeing_dimm_Electrical_ref = (seeing_dimm_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     seeing_dimm_Electrical_ref->syncI = 0;
   }



   if (strcmp("seeing_dimm_Metrology",subsystem) == 0 ) {
     seeing_dimm_Metrology_cache *seeing_dimm_Metrology_ref;
     seeing_dimm_Metrology_ref = (seeing_dimm_Metrology_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     seeing_dimm_Metrology_ref->syncI = 0;
   }



   if (strcmp("seeing_dimm_Application",subsystem) == 0 ) {
     seeing_dimm_Application_cache *seeing_dimm_Application_ref;
     seeing_dimm_Application_ref = (seeing_dimm_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     seeing_dimm_Application_ref->syncI = 0;
   }



   if (strcmp("seeing_mass_TC",subsystem) == 0 ) {
     seeing_mass_TC_cache *seeing_mass_TC_ref;
     seeing_mass_TC_ref = (seeing_mass_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     seeing_mass_TC_ref->syncI = 0;
   }



   if (strcmp("seeing_mass_Electrical",subsystem) == 0 ) {
     seeing_mass_Electrical_cache *seeing_mass_Electrical_ref;
     seeing_mass_Electrical_ref = (seeing_mass_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     seeing_mass_Electrical_ref->syncI = 0;
   }



   if (strcmp("seeing_mass_Metrology",subsystem) == 0 ) {
     seeing_mass_Metrology_cache *seeing_mass_Metrology_ref;
     seeing_mass_Metrology_ref = (seeing_mass_Metrology_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     seeing_mass_Metrology_ref->syncI = 0;
   }



   if (strcmp("seeing_mass_Application",subsystem) == 0 ) {
     seeing_mass_Application_cache *seeing_mass_Application_ref;
     seeing_mass_Application_ref = (seeing_mass_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     seeing_mass_Application_ref->syncI = 0;
   }



   if (strcmp("skycam_TC",subsystem) == 0 ) {
     skycam_TC_cache *skycam_TC_ref;
     skycam_TC_ref = (skycam_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     skycam_TC_ref->syncI = 0;
   }



   if (strcmp("skycam_Electrical",subsystem) == 0 ) {
     skycam_Electrical_cache *skycam_Electrical_ref;
     skycam_Electrical_ref = (skycam_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     skycam_Electrical_ref->syncI = 0;
   }



   if (strcmp("skycam_Metrology",subsystem) == 0 ) {
     skycam_Metrology_cache *skycam_Metrology_ref;
     skycam_Metrology_ref = (skycam_Metrology_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     skycam_Metrology_ref->syncI = 0;
   }



   if (strcmp("skycam_Application",subsystem) == 0 ) {
     skycam_Application_cache *skycam_Application_ref;
     skycam_Application_ref = (skycam_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     skycam_Application_ref->syncI = 0;
   }



   if (strcmp("environment_TC",subsystem) == 0 ) {
     environment_TC_cache *environment_TC_ref;
     environment_TC_ref = (environment_TC_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     environment_TC_ref->syncI = 0;
   }



   if (strcmp("environment_Electrical",subsystem) == 0 ) {
     environment_Electrical_cache *environment_Electrical_ref;
     environment_Electrical_ref = (environment_Electrical_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     environment_Electrical_ref->syncI = 0;
   }



   if (strcmp("environment_Weather",subsystem) == 0 ) {
     environment_Weather_cache *environment_Weather_ref;
     environment_Weather_ref = (environment_Weather_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     environment_Weather_ref->syncI = 0;
   }



   if (strcmp("environment_Dust_monitor",subsystem) == 0 ) {
     environment_Dust_monitor_cache *environment_Dust_monitor_ref;
     environment_Dust_monitor_ref = (environment_Dust_monitor_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     environment_Dust_monitor_ref->syncI = 0;
   }



   if (strcmp("environment_Lightning_detector",subsystem) == 0 ) {
     environment_Lightning_detector_cache *environment_Lightning_detector_ref;
     environment_Lightning_detector_ref = (environment_Lightning_detector_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     environment_Lightning_detector_ref->syncI = 0;
   }



   if (strcmp("environment_Seismometer",subsystem) == 0 ) {
     environment_Seismometer_cache *environment_Seismometer_ref;
     environment_Seismometer_ref = (environment_Seismometer_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     environment_Seismometer_ref->syncI = 0;
   }



   if (strcmp("environment_Video_cameras",subsystem) == 0 ) {
     environment_Video_cameras_cache *environment_Video_cameras_ref;
     environment_Video_cameras_ref = (environment_Video_cameras_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     environment_Video_cameras_ref->syncI = 0;
   }



   if (strcmp("network_Application",subsystem) == 0 ) {
     network_Application_cache *network_Application_ref;
     network_Application_ref = (network_Application_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     network_Application_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_TrackRefSys",subsystem) == 0 ) {
     tcs_kernel_TrackRefSys_cache *tcs_kernel_TrackRefSys_ref;
     tcs_kernel_TrackRefSys_ref = (tcs_kernel_TrackRefSys_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_TrackRefSys_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_Target",subsystem) == 0 ) {
     tcs_kernel_Target_cache *tcs_kernel_Target_ref;
     tcs_kernel_Target_ref = (tcs_kernel_Target_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_Target_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_DawdleFilter",subsystem) == 0 ) {
     tcs_kernel_DawdleFilter_cache *tcs_kernel_DawdleFilter_ref;
     tcs_kernel_DawdleFilter_ref = (tcs_kernel_DawdleFilter_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_DawdleFilter_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_FK5Target",subsystem) == 0 ) {
     tcs_kernel_FK5Target_cache *tcs_kernel_FK5Target_ref;
     tcs_kernel_FK5Target_ref = (tcs_kernel_FK5Target_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_FK5Target_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_OpticsVt",subsystem) == 0 ) {
     tcs_kernel_OpticsVt_cache *tcs_kernel_OpticsVt_ref;
     tcs_kernel_OpticsVt_ref = (tcs_kernel_OpticsVt_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_OpticsVt_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_PointingControl",subsystem) == 0 ) {
     tcs_kernel_PointingControl_cache *tcs_kernel_PointingControl_ref;
     tcs_kernel_PointingControl_ref = (tcs_kernel_PointingControl_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_PointingControl_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_PointingLog",subsystem) == 0 ) {
     tcs_kernel_PointingLog_cache *tcs_kernel_PointingLog_ref;
     tcs_kernel_PointingLog_ref = (tcs_kernel_PointingLog_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_PointingLog_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_PointingModel",subsystem) == 0 ) {
     tcs_kernel_PointingModel_cache *tcs_kernel_PointingModel_ref;
     tcs_kernel_PointingModel_ref = (tcs_kernel_PointingModel_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_PointingModel_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_Site",subsystem) == 0 ) {
     tcs_kernel_Site_cache *tcs_kernel_Site_ref;
     tcs_kernel_Site_ref = (tcs_kernel_Site_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_Site_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_TimeKeeper",subsystem) == 0 ) {
     tcs_kernel_TimeKeeper_cache *tcs_kernel_TimeKeeper_ref;
     tcs_kernel_TimeKeeper_ref = (tcs_kernel_TimeKeeper_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_TimeKeeper_ref->syncI = 0;
   }



   if (strcmp("tcs_kernel_TrackingTarget",subsystem) == 0 ) {
     tcs_kernel_TrackingTarget_cache *tcs_kernel_TrackingTarget_ref;
     tcs_kernel_TrackingTarget_ref = (tcs_kernel_TrackingTarget_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     tcs_kernel_TrackingTarget_ref->syncI = 0;
   }



   if (strcmp("camera_BEE_biases",subsystem) == 0 ) {
     camera_BEE_biases_cache *camera_BEE_biases_ref;
     camera_BEE_biases_ref = (camera_BEE_biases_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_BEE_biases_ref->syncI = 0;
   }



   if (strcmp("camera_BEE_clocks",subsystem) == 0 ) {
     camera_BEE_clocks_cache *camera_BEE_clocks_ref;
     camera_BEE_clocks_ref = (camera_BEE_clocks_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_BEE_clocks_ref->syncI = 0;
   }



   if (strcmp("camera_BEE_thermal",subsystem) == 0 ) {
     camera_BEE_thermal_cache *camera_BEE_thermal_ref;
     camera_BEE_thermal_ref = (camera_BEE_thermal_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_BEE_thermal_ref->syncI = 0;
   }



   if (strcmp("camera_CALSYS",subsystem) == 0 ) {
     camera_CALSYS_cache *camera_CALSYS_ref;
     camera_CALSYS_ref = (camera_CALSYS_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_CALSYS_ref->syncI = 0;
   }



   if (strcmp("camera_CCS",subsystem) == 0 ) {
     camera_CCS_cache *camera_CCS_ref;
     camera_CCS_ref = (camera_CCS_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_CCS_ref->syncI = 0;
   }



   if (strcmp("camera_FCS",subsystem) == 0 ) {
     camera_FCS_cache *camera_FCS_ref;
     camera_FCS_ref = (camera_FCS_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_FCS_ref->syncI = 0;
   }



   if (strcmp("camera_GAS",subsystem) == 0 ) {
     camera_GAS_cache *camera_GAS_ref;
     camera_GAS_ref = (camera_GAS_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_GAS_ref->syncI = 0;
   }



   if (strcmp("camera_LASERCAL",subsystem) == 0 ) {
     camera_LASERCAL_cache *camera_LASERCAL_ref;
     camera_LASERCAL_ref = (camera_LASERCAL_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_LASERCAL_ref->syncI = 0;
   }



   if (strcmp("camera_PWR",subsystem) == 0 ) {
     camera_PWR_cache *camera_PWR_ref;
     camera_PWR_ref = (camera_PWR_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_PWR_ref->syncI = 0;
   }



   if (strcmp("camera_QA_measured",subsystem) == 0 ) {
     camera_QA_measured_cache *camera_QA_measured_ref;
     camera_QA_measured_ref = (camera_QA_measured_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_QA_measured_ref->syncI = 0;
   }



   if (strcmp("camera_SCS",subsystem) == 0 ) {
     camera_SCS_cache *camera_SCS_ref;
     camera_SCS_ref = (camera_SCS_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_SCS_ref->syncI = 0;
   }



   if (strcmp("camera_SDS_amplifiers",subsystem) == 0 ) {
     camera_SDS_amplifiers_cache *camera_SDS_amplifiers_ref;
     camera_SDS_amplifiers_ref = (camera_SDS_amplifiers_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_SDS_amplifiers_ref->syncI = 0;
   }



   if (strcmp("camera_SDS",subsystem) == 0 ) {
     camera_SDS_cache *camera_SDS_ref;
     camera_SDS_ref = (camera_SDS_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_SDS_ref->syncI = 0;
   }



   if (strcmp("camera_TC_control",subsystem) == 0 ) {
     camera_TC_control_cache *camera_TC_control_ref;
     camera_TC_control_ref = (camera_TC_control_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_TC_control_ref->syncI = 0;
   }



   if (strcmp("camera_TCM",subsystem) == 0 ) {
     camera_TCM_cache *camera_TCM_ref;
     camera_TCM_ref = (camera_TCM_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_TCM_ref->syncI = 0;
   }



   if (strcmp("camera_TC_zone1",subsystem) == 0 ) {
     camera_TC_zone1_cache *camera_TC_zone1_ref;
     camera_TC_zone1_ref = (camera_TC_zone1_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_TC_zone1_ref->syncI = 0;
   }



   if (strcmp("camera_TC_zone2",subsystem) == 0 ) {
     camera_TC_zone2_cache *camera_TC_zone2_ref;
     camera_TC_zone2_ref = (camera_TC_zone2_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_TC_zone2_ref->syncI = 0;
   }



   if (strcmp("camera_TC_zone3",subsystem) == 0 ) {
     camera_TC_zone3_cache *camera_TC_zone3_ref;
     camera_TC_zone3_ref = (camera_TC_zone3_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_TC_zone3_ref->syncI = 0;
   }



   if (strcmp("camera_TC_zone4",subsystem) == 0 ) {
     camera_TC_zone4_cache *camera_TC_zone4_ref;
     camera_TC_zone4_ref = (camera_TC_zone4_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_TC_zone4_ref->syncI = 0;
   }



   if (strcmp("camera_TC_zone5",subsystem) == 0 ) {
     camera_TC_zone5_cache *camera_TC_zone5_ref;
     camera_TC_zone5_ref = (camera_TC_zone5_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_TC_zone5_ref->syncI = 0;
   }



   if (strcmp("camera_TC_zone6",subsystem) == 0 ) {
     camera_TC_zone6_cache *camera_TC_zone6_ref;
     camera_TC_zone6_ref = (camera_TC_zone6_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_TC_zone6_ref->syncI = 0;
   }



   if (strcmp("camera_UTIL",subsystem) == 0 ) {
     camera_UTIL_cache *camera_UTIL_ref;
     camera_UTIL_ref = (camera_UTIL_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_UTIL_ref->syncI = 0;
   }



   if (strcmp("camera_VCS",subsystem) == 0 ) {
     camera_VCS_cache *camera_VCS_ref;
     camera_VCS_ref = (camera_VCS_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_VCS_ref->syncI = 0;
   }



   if (strcmp("camera_WDS_wfsRaft",subsystem) == 0 ) {
     camera_WDS_wfsRaft_cache *camera_WDS_wfsRaft_ref;
     camera_WDS_wfsRaft_ref = (camera_WDS_wfsRaft_cache *)shmdata_ref;
/*   Process new data here
     ...
 */
     camera_WDS_wfsRaft_ref->syncI = 0;
   }


   return SAL__OK;
}

