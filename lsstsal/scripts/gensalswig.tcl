#!/usr/bin/tclsh
#
# Generate SALDDS swig input file
# 
# To test : 
#   set SAL_DIR $env(SAL_DIR)
#   set SAL_WORK_DIR $env(SAL_WORK_DIR)
#   set subsys camera
#   source $SAL_WORK_DIR/idl-templates/validated/[set subsys]_cmddef.tcl
#   source $SAL_WORK_DIR/idl-templates/validated/[set subsys]_evtdef.tcl
#   gensalswig $subsys
#

source $env(SAL_DIR)/utilities.tcl
source $env(SAL_DIR)/gencmdaliascode.tcl
source $env(SAL_DIR)/geneventaliascode.tcl


proc addSALDDSswig { idlfile base } {
global SAL_DIR SAL_WORK_DIR SYSDIC
  puts stdout "Configuring [set base]/python/SAL_[set base].i"
  set atypes $idlfile
  set finh [open $SAL_DIR/code/templates/SALDDS.i.template r]
  set fouth [open [set base]/python/SAL_[set base].i w]
  set rec ""
  while { [string range $rec 0 21] != "// INSERT TYPE SUPPORT" } {
     if { [string range $rec 0 22] == "// INSERT TYPE INCLUDES" } {
       puts $fouth "  #include \"ccpp_sal_[lindex [split $base _] 0].h\""
       gets $finh rec ; puts $fouth $rec
     } else {
       gets $finh rec
       puts $fouth $rec
     }
  }
  foreach i $atypes {
       set ptypes [split [exec grep pragma $i] \n]
           foreach j $ptypes {
              set name [lindex $j 2]        
               puts $fouth "
      salReturn putSample_[set name]([set base]_[set name]C *data);
      salReturn getSample_[set name]([set base]_[set name]C *data);
      salReturn getNextSample_[set name]([set base]_[set name]C *data);
"
       }
  }
  gencmdaliascode $base include $fouth
  geneventaliascode $base include $fouth
  while { [gets $finh rec] > -1 } {puts $fouth $rec}
  close $finh
  close $fouth
}

proc gensalswig { base } {
global SAL_WORK_DIR
  addSALDDSswig $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set base].idl $base
  set frep [open /tmp/sreplace3.sal w]
  puts $frep "#!/bin/sh"
  puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set base]/python/SAL_[set base].i"
  close $frep
  exec chmod 755 /tmp/sreplace3.sal
  catch { set result [exec /tmp/sreplace3.sal] } bad
}

