

proc gencmdaliascode { lang fout } {
global CMDS ALIASES
  if { $lang == "include" } {
     foreach i $ALIASES { 
       puts $fout "
      int issueCommand_[set i]C( SALData_command_[set i]C *data);
      int acceptCommand_[set i]C( SALData_command_[set i]C *data);"
     }
  }
  if { $lang == "cpp" } {
     gencmdaliascpp $subsys $fout
  }
  if { $lang == "java" }  {
     gencmdaliasjava $subsys $fout
  }
  if { $lang == "python" } {
     gencmdaliaspython $subsys $fout
  }
  if { $lang == "isocpp" } {
     gencmdaliaspython $subsys $fout
  }
}


proc gencmdaliascpp { subsys fout } {
global CMD ALIASES SAL_WORK_DIR
   foreach i $ALIASES {
      puts $fout "
int SAL_SALData::issueCommand[set i]C( SALData_command_[set i]C *data )
\{

  InstanceHandle_t cmdHandle = DDS::HANDLE_NIL;
  time_t sTime;
  SALData::command_[set i] Instance;

  // create DataWriter :
  // If autodispose_unregistered_instances is set to true (default value),
  // you will have to start the subscriber before the publisher
  bool autodispose_unregistered_instances = true;
  if (!hasWriter) \{
     createWriter(autodispose_unregistered_instances);
     hasWriter = true;
     sndSeqNum = time(&sTime);
  \}
  DataWriter_var dwriter = getWriter();
  SALCommand_[set i]DataWriter_var SALWriter = SALCommand_[set i]DataWriter::_narrow(dwriter.in());

#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
  Instance.SALDataID = subsystemID;
  cmdHandle = SALWriter->register_instance(Instance);
#endif

  Instance.private_revCode =  DDS::string_dup(\"LSST TEST REVCODE\");
  Instance.private_sndStamp = 1;
  Instance.private_origin =   1;
  Instance.private_seqNum =   sndSeqNum;
  Instance.private_host =     1;
  Instance.device =           DDS::string_dup(data->device.c_str());
  Instance.property =         DDS::string_dup(data->property.c_str());
  Instance.action =           DDS::string_dup(data->action.c_str());
  Instance.value =            DDS::string_dup(data->value.c_str());"
        set fin [open $SAL_WORK_DIR/include/SAL_[set subsys]_command_[set i]put.tmp r]
        while { gets $fin rec] > -1 } {
           puts $fout $rec
        }
        close $fin
        puts $fout "
  if (debugLevel > 0) \{
    cout << \"=== \[issueCommandC $i\] writing a command containing :\" << endl;
    cout << \" \" << Instance.device << \".\" << Instance.property << \".\" << Instance.action << \" : \" << Instance.value << endl;
  \}
  ReturnCode_t status = SALWriter->write(Instance, cmdHandle);
  sndSeqNum++;
  checkStatus(status, \"SALCommand_[set i]DataWriter::write\");  
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
    SALWriter->unregister_instance(Instance, cmdHandle);
#endif
  if (status != SAL__OK) \{
      if (debugLevel >= SAL__LOG_ROUTINES) \{
          logError(status);
      \}
  \}
  return (sndSeqNum-1);
\}
"
      puts $fout "
int SAL_SALData::acceptCommand_[set i]C( SALData_command_[set i]C *data )
{
   SampleInfoSeq info;
   ReturnCode_t status = 0;
   ReturnCode_t istatus =  -1;
   SALData::command_[set i]Seq Instances;
   SALData::ackcmd ackdata;
   InstanceHandle_t ackHandle = DDS::HANDLE_NIL;
   int j=0;

  // create DataWriter :
  // If autodispose_unregistered_instances is set to true (default value),
  // you will have to start the subscriber before the publisher
  bool autodispose_unregistered_instances = false;
  if (!hasWriter) \{
     createWriter2(autodispose_unregistered_instances);
     hasWriter = true;
  \}
  DataWriter_var dwriter = getWriter2();
  SALData::ackcmdDataWriter_var SALWriter = SALData::ackcmdDataWriter::_narrow(dwriter.in());
  DataReader_var dreader = getReader();
  SALData::command_[set i]DataReader_var SALReader = SALData::command_[set i]DataReader::_narrow(dreader.in());
  checkHandle(SALReader.in(), \"SALData::command_[set i]DataReader::_narrow\");
  istatus = SALReader->take(Instances, info, LENGTH_UNLIMITED,ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
  checkStatus(istatus, \"SALData::command_[set i]DataReader::take\");
  if (info.length() > 0) \{
   if (info\[0\].valid_data) \{
    if (debugLevel > 0) \{
      cout << \"=== \[acceptCommandC $i\] reading a command containing :\" << endl;
      cout << \"    seqNum   : \" << Instances\[0\].private_seqNum << endl;
      cout << \"    device   : \" << Instances\[0\].device << endl;
      cout << \"    property : \" << Instances\[0\].property << endl;
      cout << \"    action   : \" << Instances\[0\].action << endl;
      cout << \"    value    : \" << Instances\[0\].value << endl;
    \}
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
    ackdata.SALDataID = subsystemID;
#endif
    ackdata.private_origin = Instances\[0\].private_origin;
    ackdata.private_seqNum = Instances\[0\].private_seqNum;
    ackdata.error = 0;
    ackdata.result = DDS::string_dup(\"SAL ACK\");
    status = Instances\[0\].private_seqNum;
    rcvSeqNum = status;
    rcvOrigin = Instances\[0\].private_origin;
    ackdata.ack = SAL__CMD_ACK;

    strcpy(data->device,Instances\[0\].device);
    strcpy(data->property,Instances\[0\].property);
    strcpy(data->action,Instances\[0\].action);
    strcpy(data->value,Instances\[0\].value);"
        set fin [open $SAL_WORK_DIR/include/SAL_[set subsys]_command_[set i]get.tmp r]
        while { gets $fin rec] > -1 } {
           puts $fout $rec
        }
        close $fin
        puts $fout "
    istatus = SALReader->return_loan(Instances, info);
    checkStatus(istatus, \"SALData::command_[set i]DataReader::return_loan\");
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
    ackHandle = SALWriter->register_instance(ackdata);
    ackdata.SALDataID = subsystemID;
#endif
    istatus = SALWriter->write(ackdata, ackHandle);
    checkStatus(istatus, \"SALData::ackcmdDataWriter::write\");
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
    SALWriter->unregister_instance(ackdata, ackHandle);
#endif
   \}
  \} else \{
    status = 0;
  \}
  return status;
\}
"
   }
}



proc gencmdaliasjava { subsys fout } {
global CMD ALIASES
   foreach i $ALIASES {
      puts $fout "
	public int issueCommand_[set i]( command_[set i] data )
	\{
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
	  if (!hasWriter) \{
	     createWriter(false);
	     hasWriter = true;
	     sndSeqNum = 1;
	  \}
	  DataWriter dwriter = getWriter();	
	  command_[set i]DataWriter SALWriter = command_[set i]DataWriterHelper.narrow(dwriter);
	  data.private_revCode = \"LSST TEST COMMAND\";
	  data.private_seqNum = sndSeqNum;
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
	  data.SALDataID = subsystemID;
	  cmdHandle = SALWriter.register_instance(data);
#else
	  SALWriter.register_instance(data);
#endif
	  if (debugLevel > 0) \{
	    System.out.println( \"=== \[issueCommand\] $i writing a command containing :\");
	    System.out.println( \" \" + data.device + \".\" + data.property + \".\" + data.action + \" : \" + data.value);
	  }
	  status = SALWriter.write(data, cmdHandle);
	  sndSeqNum++;
	  return (sndSeqNum-1);
	\}
"
      puts $fout "
	public int acceptCommand_[set i]( SALData.command_[set i] data )
	\{
                command_[set i]SeqHolder aCmd = new command_[set i]SeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		SALData.ackcmd ackdata;;
   		long ackHandle = HANDLE_NIL.value;

  		// create DataWriter :
  		// If autodispose_unregistered_instances is set to true (default value),
  		// you will have to start the subscriber before the publisher
  		boolean autodispose_unregistered_instances = false;
  		if (!hasWriter) \{
     			createWriter2(autodispose_unregistered_instances);
     			hasWriter = true;
  		\}
  		DataWriter dwriter = getWriter2();
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader();
  		command_[set i]DataReader SALReader = command_[set i]DataReaderHelper.narrow(dreader);
                info = new SampleInfoSeqHolder();
  		istatus = SALReader.take(aCmd, info, LENGTH_UNLIMITED.value,ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value, ANY_INSTANCE_STATE.value);
		if (aCmd.value.length > 0) \{
   		  if (info.value\[0\].valid_data) \{
    		     if (debugLevel > 0) \{
      			System.out.println(  \"=== \[acceptCommand\] $i reading a command containing :\" );
      			System.out.println(  \"    seqNum   : \" + aCmd.value\[0\].private_seqNum );
      			System.out.println(  \"    device   : \" + aCmd.value\[0\].device);
      			System.out.println(  \"    property : \" + aCmd.value\[0\].property);
      			System.out.println(  \"    action   : \" + aCmd.value\[0\].action);
      			System.out.println(  \"    value    : \" + aCmd.value\[0\].value);
    		    \}
                    ackdata = new SALData.ackcmd();
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
	            ackdata.SALDataID = subsystemID;
#endif
		    ackdata.private_origin = aCmd.value\[0\].private_origin;
		    ackdata.private_seqNum = aCmd.value\[0\].private_seqNum;
		    ackdata.error  = 0;
		    ackdata.result = \"SAL ACK\";
                    data.device    = aCmd.value\[0\].device;
                    data.property  = aCmd.value\[0\].property;
                    data.action    = aCmd.value\[0\].action;
                    data.value     = aCmd.value\[0\].value;"
           foreach p $CMDS($subsys,$i,param) {
              puts $fout "                    data.$p = aCmd.value\[0\].$p;"
           }
           puts $fout "
		    status = aCmd.value\[0\].private_seqNum;
		    rcvSeqNum = status;
		    rcvOrigin = aCmd.value\[0\].private_origin;
		    ackdata.ack = SAL__CMD_ACK;
		    SALReader.return_loan(aCmd, info);
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
		    ackdata.SALDataID = subsystemID;
		    ackHandle = SALWriter.register_instance(ackdata);
#endif
		    istatus = SALWriter.write(ackdata, ackHandle);
           	    SALWriter.dispose(ackdata, ackHandle);
		    SALWriter.unregister_instance(ackdata, ackHandle);
		 \}
	     \} else {
	        status = 0;
	     \}
	     return status;
	\}
"
   }
}



proc gencmdaliaspython { subsys fout } {
global CMD ALIASES
   foreach i $ALIASES {
      puts $fout "
        .def( 
            \"issueCommand_[set i]\"
            , (int ( ::SAL_SALData::* )( ::SALData_command[_set i]C ) )( &::SAL_SALData::issueCommand_[set i]C )
            , ( bp::arg(\"data\") ) )    
        .def( 
            \"acceptCommand_[set i]\"
            , (::salReturn ( ::SAL_SALData::* )( ::SALData_command_[set i]C ) )( &::SAL_SALData::acceptCommand_[set i]C )
            , ( bp::arg(\"data\") ) )    
      "
   }
}



proc gencmdaliasisocpp { subsys fout } {
global CMD ALIASES
   foreach i $ALIASES { 
   }
}







