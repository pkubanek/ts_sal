
proc geneventaliascode { lang fout } {
global EVTS ALIASES
  if { $lang == "include" } {
     foreach i $ALIASES { 
       puts $fout "
      salReturn logEventC( SALData_logeventC *data, int priority );      
      int getEventC(SALData_logeventC *data);
     }
  }
  if { $lang == "cpp" } {
     geneventaliascpp $subsys $fout
  }
  if { $lang == "java" }  {
     geneventaliasjava $subsys $fout
  }
  if { $lang == "python" } {
     geneventaliaspython $subsys $fout
  }
  if { $lang == "isocpp" } {
     geneventaliaspython $subsys $fout
  }
}


proc gencmdaliascpp { subsys fout } {
global EVTS ALIASES SAL_WORK_DIR
   foreach i $ALIASES {
      puts $fout "
int SAL_SALData::getEvent_[set i]C(SALData_logevent_[set i]C *data)
\{
  SampleInfoSeq info;
  ReturnCode_t status =  -1;
  string stopic=\"SALData_logevent_[set i]\";

  if (hasEventReader == false) \{
     salTelemetrySub(const_cast<char*>(stopic.c_str()));
     hasEventReader = true;
  \}
  SALData::logevent_[set i]Seq Instance;
  DataReader_var dreader = getReader();
  SALData::logevent_[set i]DataReader_var SALReader = SALData::logevent_[set i]DataReader::_narrow(dreader.in());
  checkHandle(SALReader.in(), \"SALData::logevent_[set i]DataReader::_narrow\");
  status = SALReader->take(Instance, info,  LENGTH_UNLIMITED,ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
  checkStatus(status, \"SALData::logevent_[set i]DataReader::take\");
  if (info.length() > 0) \{
   if (info\[0\].valid_data) \{
     if (debugLevel > 0) \{
       cout << \"=== \[getEvent\] $i reading a message containing :\" << endl;
       cout << \"    revCode  : \" << Instance\[0\].private_revCode << endl;
     \}
     strcpy(data->message,Instance\[0\].message);
     status = SALReader->return_loan(Instance, info);
     checkStatus(status, \"SALData::logevent_[set i]DataReader::return_loan\");
     status = SAL__OK;
  \ }
  \} else \{
     status = SAL__NO_UPDATES;
  \}
  return status;
\}
"
     puts $fout "
salReturn SAL_SALData::logEvent_[set i]C( SALData_logevent_[set i]C *data, int priority )
{
   ReturnCode_t status = 0;
   ReturnCode_t istatus =  -1;
   SALData::logevent_[set i] Instance;
   string stopic=\"SALData_logevent_[set i]\";
   InstanceHandle_t eventHandle = DDS::HANDLE_NIL;

  if (hasEventWriter == false) \{
    salTelemetryPub(const_cast<char*>(stopic.c_str()));
    hasEventWriter = true;
  \}
  DataWriter_var dwriter = getWriter();
  SALData::logevent_[set i]DataWriter_var SALWriter = SALData::logevent_[set i]DataWriter::_narrow(dwriter.in());
  Instance.private_revCode =  DDS::string_dup(\"LSST TEST REVCODE\");
  Instance.private_sndStamp = 1;
  Instance.private_origin =   1;
  Instance.private_seqNum =   sndSeqNum;
  Instance.private_host =     1;"
     set fin [open $SAL_WORK_DIR/include/SAL_[set subsys]_logevent_[set i]put.tmp r]
     while { gets $fin rec] > -1 } {
        puts $fout $rec
     }
     close $fin
     puts $fout "
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
   Instance.SALDataID = subsystemID;
   eventHandle = SALWriter->register_instance(Instance);
#endif
  istatus = SALWriter->write(Instance, eventHandle);
  checkStatus(istatus, \"SALData::logevent_[set i]DataWriter::write\");
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
    SALWriter->unregister_instance(Instance, eventHandle);
#endif
  return status;
\}
"
   }
}

proc gencmdaliasjava { subsys fout } {
global EVTS ALIASES
   foreach i $ALIASES {
      puts $fout "
	public int getEvent_[set i](SALData.logevent_[set i] anEvent)
	\{
	  int status =  -1;

	  if (hasEventReader == false) \{
	     salTelemetrySub(\"SALData_logevent_[set i]\");
	     hasEventReader = true;
	  \}
	  DataReader dreader = getReader();
	  logevent_[set i]DataReader SALReader = logevent_[set i]DataReaderHelper.narrow(dreader);
          logevent_[set i]SeqHolder data = new logevent_[set i]SeqHolder();
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(data, infoSeq, LENGTH_UNLIMITED.value,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
          if (data.value.length > 0) \{
  	     if (infoSeq.value\[0\].valid_data) \{
		for (int i = 0; i < data.value.length; i++) \{
		  if (debugLevel > 0) \{
				System.out.println(\"=== \[getEvent\] $i message received :\");
				System.out.println(\"    revCode  : \"
						+ data.value\[i\].private_revCode);
                  \}
		\}"
           foreach p $EVTS($subsys,$i,param) {
              puts $fout "                    anEvent.$p = data.value\[0\].$p;"
           }
           puts $fout "
                status = SAL__OK;
             \} else \{
                status = SAL__NO_UPDATES;
             \}
	  \}
          SALReader.return_loan(data,infoSeq);
	  return status;
	\}

	public int logEvent_[set i]( SALData.logevent_[set i] event, int priority )
	\{
	   int status = 0;
	   int istatus =  -1;
	   String stopic=\"SALData_logevent_[set i]\";
	   long eventHandle = HANDLE_NIL.value;

	  if (hasEventWriter == false) \{
	    salTelemetryPub(stopic);
	    hasEventWriter = true;	
  	  \}
	  DataWriter dwriter = getWriter();
	  logevent_[set i]DataWriter SALWriter = logevent_[set i]DataWriterHelper.narrow(dwriter);
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
	   event.SALDataID = subsystemID;
	   eventHandle = SALWriter.register_instance(event);	
#endif
	  status=SALWriter.write(event, eventHandle);
	  checkStatus(status, \"logEvent_[set i]DataWriter.write\");
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
 	   SALWriter.dispose(event, eventHandle);
	   SALWriter.unregister_instance(event, eventHandle);
#endif
	   return status;
	\}
"
   }
}



proc geneventaliaspython { subsys fout } {
global EVTS ALIASES
   foreach i $ALIASES {
      puts $fout "
        .def( 
            \"getEvent_[set i]\"
            , (::salReturn ( ::SAL_SALData::* )( ::SALData_logevent_[set i]C ) )( &::SAL_SALData::getEvent_[set i] )
            , ( bp::arg(\"event\") ) )    
        .def( 
            \"logEvent_[set i]\"
            , (::salReturn ( ::SAL_SALData::* )( ::SALData_logevent_[set i]C,int ) )( &::SAL_SALData::logEvent_[set i] )
            , ( bp::arg(\"event\"), bp::arg(\"priority\") ) )    
      "
   }
}



proc geneventaliasisocpp { subsys fout } {
global CMD ALIASES
   foreach i $ALIASES { 
   }
}




