
proc pythonprinter { fout topic } {
global TLMS TLM_ALIASES CMDS CMD_ALIASES EVTS EVENT_ALIASES
  set base [split $topic _]
  set subsys [lindex $base 0]
  set alias [join [lrange $base 1 end] _]
  if { $alias != "ackcmd" } {
    if { [lindex $base 1] == "command" } {
      set items [array list CMDS($subsys,$alias,param)
    } else {
      if { [lindex $base 1] == "logevent" } {
        set items [array list EVTS($subsys,$alias,param)
      } else {
        set items [array list TLMS($subsys,$alias,param)
      }
    }
    foreach item [array list TLMS($subsys,$alias,param) {
      if { [llength [split $item "\[\]"] > 1 } {
        puts $fout "
i=0
print \"Array \"+id
for y in myData.$id
   print(i,y)
   i=i+1
"
      } else {
        puts $fout "print myData.$id"
      }
    }
  }
}
