#!/usr/bin/env tclsh

set SAL_WORK_DIR $env(SAL_WORK_DIR)

proc updateRevCodes { subsys } {
global SAL_WORK_DIR
  set lidl [glob $SAL_WORK_DIR/idl-templates/validated/[set subsys]_*.idl]
  set fmd5 [open $SAL_WORK_DIR/idl-templates/validated/[set subsys]_revCodes.tcl w]
  foreach i [lsort $lidl] {
    set c [lindex [exec md5sum $i] 0]
    set s [file tail [file rootname $i]]
    puts $fmd5 "set REVCODE($s) [string range $c 0 7]"
  }
  close $fmd5
}


proc activeRevCodes { subsys } {
global SAL_WORK_DIR REVCODE
  set fin [open $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl r]
  set fout [open $SAL_WORK_DIR/idl-templates/validated/sal/sal_revCoded_[set subsys].idl w]
  while { [gets $fin rec] > -1 } {
    set r2 [string trim $rec "{}"]
    if { [lindex $r2 0] == "struct" } {
       set id [lindex $r2 1]
       if { $id != "command" && $id != "logevent" } {
         puts $fout "struct [set id]_[string range [set REVCODE([set subsys]_$id)] 0 7] \{"
       } else {
         puts $fout $rec
       }
    } else {
       if { [lindex $r2 0] == "#pragma" } {
          set id [lindex $r2 2]
          if { $id != "command" && $id != "logevent" } {
            puts $fout "#pragma keylist [set id]_[string range [set REVCODE([set subsys]_$id)] 0 7] [lrange $rec 3 end]"
          } else {
            puts $fout $rec
          }
       } else {
          puts $fout $rec
       }
    }
  }
  close $fin
  close $fout
}


proc getRevCode { topic { type "long"} } {
global REVCODE
   if { [llength [split $topic _]] == 2 } {
      set it [lindex [split $topic _] end]
      if { $it == "command" || $it == "logevent" } {
         return ""
      }
   }
   if { $type == "short" } {
     set revcode _[string range [set REVCODE($topic)] 0 7]
   } else {
     set revcode $REVCODE($topic)
   }
   return $revcode
}

proc modidlforjava { subsys } {
global SAL_WORK_DIR
  puts stdout "Updating $subsys idl with revCodes"
  set lc [exec wc -l $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl]
  set lcnt [expr [lindex $lc 0] -2]
  set fin [open $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl r]
  exec rm -f $SAL_WORK_DIR/[set subsys]/java/sal_[set subsys].idl
  set fout [open $SAL_WORK_DIR/[set subsys]/java/sal_[set subsys].idl w]
  set ln 0
  while { $ln < $lcnt} {
     gets $fin rec ; puts $fout $rec
     incr ln 1
  }
  close $fin
  set fin [open $SAL_WORK_DIR/idl-templates/validated/sal/sal_revCoded_[set subsys].idl r]
  gets $fin rec
  set done 0
  while { $done == 0 } {
     gets $fin rec
     if { [string trim $rec "	 {}"] == "struct command" } {
        set done 1
     } else {
        if { [lindex [string trim $rec "	 {}"] 0] != "const" } {
          puts $fout $rec
        }
     } 
  }
  puts $fout "\};"
  close $fin
  close $fout
}





