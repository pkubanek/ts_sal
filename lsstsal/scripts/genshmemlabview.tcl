
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
  genlabviewincl $base $ptypes
  genlabviewcpp  $base $ptypes
  genlabviewmake $base
  gencommandlabviewtests $base
  geneventlabviewtests $base
  gentelemetrylabviewtests $base
}

proc genlabviewmake { subsys } {
global SAL_DIR SAL_WORK_DIR
  set frep [open /tmp/sreplace4.sal w]
  puts $frep "#!/bin/sh"
  exec touch $SAL_WORK_DIR/[set subsys]/labview/.depend.Makefile.sacpp_SALData_labview
  exec cp  $SAL_DIR/code/templates/Makefile.sacpp_SAL_labview.template $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview
  puts $frep "perl -pi -w -e 's/_SAL_/_[set subsys]_/g;' $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview"
  puts $frep "perl -pi -w -e 's/SALSubsys/[set subsys]/g;' $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview"
  puts $frep "perl -pi -w -e 's/SALData/[set subsys]/g;' $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview"
  if { [info exists SYSDIC($subsys,keyedID)] } {
     puts $frep "perl -pi -w -e 's/#-DSAL_SUBSYSTEM/-DSAL_SUBSYSTEM/g;' $SAL_WORK_DIR/[set subsys]/labview/Makefile.sacpp_[set subsys]_labview"
  }
  close $frep
  exec chmod 755 /tmp/sreplace4.sal
  catch { set result [exec /tmp/sreplace4.sal] } bad
  if { $bad != "" } {puts stdout $bad}
}



