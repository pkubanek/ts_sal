
set SAL_DIR $env(SAL_DIR)
set SAL_WORK_DIR $env(SAL_WORK_DIR)

proc genshmemlabview { subsys } {
global SAL_DIR SAL_WORK_DIR
  exec mkdir -p $SAL_WORK_DIR/[set subsys]/labview
  set idlfile $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl
  set ptypes [lsort [split [exec grep pragma $idlfile] \n]]
  set base $subsys
  genlabviewincl $base $ptypes
  genlabviewcpp  $base $ptypes
}


proc genlabviewincl { base ptypes } {
global SAL_DIR SAL_WORK_DIR
  set fout [open $SAL_WORK_DIR/[set subsys]/labview/SAL_[set base]_shmem.h w]
  puts $fout "
#include \"extcode.h\"
#include \"SAL_[set base]C\.h\"
   class SAL_[set base]_shmem \{

     struct [set base]_shmem \{"
  foreach j $ptypes {
     set name [lindex $j 2]
     puts $fout "	boolean  syncI_[set base]_[set name];"	
     puts $fout "	boolean  syncO_[set base]_[set name];"	
     puts $fout "	[set base]_[set name]C  shmemIncoming_[set base]_[set name];"	
     puts $fout "	[set base]_[set name]C  shmemOutgoing_[set base]_[set name];"	
  }
  puts $fout "    \}

     SAL_[set base] mgr;
     int shmSize = sizeof(SAL_[set base]_shmem);
     int lShmId;
     boolean shutdown;
     int [set base]_shmid = 0x[calcshmid $subsys];
  
     public:
	SAL_[set base]_shmem();
        int salShmMonitor();
        int salShmRelease();"
  foreach j $ptypes {
     set name [lindex $j 2]
     set n2 [join [lrange [split $name _] 1 end] _]
     set type [lindex [split $name _] 0]
     if { $type == "command" } {
       puts $fout "
	int issueCommandLV_[set n2]([set base]_[set name]_lv **[set name]_Ctl);	
	int acceptCommandLV_[set n2]([set base]_[set name]_lv **[set name]_Ctl);
	int ackCommandLV_[set n2]([set base]_[set name]_lv **[set name]_Ctl);
	int waitForCompletionLV_[set n2]([set base]_[set name]_lv **[set name]_Ctl);"	
     } else {
        if { $type == "logevent" } {
           puts $fout "
	int getEventLV_[set n2]([set base]_[set name]_lv **[set name]_Ctl);	
	int logEventLV_[set n2]([set base]_[set name]_lv **[set name]_Ctl);"
        } else {
           puts $fout "
	int getSampleLV_[set name]([set base]_[set name]_lv **[set name]_Ctl);	
	int putSampleLV_[set name]([set base]_[set name]_lv **[set name]_Ctl);"
        }
     }   
   }
   puts $fout "
   \}
"
  close $fout
}


proc genlabviewcpp { base ptypes } {
global SAL_DIR SAL_WORK_DIR
  set fout [open $SAL_WORK_DIR/[set subsys]/labview/SAL_[set base]_shmem.cpp w]
  puts $fout "
#include \"SAL_[set base]\.h\
using namespace [set base];

    int SAL_[set base]_shmem::salShmMonitor \{
      int status = 0;

      shutdown = false;
      int actorIdx = 0;

      [set base]_memIO *SAL_[set base]_shmem;
      lShmId = shmget([set base]_shmid, shmsize , IPC_CREAT|0666);
      [set base]_memIO  = (SAL_[set base]_shmem *) shmat(lShmId, NULL, 0);
      SAL_[set base] mgr = SAL_[set base]();
      while ( !shutdown ) \{"
  foreach j $ptypes {
     set name [lindex $j 2]
     set type [lindex [split $name _] 0]
     if { $type == "command" } {
       set n2 [join [lrange [split $name _] 1 end] _]
       monitorcommand $fout $base $name
     } else {
        if { $type == "logevent" } {
           set n2 [join [lrange [split $name _] 1 end] _]
           monitorlogevent $fout $base $name
        } else {
           monitortelemetry $fout $base $name
        }
     }   
   }
  puts $fout "
    \}
"
  foreach j $ptypes {
     set name [lindex $j 2]
     set type [lindex [split $name _] 0]
     if { $type == "command" } {
       set n2 [join [lrange [split $name _] 1 end] _]
       genlvcommand $fout $base $name
     } else {
        if { $type == "logevent" } {
           set n2 [join [lrange [split $name _] 1 end] _]
           genlvlogevent $fout $base $name
        } else {
           genlvtelemetry $fout $base $name
        }
     }   
   }

  close $fout
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


proc genlvtelemetry { fout base name } {
   puts $fout "
    int SAL_[set base]_shmem::getSampleLV_[set name]([set base]_[set name]_lv **data) \{
        int actorIdx = SAL__[set base]_[set name]_ACTOR;
        syncI_[set base]_[set name] = true;
        if ( hasIncoming_[set base]_[set name] ) \{"
   set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]shmin.tmp r]
   while { [gets $frag rec] > -1} {puts $fout $rec}
   close $frag
   puts $fout "
           hasIncoming_[set base]_[set name] = false;
        \} else ]{
           return SAL__NO_SAMPLES;
        \}
        return SAL__OK;
    \}

    int SAL_[set base]_shmem::putSampleLV_[set name]([set base]_[set name]_lv **data) \{
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

proc monitorcommand { fout base name } {
global SAL_DIR SAL_WORK_DIR
   puts $fout "
       if (syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isProcessor == false) \{
             mgr.salProcessor("[set base]_[set name]");
          \}
          status = mgr.acceptCommand_[set name](&[set base]_memIO->shmemIncoming_[set base]_[set name]);
          if (status == SAL__OK) \{
             hasIncoming_[set base]_[set name] = true;
          \}
       \}
       if (syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isCommand == false) \{
             mgr.salCommand("[set base]_[set name]");
          \}
       \}
       if ( hasOutgoing_[set base]_[set name] ) \{
          status = mgr.issueCommand_[set name](&[set base]_memIO->shmemOutgoing_[set base]_[set name])
          hasOutgoing_[set base]_[set name] = false;
       \}
"
}


proc monitorlogevent { fout base name } {
global SAL_DIR SAL_WORK_DIR
   puts $fout "
       if (syncI_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isEventReader == false) \{
             mgr.salEvent("[set base]_[set name]");
          \}
          status = mgr.getEvent_[set name](&[set base]_memIO->shmemIncoming_[set base]_[set name]);
          if (status == SAL__OK) \{
             hasIncoming_[set base]_[set name] = true;
          \}
       \}
       if (syncO_[set base]_[set name]) \{
          actorIdx = SAL__[set base]_[set name]_ACTOR;
          if (sal\[actorIdx\].isEventWriter == false) \{
             mgr.salEvent("[set base]_[set name]");
          \}
       \}
       if ( hasOutgoing_[set base]_[set name] ) \{
          status = mgr.logEvent_[set name](&[set base]_memIO->shmemOutgoing_[set base]_[set name],1)
          hasOutgoing_[set base]_[set name] = false;
       \}
"
}

