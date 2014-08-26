
set scriptdir /usr/local/scripts/tcl

source $scriptdir/genshmempersubsys.tcl

set stagingdir /tmp/salgenerator/lsst_SAL_c_$basename
set scriptdir /usr/local/scripts/tcl

catch { exec rm -fr $stagingdir }
catch { exec mkdir -p $stagingdir }
set AFILES [glob $workdir/*]

cd $stagingdir
foreach f $AFILES {
  exec cp -r $f .
}
cd ..
exec rm -fr lsstsal.$SALVERSION
exec mkdir -p lsstsal.$SALVERSION/lib
set LFILES [glob lsst_SAL_c_$basename/lib*]
foreach f $LFILES {
  exec mv $f lsstsal.$SALVERSION/lib/.
}


exec tar czf lsst_SAL_c_$basename.tar.gz lsst_SAL_c_$basename lsstsal.$SALVERSION
exec cp lsst_SAL_c_$basename.tar.gz /var/www/html/downloads/salcode/.

puts stdout "<P><HR><P>
<H2>Software Abstraction Layer - Downloads</H2>
This archive contains a SAL library and test programs.<P><UL>"
if { [array names SUBS] != "" } {
   puts stdout "Tests subscription for :
<UL>"
   foreach s [array names SUBS] {
      puts stdout "<LI>$s"
   }
   puts stdout "</UL>"
}

if { [array names PUBS] != "" } {
   puts stdout "Tests publishing for :
<UL>"
   foreach s [array names PUBS] {
      puts stdout "<LI>$s"
   }
   puts stdout "</UL>"
}

if { [array names ISSU] != "" } {
   puts stdout "Tests commanding for :
<UL>"
   foreach s [array names ISSU] {
      puts stdout "<LI>$s"
   }
   puts stdout "</UL>"
}

if { [array names PROC] != "" } {
   puts stdout "Tests command processing for :
<UL>"
   foreach s [array names PROC] {
      puts stdout "<LI>$s"
   }
   puts stdout "</UL>"
}

puts stdout "</UL><P><TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightGreen  WIDTH=400>
<TR><TD>Archive size</TD><TD>[file size /var/www/html/downloads/salcode/lsst_SAL_c_$basename.tar.gz] bytes</TD></TR>
<TR><TD>Archive type</TD><TD>Gzip compressed Tar format</TD></TR>
<TR><TD>Language</TD><TD>C (GCC compiler compatible)</TD></TR>
<TR><TD>Download link</TD><TD><A HREF=\"/downloads/salcode/lsst_SAL_c_$basename.tar.gz\">lsst_SAL_c_$basename.tar.gz</A></TD></TR>
</TABLE>
<P><HR><P>"
if { [info exists FormData(mw_ndds)] } {
puts stdout "This archive contains C/C++/Java bindings for RTI NDDS,<BR>
sample code, documentation and runtime libraries"
puts stdout "<P><TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightGreen  WIDTH=400>
<TR><TD>Archive size</TD><TD>[file size /var/www/html/downloads/ndds.tar.gz] bytes</TD></TR>
<TR><TD>Archive type</TD><TD>Gzip compressed Tar format</TD></TR>
<TR><TD>Language</TD><TD>C/C++/Java (GCC compiler compatible, Sun JVM)</TD></TR>
<TR><TD>Download link</TD><TD><A HREF=\"/downloads/ndds.tar.gz\">ndds.tar.gz</A></TD></TR>
</TABLE>
<P><HR><P>"
}

if { [info exists FormData(mw_orte)] } {
puts stdout "This archive contains the ORTE Real-time-publish-subscribe distribution."
puts stdout "<P><TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightGreen  WIDTH=400>
<TR><TD>Archive size</TD><TD>[file size /var/www/html/downloads/orte.tar.gz] bytes</TD></TR>
<TR><TD>Archive type</TD><TD>Gzip compressed Tar format</TD></TR>
<TR><TD>Language</TD><TD>C/C++ (GCC compiler compatible)</TD></TR>
<TR><TD>Download link</TD><TD><A HREF=\"/downloads/orte.tar.gz\">orte.tar.gz</A></TD></TR>
</TABLE>
<P><HR><P>"
}

if { [info exists FormData(mw_activemq)] } {
puts stdout "This archive contains the C++ interface for ActiveMQ."
puts stdout "<P><TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightGreen  WIDTH=400>
<TR><TD>Archive size</TD><TD>[file size /var/www/html/downloads/activemq.tar.gz] bytes</TD></TR>
<TR><TD>Archive type</TD><TD>Gzip compressed Tar format</TD></TR>
<TR><TD>Language</TD><TD>C/C++ (GCC compiler compatible)</TD></TR>
<TR><TD>Download link</TD><TD><A HREF=\"/downloads/activemq.tar.gz\">activemq.tar.gz</A></TD></TR>
</TABLE>
<P><HR><P>"
}







