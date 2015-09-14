#!/usr/bin/tclsh

proc doddsgen { sublist publist } {
global scriptdir
puts stdout "doddsgen sublist = $sublist"
   parsesub $sublist
puts stdout "doddsgen publist = $publist"
   parsepub $publist
   parsemakefile  $sublist $publist
}

proc doortegen { sublist publist } {
  puts stdout "<P><HR><H2>ORTE code generation not available yet</H2><HR><P>"
}


proc doicegen { sublist publist } {
  puts stdout "<P><HR><H2>ICE code generation not available yet</H2><HR><P>"
}


proc doamqgen { sublist publist } {
  puts stdout "<P><HR><H2>ActiveMQ code generation not available yet</H2><HR><P>"
}


proc dolvgen { sublist publist } {
global scriptdir
   set topiclist [lsort -unique "$sublist $publist"]
   set incs [glob $scriptdir/code/labview/*.h]
   foreach i $incs {exec cp $i .}
   set fin [open $scriptdir/code/labview/SAL_commLib.h.template r]
   set fout [open SAL_commLib.h w]
   while { [gets $fin rec] > -1 } {
      if { [string range $rec 0 8] == "###INSERT" } {
         replacelvcode $topiclist [lindex $rec 1] $fout
      } else {
         puts $fout $rec
      }
   }
   close $fin
   close $fout
   set fin [open $scriptdir/code/labview/SAL_commLib.c.template r]
   set fout [open SAL_commLib.c w]
   while { [gets $fin rec] > -1 } {
      if { [string range $rec 0 8] == "###INSERT" } {
         replacelvcode $topiclist [lindex $rec 1] $fout
      } else {
         puts $fout $rec
      }
   }
   close $fin
   close $fout
}

proc replacelvcode { topiclist op fid } {
  switch $op {
     includes {
               puts $fid "#include \"svcSAL.h\""
               foreach t $topiclist {
                 puts $fid "#include \"[set t].h\""
                 puts $fid "#include \"[set t]_cache.h\""
               }
     }
     prototypes {
                 foreach t $topiclist {
                    puts $fid "
extern int LVcomm_get_i[set t](int fd);
extern int LVcomm_send_e[set t](int fd);
extern int LVcomm_close_[set t](int fd);"
                    set fpi [open ../shmem-[set t]/[set t]_lvprostub.txt r]
                    gets $fpi rec ; puts $fid "extern $rec"
                    gets $fpi rec ; puts $fid "extern $rec"
                    close $fpi
                 }
     }
     readwrite {
                 foreach t $topiclist {
                    set fpi [open ../shmem-[set t]/[set t]_lvprostub.txt r]
                    gets $fpi rec
                    puts $fid [string trim $rec " ;"]
                    puts $fid "\{\n	it ilen;"
                    set fpro [open ../shmem-[set t]/[set t]_lvgetstub.txt r]
                    puts $fid "
	[set t]_cache *[set t]_ref;
	[set t]_ref = LV_serial\[fd\].shm_ptr;"
                    while { [gets $fpro rec] > -1 } {
                       puts $fid $rec
                    }
                    puts $fid "	[set t]_ref->syncI = 0;\nreturn(0);\n\}\n\n"
                    close $fpro
                    gets $fpi rec
                    puts $fid [string trim $rec " ;"]
                    puts $fid "\{\n"
                    set fpro [open ../shmem-[set t]/[set t]_lvputstub.txt r]
                    puts $fid "
	[set t]_cache *[set t]_ref;
	[set t]_ref = LV_serial\[fd\].shm_ptr;"
                    while { [gets $fpro rec] > -1 } {
                       puts $fid $rec
                    }
                    puts $fid "	[set t]_ref->syncO = 1;\nreturn(0);\n\}\n\n"
                    close $fpro
                    puts $fid "
int LVcomm_get_i[set t](int fd)
\{
        sem_post(&(LV_serial\[fd\].sem_read));
        return(0);
\}
int LVcomm_send_e[set t](int fd)
\{
	if (LV_serial\[fd\].ew.status == LVTRUE)
		return(-1);
	return(0);
\}
int LVcomm_close_[set t](int fd)
\{
	LV_serial\[fd\].handle = -1;
	sem_post(&(LV_serial\[fd\].sem_read));
	sem_post(&(LV_serial\[fd\].sem_write));
	return(0);
\}
"
                 }
     }
  }
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
   int [set subsys]_salHandle;
   svcSAL_cachehandle svcSAL_handle_[set subsys];
   [set subsys]_cache *[set subsys]_ref;"
  }
  foreach subsys $topiclist {
    puts $fid "
    [set subsys]_salHandle = svcSAL_connect1 (\"[set subsys]\", &svcSAL_handle_[set subsys] );
   if ( [set subsys]_salHandle != SAL__OK ) \{
      return(SAL__NOT_DEFINED);
   \}
   [set subsys]_ref  = ([set subsys]_cache *) svcSAL_handle_[set subsys].ref;

"
  }
  puts $fid "
	while (1) \{
		svcSAL_sleep(1000);"
  foreach subsys $topiclist {
    puts $fid "
		if ([set subsys]_ref->syncO == 1) \{
			[set subsys]_count++;"
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




proc replacepubcode { topiclist op fid } {
global FREQUENCY
  switch $op {
        includes {
           puts $fid "#include <sys/shm.h>"
           puts $fid "#include \"svcSAL.h\""
           foreach t $topiclist {
             puts $fid "#include \"[set t].h\""
             puts $fid "#include \"[set t]Support.h\""
             puts $fid "#include \"[set t]_cache.h\""
           }
####           puts $fid "extern svcSAL_cachehandle svcSAL_handle\[SAL__MAX_HANDLES\];"
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
    [set t]_retcode = [set t]TypeSupport_delete_data_ex([set t]_instance, DDS_BOOLEAN_TRUE);
    if ([set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"[set t]TypeSupport_delete_data error %d\\n\", [set t]_retcode);
    \}"
           } 
        }
        variables {
           foreach t $topiclist {
             if { [info exists FREQUENCY($t)] == 0 } {set FREQUENCY($t) 1}
             if { $FREQUENCY($t) > 1 } {
                set sendp "\{0,[expr int(1000000000./$FREQUENCY($t))]\}"
             } else {
                set sendp "\{[expr int(1./$FREQUENCY($t))],0\}"
             }
             puts $fid "
    DDS_Topic *[set t]_topic = NULL;
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
    [set t]_type_name = [set t]TypeSupport_get_type_name();
    [set t]_retcode = [set t]TypeSupport_register_type(
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
     [set t]_topic = DDS_DomainParticipant_create_topic(
        participant, \"Example [set t]\",
        [set t]_type_name, &DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if ([set t]_topic == NULL) \{
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
           puts $fid "#include \"svcSAL.h\""
           foreach t $topiclist {
             puts $fid "#include \"[set t].h\""
             puts $fid "#include \"[set t]Support.h\""
             puts $fid "#include \"[set t]_cache.h\""
           }
####           puts $fid "extern svcSAL_cachehandle svcSAL_handle\[SAL__MAX_HANDLES\];"
        }
        variables {
           foreach t $topiclist {
              puts $fid "
    DDS_Topic *topic_[set t] = NULL;
    struct DDS_DataReaderListener reader_listener_[set t] =
        DDS_DataReaderListener_INITIALIZER;
    DDS_DataReader *reader_[set t] = NULL;
    DDS_ReturnCode_t [set t]_retcode;
    const char *type_name_[set t] = NULL;"
           }
        }
        topics {
           foreach t $topiclist {
              puts $fid "
    /* Register type before creating topic */
    type_name_[set t] = [set t]TypeSupport_get_type_name();
    [set t]_retcode = [set t]TypeSupport_register_type(participant, type_name_[set t]);
    if ([set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"register_type error [set t] %d\\n\", [set t]_retcode);
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
    DDS_ReturnCode_t [set t]_retcode;
    int i;

    [set t]_reader = [set t]DataReader_narrow(reader);
    if ([set t]_reader == NULL) \{
        printf(\"DataReader narrow error\\n\");
        return;
    \}

    [set t]_retcode = [set t]DataReader_take(
        [set t]_reader,
        &data_seq, &info_seq, DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
    if ([set t]_retcode == DDS_RETCODE_NO_DATA) \{
        return;
    \} else if ([set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"take error %d\\n\", [set t]_retcode);
        return;
    \}

    for (i = 0; i < [set t]Seq_get_length(&data_seq); ++i) \{
        if (DDS_SampleInfoSeq_get_reference(&info_seq, i)->valid_data) \{
            [set t]_toShmem(
                [set t]Seq_get_reference(&data_seq, i));
        \}
    \}

    [set t]_retcode = [set t]DataReader_return_loan(
        [set t]_reader,
        &data_seq, &info_seq);
    if ([set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"return loan error %d\\n\", [set t]_retcode);
    \}
\}"
           }
        }
        toshmem {
           foreach t $topiclist {
              puts $fid "

int [set t]_toShmem ( [set t] *[set t]_instance )
\{
    int [set t]_salHandle;
    svcSAL_cachehandle svcSAL_handle_[set t];
    [set t]_cache *[set t]_ref;

	   [set t]_salHandle = svcSAL_connect1 (\"[set t]\", &svcSAL_handle_[set t] );
	   if ( [set t]_salHandle == 0 ) \{
	      return(SAL__NOT_DEFINED);
	   \}

	   [set t]_ref  = ([set t]_cache *) svcSAL_handle_[set t].ref;
"
              set fget [open ../shmem-[set t]/[set t]_getstub.txt r]
              while { [gets $fget rec] > -1 } { 
                 puts $fid "$rec"
              }
              close $fget
              puts $fid "
	    [set t]_ref->syncI = 1;
            printf(\"Got data for [set t]\\n\");
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
  set fin  [open $scriptdir/code/subsystem_subscriber.c.template r]
  set basename [lindex [split [lindex $topiclist 0] _] 0]
  set fout [open [set basename]_shmem_subscriber.c w]
  while { [gets $fin rec] > -1 } {
           if { [string range $rec 0 8] == "###INSERT" } {
              replacesubcode $topiclist [lindex $rec 1] $fout
           } else {
              puts $fout $rec
           }
  }
  close $fin
  close $fout
}

proc parsepub { topiclist } {
global scriptdir
global NDDS_VERSION NDDSPUBLOOPSIZE
  set fin  [open $scriptdir/code/subsystem_publisher.c.template r]
  set basename [lindex [split [lindex $topiclist 0] _] 0]
  set fout [open [set basename]_shmem_publisher.c w]
  while { [gets $fin rec] > -1 } {
           if { [string range $rec 0 8] == "###INSERT" } {
              replacepubcode $topiclist [lindex $rec 1] $fout
           } else {
              puts $fout $rec
           }
  }
  close $fin
  close $fout
}

proc parsemakefile { sublist publist } {
global LVERSION
  set basename [lindex [split [lindex "$sublist $publist" 0] _] 0]
  set mf [lindex [glob makefile*$LVERSION] 0]
  set fin [open $mf r]
  set fout [open makefile w]
  while { [gets $fin rec] > -1 } {
    if { [string range $rec 0 3] != "EXEC" } {
       if { [string range $rec 0 12] == "COMMONSOURCES" } {
          puts $fout "COMMONSOURCES	= \\"
          foreach s "$sublist $publist" {
             if { [info exists done($s)] == 0 } {
                puts $fout "	[set s].c [set s]Plugin.c [set s]Support.c \\"
                set done($s) 1
             }
          }
          puts $fout "\n\n"
       } else {
          if { [string range $rec 0 6] == "LIBS = " } {
             puts $fout $rec
             puts $fout "	./libshmSAL_linux.so \\"
          } else {
             puts $fout $rec
          }
       }
    } else {
       puts $fout "EXEC          = \\"
       foreach subsys $sublist {
          puts $fout "		[set subsys]_subscriber \\
		[set subsys]_shmem_tester \\"
       }
       foreach subsys $publist {
          puts $fout "		[set subsys]_publisher \\
		[set subsys]_shmem_publisher \\
		[set subsys]_shmem_tester \\"
       }
       if { $sublist != "" } {
          puts $fout "		[set basename]_shmem_subscriber \\"
       }
       if { $publist != "" } {
          puts $fout "		[set basename]_shmem_publisher \\"
       }
       puts $fout "\n\n"
    }
  }
  close $fin 
  close $fout
}



if { [info exists JUSTTESTING] } {
  set PUBS(camera_BEE_biases) "yes"
  set PUBS(camera_BEE_clocks) "yes"
  set PUBS(camera_BEE_thermal) "yes"
  set PROC(camera_BEE_biases) "yes"
  set PROC(camera_BEE_clocks) "yes"
  set PROC(camera_BEE_thermal) "yes"
  set SUBS(camera_CCS) "yes"
}

set scriptdir /usr/local/scripts/tcl
 
source $scriptdir/ndds_version.tcl


set basedir /home/shared/lsst/tests/api/streams
cd $basedir

source $scriptdir/managetypes.tcl
source $basedir/stream_frequencies.tcl 

if { [info exists FormData(GenerateALL)] } {
  set all [glob $subsys*.idl]
  set topiclist ""
  foreach t [lsort $all] {
    lappend topiclist [file rootname $t]
  }
} else {
  set publist ""
  set sublist ""
  foreach t [array names ISSU] {
     set s [lindex [split $t ._] 0]
     set PUBS([set s]_command)  1
     set SUBS([set s]_response) 1
  }
  foreach t [array names PROC] {
     set s [lindex [split $t ._] 0]
     set SUBS([set s]_command)  1
     set PUBS([set s]_response) 1
  }
#  foreach t [array names PUBS] {
#     set id [join [split $t .] _]
#     set publist "$publist $id"
#  }
#  foreach t [array names SUBS] {
#     set sublist "$sublist $id"
#  }
}

set publist [array names PUBS]
set sublist [array names SUBS]

set subsys [lindex [split [lindex "$sublist $publist" 0] _.] 0]
set basename [lindex [split $subsys _.] 0]
source $basedir/revCodes.tcl
exec rm -fr  $basedir/shmem-$basename
exec mkdir -p  $basedir/shmem-$basename

#printformdata
#puts stdout "basedoir = $basedir"
#puts stdout "sublist = $sublist"

puts stdout "<HTML><HEAD><TITLE>Service Abstraction Layer API generator</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"/LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"/salg.gif\" ALIGN=CENTER><P><HR><P>
<H1>Code generation phase</H1>
<P><HR><P>"

flush stdout

puts stdout "<PRE>"
catch {unset DONE}

foreach t "$sublist $publist" {
  if { [info exists DONE($t)] == 0 } {
    puts stdout "Processing $t"
    if { [info exists FormData(mw_ndds)] } {
      catch {exec $scriptdir/genshmem.tcl $t +dds} result
    } else {
      catch {exec $scriptdir/genshmem.tcl $t} result
    }
    puts stdout "$result"
    set res [glob ./shmem-$t/*]
    foreach f $res { exec cp $f ./shmem-$basename/. }
    puts stdout "Done $t\n"
    flush stdout
    set DONE($t) 1
  }
}

puts stdout "Building shmem interfaces"
puts stdout "Processing $sublist $publist"
set workdir $basedir/shmem-$basename
cd $workdir
doddsgen "$sublist" "$publist"
if { [info exists FormData(mw_orte)] } {
  doortegen $sublist $publist
}
if { [info exists FormData(mw_ice)] } {
  doicegen $sublist $publist
}
if { [info exists FormData(mw_activemq)] } {
  doamqgen $sublist $publist
}
if { [info exists FormData(langlv)] } {
  dolvgen $sublist $publist
}

set code [glob $scriptdir/code/*.c]
foreach f $code { exec cp $f . }
exec cp $scriptdir/code/makefile.sal .
exec cp $scriptdir/code/makefile.saltcl .
exec cp /usr/local/scripts/include/svcSAL.h .

source $scriptdir/genshmtclpersubsys.tcl
puts stdout "</PRE><P><HR><P><H1>Compilation phase</H1><P><PRE>"

source $scriptdir/accesspersubsystem.tcl
set res [ catch { exec $scriptdir/ddsmake -f makefile.sal } op]
puts stdout "$op"
set res [ catch { exec $scriptdir/ddsmake -f makefile.saltcl } op]
exec ln -sf libshmSALtcl_linux.so.$SALVERSION libshmSALtcl.so
puts stdout "$op"
if { [info exists FormData(mw_ndds)] } {
  set res [ catch { exec $scriptdir/ddsmake } op]
  puts stdout "$op"
}

if { [info exists FormData(mw_orte)] } {
  set res [ catch { exec $scriptdir/ortemake } op]
  puts stdout "$op"
}

if { [info exists FormData(mw_activemq)] } {
  set res [ catch { exec $scriptdir/activemqmake } op]
  puts stdout "$op"
}

if { [info exists FormData(mw_ice)] } {
  set res [ catch { exec $scriptdir/icemake } op]
  puts stdout "$op"
}

if { [info exists FormData(langlv)] } {
  set res [ catch { exec $scriptdir/lvmake } op]
  puts stdout "$op"
}


puts stdout "</PRE><P><HR><P><H1>Generating distribution</H1><P>"






