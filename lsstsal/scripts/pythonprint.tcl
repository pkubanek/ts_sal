
proc pythonprinter { fout topic } {
global TLMS TLM_ALIASES CMDS CMD_ALIASES EVTS EVENT_ALIASES
  set base [split $topic _]
  set subsys [lindex $base 0]
  set alias [join [lrange $base 1 end] _]
  if { $alias != "ackcmd" } {
    if { [lindex $base 1] == "command" } {
      set items $CMDS($subsys,$alias,param)
    } else {
      if { [lindex $base 1] == "logevent" } {
        set items $EVTS($subsys,$alias,param)
      } else {
        set items $TLMS($subsys,$alias,param)
      }
    }
    foreach item $items {
      set id [lindex $item end]
      if { [llength [split $item "\[\]"]] > 1 } {
        puts $fout "    print myData.$id\[0\]"
      } else {
        puts $fout "    print myData.$id"
      }
    }
  }
}

