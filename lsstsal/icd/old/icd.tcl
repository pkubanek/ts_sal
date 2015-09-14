
proc telemetrytables { fid } {
global SUBSYSTEM2 SID ITEM PROP DESC COMMENT
  set all [lsort [array names ITEM]]
  foreach i $all {
    set s [lindex [split $i .] 0]
    if { $s == $SUBSYSTEM2 } {
       puts $fid "<H3>Telemetry datastream topic : $i</H3><P>
$DESC($i)<P>
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightGrey WIDTH=700><TR><TD>Item</TD><TD>Type</TD><TD>Size</TD><TD>Freq.</TD><TD>Notes</TD></TR>"
       foreach p $ITEM($i) {
           set it $PROP($i,$p)
           set cmt "None"
           catch { set cmt $COMMENT($i.$p) }
           puts $fid "<TR><TD>$p</TD><TD>[lindex $it 1]</TD><TD>[lindex $it 0]</TD><TD>[lindex $it 2]</TD><TD>$cmt</TD></TR>"
       }
       puts $fid "</TABLE><P>"
    }
  }
}

source ../tests/api/streams/newstreams.tcl

set fin [open ../tests/api/streams/datastreams.detail r]
while { [gets $fin rec] > -1 } {
  set r [split [lindex $rec 0] .]
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


source streamdesc.tcl
source subsysdesc.tcl
source camera-subsysdesc.tcl

source newcomments.tcl
source template.html
 
set SUBS "auxscope calibration camera enclosure environment lasercal m1 m2 m3 mount power seeing-dimm.Electrical seeing_dimm seeing_mass skycam"

set GLOSSARY "
DDS - Data Distribution Service<BR>
OMG - Object Management Group<BR>
LSST - Large Synoptic Survey Telescope<BR>
QoS - Quality of Service<BR>
RTI - Real Time Innovation<BR>
SAL - Software Abstraction Layer<BR>
"

foreach i [array names SDESC] {
  if { [info exists DESC($i)] == 0 } {set DESC($i) $SDESC($i)}
  puts stdout "No DESC for $i"
}

set SUBSYSTEM1 OCS
foreach i $SUBS {
  set SUBSYSTEM2 $i
  set ORIGDATE "Jan 7 2008"
  source template.html
  set fout [open icd-sw-$SID($SUBSYSTEM1)-$SID($SUBSYSTEM2).html w]
  puts $fout "$TICD"
  telemetrytables $fout
  puts $fout "$TICD2"
  close $fout
  puts stdout "Done $i"
}


