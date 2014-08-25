#!/usr/bin/tclsh
#
# Generate SALDDS methods for getSample and putSample for all types
# and generate salTypeSupport routine
#  

proc insertcfragments { fout base name } {
global SAL_WORK_DIR
   if { $name == "command" || $name == "ackcmd" || $name == "logevent" } {return}
   puts $fout "
salReturn SAL_[set base]::putSample[set name]([set base]_[set name]C *data)
\{
  DataWriter_var dwriter = getWriter();
  [set base]::[set name]DataWriter_var SALWriter = [set base]::[set name]DataWriter::_narrow(dwriter
.in());
  [set base]::[set name] Instance;
  long iseq;

  Instance.private_revCode = DDS::string_dup(\"LSST TEST REVCODE\");
  Instance.private_sndStamp = 1;
  Instance.private_origin = 1;
  Instance.private_seqNum = sndSeqNum;
  Instance.private_host = 1;
   "
  set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]Cput.tmp r]
  while { [gets $frag rec] > -1} {puts $fout $rec}
  close $frag
  puts $fout "

  sndSeqNum++;
  if (debugLevel > 0) \{
    cout << \"=== \[putSample\] [set base]::[set name] writing a message containing :\" << endl;
    cout << \"    revCode  : \" << Instance.private_revCode << endl;
  \}
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
   Instance.[set base]ID = subsystemID;
   InstanceHandle_t dataHandle = SALWriter->register_instance(Instance);
#else
   InstanceHandle_t dataHandle = DDS::HANDLE_NIL;
#endif
  ReturnCode_t status = SALWriter->write(Instance, dataHandle);
  checkStatus(status, \"[set base]::[set name]DataWriter::write\");  
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
          SALWriter->unregister_instance(Instance, dataHandle);
#endif
  return status;
\}

salReturn SAL_[set base]::getSample[set name]([set base]_[set name]C *data)
\{
  [set base]::[set name]Seq Instances;
  SampleInfoSeq infoSeq;
  ReturnCode_t status =  - 1;
  salReturn istatus = -1;
  long iseq;

  DataReader_var dreader = getReader();
  [set base]::[set name]DataReader_var SALReader = [set base]::[set name]DataReader::_narrow(dreader
.in());
  checkHandle(SALReader.in(), \"[set base]::[set name]DataReader::_narrow\");
  status = SALReader->take(Instances, infoSeq, LENGTH_UNLIMITED, ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
  checkStatus(status, \"[set base]::[set name]DataReader::take\");
  istatus = SAL__NO_UPDATES;
  for (DDS::ULong j = 0; j < Instances.length(); j++)
  \{
    if (debugLevel > 0) \{
      cout << \"=== \[GetSample\] message received :\" << endl;
      cout << \"    revCode  : \" << Instances\[j\].private_revCode << endl;
      cout << \"    sndStamp  : \" << Instances\[j\].private_sndStamp << endl;
      cout << \"    origin  : \" << Instances\[j\].private_origin << endl;
      cout << \"    host  : \" << Instances\[j\].private_host << endl;
    \}

"
  set frag [open $SAL_WORK_DIR/include/SAL_[set base]_[set name]Cget.tmp r]
  while { [gets $frag rec] > -1} {puts $fout $rec}
  close $frag
  puts $fout "

    istatus = SAL__OK;
  \}
  status = SALReader->return_loan(Instances, infoSeq);
  checkStatus(status, \"[set base]::[set name]DataReader::return_loan\");
  return istatus;
\}

"
}

proc testifdef { } {
global SYSDIC
  set SYSDIC(hexapod,keyedID) 1
  set fin [open SALDDS.java.template r]
  set fout [open SALDDS.java.ifdefd w]
  while { [gets $fin rec] > -1 } {
     if { [string range $rec 0 31] == "#ifdef SAL_SUBSYSTEM_ID_IS_KEYED" } {
         processifdefregion $fin $fout hexapod
     } else {
         puts $fout $rec
     }
  }
  close $fin
  close $fout
}


proc processifdefregion { fin fout base } {
global SYSDIC
   if { [info exists SYSDIC($base,keyedID)] } { 
      gets $fin rec
      while { $rec != "#endif" && $rec != "#else" } {
           puts $fout $rec
           gets $fin rec
      }          
      while { $rec != "#endif" } {gets $fin rec}
   } else {
      gets $fin rec
      while { $rec != "#endif" && $rec != "#else" } {gets $fin rec}
      while { $rec != "#endif" } {
          gets $fin rec
          if { $rec != "#endif" } {puts $fout rec}
      }
   }
}



proc addSALDDStypes { idlfile id lang base } {
global SAL_DIR SYSDIC
 set atypes $idlfile
 if { $lang == "java" } {
  set fin [open $SAL_DIR/code/templates/SALDDS.java.template r]
  set fout [open [set id]/java/src/org/lsst/sal/SAL_[set base].java w]
  puts stdout "Configuring [set id]/java/src/org/lsst/sal/SAL_[set base].java"
  while { [gets $fin rec] > -1 } {
     if { [string range $rec 0 20] == "// INSERT SAL IMPORTS" } {
        puts $fout "import [set base].*;"
     }
     if { [string range $rec 0 31] == "#ifdef SAL_SUBSYSTEM_ID_IS_KEYED" } {
         processifdefregion $fin $fout $base
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
	  \}"
        if { [info exists SYSDIC($base,keyedID)] } { 
          puts $fout "
           data.[set base]ID = subsystemID;
           long dataHandle = SALWriter.register_instance(data);
	   SALWriter.register_instance(data);
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, \"[set name]DataWriter.write\");
           SALWriter.dispose(data, dataHandle);
           SALWriter.unregister_instance(data, dataHandle);"
        } else { 
          puts $fout "
           long dataHandle = DDS.HANDLE.NIL;
	   status = SALWriter.write(data, dataHandle);
	   checkStatus(status, \"[set name]DataWriter.write\");"
        }
        puts $fout "
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
        if { [string range $rec 0 5] != "#ifdef" } {
          puts $fout $rec
        }
     }

  }
  close $fin 
  close $fout
  exec cp [set id]/java/src/org/lsst/sal/SAL_[set base].java [set base]/java/src/org/lsst/sal/.
 }
 if { $lang == "cpp" } {
  set finh [open $SAL_DIR/code/templates/SALDDS.h.template r]
  set fouth [open [set base]/cpp/src/SAL_[set base].h w]
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
  puts stdout "Configuring [set id]/cpp/src/SAL_[set base].cpp"
  set fout [open [set base]/cpp/src/SAL_[set base].cpp w]
  while { [gets $fin rec] > -1 } {
     if { [string range $rec 0 21] == "// INSERT TYPE SUPPORT" } {
        puts $fout " void SAL_[set base]::salTypeSupport(char *topicName) 
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
salReturn SAL_[set base]::putSample([set base]::[set name] data)
\{
  DataWriter_var dwriter = getWriter();
  [set base]::[set name]DataWriter_var SALWriter = [set base]::[set name]DataWriter::_narrow(dwriter.in());
  data.private_revCode = DDS::string_dup(\"LSST TEST REVCODE\");
  if (debugLevel > 0) \{
    cout << \"=== \[putSample\] [set base]::[set name] writing a message containing :\" << endl;
    cout << \"    revCode  : \" << data.private_revCode << endl;
  \}
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
   data.[set base]ID = subsystemID;
   InstanceHandle_t dataHandle = SALWriter->register_instance(data);
#else
   InstanceHandle_t dataHandle = DDS::HANDLE_NIL;
#endif
  ReturnCode_t status = SALWriter->write(data, dataHandle);
  checkStatus(status, \"[set base]::[set name]DataWriter::write\");  
#ifdef SAL_SUBSYSTEM_ID_IS_KEYED
          SALWriter->unregister_instance(data, dataHandle);
#endif
  return status;
\}

salReturn SAL_[set base]::getSample([set base]::[set name]Seq data)
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
      salReturn putSample[set name]([set base]_[set name]C *data);
      salReturn getSample[set name]([set base]_[set name]C *data);
"
               insertcfragments $fout $base $name
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

proc modpubsubexamples { id } {
global SAL_DIR SAL_WORK_DIR
  set fin [open $SAL_DIR/code/templates/SALDataPublisher.cpp.template r]
  set fout [open $SAL_WORK_DIR/[set id]/cpp/src/[set id]DataPublisher.cpp w]
  while { [gets $fin rec] > -1 } {
      puts $fout $rec
      if { [string range $rec 0 17] == "// INSERT_SAL_PUBC" } {
         set frag [open $SAL_WORK_DIR/include/SAL_[set id]Cpub.tmp r]
         while { [gets $frag r2] > -1 } {puts $fout $r2}
         close $frag         
      }
  }
  close $fin
  close $fout
  set fin [open $SAL_DIR/code/templates/SALDataSubscriber.cpp.template r]
  set fout [open $SAL_WORK_DIR/[set id]/cpp/src/[set id]DataSubscriber.cpp w]
  while { [gets $fin rec] > -1 } {
      puts $fout $rec
      if { [string range $rec 0 17] == "// INSERT_SAL_SUBC" } {
         set frag [open $SAL_WORK_DIR/include/SAL_[set id]Csub.tmp r]
         while { [gets $frag r2] > -1 } {puts $fout $r2}
         close $frag         
      }
  }
  close $fin
  close $fout
}