proc genlabviewincl { base ptypes } {
global SAL_DIR SAL_WORK_DIR SYSDIC TELEMETRY_ALIASES
  set idarg ""
  if { [info exists SYSDIC($base,keyedID)] } {
     set idarg "unsigned int [set base]ID"
  }
  set fout [open $SAL_WORK_DIR/[set base]/labview/SAL_[set base]_shmem.h w]
  set fhlv [open $SAL_WORK_DIR/[set base]/cpp/src/SAL_[set base]LV.h r]
  while  { [gets $fhlv rec] > -1 } {
     puts $fout $rec
  }
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
     puts $fout "	[set base]_[set name]C  shmemIncoming_[set base]_[set name];"	
     puts $fout "	[set base]_[set name]C  shmemOutgoing_[set base]_[set name];"
     if { $type == "command" && $name != "command" } {
        puts $fout "	int shmemOutgoing_[set base]_[set name]_cmdSeqNum;"
        puts $fout "	int shmemIncoming_[set base]_[set name]_rcvSeqNum;"
        puts $fout "	salLONG shmemOutgoing_[set base]_[set name]_cmdStatus;"
        puts $fout "	salLONG shmemOutgoing_[set base]_[set name]_errorCode;"
        puts $fout "	char shmemOutgoing_[set base]_[set name]_resultCode\[128\];"
     }	
  }
  puts $fout "	[set base]_ackcmdC  shmemIncoming_ackcmd;"	
  puts $fout "	[set base]_ackcmdC  shmemOutgoing_ackcmd;"	
  puts $fout "    \};

     int shmSize = sizeof([set base]_shmem);
     int lShmId;
     bool shutdown_shmem;
     int [set base]_shmid = 0x[calcshmid $base];
  
        int [set base]_salShmMonitor($idarg);
        int [set base]_salShmConnect($idarg);
        int [set base]_salShmRelease($idarg);"
  foreach j $ptypes {
     set name [lindex $j 2]
     set n2 [join [lrange [split $name _] 1 end] _]
     set type [lindex [split $name _] 0]
     if { $type == "command" && $name != "command" } {
       puts $fout "
	int [set base]_shm_issueCommand_[set n2]LV([set base]_[set name]C **[set name]_Ctl);
	int [set base]_shm_acceptCommand_[set n2]LV([set base]_[set name]C **[set name]_Ctl);
	int [set base]_shm_ackCommand_[set n2]LV(int cmdSeqNum, salLONG ack, salLONG error, char *result);
	int [set base]_shm_waitForCompletion_[set n2]LV(int cmdSeqNum , unsigned int timeout);
        int [set base]_shm_getResponse_[set n2]LV([set base]_ackcmdC **[set name]_Ctl);"
     } else {
        if { $type == "logevent" && $name != "logevent" } {
           puts $fout "
	int [set base]_shm_getEvent_[set n2]LV([set base]_[set name]C **[set name]_Ctl);
	int [set base]_shm_logEvent_[set n2]LV([set base]_[set name]C **[set name]_Ctl);"
        } else {
           if { $name != "ackcmd" && $name != "command" && $name != "logevent" } {
              lappend TELEMETRY_ALIASES($base) $name
           }
           puts $fout "
	int [set base]_shm_getSample_[set name]LV([set base]_[set name]C **[set name]_Ctl);
	int [set base]_shm_getNextSample_[set name]LV([set base]_[set name]C **[set name]_Ctl);
	int [set base]_shm_putSample_[set name]LV([set base]_[set name]C **[set name]_Ctl);"
        }
     }   
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
global SAL_DIR SAL_WORK_DIR SYSDIC
  set idarg ""
  set idarg2 ""
  set idoff 0
  if { [info exists SYSDIC($base,keyedID)] } {
     set idarg "unsigned int [set base]ID"
     set idarg2 "[set base]ID"
     set idoff "[set base]ID"
  }
  set fout [open $SAL_WORK_DIR/[set base]/labview/SAL_[set base]_salShmMonitor.cpp w]
  puts $fout "
#include <sys/ipc.h>
#include <sys/shm.h>
#include \"SAL_[set base]\.h\"
#include \"SAL_[set base]_shmem\.h\"
#include \"SAL_actors.h\"
using namespace [set base];
"
  puts $fout "
    int [set base]_salShmMonitor ([set idarg]) \{
      int status = 0;

      shutdown_shmem = false;
      int actorIdx = 0;

      [set base]_shmem *[set base]_memIO;
      lShmId = shmget([set base]_shmid + [set idoff], shmSize , IPC_CREAT|0666);
      [set base]_memIO  = ([set base]_shmem *) shmat(lShmId, NULL, 0);
      SAL_[set base] mgr = SAL_[set base]($idarg2);

      while ( !shutdown_shmem ) \{"
  foreach j $ptypes {
     set name [lindex $j 2]
     set type [lindex [split $name _] 0]
     if { $type == "command" && $name != "command" } {
       monitorcommand $fout $base $name
     } else {
        if { $type == "logevent" && $name != "logevent" } {
           monitorlogevent $fout $base $name
        } else {
           monitortelemetry $fout $base $name
        }
     }   
   }
  puts $fout "
      \}
    \}
"
  close $fout
  set fout [open $SAL_WORK_DIR/[set base]/labview/SAL_[set base]_salShm.c w]
  puts $fout "
#include <sys/ipc.h>
#include <sys/shm.h>
#include \"SAL_[set base]\.h\"
#include \"SAL_[set base]_shmem\.h\"
#include \"SAL_actors.h\"
"
  puts $fout "
    [set base]_shmem *[set base]_memIO;

    int [set base]_salShmConnect ([set idarg]) \{

      lShmId = shmget([set base]_shmid + [set idoff], shmSize , IPC_CREAT|0666);
      [set base]_memIO  = ([set base]_shmem *) shmat(lShmId, NULL, 0);
      return SAL__OK;
    \}

    int [set base]_shm_salShmRelease([set idarg]) \{
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
   }
  close $fout
}

