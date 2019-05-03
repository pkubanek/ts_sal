#
#  yum install tk_devel influxdb
#
#  systemctl disable firewalld
#  disable selinux in /etc/selinux/config
#
#  set SAL_WORK_DIR $env(SAL_WORK_DIR)
#  creategenericefds camera
#
#  Remember to delete anonymous users
#  Give efduser all permissions
#  .my.cnf for auto pass
#
#  after schema change, run validate, sal html, and sal cpp steps
#
#  rules : field names exclusions : dec limit
#


proc writetoefd1 { topic } {
global SQLREC TYPEFORMAT
  set flds [split $SQLREC($topic) ,]
  set record "build\n	  .meas(\"$topic\")"
  set rformat ""
  set rvars ""
  set ldata "myData_[join [lrange [split $topic _] 1 end] _]"
  while { [llength $flds] != 0 } {
      set i [lindex $flds 0]
      set flds [lrange $flds 1 end]
      set type [lindex [split $i .] 0]
      set name [lindex [split $i .] 1]
      set isarray [lindex [split $i .] 2]
      if { $type == "char" } {
             set name "[set name].m_ptr"
             set isarray ""
      } 
###puts stdout "$i $type $name $isarray"
      if { $isarray == "" } {
              set value "[set ldata]\[iloop\].[set name]"
      } else {
             set value "[set ldata]\[iloop\].[set name]\[0\]"
             set j 1
             while { $j <= [expr $isarray -1] } {
                set value "[set ldata]\[iloop\].[set name]\[$j\]"
                set rvars "$rvars\n	  .field(\"[set name][set j]\",$value)"
                incr j 1
             }
             set value [string trim $value ","]
      }
      if { $isarray == "" } {
        set rvars "$rvars\n	  .field(\"[set name]\",$value)"
      }
###puts stdout $rvars
###puts stdout $rformat
  }
  set record "$record [set rvars]\n	  .timestamp((unsigned long long)(mgr.getCurrentTime()*1000000000));\n"
  return $record
}

proc writetoefd3 { topic } {
global SQLREC TYPEFORMAT
  set flds [split $SQLREC($topic) ,]
  set record "build\n	  .meas(\"$topic\")"
  set rformat ""
  set rvars ""
  set ldata "myData_[join [lrange [split $topic _] 1 end] _]"
  while { [llength $flds] != 0 } {
      set i [lindex $flds 0]
      set flds [lrange $flds 1 end]
      set type [lindex [split $i .] 0]
      set name [lindex [split $i .] 1]
      set isarray [lindex [split $i .] 2]
      if { $type == "char" } {
             set name "[set name].m_ptr"
             set isarray ""
      } 
###puts stdout "$i $type $name $isarray"
      if { $isarray == "" } {
              set value "[set ldata]\[iloop\].[set name]"
      } else {
             set value "[set ldata]\[iloop\].[set name]\[0\]"
             set j 1
             while { $j <= [expr $isarray -1] } {
                set value "[set ldata]\[iloop\].[set name]\[$j\]"
                set rvars "$rvars\n	  .field(\"[set name][set j]\",$value)"
                incr j 1
             }
             set value [string trim $value ","]
      }
      if { $isarray == "" } {
        set rvars "$rvars\n	  .field(\"[set name]\",$value)"
      }
###puts stdout $rvars
###puts stdout $rformat
  }
  set record "$record [set rvars]\n	  .timestamp((unsigned long long)(mgr.getCurrentTime()*1000000000));\n"
  return $record
}
proc writetoefd2 { topic } {
global SQLREC TYPEFORMAT
  set flds [split $SQLREC($topic) ,]
  set record "ret = build\n	  .meas(\"$topic\")"
  set rformat ""
  set rvars ""
  set ldata "myData_[join [lrange [split $topic _] 1 end] _]"
  while { [llength $flds] != 0 } {
      set i [lindex $flds 0]
      set flds [lrange $flds 1 end]
      set type [lindex [split $i .] 0]
      set name [lindex [split $i .] 1]
      set isarray [lindex [split $i .] 2]
      if { $type == "char" } {
             set name "[set name].m_ptr"
             set isarray ""
      } 
###puts stdout "$i $type $name $isarray"
      if { $isarray == "" } {
              set value "[set ldata]\[iloop\].[set name]"
      } else {
             set value "[set ldata]\[iloop\].[set name]\[0\]"
             set j 1
             while { $j <= [expr $isarray -1] } {
                set value "[set ldata]\[iloop\].[set name]\[$j\]"
                set rvars "$rvars\n	  .field(\"[set name][set j]\",$value)"
                incr j 1
             }
             set value [string trim $value ","]
      }
      if { $isarray == "" } {
        set rvars "$rvars\n	  .field(\"[set name]\",$value)"
      }
###puts stdout $rvars
###puts stdout $rformat
  }
  set record "$record [set rvars]\n	  .timestamp((unsigned long long)(mgr.getCurrentTime()*1000000000))\n	  .post_http(si,&resp);"
  return $record
}



