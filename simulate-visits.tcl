#!/usr/bin/tclsh

load $env(SAL_DIR)/../lib/libxtcs.so
set startrec 1
set numvisits 1000

if { $argc > 1 } {
  set startrec [lindex $argv 1]
  set numvisits [lindex $argv 2]
}

puts stdout "Simulating $numvisits visits, starting from record $startrec"
set count 0
set ok 0
set fin [open circumpolar.dat r]
while { $count < $startrec } {
  gets $fin rec
  incr count 1
}

puts stdout "Started visits at record $count"
set count 0 
set lastfield 0
set lastfilter r

proc simvisits { {n 1} } {
global TARGETS numvisits fin lastfield lastfilter env
  gets $fin rec
  if { [lindex $rec 29] < -1.1 } {
    set field [lindex $rec 3]
    if { $field != $lastfield } {
puts stdout "Field $field"
      set lastfield $field
      set filter [lindex $rec 4]
      set mjd [lindex $rec 9]
      set exptime [lindex $rec 10]
      set slewtime [lindex $rec 11]
      set rot [lindex $rec 13]
      set ra  [split [radians_to_hms [lindex $rec 28]] :]
      set dec [split [radians_to_dms [lindex $rec 29]] :]
      set alt [lindex $rec 31]
      set az  [lindex $rec 32]
      puts stdout "Visiting field $field $ra, $dec"
#      puts stdout "command -> dome target position azimuth=$az elevation=$alt"
#      puts stdout "command -> hexapod 1 actuators position absolute x=1.0 y=2.0 z=3.0 v=-1.0 w=-2.0 z=-3.0"
#      puts stdout "command -> hexapod 2 actuators position absolute x=1.0 y=2.0 z=3.0 v=-1.0 w=-2.0 z=-3.0"
#      puts stdout "command -> rotator target position angle=$rot"
#      puts stdout "command -> camera guiders roi set xpos=1,1,1,1,1,1,1,1 ypos=2,2,2,2,2,2,2,2 roiSize=32,32,32,32,32,32,32,32" 
      if { [info exists TARGETS($field)] == 0 } {
        catch {target create icrs "$ra $dec" TARGETS($field)}
      }
      after 10 slew TARGETS($field)
      if { $filter != $lastfilter } {
         puts stdout "Filter change required last=$lastfilter filter=$filter"
##         after 130000 "simvisits $n"
         set lastfilter $filter
         exec gnome-terminal --geometry 130x24 -t "Visit with filter change" -e "$env(SAL_HOME)/scripts/standardvisit_commands.tcl $az $alt $filter" &
      } else {
         exec gnome-terminal --geometry 130x24+30+30 -t "Standard Visit" -e "$env(SAL_HOME)/scripts/standardvisit_commands.tcl $az $alt" &
      }
##      after [expr int($slewtime*1000)] {puts stdout "command -> camera imager expose numimages=2 expTime=15 shutter=true guide=true wfs=true"}
      incr n 1
      set lastfilter $filter
      if { $n < $numvisits } {
        after [expr int(($exptime+$slewtime+14) * 1000)] "simvisits $n"
      }
    } else {
      after 10 "simvisits $n"
    }
  } else {
    after 10 "simvisits $n"
  }
}
puts stdout "Type simvisits to start"

