

source $SAL_DIR/geneventtests.tcl 
source $SAL_DIR/geneventtestsjava.tcl 

proc geneventaliascode { subsys lang fout } {
global EVENT_ALIASES EVTS
 if { [info exists EVENT_ALIASES($subsys)] } {
  stdlog "Generate event alias support for $lang"
  if { $lang == "include" } {
     foreach i $EVENT_ALIASES($subsys) { 
      if { [info exists EVTS($subsys,$i,param)] } {
         puts $fout "
      salReturn logEvent_[set i]( SALData_logevent_[set i]C *data, int priority );      
      int getEvent_[set i]( SALData_logevent_[set i]C *data );"
      }
     }
  }
  if { $lang == "cpp" } {
     catch { set result [geneventaliascpp $subsys $fout] } bad
     stdlog "$result"
     catch { set result [geneventtestscpp $subsys] } bad
     stdlog "$result"
   }
  if { $lang == "java" }  {
     catch { set result [geneventaliasjava $subsys $fout] } bad
     stdlog "$result"
     catch { set result [geneventtestsjava $subsys] } bad
     stdlog "$result"
  }
  if { $lang == "python" } {
     catch { set result [geneventaliaspython $subsys $fout] } bad
     stdlog "$result"
  }
  if { $lang == "isocpp" } {
     catch { set result [geneventaliasisocpp $subsys $fout] } bad
     stdlog "$result"
  }
 }
}


proc geneventaliascpp { subsys fout } {
global EVENT_ALIASES EVTS SAL_WORK_DIR
   foreach i $EVENT_ALIASES($subsys) {
    if { [info exists EVTS($subsys,$i,param)] } {
      stdlog "	: alias = $i"
      puts $fout "
int SAL_SALData::getEvent_[set i](SALData_logevent_[set i]C *data)
\{
  ReturnCode_t status =  -1;
  string stopic=\"SALData_logevent_[set i]\";
  int actorIdx = SAL__SALData_logevent_[set i]_ACTOR;
  if (sal\[actorIdx\].subscriber == NULL) \{
     createSubscriber(actorIdx);
     createReader(actorIdx,false);
     sal\[actorIdx\].isEventReader = true;
  \}
  status = getSample_logevent_[set i](data);
  return status;
\}
"
     puts $fout "
salReturn SAL_SALData::logEvent_[set i]( SALData_logevent_[set i]C *data, int priority )
\{
  int actorIdx = SAL__SALData_logevent_[set i]_ACTOR;
  data->priority=priority;
  if (sal\[actorIdx\].publisher == NULL) \{
     createPublisher(actorIdx);
     bool autodispose_unregistered_instances = false;
     createWriter(actorIdx,autodispose_unregistered_instances);
     sal\[actorIdx\].isEventWriter = true;
  \}
  status = putSample_logevent_[set i](data);
  return status;
\}
"
    } else {
      stdlog "Alias $i has no parameters - uses standard [set subsys]_logevent"
    }
   }
}


proc geneventaliasjava { subsys fout } {
global EVENT_ALIASES EVTS
   foreach i $EVENT_ALIASES($subsys) {
    if { [info exists EVTS($subsys,$i,param)] } {
      stdlog "	: alias = $i"
      puts $fout "
	public int getEvent_[set i](SALData.logevent_[set i] anEvent)
	\{
	  int status =  -1;
          int actorIdx = SAL__SALData_logevent_[set i]_ACTOR;
          if (sal\[actorIdx\].subscriber == null) \{
             createSubscriber(actorIdx);
             createReader(actorIdx,false);
             sal\[actorIdx\].isEventReader = true;
          \}
          status = getSample_logevent_[set i](data);
	  return status;
	\}

	public int logEvent_[set i]( SALData.logevent_[set i] event, int priority )
	\{
	   int status = 0;
           int actorIdx = SAL__SALData_logevent_[set i]_ACTOR;
           data.priority=priority;
           if (sal\[actorIdx\].publisher == null) \{
              createPublisher(actorIdx);
              boolean autodispose_unregistered_instances = false;
              createWriter(actorIdx,autodispose_unregistered_instances);
              sal\[actorIdx\].isEventWriter = true;
           \}
           status = putSample_logevent_[set i](data);
           return status;
	\}
"
    } else {
      stdlog "Alias $i has no parameters - uses standard [set subsys]_logevent"
    }
   }
}



proc geneventaliaspython { subsys fout } {
global EVENT_ALIASES EVTS
   foreach i $EVENT_ALIASES($subsys) {
    if { [info exists EVTS($subsys,$i,param)] } {
      stdlog "	: alias = $i"
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
    } else {
      stdlog "Alias $i has no parameters - uses standard [set subsys]_logevent"
    }
   }
}



proc geneventaliasisocpp { subsys fout } {
global EVENT_ALIASES
   foreach i $EVENT_ALIASES { 
    if { [info exists EVTS($subsys,$i,param)] } {
      stdlog "	: alias = $i"
    } else {
      stdlog "Alias $i has no parameters - uses standard [set subsys]_command"
    }
   }
}




