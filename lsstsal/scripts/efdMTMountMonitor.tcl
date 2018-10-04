#!/usr/bin/wish

proc updateview { subsys poll } {
global NROW
  set q [lrange [split [exec mysql -A --host=83.56.45.3 --user=efduser --password=lssttest EFD < /tmp/dosql] \n] 2 end]
  foreach t $q { set NROW([lindex $t 0]) [format %12d [lindex $t 1]] }
  after $poll "updateview $subsys $poll"
}

set topics [split "MTMount_Alt_OSS
MTMount_Alt
MTMount_Alt_TC
MTMount_Auxiliary_Boxes
MTMount_Auxliary_Cabinet_Azimuth
MTMount_Az_CW
MTMount_Azimuth_Cable_Wrap
MTMount_Azimuth_Drives
MTMount_Azimuth_Drives_Thermal
MTMount_Azimuth
MTMount_Az_OSS
MTMount_Az
MTMount_Az_TC
MTMount_Balancing_Drives
MTMount_Balancing
MTMount_Bal
MTMount_Cab_TC
MTMount_Cam_CW
MTMount_Camera_Cable_Wrap
MTMount_Compressed_Air
MTMount_Cooling
MTMount_Deployable_Platforms
MTMount_DP_1
MTMount_DP_2
MTMount_Dynalene_Cooling
MTMount_Elevation_Drives
MTMount_Elevation_Drives_Thermal
MTMount_Elevation
MTMount_Encoder_EIB
MTMount_General_Purpose_Glycol_Water
MTMount_General
MTMount_Locking_Pins
MTMount_Main_Power_Supply_Cabinet
MTMount_Main_Power_Supply
MTMount_MC
MTMount_Mirror_Cover_Locks
MTMount_Mirror_Cover
MTMount_MotionParameters
MTMount_Mount_Control_Main_Cabinet
MTMount_OSS
MTMount_Safety_System
MTMount_Top_End_Chiller" \n]

set fout [open /tmp/dosql w]
puts $fout "SELECT table_name, table_rows FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA='EFD' order by table_rows;\nexit"
close $fout 
set subsys MTMount
set poll 5000
if { $argc > 1 } { set poll [expr [lindex $argv 1]*1000] }
toplevel .w[set subsys] -width 1500 -height 900
set iy 0
set ix 10
set n 0
foreach t [lsort $topics] {
  set id [file root [file tail $t]]
  if { [lindex [split $id _] 1] != "command" } {
      set NROW(id) [format %10d 0]
      label .w[set subsys].l[set id] -text $id -width 40 -bg gray
      label .w[set subsys].t[set id] -width 14 -bg LightBlue -textvariable NROW($id)
      place .w[set subsys].l[set id] -x $ix -y $iy
      place .w[set subsys].t[set id] -x [expr $ix + 300] -y $iy
      incr iy 25
      incr n 1
      if { $iy > 500 } {incr ix 420; set iy 0}
  }
}
button .w[set subsys].stop -text "Quit" -width 101 -command exit -bg orange 
place .w[set subsys].stop -x 10 -y 525
wm geometry .w[set subsys] 850x558
wm title .w[set subsys] "EFD Row counts for $subsys"
wm withdraw .
updateview $subsys $poll


