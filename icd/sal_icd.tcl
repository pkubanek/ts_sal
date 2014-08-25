
proc telemetrytables { fid } {
global SUBSYSTEM2 SID ITEM PROP DESC COMMENT
  set all [lsort [array names ITEM]]
  foreach i $all {
    set s [lindex [split $i .] 0]
    if { $s == $SUBSYSTEM2 } {
      set cr [lindex [split $i .] 1]
      if { $cr !="command" && $cr != "response" } {
       if { [info exists DESC($i)] == 0 } {set DESC($i) ""}
       puts $fid "<H3>Telemetry datastream topic : $i</H3><P>
$DESC($i)<P><UL>
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue WIDTH=700><TR BGCOLOR=yellow><B><TD>Item</TD><TD>Type</TD><TD>Size</TD><TD>Freq.</TD><TD>Notes</TD></B></TR>"
       foreach p $ITEM($i) {
           set it $PROP($i,$p)
           set cmt "None"
           catch { set cmt $COMMENT($i.$p) }
           puts $fid "<TR><TD>$p</TD><TD>[lindex $it 1]</TD><TD>[lindex $it 0]</TD><TD>[lindex $it 2]</TD><TD>$cmt</TD></TR>"
       }
       puts $fid "</TABLE></UL><P>"
     }
    }
  }
}


proc commandtables { fid } {
global CMDS SUBSYSTEM2 SAL_DIR
  catch {unset CMDS}
  if { [file exists $SAL_DIR/command-list-$SUBSYSTEM2] } {
    set fin [open $SAL_DIR/command-list-$SUBSYSTEM2 r]
    while { [gets $fin rec] > -1 } {
      if { [string index $rec 0] == "#" || [string trim $rec] == "" } {
      } else {
        set s [lindex $rec 0]
        if { $s != "Any" } {
           lappend CMDS($SUBSYSTEM2) [join [lrange $rec 1 end] :]
        }
      } 
    }
    close $fin
    foreach s [lsort [array names CMDS]] {
     if { [lindex [split $s .] 0] == $SUBSYSTEM2 } {
      set s $SUBSYSTEM2
      puts stdout "Processing $s"
      puts $fid "<H4>$s Commands</H4><P><UL>"
      puts $fid "<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Subsystem</TD><TD>Device</TD><TD>Property</TD><TD>Action</TD<TD>Parameter</TD></B></TR>"
      foreach c [lsort $CMDS($s)] {
       set f "[split $c :] <EM>n/a</EM> <EM>n/a</EM> <EM>n/a</EM>"
       puts $fid "<TR><TD>$s</TD><TD>[lindex $f 0]</TD><TD>[lindex $f 1]</TD><TD> [lindex $f 2]</TD><TD> [lindex $f 3]</TD></TR>"
      }
      puts $fid "</TABLE></UL><P>"
     }
    }
  } else {
    return -1
  }
}


proc insertGlossary { } {
global GLOSSARY
  set all [lsort [array names GLOSSARY]]
  set g "<P>"
  foreach i $all {set g "$g<BR>$i - $GLOSSARY($i)"}
  return "$g<<P>"
}

set SAL_DIR /opt/lsstsal/scripts
set SAL_WORK_DIR /efdb1/test

set fin [open $SAL_WORK_DIR/.salwork/datastreams.detail r]
while { [gets $fin rec] > -1 } {
  set r [split [lindex $rec 1] .]
  if { [llength $r] == 4 } {
    set s [join [lrange $r 0 2] .]
    lappend ITEM($s) [lindex $r 3]
    set PROP($s,[lindex $r 3]) [lrange $rec 1 end]
  } else {
    set s [join [lrange $r 0 1] .]
    lappend ITEM($s) [lindex $r 2]
    set PROP($s,[lindex $r 2]) [lrange $rec 1 end]
  }
}
close $fin

source $SAL_DIR/icd/documentrefs.tcl
source $SAL_DIR/datastream_desc.tcl
source $SAL_DIR/streamdesc.tcl
source $SAL_DIR/camera-subsysdesc.tcl
source $SAL_DIR/unitsdesc.tcl
source $SAL_DIR/qosdesc.tcl
#override SID's from subsysdesc.tcl
source $SAL_DIR/icd/sid.tcl

source $SAL_DIR/newcomments.tcl
 
if { [info exists SINGLESUBSYSTEM] } {
  set SUBS $SINGLESUBSYSTEM
} else {
  set SUBS "auxscope calibration camera dm enclosure environment lasercal m1m3 m2 mount network operations power scheduler seeing_dimm seeing_mass skycam system tcs"
}


set GLOSSARY(DDS) "Data Distribution Service"
set GLOSSARY(OMG) "Object Management Group"
set GLOSSARY(LSST) "Large Synoptic Survey Telescope"
set GLOSSARY(QoS) "Quality of Service"
set GLOSSARY(RTI) "Real Time Innovation"
set GLOSSARY(SAL) "Software Abstraction Layer"

foreach i [array names SDESC] {
  if { [info exists DESC($i)] == 0 } {set DESC($i) $SDESC($i)}
  if { [info exists SINGLESUBSYSTEM] ==0  } {
    puts stdout "No DESC for $i"
  }
}

set SUBSYSTEM1 ocs
foreach i $SUBS {
  set SUBSYSTEM2 $i
  set ORIGDATE [exec date +%m-%d-%Y]
  source $SAL_DIR/icd/template.html
  set fout [open icd-sw-$SID($SUBSYSTEM1)-$SID($SUBSYSTEM2).html w]
  puts $fout "$TICD1"
  commandtables $fout
  puts $fout "$TICD2"
  telemetrytables $fout
  puts $fout "$TICD3"
  close $fout
  puts stdout "Done $i"
}

source $SAL_DIR/icd/bandwidth-appendix.tcl
source $SAL_DIR/icd/add_system_dictionary.tcl
cp  $SAL_DIR/icd/lse74-template.html LSE74-html/index.html
set fout [open LSE74-html/index.html a]
add_system_dictionary_appendix $fout
set n 1
puts $fout "<P><H1>Appendix B - Telemetry Datastream Definitions</H1><P>"
foreach i $SUBS {
puts $fout "<H2>B$n $i Telemetry</H2>"
set SUBSYSTEM2 $i
  telemetrytables $fout
  incr n 1
}
set n 1
  set SUBS "auxscope calibration dm enclosure environment lasercal m1m3 m2 mount network operations power scheduler seeing_dimm seeing_mass skycam system tcs"
puts $fout "<P><H1>Appendix C - Command Definitions</H1><P>"
foreach i $SUBS {
set SUBSYSTEM2 $i
puts $fout "<H2>C$n $i Commanding</H2>"
  set res [commandtables $fout]
  incr n 1
}
puts $fout "<P><H1>Engineering and Facility Database</H1>
<P>
The following tables list the projected datga ingest rates the to
the EFB tables, both in summary form, and per-subsystem.
<P>"
add_bandwidth_appendix $fout
close $fout