proc genlvtelemetry { fout base name } {
global SAL_WORK_DIR
   puts $fout "
    int [set base]_shm_getSample_[set name]LV([set base]_[set name]C **pdata) \{
        struct [set base]_[set name]C *data = *pdata;
        [set base]_memIO->syncI_[set base]_[set name] = true;
        [set base]_memIO->skipOld_[set base]_[set name] = false;
        if ( [set base]_memIO->hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           [set base]_memIO->hasIncoming_[set base]_[set name] = false;
        \} else \{
           return SAL__NO_UPDATES;
        \}
        return SAL__OK;
    \}

    int [set base]_shm_getNextSample_[set name]LV([set base]_[set name]C **pdata) \{
        int status = SAL__NO_UPDATES;
        [set base]_memIO->syncI_[set base]_[set name] = true;
        [set base]_memIO->skipOld_[set base]_[set name] = true;
	status = [set base]_shm_getSample_[set name]LV(pdata);
        return status;
    \}

    int [set base]_shm_putSample_[set name]LV([set base]_[set name]C **pdata) \{
        struct [set base]_[set name]C *data = *pdata;
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

proc genlvcommand { fout base name } {
global SAL_WORK_DIR
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
    int [set base]_shm_issueCommand_[set n2]LV([set base]_[set name]C **pdata) \{
        struct [set base]_[set name]C *data = *pdata;
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
    \}"
   puts $fout "
    int [set base]_shm_acceptCommand_[set n2]LV([set base]_[set name]C **pdata) \{
        struct [set base]_[set name]C *data = *pdata;
        [set base]_memIO->syncI_[set base]_[set name] = true;
        if ( [set base]_memIO->hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           [set base]_memIO->hasIncoming_[set base]_[set name] = false;
        \} else \{
           return SAL__NO_UPDATES;
        \}
        return SAL__OK;
    \}"
   puts $fout "
    int [set base]_shm_ackCommand_[set n2]LV(int cmdSeqNum, salLONG ack, salLONG error, char *result) \{
        [set base]_memIO->syncO_[set base]_ackcmd = true;
        if ([set base]_memIO->hasOutgoing_[set base]_ackcmd) \{ 
           return SAL__ERROR;
        \}"
   puts $fout "
        [set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdSeqNum = cmdSeqNum;
        [set base]_memIO->shmemOutgoing_ackcmd.ack = ack;
        [set base]_memIO->shmemOutgoing_ackcmd.error = error;
        [set base]_memIO->shmemOutgoing_ackcmd.result = result;
        [set base]_memIO->hasOutgoing_[set base]_ackcmd = true;
        return SAL__OK;
    \}"
   puts $fout "
    int [set base]_shm_waitForCompletion_[set n2]LV(int cmdSeqNum , unsigned int timeout ) \{
      int debugLevel = 1;
      salReturn status = SAL__OK;
      int countdown = timeout;
      [set base]_ackcmdC response;
      [set base]_ackcmdC *presponse = &response;
      

   while (status != SAL__CMD_COMPLETE && countdown != 0) \{
      status = [set base]_shm_getResponse_[set n2]LV(&presponse);
      if (status != SAL__CMD_NOACK) \{
        if ([set base]_memIO->shmemIncoming_[set base]_[set name]_rcvSeqNum != cmdSeqNum) \{ 
           status = SAL__CMD_NOACK;
        \}
      \}
      usleep(SAL__SLOWPOLL);
      countdown--;
   \}
   if (status != SAL__CMD_COMPLETE) \{
      if (debugLevel > 0) \{
         cout << \"=== \[waitForCompletion\]_[set n2] command \" << cmdSeqNum <<  \" timed out :\" << endl;
      \} 
   \} else \{
      if (debugLevel > 0) \{
         cout << \"=== \[waitForCompletion\]_[set n2] command \" << cmdSeqNum << \" completed ok :\" << endl;
      \} 
   \}
   return status;
    \}
"
  puts $fout "
    int [set base]_shm_getResponse_[set n2]LV([set base]_ackcmdC **presponse ) \{
        struct [set base]_ackcmdC *response = *presponse;
        ReturnCode_t status = SAL__CMD_NOACK;
        [set base]_memIO->syncI_[set base]_ackcmd = true;
        [set base]_memIO->shmemIncoming_[set base]_[set name]_rcvSeqNum = 0;
        if ( [set base]_memIO->hasIncoming_[set base]_ackcmd ) \{
           [set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdSeqNum = [set base]_memIO->shmemIncoming_[set base]_[set name]_rcvSeqNum;
           response->ack = [set base]_memIO->shmemIncoming_ackcmd.ack;
           response->error = [set base]_memIO->shmemIncoming_ackcmd.error;
           response->result = [set base]_memIO->shmemIncoming_ackcmd.result;
           status = [set base]_memIO->shmemIncoming_ackcmd.ack;
           [set base]_memIO->hasIncoming_[set base]_ackcmd = false;
        \}
        return status;
    \}
"
}



proc genlvlogevent { fout base name } {
global SAL_WORK_DIR
   set n2 [join [lrange [split $name _] 2 end] _]
   puts $fout "
    int [set base]_shm_getEvent_[set n2]LV([set base]_[set name]C **pdata) \{
        struct [set base]_[set name]C *data = *pdata;
        [set base]_memIO->syncI_[set base]_[set name] = true;
        if ( [set base]_memIO->hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           [set base]_memIO->hasIncoming_[set base]_[set name] = false;
        \} else \{
           return SAL__NO_UPDATES;
        \}
        return SAL__OK;
    \}

    int [set base]_shm_logEvent_[set n2]LV([set base]_[set name]C **pdata) \{
        struct [set base]_[set name]C *data = *pdata;
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
global SAL_DIR SAL_WORK_DIR
   puts $fout "
       if ([set base]_memIO->syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorReader(actorIdx) == false) \{
             mgr.salTelemetrySub(actorIdx);
          \}
          if ( [set base]_memIO->hasIncoming_[set base]_[set name] == false ) \{
             status = mgr.getNextSample_[set name](&[set base]_memIO->shmemIncoming_[set base]_[set name]);
             if (status == SAL__OK) \{
                [set base]_memIO->hasIncoming_[set base]_[set name] = true;
             \}
          \}
       \}
       if ([set base]_memIO->syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorReader(actorIdx) == false) \{
             mgr.salTelemetryPub(actorIdx);
          \}
       \}
       if ( [set base]_memIO->hasOutgoing_[set base]_[set name] ) \{
          status = mgr.putSample_[set name](&[set base]_memIO->shmemOutgoing_[set base]_[set name]);
          [set base]_memIO->hasOutgoing_[set base]_[set name] = false;
       \}
"
}


proc monitorcommand { fout base name } {
global SAL_DIR SAL_WORK_DIR
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
       if ([set base]_memIO->syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorProcessor(actorIdx) == false) \{
             mgr.salProcessor(\"[set base]_[set name]\");
          \}
          status = mgr.acceptCommand_[set n2](\&[set base]_memIO->shmemIncoming_[set base]_[set name]);
          if (status == SAL__OK) \{
             [set base]_memIO->hasIncoming_[set base]_[set name] = true;
          \}
       \}
       if ([set base]_memIO->syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorCommand(actorIdx) == false) \{
             mgr.salCommand(\"[set base]_[set name]\");
          \}
       \}
       if ( [set base]_memIO->hasOutgoing_[set base]_[set name] ) \{
          status = mgr.issueCommand_[set n2](&[set base]_memIO->shmemOutgoing_[set base]_[set name]);
          [set base]_memIO->hasOutgoing_[set base]_[set name] = false;
       \}
       if ( [set base]_memIO->hasOutgoing_[set base]_ackcmd ) \{
          status = mgr.ackCommand_[set n2](
				[set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdSeqNum,
				[set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdStatus,
				[set base]_memIO->shmemOutgoing_[set base]_[set name]_errorCode,
				\"\"
                                          );
          [set base]_memIO->hasOutgoing_[set base]_ackcmd = false;
       \}
"
}


proc monitorlogevent { fout base name } {
global SAL_DIR SAL_WORK_DIR
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
       if ([set base]_memIO->syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorEventReader(actorIdx) == false) \{
             mgr.salEvent(\"[set base]_[set name]\");
          \}
          status = mgr.getEvent_[set n2](\&[set base]_memIO->shmemIncoming_[set base]_[set name]);
          if (status == SAL__OK) \{
             [set base]_memIO->hasIncoming_[set base]_[set name] = true;
          \}
       \}
       if ([set base]_memIO->syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (mgr.actorEventWriter(actorIdx) == false) \{
             mgr.salEvent(\"[set base]_[set name]\");
          \}
       \}
       if ( [set base]_memIO->hasOutgoing_[set base]_[set name] ) \{
          status = mgr.logEvent_[set n2](\&[set base]_memIO->shmemOutgoing_[set base]_[set name],1);
          [set base]_memIO->hasOutgoing_[set base]_[set name] = false;
       \}
"
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



