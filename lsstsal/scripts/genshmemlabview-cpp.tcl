
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
  puts $fout "
#include \"extcode.h\"
#include \"SAL_[set base]C\.h\"
   class SAL_[set base]_shmem \{

     struct [set base]_shmem \{"
  foreach j $ptypes {
     set name [lindex $j 2]
     set type [lindex [split $name _] 0]
     puts $fout "	boolean  syncI_[set base]_[set name];"	
     puts $fout "	boolean  syncO_[set base]_[set name];"	
     puts $fout "	boolean  skipOld_[set base]_[set name];"	
     puts $fout "	boolean  hasIncoming_[set base]_[set name];"	
     puts $fout "	boolean  hasOutgoing_[set base]_[set name];"	
     puts $fout "	[set base]_[set name]C  shmemIncoming_[set base]_[set name];"	
     puts $fout "	[set base]_[set name]C  shmemOutgoing_[set base]_[set name];"
     if { $type == "command" && $name != "command" } {
        puts $fout "	unsigned long shmemOutgoing_[set base]_[set name]_cmdId;"
        puts $fout "	long          shmemOutgoing_[set base]_[set name]_cmdStatus;"
        puts $fout "	long          shmemOutgoing_[set base]_[set name]_errorCode;"
        puts $fout "	std::string   shmemOutgoing_[set base]_[set name]_resultText;"
        puts $fout "	long          cmdSeqNum_[set name];"
        puts $fout "	long          rcvSeqNum_[set name];"
        puts $fout "	long          sndSeqNum_[set name];"
     }	
  }
  puts $fout "    \}

     SAL_[set base] mgr;
     int shmSize = sizeof([set base]_shmem);
     int lShmId;
     boolean shutdown;
     int [set base]_shmid = 0x[calcshmid $base];
  
     public:
	SAL_[set base]_shmem();
        int salShmMonitor($idarg);
        int salShmConnect($idarg);
        int salShmRelease($idarg);"
  foreach j $ptypes {
     set name [lindex $j 2]
     set n2 [join [lrange [split $name _] 1 end] _]
     set type [lindex [split $name _] 0]
     if { $type == "command" && $name != "command" } {
       puts $fout "
	int issueCommand_[set n2]LV([set base]_[set name]_lv **[set name]_Ctl);	
	int acceptCommand_[set n2]LV([set base]_[set name]_lv **[set name]_Ctl);
	int ackCommand_[set n2]LV(int cmdId, salLONG ack, salLONG error, char *result);
	int waitForCompletion_[set n2]LV(int cmdSeqNum , unsigned int timeout);
        int getResponse_[set n2]LV([set base]_ackcmd_lv **[set name]_Ctl"	
     } else {
        if { $type == "logevent" && $name != "logevent" } {
           puts $fout "
	int getEvent_[set n2]LV([set base]_[set name]_lv **[set name]_Ctl);	
	int logEvent_[set n2]LV([set base]_[set name]_lv **[set name]_Ctl);"
        } else {
           if { $name != "ackcmd" && $name != "command" && $name != "logevent" } {
              lappend TELEMETRY_ALIASES($base) $name
           }
           puts $fout "
	int getSample_[set name]LV([set base]_[set name]_lv **[set name]_Ctl);	
	int getNextSample_[set name]LV([set base]_[set name]_lv **[set name]_Ctl);	
	int putSample_[set name]LV([set base]_[set name]_lv **[set name]_Ctl);"
        }
     }   
   }
   puts $fout "
   \}
"
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
  set fout [open $SAL_WORK_DIR/[set base]/labview/SAL_[set base]_shmem.cpp w]
  puts $fout "
#include <sys/ipc.h>
#include <sys/shm.h>
#include \"SAL_[set base]\.h\"

using namespace [set base];
"
  puts $fout "
    int SAL_[set base]_shmem::salShmMonitor ([set idarg]) \{
      int status = 0;

      shutdown = false;
      int actorIdx = 0;

      [set base]_shmem *[set base]_memIO;
      lShmId = shmget([set base]_shmid + [set idoff], shmSize , IPC_CREAT|0666);
      [set base]_memIO  = ([set base]_shmem *) shmat(lShmId, NULL, 0);
      SAL_[set base] mgr = SAL_[set base]($idarg2);
      while ( !shutdown ) \{"
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
  puts $fout "
    int SAL_[set base]_shmem::salShmConnect ([set idarg]) \{
      int status = 0;
      int actorIdx = 0;

      [set base]_shmem *[set base]_memIO;
      lShmId = shmget([set base]_shmid + [set idoff], shmSize , IPC_CREAT|0666);
      [set base]_memIO  = ([set base]_shmem *) shmat(lShmId, NULL, 0);
      SAL_[set base] mgr = SAL_[set base]($idarg2);
      return SAL__OK;
    \}

    int SAL_[set base]_shmem::salShmRelease([set idarg]) \{
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
    int SAL_[set base]_shmem::getSample_[set name]LV([set base]_[set name]_lv **data) \{
        int actorIdx = SAL__[set base]_[set name]_ACTOR;
        syncI_[set base]_[set name] = true;
        skipOld_[set base]_[set name] = false;
        if ( hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           hasIncoming_[set base]_[set name] = false;
        \} else \{
           return SAL__NO_SAMPLES;
        \}
        return SAL__OK;
    \}

    int SAL_[set base]_shmem::getNextSample_[set name]LV([set base]_[set name]_lv **data) \{
        int status = SAL__NO_SAMPLES;
        int actorIdx = SAL__[set base]_[set name]_ACTOR;
        syncI_[set base]_[set name] = true;
        skipOld_[set base]_[set name] = true;
	status = getSample_[set name]LV(data);
        return status;
    \}

    int SAL_[set base]_shmem::putSample_[set name]LV([set base]_[set name]_lv **data) \{
        int actorIdx = SAL__[set base]_[set name]_ACTOR;
        syncO_[set base]_[set name] = true;
        if (hasOutgoing_[set base]_[set name]) \{ 
           return SAL__ERROR;
        \}"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmout.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
        hasOutgoing_[set base]_[set name] = true;
        return SAL__OK;
    \}
"
}

proc genlvcommand { fout base name } {
global SAL_WORK_DIR
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
    int SAL_[set base]_shmem::issueCommand_[set n2]LV([set base]_[set name]_lv **data) \{
        int actorIdx = SAL__[set base]_[set name]_ACTOR;
        syncO_[set base]_[set name] = true;
        if (hasOutgoing_[set base]_[set name]) \{ 
           return SAL__ERROR;
        \}"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmout.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
        hasOutgoing_[set base]_[set name] = true;
        return SAL__OK;
    \}"
   puts $fout "
    int SAL_[set base]_shmem::acceptCommand_[set n2]LV([set base]_[set name]_lv **data) \{
        int actorIdx = SAL__[set base]_[set name]_ACTOR;
        syncI_[set base]_[set name] = true;
        if ( hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           hasIncoming_[set base]_[set name] = false;
        \} else \{
           return SAL__NO_SAMPLES;
        \}
        return SAL__OK;
    \}"
   puts $fout "
    int SAL_[set base]_shmem::ackCommand_[set n2]LV(int cmdId, salLONG ack, salLONG error, char *result) \{
        int actorIdx = SAL__[set base]_ackcmd_ACTOR;
        syncO_[set base]_ackcmd = true;
        if (hasOutgoing_[set base]_ackcmd) \{ 
           return SAL__ERROR;
        \}"
   puts $fout "
        [set base]_memIO->shmemOutgoing_ackcmd->cmdId = cmdId;
        [set base]_memIO->shmemOutgoing_ackcmd->ack = ack;
        [set base]_memIO->shmemOutgoing_ackcmd->error = error;
        strcpy([set base]_memIO->shmemOutgoing_ackcmd->result, result);
        hasOutgoing_[set base]_ackcmd = true;
        return SAL__OK;
    \}"
   puts $fout "
    int SAL_[set base]_shmem::waitForCompletion_[set n2]LV(int cmdSeqNum , unsigned int timeout ) \{
      salReturn status = SAL__OK;
      int countdown = timeout;
      [set base]_ackcmdC response;
      int actorIdx = SAL__[set base]_ackcmd_ACTOR;

   while (status != SAL__CMD_COMPLETE && countdown != 0) \{
      status = getResponse_[set n2](response);
      if (status != SAL__CMD_NOACK) \{
        if (rcvSeqNum_[set n2] != cmdSeqNum_[set n2]) \{ 
           status = SAL__CMD_NOACK;
        \}
      \}
      usleep(SAL__SLOWPOLL);
      countdown--;
   \}
   if (status != SAL__CMD_COMPLETE) \{
      if (debugLevel >= SAL__LOG_ROUTINES) \{
          logError(status);
      \}
      if (debugLevel > 0) \{
         cout << \"=== \[waitForCompletion\]_[set n2] command \" << [set n2]_cmdSeqNum <<  \" timed out :\" << endl;
      \} 
   \} else \{
      if (debugLevel > 0) \{
         cout << \"=== \[waitForCompletion\]_[set n2] command \" << [set n2]_cmdSeqNum << \" completed ok :\" << endl;
      \} 
   \}
   return status;
    \}
"
  puts $fout "
    int SAL_[set base]_shmem::getResponse_[set n2]LV([set base]_ackcmdC *response ) \{
        ReturnCode_t status = SAL__CMD_NOACK;
        syncI_[set base]_ackcmd = true;
        rcvSeqNum_[set n2] = 0;
        if ( hasIncoming_[set base]_ackcmd ) \{
           rcvSeqNum_[set n2]= [set base]_memIO->shmemIncoming_ackcmd->cmdId;
           response->cmdId = [set base]_memIO->shmemIncoming_ackcmd->cmdId;
           response->ack = [set base]_memIO->shmemIncoming_ackcmd->ack;
           response->error = [set base]_memIO->shmemIncoming_ackcmd->error;
           strcpy (response->result, [set base]_memIO->shmemIncoming_ackcmd->result);
           status = [set base]_memIO->shmemIncoming_ackcmd->ack;
           hasIncoming_[set base]_ackcmd = false;
        \}
        return status;
    \}
"
}



proc genlvlogevent { fout base name } {
global SAL_WORK_DIR
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
    int SAL_[set base]_shmem::getEvent_[set n2]LV([set base]_[set name]_lv **data) \{
        int actorIdx = SAL__[set base]_[set name]_ACTOR;
        syncI_[set base]_[set name] = true;
        if ( hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           hasIncoming_[set base]_[set name] = false;
        \} else \{
           return SAL__NO_SAMPLES;
        \}
        return SAL__OK;
    \}

    int SAL_[set base]_shmem::logEvent_[set n2]LV([set base]_[set name]_lv **data) \{
        int actorIdx = SAL__[set base]_[set name]_ACTOR;
        syncO_[set base]_[set name] = true;
        if (hasOutgoing_[set base]_[set name]) \{ 
           return SAL__ERROR;
        \}"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmout.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
        hasOutgoing_[set base]_[set name] = true;
        return SAL__OK;
    \}
"
}


proc monitortelemetry { fout base name } {
global SAL_DIR SAL_WORK_DIR
   puts $fout "
       if (syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isReader == false) \{
             mgr.salTelemetrySub(actorIdx);
          \}
          if ( hasIncoming_[set base]_[set name] = false ) \{
             status = mgr.getNextSample_[set name](&[set base]_memIO->shmemIncoming_[set base]_[set name]);
             if (status == SAL__OK) \{
                hasIncoming_[set base]_[set name] = true;
             \}
          \}
       \}
       if (syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isReader == false) \{
             mgr.salTelemetryPub(actorIdx);
          \}
       \}
       if ( hasOutgoing_[set base]_[set name] ) \{
          status = putSample_[set name](&[set base]_memIO->shmemOutgoing_[set base]_[set name])
          hasOutgoing_[set base]_[set name] = false;
       \}
"
}


proc monitorcommand { fout base name } {
global SAL_DIR SAL_WORK_DIR
   set n2 [join [lrange [split $name _] 1 end] _]
   puts $fout "
       if (syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isProcessor == false) \{
             mgr.salProcessor(\"[set base]_[set name]\");
          \}
          status = mgr.acceptCommand_[set n2](\&[set base]_memIO->shmemIncoming_[set base]_[set name]);
          if (status == SAL__OK) \{
             hasIncoming_[set base]_[set name] = true;
          \}
       \}
       if (syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isCommand == false) \{
             mgr.salCommand(\"[set base]_[set name]\");
          \}
       \}
       if ( hasOutgoing_[set base]_[set name] ) \{
          status = mgr.issueCommand_[set n2](&[set base]_memIO->shmemOutgoing_[set base]_[set name])
          hasOutgoing_[set base]_[set name] = false;
       \}
       if ( hasOutgoing_[set base]_ackcmd ) \{
          status = mgr.ackCommand_[set n2](
				\&[set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdId,
				\&[set base]_memIO->shmemOutgoing_[set base]_[set name]_cmdStatus,
				\&[set base]_memIO->shmemOutgoing_[set base]_[set name]_errorCode,
				\&[set base]_memIO->shmemOutgoing_[set base]_[set name]_resultText
                                          );
          hasOutgoing_[set base]_ackcmd = false;
       \}
"
}


proc monitorlogevent { fout base name } {
global SAL_DIR SAL_WORK_DIR
   puts $fout "
       if (syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isEventReader == false) \{
             mgr.salEvent(\"[set base]_[set name]\");
          \}
          status = mgr.getEvent_[set name](\&[set base]_memIO->shmemIncoming_[set base]_[set name]);
          if (status == SAL__OK) \{
             hasIncoming_[set base]_[set name] = true;
          \}
       \}
       if (syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isEventWriter == false) \{
             mgr.salEvent(\"[set base]_[set name]\");
          \}
       \}
       if ( hasOutgoing_[set base]_[set name] ) \{
          status = mgr.logEvent_[set name](\&[set base]_memIO->shmemOutgoing_[set base]_[set name],1)
          hasOutgoing_[set base]_[set name] = false;
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



