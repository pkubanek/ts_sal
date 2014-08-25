proc doitem { fid fo2 name type } {
   switch $type {
       String16 { puts $fid "  string<16> $name;" 
                  puts $fo2 "  $name char(16),"
              }
       String - 
       String32 { puts $fid "  string<32> $name;" 
                  puts $fo2 "  $name char(32),"
              }
       String64 { puts $fid "  string<64> $name;" 
                  puts $fo2 "  $name char(64),"
              }
       String1K { puts $fid "  string<1024> $name;" 
                  puts $fo2 "  $name char(1024),"
              }
       Long   -
       Int    { puts $fid "  long $name;" 
                puts $fo2 "  $name int,"
              }
       Short  { puts $fid "  short $name;" 
                puts $fo2 "  $name short,"
              }
       Byte   { puts $fid "  byte $name;"
                puts $fo2 "  $name byte,"
              }
       Float  { puts $fid "  float $name;" 
                puts $fo2 "  $name float," 
               }
   }
}


set last ""
set fin [open datastreams.detail r]
set fsum [open datastreams.names w]
while { [gets $fin rec] > -1 } {
   set d [split [lindex $rec 0] "./"]
   set id [join [lrange $d 0 [expr [llength $d]-2]] .]
   set topic [join [lrange $d 0 [expr [llength $d]-2]] .]
   if { $id != $last  } {
      if { $last != "" } {puts $fsum $last}
      catch { puts $fout "\};"
              close $fout
              puts $fo2 "  PRIMARY KEY (date_time)"
              puts $fo2 "\};"
              close $fo2
            }
      set last $id
      puts stdout "Processing $id"
      set cid [join [split $id .] _]
      exec mkdir -p $id
      set fout [open $id/$cid.idl w]
      set fo2  [open $id/$cid.sqldef w]
      puts $fout "struct [join [split $topic .] _] \{
  string<32>  private_revCode; //private
  long private_sndStamp; //private
  long private_rcvStamp; //private
  long private_seqNum; //private
  long private_origin; //private"
      puts $fo2  "CREATE TABLE $topic \{"
      puts $fo2  "  date_time date time NOT NULL,
  private_revCode char(32),
  private_sndStamp long,
  private_rcvStamp long,
  private_seqNum long,
  private_origin long,"
   }
   if { [lindex $rec 1] > 1 && [string range [lindex $rec 2] 0 5] != "String"} {
      set i 1
      while { $i < [lindex $rec 1] } {
         doitem $fout $fo2 [lindex [lindex $d end] 0]_$i [lindex $rec 2]
         incr i 1
      }
   } else {
      doitem $fout $fo2 [lindex [lindex $d end] 0] [lindex $rec 2]
   }
}


close $fsum

