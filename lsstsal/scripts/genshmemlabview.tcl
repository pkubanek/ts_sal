
set SAL_DIR $env(SAL_DIR)
set SAL_WORK_DIR $env(SAL_WORK_DIR)
source $SAL_DIR/add_system_dictionary.tcl 
source $SAL_DIR/gencommandlabviewtests.tcl 
source $SAL_DIR/geneventlabviewtests.tcl 
source $SAL_DIR/gentelemetrylabviewtests.tcl 
source $SAL_DIR/utilities.tcl 

proc genshmemlabview { subsys } {
global SAL_DIR SAL_WORK_DIR
  exec mkdir -p $SAL_WORK_DIR/[set subsys]/labview
  set idlfile $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl
  set ptypes [lsort [split [exec grep pragma $idlfile] \n]]
  set base $subsys
  updateLabVIEWTypes $base
  genlabviewidl  $base
  genlabviewincl $base $ptypes
  genlabviewcpp  $base $ptypes
  genlabviewmake $base
  gencommandlabviewtests $base
  geneventlabviewtests $base
  gentelemetrylabviewtests $base
  cd $SAL_WORK_DIR/[set subsys]/labview
  exec ln -sf ../cpp/src/SAL_[set subsys].cpp .
  exec ln -sf ../cpp/src/SAL_actors.h .
  exec ln -sf ../../../lsstsal/include/SAL_defines.h .
  exec ln -sf ../cpp/src/CheckStatus.cpp .
  exec ln -sf ../cpp/src/CheckStatus.h .
  exec make -f Makefile.sacpp_[set subsys]_labview
}

proc genlabviewidl { subsys } {
global SAL_WORK_DIR
   set fin  [open $SAL_WORK_DIR/[set subsys]/cpp/sal_[set subsys].idl r]
   set fout [open $SAL_WORK_DIR/[set subsys]/labview/sal_[set subsys].idl w]
   while { [gets $fin rec] > -1 } {
      set it [string trim $rec "\{\}"]
      if { [lsearch "device\; property\; action\; value\;" [lindex $it 1]] < 0 } {
         puts $fout $rec
      }
   }
   close $fin
   close $fout
}



proc genlabviewmake { subsys } {
global SAL_DIR SAL_WORK_DIR
  set lvv [file tail [glob /usr/local/natinst/LabVIEW*64]]
  set frep [open /tmp/sreplace4.sal w]
  puts $frep "#!/bin/sh"
  exec touch $SAL_WORK_DIR/[set subsys]/labview/.depend.Makefile.sacpp_SALData_labview
  exec cp  $SAL_DIR/code/templates/Makefile.sacpp_SAL_labview.template $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview
  puts $frep "perl -pi -w -e 's/_SAL_/_[set subsys]_/g;' $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview"
  puts $frep "perl -pi -w -e 's/SALSubsys/[set subsys]/g;' $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview"
  puts $frep "perl -pi -w -e 's/SALData/[set subsys]/g;' $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview"
  puts $frep "perl -pi -w -e 's/LabVIEW-2015-64/[set lvv]/g;' $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview"
  if { [info exists SYSDIC($subsys,keyedID)] } {
     puts $frep "perl -pi -w -e 's/#-DSAL_SUBSYSTEM/-DSAL_SUBSYSTEM/g;' $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview"
  }
  close $frep
  exec chmod 755 /tmp/sreplace4.sal
  catch { set result [exec /tmp/sreplace4.sal] } bad
  if { $bad != "" } {puts stdout $bad}
}



