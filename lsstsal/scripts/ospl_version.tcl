set OSPL_HDE $env(OSPL_HOME)
set ospl [lsearch [split $OSPL_HDE) "/"] OpenSpliceDDS]
set OSPL_VERSION [string trim [lindex [split $OSPL_HDE) "/"]  5] V]
set l  [llength [split $OSPL_VERSION .]]
if { $l == 2 } {set OSPL_VERSION $OSPL_VERSION.0}
set SIMD_BASE_DIR /opt/simd
set DDSGEN "$OSPL_HDE/bin/idlpp -I $OSPL_HDE/etc/idl"


