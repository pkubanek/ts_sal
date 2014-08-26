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


source /usr/local/scripts/tcl/GetPostedData.tcl
source /usr/local/scripts/tcl/streamdesc.tcl

GetPostedData
puts stdout "Content-type: text/html\n\n"
if { $FormData(DEBUG) == 1 } {
  puts stdout "<HTML><HEAD></HEAD><BODY>"
  printformdata
}

set STREAMS [array names SDESC]
set SUBS ""
set PUBS ""
set ISSU ""
set PROC ""

if { $JUSTTESTING } {
   set FormData(sub_system.Computer_status) yes
   set FormData(pub_system.Computer_status) yes
   set FormData(issue_system.Computer_status) yes
   set FormData(proc_system.Computer_status) yes
   set FormData(langc) yes
   set FormData(mw_test) yes
}


foreach s $STREAMS {
  if { [info exists FormData(sub_$s)] }   {lappend SUBS $s}
  if { [info exists FormData(pub_$s)] }   {lappend PUBS $s}
  if { [info exists FormData(issue_$s)] } {lappend ISSU $s}
  if { [info exists FormData(proc_$s)] }  {lappend PROC $s}     
}

if { [info exists FormData(langc)] }    {source /usr/local/scripts/tcl/salgenerator-c.tcl}
if { [info exists FormData(langjava)] } {source /usr/local/scripts/tcl/salgenerator-java.tcl}
if { [info exists FormData(langpy)] }   {source /usr/local/scripts/tcl/salgenerator-python.tcl}
if { [info exists FormData(langruby)] } {source /usr/local/scripts/tcl/salgenerator-ruby.tcl}
if { [info exists FormData(langxml)] }  {source /usr/local/scripts/tcl/salgenerator-xml.tcl}



puts stdout "</BODY></HTML>"
