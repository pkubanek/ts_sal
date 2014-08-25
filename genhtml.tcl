#!/usr/bin/tclsh

proc dometa { id } {
global SDESC UDESC QDESC
   exec mkdir -p $id
   set fmet [open $id/[tidyname $id]-metadata.html w]
   puts $fmet "<HTML><HEAD><TITLE>Stream definition editor - $id</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"../LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"../dde.gif\" ALIGN=CENTER><P><HR><P>
<H1>Stream $id MetaData</H1><P>"
      if { [info exists SDESC($id)] == 0 } {
           puts stderr "No SDESC for $id"
           set SDESC($id) "unknown"
      }
      puts $fmet "$SDESC($id)<HR><P>
<FORM action=\"/cgi-bin/metadef\" method=\"post\">
<INPUT NAME=\"streamid\" TYPE=\"HIDDEN\" VALUE=\"$id\">
<H2>Units for stream data</H2><P>
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Unit</TD><TD>Definition</TD><TD>Usable</TD></B></TR>"
   foreach u [lsort [array names UDESC]] {
     puts $fmet "<TR><TD>$u</TD><TD>$UDESC($u)</TD><TD><INPUT TYPE=\"checkbox\" NAME=\"allow_$u\" VALUE=\"yes\"></TD></TR>"
   }
   puts $fmet "</TABLE><P><HR><P>"
   puts $fmet "<H2>Update Frequency</H2> <select name=\"freq_$u\">
<option value=\"0.05\">20 second period
<option value=\"0.1\">10 second period
<option value=\"0.5\">2 second period
<option value=\"1\" selected>1 Hz
<option value=\"10\">10 Hz
<option value=\"30\">30 Hz
<option value=\"100\">100 Hz
</select>"
   puts $fmet "<P><HR><P>"
   set qs [array names QDESC]
   puts $fmet "<H2>Quality Of Service</H2> <select name=\"qos_$u\">
<option value=\"[lindex $qs 0]\" selected>$QDESC([lindex $qs 0])"
   foreach q [lrange $qs 1 end] {
      puts $fmet "<option value=\"$q\">$QDESC($q)"
   }
   puts $fmet "</select><P><HR><P>"
   puts $fmet "<input type=\"submit\" value=\"Update MetaData settings for stream\" name=\"apply\">
</FORM><P><HR><P></BODY></HTML>"
   close $fmet
}

proc pubsubs { } {
global PUBLISHERS SUBSCRIBERS SAL_DIR
  set fps [open $SAL_DIR/datastreams_desc.pubsub r]
  while { [gets $fps rec] > -1 } {
    set PUBLISHERS([lindex $rec 0]) [lindex $rec 1]
    set SUBSCRIBERS([lindex $rec 0]) [lindex $rec 2]
  }
  close $fps
}
 
proc tidyname { f } { 
  return [join [split $f .] _]
}


catch { unset MSYS}
set scriptdir $env(SAL_DIR)

source $scriptdir/checkdesc.tcl
source $scriptdir/comments.tcl
source $scriptdir/streamutils.tcl
pubsubs

set SYSTEMS ""
set fidx [open index-streamdef.html w]
puts $fidx "<HTML><HEAD><TITLE>Stream definition editor index</TITLE></HEAD>
<BODY BGCOLOR=White>
<IMG SRC=\"LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"dde.gif\" ALIGN=CENTER><P><HR><P>
<H2>Create a new Datastream</H2><P>
<FORM action=\"/cgi-bin/streamdef\" method=\"post\">
<P>Copy item list from named datastream (optional) : 
<select name=\"copy\"><option value=\" \" selected>"
foreach s [lsort [array names SDESC]] {
  puts $fidx "<option value=\"$s\">$s"
  set MSYS([lindex [split $s .] 0]) 1
}


puts $fidx "</select>
<P>Name of new datastream definition: 
<select name=\"system\"><option value=\"?\" selected>"
foreach s [lsort [array names MSYS]] {
  puts $fidx "<option value=\"$s\">$s."
}

puts $fidx "</select>
<input name=\"new\" value=\"\" size=32>
<P>Please enter a brief description of the new datastream<P>
<TEXTAREA NAME=\"description\" COLS=60 ROWS=6></TEXTAREA><P>
<input type=\"submit\" value=\"Create a template for the new stream\" name=\"create\">
</FORM><P><HR><P>
<H2>Modify current Datastream definitions</H2><P>
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Stream Name</TD><TD>Edit contents</TD><TD>Edit MetaData</TD>
<TD>Configure SAL</TD></B></TR>"