proc genlabviewincl { base ptypes } {
global SAL_DIR SAL_WORK_DIR SYSDIC TELEMETRY_ALIASES LVSTRINGS LVSTRPARS
  set idarg ""
  if { [info exists SYSDIC($base,keyedID)] } {
     set idarg "unsigned int [set base]ID"
  }
  set fout [open $SAL_WORK_DIR/[set base]/labview/SAL_[set base]_shmem.h w]
  set fhlv [open $SAL_WORK_DIR/[set base]/cpp/src/SAL_[set base]LV.h r]
  puts $fout "#ifdef BUILD_FOR_LV"
  while  { [gets $fhlv rec] > -1 } {
     if { [string range $rec 0 13] == "typedef struct" } {
        set sname [lindex [string trim $rec "\{"] 2]
        if { $sname != "" } {set LVSTRPARS([set sname]) ""}
     }
     set crec [string trim $rec "\{\}"]
     if { [lindex $crec 0] == "StrHdl" && $sname != "" } {
       set param [string trim [lindex $crec 1] "*;"]
       if { [lsearch "device property action value" $param] < 0 } {
         set LVSTRINGS([set sname]_[set param]) 1
#       set LVSTRINGS([set sname]) "$LVSTRINGS([set sname]), char *$param"
         set LVSTRPARS([set sname]) "$LVSTRPARS([set sname]) $param"
         puts $fout $rec
       }
     } else {
       puts $fout $rec
     }
 }
 puts $fout "#endif
"
  close $fhlv
  puts $fout "
#define salLONG long
     struct [set base]_shmem \{"
  foreach j $ptypes {
     set name [lindex $j 2]
     set type [lindex [split $name _] 0]
     puts $fout "	bool  syncI_[set base]_[set name];"	
     puts $fout "	bool  syncO_[set base]_[set name];"	
     puts $fout "	bool  skipOld_[set base]_[set name];"	
     puts $fout "	bool  hasIncoming_[set base]_[set name];"	
     puts $fout "	bool  hasOutgoing_[set base]_[set name];"
     puts $fout "	bool  hasCallback_[set base]_[set name];"	
     puts $fout "	long  callbackHdl_[set base]_[set name];"	
     puts $fout "	bool  hasReader_[set base]_[set name];"	
     puts $fout "	bool  hasWriter_[set base]_[set name];"	
     if { $name != "command" && $name != "logevent" } {
       puts $fout "	[set base]_[set name]C  shmemIncoming_[set base]_[set name];"	
       puts $fout "	[set base]_[set name]C  shmemOutgoing_[set base]_[set name];"
     }
     if { $type == "command" && $name != "command" } {
        puts $fout "	int shmemOutgoing_[set base]_[set name]_cmdSeqNum;"
        puts $fout "	int shmemIncoming_[set base]_[set name]_rcvSeqNum;"
        puts $fout "	salLONG shmemOutgoing_[set base]_[set name]_cmdStatus;"
        puts $fout "	salLONG shmemOutgoing_[set base]_[set name]_errorCode;"
        puts $fout "	salLONG shmemIncoming_[set base]_[set name]_cmdStatus;"
        puts $fout "	salLONG shmemIncoming_[set base]_[set name]_errorCode;"
        puts $fout "	char *shmemOutgoing_[set base]_[set name]_resultCode;"
        puts $fout "	char *shmemIncoming_[set base]_[set name]_resultCode;"
     }
#puts stdout "reading  $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmstr.tmp"
#     if { $name != "ackcmd" && $name != "command" && $name != "logevent" } {
#       set fstrb [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmstr.tmp r]
#       while { [gets $fstrb rec] > -1 } {
#          puts $fout $rec
#       }
#       close $fstrb
#     }
  }
  foreach lvs [lsort [array names LVSTRINGS]] {
     puts $fout "
      char [set lvs]_bufferOut\[128\];
      char [set lvs]_bufferIn\[128\];
    "
  }
  puts $fout "	[set base]_ackcmdC shmemIncoming_ackcmd;"
  puts $fout "  [set base]_ackcmdC shmemOutgoing_ackcmd;"
  puts $fout "    \};

     int shmSize = sizeof([set base]_shmem);
     int lShmId;
     bool shutdown_shmem;
     int [set base]_shmid = 0x[calcshmid $base];
  
        int [set base]_salShmMonitor($idarg);
        int [set base]_salShmConnect($idarg);
        int [set base]_salShmRelease($idarg);
        void [set base]_shm_checkCallbacksLV();
"
  foreach j $ptypes {
     set name [lindex $j 2]
     set n2 [join [lrange [split $name _] 1 end] _]
     set type [lindex [split $name _] 0]
#     if { [info exists LVSTRINGS([set base]_[set name]C)] } {
#        set xtrargs  $LVSTRINGS([set base]_[set name]C)
#        set xtrargs2 $LVSTRPARS([set base]_[set name]C)
#     } else {
        set xtrargs ""
        set xtrargs2 ""
#     }
     if { $type == "command" && $name != "command" } {
       puts $fout "
	int [set base]_shm_issueCommand_[set n2]LV([set base]_[set name]LV *[set name]_Ctl $xtrargs);
	int [set base]_shm_acceptCommand_[set n2]LV([set base]_[set name]LV *[set name]_Ctl $xtrargs);
	int [set base]_shm_ackCommand_[set n2]LV([set base]_ackcmdLV *ackcmd_Ctl);
	int [set base]_shm_waitForCompletion_[set n2]LV([set base]_waitCompleteLV *waitComplete_Ctl);
        int [set base]_shm_getResponse_[set n2]LV([set base]_ackcmdLV *ackcmd_Ctl);"
     } else {
        if { $type == "logevent" && $name != "logevent" } {
           puts $fout "
	int [set base]_shm_getEvent_[set n2]LV([set base]_[set name]LV *[set name]_Ctl $xtrargs);
	int [set base]_shm_logEvent_[set n2]LV([set base]_[set name]LV *[set name]_Ctl $xtrargs);"
        } else {
           if { $name != "ackcmd" && $name != "command" && $name != "logevent" } {
              lappend TELEMETRY_ALIASES($base) $name
           }
           if { $name != "command" && $name != "logevent" } {
             puts $fout "
  	     int [set base]_shm_getSample_[set name]LV([set base]_[set name]LV *[set name]_Ctl $xtrargs);
	     int [set base]_shm_getNextSample_[set name]LV([set base]_[set name]LV *[set name]_Ctl $xtrargs);
	     int [set base]_shm_putSample_[set name]LV([set base]_[set name]LV *[set name]_Ctl $xtrargs);"
           }
        }
     }   
     puts $fout "        int [set base]_shm_registerCallback_[set name]LV(long handle, bool skipOld);"
     puts $fout "        int [set base]_shm_cancelCallback_[set name]LV();"
   }
  close $fout
}

proc updateLabVIEWTypes { subsys } {
global SAL_DIR SAL_WORK_DIR
   set fin [open $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl r]
   set fout [open $SAL_DIR/../../ts_SALLabVIEW/SALTypeGenerator/IDLs/sal_[set subsys].idl w]
   while { [gets $fin rec] > -1 } {
      set t [string trim $rec "\{\}"]
      if { [string range [lindex $t 1] 0 7] != "private_" } {
         puts $fout $rec
      }
   }
   close $fin
   close $fout
}

proc genlabviewcpp { base ptypes } {
global SAL_DIR SAL_WORK_DIR SYSDIC LVSTRINGS LVSTRPARS
  set idarg ""
  set idarg2 ""
  set idarg3 "     unsigned int [set base]ID = 0;"
  set idoff "[set base]ID"
  if { [info exists SYSDIC($base,keyedID)] } {
     set idarg "unsigned int [set base]ID"
     set idarg2 "[set base]ID"
  }
  set fout [open $SAL_WORK_DIR/[set base]/labview/SAL_[set base]_salShmMonitor.cpp w]
  puts $fout "
#include <sys/ipc.h>
#include <sys/shm.h>
#include \"SAL_[set base].h\"
#define BUILD_FOR_LV
#include \"SAL_[set base]_shmem.h\"
#include \"SAL_actors.h\"
using namespace [set base];
"
  puts $fout "
    int main (int argc, char *argv\[\]) \{
      int status = 0;
      long lpriority = 0;
      int [set idoff] = 0;

      if (argc > 1) \{
         sscanf(argv\[1\], \"%d\", &[set idoff]);
      \}
      shutdown_shmem = false;
      int actorIdx = 0;
      [set base]_shmem *[set base]_memIO;
      lShmId = shmget([set base]_shmid + [set idoff], shmSize , IPC_CREAT|0666);
      [set base]_memIO  = ([set base]_shmem *) shmat(lShmId, NULL, 0);
      SAL_[set base] mgr = SAL_[set base]($idarg2);"
  foreach j $ptypes {
     set name [lindex $j 2]
     monitorsyncinit $fout $base $name
  }
  puts $fout "       [set base]::ackcmdSeq [set base]_ackcmdSeq;"
  puts $fout "      while ( !shutdown_shmem ) \{"
  foreach j $ptypes {
     set name [lindex $j 2]
     set type [lindex [split $name _] 0]
     if { $type == "command" && $name != "command" } {
       monitorcommand $fout $base $name
     } else {
        if { $type == "logevent" && $name != "logevent" } {
           monitorlogevent $fout $base $name
        } else {
           if { $name != "ackcmd" && $name != "command" && $name != "logevent" } {
              monitortelemetry $fout $base $name
           }
        }
     }   
   }
  puts $fout "
        usleep(100);
      \}
       exit(0);
    \}
"
  close $fout
  set fout [open $SAL_WORK_DIR/[set base]/labview/SAL_[set base]_salShm.cpp w]
  puts $fout "
#include <sys/ipc.h>
#include <sys/shm.h>
#include \"extcode.h\"
#include \"SAL_[set base].h\"
extern \"C\" \{
#include \"SAL_defines.h\"
#define BUILD_FOR_LV
#include \"SAL_[set base]_shmem.h\"
#include \"SAL_actors.h\"
#define ReturnCode_t int

"
  puts $fout "
    [set idarg3]
    [set base]_shmem *[set base]_memIO;

    int [set base]_salShmConnect ([set idarg]) \{

      lShmId = shmget([set base]_shmid + [set idoff], shmSize , IPC_CREAT|0666);
      [set base]_memIO  = ([set base]_shmem *) shmat(lShmId, NULL, 0);
      return SAL__OK;
    \}

    int [set base]_salShmRelease([set idarg]) \{
      return SAL__OK;
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
  puts $fout "\}
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
    int [set base]_shm_registerCallback_[set name]LV(long handle, bool skipOld) \{
        [set base]_memIO->syncI_[set base]_[set name] = true;
        [set base]_memIO->skipOld_[set base]_[set name] = skipOld;
        while ([set base]_memIO->hasReader_[set base]_[set name] == false) \{
           usleep(1000);
        \}
        [set base]_memIO->hasCallback_[set base]_[set name] = true;
        [set base]_memIO->callbackHdl_[set base]_[set name] = handle;
        return SAL__OK;
    \}
    int [set base]_shm_cancelCallback_[set name]LV() \{
        [set base]_memIO->hasCallback_[set base]_[set name] = false;
        [set base]_memIO->callbackHdl_[set base]_[set name] = 0;
        return SAL__OK;
    \}
"
}


proc genlvlaunchcallbacks { fout base ptypes } {
   puts $fout "
    void [set base]_shm_checkCallbacksLV() \{
       int salActorIdx=0;"
   foreach j $ptypes {
     set name [lindex $j 2]
     puts $fout "
        if ( [set base]_memIO->hasCallback_[set base]_[set name] ) \{
           if ( [set base]_memIO->hasIncoming_[set base]_[set name] ) \{
              [set base]_memIO->hasCallback_[set base]_[set name] = false;
              salActorIdx=SAL__[set base]_[set name]_ACTOR;
              PostLVUserEvent([set base]_memIO->callbackHdl_[set base]_[set name], &salActorIdx);
           \}
        \}"
   }
   puts $fout "
   \}
"
}




proc genlvtelemetry { fout base name } {
global SAL_WORK_DIR LVSTRINGS LVSTRPARS
#     if { [info exists LVSTRINGS([set base]_[set name]C)] } {
#        set xtrargs  [join $LVSTRINGS([set base]_[set name]C)]
#        set xtrargs2 [join $LVSTRPARS([set base]_[set name]C)]
#     } else {
        set xtrargs ""
        set xtrargs2 ""
#     }
   puts $fout "
    int [set base]_shm_getSample_[set name]LV([set base]_[set name]LV *data $xtrargs) \{
        [set base]_memIO->syncI_[set base]_[set name] = true;
        [set base]_memIO->skipOld_[set base]_[set name] = false;
        while ([set base]_memIO->hasReader_[set base]_[set name] == false) \{
           usleep(1000);
        \}
        if ( [set base]_memIO->hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           [set base]_memIO->hasIncoming_[set base]_[set name] = false;
        \} else \{
           return SAL__NO_UPDATES;
        \}
        if ([set base]_memIO->callbackHdl_[set base]_[set name] > 0) \{
           [set base]_memIO->hasCallback_[set base]_[set name] = true;
        \}
        return SAL__OK;
    \}

    int [set base]_shm_getNextSample_[set name]LV([set base]_[set name]LV *data $xtrargs) \{
        int status = SAL__NO_UPDATES;
        [set base]_memIO->syncI_[set base]_[set name] = true;
        [set base]_memIO->skipOld_[set base]_[set name] = true;
	status = [set base]_shm_getSample_[set name]LV(data $xtrargs2);
        return status;
    \}

    int [set base]_shm_putSample_[set name]LV([set base]_[set name]LV *data $xtrargs) \{
        [set base]_memIO->syncO_[set base]_[set name] = true;
        while ([set base]_memIO->hasWriter_[set base]_[set name] == false) \{
           usleep(1000);
        \}
        if ([set base]_memIO->hasOutgoing_[set base]_[set name]) \{ 
           return SAL__ERROR;
        \}"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmout.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
        [set base]_memIO->hasOutgoing_[set base]_[set name] = true;
        while ([set base]_memIO->hasOutgoing_[set base]_[set name] == true) \{
           usleep(1000);
        \}
        return SAL__OK;
    \}
"
}

proc genlvcommand { fout base name } {
global SAL_WORK_DIR LVSTRINGS LVSTRPARS
#     if { [info exists LVSTRINGS([set base]_[set name]C)] } {
#        set xtrargs  [join $LVSTRINGS([set base]_[set name]C)]
#        set xtrargs2 [join $LVSTRPARS([set base]_[set name]C)]
#     } else {
        set xtrargs ""
        set xtrargs2 ""
#     }
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
    int [set base]_shm_issueCommand_[set n2]LV([set base]_[set name]LV *data $xtrargs) \{
        int cmdId = 0;
        [set base]_memIO->syncO_[set base]_[set name] = true;
        while ([set base]_memIO->hasWriter_[set base]_[set name] == false) \{
           usleep(1000);
        \}
        if ([set base]_memIO->hasOutgoing_[set base]_[set name]) \{ 
           return SAL__ERROR;
        \}"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmout.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
        [set base]_memIO->hasOutgoing_[set base]_[set name] = true;
        cmdId = [set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdSeqNum;
        while (cmdId == 0) \{
           cmdId = [set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdSeqNum;
           usleep(1000);
        \}
        [set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdSeqNum = 0;
        return cmdId;
    \}"
   puts $fout "
    int [set base]_shm_acceptCommand_[set n2]LV([set base]_[set name]LV *data $xtrargs) \{
        int cmdId;
        [set base]_memIO->syncI_[set base]_[set name] = true;
        while ([set base]_memIO->hasReader_[set base]_[set name] == false) \{
           usleep(1000);
        \}
        if ( [set base]_memIO->hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           cmdId = [set base]_memIO->shmemIncoming_[set base]_[set name]_rcvSeqNum;
           [set base]_memIO->hasIncoming_[set base]_[set name] = false;
           if (cmdId != 0) \{
              [set base]_memIO->shmemIncoming_[set base]_[set name]_rcvSeqNum = 0;
              return cmdId;
           \}
        \} else \{
           return SAL__NO_UPDATES;
        \}
        if ([set base]_memIO->callbackHdl_[set base]_[set name] > 0) \{
           [set base]_memIO->hasCallback_[set base]_[set name] = true;
        \}
        return SAL__OK;
    \}"
   puts $fout "
    int [set base]_shm_ackCommand_[set n2]LV([set base]_ackcmdLV *theack) \{
        [set base]_memIO->syncO_[set base]_ackcmd = true;
        while ([set base]_memIO->hasWriter_[set base]_ackcmd == false) \{
           usleep(1000);
        \}
        if ([set base]_memIO->hasOutgoing_[set base]_ackcmd) \{ 
           return SAL__ERROR;
        \}"
   puts $fout "
        [set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdSeqNum = theack->cmdSeqNum;
        [set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdStatus = theack->ack;
        [set base]_memIO->shmemOutgoing_[set base]_[set name]_errorCode = theack->error;
        int resultSize = (*(theack->result))->size;
        strncpy([set base]_memIO->shmemOutgoing_[set base]_[set name]_resultCode, (*(theack->result))->data, resultSize);
        [set base]_memIO->hasOutgoing_[set base]_ackcmd = true;
        return SAL__OK;
    \}"
   puts $fout "
    int [set base]_shm_waitForCompletion_[set n2]LV([set base]_waitCompleteLV *waitStatus ) \{
      int debugLevel = 1;
      salReturn status = SAL__OK;
      int countdown = waitStatus->timeout;
      [set base]_ackcmdLV response;
      char *result=(char *)malloc(128);

   while (status != SAL__CMD_COMPLETE && countdown != 0) \{
      status = [set base]_shm_getResponse_[set n2]LV(&response);
      if (status != SAL__CMD_NOACK) \{
        if ([set base]_memIO->shmemIncoming_[set base]_[set name]_rcvSeqNum != waitStatus->cmdSeqNum) \{ 
           status = SAL__CMD_NOACK;
        \}
      \}
      usleep(SAL__SLOWPOLL);
      countdown--;
   \}
   if (status != SAL__CMD_COMPLETE) \{
      if (debugLevel > 0) \{
//         cout << \"=== \[waitForCompletion\]_[set n2] command \" << cmdSeqNum <<  \" timed out :\" << endl;
      \} 
   \} else \{
      if (debugLevel > 0) \{
//         cout << \"=== \[waitForCompletion\]_[set n2] command \" << cmdSeqNum << \" completed ok :\" << endl;
      \} 
   \}
   free(result);
   return status;
    \}
"
  puts $fout "
    int [set base]_shm_getResponse_[set n2]LV([set base]_ackcmdLV *data) \{
        ReturnCode_t status = SAL__CMD_NOACK;
        [set base]_memIO->syncI_[set base]_ackcmd = true;
        while ([set base]_memIO->hasReader_[set base]_ackcmd == false) \{
           usleep(1000);
        \}
        if ( [set base]_memIO->hasIncoming_[set base]_ackcmd ) \{
           data->ack = [set base]_memIO->shmemIncoming_[set base]_[set name]_cmdStatus;
           data->error = [set base]_memIO->shmemIncoming_[set base]_[set name]_errorCode;
           int resultSize = sizeof(int) + 32;
           (*(data->result))->size = resultSize;
           NumericArrayResize(5, 1, (UHandle*)(&(data->result)), resultSize);
           for (int i=0;i<32;i++)\{(*(data->result))->data\[i\] = [set base]_memIO->[set base]_ackcmdLV_result_bufferIn\[i\];\}
           status = [set base]_memIO->shmemIncoming_ackcmd.ack;
           [set base]_memIO->hasIncoming_[set base]_ackcmd = false;
           if ([set base]_memIO->callbackHdl_[set base]_ackcmd > 0) \{
              [set base]_memIO->hasCallback_[set base]_ackcmd = true;
           \}
        \}
        return status;
    \}
"
}



proc genlvlogevent { fout base name } {
global SAL_WORK_DIR LVSTRINGS LVSTRPARS
#     if { [info exists LVSTRINGS([set base]_[set name]C)] } {
#        set xtrargs  [join $LVSTRINGS([set base]_[set name]C)]
#        set xtrargs2 [join $LVSTRPARS([set base]_[set name]C)]
#     } else {
        set xtrargs ""
        set xtrargs2 ""
#     }
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
    int [set base]_shm_getEvent_[set n2]LV([set base]_[set name]LV *data $xtrargs) \{
        [set base]_memIO->syncI_[set base]_[set name] = true;
        while ([set base]_memIO->hasReader_[set base]_[set name] == false) \{
           usleep(1000);
        \}
        if ( [set base]_memIO->hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           [set base]_memIO->hasIncoming_[set base]_[set name] = false;
        \} else \{
           return SAL__NO_UPDATES;
        \}
        if ([set base]_memIO->callbackHdl_[set base]_[set name] > 0) \{
           [set base]_memIO->hasCallback_[set base]_[set name] = true;
        \}
        return SAL__OK;
    \}

    int [set base]_shm_logEvent_[set n2]LV([set base]_[set name]LV *data $xtrargs) \{
        [set base]_memIO->syncO_[set base]_[set name] = true;
        if ([set base]_memIO->hasOutgoing_[set base]_[set name]) \{ 
           return SAL__ERROR;
        \}"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmout.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
        [set base]_memIO->hasOutgoing_[set base]_[set name] = true;
        return SAL__OK;
    \}
"
}


proc monitortelemetry { fout base name } {
global SAL_DIR SAL_WORK_DIR LVSTRPARS
   puts $fout "
       if ([set base]_memIO->syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorReader(actorIdx) == false) \{
             mgr.salTelemetrySub(actorIdx);
             [set base]_memIO->hasReader_[set base]_[set name] = true;
          \}
          if ( [set base]_memIO->hasIncoming_[set base]_[set name] == false ) \{
            if ( [set base]_memIO->skipOld_[set base]_[set name] == true ) \{
                status = mgr.getSample_[set name](Incoming_[set base]_[set name]);
             \} else \{
                status = mgr.getNextSample_[set name](Incoming_[set base]_[set name]);
             \}
             if (status == SAL__OK) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]monin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
                [set base]_memIO->hasIncoming_[set base]_[set name] = true;
             \}
          \}
       \}
       if ([set base]_memIO->syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorWriter(actorIdx) == false) \{
             mgr.salTelemetryPub(actorIdx);
             [set base]_memIO->hasWriter_[set base]_[set name] = true;
          \}
       \}
       if ( [set base]_memIO->hasOutgoing_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]monout.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
          status = mgr.putSample_[set name](Outgoing_[set base]_[set name]);
          [set base]_memIO->hasOutgoing_[set base]_[set name] = false;
       \}
"
}


proc monitorcommand { fout base name } {
global SAL_DIR SAL_WORK_DIR LVSTRPARS
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
       if ([set base]_memIO->syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorProcessor(actorIdx) == false) \{
             mgr.salProcessor(\"[set base]_[set name]\");
             [set base]_memIO->hasReader_[set base]_[set name] = true;
          \}
          status = mgr.acceptCommand_[set n2](Incoming_[set base]_[set name]);
          if (status > 0) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]monin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts  $fout "
             [set base]_memIO->hasIncoming_[set base]_[set name] = true;
             [set base]_memIO->shmemIncoming_[set base]_[set name]_rcvSeqNum = status;
          \}
       \}
       if ([set base]_memIO->syncI_[set base]_ackcmd) \{
          actorIdx = SAL__[set base]_ackcmd_ACTOR;
          status = mgr.getResponse_[set n2]([set base]_ackcmdSeq);
          [set base]_memIO->hasReader_[set base]_ackcmd = true;
          if (status == SAL__CMD_COMPLETE) \{
             strcpy([set base]_memIO->shmemIncoming_[set base]_[set name]_resultCode,[set base]_ackcmdSeq\[0\].result);
             [set base]_memIO->shmemIncoming_[set base]_[set name]_cmdStatus = [set base]_ackcmdSeq\[0\].ack;
             [set base]_memIO->shmemIncoming_[set base]_[set name]_errorCode = [set base]_ackcmdSeq\[0\].error;
             [set base]_memIO->hasIncoming_[set base]_ackcmd = true;
          \}
       \}
       if ([set base]_memIO->syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorCommand(actorIdx) == false) \{
             mgr.salCommand(\"[set base]_[set name]\");
          \}
       \}
       if ( [set base]_memIO->hasOutgoing_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]monout.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
          status = mgr.issueCommand_[set n2](Outgoing_[set base]_[set name]);
          [set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdSeqNum = status;
          [set base]_memIO->hasOutgoing_[set base]_[set name] = false;
          [set base]_memIO->hasWriter_[set base]_[set name] = true;
       \}
       if ( [set base]_memIO->hasOutgoing_[set base]_ackcmd ) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorProcessor(actorIdx) == false) \{
             mgr.salProcessor(\"[set base]_[set name]\");
             [set base]_memIO->hasWriter_[set base]_ackcmd = true;
          \}
          status = mgr.ackCommand_[set n2](
				[set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdSeqNum,
				[set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdStatus,
				[set base]_memIO->shmemOutgoing_[set base]_[set name]_errorCode,
				[set base]_memIO->shmemOutgoing_[set base]_[set name]_resultCode
                                          );
          [set base]_memIO->hasOutgoing_[set base]_ackcmd = false;
       \}
"
}


proc monitorlogevent { fout base name } {
global SAL_DIR SAL_WORK_DIR LVSTRPARS
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
       if ([set base]_memIO->syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorEventReader(actorIdx) == false) \{
             mgr.salEvent(\"[set base]_[set name]\");
             [set base]_memIO->hasReader_[set base]_[set name] = true;
          \}
          status = mgr.getEvent_[set n2](Incoming_[set base]_[set name]);
          if (status == SAL__OK) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]monin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
             [set base]_memIO->hasIncoming_[set base]_[set name] = true;
          \}
       \}
       if ([set base]_memIO->syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorEventWriter(actorIdx) == false) \{
             mgr.salEvent(\"[set base]_[set name]\");
             [set base]_memIO->hasWriter_[set base]_[set name] = true;
          \}
       \}
       if ( [set base]_memIO->hasOutgoing_[set base]_[set name] ) \{
          lpriority = [set base]_memIO->shmemOutgoing_[set base]_[set name].priority;"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]monout.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
          status = mgr.logEvent_[set n2](Outgoing_[set base]_[set name],lpriority);
          [set base]_memIO->hasOutgoing_[set base]_[set name] = false;
       \}
