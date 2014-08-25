#!/usr/bin/tclsh

set all [lsort [glob *.idl]]
set fin [open /opt/lsstsal/scripts/code/jSAL/salbuild.xml.template r]
set fout [open /opt/lsstsal/scripts/code/jSAL/salbuild.xml w]
while { [gets $fin rec] > -1 } {
  if { [lrange $rec 1 3] == "Insert idlpp here" } {
    foreach i $all {
      puts $fout "		<exec command=\"idlpp -S -l java -d \$\{examplesrcgen.dir\} resources/$i\"/>"
    }
  } else { 
    puts $fout $rec
  }
}
close $fout
close $fin
