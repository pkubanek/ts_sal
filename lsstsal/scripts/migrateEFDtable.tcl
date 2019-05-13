#!/usr/bin/env tclsh


proc migrateEFDtable { subsys tname } {
   source /opt/lsst/ts_sal/scripts/[set subsys]_revCodes.tcl
   catch {
      set res1 [exec echo "select * from $tname limit 1" | mysql -sN EFD]
      set hash [lindex $res 2]
      set res2 [exec echo "RENAME $tname TO $tname_[set hash];" | mysql EFD]
      set res3 [exec mysql EFD < /opt/lsst/ts_sal/sql/[set tname].sqldef]
   }
}


