
proc replacepubcode { topiclist op fid } {
global FREQUENCY
  switch $op {
        includes {
           puts $fid "#include <sys/shm.h>"
           puts $fid "#include \"svcSAL.h\""
           foreach t $topiclist {
             puts $fid "#include \"[set t].h\""
             puts $fid "#include \"[set t]_cache.h\""
           }
####           puts $fid "extern svcSAL_cachehandle svcSAL_handle\[SAL__MAX_HANDLES\];"
        }
        finalize {
           foreach t $topiclist {
 	     puts $fid "    /* No OSPL M[set  t]TypeSupport_finalize(); */"
           } 
        }
        tidyup {
           foreach t $topiclist {
             puts $fid "
    [set t]_retcode = M[set t]DataWriter_unregister_instance(
        M[set t]_writer, [set t]_instance, &[set t]_instance_handle);
    if (M[set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"M[set t] unregister instance error %d\\n\", M[set t]_retcode);
    \}
    /* Delete data sample  - NOT in OSPL
    M[set t]_retcode = M[set t]TypeSupport_delete_data_ex([set t]_instance, DDS_BOOLEAN_TRUE);
    if (M[set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"M[set t]TypeSupport_delete_data error %d\\n\", M[set t]_retcode);
    \}
    */"
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
    DDS_Topic *M[set t]_topic = NULL;
    DDS_DataWriter *M[set t]_DDSwriter = NULL;
    M[set t]DataWriter *M[set t]_writer = NULL;
    M[set t] *[set t]_instance = NULL;
    DDS_ReturnCode_t M[set t]_retcode;
    DDS_InstanceHandle_t [set t]_instance_handle = DDS_HANDLE_NIL;
    const char *M[set t]_type_name = NULL;
    int M[set t]_count = 0;  
    struct DDS_Duration_t M[set t]_send_period = $sendp;"
          } 
        }
        registertypes {
           foreach t $topiclist {
              puts $fid "
    M[set t]_type_name = M[set t]TypeSupport_get_type_name();
    M[set t]_type_name = [set t]_msgTypeSupport__alloc ();
    M[set t]_retcode = M[set t]TypeSupport_register_type(
        participant, M[set t]_type_name, \"M::[set t]\");
    if (M[set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"M[set t] register_type error %d\\n\", M[set t]_retcode);
        publisher_shutdown(participant);
        return -1;
    \}"
           } 
        }
        createtopics {
           foreach t $topiclist {
             puts $fid "
     M[set t]_topic = DDS_DomainParticipant_create_topic(
        participant, \"[set t]_topic\", \"M::[set t]\" ,
        DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_ANY_STATUS);
    if (M[set t]_topic == NULL) \{
        printf(\"M[set t] create_topic error\\n\");
        publisher_shutdown(participant);
        return -1;
    \}"
          } 
        }
        createwriters {
           foreach t $topiclist {
             puts $fid "
    M[set t]_DDSwriter = DDS_Publisher_create_datawriter(
        publisher, M[set t]_topic,
        DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */, DDS_ANY_STATUS);
    if (M[set t]_DDSwriter == NULL) \{
        printf(\"M[set t ] create_datawriter error\\n\");
        publisher_shutdown(participant);
        return -1;
    \}"
           } 
        }
        fromshmem { 
            addshmempub $topiclist $fid
        }
        createinstances {
           foreach t $topiclist {
             puts $fid "
                        [set t]_instance = M[set t]__alloc ();
    if ([set t]_instance == NULL) \{
        printf(\"M[set t]__alloc error\\n\");
        publisher_shutdown(participant);
        return -1;
    \}
    /* For data type that has key, if the same instance is going to be
       written multiple times, initialize the key here
       and register the keyed instance prior to writing */
    /*
    [set t]_instance_handle = M[set t]DataWriter_register_instance(
        M[set t]_writer, [set t]_instance);
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
             puts $fid "#include \"[set t]_cache.h\""
           }
####           puts $fid "extern svcSAL_cachehandle svcSAL_handle\[SAL__MAX_HANDLES\];"
        }
        variables {
           puts $fid "    DDS_WaitSet		w;"
           foreach t $topiclist {
              puts $fid "
    DDS_Topic *topic_M[set t] = NULL;
    /* copy this struct from ndds ?*/
    struct DDS_DataReaderListener reader_listener_M[set t] =
        DDS_DataReaderListener_INITIALIZER;
    DDS_DataReader *reader_M[set t] = NULL;
    DDS_StatusCondition *condition_M[set t] = DDS_OBJECT_NIL;
    DDS_ReturnCode_t M[set t]_retcode;
    const char *type_name_M[set t] = NULL;"
           }
        }
        topics {
           foreach t $topiclist {
              puts $fid "
    /* Register type before creating topic */
    type_name_[set t] = M[set t]_msgTypeSupport__alloc ();
    type_name_[set t] = [set t]TypeSupport_get_type_name();
    M[set t]_retcode = M[set t]TypeSupport_register_type(
        participant, M[set t]_type_name, \"M::[set t]\");
    if (M[set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"register_type error M[set t] %d\\n\", M[set t]_retcode);
        subscriber_shutdown(participant);
        return -1;
    \}

    /* To customize topic QoS, use
       DDS_DomainParticipant_get_default_topic_qos() */
    topic_M[set t] = DDS_DomainParticipant_create_topic(
        participant, \"[set t]_topic\", \"M::[set t]\" ,
        DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_ANY_STATUS);
    if (topic_M[set t] == NULL) \{
        printf(\"create_topic M[set t]error\\n\");
        subscriber_shutdown(participant);
        return -1;
    \}

    /* Setup data reader listener */
    reader_listener_M[set t].on_requested_deadline_missed  =
        [set t]DataReader_get_requested_deadline_missed_status;
    reader_listener_M[set t].on_requested_incompatible_qos =
        [set t]DataReader_get_requested_incompatible_qos_status;
    reader_listener_M[set t].on_sample_rejected =
        [set t]DataReader_get_sample_rejected_status;
    reader_listener_M[set t].on_liveliness_changed =
        [set t]DataReader_get_liveliness_changed_status;
    reader_listener_M[set t].on_sample_lost =
        [set t]DataReader_get_sample_lost_status ;
    reader_listener_M[set t].on_subscription_matched =
        [set t]DataReader_get_subscription_match_status;
    reader_listener_M[set t].on_data_available =
        [set t]Listener_on_data_available;

    /* To customize data reader QoS, use
       DDS_Subscriber_get_default_datareader_qos() */
    reader_M[set t] = DDS_Subscriber_create_datareader(
        subscriber, topic_M[set t],
        DDS_DATAREADER_QOS_DEFAULT, &reader_listener_M[set t], DDS_ANY_STATUS);

    /* OSPL maybe uses this instead Add datareader statuscondition to waitset 
	then waits on DDS_WaitSet_wait (w, conditionList, &wait_timeout)
	to locate incoming message type via conditionlist.....
    condition_M[set t] = DDS_DataReader_get_statuscondition (reader_M[set t]);
    DDS_StatusCondition_set_enabled_statuses (condition_M[set t], DDS_DATA_AVAILABLE_STATUS);
    M[set t]_retcode = DDS_WaitSet_attach_condition (w, condition_M[set t]);
    */    
    if (reader_M[set t] == NULL) \{
        printf(\"create_datareader M[set t] error\\n\");
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
    M[set t]DataReader *M[set t]_reader = NULL;
    struct M[set t]Seq data_seq = DDS_SEQUENCE_INITIALIZER;
    struct DDS_SampleInfoSeq info_seq = DDS_SEQUENCE_INITIALIZER;
    DDS_ReturnCode_t M[set t]_retcode;
    int i;

    M[set t]_retcode = M[set t]DataReader_take_next_instance(
        M[set t]_reader,
        &data_seq, &info_seq, DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
    if (M[set t]_retcode == DDS_RETCODE_NO_DATA) \{
        return;
    \} else if (M[set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"take error %d\\n\", M[set t]_retcode);
        return;
    \}

    for (i = 0; i < M[set t]Seq_get_length(&data_seq); ++i) \{
        if (DDS_SampleInfoSeq_get_reference(&info_seq, i)->valid_data) \{
            M[set t]_toShmem(
                M[set t]Seq_get_reference(&data_seq, i));
        \}
    \}

    M[set t]_retcode = M[set t]DataReader_return_loan(
        M[set t]_reader,
        &data_seq, &info_seq);
    if (M[set t]_retcode != DDS_RETCODE_OK) \{
        printf(\"return loan error %d\\n\", M[set t]_retcode);
    \}
\}"
           }
        }
        toshmem {
           foreach t $topiclist {
              puts $fid "

int [set t]_toShmem ( M[set t] *[set t]_instance )
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

proc osplddsgen { topiclist {lang c} } {
global WORKING
   foreach t $topiclist {
      exec mkdir -p $WORKING/ospl-$t
      set fin [open $WORKING/$t.idl r]
      set fout [open $WORKING/ospl-$t/$t.idl w]
      puts $fout "module M$t
\{
  struct $t
  \{
	unsigned long       block;"
      gets $fin rec
      while { [gets $fin rec] > -1 } {
           puts $fout "	$rec"
      }
      puts $fout "  #pragma keylist $t block     
\};
"
      close $fin
      close $fout
      foreach l $lang {
        exec idlpp -d $WORKING/ospl-$t -S -l $l $WORKING/ospl-$t/$t.idl
      }
   }
}

