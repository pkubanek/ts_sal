#!/usr/bin/tclsh

exec tar xvzf icd-support.tgz
set SUBS "auxscope calibration camera enclosure dm environment lasercal m1m3 m2 mount network ocs power seeing_dimm seeing_mass skycam tcs"


foreach s $SUBS {
  set all [glob $s.*/*]
  foreach i $all {
     exec mv $i $s/.
  }
  set alld [glob $s.*]
  foreach d $alld {
    exec rmdir $d
  }
}



