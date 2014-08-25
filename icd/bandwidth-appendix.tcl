
proc add_bandwidth_appendix { fout } {
global SYSDIC
   set all "datastreams-bandwidths-by-subsystem.html datastreams-bandwidths-by-blobs.html"
   foreach s [lsort $SYSDIC(systems)] {
      set all "$all datastreams-bandwidths-$s.html"
   }
  foreach i $all { 
     set fin [open bandwidth/$i r]
     gets $fin rec
     while { [gets $fin rec] > -1 } {
        if { [string range $rec 0 18] == "This table does not" } {
           gets $fin rec
           gets $fin rec
        }
        if { $rec != "</TABLE><P></BODY></HTML>" } {
           puts $fout $rec
        } else {
           puts $fout "</TABLE><P>"
        }
     }
     close $fin
  }
}



