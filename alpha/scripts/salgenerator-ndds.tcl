set CNV(byte) CHAR
set CNV(double) DOUBLE
set CNV(float) FLOAT
set CNV(int) INT
set CNV(short) SHORT
set CNV(long) INT
set CNV(string) CHAR


proc parsetemplate { op fid } {
global NDDSGEN SUBS PUBS CNV streamdir DOMAINID
   if { $op == "init" } {
      foreach s [array names NDDSGEN] {
        puts $fid "
    if ( strcmp(\"$s\",streamName) == 0) \{
       currentInstance = ($s)new $s;"
    if { [info exists SUBS($s) } {
       puts $fid "    [set s]_subscriber_ndds(domainID);"
    }
    if { [info exists PUBS($s) } {
       puts $fid "    [set s]_publisher_ndds(domainID, currentInstance);"
    }
    puts $fid "    }"
   }
   if { $op == "delete" } {
     puts $fid "delete currentInstance;"
   }
   if { $op == "wait" } {
        puts $fid "
    currentSample->newData = SAL__WAITING_FOR_NEXT;
    status = waitOnTlm(timeout);
    if (status != SAL__OK) \{return status;\} 
    }"
   }
   if { $op == "include" } {
      foreach s [array names NDDSGEN] {
        puts $fid "#include \"$s.h\""
      }
   }
   if { [lindex [split $op -] 0] == "get" } {
      set ctyp [lindex [split $op -] 1]
      foreach s [array names SUBS] {
        set fin [open $streamdir/$s.idl r]
        gets $fin rec
        while { [gets $fin rec] > -1 } {
           if { [string length $rec] > 3 } {
              set t [lindex [lindex [split $rec "\<"] 0] 0]
              set n [string trim [lindex $rec 1] ";"]
              if { $CNV($t) == $ctyp } {
                 puts $fid "  if (strcmp(\"$n\",itemName) == 0) \{"
                 switch $ctyp {
                    CHAR {
                      puts $fid "    strcpy(textValue,currentInstance->$n);"
                    }
                    SHORT -
                    USHORT -
                    UINT -
                    INT {
                      puts $fid "    intValue = currentInstance->$n;"
                    }
                    FLOAT {
                      puts $fid "    fValue = currentInstance->$n;"
                    }
                    DOUBLE {
                      puts $fid "    dValue = currentInstance->$n;"
                    }
                 }
                 puts $fid "  \}"
              }
           }
        }
        close $fin
      }
   }
   if { [lindex [split $op -] 0] == "put" } {
      set ctyp [lindex [split $op -] 1]
      foreach s [array names SUBS] {
        set fin [open $streamdir/$s.idl r]
        gets $fin rec
        while { [gets $fin rec] > -1 } {
           if { [string length $rec] > 3 } {
              set t [lindex [lindex [split $rec "\<"] 0] 0]
              set n [string trim [lindex $rec 1] ";"]
              if { $CNV($t) == $ctyp } {
                 puts $fid "  if (strcmp(\"$n\",itemName) == 0) \{"
                 switch $ctyp {
                    CHAR {
                      puts $fid "    strcpy(currentInstance->$n,textValue);"
                    }
                    SHORT -
                    USHORT -
                    UINT -
                    INT {
                      puts $fid "    currentInstance->$n = intValue;"
                    }
                    FLOAT {
                      puts $fid "    currentInstance->$n = fValue;"
                    }
                    DOUBLE {
                      puts $fid "    currentInstance->$n = dValue;"
                    }
                 }
                 puts $fid "  \}"
              }
           }
        }
        close $fin
      }
   }
}

proc buildsalndds { } {
global stagingdir salcodedir
  set fin [open $salcodedir/svcSAL_ndds.cpp r]
  set fout [open $stagingdir/svcSAL_template_ndds.cpp w]
  while { [gets $fin rec] > -1 } {
     if { [string range $rec 0 2] != "###" } {
        puts $fout $rec
     } else {
        set op [string range $rec 3 end]
        parsetemplate $op $fout
     }
  }
  close $fin
  close $fout
}


proc genndds { pub sub s } {
global NDDSCOMPILER stagingdir
   puts stdout "Subsystem $s : pub=$pub sub=$sub"
   catch {exec rtiddsgen -language C++ -example $NDDSCOMPILER $s.idl -replace} result
   set flist "[set s].h $s.idl $s.cxx [set s]Support.h [set s]Support.cxx [set s]Plugin.h [set s]Plugin.cxx"
   if { $pub } {
     set fpout [open $stagingdir/[set s]_publisher.cxx w]
     puts $fpout "
#include <stdio.h>
#include <stdlib.h>
#include \"ndds/ndds_cpp.h\"
#include \"$s.h\"
#include \"[set s]Support.h\"
extern \"C\" int [set s]_publisher_ndds(int domainId, [set s] *instance)
\{
    DDSDomainParticipant *participant = NULL;
    DDSPublisher *publisher = NULL;
    DDSTopic *topic = NULL;
    DDSDataWriter *writer = NULL;
    [set s]DataWriter * [set s]_writer = NULL;
    DDS_ReturnCode_t retcode;
    DDS_InstanceHandle_t instance_handle = DDS_HANDLE_NIL;
    const char *type_name = NULL;

    /* To customize participant QoS, use
       DDSTheParticipantFactory->get_default_participant_qos() */
    participant = DDSTheParticipantFactory->create_participant(
        domainId, DDS_PARTICIPANT_QOS_DEFAULT,
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (participant == NULL) \{
        printf(\"create_participant error\\n\");
    /*        [set s]_publisher_shutdown(participant); */
        return -1;
    \}
                                                                                
    /* To customize publisher QoS, use
       participant->get_default_publisher_qos() */
    publisher = participant->create_publisher(
        DDS_PUBLISHER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (publisher == NULL) \{
        printf(\"create_participant error\\n\");
    /*    publisher_shutdown(participant); */
        return -1;
    \}

    /* Register type before creating topic */
    type_name = [set s]TypeSupport::get_type_name();
    retcode = [set s]TypeSupport::register_type(
        participant, type_name);
    if (retcode != DDS_RETCODE_OK) \{
        printf(\"register_type error %d\\n\", retcode);
    /*    publisher_shutdown(participant); */
        return -1;
    \}
                                                                                
    /* To customize topic QoS, use
       participant->get_default_topic_qos() */
    topic = participant->create_topic(
        \"Topic [set s]\",
        type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic == NULL) \{
        printf(\"create_topic error\\n\");
    /*    publisher_shutdown(participant); */
        return -1;
    \}

    /* To customize data writer QoS, use
       publisher->get_default_datawriter_qos() */
    writer = publisher->create_datawriter(
        topic, DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (writer == NULL) \{
        printf(\"create_datawriter error\\n\");
    /*    publisher_shutdown(participant); */
        return -1;
    \}

    [set s]_writer = [set s]DataWriter::narrow(writer);
    if ([set s]_writer == NULL) \{
        printf(\"DataWriter narrow error\\n\");
    /*    publisher_shutdown(participant); */
        return -1;
    \}
                                                                                
    /* Create data sample for writing */
    instance = [set s]TypeSupport::create_data();
    if (instance == NULL) \{
        printf(\"[set s]TypeSupport::create_data error\\n\");
    /*    publisher_shutdown(participant); */
        return -1;
    \}

    /* For data type that has key, if the same instance is going to be
       written multiple times, initialize the key here
       and register the keyed instance prior to writing */
    /*
    instance_handle = [set s]_writer->register_instance(*instance);
    */
     
    return 0;
\}
                                                                           
extern \"C\" int [set s]_tidyup_ndds(DDS_InstanceHandle_t instance_handle, [set s] *instance)
\{
    if (instance_handle != NULL) \{
       retcode = [set s]_writer->unregister_instance(
        *instance, instance_handle);
       if (retcode != DDS_RETCODE_OK) {
        printf(\"unregister instance error %d\\n\", retcode);
    \}

    /* Delete data sample */
    retcode = [set s]TypeSupport::delete_data(instance);
    if (retcode != DDS_RETCODE_OK) {
        printf(\"[set s]TypeSupport::delete_data error %d\\n\", retcode);
    }
                                                                                
    /* Delete all entities */
    /* return publisher_shutdown(participant); */
    return 0;
\}
"
     close $fpout
   }
   if { $sub } {
     set fsout [open $stagingdir/[set s]_subscriber.cxx w]
     puts $fsout "
#include <stdio.h>
#include <stdlib.h>
#include \"ndds/ndds_cpp.h\"
#include \"$s.h\"
#include \"[set s]Support.h\"
 
class [set s]Listener : public DDSDataReaderListener \{
  public:
    virtual void on_requested_deadline_missed(
        DDSDataReader* /*reader*/,
        const DDS_RequestedDeadlineMissedStatus& /*status*/) \{\}
     
    virtual void on_requested_incompatible_qos(
        DDSDataReader* /*reader*/,
        const DDS_RequestedIncompatibleQosStatus& /*status*/) \{\}
     
    virtual void on_sample_rejected(
        DDSDataReader* /*reader*/,
        const DDS_SampleRejectedStatus& /*status*/) \{\}
 
    virtual void on_liveliness_changed(
        DDSDataReader* /*reader*/,
        const DDS_LivelinessChangedStatus& /*status*/) \{\}
                                                                                
    virtual void on_sample_lost(
        DDSDataReader* /*reader*/,
        const DDS_SampleLostStatus& /*status*/) \{\}
                                                                                
    virtual void on_subscription_matched(
        DDSDataReader* /*reader*/,
        const DDS_SubscriptionMatchedStatus& /*status*/) \{\}
                                                                                
    virtual void on_data_available(DDSDataReader* reader);
    struct [set s] *previousInstance;
    struct [set s] *currentInstance;

\};
    
void [set s]Listener::on_data_available(DDSDataReader* reader)
{
    [set s]DataReader *[set s]_reader = NULL;
    [set s]Seq data_seq;
    DDS_SampleInfoSeq info_seq;
    DDS_ReturnCode_t retcode;
    struct [set s] *instance = NULL;

    int i;
                                                                                
    [set s]_reader = [set s]DataReader::narrow(reader);
    if ([set s]_reader == NULL) \{
        printf(\"DataReader narrow error\\n\");
        return;
    \}
                                                                                
    retcode = [set s]_reader->take(
        data_seq, info_seq, DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
                                                                                
    if (retcode == DDS_RETCODE_NO_DATA) \{
        return;
    \} else if (retcode != DDS_RETCODE_OK) \{
        printf(\"take error %d\\n\", retcode);
        return;
    \}
                                                                                
    for (i = 0; i < data_seq.length(); ++i) \{
        if (DDS_SampleInfoSeq_get_reference(&info_seq, i)->valid_data) \{
                currentInstance = [set s]Seq_get_reference(&data_seq, i);
        \}
    \}
                                                           
    retcode = [set s]_reader->return_loan(data_seq, info_seq);
    if (retcode != DDS_RETCODE_OK) \{
        printf(\"return loan error %d\\n\", retcode);
    \}
\}
   
extern \"C\" int [set s]_subscriber_ndds(int domainId)
\{
    DDSDomainParticipant *participant = NULL;
    DDSSubscriber *subscriber = NULL;
    DDSTopic *topic = NULL;
    [set s]Listener *reader_listener = NULL;
    DDSDataReader *reader = NULL;
    DDS_ReturnCode_t retcode;
    const char *type_name = NULL;
    int status = 0;
                                                                                
    /* To customize participant QoS, use
       DDSTheParticipantFactory->get_default_participant_qos() */
    participant = DDSTheParticipantFactory->create_participant(
        domainId, DDS_PARTICIPANT_QOS_DEFAULT,
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (participant == NULL) \{
        printf(\"create_participant error\\n\");
    /*    subscriber_shutdown(participant); */
        return -1;
    \}
                                                                                
    /* To customize subscriber QoS, use
       participant->get_default_subscriber_qos() */
    subscriber = participant->create_subscriber(
        DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (subscriber == NULL) \{
        printf(\"create_subscriber error\\n\");
    /*    subscriber_shutdown(participant); */
        return -1;
    \}
                                                                                
    /* Register type before creating topic */
    type_name = [set s]TypeSupport::get_type_name();
    retcode = [set s]TypeSupport::register_type(
        participant, type_name);
    if (retcode != DDS_RETCODE_OK) \{
        printf(\"register_type error %d\\n\", retcode);
    /*    subscriber_shutdown(participant); */
        return -1;
    \}
                                                                                
    /* To customize topic QoS, use
       participant->get_default_topic_qos() */
    topic = participant->create_topic(
        \"Topic [set s]\",
        type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic == NULL) \{
        printf(\"create_topic error\\n\");
    /*    subscriber_shutdown(participant); */
        return -1;
    \}
                                                                                

    /* Create data reader listener */
    reader_listener = new [set s]Listener();
    if (reader_listener ==  NULL) \{
        printf(\"listener instantiation error\\n\");
    /*    subscriber_shutdown(participant); */
        return -1;
    \}
                                                                                
    /* To customize data reader QoS, use
       subscriber->get_default_datareader_qos() */
    reader = subscriber->create_datareader(
        topic, DDS_DATAREADER_QOS_DEFAULT, reader_listener,
        DDS_STATUS_MASK_ALL);
    if (reader == NULL) \{
        printf(\"create_datareader error\\n\");
    /*    subscriber_shutdown(participant); */
        delete reader_listener;
        return -1;
    \}
                                                                                
    return 0;
\}
                                                                         
extern \"C\" int [set s]_subscriber_tidyup(DDSDomainParticipant *participant , [set s]Listener *reader_listener)
\{
    int status;

    /* Delete all entities */
    status = subscriber_shutdown(participant);
    delete reader_listener;
                                                                                
    return status;
\}


"
     close $fsout
   }
   buildsalndds
   foreach f $flist {
      exec cp $f $stagingdir/.
   }
}

unset NDDSGEN
foreach sid [array names SUBS] {
   set s [join [split $sid .] _]
   if { [info exists PUBS($s)] } {
      genndds 1 1 $s
      set NDDSGEN($s) 1
   } else {
      genndds 0 1 $s
      set NDDSGEN($s) 1
   }    
}
foreach sid [array names PUBS] { 
   set s [join [split $sid .] _]
   if { [info exists NDDSGEN($s)] == 0 } {
      genndds 1 0 $s
      set NDDSGEN($s) 1
   }
}

set NDDSCOMPILER i86Linux2.6gcc3.4.3
