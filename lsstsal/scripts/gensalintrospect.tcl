#!/usr/bin/env tclsh

proc generatetypelists { subsys {fout stdout} } {
global env
  set idlfile $env(SAL_WORK_DIR)/idl-templates/validated/sal/sal_[set subsys].idl
  set ptypes [lsort [split [exec grep pragma $idlfile] \n]]
  foreach t $ptypes {
     set id [lindex $t 2]
     if { $id != "command" && $id != "logevent" && $id != "ackcmd" } {
      if { [lindex [split $id _] 0] == "command" } {
        lappend cmds [join [lrange [split $id _] 1 end] _]
      } else {
       if { [lindex [split $id _] 0] == "logevent" } {
          lappend evts [join [lrange [split $id _] 1 end] _]
       } else {
          lappend tlms $id
       }
     }
   }
  }
  if { [info exists cmds] } {
  puts $fout "
std::vector<std::string> SAL_[set subsys]::getCommandNames()
\{
    std::vector<std::string> it;"
  foreach i $cmds {
     puts $fout "    it.push_back(\"$i\");"
  }
  puts $fout "    return it;
\}
"
  }
  if { [info exists evts] } {
  puts $fout "
std::vector<std::string> SAL_[set subsys]::getEventNames()
\{
    std::vector<std::string> it;"
  foreach i $evts {
     puts $fout "    it.push_back(\"$i\");"
  }
  puts $fout "    return it;
\}
"
  }
  if { [info exists tlms] } {
  puts $fout "
std::vector<std::string> SAL_[set subsys]::getTelemetryNames()
\{
    std::vector<std::string> it;"
  foreach i $tlms {
     puts $fout "    it.push_back(\"$i\");"
  }
  puts $fout "    return it;
\}
"
  }
}


