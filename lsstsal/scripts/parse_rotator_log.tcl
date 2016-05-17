#!/usr/bin/tclsh

set id $argv
set fin [open $id r]
set num 1
set fout [open [set id]_[set num] w]
while { [gets $fin rec] > -1 }  {
   if { [lindex $rec 0] == "modifiers:" } {
    if { [string range $rec 0 16] != "    modifiers: sp" } {
      set d [split $rec ",="]
      set tai [lindex $d 1]
      set ang [lindex $d 3]
      set vel [lindex $d 5]
      if { [expr abs($vel)] > 50.0 } {
         close $fout
         incr num 1
         puts stdout "starting part $num"
         set fout [open [set id]_[set num] w]
      } else {
        puts $fout "$tai $ang $vel"  
      }
    }
   }
}
close $fin
close $fout


