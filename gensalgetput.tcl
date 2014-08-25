#!/usr/bin/tclsh
#
# Generate SALDDS methods for getSample and putSample for all types
# and generate salTypeSupport routine
#



proc addSALDDStypes { idlfile id lang base } {
global SAL_DIR
 set atypes $idlfile
 if { $lang == "java" } {
  set fin [open $SAL_DIR/code/templates/SALDDS.java.template r]
  set fout [open [set id]/java/src/org/lsst/sal/SALDDS.java w]
  puts stdout "Configuring [set id]/java/src/org/lsst/sal/SALDDS.java"
  while { [gets $fin rec] > -1 } {
     if { [string range $rec 0 20] == "// INSERT SAL IMPORTS" } {
        puts $fout "import [set base].*;"
     }
     if { [string range $rec 0 21] == "// INSERT TYPE SUPPORT" } {
        puts $fout "        public void salTypeSupport(String topicName) \{
		String\[\] parts = topicName.split(\"_\");"
        foreach i $atypes {
           set base [lindex [exec grep module $i] 1]
           puts $fout "                if (\"[set base]\".equals(parts\[0\]) ) \{"
           set ptypes [split [exec grep pragma $i] \n]
           foreach j $ptypes {
               set name [lindex $j 2]
               puts stdout "	for $base $name"
               puts $fout "
                    if ( \"[set base]_$name\".equals(topicName) ) \{
			[set name]TypeSupport [set name]TS = new [set name]TypeSupport();
			registerType([set name]TS);
		    \}"
           }
           puts $fout "	 \}"
        }
        puts $fout "\}"
        foreach i $atypes {
           set base [lindex [exec grep module $i] 1]
           set ptypes [split [exec grep pragma $i] \n]
           foreach j $ptypes {
               set name [lindex $j 2]
puts $fout "
	public int putSample($name data)
	\{
          int status = SAL__OK;
	  DataWriter dwriter = getWriter();
	  [set name]DataWriter SALWriter = [set name]DataWriterHelper.narrow(dwriter);
	  data.private_revCode = \"LSST TEST REVCODE\";
	  if (debugLevel > 0) \{
	    System.out.println(\"=== \[putSample $name\] writing a message containing :\");
	    System.out.println(\"    revCode  : \" + data.private_revCode);
	  \}
	  SALWriter.register_instance(data);
	  status = SALWriter.write(data, HANDLE_NIL.value);
	  checkStatus(status, \"[set name]DataWriter.write\");
	  return status;
	\}


	public int getSample($name data)
	\{
	  int status =  -1;
          int last = 0;
          [set name]SeqHolder SALInstance = new [set name]SeqHolder();
	  DataReader dreader = getReader();
	  [set name]DataReader SALReader = [set name]DataReaderHelper.narrow(dreader);
  	  SampleInfoSeqHolder infoSeq = new SampleInfoSeqHolder();
	  SALReader.take(SALInstance, infoSeq, LENGTH_UNLIMITED.value,
					ANY_SAMPLE_STATE.value, ANY_VIEW_STATE.value,
					ANY_INSTANCE_STATE.value);
	  if (debugLevel > 0) \{
		for (int i = 0; i < SALInstance.value.length; i++) \{
				System.out.println(\"=== \[getSample $name \] message received :\");
				System.out.println(\"    revCode  : \"
						+ SALInstance.value\[i\].private_revCode);
                   last = i;
		\}
	  \}
          if (last > 0) \{
            data = SALInstance.value\[last\];
          \}
          status = SALReader.return_loan (SALInstance, infoSeq);
	  return last;
	\}"

           }
        }
     } else {
        puts $fout $rec
     }

  }
  close $fin 
  close $fout
 }
 if { $lang == "cpp" } {
  set finh [open $SAL_DIR/code/templates/SALDDS.h.template r]
  set fouth [open [set base]/cpp/src/SALDDS.h w]
  set rec ""
  while { [string range $rec 0 21] != "// INSERT TYPE SUPPORT" } {
     if { [string range $rec 0 22] == "// INSERT TYPE INCLUDES" } {
       puts $fouth "  #include \"ccpp_sal_[lindex [split $id _] 0].h\""
       gets $finh rec ; puts $fouth $rec
     } else {
       gets $finh rec
       puts $fouth $rec
     }
  }
  set fin [open $SAL_DIR/code/templates/SALDDS.cpp.template r]
  puts stdout "Configuring [set id]/cpp/src/SALDDS.cpp"
  set fout [open [set base]/cpp/src/SALDDS.cpp w]
  while { [gets $fin rec] > -1 } {
     if { [string range $rec 0 21] == "// INSERT TYPE SUPPORT" } {
        puts $fout " void SALDDS::salTypeSupport(char *topicName) 
\{"
        foreach i $atypes {
           set base [lindex [exec grep module $i] 1]
           puts $fout "    if (strncmp(\"$base\",topicName,[string length $base]) == 0) \{"
           set ptypes [split [exec grep pragma $i] \n]
           foreach j $ptypes {
               set name [lindex $j 2]
               puts stdout "	for $base $name"
               puts $fout "
       if ( strcmp(\"[set base]_[set name]\",topicName) == 0) \{
	  [set base]::[set name]TypeSupport_var mt = new [set base]::[set name]TypeSupport();
	  registerType(mt.in());
       \}"
           }
           puts $fout "  \}"
        }
        puts $fout "\}"
        foreach i $atypes {
           set base [lindex [exec grep module $i] 1]
           set ptypes [split [exec grep pragma $i] \n]
           foreach j $ptypes {
              set name [lindex $j 2]        
puts $fout "
salReturn SALDDS::putSample([set base]::[set name] data)
\{
  DataWriter_var dwriter = getWriter();
  [set base]::[set name]DataWriter_var SALWriter = [set base]::[set name]DataWriter::_narrow(dwriter.in());
  data.private_revCode = DDS::string_dup(\"LSST TEST REVCODE\");
  if (debugLevel > 0) \{
    cout << \"=== \[putSample\] [set base]::[set name] writing a message containing :\" << endl;
    cout << \"    revCode  : \" << data.private_revCode << endl;
  \}
  ReturnCode_t status = SALWriter->write(data, DDS::HANDLE_NIL);
  checkStatus(status, \"[set base]::[set name]DDataWriter::write\");  
  return status;
\}

salReturn SALDDS::getSample([set base]::[set name]Seq data)
\{
  SampleInfoSeq infoSeq;
  ReturnCode_t status =  - 1;
  DataReader_var dreader = getReader();
  [set base]::[set name]DataReader_var SALReader = [set base]::[set name]DataReader::_narrow(dreader.in());
  checkHandle(SALReader.in(), \"[set base]::[set name]DataReader::_narrow\");
  status = SALReader->take(data, infoSeq, LENGTH_UNLIMITED, ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
  checkStatus(status, \"[set base]::[set name]DataReader::take\");
  for (DDS::ULong j = 0; j < data.length(); j++)
  \{
    cout << \"=== \[GetSample\] message received :\" << endl;
    cout << \"    revCode  : \" << data\[j\].private_revCode << endl;
  \}
  status = SALReader->return_loan(data, infoSeq);
  checkStatus(status, \"[set base]::[set name]DataReader::return_loan\");
  return status;
\}"
               puts $fouth "
      salReturn putSample([set base]::[set name] data);
      salReturn getSample([set base]::[set name]Seq data);
"

           }
        }
     } else {
        if { $rec == "using namespace SALData;" } {
          puts $fout "using namespace [set base];"
        } else {
          puts $fout $rec
        }
     }
  }
  close $fin 
  close $fout
  while { [gets $finh rec] > -1 } {puts $fouth $rec}
  close $finh
  close $fouth
 }
}


