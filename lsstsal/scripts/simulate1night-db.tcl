#!/usr/bin/env tclsh
set SAL_DIR $env(SAL_DIR)
set SAL_WORK_DIR $env(SAL_WORK_DIR)
source $env(SAL_DIR)/simulatedb.tcl
unset FREQUENCY

source $SAL_WORK_DIR/bandwidth/stream_frequencies.tcl
set dbstart "2020-01-01 18:00:00"
set dbend   "2020-01-02 06:00:00"

foreach stopic [lsort [array names FREQUENCY]] {
  set topic [join [split $stopic .] _]
  set ttype [lindex [split $topic _] 1]
  if { $ttype != "command" && $ttype != "logevent" && $ttype != "ackcmd" && $ttype != "timestamp" } {
   puts stdout "Processing $topic"
   if { [file exists $SAL_WORK_DIR/[set topic]_telemetry_simulation.tcl] } {
     stdlog "Loading simulation routines from $SAL_WORK_DIR/[set topic]_telemetry_simulation.tcl"
     source $SAL_WORK_DIR/[set topic]_telemetry_simulation.tcl
   }
   if { [file exists $SAL_WORK_DIR/sql/[set topic].sqldef] } {
       if { [file exists /d2/singlenight/$topic-[join $dbstart -]_to_[join $dbend -].sql] == 0 } {
         set fout [open /d2/singlenight/$topic-[join $dbstart -]_to_[join $dbend -].sql w]
         simulateperiod $fout $topic "$dbstart" "$dbend" [expr 1.0/$FREQUENCY($stopic)]
         close $fout
         puts stdout "   data in $topic-[join $dbstart -]_to_[join $dbend -].sql"
       }
   }
  }
}




