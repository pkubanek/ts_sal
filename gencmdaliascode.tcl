
source $SAL_DIR/gencommandtests.tcl 

proc gencmdaliascode { subsys lang fout } {
global CMD_ALIASES
  stdlog "Generate command alias support for $lang"
  if { $lang == "include" } {
     foreach i $CMD_ALIASES($subsys) { 
       puts $fout "
      int issueCommand_[set i]( SALData_command_[set i]C *data);
      int acceptCommand_[set i]( SALData_command_[set i]C *data);
      salReturn waitForCompletion_[set i]( int cmdSeqNum , unsigned int timeout );
      salReturn ackCommand_[set i]( int cmdSeqNum, salLONG  ack, salLONG error, char *result );
      salReturn getResponse_[set i](SALData::ackcmdSeq data);"
     }
  }
  if { $lang == "cpp" } {
     catch { set result [gencmdaliascpp $subsys $fout] } bad
     stdlog "$result"
     catch { set result [gencommandtestscpp $subsys] } bad
     stdlog "$result"
  }
  if { $lang == "java" }  {
     catch { set result [gencmdaliasjava $subsys $fout] } bad
     stdlog "$result"
  }
  if { $lang == "python" } {
     catch { set result [gencmdaliaspython $subsys $fout] } bad
     stdlog "$result"
  }
  if { $lang == "isocpp" } {
     catch { set result [gencmdaliasisocpp $subsys $fout] } bad
     stdlog "$result"
  }
}


