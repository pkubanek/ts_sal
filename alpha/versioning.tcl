
set vfiles [glob /usr/local/scripts/tcl/*_version.tcl]
foreach f $vfiles {
  source $f
}
