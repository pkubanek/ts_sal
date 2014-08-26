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


source /usr/local/scripts/tcl/versioning.tcl
source /usr/local/scripts/tcl/datastream_desc.tcl
source /usr/local/scripts/tcl/camera-subsysdesc.tcl


set STREAMS "[array names SDESC] [array names DESC]"

set basename $argv
set all [glob $basename*.idl]
set topiclist ""
foreach t [lsort $all] {
   lappend topiclist [file rootname $t]
}

foreach id $topiclist {
   set FormData(sub_$id) yes
   set FormData(pub_$id) yes
   set FormData(issue_$id) yes
   set FormData(proc_$id) yes
}

set FormData(langc) yes
set FormData(langlv) yes
set FormData(mw_test) yes
set FormData(mw_ndds) yes

foreach s $STREAMS {
  set id [join [split $s .] _]
  if { [info exists FormData(sub_$id)] }   {set TSUBS($id) yes}
  if { [info exists FormData(pub_$id)] }   {set TPUBS($id) yes}
  if { [info exists FormData(issue_$id)] } {set TISSU($id) yes}
  if { [info exists FormData(proc_$id)] }  {set TPROC($id) yes}     
}

foreach i [array names TSUBS] {set SUBS([makestreamid $i]) yes}
foreach i [array names TPUBS] {set PUBS([makestreamid $i]) yes}
foreach i [array names TISSU] {set ISSU([makestreamid $i]) yes}
foreach i [array names TPROC] {set PROC([makestreamid $i]) yes}

set basedir /home/shared/lsst/tests/api/streams
set FormData(workingDir) /home/shared/lsst/tests/api/streams


if { [info exists FormData(langc)] }    {source /usr/local/scripts/tcl/salgenerator-c.tcl}
if { [info exists FormData(langjava)] } {source /usr/local/scripts/tcl/salgenerator-java.tcl}
if { [info exists FormData(langpy)] }   {source /usr/local/scripts/tcl/salgenerator-python.tcl}
if { [info exists FormData(langruby)] } {source /usr/local/scripts/tcl/salgenerator-ruby.tcl}
if { [info exists FormData(langxml)] }  {source /usr/local/scripts/tcl/salgenerator-xml.tcl}