"
}


proc monitorsyncinit { fout base name } {
global SAL_DIR SAL_WORK_DIR
   set n2 [join [lrange [split $name _] 1 end] _]
   set type [lindex [split $name _] 0]
   puts $fout "
       [set base]_memIO->syncI_[set base]_[set name] = false;
       [set base]_memIO->hasIncoming_[set base]_[set name] = false;
       [set base]_memIO->hasCallback_[set base]_[set name] = false;
       [set base]_memIO->syncO_[set base]_[set name] = false;
       [set base]_memIO->callbackHdl_[set base]_[set name] = 0;
       [set base]_memIO->hasOutgoing_[set base]_[set name] = false;
       [set base]_memIO->skipOld_[set base]_[set name] = false;
       [set base]_memIO->hasReader_[set base]_[set name] = false;
       [set base]_memIO->hasWriter_[set base]_[set name] = false;
       [set base]_[set name]C *Incoming_[set base]_[set name] = new [set base]_[set name]C;
       [set base]_[set name]C *Outgoing_[set base]_[set name] = new [set base]_[set name]C;"
     if { $type == "command" && $name != "command" } {
       puts $fout "    
       [set base]_memIO->shmemOutgoing_[set base]_[set name]_resultCode = (char *)malloc(128);
       [set base]_memIO->shmemIncoming_[set base]_[set name]_resultCode = (char *)malloc(128);
"
     }
}

