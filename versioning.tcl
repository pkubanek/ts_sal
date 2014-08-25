
set vfiles [glob $SAL_DIR/*_version.tcl]
foreach f $vfiles {
  source $f
}