set fgen [open sal-generator.html w]
puts $fgen "<HTML><HEAD><TITLE>Software Abstraction Layer API generator</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"salg.gif\" ALIGN=CENTER><P><HR><P>
<H1>Datastream and command capabilties</H1><P><HR><P>
Use the checkboxes in the form to select the combination<BR>
of telemetry datastreams for which the application requires<BR>
read and/or write access, and the command streams upon<BR>
which commands need to be issued or processed.<P>
<FORM action=\"/cgi-bin/salgenerator\" method=\"post\">
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Stream Name</TD><TD>Subscribe</TD><TD>Publish</TD><TD>Issue Command</TD>
<TD>Process Comamnd</TD></B></TR>"

set last ""
set fin [open $SAL_WORK_DIR/.salwork/datastreams.detail r]
while { [gets $fin rec] > -1 } {
  set cmdresp [lindex [split $rec "_ "] 1]
  if { $cmdresp != "command" && $cmdresp != "response" } {
   set d [split [lindex $rec 0] "./_"]
   set id [join [lrange $d 0 [expr [llength $d]-2]] .]
   set FREQUENCY($id) [lindex $rec 4]
   set system [lindex $d 0]
   set topic [join $d .]
   if { $id != $last  } {
      catch { doitem $nid $fout "" int 1
              puts $fout "</TABLE><P>Click here to update: <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
              close $fout
              puts stdout "Done $last"
            }
      set last $id
      exec mkdir -p $id
      set fout [open $id/[tidyname $id]-streamdef.html w]
      set nid 1
      set CSYS $id
      puts $fout "<HTML><HEAD><TITLE>Stream definition editor - $id</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"../LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"../dde.gif\" ALIGN=CENTER><P><HR><P>
<H1>Stream $id</H1><P><H2>Description</H2>"
      if { [info exists SDESC($id)] == 0 } {
           puts stderr "No SDESC for $id"
           set SDESC($id) "unknown"
      }
      puts $fout "$SDESC($id)<HR><P>"
      if { [info exists FREQUENCY($id)] } {
            puts $fout "<H2>Update frequency</H2>"
            if { $FREQUENCY($id) < 1.0 } {
                    puts $fout "This telemetry stream publishes a new record every [expr int(1.0/$FREQUENCY($id))] seconds"
            } else {
                    puts $fout "This telemetry stream publishes a new record at [expr int($FREQUENCY($id))] Hz"
            }
     }
     if { [info exists PUBLISHERS($id)] } {
            puts $fout "<H2>Publishers</H2>"
            if { $PUBLISHERS($id) > 1 } {
                    puts $fout "There are $PUBLISHERS($id) instances of this stream published."
            } else {
                    puts $fout "Only one instance of this stream is published."
            }
      }
      puts $fout "<P><HR><FORM action=\"/cgi-bin/streamdef\" method=\"post\">
<INPUT NAME=\"streamid\" TYPE=\"HIDDEN\" VALUE=\"$id\">
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Name</TD><TD>Type</TD><TD>Size</TD><TD>Units</TD>
<TD>Range</TD><TD>Comment</TD><TD>Delete</TD></B></TR>"
#      puts $fidx "<LI><A HREF=\"$id/[tidyname $id]-streamdef.html\">Edit stream definition for $id</A>"
      puts $fidx "<TR><TD>$id</TD><TD><A HREF=\"$id/[tidyname $id]-streamdef.html\">Edit</A></TD><TD>
<A HREF=\"$id/[tidyname $id]-metadata.html\">Edit</A></TD><TD><A HREF=\"sal-generator-$system.html\">Setup</A></TD></TR>"
      dogen $fgen $id
      dometa $id
   }
   doitem $nid $fout [lindex $d end] [lindex $rec 2] [lindex $rec 1]
   incr nid 1
  }
}

doitem $nid $fout "" int 1
dogen $fgen $id
catch {
  puts $fout "</TABLE><P>Click here to update: <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
  close $fout
}

catch {
 puts $fidx "</TABLE><P><HR><P>
<H2>MetaData management</H2>
<P><UL>
<A HREF=\"metadata-units.html\">Edit the set of known units and datatypes</A></UL><BR>"
 puts $fidx "</BODY></HTML>"
 close $fidx
}

