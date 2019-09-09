#
# export LSST_KAFKA_BROKERS=efd-kafka0.lsst.codes:9094,efd-kafka1.lsst.codes:9094,efd-kafka2.lsst.codes:9094​
#


proc writetokafka { base ttype topic } {
global SQLREC TYPEFORMAT
  set flds [split $SQLREC($topic) ,]
  set record "sprintf(thequery,\"[set base]_[set ttype] [set topic]:("
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
              set vform $TYPEFORMAT($type)
              if { $type == "char" } {
                 set vform "'$TYPEFORMAT($type)'"
              }
      } else {
             set value "[set ldata]\[iloop\].[set name]\[0\]"
             set vform "$TYPEFORMAT($type)"
             set j 1
             while { $j <= [expr $isarray -1] } {
                set value "$value,[set ldata]\[iloop\].[set name]\[$j\]"
                set vform "$vform, $TYPEFORMAT($type)"
                incr j 1
             }
             set value [string trim $value ","]
      }
      set rvars "$rvars , $value"
      set rformat "$rformat , $vform"
###puts stdout $rvars
###puts stdout $rformat
  }
  set rformat [string trim $rformat " ,"]
  set record "$record [set rformat])\" $rvars );"
  return $record
}


proc generickafkafragment { fout base ttype ctype } {
global ACTORTYPE SAL_WORK_DIR BLACKLIST
   if { $ctype == "connect" } {
       puts $fout "
  char *brokers;
  rd_kafka_topic_t *rkt;
  char mode = 'C';
  const char *topic = \"[set base]_[set ttype]\"; /* Substitute from template */
  const char *estr; /* Kafka error string for legacy methods */
  int partition = RD_KAFKA_PARTITION_UA;
  int opt;
  rd_kafka_conf_t *conf;
  rd_kafka_topic_conf_t *topic_conf;
  char errstr\[512\];
  int64_t start_offset = 0;
  int do_conf_dump = 0;
  char tmp\[16\];
  int64_t seek_offset = 0;
  int64_t tmp_offset = 0;
  int get_wmarks = 0;
  rd_kafka_headers_t *hdrs = NULL;
  rd_kafka_resp_err_t err;

  /* Kafka configuration */
  conf = rd_kafka_conf_new();

  /* Set up a message delivery report callback.
   * It will be called once for each message, either on successful
   * delivery to broker, or upon failure to deliver to broker. */
  rd_kafka_conf_set_dr_msg_cb(conf, msg_delivered);

  /* Create Kafka handle */
  if (!(rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf,
                          errstr, sizeof(errstr)))) \{
      fprintf(stderr,
              \"%% Failed to create new producer: %s\\n\",
              errstr);
      exit(1);
  \}

  /* New environment variable for Kafka endpoints */
  /* Comma-separated list of host:port tuples */
  /* e.g. \"172.17.0.5:9092,172.17.0.6:9092\" */
  brokers = getenv(\"LSST_KAFKA_BROKERS\");
  if (brokers == NULL) \{
      fprintf(stderr,\"KAFKA : LSST_KAFKA_BROKERS not defined\\n\");
      exit(1);
  \}


  /* Add brokers */
  if (rd_kafka_brokers_add(rk, brokers) == 0) \{
      fprintf(stderr, \"%% No valid brokers specified\\n\");
      exit(1);
  \}

  /* Quick termination */
  snprintf(tmp, sizeof(tmp), \"%i\", SIGIO);
  rd_kafka_conf_set(conf, \"internal.termination.signal\", tmp, NULL, 0);

  /* Topic configuration */
  topic_conf = rd_kafka_topic_conf_new();
  if (topic_conf == NULL) \{
    err = rd_kafka_last_error();
    estr = rd_kafka_err2str(err);
    fprintf(stderr,\"%% Failed to create Kafka topic config: %s.\\n\", estr);
    exit(1);
  \}

  /* Create topic */
  rkt = rd_kafka_topic_new(rk, topic, topic_conf);
  if (rkt == NULL) \{
    err = rd_kafka_last_error();
    estr = rd_kafka_err2str(err);
    fprintf(stderr,\"%% Failed to create Kafka topic: %s.\\n\", estr);
    exit(1);
  \}
  topic_conf = NULL; /* Now owned by topic */

  cout << \"Kafka client for $base ready\" << endl;

  int sendcnt=0;
  size_t len;
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
#       puts $fout "  [set base]::[set topic][set revcode]Seq myData_[set topic][set revcode];
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
        if { $topic != "command" && $topic != "logevent" } {
        puts $fout "  
       [set base]::[set topic][set revcode]Seq myData_[set topic];
       SampleInfoSeq_var [set topic]_info = new SampleInfoSeq;
       status = [set topic]_SALReader->take(myData_[set topic], [set topic]_info, 100, ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
       mgr.checkStatus(status,\"[set base]::[set topic][set revcode]DataReader::take\");
       numsamp = myData_[set topic].length();
       if (status == SAL__OK && numsamp > 0) \{
        for (iloop=0;iloop<numsamp;iloop++) \{
         if (myData_[set topic]\[iloop\].private_origin != 0) \{
          myData_[set topic]\[iloop\].private_rcvStamp = mgr.getCurrentTime();"
       if { $topic != "ackcmd" } {
         puts $fout "
          [writetokafka $base $ttype [set base]_[set topic]]
//          cout << thequery << endl;

          /* Kafka boilerplate to submit query */
          err = RD_KAFKA_RESP_ERR_NO_ERROR;
	  len = strlen(thequery);
          if (rd_kafka_produce(rkt, partition,
                               RD_KAFKA_MSG_F_COPY,
                               thequery,
                               len,
                               /* No key, no opaque */
                               NULL, 0, NULL) == -1) \{
              err = rd_kafka_last_error();
          \}
          if (err) \{
              fprintf(stderr,
                      \"%% Failed to produce to topic %s \"
                      \"partition %i: %s\\n\",
                      rd_kafka_topic_name(rkt), partition,
                      rd_kafka_err2str(err));

              /* Poll to handle delivery reports */
              rd_kafka_poll(rk, 0);
              continue;
          \}
          if (!quiet) fprintf(stderr,\"-\");
//              fprintf(stderr, \"%% Sent %zd bytes to topic \"
//                      \"%s partition %i\\n\",
//                      len, rd_kafka_topic_name(rkt), partition);
          sendcnt++;
          /* Poll to handle delivery reports */
          rd_kafka_poll(rk, 0);
"
         }
###         puts $fout "       \}"
           if { $base != "efd" } {
             checkkafkaLFO $fout $topic
           }
         }
         if { $topic != "command" && $topic != "logevent" } {
           puts $fout "         \}
        \}
       \}
       status = [set topic]_SALReader->return_loan(myData_[set topic], [set topic]_info);
"
         }
      }
    }
   }
}


proc genquerykafka { fout base topic key } {
   if { $key == "last" } {
      puts $fout "
#include <sys/time.h>
#include <time.h>
#include \"SAL_[set base].h\"
using namespace [set base];

int SAL_[set base]::getLastSample_[set topic] ([set base]_[set topic]C *mydata) \{

      int num_fields=0;
      int mstatus=0;
      char *thequery = (char *) malloc(sizeof(char)*4000);
      MYSQL_RES *result;
      MYSQL_ROW *row;

      if ( getSample_[set topic] ([set base]_[set topic]C *mydata) == SAL__NO_UPDATES) \{
        sprintf(thequery,\"SELECT * FROM [set base]_[set topic] LIMIT 1;\");
        mstatus = mysql_query(efdConnection,thequery);
        if (mstatus != 0) \{
             return SAL__NO_UPDATES;
        \}
        result = mysql_store_result(efdConnection);
        int num_fields = mysql_num_fields(result);
        row = mysql_fetch_row(result);
        [readfromkafka [set base]_[set topic] 1]
"
      puts $fout "
        mysql_free_result(result);
      \}
      return SAL__OK;
\}
"
   }
}



proc checkkafkaLFO { fout topic } {
  set alias [join [lrange [split $topic _] 1 end] _]
  if { $alias == "largeFileObjectAvailable" } {
     set alias "'[join [lrange [split $topic _] 1 end] _]'"
     puts $fout "
       if (status == SAL__OK && numsamp > 0) \{
           printf(\"EFD TBD : Large File Object Announcement Event $topic received\\n\");
           sprintf(thequery,\"process_LFO_logevent  %d '%s' '%s' '%s' '%s' %f '%s'\"  ,  myData_[set topic]\[iloop\].byteSize , myData_[set topic]\[iloop\].checkSum.m_ptr , myData_[set topic]\[iloop\].generator.m_ptr , myData_[set topic]\[iloop\].mimeType.m_ptr , myData_[set topic]\[iloop\].url.m_ptr , myData_[set topic]\[iloop\].version, myData_[set topic]\[iloop\].id.m_ptr);
          mstatus = system(thequery);
          if (mstatus < 0) \{
             fprintf(stderr,\"LFO Processor ERROR : %d\\n\",mstatus);
          \}
      \}
"
  }
}


proc genkafkawritermake { base } {
global SAL_DIR SAL_WORK_DIR env
  set frep [open /tmp/sreplace5.sal w]
  puts $frep "#!/bin/sh"
  exec touch $SAL_WORK_DIR/[set base]/cpp/src/.depend.Makefile.sacpp_SALData_kafkawriter
  exec cp  $SAL_DIR/code/templates/Makefile.sacpp_SAL_kafkawriter.template $SAL_WORK_DIR/[set base]/cpp/src/Makefile.sacpp_[set base]_kafkawriter
  puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' $SAL_WORK_DIR/[set base]/cpp/src/Makefile.sacpp_[set base]_kafkawriter"
  puts $frep "perl -pi -w -e 's/SALSubsys/[set base]/g;' $SAL_WORK_DIR/[set base]/cpp/src/Makefile.sacpp_[set base]_kafkawriter"
  puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' $SAL_WORK_DIR/[set base]/cpp/src/Makefile.sacpp_[set base]_kafkawriter"
  close $frep
  exec chmod 755 /tmp/sreplace5.sal
  catch { set result [exec /tmp/sreplace5.sal] } bad
  if { $bad != "" } {puts stdout $bad}
}


proc genktelemetryreader { base } {
global SAL_WORK_DIR SYSDIC
   set fout [open $SAL_WORK_DIR/[set base]/cpp/src/sacpp_[set base]_telemetry_kafkawriter.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the [set base] generic Telemetry reader.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <librdkafka/rdkafka.h>
#include <syslog.h>
#include \"SAL_[set base].h\"
#include \"SAL_actors.h\"
#include \"ccpp_sal_[set base].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set base];
/* Three static variables for Kafka */
static rd_kafka_t *rk;
static int quiet=0;
static int run=1;


/**
 * Message delivery report callback using the richer rd_kafka_message_t object.
 */
static void msg_delivered (rd_kafka_t *rk,
                           const rd_kafka_message_t *rkmessage, void *opaque) \{
        if (rkmessage->err)
          fprintf(stderr,\"#\");
//        fprintf(stderr, \"%% Message delivery failed: %s\\n\",
//                        rd_kafka_err2str(rkmessage->err));
    else if (!quiet)
          fprintf(stderr,\"+\");
//        fprintf(stderr,
//                        \"%% Message delivered (%zd bytes, offset %\" PRId64\", \"
//                        \"partition %\" PRId32\"): %.*s\\n\",
//                        rkmessage->len, rkmessage->offset,
//            rkmessage->partition,
//            (int)rkmessage->len, (const char *)rkmessage->payload);
\}

/**
 * Kafka logger callback (optional)
 */

/* Not currently using, but keep around for now.

static void logger (const rd_kafka_t *rk, int level,
            const char *fac, const char *buf) \{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(stderr, \"%u.%03u RDKAFKA-%i-%s: %s: %s\n\",
        (int)tv.tv_sec, (int)(tv.tv_usec / 1000),
        level, fac, rk ? rd_kafka_name(rk) : NULL, buf);
\}

*/


/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int test_[set base]_telemetry_kafkawriter();
\}

int test_[set base]_telemetry_kafkawriter()
\{   

  char *thequery = (char *) malloc(sizeof(char)*100000);
  SAL_[set base] mgr = SAL_[set base]();
"
  generickafkafragment $fout $base telemetry init
  puts $fout "
  os_time delay_5ms = \{ 0, 5000000 \};
  int numsamp = 0;
  int actorIdx = 0;
  int isyslog = 1;
  int iloop = 0;
  int mstatus = 0;
  int status = 0;"
  generickafkafragment $fout $base telemetry subscriber
  generickafkafragment $fout $base telemetry connect
  puts $fout "
       while (1) \{
"
  generickafkafragment $fout $base telemetry getsamples
   puts $fout "
          os_nanoSleep(delay_5ms);
      \}

       return 0;
\}

int main (int argc, char **argv[])
\{
  return test_[set base]_telemetry_kafkawriter();
\}
"
   close $fout
}



proc genkeventreader { base } {
global SAL_WORK_DIR SYSDIC
   set fout [open $SAL_WORK_DIR/[set base]/cpp/src/sacpp_[set base]_event_kafkawriter.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the [set base] generic event kafkawriter.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <librdkafka/rdkafka.h>
#include <syslog.h>
#include \"SAL_[set base].h\"
#include \"SAL_actors.h\"
#include \"ccpp_sal_[set base].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set base];
/* Three static variables for Kafka */
static rd_kafka_t *rk;
static int quiet=0;
static int run=1;



/**
 * Message delivery report callback using the richer rd_kafka_message_t object.
 */
static void msg_delivered (rd_kafka_t *rk,
                           const rd_kafka_message_t *rkmessage, void *opaque) \{
        if (rkmessage->err)
          fprintf(stderr,\"#\");
//        fprintf(stderr, \"%% Message delivery failed: %s\\n\",
//                        rd_kafka_err2str(rkmessage->err));
    else if (!quiet)
          fprintf(stderr,\"+\");
//        fprintf(stderr,
//                        \"%% Message delivered (%zd bytes, offset %\" PRId64\", \"
//                        \"partition %\" PRId32\"): %.*s\\n\",
//                        rkmessage->len, rkmessage->offset,
//            rkmessage->partition,
//            (int)rkmessage->len, (const char *)rkmessage->payload);
\}

/**
 * Kafka logger callback (optional)
 */

/* Not currently using, but keep around for now.

static void logger (const rd_kafka_t *rk, int level,
            const char *fac, const char *buf) \{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(stderr, \"%u.%03u RDKAFKA-%i-%s: %s: %s\n\",
        (int)tv.tv_sec, (int)(tv.tv_usec / 1000),
        level, fac, rk ? rd_kafka_name(rk) : NULL, buf);
\}
*/

/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int test_[set base]_event_kafkawriter();
\}

int test_[set base]_event_kafkawriter()
\{

  char *thequery = (char *) malloc(sizeof(char)*100000);
  SAL_[set base] mgr = SAL_[set base]();
"
  generickafkafragment $fout $base logevent init

  puts $fout "
  os_time delay_5ms = \{ 0, 5000000 \};
  int numsamp = 0;
  int actorIdx = 0;
  int isyslog = 1;
  int iloop = 0;
  int mstatus = 0;
  int status=0;"
  generickafkafragment $fout $base logevent subscriber
  generickafkafragment $fout $base logevent connect
  puts $fout "
  while (1) \{
"
  generickafkafragment $fout $base logevent getsamples
   puts $fout "
     os_nanoSleep(delay_5ms);
  \}
  return 0;
\}

int main (int argc, char **argv[])
\{
  return test_[set base]_event_kafkawriter();
\}
"
   close $fout
}


proc genkcommandreader { base } {
global SAL_WORK_DIR SYSDIC
   set fout [open $SAL_WORK_DIR/[set base]/cpp/src/sacpp_[set base]_command_kafkawriter.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the [set base] generic command kafkawriter.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <librdkafka/rdkafka.h>
#include <syslog.h>
#include \"SAL_[set base].h\"
#include \"SAL_actors.h\"
#include \"ccpp_sal_[set base].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set base];
/* Three static variables for Kafka */
static rd_kafka_t *rk;
static int quiet=0;
static int run=1;


/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int test_[set base]_command_kafkawriter();
\}


/**
 * Message delivery report callback using the richer rd_kafka_message_t object.
 */
static void msg_delivered (rd_kafka_t *rk,
                           const rd_kafka_message_t *rkmessage, void *opaque) \{
        if (rkmessage->err)
          fprintf(stderr,\"#\");
//        fprintf(stderr, \"%% Message delivery failed: %s\\n\",
//                        rd_kafka_err2str(rkmessage->err));
    else if (!quiet)
          fprintf(stderr,\"+\");
//        fprintf(stderr,
//                        \"%% Message delivered (%zd bytes, offset %\" PRId64\", \"
//                        \"partition %\" PRId32\"): %.*s\\n\",
//                        rkmessage->len, rkmessage->offset,
//            rkmessage->partition,
//            (int)rkmessage->len, (const char *)rkmessage->payload);
\}

/**
 * Kafka logger callback (optional)
 */

/* Not currently using, but keep around for now.

static void logger (const rd_kafka_t *rk, int level,
            const char *fac, const char *buf) \{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(stderr, \"%u.%03u RDKAFKA-%i-%s: %s: %s\\n\",
        (int)tv.tv_sec, (int)(tv.tv_usec / 1000),
        level, fac, rk ? rd_kafka_name(rk) : NULL, buf);
\}

*/


int test_[set base]_command_kafkawriter()
\{ 

  char *thequery = (char *)malloc(sizeof(char)*100000);
  SAL_[set base] mgr = SAL_[set base]();
"
  generickafkafragment $fout $base command init
  puts $fout "
  os_time delay_5ms = \{ 0, 5000000 \};
  int numsamp = 0;
  int actorIdx = 0;
  int isyslog = 1;
  int iloop = 0;
  int mstatus = 0;
  int status=0;"
  generickafkafragment $fout $base command subscriber
  generickafkafragment $fout $base command connect
  puts $fout "
  while (1) \{
"
  generickafkafragment $fout $base command getsamples
   puts $fout "
     os_nanoSleep(delay_5ms);
  \}

  return 0;
\}

int main (int argc, char **argv[])
\{
  return test_[set base]_command_kafkawriter();
\}
"
   close $fout
}


proc updatekafkaschema { } {
global SYSDIC SAL_WORK_DIR
   set bad 0
   foreach subsys $SYSDIC(systems) {
      if { [file exists $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl] } {
        puts stdout "Updating schema for $subsys"
        set bad [catch {genkafkawriters $subsys} res]
        if { $bad } {puts stdout $res}
      } else {
        puts stdout "WARNING : No IDL for $subsys available"
      }
   }
}



proc genkafkawriters { base } {
global SQLREC SAL_WORK_DIR
   set SQLREC([set base]_ackcmd)  "char.private_revCode,double.private_sndStamp,double.private_rcvStamp,int.private_seqNum,int.private_origin,int.private_host,int.ack,int.error,char.result"
   set SQLREC([set base]_commandLog)  "char.private_revCode,double.private_sndStamp,int.private_seqNum,char.name,int.ack,int.error"
####   set SQLREC([set base]_logevent_largeFileObjectAvailable)  "char.private_revCode,double.private_sndStamp,int.private_seqNum,char.url,char.generator,float.version,char.checkSum,char.mimeType,char.id,int.byteSize"
#   makesummarytables  $base
   genktelemetryreader $base
   genkcommandreader   $base
   genkeventreader     $base
   genkafkawritermake   $base
   cd $SAL_WORK_DIR/[set base]/cpp/src
   exec make -f Makefile.sacpp_[set base]_kafkawriter
}

proc startkafkawriters { subsys } { 
global SAL_WORK_DIR
   foreach s $subsys {
      if { [file exists $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_telemetry_kafkawriter] == 0 } {
         puts sdout "ERROR : No telemetry writer available for $s"
         exit
      }
      if { [file exists $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_command_kafkawriter] == 0 } {
         puts sdout "ERROR : No command writer available for $s"
         exit
      }
      if { [file exists $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_telemetry_kafkawriter] == 0 } {
         puts sdout "ERROR : No event writer available for $s"
         exit
      }
      set tid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_telemetry_kafkawriter >& efd_[set s]_telemetry_[clock seconds].log &]
      set cid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_command_kafkawriter >& efd_[set s]_command_[clock seconds].log &]
      set eid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_event_kafkawriter >& efd_[set s]_event_[clock seconds].log &]
   }
   while { 1 } {
     foreach s $subsys {
       set bad [catch {exec ps -F --pid $tid($s)} res]
       if { $bad } {
          set tid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_telemetry_kafkawriter >& efd_[set s]_telemetry_[clock seconds].log &]
       }
       set bad [catch {exec ps -F --pid $cid($s)} res]
       if { $bad } {
          set cid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_command_kafkawriter >& efd_[set s]_command_[clock seconds].log &]
       }
       set bad [catch {exec ps -F --pid $eid($s)} res]
       if { $bad } {
          set eid($s) [exec $SAL_WORK_DIR/[set s]/cpp/src/sacpp_[set s]_event_kafkawriter >& efd_[set s]_event_[clock seconds].log &]
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