proc gencmdaliascpp { subsys fout } {
global CMD_ALIASES SAL_WORK_DIR
   foreach i $CMD_ALIASES($subsys) {
      stdlog "	: command alias = $i"
      puts $fout "
int SAL_SALData::issueCommand_[set i]( SALData_command_[set i]C *data )
\{
  
  InstanceHandle_t cmdHandle = DDS::HANDLE_NIL;
  time_t sTime;
  SALData::command_[set i] Instance;
  int actorIdx = SAL__SALData_command_[set i]_ACTOR;
  // create DataWriter :
  if (sal\[actorIdx\].isCommand == false) \{
     salCommand(sal\[actorIdx\].topicName);
     sal\[actorIdx\].isCommand = true;
     sal\[actorIdx\].sndSeqNum = time(&sTime);
  \}
  DataWriter_var dwriter = getWriter(actorIdx);
  SALCommand_[set i]DataWriter_var SALWriter = SALCommand_[set i]DataWriter::_narrow(dwriter.in());

#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
  Instance.SALDataID = subsystemID;
  cmdHandle = SALWriter->register_instance(Instance);
#endif

  Instance.private_revCode =  DDS::string_dup(\"LSST TEST REVCODE\");
  Instance.private_sndStamp = 1;
  Instance.private_origin =   1;
  Instance.private_seqNum =   sal\[actorIdx\].sndSeqNum;
  Instance.private_host =     1;"
        set fin [open $SAL_WORK_DIR/include/SAL_[set subsys]_command_[set i]Cput.tmp r]
        while { [gets $fin rec] > -1 } {
           puts $fout $rec
        }
        close $fin
        puts $fout "
  if (debugLevel > 0) \{
    cout << \"=== \[issueCommandC $i\] writing a command containing :\" << endl;"
        set fin [open $SAL_WORK_DIR/include/SAL_[set subsys]_command_[set i]Cout.tmp r]
        while { [gets $fin rec] > -1 } {
           puts $fout $rec
        }
        close $fin
        puts $fout "
  \}
  ReturnCode_t status = SALWriter->write(Instance, cmdHandle);
  sal\[actorIdx\].sndSeqNum++;
  checkStatus(status, \"SALCommand_[set i]DataWriter::write\");  
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
    SALWriter->unregister_instance(Instance, cmdHandle);
#endif
  if (status != SAL__OK) \{
      if (debugLevel >= SAL__LOG_ROUTINES) \{
          logError(status);
      \}
  \}
  return (sal\[actorIdx\].sndSeqNum-1);
\}
"
      puts $fout "
int SAL_SALData::acceptCommand_[set i]( SALData_command_[set i]C *data )
\{
   SampleInfoSeq info;
   ReturnCode_t status = 0;
   ReturnCode_t istatus =  -1;
   SALData::command_[set i]Seq Instances;
   SALData::ackcmd ackdata;
   InstanceHandle_t ackHandle = DDS::HANDLE_NIL;
   int actorIdx = SAL__SALData_command_[set i]_ACTOR;
   int j=0;

  // create DataWriter :
  if (sal\[actorIdx\].isProcessor == false) \{
     salProcessor(sal\[actorIdx\].topicName);
     sal\[actorIdx\].isProcessor = true;
  \}
  DataWriter_var dwriter = getWriter2(actorIdx);
  SALData::ackcmdDataWriter_var SALWriter = SALData::ackcmdDataWriter::_narrow(dwriter.in());
  DataReader_var dreader = getReader(actorIdx);
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
    ackdata.ack = SAL__CMD_ACK;"
        set fin [open $SAL_WORK_DIR/include/SAL_[set subsys]_command_[set i]Cget.tmp r]
        while { [gets $fin rec] > -1 } {
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
   puts $fout "
salReturn SAL_SALData::waitForCompletion_[set i]( int cmdSeqNum , unsigned int timeout )
\{
   salReturn status = SAL__OK;
   int countdown = timeout;
   SALData::ackcmdSeq response;
   int actorIdx = SAL__SALData_command_[set i]_ACTOR;

   while (status != SAL__CMD_COMPLETE && countdown != 0) \{
      status = getResponse_[set i](response);
      if (status != SAL__CMD_NOACK) \{
        if (sal\[actorIdx\].rcvSeqNum != sal\[actorIdx\].cmdSeqNum) \{ 
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
         cout << \"=== \[waitForCompletion\] command \" << sal\[actorIdx\].cmdSeqNum <<  \" timed out :\" << endl;
      \} 
   \} else \{
      if (debugLevel > 0) \{
         cout << \"=== \[waitForCompletion\] command \" << sal\[actorIdx\].cmdSeqNum << \" completed ok :\" << endl;
      \} 
   \}
   return status;
\}
"
   puts $fout "
salReturn SAL_SALData::getResponse_[set i](SALData::ackcmdSeq data)
\{
  int actorIdx = SAL__SALData_command_[set i]_ACTOR;
  SampleInfoSeq info;
  ReturnCode_t status =  - 1;
  ReturnCode_t istatus =  - 1;
  DataReader_var dreader = getReader2(actorIdx);
  SALData::ackcmdDataReader_var SALReader = SALData::ackcmdDataReader::_narrow(dreader.in());
  checkHandle(SALReader.in(), \"SALData::ackcmdDataReader::_narrow\");
  istatus = SALReader->take(data, info, LENGTH_UNLIMITED,ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
  sal\[actorIdx\].rcvSeqNum = 0;
  sal\[actorIdx\].rcvOrigin = 0;
  checkStatus(istatus, \"SALData::ackcmdDataReader::take\");
  if (info.length() > 0) \{
    if (debugLevel > 0) \{
      cout << \"=== \[getResponse\] reading a message containing :\" << endl;
      cout << \"    revCode  : \" << data\[0\].private_seqNum << endl;
      cout << \"    error    : \" << data\[0\].error << endl;
      cout << \"    ack      : \" << data\[0\].ack << endl;
      cout << \"    result   : \" << data\[0\].result << endl;
    \}
    status = data\[0\].ack;
    sal\[actorIdx\].rcvSeqNum = data\[0\].private_seqNum;
    sal\[actorIdx\].rcvOrigin = data\[0\].private_origin;
    istatus = SALReader->return_loan(data, info);
    checkStatus(istatus, \"SALData::ackcmdDataReader::return_loan\");
  \} else \{
      cout << \"=== \[getResponse\] No ack yet!\" << endl;
      status = SAL__CMD_NOACK;
  \}
  return status;
\}
"
   puts $fout "
salReturn SAL_SALData::ackCommand_[set i]( int cmdId, salLONG ack, salLONG error, char *result )
\{
   ReturnCode_t istatus = -1;
   InstanceHandle_t ackHandle = DDS::HANDLE_NIL;
   int actorIdx = SAL__SALData_command_[set i]_ACTOR;

   SALData::ackcmd ackdata;
   DataWriter_var dwriter = getWriter2(actorIdx);
   SALData::ackcmdDataWriter_var SALWriter = SALData::ackcmdDataWriter::_narrow(dwriter.in());

   ackdata.private_origin = sal\[actorIdx\].rcvOrigin;
   ackdata.private_seqNum = sal\[actorIdx\].rcvSeqNum;
   ackdata.error = error;
   ackdata.ack = ack;
   ackdata.result = DDS::string_dup(result);
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
   ackdata.SALDataID = subsystemID;
#endif
   if (debugLevel > 0) \{
      cout << \"=== \[ackCommand\] acknowledging a command with :\" << endl;
      cout << \"    seqNum   : \" << ackdata.private_seqNum << endl;
      cout << \"    ack      : \" << ackdata.ack << endl;
      cout << \"    error    : \" << ackdata.error << endl;
      cout << \"    result   : \" << ackdata.result << endl;
   \}
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
   ackHandle = SALWriter->register_instance(ackdata);
   ackdata.SALDataID = subsystemID;
#endif
   istatus = SALWriter->write(ackdata, ackHandle);
   checkStatus(istatus, \"SALData::ackcmdDataWriter::return_loan\");
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
    SALWriter->unregister_instance(ackdata, ackHandle);
#endif
   return SAL__OK;
\}
"
   }
}



proc gencmdaliasjava { subsys fout } {
global CMD_ALIASES CMDS
   foreach i $CMD_ALIASES($subsys) {
      stdlog "	: alias = $i"
      puts $fout "
	public int issueCommand_[set i]( command_[set i] data )
	\{
  	  long cmdHandle = HANDLE_NIL.value;
          int status;
          int actorIdx = SAL__SALData_command_[set i]_ACTOR;
	  if (sal\[actorIdx\].isCommand == false) \{
	     salCommand(sal\[actorIdx\].topicName);
	     sal\[actorIdx\].isCommand = true;
	     sal\[actorIdx\].sndSeqNum = 1;
	  \}
	  DataWriter dwriter = getWriter(actorIdx);	
	  command_[set i]DataWriter SALWriter = command_[set i]DataWriterHelper.narrow(dwriter);
	  data.private_revCode = \"LSST TEST COMMAND\";
	  data.private_seqNum = sal\[actorIdx\].sndSeqNum;
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
	  data.SALDataID = subsystemID;
	  cmdHandle = SALWriter.register_instance(data);
#else
	  SALWriter.register_instance(data);
#endif
	  if (debugLevel > 0) \{
	    System.out.println( \"=== \[issueCommand\] $i writing a command containing :\");
	    System.out.println( data.device + \".\" + data.property + \".\" + data.action + \" : \" + data.value);
	  \}
	  status = SALWriter.write(data, cmdHandle);
	  sal\[actorIdx\].sndSeqNum++;
	  return (sal\[actorIdx\].sndSeqNum-1);
	\}
"
      puts $fout "
	public int acceptCommand_[set i]( SALData.command_[set i] data )
	\{
                command_[set i]SeqHolder aCmd = new command_[set i]SeqHolder();
   		SampleInfoSeqHolder info;
   		int status = 0;
   		int istatus =  -1;
   		SALData.ackcmd ackdata;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__SALData_command_[set i]_ACTOR;

  		// create DataWriter :
  		if (sal\[actorIdx\].isProcessor == false) \{
     			salProcessor(sal\[actorIdx\].topicName);
     			sal\[actorIdx\].isProcessor = true;
  		\}
  		DataWriter dwriter = getWriter2(actorIdx);
  		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
  		DataReader dreader = getReader(actorIdx);
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
	       \} else \{
	          status = 0;
	       \}
             \}
	     return status;
	\}
"
   puts $fout "
	public int waitForCompletion_[set i]( int cmdSeqNum , int timeout )
	\{
	   int status = 0;
	   int countdown = timeout;
           int actorIdx = SAL__SALData_command_[set i]_ACTOR;
	   ackcmdSeqHolder ackcmd = new ackcmdSeqHolder();

	   while (status != SAL__CMD_COMPLETE && countdown != 0) \{
	      status = getResponse_[set i](ackcmd);
	      if (status != SAL__CMD_NOACK) \{
	        if (sal\[actorIdx\].rcvSeqNum != sal\[actorIdx\].cmdSeqNum) \{ 
	           status = SAL__CMD_NOACK;
	        \}
	      \}
	      try
		\{
	 	  Thread.sleep(100*timeout);
		\}
		catch(InterruptedException ie)
		\{
			// nothing to do
	      \}
	      System.out.println( \"=== \[waitForCompletion\] command \" + sal\[actorIdx\].cmdSeqNum +  \" countdown = \" + countdown);
	      countdown--;
	   \}
	   if (status != SAL__CMD_COMPLETE) \{
	      if (debugLevel > 0) \{
	         System.out.println( \"=== \[waitForCompletion\] command " + sal\[actorIdx\].cmdSeqNum +  \" timed out\");
	      \} 
	      logError(status);
	   \} else \{
	      if (debugLevel > 0) \{
	         System.out.println( \"=== \[waitForCompletion\] command \" + sal\[actorIdx\].cmdSeqNum +  \" completed ok\");
	      \} 
           \}
 	   return status;
	\}
"
   puts $fout "
	public int getResponse_[set i](ackcmdSeqHolder data)
	\{
	  int status =  -1;
          int lastsample = 0;
          int actorIdx = SAL__SALData_command_[set i]_ACTOR;

	  DataReader dreader = getReader2(actorIdx);
	  ackcmdDataReader SALReader = ackcmdDataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, LENGTH_UNLIMITED.value,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (data.value.length > 0) \{
 		for (int i = 0; i < data.value.length; i++) \{
                     if ( debugLevel > 0) \{
				System.out.println(\"=== \[getResponse\] message received :\");
				System.out.println(\"    revCode  : \"
						+ data.value[i].private_revCode);
		    \}
                    lastsample = i;
		\}
	 	status = data.value[lastsample].ack;
	  	sal\[actorIdx\].rcvSeqNum = data.value\[lastsample\].private_seqNum;
	  	sal\[actorIdx\].rcvOrigin = data.value\[lastsample\].private_origin;
	  \} else \{
	        System.out.println(\"=== \[getResponse\] No ack yet!\"); 
	        status = SAL__CMD_NOACK;
	  \}
    	  SALReader.return_loan(data, infoSeq);
	  return status;
	\}
"
   puts $fout "
	public int ackCommand( int cmdId, int ack, int error, String result )
	\{
   		int istatus = -1;
   		long ackHandle = HANDLE_NIL.value;
                int actorIdx = SAL__SALData_command_[set i]_ACTOR;

   		SALData.ackcmd ackdata;
   		DataWriter dwriter = getWriter2(actorIdx);
   		ackcmdDataWriter SALWriter = ackcmdDataWriterHelper.narrow(dwriter);
                ackdata = new SALData.ackcmd();
   		ackdata.private_origin = sal\[actorIdx\].rcvOrigin;
   		ackdata.private_seqNum = sal\[actorIdx\].rcvSeqNum;
   		ackdata.error = error;
   		ackdata.ack = ack;
   		ackdata.result = result;
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
   		ackdata.SALDataID = subsystemID;
#endif
   		if (debugLevel > 0) \{
      			System.out.println(  \"=== \[ackCommand\] acknowledging a command with :\" );
      			System.out.println(  \"    seqNum   : \" + ackdata.private_seqNum );
      			System.out.println(  \"    ack      : \" + ackdata.ack );
      			System.out.println(  \"    error    : \" + ackdata.error );
      			System.out.println(  \"    result   : \" + ackdata.result );
   		\}
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
   		ackdata.SALDataID = subsystemID;
   		ackHandle = SALWriter.register_instance(ackdata);
#endif
   		istatus = SALWriter.write(ackdata, ackHandle);
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
    		SALWriter.unregister_instance(ackdata, ackHandle);
#endif
   		return SAL__OK;
	\}
"
   }
}



proc gencmdaliaspython { subsys fout } {
global CMD_ALIASES
   foreach i $CMD_ALIASES($subsys) {
      stdlog "	: alias = $i"
      puts $fout "
        .def( 
            \"issueCommand_[set i]\"
            , (int ( ::SAL_SALData::* )( ::SALData_command_[set i]C ) )( &::SAL_SALData::issueCommand_[set i] )
            , ( bp::arg(\"data\") ) )    
        .def( 
            \"acceptCommand_[set i]\"
            , (int ( ::SAL_SALData::* )( ::SALData_command_[set i]C ) )( &::SAL_SALData::acceptCommand_[set i] )
            , ( bp::arg(\"data\") ) )    
        .def( 
            \"ackCommand_[set i]\"
            , (::salReturn ( ::SAL_SALData::* )( int,::salLONG,::salLONG,char * ) )( &::SAL_SALData::ackCommand_[set i] )
            , ( bp::arg(\"cmdSeqNum\"), bp::arg(\"ack\"), bp::arg(\"error\"), bp::arg(\"result\") ) )    
        .def( 
            \"waitForCompletion_[set i]\"
            , (::salReturn ( ::SAL_SALData::* )( int,int ) )( &::SAL_SALData::waitForCompletion_[set i] )
            , ( bp::arg(\"cmdSeqNum\"), bp::arg(\"timeout\") ) )
      "
   }
}



proc gencmdaliasisocpp { subsys fout } {
global CMD_ALIASES
   foreach i $CMD_ALIASES($subsys) { 
      stdlog "	: alias = $i"
   }
}







