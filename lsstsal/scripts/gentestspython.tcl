# set SAL_WORK_DIR $env(SAL_WORK_DIR)
# set SAL_DIR $env(SAL_DIR)
# source $SAL_DIR/utilities.tcl
# source $SAL_DIR/gentestspython.tcl
# source $SAL_WORK_DIR/idl-templates/validated/camera_tlmdef.tcl
# source $SAL_WORK_DIR/idl-templates/validated/camera_evtdef.tcl
# source $SAL_WORK_DIR/idl-templates/validated/camera_cmddef.tcl
# geneventtestspython camera
# gencmdtestspython camera
#

source $SAL_DIR/pythonprint.tcl

proc gentelemetrytestspython { subsys } {
global SAL_WORK_DIR SYSDIC SAL_DIR
   if { [info exists SYSDIC($subsys,keyedID)] } {
       set initializer "(1)"
   } else {
       set initializer "()"
   }
   set idlfile "$SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl"
   set ptypes [split [exec grep pragma $idlfile] \n]
   foreach j $ptypes {
      set name [lindex $j 2]
      set type [lindex [split $name _] 0]
      if { $type != "command" && $type != "logevent" && $type != "ackcmd" } {
         stdlog "	: publisher for = $name"
         set fpub [open $SAL_WORK_DIR/$subsys/python/[set subsys]_[set name]_Publisher.py w]
	 puts $fpub "
import time
import sys
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
mgr.salTelemetryPub(\"[set subsys]_[set name]\")
myData = [set subsys]_[set name]C()"
         set farg [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Ppub.tmp r]
	 while { [gets $farg rec] > -1 } {
	    puts $fpub $rec
	 }
	 puts $fpub "i=0
while i<10:
  retval = mgr.putSample_[set name](myData)
  i=i+1
  time.sleep(1)

mgr.salShutdown()
exit()
"
         close $fpub
         stdlog "	: subscriber for = $name"
         set fsub [open $SAL_WORK_DIR/$subsys/python/[set subsys]_[set name]_Subscriber.py w]
	 puts $fsub "
import time
import sys
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
mgr.salTelemetrySub(\"[set subsys]_[set name]\")
myData = [set subsys]_[set name]C()
print(\"[set subsys]_[set alias] subscriber ready\")
while True:
  retval = mgr.getNextSample_[set name](myData)
  if retval==0:"
         pythonprinter $fsub [set subsys]_[set name]
	 puts $fsub "  time.sleep(1)

mgr.salShutdown()
exit()
"
         close $fsub
      }
   }
}


proc geneventtestspython { subsys } {
global EVENT_ALIASES EVTS SAL_WORK_DIR SYSDIC SAL_DIR
 exec mkdir -p $SAL_WORK_DIR/$subsys/python
 if { [info exists EVENT_ALIASES($subsys)] } {
   if { [info exists SYSDIC($subsys,keyedID)] } {
       set initializer "(1)"
   } else {
       set initializer "()"
   }
   foreach alias $EVENT_ALIASES($subsys) {
    if { [info exists EVTS($subsys,$alias,param)] } {
      stdlog "	: event test send for = $alias"
      set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]_Event_[set alias].py w]
      puts $fcmd "
import time
import sys
if len(sys.argv) < [expr [llength $EVTS([set subsys],[set alias],plist)] +1]:
  print(\"ERROR : Invalid or missing arguments : $EVTS([set subsys],[set alias],plist)\")
  exit()

from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
myData = [set subsys]_logevent_[set alias]C()"
      set farg [open $SAL_WORK_DIR/include/SAL_[set subsys]_logevent_[set alias]Pargs.tmp r]
      while { [gets $farg rec] > -1 } {
         puts $fcmd $rec
      }
      close $farg
      puts $fcmd "mgr.logEvent_[set alias](myData, priority)
time.sleep(1)
mgr.salShutdown()
exit()
"
      close $fcmd
      stdlog "	: event test receive for = $alias"
      set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]_EventLogger_[set alias].py w]
      puts $fcmd "
import time
import sys
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
print(\"[set subsys]_[set alias] logger ready\")
while True:
  event = [set subsys]_logevent_[set alias]C()
  retval = mgr.getEvent_[set alias](event)
  print(\"Event $subsys $alias received\")
  time.sleep(1)
mgr.salShutdown()
exit()
"
      close $fcmd
    } 
   }
 }
}



proc gencommandtestspython { subsys } {
global CMD_ALIASES CMDS SAL_WORK_DIR SYSDIC SAL_DIR
 exec mkdir -p $SAL_WORK_DIR/$subsys/python
 if { [info exists CMD_ALIASES($subsys)] } {
   if { [info exists SYSDIC($subsys,keyedID)] } {
       set initializer "(1)"
   } else {
       set initializer "()"
   }
   foreach alias $CMD_ALIASES($subsys) {
    if { [info exists CMDS($subsys,$alias,param)] } {
      stdlog "	: command test send for = $alias"
      set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]_Commander_[set alias].py w]
      puts $fcmd "
import time
import sys
timeout=5
if len(sys.argv) < [expr [llength $CMDS([set subsys],[set alias],plist)] +1]:
  print(\"ERROR : Invalid or missing arguments : $CMDS([set subsys],[set alias],plist)\")
  exit()

from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
mgr.salCommand(\"[set subsys]_command_[set alias]\")
myData = [set subsys]_command_[set alias]C()"
       set farg [open $SAL_WORK_DIR/include/SAL_[set subsys]_command_[set alias]Pargs.tmp r]
       gets $farg rec;gets $farg rec;gets $farg rec;gets $farg rec
       while { [gets $farg rec] > -1 } {
          puts $fcmd $rec
       }
       close $farg
       puts $fcmd "cmdId = mgr.issueCommand_[set alias](myData)
retval = mgr.waitForCompletion_[set alias](cmdId,timeout)
time.sleep(1)
mgr.salShutdown()
exit()
"
      close $fcmd
      stdlog "	: command test receive for = $alias"
      set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]_Controller_[set alias].py w]
      puts $fcmd "
import time
import sys
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
mgr.salProcessor(\"[set subsys]_command_[set alias]\")
myData = [set subsys]_command_[set alias]C()
print(\"[set subsys]_[set alias] controller ready\")
SAL__CMD_COMPLETE=303
while True:
    cmdId = mgr.acceptCommand_[set alias](myData)"
     pythonprinter $fcmd [set subsys]_command_[set alias]
     puts $fcmd "    time.sleep(1)
    mgr.ackCommand_[set alias](cmdId, SAL__CMD_COMPLETE, 0, \"Done : OK\");
    time.sleep(1)

mgr.salShutdown()
exit()
"
      close $fcmd
    }
   }
 }
}



