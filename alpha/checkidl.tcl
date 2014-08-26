proc noncoding { r } {
global NEWCONSTS KEYINDEX
  set r [string trim $r "\{\}"]
  if { [string range $r 0 5] == "#index" } {
     set KEYINDEX [lindex $r 1]
     return 1
  }
  if { [string trim $r] == "" || [string range $r 0 0] == "#" || [string range $r 0 1] == "//"} {
     return 1
  }
  if { [string range $r 0 4] == "const" } {
     set var [lindex [split [lrange $r 1 end] =] 0]
     set val [lindex [split [lrange $r 1 end] =] 1]
     set NEWCONSTS([string trim $var]) $val
     return 1
  }
  return 0
}

proc salsyntaxcheck { type value } {
    switch $type {
         topic { 
                 set vfd [join [split $value "\"\'\;,\]\[\}\{()@\\&\%\!\` ^=-+\<\>\/\n"] _]
                 return "OK $vfd"
               }
    }
}

proc streamsizes { } {
global NEWSIZES FREQUENCY PUBLISHERS
  set stotal 0 ; set dtotal 0 ; set btotal 0
  foreach s [lsort [array names NEWSIZES]] {
     set payload $NEWSIZES($s)
     set total   [expr ($payload + 48) * $PUBLISHERS($s)]
     set persec [expr int($total  * $FREQUENCY($s))]
     set perday [expr $persec * 3600. * 24. /1024./1024.]
     puts stdout "[format %-20s $s]	size=[format %6d $total]	rate=[format %6d $persec] Bytes/sec [format %5.1f $perday] Mb/day" 
     set btotal [expr $btotal + $total]
     set stotal [expr $stotal + $persec]
     set dtotal [expr $dtotal + $perday]
  }
  puts stdout "\n[format %-20s Total]	size=[format %6d $btotal]	rate=[format %6d [expr int($stotal)]] Bytes/sec [expr int($dtotal)] Mb/day" 
}


