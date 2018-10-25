#!/usr/bin/env tclsh

source $env(SAL_DIR)/sal_version.tcl 

proc generategenerics { subsys } {
global SALVERSION
  exec cp SALGenerics.xml [set subsys]_Generics.xml
  set fout [open /tmp/salgenerics w]
  puts $fout "perl -pi -w -e 's/SALGeneric/$subsys/g;' [set subsys]_Generics.xml"
  puts $fout "perl -pi -w -e 's/SALVersion/$SALVERSION/g;' [set subsys]_Generics.xml"
  close $fout
  exec chmod 755 /tmp/salgenerics
  exec /tmp/salgenerics
}


