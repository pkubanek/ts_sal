#!/usr/bin/tclsh

# Run runtime-generator.sh first

set SAL_DIR $env(SAL_DIR)
set SAL_WORK_DIR $env(SAL_WORK_DIR)
source $SAL_DIR/add_system_dictionary.tcl

source $SAL_DIR/sal_version.tcl

set DEST /data/staging/ts_visit_simulator

exec mkdir -p $DEST/test/tcs
exec mkdir -p $DEST/test/lib
exec mkdir -p $DEST/test/include

puts stdout "Copying tcs simulator"
exec cp -rv $SAL_WORK_DIR/tcs/tcs $DEST/test/tcs/.

puts stdout "Copying lsstsal baseline"
exec cp -rv /data/gitrepo/ts_visit_simulator/lsstsal $DEST/.
exec cp -rv /data/gitrepo/ts_visit_simulator/README $DEST/.
exec cp -rv /data/gitrepo/ts_visit_simulator/SAL_TCS_Simulator_User_Guide.pdf $DEST/.
exec cp -rv /data/gitrepo/ts_visit_simulator/setup.env $DEST/.

puts stdout "Copying OpenSplice"
exec tar -C $env(LSST_SDK_INSTALL) -cvf - OpenSpliceDDS | tar -C $DEST -xvf -

puts stdout "Updating XML"
set all [glob $SAL_WORK_DIR/*.xml]
foreach i $all {
   exec cp -v $i $DEST/test/.
}

puts stdout "Updating libsacpp"
set all [glob $SAL_WORK_DIR/*/cpp/libsacpp_*.so]
foreach i $all {
puts stdout $i
   exec cp -v $i $DEST/test/lib/.
}

puts stdout "Updating includes"
set all [glob $SAL_WORK_DIR/*/cpp/src/SAL_*.h]
foreach i $all {
puts stdout $i
   exec cp -v $i $DEST/test/include/.
}

puts stdout "Updating libSAL"
set all [glob $SAL_WORK_DIR/lib/libSAL_*.so]
foreach i $all {
   exec cp -v $i $DEST/test/lib/.
}

if {0}
puts stdout "Updating libSALLV"
set all [glob $SAL_WORK_DIR/lib/SALLV_*.so]
foreach i $all {
   exec cp -v $i $DEST/test/lib/.
}
set all [glob $SAL_WORK_DIR/*/labview]
foreach i $all {
   exec cp -rv $i $DEST/test/.
}
}

puts stdout "Updating libSALPY"
set all [glob $SAL_DIR/../lib/SALPY_*.so]
foreach i $all {
   exec cp -v $i $DEST/test/lib/.
}

puts stdout "Updating saj"
set all [glob $SAL_WORK_DIR/*/java/saj_*.jar]
foreach i $all {
   exec cp -v $i $DEST/test/lib/.
}

puts stdout "Updating sal java"
set all [glob $SAL_WORK_DIR/maven/*_$SALVERSION/target/sal_*$SALVERSION.jar]
foreach i $all {
   exec cp -v $i $DEST/test/lib/.
}

puts stdout "Updating Telemetry tests"
foreach subsys $SYSDIC(systems) {
   catch {
     set all [glob $SAL_WORK_DIR/[set subsys]_*]
     foreach i $all {
      if { [file isdirectory $i] } {
         puts stdout "Processing $i"
         set id [file tail $i]
         exec mkdir -p $DEST/test/[set subsys]/cpp/src/
         exec cp -v $SAL_WORK_DIR/$id/cpp/standalone/sacpp_[set subsys]_pub $DEST/test/[set subsys]/cpp/src/sacpp_[set id]_publisher
         exec cp -v $SAL_WORK_DIR/$id/cpp/standalone/sacpp_[set subsys]_sub $DEST/test/[set subsys]/cpp/src/sacpp_[set id]_subscriber
      }
     }
   }
}

puts stdout "Updating Command tests"
foreach subsys $SYSDIC(systems) {
  catch {
   set all [glob $SAL_WORK_DIR/[set subsys]/cpp/src/*_commander]
   foreach i $all {
      exec cp -v $i $DEST/test/[set subsys]/cpp/src/.
      puts stdout "copied $i"
   }
   set all [glob $SAL_WORK_DIR/[set subsys]/cpp/src/*_controller]
   foreach i $all {
      exec cp -v $i $DEST/test/[set subsys]/cpp/src/.
      puts stdout "copied $i"
   }
  }
}

puts stdout "Updating Event tests"
foreach subsys $SYSDIC(systems) {
  catch {
   set all [glob $SAL_WORK_DIR/[set subsys]/cpp/src/*_log]
   foreach i $all {
      exec cp -v $i $DEST/test/[set subsys]/cpp/src/.
      puts stdout "copied $i"
   }
   set all [glob $SAL_WORK_DIR/[set subsys]/cpp/src/*_send]
   foreach i $all {
      exec cp -v $i $DEST/test/[set subsys]/cpp/src/.
      puts stdout "copied $i"
   }
  }
}


puts stdout "Updating EFD clients"
source $env(SAL_DIR)/gengenericefd.tcl

updateefdschema
foreach subsys $SYSDIC(systems) {
  catch {
   set all [glob $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_*_efdwriter]
   foreach i $all {
      exec cp -v $i $DEST/test/[set subsys]/cpp/src/.
      puts stdout "copied $i"
   }
  }
}


puts stdout "Updating sal scripts"
foreach i "command_test_gui hexapod_sim.tcl simulate_controllers simulate-visits.tcl genidlshmem.tcl logevent_test_gui simulate_java_controllers  standardvisit_commands.tcl" {
   exec cp -v $SAL_DIR/$i $DEST/lsstsal/scripts/.
}


puts stdout "*******Remember to delete unused OpenSpliceDDS versions********"