proc checkidl { f } {
global NEWTOPICS NEWSIZES NEWCONSTS
global DESC SDESC IDLTYPES IDLSIZES
global PUBLISHERS FREQUENCY KEYINDEX
  set fin [open $f r]
  set fout [open validated/$f w]
  set id [file rootname $f]
  set hid [join [split $id _] .]
  set NONCODING 0
  set KEYINDEX ""
  set finds 0
  set eid 0
  while { [gets $fin rec] > -1 } {
     puts stdout "--->  $rec"
     if { [noncoding $rec] } {
        incr NONCODING 1
     } else {
         if { [string trim $rec] == "\};" } {
           puts $fout $rec
           close $fout
           close $fdet
           close $fcmt
           puts $fhtm "</TABLE><P>Click here to update: <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
           close $fhtm
        }
        if { [string range $rec 0 6] == "typedef" } {
           return "ERROR : $rec\nOnly primitive types supported"
        }
        if { [string range $rec 0 5] == "module" } {
           return "ERROR : $rec\nNot supported"
        }
        if { [string range $rec 0 5] == "struct" } {
           incr finds 1
           set sname [lindex [string trim $rec "\{"] 1]
           set status [salsyntaxcheck topic $sname]
           set id [file rootname $sname]
           set hid [join [split $id _] .]
           if { [lindex $status 0] == "OK" } {
              set nt [lindex $status 1]
              if { [info exists NEWTOPICS($nt)] } {
                 return "ERROR : $rec\nDuplicate struct definition"
              }
              catch {
                 close $fout
                 incr eid 1
                 doitem $eid $fhtm "" int 1
                 puts $fhtm "</TABLE><P>Click here to update: <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
                 close $fhtm
                 close $fdet
                 close $fcmt
              }    
              set fhtm [open validated/$nt-streamdef.html w]
              puts $fhtm "<HTML><HEAD><TITLE>Stream definition editor - $hid</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"../LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"../dde.gif\" ALIGN=CENTER><P><HR><P>
<H1>Stream $hid</H1><P>"
              if { [info exists SDESC($hid)] } {
                 puts $fhtm "<H2>Description</H2><P>$SDESC($hid)"
              } else {
                 if { [info exists DESC($hid)] } {
                    puts $fhtm "<H2>Description</H2><P>$DESC($hid)"
                 } else {
                    puts $fhtm "<H2>Description</H2><P>TBD"
                 }
              }
              if { [info exists NEWCONSTS(FREQUENCY)] } {
                 puts $fhtm "<H2>Update frequency</H2>"
                 set FREQUENCY($hid) $NEWCONSTS(FREQUENCY)
                 if { $NEWCONSTS(FREQUENCY) < 1.0 } {
                    puts $fhtm "This telemetry stream publishes a new record every [expr int(1.0/$NEWCONSTS(FREQUENCY))] seconds"
                 } else {
                    puts $fhtm "This telemetry stream publishes a new record at [expr int($NEWCONSTS(FREQUENCY))] Hz"
                 }
              }
              if { [info exists NEWCONSTS(PUBLISHERS)] } {
                 set PUBLISHERS($hid) $NEWCONSTS(PUBLISHERS)
                 puts $fhtm "<H2>Publishers</H2>"
                 if { $NEWCONSTS(PUBLISHERS) > 1 } {
                    puts $fhtm "There are $NEWCONSTS(PUBLISHERS) instances of this stream published."
                 } else {
                    puts $fhtm "Only one instance of this stream is published."
                 }
              }
              puts $fhtm "<P><HR><H2>Topic Definition</H2><P>
<FORM action=\"/cgi-bin/streamdef\" method=\"post\">
<INPUT NAME=\"streamid\" TYPE=\"HIDDEN\" VALUE=\"$id\">
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Name</TD><TD>Type</TD><TD>Size</TD><TD>Units</TD>
<TD>Range</TD><TD>Comment</TD><TD>Delete</TD></B></TR>"
              set fout [open validated/$nt.idl w]
              set fdet [open validated/$nt.detail w]
              if { $KEYINDEX != "" } {puts $fdet "#index $KEYINDEX"; set KEYINDEX ""}
              set fcmt [open validated/$nt.comments w]
              puts $fout "struct $nt \{
  string<32> private_revCode;  //private
  long       private_sndStamp; //private
  long       private_rcvStamp; //private
  long       private_seqNum;   //private
  long       private_origin;   //private"
              set NEWTOPICS($hid) 1
              set NEWSIZES($hid)  0
           } else {
              return "ERROR : $rec\n$status"
           }
        } else {
           if { $finds == 0 } {
              return "ERROR : $rec\nItem precedes struct"
           }
           if { [string trim $rec] != "\};" } {
           set u 0
           if { [string trim [lindex $rec 0]] == "unsigned" } {
              set u 1
              set rec "[string range $rec 11 end]"
           }
           set type [string tolower [lindex [split [string trim [lindex $rec 0]] "<"] 0]]
           if { [lsearch $IDLTYPES $type] < 0 } {
              return "ERROR : $rec\nType $type not supported"
           }
           if { $type == "string" } { 
              set siz  [lindex [split $rec "<>"] 1]
              if { [info exists NEWCONSTS($siz)] } {set siz $NEWCONSTS($siz)}
              set nof $siz
              set item [lindex [lindex [split $rec "<>"] 2] 0]
           } else {
              if { [llength [split $rec "\[\]"]] > 1 } {
                set dim [lindex [split $rec "\[\]"] 1]
                if { [info exists NEWCONSTS($dim)] } {
                  set siz  [expr $IDLSIZES($type) * $NEWCONSTS($dim)]
                  set nof $NEWCONSTS($dim)
                } else {
                  set siz  [expr $IDLSIZES($type) * [lindex [split $rec "\[\]"] 1]]
                  set nof [lindex [split $rec "\[\]"] 1]
                }
                set item [lindex [lindex [split $rec "\[\]"] 0] 1]
              } else {
                set siz $IDLSIZES($type)
                set item [lindex $rec 1]
                set nof 1
              }
           }
           set item [string trim $item "; "]
           if { [lindex [split $item _] 0] == "private" } {
              puts stdout "Skipping private item $item"
           } else {
             set m1 [string trim [lindex [split $rec #] 1]]
             set meta [split $m1 ";"]
             set units [string trim [lindex $meta 0]]
             set range [string trim [lindex $meta 1]]
             set comments [string trim [lrange $meta 2 end] " \{\}"]
#             puts stdout "$nt - $u $item $type $siz $units $range $comments"
             incr NEWSIZES($hid) $siz
             if { $u } {
               puts $fout "  unsigned $rec"
             } else {
               puts $fout $rec
             }
             incr eid 1
             doitem $eid $fhtm $item $type $nof "$units" "$range" "$comments" 
#            puts stdout  "doitem $eid $fhtm $item $type $nof |$units |$range  |$comments "
             puts $fdet "$hid.$item $nof $type $FREQUENCY($hid)"
             if { [string trim $comments] != "none" && [string trim $comments] != "" } {
                puts $fcmt "set COMMENT($hid.$item) \"[string trim $comments]\""
             }
           }
          }
        }
     }
  }
  close $fin
  if { $finds == 0 } {
     return "ERROR : No struct found"
  }
  return OK
}


proc checkall { } {
  set all [glob *.idl]
  foreach i $all {
     set type [lindex [split [file rootname $i] _] end]
     if { $type != "command" && $type != "response" } {
       checkidl $i ; puts stdout "Checked $i"
     }
  }
}


source /usr/local/scripts/tcl/streamutils.tcl
source /usr/local/scripts/tcl/unitsdesc.tcl
source /usr/local/scripts/tcl/datastream_desc.tcl
source /usr/local/scripts/tcl/camera-subsysdesc.tcl

set IDLTYPES "byte short int long float double string unsigned"
set IDLSIZES(byte)   1
set IDLSIZES(string) 1
set IDLSIZES(short)  2
set IDLSIZES(int)    4
set IDLSIZES(long)   4
set IDLSIZES(float)  4
set IDLSIZES(double) 8



