
proc generaterecs { handle pkey topic } {
global SQLREC 
  set cmd "INSERT INTO $topic VALUES (\"$pkey\""
  set flds [split $SQLREC($topic) ,]
  writesql $handle $topic $cmd $flds
}


proc writesql { handle topic cmd flds } {
global SQLREC KEYRANGE
  while { [llength $flds] != 0 } {
      set i [lindex $flds 0]
      set flds [lrange $flds 1 end]
      set type [lindex [split $i .] 0]
      set name [lindex [split $i .] 1]
      if { [info exists KEYRANGE($name)] } {
         set i 1
         while { $i <= $KEYRANGE($name) } {
            writesql $handle $topic "$cmd ,$i" $flds
            incr i 1
         }
         return
      } else {
          set generic [lindex [split $name _] 0]
          if { [info command simulate_[set generic]_value] != "" } {
             set value [simulate_[set generic]_value $topic]
          } else {
             set value [simulate_[set type]_value]
          }
      }
      set cmd "$cmd ,$value"
  }
  puts $handle "$cmd);"
}


proc simulate_revCode_value { topic } {
global REVCODE
   return "\"$REVCODE($topic)\""
}

proc simulate_sndStamp_value { topic } {
   return [clock seconds]
}

proc simulate_rcvStamp_value { topic } {
   return [expr [clock seconds] + 1]
}

proc simulate_origin_value { topic } {
   return 9999
}

proc simulate_heaterPower_value { topic } {
   return [expr rand() + 2.5]
}
proc simulate_temperature_value { topic } {
   return [expr rand() + 29.5]
}

proc simulate_cold_value { topic } {
   return [expr rand() + 19.5]
}


proc simulate_setpoint_value { topic } {
   return [expr rand() + 29.5]
}

proc simulate_flow_value { topic } {
   return [expr rand() + 0.5]
}

proc simulate_supply_value { topic } {
   return [expr rand() + 19.5]
}

proc simulate_seqNum_value { topic } {
   return [clock seconds]
}

proc simulate_current_value { topic } {
   return [expr rand() + 0.5]
}

proc simulate_pressure_value { topic } {
   return [expr rand()/10000.0 + 0.01]
}

proc simulate_zernikes_value { topic } {
   return [expr rand()/1.0e6]
}

if { 0 } {
proc simulate_reset_value { topic } {
   return [expr rand() + 4.0]
}

proc simulate_operate_value { topic } {
   return [expr rand() + 14.5]
}

proc simulate_substrate_value { topic } {
   return [expr rand() + 20.0]
}

proc simulate_serial_value { topic } {
   return [expr rand()/100.+0.5]
}

proc simulate_parallel_value { topic } {
   return [expr rand()/100. + 5.5]
}

}




proc simulate_int_value { } {
  set v [expr int(rand()*20)+90]
  return $v
}

proc simulate_short_value { } {
  set v [expr int(rand()*20)+90]
  return $v
}

proc simulate_byte_value { } {
  set v [expr int(rand()*20)+90]
  return $v
}

proc simulate_float_value { } {
  set v [expr rand()*20.+90.]
  return $v
}

proc simulate_double_value { } {
  set v [expr rand()*20.+90.]
  return $v
}

proc simulate_char_value { } {
  set v [expr rand()*20.+90.]
  return "\"Text $v\""
}

proc simulateperiod { handle topic start end freq } {
   set sample $start
   while { [calcms $sample] < [calcms $end] } {
      generaterecs $handle $sample $topic
      set sample [nextsample $sample $freq]
   }
}

proc nextsample { sample freq } {
  set s [clock scan $sample]
  set n [expr $s + $freq]
  return [clock format $n -format "%Y-%m-%d %H:%M:%S"]
}

proc calcms { sample } {
  return [clock scan $sample]
}

proc dumpsql { host database table } {
   exec mysqldump --add-drop-table --allow-keywords -q -c -h $host -u root $database $table | gzip -9 > $table.sql.gz
   set now [clock format [clock seconds] -format "%H:%M:%S"]
   puts stdout "$now Dumped $host:$database:$table to $table.sql.gz - size [file size $table.sql.gz]"
}

proc dumpall { host database } {
   set all [split [exec echo "show tables;" | mysql -h $host -u root $database ] \n]
   foreach i $all {
     if { [file exists $i.sqldef] } {
        dumpsql $host $database $i
     }
   }
}

proc insertall { host database } {
   set all [split [exec echo "show tables;" | mysql -h $host -u root $database ] \n]
   foreach i $all {
     if { [file exists $i.sql] } {
        exec mysql -u root -h $host $database < $i.sql
        puts stdout "$now Imported $host:$database:$table to $i.sql]"
     }
   }
}


set KEYRANGE(ccdID) 201
set KEYRANGE(raftID) 25
set KEYRANGE(ampID) 132

source /usr/local/scripts/tcl/streamutils.tcl

set recdef [glob $SAL_WORK_DIR/sql/*.sqlwrt]
foreach i $recdef { 
   source $i
}

source $SAL_DIR/revCodes.tcl
source $SAL_WORK_DIR/.salwork/revCodes.tcl
source $SAL_DIR/datastreams.freqs


foreach s [array names FREQUENCY] {
  set id [join [split $s .] _]
  set DELTASECS($id) [expr int(1.0/$FREQUENCY($s))]
  if { $DELTASECS($id) < 1 } {set DELTASECS($id) 1}
}

##clock format 1226532001 -format "%Y-%m-%d %H:%M:%S"
## source /usr/local/scripts/tcl/checkidl.tcl
## checkidl camera-subsystems-init-v1.idl
## cat validated/*.detail > datastreams.detail
## generaterecs stdout somekey camera_BEE_biases
##   simulateperiod $fout $i $start $end $DELTASECS($i)




