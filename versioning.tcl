
set vfiles [glob /opt/lsstsal/scripts/*_version.tcl]
foreach f $vfiles {
  source $f
}