puts $fgen "</TABLE>
<P><HR>
<P>
Select the required language product(s) for code generation
<P>
<INPUT TYPE=\"checkbox\" NAME=\"langc\" VALUE=\"yes\" CHECKED>Generate C++ library and sample applications<BR>
<INPUT TYPE=\"checkbox\" NAME=\"langjava\" VALUE=\"yes\">Generate Java classes and sample applications <BR>
<INPUT TYPE=\"checkbox\" NAME=\"langlv\" VALUE=\"yes\">Generate Labview library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"langpy\" VALUE=\"yes\">Generate Python wrapper and sample applications<BR>
<INPUT TYPE=\"checkbox\" NAME=\"langruby\" VALUE=\"yes\">Generate Ruby wrapper and sample applications<BR>
<INPUT TYPE=\"checkbox\" NAME=\"langxml\" VALUE=\"yes\">Generate XML for use with Enterprise Architect <BR>
<P><HR><P>
<P>
Select the required middleware transport(s) for code generation
<P>
<INPUT TYPE=\"checkbox\" NAME=\"mw_ice\" VALUE=\"yes\">Generate ICE SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_ndds\" VALUE=\"yes\">Generate RTI NDDS SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_orte\" VALUE=\"yes\">Generate ORTE RTPS SAL  library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_activemq\" VALUE=\"yes\">Generate ActiveMQ SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_test\" VALUE=\"yes\" CHECKED>Generate test stub SAL library<BR>
<P><HR>
<P>Click here to generate code : <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
close $fgen

#
# do fgen for each system on its own
# 
foreach s [array names MSYS] {
catch {unset doneit}
set fgen [open sal-generator-$s.html w]
puts $fgen "<HTML><HEAD><TITLE>Software Abstraction Layer API generator</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"salg.gif\" ALIGN=CENTER><P><HR><P>
<H1>Datastream and command capabilties</H1>
<H2>$s</H2><P><HR><P>
Use the checkboxes in the form to select the combination<BR>
of telemetry datastreams for which the application requires<BR>
read and/or write access, and the command streams upon<BR>
which commands need to be issued or processed.<P>
<FORM action=\"/cgi-bin/salgenerator\" method=\"post\">
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Stream Name</TD><TD>Subscribe</TD><TD>Publish</TD><TD>Issue Command</TD>
<TD>Process Comamnd</TD></B></TR>"

set nid 1
set fin [open $SAL_WORK_DIR/.salwork/datastreams.detail r]
while { [gets $fin rec] > -1 } {
   set d [split [lindex $rec 0] "./"]
   set id [join [lrange $d 0 [expr [llength $d]-2]] .]
   set topic [join [lrange $d 0 [expr [llength $d]-2]] _]
   if { [lindex $d 0] == $s } {
    if { [info exists doneit($id)] == 0 } {
      dogen $fgen $id
      set doneit($id) 1
      puts stdout "Done $id"
      incr nid 1
    }
   }
}
close $fin

puts $fgen "</TABLE>
<P><HR>
<P>
Select the required language product(s) for code generation
<P>
<INPUT TYPE=\"checkbox\" NAME=\"langc\" VALUE=\"yes\" CHECKED>Generate C++ library and sample applications<BR>
<INPUT TYPE=\"checkbox\" NAME=\"langjava\" VALUE=\"yes\">Generate Java classes and sample applications <BR>
<INPUT TYPE=\"checkbox\" NAME=\"langlv\" VALUE=\"yes\">Generate Labview library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"langpy\" VALUE=\"yes\">Generate Python wrapper and sample applications<BR>
<INPUT TYPE=\"checkbox\" NAME=\"langruby\" VALUE=\"yes\">Generate Ruby wrapper and sample applications<BR>
<INPUT TYPE=\"checkbox\" NAME=\"langxml\" VALUE=\"yes\">Generate XML for use with Enterprise Architect <BR>
<P><HR><P>
<P>
Select the required middleware transport(s) for code generation
<P>
<INPUT TYPE=\"checkbox\" NAME=\"mw_ice\" VALUE=\"yes\">Generate ICE SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_ndds\" VALUE=\"yes\">Generate RTI NDDS SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_orte\" VALUE=\"yes\">Generate ORTE RTPS SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_activemq\" VALUE=\"yes\">Generate ActiveMQ SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_test\" VALUE=\"yes\" CHECKED>Generate test stub SAL library<BR>
<P><HR>
<P>Click here to generate code : <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
close $fgen
}


catch { close $fout }
catch { close $fmet }
catch { close $fps }
catch { close $fidx }
catch { close $fgen }
catch { close $fin }



