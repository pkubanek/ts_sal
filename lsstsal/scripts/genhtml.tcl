#!/usr/bin/env tclsh

proc dometa { id } {
global SDESC UDESC QDESC SAL_WORK_DIR
   set system [lindex [split $id "_."] 0]
   exec mkdir -p $SAL_WORK_DIR/html/salgenerator/$system
   set fmet [open $SAL_WORK_DIR/html/salgenerator/$system/[tidyname $id]-metadata.html w]
   puts $fmet "<HTML><HEAD><TITLE>Stream definition editor - $id</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"../LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"../dde.gif\" ALIGN=CENTER><P><HR><P>
<H1>Stream $id MetaData</H1><P>"
      if { [info exists SDESC($id)] == 0 } {
           puts stderr "No SDESC for $id"
           set SDESC($id) "Detail : unknown"
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
set SAL_WORK_DIR $env(SAL_WORK_DIR)
exec mkdir -p $SAL_WORK_DIR/html/salgenerator

source $scriptdir/add_system_dictionary.tcl
source $scriptdir/checkdesc.tcl
source $scriptdir/comments.tcl
source $scriptdir/streamutils.tcl
pubsubs

set SYSTEMS ""
set fidx [open $SAL_WORK_DIR/html/salgenerator/index-streamdef.html w]
puts $fidx "<HTML><HEAD><TITLE>Stream definition editor index</TITLE></HEAD>
<BODY BGCOLOR=White>
<IMG SRC=\"LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"dde.gif\" ALIGN=CENTER><P><HR><P>
<H2>Create a new Datastream</H2><P>
<FORM action=\"/cgi-bin/streamdef\" method=\"post\">
<P>Copy item list from named datastream (optional) : 
<select name=\"copy\"><option value=\" \" selected>"

foreach s [liststreams] {
  puts $fidx "<option value=\"$s\">$s"
}


puts $fidx "</select>
<P>Name of new datastream definition: 
<select name=\"system\"><option value=\"?\" selected>"
foreach s $SYSDIC(systems) {
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

set fgen [open $SAL_WORK_DIR/html/salgenerator/sal-generator.html w]
puts $fgen "<HTML><HEAD><TITLE>Service Abstraction Layer API generator</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"salg.gif\" ALIGN=CENTER><P><HR><P>
<H1>Datastream and command capabilties</H1><P><HR><P>
Use the checkboxes in the form to select the combination<BR>
of subsystems for which the application requires<BR>
read and/or write access, and the command streams upon<BR>
which commands need to be issued or processed.<P>
<FORM action=\"/cgi-bin/salgenerator\" method=\"post\">
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Stream Name</TD><TD>Subscribe</TD><TD>Publish</TD><TD>Issue Command</TD>
<TD>Process Comamnd</TD></B></TR>"

set nid 0
set last ""
set fin [open $SAL_WORK_DIR/.salwork/datastreams.detail r]
while { [gets $fin rec] > -1 } {
  set cmdresp [lindex [split $rec "_ "] 1]
  if { $cmdresp != "command" && $cmdresp != "ackcmd" && $cmdresp != "logevent" } {
   set d [split [lindex $rec 0] "./_"]
   set id [join [lrange $d 0 1] .]
   if { $id == "" } {set id [lindex $rec 0]}
   set aname [lindex $rec 1]
   set FREQUENCY($id) [lindex $rec 4]
   set system [lindex $d 0]
   set asize [lindex $rec 2]
   set atype [lindex $rec 3]
   set topic [join $d .]
   if { $id != $last && [lsearch $TSUBSYSTEMS $system] > -1 } {
      catch { doitem $nid $fout "" 1 int
              puts $fout "</TABLE><P>Click here to update: <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
              close $fout
              puts stdout "Done $last"
            }
      set last $id
#      exec mkdir -p $system
      puts stdout "Creating $system/[tidyname $id] stream editor" 
      exec mkdir -p $SAL_WORK_DIR/html/salgenerator/$system
      set fout [open $SAL_WORK_DIR/html/salgenerator/$system/[tidyname $id]-streamdef.html w]
      set nid 1
      set CSYS $id
      puts $fout "<HTML><HEAD><TITLE>Stream definition editor - $id</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"../LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"../dde.gif\" ALIGN=CENTER><P><HR><P>
<H1>Stream $id</H1><P><H2>Description</H2>"
      if { [info exists SYSDIC($id,title)] == 0 } {
          puts stderr "***WARNING*** No entry in system dictionary for $id"
          set SYSDIC($id,title) $id
      }
      puts $fout "$SYSDIC($id,title)<P>"
      if { [info exists SDESC($id)] == 0 } {
           puts stderr "***WARNING*** No detailed description (SDESC) for $id"
           set SDESC($id) "Detail : unknown"
      }
      puts $fout "Detail : $SDESC($id)<HR><P>"
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
      puts $fidx "<TR><TD>$id</TD><TD><A HREF=\"[tidyname $id]-streamdef.html\">Edit</A></TD><TD>
<A HREF=\"[tidyname $id]-metadata.html\">Edit</A></TD><TD><A HREF=\"sal-generator-$system.html\">Setup</A></TD></TR>"
      dometa $id
   }
   doitem $nid $fout $aname $asize $atype
   incr nid 1
  }
}

doitem $nid $fout "" 1 int

foreach sname $TSUBSYSTEMS {
   set id [join [split $sname "_"] "."]
   dogen $fgen $id
}
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
<INPUT TYPE=\"checkbox\" NAME=\"langxml\" VALUE=\"yes\">Generate XML for use with Enterprise Architect <BR>
<P><HR><P>
<P>
Select the required middleware transport(s) for code generation
<P>
<INPUT TYPE=\"checkbox\" NAME=\"mw_test\" VALUE=\"yes\" CHECKED>Generate shmem SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_opensplice\" VALUE=\"yes\">Generate OpenSplice DDS SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_opendds\" VALUE=\"yes\">Generate OpenDDS SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_coredx\" VALUE=\"yes\">Generate CoreDX DDS SAL library<BR>
<P><HR>
<P>Click here to generate code : <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
close $fgen

#
# do fgen for each system on its own
# 
puts stdout "*************TSUBSYSTEMS is $TSUBSYSTEMS"
foreach s $TSUBSYSTEMS {
catch {unset doneit}
set fgen [open $SAL_WORK_DIR/html/salgenerator/sal-generator-$s.html w]
puts stdout "Creating sal-generator-$s form"
puts $fgen "<HTML><HEAD><TITLE>Service Abstraction Layer API generator</TITLE></HEAD>
<BODY BGCOLOR=White><H1>
<IMG SRC=\"LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"salg.gif\" ALIGN=CENTER><P><HR><P>
<H1>Datastream and command capabilties</H1>
<H2>$s</H2><P><HR><P>
Use the checkboxes in the form to select the combination<BR>
of telemetry datastreams for which the application requires<BR>
read and/or write access.<P>
<FORM action=\"/cgi-bin/salgenerator\" method=\"post\">
<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Stream Name</TD><TD>Subscribe</TD><TD>Publish</TD></B></TR>"


foreach sname [liststreams $s] {
#   set id [join [split $sname "_"] "."]
   set id $sname
   dogen $fgen $id no
   puts stdout "Added sal-generator-$id to form"
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
<INPUT TYPE=\"checkbox\" NAME=\"langxml\" VALUE=\"yes\">Generate XML for use with Enterprise Architect <BR>
<P><HR><P>
<P>
Select the required middleware transport(s) for code generation
<P>
<INPUT TYPE=\"checkbox\" NAME=\"mw_test\" VALUE=\"yes\" CHECKED>Generate shmem SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_opensplice\" VALUE=\"yes\">Generate OpenSplice DDS SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_opendds\" VALUE=\"yes\">Generate OpenDDS SAL library<BR>
<INPUT TYPE=\"checkbox\" NAME=\"mw_coredx\" VALUE=\"yes\">Generate CoreDX DDS SAL library<BR>
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



