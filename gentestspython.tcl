# set SAL_WORK_DIR $env(SAL_WORK_DIR)
# set SAL_DIR $env(SAL_DIR)
# source $SAL_DIR/utilities.tcl
# source $SAL_DIR/gentestspython.tcl
# source $SAL_WORK_DIR/idl-templates/validated/camera_evtdef.tcl
# source $SAL_WORK_DIR/idl-templates/validated/camera_cmddef.tcl
# geneventtestspython camera
# gencmdtestspython camera
#



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
      set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]Event_[set alias].py w]
      puts $fcmd "
import time
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
event = [set subsys]_logevent_[set alias]C()
mgr.logEvent_[set alias](event, 1)
time.sleep(1)
mgr.salShutdown()
"
      close $fcmd
      stdlog "	: event test receive for = $alias"
      set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]EventLogger_[set alias].py w]
      puts $fcmd "
import time
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
while True:
	event = [set subsys]_logevent_[set alias]C()
	retval = mgr.getEvent_[set alias](event)
	print retval
	print \">%s<\" % event.message
	time.sleep(1)
mgr.salShutdown()
"
      close $fcmd
    } else {
      stdlog "	: generic event test send for = $alias"
      set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]Event_[set alias].py w]
      puts $fcmd "
import time
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
event = [set subsys]_logeventC()
event.message=\"[set alias]\"
mgr.logEvent(event, 1)
time.sleep(1)
mgr.salShutdown()
"
      close $fcmd
    }
   }
 }
 stdlog "	: generic event test receiver"
 set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]EventLogger.py w]
 puts $fcmd "
import time
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
while True:
	event = [set subsys]_logeventC()
	retval = mgr.getEvent(event)
	print retval
	print \">%s<\" % event.message
	time.sleep(1)
mgr.salShutdown()
"
 close $fcmd
}



proc gencmdtestspython { subsys } {
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
      set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]Commander_[set alias].py w]
      puts $fcmd "
import time
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
mgr.salCommander(\"[set subsys]_command_[set alias]\")
command = [set subsys]_command_[set alias]C()
command.device = sys.argv\[1\]
cmdId = mgr.issueCommand_[set alias](command)
retval = msg.waitForCompletion_[set alias](cmdId)
time.sleep(1)
"
      close $fcmd
      stdlog "	: command test receive for = $alias"
      set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]Controller_[set alias].py w]
      puts $fcmd "
import time
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
mgr.salProcessor(\"[set subsys]_command_[set alias]\")
command = [set subsys]_command_[set alias]C()
while True:
	retval = mgr.acceptCommand_[set alias](command)
	time.sleep(1)
"
      close $fcmd
    }
   }
 }
 stdlog "	: generic command test sender"
 set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]Commander.py w]
 puts $fcmd "
import time
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
mgr.salCommander(\"[set subsys]_command\")
command = [set subsys]_commandC()
command.device   = sys.argv\[1\]
command.property = sys.argv\[2\]
command.action   = sys.argv\[3\]
command.value    = sys.argv\[4\]
cmdId = mgr.issueCommand(command)
retval = msg.waitForCompletion(cmdId)
time.sleep(1)
"
 close $fcmd
 stdlog "	: generic command test receiver"
 set fcmd [open $SAL_WORK_DIR/$subsys/python/[set subsys]Controller.py w]
 puts $fcmd "
import time
from SALPY_[set subsys] import *
mgr = SAL_[set subsys][set initializer]
mgr.salProcessor(\"[set subsys]_command\")
command = [set subsys]_commandC()
while True:
	retval = mgr.acceptCommand(command)
	time.sleep(1)
"
 close $fcmd
}



