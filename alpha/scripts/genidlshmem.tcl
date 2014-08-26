#!/usr/bin/tclsh

#
# Step 1 : Modify datastreams.detail as necessary (web tools)
#      1a: or cat baseline_sep08.detail */*.detail > datastreams.detail
# Step 2 : ./genidlshmem.tcl to .idl and .sqldef files per topic
# Step 3 : ./genshmem.tcl [subsys] to generate c libraries/apps
# Step 4 : ./genshmtcl.tcl to generate tcl test code
# Step 5 : make ; touch Shared/*.o ; make to lib libshm.so
#

proc doitem { fid fo2 name type } {
   switch $type {
       string -
       String { puts $fid "  string<32> $name;" 
                puts $fo2 "  $name char(32),"
              }
       int    -
       long   -
       Int    { puts $fid "  long $name;" 
                puts $fo2 "  $name int,"
              }
       short  -
       Short  { puts $fid "  short $name;" 
                puts $fo2 "  $name short,"
              }
       char   -
       Char   {
                puts $fid "  string<1> $name;"
                puts $fo2 "  $name byte,"
              }
       byte   -
       Byte   { puts $fid "  octet $name;"
                puts $fo2 "  $name byte,"
              }
       float  -
       Float  { puts $fid "  float $name;" 
                puts $fo2 "  $name float," 
               }
       double -
       Double { puts $fid "  float $name;" 
                puts $fo2 "  $name float," 
               }
   }
}
proc nditem { fid fo2 name type nd } {
   switch $type {
       string -
       String { puts $fid "  string<$nd> $name;" 
                puts $fo2 "  $name char($nd),"
              }
       int    -
       long   -
       Int    { puts $fid "  long $name\[$nd\];" 
                puts $fo2 "  $name int($nd),"
              }
       short  -
       Short  { puts $fid "  short $name\[$nd\];" 
                puts $fo2 "  $name short($nd),"
              }
       char   -
       Char   {
                puts $fid "  string<$nd> $name;"
                puts $fo2 "  $name byte($nd),"
              }       byte   -
       Byte   { puts $fid "  octet $name\[$nd\];"
                puts $fo2 "  $name byte($nd),"
              }
       float  -
       Float  { puts $fid "  float $name\[$nd\];" 
                puts $fo2 "  $name float($nd)," 
               }
       double -
       Double { puts $fid "  float $name\[$nd\];" 
                puts $fo2 "  $name float($nd)," 
               }
   }
}

set defdir /home/shared/lsst/tests/api/streams/
set last ""
set fin [open $defdir/datastreams.detail r]
set fsum [open datastreams.names w]
while { [gets $fin rec] > -1 } {
   set d [split [lindex $rec 0] "./"]
   set ncmp [expr [llength $d] -2]
   set id [join [lrange $d 0 $ncmp] _]
   set topic [join [lrange $d 0 $ncmp] _]
   if { $id != $last  } {
      if { $last != "" } {puts $fsum $last}
      catch { puts $fout "\};"
              close $fout
              puts $fo2 "  PRIMARY KEY (date_time)"
              puts $fo2 "\};"
              close $fo2
            }
      set last $id
      set fout [open $id.idl w]
      set fo2  [open $id.sqldef w]
      puts $fout "struct $topic \{
  string<32> private_revCode; //private
  long private_sndStamp; //private
  long private_rcvStamp; //private
  long private_seqNum; //private
  long private_origin; //private"
      puts $fo2  "CREATE TABLE $topic \{"
      puts $fo2  "  date_time date time NOT NULL,
  private_revCode char(32),
  private_sndStamp int,
  private_rcvStamp int,
  private_seqNum int,
  private_origin int,"
   }
   if { [lindex $rec 1] > 1 } {
      set nd [lindex $rec 1]
      nditem $fout $fo2 [lindex [lindex $d end] 0] [lindex $rec 2] $nd
   } else {
      doitem $fout $fo2 [lindex [lindex $d end] 0] [lindex $rec 2]
   }
   puts stdout "Added [lindex [lindex $d end] 0] to $topic"
}


close $fsum
set lidl [glob *.idl]
set fmd5 [open revCodes.tcl w]
foreach i [lsort $lidl] {
  set c [lindex [exec md5sum $i] 0]
  set s [file rootname $i]
  puts $fmd5 "set REVCODE($s) $c"
}
close $fmd5
