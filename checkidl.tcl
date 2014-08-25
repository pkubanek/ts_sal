proc noncoding { r } {
global NEWCONSTS KEYINDEX
  set r [string trim $r "\{"]
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

proc validitem { type item {op all} } {
global NEWCONSTS IDLSIZES IDLRESERVED
  if { $type == "int" } {set type "long"}
  if { $type == "byte" } {set type "octet"}
  if { [string range $type 0 5] == "string" } { 
      set id [string trim $item "\;"]
      set siz  [lindex [split $type "<>"] 1]
      if { [info exists NEWCONSTS($siz)] } {set siz $NEWCONSTS($siz)}
      set nof $siz
      set t $type
      set v "  string<$siz>	$id"
   } else {
     set it [split $item "\[\]"]
     set t $type
     if { [llength $it] == 1 } {
      set id [string trim [lindex $it 0] "\;"]
      set siz 1
      set v "  $t	$id"
     } else {
      set id [string trim [lindex $it 0] "\;"]
      set siz  [lindex $it 1]
      if { [info exists NEWCONSTS($siz)] } {set siz $NEWCONSTS($siz)}
      set v "  $type	$id\[$siz\]"
     }
   }
#puts stdout "valid is $v"
   if { [lsearch $IDLRESERVED [string tolower $id]] > -1 } {errorexit "Invalid use of IDL reserved token $id"}
   if { $op == "dim" } {return $siz}
   if { $op == "type" } {return $t}
   if { $op == "id" } {return $id}
   return $v
}


proc htmheader { fhtm hid } {
global NEWCONSTS DEC SDESC
           set id [join [split $hid .] _]
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
     if { [info exists FREQUENCY($s)] == 0 } {set FREQUENCY($s) 0.1}
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
global SAL_DIR TIDUSED SAL_WORK_DIR
  set fin [open $f r]
  set fout [open $SAL_WORK_DIR/idl-templates/validated/$f w]
  stdlog "Creating $SAL_WORK_DIR/idl-templates/validated/$f"
  set id [file rootname $f]
  set hid [join [split $id _] .]
  set NONCODING 0
  set KEYINDEX ""
  set finds 0
  set iinum 0
  set eid 0
  while { [gets $fin rec] > -1 } {
     puts stdout "--->  $rec"
     if { [noncoding $rec] } {
        incr NONCODING 1
#puts stdout "is noncoding"
     } else {
       if { [string trim $rec] == "\}" ||  [string trim $rec] == "\};" } {
           puts stdout "end of topic"
           puts $fout "\};"
           puts $fout "#pragma keylist $topicid"
           close $fout
           close $fdet
           close $fcmt
           set mdid [lindex [exec md5sum $SAL_WORK_DIR/idl-templates/validated/$topicid.idl] 0]
           set tid [format %d 0x[string range $mdid 26 end]]
           set fdef [open $SAL_DIR/code/include/sal/svcSAL_[set topicid]_iid.h w]
           gentopicdefsql $topicid
           set fsql [open $SAL_DIR/code/sql/[set topicid]_items.sql a]
           puts $fdef "
#if !defined(SAL_[set topicid]_IID__INCLUDED_)
#define SAL_[set topicid]_IID__INCLUDED_"
           foreach t $tnames {
              set ps $props($t,size)
              if { $ps > 1 && $props($t,type) != "string" } {
                 incr ps 1
              }
              puts $fdef "#define SAL_IID_[set topicid]_[set t] $tid		// $t $props($t,type) $ps"
              puts $fsql "INSERT INTO [set topicid]_items VALUES ($props($t,num),\"$t\",\"$props($t,type)\",$props($t,size),\"$props($t,units)\",$props($t,freq),\"$props($t,range)\",\"$props($t,comment)\");"
              incr tid 1
           }
           puts $fdef "#endif\n"
           close $fdef
           close $fsql
           puts $fhtm "</TABLE><P>Click here to update: <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
           close $fhtm
      } else {
        if { [string range $rec 0 6] == "typedef" } {
           return "ERROR : $rec\nOnly primitive types supported"
        }
        if { [string range $rec 0 5] == "module" } {
           return "ERROR : $rec\nNot supported"
        }
        if { [string range $rec 0 5] == "struct" } {
           incr finds 1
           set iinum 0
           set sname [lindex [string trim $rec "\{"] 1]
           set status [salsyntaxcheck topic $sname]
           set id [file rootname $sname]
           set hid [join [split $id _] .]
           set topicid [file rootname $sname]
           if { [lindex $status 0] == "OK" } {
              catch {unset tnames}
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
              set fhtm [open $SAL_WORK_DIR/idl-templates/validated/$nt-streamdef.html w]
              htmheader $fhtm $hid
              set fout [open $SAL_WORK_DIR/idl-templates/validated/$nt.idl w]
              set fdet [open $SAL_WORK_DIR/idl-templates/validated/$nt.detail w]
              if { $KEYINDEX != "" } {puts $fdet "#index $KEYINDEX"; set KEYINDEX ""}
              set fcmt [open $SAL_WORK_DIR/idl-templates/validated/$nt.comments w]
              puts $fout "struct $nt \{
  string<32> private_revCode;  //private
  double     private_sndStamp; //private
  double     private_rcvStamp; //private
  long       private_seqNum;   //private
  long       private_origin;   //private
  long       private_host;     //private"
              set NEWTOPICS($hid) 1
              set NEWSIZES($hid)  0
           } else {
              return "ERROR : $rec\n$status"
           }
        } else {
           if { $finds == 0 } {
              return "ERROR : $rec\nItem precedes struct"
           }
           set u ""
           if { [string trim [lindex $rec 0]] == "unsigned" } {
              set u " unsigned"
              set rec [string range [string trim $rec] 9 end]
           }
           set type [string tolower [lindex [split [string trim [lindex $rec 0]] "<"] 0]]
           if { [lsearch $IDLTYPES $type] < 0 } {
              return "ERROR : $rec\nType $type not supported"
           }
           set vitem [validitem [lindex $rec 0] [lindex $rec 1]]
           set siz [validitem [lindex $rec 0] [lindex $rec 1] dim ]
           set type [validitem [lindex $rec 0] [lindex $rec 1] type ]
           set id [validitem [lindex $rec 0] [lindex $rec 1] id ]
           if { [lindex [split $id _] 0] == "private" } {
              puts stdout "Skipping private item $id"
           } else {
             set m1 [string trim [lindex [split $rec "|"] 1]]
             set meta [split $m1 ";"]
             set units [string trim [lindex $meta 0]]
             set range [string trim [lindex $meta 1]]
             set comments [string trim [lrange $meta 2 end] " \{\}"]
#             puts stdout "$nt - $u $id $type $siz $units $range $comments"
             incr NEWSIZES($hid) $siz
             puts $fout " $u [string trim $vitem];"
             incr eid 1
             doitem $eid $fhtm $id $type $siz "$units" "$range" "$comments" 
            puts stdout  "doitem $eid $fhtm $id $type $siz |$units |$range  |$comments "
             if { [info exists FREQUENCY($hid)] == 0 } {set FREQUENCY($hid) 0.1}
             puts $fdet "$hid.$id $siz $type $FREQUENCY($hid)"
             lappend tnames $id
             incr iinum 1
             set props($id,num) "$iinum"
             set props($id,size) $siz
             set props($id,type) "$u[lindex [split $type "<"] 0]"
             set props($id,freq) "$FREQUENCY($hid)"
             set props($id,range) "$range"
             set props($id,units) "$units"
             set props($id,comment) "$comments"
             if { [string trim $comments] != "none" && [string trim $comments] != "" } {
                puts $fcmt "set COMMENT($hid.$id) \"[string trim $comments]\""
             }
           }
          }
        }
     }
  }
  close $fin
  if { $finds == 0 } {
     errorexit "No struct found in $f"
  }
  return OK
}


proc gentopicdefsql { topic } {
global SAL_DIR
   set fsql [open $SAL_DIR/code/sql/[set topic]_items.sql w]
   puts $fsql "DROP TABLE IF EXISTS [set topic]_items;
CREATE TABLE [set topic]_items (
  num	int,
  item	char(32),
  type  char(32),
  size  int,
  units char(32),
  freq  float,
  range char(32),
  comment char(128),
  PRIMARY KEY (num)
);"
  close $fsql
}


proc checkall { } {
  set all [glob *.idl]
  foreach i $all { checkidl $i ; puts stdout "Validated $i" }
}

proc testdupiid { } {
global SAL_DIR
   set all [lsort [glob $SAL_DIR/code/include/sal/svcSAL_*_iid.h]]
   foreach i $all { 
      stdlog "Checking $i"
      set fin [open $i r]
      while { [gets $fin rec] > -1 } {
         set n [lindex $rec 2]
         if { [info exists used($)] } {
            stdlog "Duplicate IID = $n in $i"
            close $fin
            return
         } else {
            set used([lindex $rec 2]) 1
         }
      }
      close $fin
   }
}


source $env(SAL_DIR)/streamutils.tcl
source $env(SAL_DIR)/unitsdesc.tcl
source $env(SAL_DIR)/datastream_desc.tcl
source $env(SAL_DIR)/camera-subsysdesc.tcl
source $env(SAL_DIR)/utilities.tcl

set IDLTYPES "boolean char byte octet short int long longlong float double string unsigned"
set IDLSIZES(byte)     1
set IDLSIZES(char)     1
set IDLSIZES(octet)    1
set IDLSIZES(boolean)  2
set IDLSIZES(string)   1
set IDLSIZES(short)    2
set IDLSIZES(int)      4
set IDLSIZES(long)     4
set IDLSIZES(longlong) 8
set IDLSIZES(float)    4
set IDLSIZES(double)   8
set IDLRESERVED "abstract any attribute boolean case char component const consumes context custom default double emits enum eventtype exception factory false finder fixed float getraises home import in inout interface local long module multiple native object octet oneway out primarykey private provides public publishes raises readonly sequence setraises short string struct supports switch true truncatable typedef typeid typeprefix union unsigned uses valuebase valuetype void wchar wstring"



