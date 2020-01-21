#!/usr/bin/env tclsh

set SAL_DIR $env(SAL_DIR)
set OSPL_HOME $env(OSPL_HOME)
foreach o "validate efd writers code compile cpp idl isocpp java jni lib link maven tcl db icd labview python pydds html rpm sal s
hmem sim simd verbose fastest" {
  set OPTIONS($o) 0
  if { [lsearch [string tolower $argv] $o] > -1 } {
     set OPTIONS($o) 1
  }
}
source $SAL_DIR/versioning.tcl
source $SAL_DIR/utilities.tcl
source $SAL_DIR/activaterevcodes.tcl
source $SAL_DIR/add_system_dictionary.tcl
source $SAL_DIR/gensimplesample.tcl
source $SAL_DIR/gensalcodes.tcl
source $SAL_DIR/activaterevcodes.tcl

set DONE_CMDEVT 0

puts stdout " Now do 
  checkTopicTypes subsys
  source $SAL_WORK_DIR/idl-templates/validated/[set subsys]_revCodes.tcl
"


