proc writesql { topic } {
global SQLREC TYPEFORMAT
  set flds [split $SQLREC($topic) ,]
  set record "sprintf(thequery,\"INSERT INTO [set topic] VALUES (\"
  set rformat ""
  set rvars ""
  while { [llength $flds] != 0 } {
      set i [lindex $flds 0]
      set flds [lrange $flds 1 end]
      set type [lindex [split $i .] 0]
      set name [lindex [split $i .] 1]
      set isarray [lindex [split $i .] 2]
puts stdout "$i $type $name $isarray"
          if { $isarray == "" } {
              set value "SALInstance.[set name]"
              set vform $TYPEFORMAT($type)
          } else {
             set value ""
             set vform ""
             set j 0
             while { $j <= $isarray } {
                set value "$value,SALInstance.[set name]\[$i\]"
                set vform "$vform,$TYPEFORMAT($type)"
                incr j 1
             }
             set value [string trim $astr ","]
          }
      set rvars "$rvars ,$value"
      set rformat "$rformat,$vform"
puts stdout $rvars
puts stdout $rformat
  }
  set record "$record [set rformat] \" , $rvars );"
  return $record
}



source $SAL_DIR/streamutils.tcl

set recdef [glob $SAL_WORK_DIR/sql/*.sqlwrt]
foreach i $recdef { 
   source $i
}

source $SAL_DIR/revCodes.tcl
source $SAL_WORK_DIR/.salwork/revCodes.tcl
source $SAL_DIR/managetypes.tcl


