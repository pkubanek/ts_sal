#!/usr/bin/env tclsh


proc migrateEFDtable { subsys topic } {
   source /opt/lsst/ts_sal/scripts/[set subsys]_revCodes.tcl
   set tname [set topic]
   catch {
      catch {set res1 [exec echo "select * from $tname limit 1" | mysql -sN EFD]} ok
      if { [lrange $ok 0 1] == "ERROR 1146" } {
        puts stdout "Creating new table for $tname"
        set res3 [exec mysql EFD < /opt/lsst/ts_sal/sql/[set tname].sqldef]
        return
      }
      if { $res1 == "" } {
        puts stdout "DROP and recreate empty table $tname"
        set res2 [exec echo "DROP TABLE IF EXISTS $tname;" | mysql EFD]
        set res3 [exec mysql EFD < /opt/lsst/ts_sal/sql/[set tname].sqldef]
        return
      }
      set hash [lindex $res1 2]
      if  { $hash != $REVCODE([set tname]) } {
          puts stdout "Migrating $tname to $tname_[set hash]"
          set res2 [exec echo "RENAME $tname TO $tname_[set hash];" | mysql EFD]
          set res3 [exec mysql EFD < /opt/lsst/ts_sal/sql/[set tname].sqldef]
      } else { 
          puts stdout "No migration required for $tname"
      }
   }
}


set all [glob /opt/lsst/ts_sal/sql/*.sqldef]
foreach t $all {
    set subsys [lindex [split [file tail $t] "._"] 0]
    set topic [lindex [split [file tail $t] "."] 0]
    migrateEFDtable $subsys $topic
}
