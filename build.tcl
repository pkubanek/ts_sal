#!/usr/bin/tclsh

set whereami [pwd]
puts stdout "Building idl and sql definition files"
source $whereami/genidlshmem.tcl
set all [lsort [glob *.idl]]
foreach i $all {
  puts stdout "Building DDS libs/apps for $i"
  set subsys [file rootname $i]
  exec $whereami/genshmem.tcl $subsys
  cd $whereami
}

puts stdout "Building test scripts"
source $whereami/genshmtcl.tcl
puts stdout "Building libshm.so"
exec make
exec touch Shared/*.o
exec make

