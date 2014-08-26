
set fout [open datastreams.detail w]
set all [glob */*.detail]
foreach s $all {
  set id [file rootname [file tail $s]]
  set fin [open $s r]
  while { [gets $fin rec] > -1 } {
     puts $fout "$id $rec"
  }
}

close $fout
