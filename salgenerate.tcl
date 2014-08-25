#!/usr/bin/tclsh

set topic $argv
exec mkdir -p $topic

set whereami [pwd]
set scriptdir /usr/local/scripts/tcl

set lidl [glob *.idl]
set fmd5 [open revCodes.tcl w]
foreach i [lsort $lidl] {
  set c [lindex [exec md5sum $i] 0]
  set s [file rootname $i]
  puts $fmd5 "set REVCODE($s) $c"
}
close $fmd5

puts stdout "Building DDS libs/apps for $topic"
set subsys $topic
exec $scriptdir/genshmem.tcl $subsys

cd $topic

puts stdout "Building test scripts"
source $scriptdir/genshmtcl.tcl

puts stdout "Building libshm.so"
exec make
exec touch Shared/*.o
exec make

