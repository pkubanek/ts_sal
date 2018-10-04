#!/usr/bin/env tclsh

proc tidyname { f } { 
  return [join [split $f .] _]
}

proc dodbsim { fid id nid } {
   puts $fid "<TR><TD>$id<INPUT NAME=\"dbsim_stream$nid\" TYPE=\"HIDDEN\" VALUE=\"$id\"></TD>
<TD><INPUT TYPE=\"checkbox\" NAME=\"dbsim_tlm$nid\" VALUE=\"yes\"></TD>
<TD><INPUT TYPE=\"checkbox\" NAME=\"dbsim_cmd$nid\" VALUE=\"yes\"></TD>
<TD><INPUT TYPE=\"checkbox\" NAME=\"dbsim_log$nid\" VALUE=\"yes\"></TD></TR>"
}



set scriptdir $env(SAL_DIR)
source $scriptdir/streamutils.tcl
source $scriptdir/add_system_dictionary.tcl
catch {unset MSYS}
set MSYS [lsort [split [exec cat $SAL_DIR/datastreams.names] \n]]]
foreach id $MSYS {
   set SYS([lindex [split $id _] 0]) 1
}

exec mkdir -p html/dbsimulate
set fall [open html/dbsimulate/index-dbsimulate.html w]
puts $fall "<HTML><HEAD><TITLE>Stream facility database simulation</TITLE></HEAD>
<BODY BGCOLOR=White>
<IMG SRC=\"LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"dbsim.gif\" ALIGN=CENTER><P><HR><P>
<H2>Stream Facility Database simulation</H2><P><UL><UL>
<FORM><TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=200>
<TR BGCOLOR=Yellow><B><TD>Stream Name</TD></TR>"


foreach subsystem $TSUBSYSTEMS {

set nid 1
puts $fall "<TR><TD><A HREF=\"index-dbsimulate-$subsystem.html\">$subsystem</A></TD></TR>"

set fidx [open html/dbsimulate/index-dbsimulate-$subsystem.html w]
puts $fidx "<HTML><HEAD><TITLE>Stream facility database simulation</TITLE></HEAD>
<BODY BGCOLOR=White>
<IMG SRC=\"LSST_logo.gif\" ALIGN=CENTER>
<IMG SRC=\"dbsim.gif\" ALIGN=CENTER><P><HR><P>
<H2>Stream Facility Database simulation - $subsystem</H2><P>
<FORM action=\"/cgi-bin/simulatefacility\" method=\"post\">

<TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightBlue  WIDTH=600>
<TR BGCOLOR=Yellow><B><TD>Stream Name</TD><TD>Simulate telemetry</TD><TD>Simulate commands</TD>
<TD>Simulate logging/alerts</TD></B></TR>"

foreach id $MSYS {
   if { [lindex [split $id _] 0] == $subsystem } {
     dodbsim $fidx $id $nid
     incr nid 1
   }
}


puts $fidx "</TABLE><P><HR><P>
<INPUT NAME=\"dbsim_numstreams\" TYPE=\"HIDDEN\" VALUE=\"$nid\">

Select the required period for data simulation.
<P>Start time : Year 
<SELECT NAME=\"dbsim_starty\">
<OPTION VALUE=\"2008\">2008
<OPTION VALUE=\"2009\">2009
<OPTION VALUE=\"2010\">2010
<OPTION VALUE=\"2011\">2011
<OPTION VALUE=\"2012\">2012
<OPTION VALUE=\"2013\">2013
<OPTION VALUE=\"2014\">2014
<OPTION VALUE=\"2015\">2015
<OPTION VALUE=\"2016\">2016
<OPTION VALUE=\"2017\">2017
<OPTION VALUE=\"2018\">2018
<OPTION VALUE=\"2019\">2019
<OPTION VALUE=\"2020\">2020
<OPTION VALUE=\"2021\">2021
<OPTION VALUE=\"2022\">2022
<OPTION VALUE=\"2023\">2023
</SELECT>
Month <INPUT NAME=\"dbsim_startmon\" SIZE=4 VALUE=\"01\">
Day <INPUT NAME=\"dbsim_startday\" SIZE=4 VALUE=\"01\">
Hour <INPUT NAME=\"dbsim_starthour\" SIZE=4 VALUE=\"00\">
Minute <INPUT NAME=\"dbsim_startmin\" SIZE=4 VALUE=\"00\">
Second <INPUT NAME=\"dbsim_startsec\" SIZE=4 VALUE=\"00\">
<BR>
<P>End time : Year 
<SELECT NAME=\"dbsim_endy\">
<OPTION VALUE=\"2008\">2008
<OPTION VALUE=\"2009\">2009
<OPTION VALUE=\"2010\">2010
<OPTION VALUE=\"2011\">2011
<OPTION VALUE=\"2012\">2012
<OPTION VALUE=\"2013\">2013
<OPTION VALUE=\"2014\">2014
<OPTION VALUE=\"2015\">2015
<OPTION VALUE=\"2016\">2016
<OPTION VALUE=\"2017\">2017
<OPTION VALUE=\"2018\">2018
<OPTION VALUE=\"2019\">2019
<OPTION VALUE=\"2020\">2020
<OPTION VALUE=\"2021\">2021
<OPTION VALUE=\"2022\">2022
<OPTION VALUE=\"2023\">2023

</SELECT>
Month <INPUT NAME=\"dbsim_endmon\" SIZE=4 VALUE=\"01\">
Day <INPUT NAME=\"dbsim_endday\" SIZE=4 VALUE=\"01\">
Hour <INPUT NAME=\"dbsim_endhour\" SIZE=4 VALUE=\"00\">
Minute <INPUT NAME=\"dbsim_endmin\" SIZE=4 VALUE=\"00\">
Second <INPUT NAME=\"dbsim_endsec\" SIZE=4 VALUE=\"00\">
<P>


<INPUT TYPE=\"radio\" NAME=\"dbsim_type\" VALUE=\"sql\" checked>Generate sql dump archive<BR>
<INPUT TYPE=\"radio\" NAME=\"dbsim_type\" VALUE=\"rt\">Generate Real-time data<BR>
<P><HR><P>

<INPUT TYPE=\"radio\" NAME=\"dbsim_type\" VALUE=\"db\">Insert into database<BR>
Hostname : <INPUT NAME=\"dbsim_host\" SIZE=16 VALUE=\"\">
 Username : <INPUT NAME=\"dbsim_user\" SIZE=16 VALUE=\"\"><BR>
 Password : <INPUT NAME=\"dbsim_pass\" TYPE=\"password\" SIZE=16 VALUE=\"\">
 Database : <INPUT NAME=\"dbsim_name\" SIZE=16 VALUE=\"lsstFacility\">
<P><HR><P>
<P><HR>
<P>Click here to generate simulation : <input type=\"submit\" value=\"Submit\" name=\"update\"></FORM><P></BODY></HTML>"
close $fidx

}

puts $fall "</TABLE><P><HR><P></BODY></HTML>"
close $fall


