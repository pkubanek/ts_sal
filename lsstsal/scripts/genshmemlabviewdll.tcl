#
#  add to .h and change m2ms_shmem to shmemIO
#     struct m2ms_shmem {
#        shmemIO client[50];
#     };
#
# add inUse flag to client struct
#
# in cpp change all m2ms_memIO->  to m2ms_memIO->client[cid].
#
# in connect look for unused inUse slot and clear all flags in it
# store returned slot number in global var in LV library
# in disconnect , clear all flags and reset inUse flag
#
# change monitor syncInit to a routine and call on connect/disconnect
#


set SAL_DIR $env(SAL_DIR)
set SAL_WORK_DIR $env(SAL_WORK_DIR)
source $SAL_DIR/add_system_dictionary.tcl 
source $SAL_DIR/gencommandlabviewtests.tcl 
source $SAL_DIR/geneventlabviewtests.tcl 
source $SAL_DIR/gentelemetrylabviewtests.tcl 
source $SAL_DIR/utilities.tcl 

proc genshmemlabviewdll { subsys } {
global SAL_DIR SAL_WORK_DIR
  exec mkdir -p $SAL_WORK_DIR/[set subsys]/labview
  set idlfile $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl
  set ptypes [lsort [split [exec grep pragma $idlfile] \n]]
  set base $subsys
  genlabviewcpp  $base $ptypes
}

proc genlabviewcpp { base ptypes } {
global SAL_DIR SAL_WORK_DIR SYSDIC LVSTRINGS
  set idarg ""
  set idarg2 ""
  set idarg3 "     unsigned int [set base]ID = 0;"
  set idoff "[set base]ID"
  if { [info exists SYSDIC($base,keyedID)] } {
     set idarg "unsigned int [set base]ID"
     set idarg2 "[set base]ID"
  }
  set fout [open $SAL_WORK_DIR/[set base]/labview/SAL_[set base]_salShmDLL.cpp w]
  puts $fout "
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/syscall.h>
#include <thread>
#include \"extcode.h\"
extern \"C\" \{
#define BUILD_FOR_LV
#include \"SAL_[set base]C.h\"
#include \"SAL_[set base]_shmem.h\"
#define ReturnCode_t int
#define SAL__OK 0
"
  puts $fout "
    [set idarg3]
    [set base]_shmem *[set base]_memIO;
    __thread int LVClient;
    int [set base]_salShmConnect ([set idarg]) \{
      return SAL__OK;
    \}

    int [set base]_salShmRelease() \{
      return SAL__OK;
    \}

    double [set base]_shm_getCurrentTimeLV() \{
      return 0.0;
    \}

"
  foreach j $ptypes {
     set name [lindex $j 2]
     set type [lindex [split $name _] 0]
     if { $type == "command" && $name != "command" } {
       genlvcommand $fout $base $name
     }
     if { $type == "logevent" && $name != "logevent"} {
       genlvlogevent $fout $base $name
     }
     if { $name != "ackcmd" && $type != "command" && $type != "logevent" } {
       genlvtelemetry $fout $base $name
     }
     genlvcallback $fout $base $name  
   }
   genlvlaunchcallbacks $fout $base $ptypes
   puts $fout "
    void [set base]_shm_initFlags () \{
\}
\}
"
  close $fout
}


#
#  Sample callback usage
#
#  1. Get a LV handle for the callback
#  2. xxx_shm_registerCallback_yyy(handle)
#  3. Receive and process LVUserEvent
#  4. Call xxx_shm_getSample/acceptCommand/getEvent
#  5. Goto step 3
#
#

proc genlvcallback { fout base name } {
   puts $fout "
    int [set base]_shm_registerCallback_[set name]LV(int handle, bool skipOld) \{
         return SAL__OK;
    \}
    int [set base]_shm_cancelCallback_[set name]LV() \{
        return SAL__OK;
    \}
"
    set type [lindex [split $name _] 0]
    if { $type == "command" && $name != "command" } {
   puts $fout "
    int [set base]_shm_registerCallback_[set name]_ackcmdLV(int handle, bool skipOld) \{
         return SAL__OK;
    \}
    int [set base]_shm_cancelCallback_[set name]_ackcmdLV() \{
        return SAL__OK;
    \}
"
    }
}


proc genlvlaunchcallbacks { fout base ptypes } {
   puts $fout "
    void [set base]_shm_checkCallbacksLV() \{
   \}
"
}




proc genlvtelemetry { fout base name } {
global SAL_WORK_DIR LVSTRINGS
   puts $fout "
    int [set base]_shm_salTelemetrySub_[set name]LV() \{
        return SAL__OK;
    \}

    int [set base]_shm_getSample_[set name]LV([set base]_[set name]LV *data ) \{
        return SAL__OK;
    \}

    int [set base]_shm_getNextSample_[set name]LV([set base]_[set name]LV *data ) \{
        return SAL__OK;
    \}

    int [set base]_shm_putSample_[set name]LV([set base]_[set name]LV *data ) \{
        return SAL__OK;
    \}
"
}


proc genlvcommand { fout base name } {
global SAL_WORK_DIR LVSTRINGS
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
    int [set base]_shm_issueCommand_[set n2]LV([set base]_[set name]LV *data ) \{
       return 0;
    \}"
   puts $fout "

    int [set base]_shm_salProcessor_[set n2]LV() \{
         return SAL__OK;
    \}

    int [set base]_shm_salCommander_[set n2]LV() \{
        return SAL__OK;
    \}

    int [set base]_shm_monitorCommand_[set n2]LV([set base]_[set name]LV *data ) \{
        return SAL__OK;
    \}

    int [set base]_shm_acceptCommand_[set n2]LV([set base]_[set name]LV *data ) \{
        return SAL__OK;
    \}"
   puts $fout "
    int [set base]_shm_ackCommand_[set n2]LV([set base]_ackcmdLV *theack) \{
        return SAL__OK;
    \}"
   puts $fout "
    int [set base]_shm_waitForCompletion_[set n2]LV([set base]_waitCompleteLV *waitStatus ) \{
   return SAL__OK;
    \}
"
  puts $fout "
    int [set base]_shm_getResponse_[set n2]LV([set base]_ackcmdLV *data) \{
        return SAL__OK;
    \}
"
}




proc genlvlogevent { fout base name } {
global SAL_WORK_DIR LVSTRINGS
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
    int [set base]_shm_salEvent_[set n2]LV() \{
        return SAL__OK;
    \}

    int [set base]_shm_getEvent_[set n2]LV([set base]_[set name]LV *data ) \{
         return SAL__OK;
    \}

    int [set base]_shm_logEvent_[set n2]LV([set base]_[set name]LV *data ) \{
        return SAL__OK;
    \}

    int [set base]_shm_flushSamplesEvent_[set n2]LV() \{
         return SAL__OK;
    \}
"
}




