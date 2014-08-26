#!/usr/bin/tclsh
set subsys $argv
puts stdout "Generating code for subsystem $argv"

proc doddsgen { topiclist } {
   parsepub $topiclist
   parsesub $topiclist
   generatetester $topiclist
   parsemakefile $topiclist
}

proc calcshmid { subsys } {
  set fout [open /tmp/subsys.tmp w]
  puts $fout "$subsys"
  close $fout
  set id [string range [exec md5sum /tmp/subsys.tmp] 0 3]
  return $id
}


proc addshmempub { topiclist fid } {
global VPROPS
  foreach subsys $topiclist {
    puts $fid "
   int [set subsys]_shmsize;
   int lshmid_[set subsys];
   int [set subsys]_shmid = 0x[calcshmid $subsys];
   [set subsys]_cache *[set subsys]_ref;"
  }
  foreach subsys $topiclist {
    puts $fid "
   [set subsys]_shmsize = sizeof(struct [set subsys]_cache);
   lshmid_[set subsys] = shmget([set subsys]_shmid, [set subsys]_shmsize , IPC_CREAT|0666);
   [set subsys]_ref  = ([set subsys]_cache *) shmat(lshmid_[set subsys], NULL, 0);"
  }
  puts $fid "
	while (1) \{
		svcSAL_sleep(1);"
  foreach subsys $topiclist {
    puts $fid "
		if ([set subsys]_ref->syncO == 1) \{
			count++;"
     set fin [open ../shmem-[set subsys]/[set subsys]_putstub.txt r]
     while { [gets $fin rec] > -1 } {
       puts $fid $rec
     }
     close $fin
     puts $fid "		\}"
  }
  puts $fid "	\}"
}


proc shcoder { topiclist } {
global SHC TOPICPROPS
 foreach subsys $topiclist {
  set fcod [open shmem_[set subsys].h w]
  puts $fcod $SHC(genericshmem.h)
  close $fcod
  set fcod [open shmem_[set subsys]_server.cpp w]
  puts $fcod $SHC(genericshmem.cpp)
  close $fcod
  set fcod [open test_shmem_[set subsys].cpp w]
  puts $fcod $SHC(genericshclient.cpp)
  close $fcod
  exec g++ -shared -g shmem_[set subsys]_server.cpp -o libshm_[set subsys]_server.so -lstdc++
  exec gcc -g test_shmem_[set subsys].cpp -o test_[set subsys] -lpthread -L. -lshm_[set subsys]_server
 }
}


proc generatetester { topiclist } {
 foreach subsys $topiclist {
  set fout [open [set subsys]_shmem_tester.c w]
  puts $fout "
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from [set subsys].idl using \"genshmem\".
  The genshmem tool is part of the LSST SAL middleware stack
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include \"[set subsys]_cache.h\"

int main(int argc, char *argv\[\])
\{
   int [set subsys]_shmsize;
   int lshmid;
   int icount=0;
   int [set subsys]_shmid = 0x[calcshmid $subsys];
   [set subsys]_cache *[set subsys]_ref;
   [set subsys]_shmsize = sizeof(struct [set subsys]_cache);
   lshmid = shmget([set subsys]_shmid, [set subsys]_shmsize , IPC_CREAT|0666);
   [set subsys]_ref  = ([set subsys]_cache *) shmat(lshmid, NULL, 0);
 
"
  set fin [open [set subsys]_cache.h r]
  gets $fin rec
  gets $fin rec
  while { [gets $fin rec] > -1 } {
     set v [string trim [lindex $rec 1] ";"]
     if { $v != "syncO" } {
       switch [lindex $rec 0] {
         byte -
         short -
         int - 
         long -
         float - 
         double { puts $fout "   [set subsys]_ref->$v++;" }
         char { set cv [lindex [split $v "\[\]"] 0]
                puts $fout "   icount++;
   sprintf([set subsys]_ref->$cv,\"string %d\",icount);" }
       }
     }
  }
  puts $fout "   [set subsys]_ref->syncO = 1;
   return(0);
\}
"  
  close $fout
 }
}





proc replacepubcode { topiclist op fid } {
global FREQUENCY
  switch $op {
        includes {
           puts $fid "#include <sys/shm.h>"
           foreach t $topiclist {
             puts $fid "#include \"[set subsys].h\""
             puts $fid "#include \"[set subsys]Support.h\""
             puts $fid "#include \"[set subsys]_cache.h\""
           }
        }
        finalize {
           foreach t $topiclist {
 	     puts $fid "    [set  t]TypeSupport_finalize();"
           } 
        }
        tidyup {
           foreach t $topiclist {
             puts $fid "
    [set t]_retcode = [set t]DataWriter_unregister_instance(
        [set t]_writer, [set t]_instance, &[set t]_instance_handle);
    if ([set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"[set t] unregister instance error %d\\n\", [set t]_retcode);
    \}
    /* Delete data sample */
    [set t]_retcode = [set t]TypeSupport_delete_data_ex(instance, DDS_BOOLEAN_TRUE);
    if ([set t]_retcode != DDS_RETCODE_OK) \{
        printf(\[set t\]TypeSupport_delete_data error %d\\n\", [set t]_retcode);
    \}"
           } 
        }
        variables {
           foreach t $topiclist {
             if { [info exists FREQUENCY($t)] == 0 } {set FREQUENCY($t) 1}
             if { $FREQUENCY($t) > 1 } {
                set sendp "\{0,[expr int(1000./$FREQUENCY($t))]\}"
             } else {
                set sendp "\{[expr int(1./$FREQUENCY($t))],0\}"
             }
             puts $fid "
    DDS_Topic *[set t]topic = NULL;
    DDS_DataWriter *[set t]_DDSwriter = NULL;
    [set t]DataWriter *[set t]_writer = NULL;
    [set t] *[set t]_instance = NULL;
    DDS_ReturnCode_t [set t]_retcode;
    DDS_InstanceHandle_t [set t]_instance_handle = DDS_HANDLE_NIL;
    const char *[set t]_type_name = NULL;
    int [set t]_count = 0;  
    struct DDS_Duration_t [set t]_send_period = $sendp;"
          } 
        }
        registertypes {
           foreach t $topiclist {
              puts $fid "
    [set t]_type_name = [set t]_TypeSupport_get_type_name();
    [set t]_retcode = [set t]_TypeSupport_register_type(
        participant, [set t]_type_name);
    if ([set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"[set t] register_type error %d\\n\", [set t]_retcode);
        publisher_shutdown(participant);
        return -1;
    \}"
           } 
        }
        createtopics {
           foreach t $topiclist {
             puts $fid "
     [set t]topic = DDS_DomainParticipant_create_topic(
        participant, \"Example [set t]\",
        [set t]type_name, &DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if ([set t]topic == NULL) \{
        printf(\"[set t] create_topic error\\n\");
        publisher_shutdown(participant);
        return -1;
    \}"
          } 
        }
        createwriters {
           foreach t $topiclist {
             puts $fid "
    [set t]_DDSwriter = DDS_Publisher_create_datawriter(
        publisher, [set t]_topic,
        &DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if ([set t]_DDSwriter == NULL) \{
        printf(\"[set t ] create_datawriter error\\n\");
        publisher_shutdown(participant);
        return -1;
    \}
    [set t]_writer = [set t]DataWriter_narrow([set t]_DDSwriter);
    if ([set t]_writer == NULL) \{
        printf(\"[set t] DataWriter narrow error\\n\");
        publisher_shutdown(participant);
        return -1;
    \}"
           } 
        }
        fromshmem { 
            addshmempub $topiclist $fid
        }
        finalize {
           foreach t $topiclist {
             puts $fid "
    [set t]_instance = [set t]TypeSupport_create_data_ex(DDS_BOOLEAN_TRUE);
    if ([set t]_instance == NULL) \{
        printf(\"[set t]TypeSupport_create_data error\\n\");
        publisher_shutdown(participant);
        return -1;
    \}
    /* For data type that has key, if the same instance is going to be
       written multiple times, initialize the key here
       and register the keyed instance prior to writing */
    /*
    [set t]_instance_handle = [set t]DataWriter_register_instance(
        [set t]_writer, [set t]_instance);
    */"
           } 
        }
  }
}

proc replacesubcode { topiclist op fid } {
  switch $op {
        includes {
           puts $fid "#include <sys/shm.h>"
           foreach t $topiclist {
             puts $fid "#include \"[set subsys].h\""
             puts $fid "#include \"[set subsys]Support.h\""
             puts $fid "#include \"[set subsys]_cache.h\""
           }
        }
        variables {
           foreach t $topiclist {
              puts $fid "
    DDS_Topic *topic_[set t] = NULL;
    struct DDS_DataReaderListener reader_listener_[set t] =
        DDS_DataReaderListener_INITIALIZER;
    DDS_DataReader *reader_[set t] = NULL;
    DDS_ReturnCode_t retcode_[set t];
    const char *type_name_[set t] = NULL;"
           }
        }
        topics {
           foreach t $topiclist {
              puts $fid "
    /* Register type before creating topic */
    type_name_[set t] = [set t]TypeSupport_get_type_name();
    retcode_[set t] = [set t]TypeSupport_register_type(participant, type_name_[set t]);
    if (retcode_[set t] != DDS_RETCODE_OK) \{
        printf(\"register_type error [set t] %d\\n\", retcode_[set t]);
        subscriber_shutdown(participant);
        return -1;
    \}

    /* To customize topic QoS, use
       DDS_DomainParticipant_get_default_topic_qos() */
    topic_[set t] = DDS_DomainParticipant_create_topic(
        participant, \"Example [set t]\",
        type_name_[set t], &DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic_[set t] == NULL) \{
        printf(\"create_topic [set t]error\\n\");
        subscriber_shutdown(participant);
        return -1;
    \}

    /* Setup data reader listener */
    reader_listener_[set t].on_requested_deadline_missed  =
        [set t]Listener_on_requested_deadline_missed;
    reader_listener_[set t].on_requested_incompatible_qos =
        [set t]Listener_on_requested_incompatible_qos;
    reader_listener_[set t].on_sample_rejected =
        [set t]Listener_on_sample_rejected;
    reader_listener_[set t].on_liveliness_changed =
        [set t]Listener_on_liveliness_changed;
    reader_listener_[set t].on_sample_lost =
        [set t]Listener_on_sample_lost;
    reader_listener_[set t].on_subscription_matched =
        [set t]Listener_on_subscription_matched;
    reader_listener_[set t].on_data_available =
        [set t]Listener_on_data_available;

    /* To customize data reader QoS, use
       DDS_Subscriber_get_default_datareader_qos() */
    reader_[set t] = DDS_Subscriber_create_datareader(
        subscriber, DDS_Topic_as_topicdescription(topic_[set t]),
        &DDS_DATAREADER_QOS_DEFAULT, &reader_listener_[set t], DDS_STATUS_MASK_ALL);
    if (reader_[set t] == NULL) \{
        printf(\"create_datareader [set t] error\\n\");
        subscriber_shutdown(participant);
        return -1;
    \}"
           }
        }
        callbacks {
           foreach t $topiclist {
              puts $fid "
void [set t]Listener_on_requested_deadline_missed(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_RequestedDeadlineMissedStatus *status)
\{
\}

void [set t]Listener_on_requested_incompatible_qos(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_RequestedIncompatibleQosStatus *status)
\{
\}

void [set t]Listener_on_sample_rejected(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SampleRejectedStatus *status)
\{
\}

void [set t]Listener_on_liveliness_changed(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_LivelinessChangedStatus *status)
\{
\}

void [set t]Listener_on_sample_lost(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SampleLostStatus *status)
\{
\}

void [set t]Listener_on_subscription_matched(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SubscriptionMatchedStatus *status)
\{
\}"
           }
        }
        newdata {
           foreach t $topiclist {
              puts $fid "
void [set t]Listener_on_data_available(
    void* listener_data,
    DDS_DataReader* reader)
\{
    [set t]DataReader *[set t]_reader = NULL;
    struct [set t]Seq data_seq = DDS_SEQUENCE_INITIALIZER;
    struct DDS_SampleInfoSeq info_seq = DDS_SEQUENCE_INITIALIZER;
    DDS_ReturnCode_t retcode;
    int i;

    [set t]_reader = [set t]DataReader_narrow(reader);
    if ([set t]_reader == NULL) \{
        printf(\"DataReader narrow error\\n\");
        return;
    \}

    retcode = [set t]DataReader_take(
        [set t]_reader,
        &data_seq, &info_seq, DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
    if (retcode == DDS_RETCODE_NO_DATA) \{
        return;
    \} else if (retcode != DDS_RETCODE_OK) \{
        printf(\"take error %d\\n\", retcode);
        return;
    \}

    for (i = 0; i < [set t]Seq_get_length(&data_seq); ++i) \{
        if (DDS_SampleInfoSeq_get_reference(&info_seq, i)->valid_data) \{
            [set t]_toShmem(
                [set t]Seq_get_reference(&data_seq, i));
        \}
    \}

    retcode = [set t]DataReader_return_loan(
        [set t]_reader,
        &data_seq, &info_seq);
    if (retcode != DDS_RETCODE_OK) \{
        printf(\"return loan error %d\\n\", retcode);
    \}
\}"
           }
        }
        toshmem {
           foreach t $topiclist {
              puts $fid "
int [set subsys]_shmsize;
int [set subsys]_lshmid = NULL;
int [set subsys]_shmid = 0x[calcshmid $subsys];
[set subsys]_cache *[set subsys]_ref;

void [set t]_toShmem ( ([set t] *)instance ,int iterator )
\{
    if ([set subsys]_lshmid == NULL ) \{
      [set subsys]_shmid = 0x[calcshmid $subsys];
      [set subsys]_shmsize = sizeof(struct [set subsys]_cache);
      [set subsys]_lshmid = shmget([set subsys]_shmid, [set subsys]_shmsize , IPC_CREAT|0666);
    \}
"
              set fget [open [set subsys]_getstub.txt r]
              while { [gets $fget] > -1 } { 
                 puts $fid "$rec"
              }
              close $fget
              puts $fid "
    [set subsys]_ref->syncI = 1; 
\}
"
           }
        }
        tidyup {
           foreach t $topiclist {
              puts $fid ""
           }
        }
  }
}





proc parsesub { topiclist } {
global scriptdir
global NDDS_VERSION NDDSPUBLOOPSIZE
  set fin  [open $scriptdir/subsystem_subscriber.c.template r]
  set basename [lindex [split [lindex $topiclist 0] _] 0]
  set fout [open [set basename]_shmem_subscriber.c w]
  while { [gets $fin rec] > -1 } {
    if { [string trim $rec] == "/* Main loop */" } {
           addshmemcode $subsys $fout
    } else {
           if { [string range $rec 0 8] == "###INSERT" } {
              replacesubcode $topiclist [lindex $rec 1] $fout
           } else {
              puts $fout $rec
           }
    }
  }
  close $fin
  close $fout
}

proc parsepub { topiclist } {
global scriptdir
global NDDS_VERSION NDDSPUBLOOPSIZE
  set fin  [open $scriptdir/subsystem_publisher.c.template r]
  set basename [lindex [split [lindex $topiclist 0] _] 0]
  set fout [open [set basename]_shmem_publisher.c w]
  while { [gets $fin rec] > -1 } {
    if { [string trim $rec] == "/* Main loop */" } {
           addshmemcode $subsys $fout
           set i $NDDSPUBLOOPSIZE($NDDS_VERSION)
           while { $i > 0 } {gets $fin rec ; incr i -1}
    } else {
           if { [string range $rec 0 8] == "###INSERT" } {
              replacepubcode $topiclist [lindex $rec 1] $fout
           } else {
              puts $fout $rec
           }
    }
  }
  close $fin
  close $fout
}

proc parsemakefile { subsys } {
  set mf [glob makefile*i86Linux2.6gcc3.4.3]
  set fin [open $mf r]
  set fout [open makefile w]
  while { [gets $fin rec] > -1 } {
    if { [string range $rec 0 3] != "EXEC" } {
       puts $fout $rec
    } else {
       puts $fout "EXEC          = [set subsys]_subscriber \\
		[set subsys]_publisher \\
		[set subsys]_shmem_publisher \\
		[set subsys]_shmem_tester"
    }
  }
  close $fin 
  close $fout
}




set NDDS_VERSION 4.2e
set NDDSPUBLOOPSIZE(4.2e) 17
set LVERSION i86Linux2.6gcc3.4.3
set basedir .
set scriptdir /usr/local/scripts/tcl

source $scriptdir/managetypes.tcl
source $basedir/stream_frequencies.tcl 

set all [glob $subsys*.idl]
set topiclist ""
foreach t [lsort $all] {
  lappend topiclist [file rootname $t]
}

set basename [lindex [split $subsys _] 0]
source $basedir/revCodes.tcl
set workdir $basedir/shmem-$basename
exec mkdir -p $workdir


puts stdout "Processing $subsys"
cd $workdir
doddsgen $topiclist
shcoder $subsys
generatetcllib $subsys