proc genericinfluxfragment { fout base ttype ctype } {
global ACTORTYPE SAL_WORK_DIR BLACKLIST
   if { $ctype == "connect" } {
       puts $fout "

  char *efdb_host = getenv(\"LSST_EFD_HOST\");
  if (efdb_host == NULL) \{
      fprintf(stderr,\"MYSQL : LSST_EFD_HOST not defined\\n\");
      exit(1);
  \}

  influxdb_cpp::server_info si(efdb_host,8086,\"EFD\", \"efduser\" , \"lssttest\");
 
"
       return 
   }
   set idlfile $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set base].idl
   set ptypes [lsort [split [exec grep pragma $idlfile] \n]]
   foreach j $ptypes {
     set topic [lindex $j 2]
     set revcode [getRevCode [set base]_[set topic] short]
     set type [lindex [split $topic _] 0]
     set doit 0
     set trail  [string range $topic [expr [string bytelength $topic]-9] end]
     set trail2 [string range $topic [expr [string bytelength $topic]-15] end]
     if { $ttype == "command" && $type == "command" || $topic == "ackcmd"} {set doit 1}
     if { $ttype == "logevent" && $type == "logevent" && $topic != "ackcmd"} {set doit 1}
     if { $ttype == "telemetry" && $type != "command" && $type != "logevent" && $topic != "ackcmd" } {set doit 1}
     if { $trail == "Heartbeat" || $trail2 == "InternalCommand" } {set doit 0}
     if { $ttype != "command" && $topic == "ackcmd" } {set doit 0}
     if { [info exists BLACKLIST([set topic])] } {set doit 0}
     if { $doit } {
#      if { $ctype == "init" } {
#       puts $fout "  [set base]::[set topic][set revcode]Seq myData_[set topic];
#  SampleInfoSeq_var [set topic][set revcode]_info = new SampleInfoSeq;"
#      }
      if { $ctype == "subscriber" } {
       puts $fout "  mgr.salTelemetrySub(\"[set base]_[set topic]\");
  actorIdx = SAL__[set base]_[set topic]_ACTOR;
  DataReader_var [set topic][set revcode]_dreader = mgr.getReader(actorIdx);
  [set base]::[set topic][set revcode]DataReader_var [set topic]_SALReader = [set base]::[set topic][set revcode]DataReader::_narrow([set topic][set revcode]_dreader.in());
  mgr.checkHandle([set topic]_SALReader.in(), \"[set base]::[set topic][set revcode]DataReader::_narrow\");
"
      }
      if { $ctype == "getsamples" } {
        if { $topic != "command" && $topic != "logevent" && $topic != "ackcmd" } {
          puts $fout "  
       [set base]::[set topic][set revcode]Seq myData_[set topic];
       SampleInfoSeq_var [set topic]_info = new SampleInfoSeq;
       status = [set topic]_SALReader->take(myData_[set topic], [set topic]_info, 100, ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
       mgr.checkStatus(status,\"[set base]::[set topic][set revcode]DataReader::take\");
       numsamp = myData_[set topic].length();
       if (status == SAL__OK && numsamp > 0) \{
	influxdb_cpp::builder build;
        bool first_value = true;
        int ret;
        for (iloop=0;iloop<numsamp;iloop++) \{
         if (myData_[set topic]\[iloop\].private_origin != 0) \{
          myData_[set topic]\[iloop\].private_rcvStamp = mgr.getCurrentTime();
          if(iloop<numsamp-1 && first_value){
                first_value = false;
	  	[writetoefd1 [set base]_[set topic]]
	  }else if(iloop<numsamp-1 && !first_value){
                [writetoefd3 [set base]_[set topic]]
          }else{
	  	[writetoefd2 [set base]_[set topic]]
	  }"
          if { $base != "efd" } {
             checkinfluxLFO $fout $topic
          }
          puts $fout "
          //cout << ret << endl << resp << endl;
          //cout << \"logged [set topic]\" << endl;
         \}
        \}
       \}
          status = [set topic]_SALReader->return_loan(myData_[set topic], [set topic]_info);
"
        }
      }
    }
   }
}


proc checkinfluxLFO { fout topic } {
  set alias [join [lrange [split $topic _] 1 end] _]
  if { $alias == "LargeFileObjectAvailable" } {
     set alias "'[join [lrange [split $topic _] 1 end] _]'"
     puts $fout "
       if (status == SAL__OK && numsamp > 0) \{
           printf(\"EFD TBD : Large File Object Announcement Event $topic received\\n\");
           sprintf(thequery,\"process_LFO_logevent  %d '%s' '%s' '%s' '%s' %f '%s'\"  ,  myData_[set topic]\[iloop\].Byte_Size , myData_[set topic]\[iloop\].Checksum.m_ptr , myData_[set topic]\[iloop\].Generator.m_ptr , myData_[set topic]\[iloop\].Mime_Type.m_ptr , myData_[set topic]\[iloop\].URL.m_ptr , myData_[set topic]\[iloop\].Version, myData_[set topic]\[iloop\].ID.m_ptr);
          mstatus = system(thequery);
          if (mstatus < 0) \{
             fprintf(stderr,\"LFO Processor ERROR : %d\\n\",mstatus);
          \}
      \}
"
  }
}


proc geninfluxwritermake { base } {
global SAL_DIR SAL_WORK_DIR env
  set frep [open /tmp/sreplace5.sal w]
  puts $frep "#!/bin/sh"
  exec touch $SAL_WORK_DIR/[set base]/cpp/src/.depend.Makefile.sacpp_SALData_influxwriter
  exec cp  $SAL_DIR/code/templates/Makefile.sacpp_SAL_influxwriter.template $SAL_WORK_DIR/[set base]/cpp/src/Makefile.sacpp_[set base]_influxwriter
  puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' $SAL_WORK_DIR/[set base]/cpp/src/Makefile.sacpp_[set base]_influxwriter"
  puts $frep "perl -pi -w -e 's/SALSubsys/[set base]/g;' $SAL_WORK_DIR/[set base]/cpp/src/Makefile.sacpp_[set base]_influxwriter"
  puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' $SAL_WORK_DIR/[set base]/cpp/src/Makefile.sacpp_[set base]_influxwriter"
  close $frep
  exec chmod 755 /tmp/sreplace5.sal
  catch { set result [exec /tmp/sreplace5.sal] } bad
  if { $bad != "" } {puts stdout $bad}
}


proc geninfluxtelemetryreader { base } {
global SAL_WORK_DIR SYSDIC
   set fout [open $SAL_WORK_DIR/[set base]/cpp/src/sacpp_[set base]_telemetry_influxwriter.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the [set base] generic Telemetry reader.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <influxdb.hpp>
#include <syslog.h>
#include \"SAL_[set base].h\"
#include \"SAL_actors.h\"
#include \"ccpp_sal_[set base].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set base];

/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int test_[set base]_telemetry_influxwriter();
\}

int test_[set base]_telemetry_influxwriter()
\{   

  char *thequery = (char *) malloc(sizeof(char)*100000);
  SAL_[set base] mgr = SAL_[set base]();
"
  genericinfluxfragment $fout $base telemetry init
  puts $fout "
  os_time delay_10us = \{ 0, 10000 \};
  int numsamp = 0;
  int actorIdx = 0;
  int iloop = 0;
  int mstatus = 0;
  string resp;
  int status = 0;"
  genericinfluxfragment $fout $base telemetry subscriber
  genericinfluxfragment $fout $base telemetry connect
  puts $fout "
       while (1) \{
"
  genericinfluxfragment $fout $base telemetry getsamples
   puts $fout "
          os_nanoSleep(delay_10us);
      \}

  /* Remove the DataWriters etc */
       mgr.salShutdown();

      return 0;
\}

int main (int argc, char **argv[])
\{
  return test_[set base]_telemetry_influxwriter();
\}
"
   close $fout
}



proc geninfluxeventreader { base } {
global SAL_WORK_DIR SYSDIC
   set fout [open $SAL_WORK_DIR/[set base]/cpp/src/sacpp_[set base]_event_influxwriter.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the [set base] generic event influxwriter.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <influxdb.hpp>
#include <syslog.h>
#include \"SAL_[set base].h\"
#include \"SAL_actors.h\"
#include \"ccpp_sal_[set base].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set base];

/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int test_[set base]_event_influxwriter();
\}

int test_[set base]_event_influxwriter()
\{

  char *thequery = (char *) malloc(sizeof(char)*100000);
  SAL_[set base] mgr = SAL_[set base]();
"
  genericinfluxfragment $fout $base logevent init

  puts $fout "
  os_time delay_10us = \{ 0, 10000 \};
  int numsamp = 0;
  int actorIdx = 0;
  string resp;
  int iloop = 0;
  int mstatus = 0;
  int status=0;"
  genericinfluxfragment $fout $base logevent subscriber
  genericinfluxfragment $fout $base logevent connect
  puts $fout "
  while (1) \{
"
  genericinfluxfragment $fout $base logevent getsamples
   puts $fout "
     os_nanoSleep(delay_10us);
  \}

  /* Remove the DataWriters etc */
   mgr.salShutdown();

  return 0;
\}

int main (int argc, char **argv[])
\{
  return test_[set base]_event_influxwriter();
\}
"
   close $fout
}


proc geninfluxcommandreader { base } {
global SAL_WORK_DIR SYSDIC
   set fout [open $SAL_WORK_DIR/[set base]/cpp/src/sacpp_[set base]_command_influxwriter.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the [set base] generic command influxwriter.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <influxdb.hpp>
#include <syslog.h>
#include \"SAL_[set base].h\"
#include \"SAL_actors.h\"
#include \"ccpp_sal_[set base].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set base];

/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int test_[set base]_command_influxwriter();
\}

int test_[set base]_command_influxwriter()
\{ 

  char *thequery = (char *)malloc(sizeof(char)*100000);
  SAL_[set base] mgr = SAL_[set base]();
"
  genericinfluxfragment $fout $base command init
  puts $fout "
  os_time delay_10us = \{ 0, 10000 \};
  int numsamp = 0;
  int actorIdx = 0;
  string resp;
  int iloop = 0;
  int mstatus = 0;
  int status=0;"
  genericinfluxfragment $fout $base command subscriber
  genericinfluxfragment $fout $base command connect
  puts $fout "
  while (1) \{
"
  genericinfluxfragment $fout $base command getsamples
   puts $fout "
     os_nanoSleep(delay_10us);
  \}

  /* Remove the DataWriters etc */
  mgr.salShutdown();

  return 0;
\}

int main (int argc, char **argv[])
\{
  return test_[set base]_command_influxwriter();
\}
"
   close $fout
}


proc updateinfluxtables { } {
global SAL_WORK_DIR SYSDIC BLACKLIST
   cd $SAL_WORK_DIR
   foreach i [array names BLACKLIST] {
     catch {
      set blk [glob sql/*$i*]
      foreach blkn $blk {
        exec rm $blkn
      }
     }
   }
   foreach subsys $SYSDIC(systems) {
      if { [file exists $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl] } {
        puts stdout "Updating schema for $subsys"
        makesummarytables $subsys
        set all [glob sql/[set subsys]_*.sqldef]
        set cmd "exec cat $all > sql/create-tables-[set subsys]"
        set docat [eval $cmd]
##        exec mysql EFD < sql/create-tables-[set base]
      }
   }
}


proc updateinfluxschema { } {
global SYSDIC SAL_WORK_DIR
   set bad 0
   foreach subsys $SYSDIC(systems) {
      if { [file exists $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl] } {
        puts stdout "Updating schema for $subsys"
        set bad [catch {geninfluxwriters $subsys} res]
        if { $bad } {puts stdout $res}
        exec ls -l $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_[set subsys]_event_influxwriter
      } else {
        puts stdout "WARNING : No IDL for $subsys available"
      }
   }
}

proc updateSALinfluxqueries { } {
global SYSDIC SAL_WORK_DIR
   set bad 0
   foreach subsys $SYSDIC(systems) {
      if { [file exists $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl] } {
        puts stdout "Updating SAL queries for $subsys"
        set bad [catch {genSALinfluxqueries $subsys} res]
        if { $bad } {puts stdout $res}
      } else {
        puts stdout "WARNING : No IDL for $subsys available"
      }
   }
}

proc geninfluxwriters { base } {
global SQLREC SAL_WORK_DIR
   set SQLREC([set base]_ackcmd)  "char.private_revCode,double.private_sndStamp,double.private_rcvStamp,int.private_seqNum,int.private_origin,int.private_host,int.ack,int.error,char.result"
   set SQLREC([set base]_commandLog)  "char.private_revCode,double.private_sndStamp,int.private_seqNum,char.name,int.ack,int.error"
   set SQLREC([set base]_logeventLFO)  "char.private_revCode,double.private_sndStamp,int.private_seqNum,char.alias,char.URL,char.Generator,char.Version,char.Checksum,char.Mime_Type,char.ID,int.Byte_size"
##   makesummarytables  $base
   geninfluxtelemetryreader $base
   geninfluxcommandreader   $base
   geninfluxeventreader     $base
   geninfluxwritermake   $base
   cd $SAL_WORK_DIR/[set base]/cpp/src
   exec make -f Makefile.sacpp_[set base]_influxwriter
   cd $SAL_WORK_DIR
}

proc startinfluxwriters { subsys } { 
global SAL_WORK_DIR
   foreach s $subsys {
      if { [file exists $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_telemetry_influxwriter] == 0 } {
         puts sdout "ERROR : No telemetry writer available for $s"
         exit
      }
      if { [file exists $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_command_influxwriter] == 0 } {
         puts sdout "ERROR : No command writer available for $s"
         exit
      }
      if { [file exists $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_telemetry_influxwriter] == 0 } {
         puts sdout "ERROR : No event writer available for $s"
         exit
      }
      set tid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_telemetry_influxwriter >& efd_[set s]_telemetry_[clock seconds].log &]
      set cid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_command_influxwriter >& efd_[set s]_command_[clock seconds].log &]
      set eid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_event_influxwriter >& efd_[set s]_event_[clock seconds].log &]
   }
   while { 1 } {
     foreach s $subsys {
       set bad [catch {exec ps -F --pid $tid($s)} res]
       if { $bad } {
          set tid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_telemetry_influxwriter >& efd_[set s]_telemetry_[clock seconds].log &]
       }
       set bad [catch {exec ps -F --pid $cid($s)} res]
       if { $bad } {
          set cid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_command_influxwriter >& efd_[set s]_command_[clock seconds].log &]
       }
       set bad [catch {exec ps -F --pid $eid($s)} res]
       if { $bad } {
          set eid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_event_influxwriter >& efd_[set s]_event_[clock seconds].log &]
       }
     }
   }
}


set SAL_DIR $env(SAL_DIR)
set SAL_WORK_DIR $env(SAL_WORK_DIR)

set recdef [glob $SAL_WORK_DIR/sql/*.sqlwrt]
foreach i $recdef { 
   source $i
}

set BLACKLIST(Cluster_Encoder) 1
set BLACKLIST(sequencePropConfig) 1
set BLACKLIST(blockPusher) 1
set BLACKLIST(Surface) 1


source $SAL_DIR/add_system_dictionary.tcl
source $SAL_DIR/add_system_dictionary.tcl
foreach subsys $SYSDIC(systems) {
   if { [file exists $SAL_WORK_DIR/idl-templates/validated/[set subsys]_revCodes.tcl] } {
      source $SAL_WORK_DIR/idl-templates/validated/[set subsys]_revCodes.tcl
   } else {
      puts stdout "WARNING : No revCodes for $subsys"
   }
}
source $SAL_DIR/managetypes.tcl
source $SAL_DIR/activaterevcodes.tcl



