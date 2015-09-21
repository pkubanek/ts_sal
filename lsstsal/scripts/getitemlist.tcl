
proc getitemlist { topic } {
global SAL_WORK_DIR
   set items [split [exec grep $topic $SAL_WORK_DIR/.salwork/datastreams.detail] \n]
   set ilist ""
   set idx 0
   while { $idx < [llength $items] } {
      set it [lindex $items $idx]
      lappend ilist [lrange [split $it ". "] 3 end]
      incr idx 1
   }
   return $ilist
}


proc getitemlist { topic } {
global SAL_WORK_DIR
   set items [split [exec grep $topic $SAL_WORK_DIR/idl-templates/validated/$topic.detail] \n]
   set ilist ""
   set idx 0
   while { $idx < [llength $items] } {
      set it [lindex $items $idx]
      lappend ilist [lrange [split $it ". "] 1 end]
      incr idx 1
   }
   return $ilist
}


