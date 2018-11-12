#!/usr/bin/env tclsh

source $env(SAL_DIR)/add_system_dictionary.tcl
source $env(SAL_DIR)/updatedetails.tcl
source $env(SAL_DIR)/genidlshmem.tcl
source $env(SAL_WORK_DIR)/.salwork/revCodes.tcl
set fout [open $env(SAL_WORK_DIR)/.salwork/sid.tcl w]
set ffrq [open bandwidth/stream_frequencies.tcl w]

set FASTTLM(MTMount)    20.0
set FASTTLM(ATMount)    20.0
set FASTTLM(MTM1M3)     20.0
set FASTTLM(M2MS)       20.0
set FASTTLM(ATDome)      1.0
set FASTTLM(Dome)        1.0
set FASTTLM(DomeADB)     1.0
set FASTTLM(DomeAPS)     1.0
set FASTTLM(DomeLouvers) 1.0
set FASTTLM(DomeLWS)     1.0
set FASTTLM(DomeMONCS)   1.0
set FASTTLM(DomeTHCS)    1.0
set FASTTLM(EEC)        10.0
set FASTTLM(SummitFacility) 1.0
set FASTTLM(Scheduler.slewConfig) 0.0001
set FASTTLM(Scheduler.sequencePropConfig) 0.0001
set FASTTLM(Scheduler.driverConfig) 0.0001
set FASTTLM(Scheduler.cameraConfig) 0.0001
set FASTTLM(Scheduler.generalPropConfig) 0.0001
set FASTTLM(Scheduler.propConfig) 0.0001
set FASTTLM(Scheduler.surveyTopology) 0.0001
set FASTTLM(Scheduler.observation) 0.0001
set FASTTLM(Scheduler.observatoryState) 0.0001

set FASTCMD(MTMount.command.trackTarget) 20.0
set FASTCMD(ATMCS.command.trackTarget)   20.0
set FASTCMD(Rotator.command.track)       20.0

set n 1
foreach s [lsort $SYSDIC(systems)] {
  puts $fout "set SID($s) 4.5.$n"
  incr n 1
  if { [info exists FASTTLM($s)] } {
     puts $ffrq "set FREQUENCY($s) $FASTTLM($s)"
  } else { 
     puts $ffrq "set FREQUENCY($s) 1.0"
  }
}

foreach i [lsort [array names REVCODE]] {
puts stdout "doing $i"
  puts $fout "set SID($i) $REVCODE($i)"
  set type [lindex [split $i _] 1]
  set j [join [split $i _] .]
  if { $type == "command" } {
     if { [info exists FASTCMD($j)] } {
       puts $ffrq "set FREQUENCY($j) $FASTCMD($j)"
     } else {
       puts $ffrq "set FREQUENCY($j) 0.054"
     }
  } else {
     if { $type == "logevent" } {
        puts $ffrq "set FREQUENCY($j) 0.054"
     } else {
        set subsys [lindex [split $i _] 0]
        if { [info exists FASTTLM($j)] } {
           puts $ffrq "set FREQUENCY($j) $FASTTLM($j)"
        } else { 
           if { [info exists FASTTLM($subsys)] } {
              puts $ffrq "set FREQUENCY($j) $FASTTLM($subsys)"
           } else {
              puts $ffrq "set FREQUENCY($j) 1.0"
           }
        }
     }
  }
}

close $ffrq
close $fout 

