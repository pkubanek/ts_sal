#!/usr/bin/tclsh

proc printformdata { } {
global env FormData
   foreach i [lsort [array names env]] {
       puts stdout "Env $i = $env($i)<BR>"
  }
   foreach i [lsort [array names FormData]] {
       puts stdout "Form $i = $FormData($i)<BR>"
  }
}

proc makestreamid { name } {
  return [join [split $name .] _]
}


source /opt/lsstsal/scripts/GetPostedData.tcl
source /opt/lsstsal/scripts/versioning.tcl
source /opt/lsstsal/scripts/datastream_desc.tcl
source /opt/lsstsal/scripts/camera-subsysdesc.tcl

GetPostedData
puts stdout "Content-type: text/html\n\n"
if { [info exists FormData(DEBUG)] } {
  puts stdout "<HTML><HEAD></HEAD><BODY>"
  printformdata
}

set STREAMS "[array names SDESC] [array names DESC]"

if { [info exists JUSTTESTING] } {
   set FormData(sub_system.Computer_status) yes
   set FormData(pub_system.Computer_status) yes
   set FormData(issue_system.Computer_status) yes
   set FormData(proc_system.Computer_status) yes
   set FormData(langc) yes
   set FormData(mw_test) yes
}


foreach s $STREAMS {
  if { [info exists FormData(sub_$s)] }   {set TSUBS($s) yes}
  if { [info exists FormData(pub_$s)] }   {set TPUBS($s) yes}
  if { [info exists FormData(issue_$s)] } {set TISSU($s) yes}
  if { [info exists FormData(proc_$s)] }  {set TPROC($s) yes}     
}

foreach i [array names TSUBS] {set SUBS([makestreamid $i]) yes}
foreach i [array names TPUBS] {set PUBS([makestreamid $i]) yes}
foreach i [array names TISSU] {set ISSU([makestreamid $i]) yes}
foreach i [array names TPROC] {set PROC([makestreamid $i]) yes}

if { [info exists FormData(langc)] }    {source /opt/lsstsal/scripts/salgenerator-c.tcl}
if { [info exists FormData(langjava)] } {source /opt/lsstsal/scripts/salgenerator-java.tcl}
if { [info exists FormData(langpy)] }   {source /opt/lsstsal/scripts/salgenerator-python.tcl}
if { [info exists FormData(langruby)] } {source /opt/lsstsal/scripts/salgenerator-ruby.tcl}
if { [info exists FormData(langxml)] }  {source /opt/lsstsal/scripts/salgenerator-xml.tcl}



puts stdout "</BODY></HTML>"