proc modlabviewpubsubexamples { id } {
global SAL_DIR SAL_WORK_DIR
  set fin [open $SAL_DIR/code/templates/SALLVDataPublisher.cpp.template r]
  set fout [open $SAL_WORK_DIR/[set id]/labview/[set id]LVDataPublisher.cpp w]
  while { [gets $fin rec] > -1 } {
      puts $fout $rec
      if { [string range $rec 0 19] == "// INSERT_SAL_SHMOUT" } {
         set frag [open $SAL_WORK_DIR/include/SAL_[set id]shmout.tmp r]
         while { [gets $frag r2] > -1 } {puts $fout $r2}
         close $frag         
      }
  }
  close $fin
  close $fout
  set fin [open $SAL_DIR/code/templates/SALLVDataSubscriber.cpp.template r]
  set fout [open $SAL_WORK_DIR/[set id]/labview/[set id]LVDataSubscriber.cpp w]
  while { [gets $fin rec] > -1 } {
      puts $fout $rec
      if { [string range $rec 0 18] == "// INSERT_SAL_SHMIN" } {
         set frag [open $SAL_WORK_DIR/include/SAL_[set id]shmin.tmp r]
         while { [gets $frag r2] > -1 } {puts $fout $r2}
         close $frag         
      }
  }
  close $fin
  close $fout
}



