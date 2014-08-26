
set vfiles [glob /usr/local/scritpts/*_version.tcl]
foreach f $vfiles {
  source $f
}
