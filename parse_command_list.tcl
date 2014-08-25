#!/usr/bin/tclsh

set SAL_DIR $env(SAL_DIR)
set SAL_WORK_DIR $env(SAL_WORK_DIR)
source $SAL_DIR/add_system_dictionary.tcl
source $SAL_DIR/add_private_idl.tcl


set subsys [lindex $argv 0]
set fin [open $SAL_WORK_DIR/command_list_$subsys r]

puts stdout "Parsing command list for $subsys"
while { [gets $fin rec] > -1 } {
  if { [string index $rec 0] == "#" || [string trim $rec] == "" } {
  } else {
       if { [lindex $rec 0] == "command" } {  
          set spl   [split $rec "|"]
          set cmd [string trim [join [split [lrange [lindex $spl 0] 1 end] " "] " "]]
          set alias [string trim [lindex $spl 1]]
          set freq  [lindex $spl 2]
          set CMDS($subsys,$alias) $cmd                 
          set CMDS($subsys,$alias,freq) $freq
          lappend ALIASES $alias            
       } else {
          set x [string trim $rec]
          set y [join [split $x "\[" ] "\\\["]
          set z [join [split $y "\]" ] "\\\]"]
          lappend CMDS($subsys,$alias,param) $z
       }
  }
}
close $fin

puts stdout "Generating command IDL for $subsys"
puts stdout "**************NOT CURRENTLY USED****************"
set fidl [open $SAL_WORK_DIR/command_[set subsys].idl w]
foreach i [lsort $ALIASES] {
   puts $fidl "   struct command_$i \{"
   add_private_idl $fidl "      "
   if { [info exists SYSDIC($subsys,keyedID)] } {
       puts $fidl "      short [set subsys]ID;"
   }
   if { [info exists CMDS($subsys,$i,param)] } {
     foreach p $CMDS($subsys,$i,param) {
         puts $fidl "      $p;"
     }
   }
   puts $fidl "   \};"
   if { [info exists SYSDIC($subsys,keyedID)] } {
      puts $fidl "   #pragma keylist command_$i [set subsys]ID"
   } else {
      puts $fidl "   #pragma keylist command_$i"
   }
}
close $fidl

puts stdout "Generating test command gui input"        
set fout [open $SAL_WORK_DIR/idl-templates/validated/[set subsys]_cmddef.tcl w]
puts $fout "set ALIASES \"$ALIASES\""
foreach c [array names CMDS] {
   puts $fout "set CMDS($c) \"$CMDS($c)\""
}
close $fout

exec mkdir -p $SAL_WORK_DIR/html/[set subsys]
set fout [open $SAL_WORK_DIR/html/[set subsys]/command_[set subsys].html w]
puts stdout "Generating html command table $subsys"
puts $fout "<H3>$subsys Commands</H3><P><UL>"
puts $fout "<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=800>
<TR BGCOLOR=Yellow><B><TD>Command Alias</TD><TD>Device</TD><TD>Property
</TD><TD>Action</TD><TD>Parameter</TD></B></TR>"
foreach i [lsort $ALIASES] {
      set cmd "$CMDS($subsys,$i) - - -"
      puts $fout "<TR><TD>$subsys<BR>$i</TD><TD>[lindex $cmd 0] </TD><TD>[lindex $cmd 1] </TD><TD> [lindex $cmd 2]</TD><TD> "
      if { [info exists CMDS($subsys,$i,param)] } {
        foreach p $CMDS($subsys,$i,param) {
          puts $fout "$p<BR>"
        } 
        puts $fout "</TD></TR>"
      } else {
        puts $fout "n/a"
      }
}
puts $fout "</TABLE></UL><P>"
close $fout



