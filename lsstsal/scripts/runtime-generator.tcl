#!/usr/bin/env tclsh

source $env(SAL_DIR)/add_system_dictionary.tcl
set EVERYTHING [lsort $SYSDIC(systems)]
foreach subsys $EVERYTHING {
   catch {
      set x [glob $subsys*.xml]
      set DO($subsys) 1
   } else {
     puts stdout "No definitions for $subsys"
   }
}

if { $argv == "" || [lsearch $argv validate] > -1} {
  puts stdout "Removing old idl-templates"
  exec rm -fr idl-templates

  puts stdout  "Validating interfaces"
  foreach subsys $EVERYTHING {
   if { [info exists DO($subsys)] } {
   set bad ""
   set result ""
   catch { set results [exec salgenerator $subsys validate ] } bad
   puts stdout "$result $bad"
   set bad ""
   set result ""
   catch {exec salgenerator $subsys html}
   puts stdout "$result $bad"
   }
  }
}

if { $argv == "" || [lsearch $argv cpp] > -1 } {
 puts stdout  "Generating C++"
 foreach subsys $EVERYTHING {
  if { [info exists DO($subsys)] } {
   set bad ""
   set result ""
   catch { set results [exec salgenerator $subsys sal cpp ] } bad
   puts stdout "$result $bad"
  }
 }
}

if { $argv == "" || [lsearch $argv python] > -1 } {
 puts stdout  "Generating Python"
 foreach subsys $EVERYTHING {
  if { [info exists DO($subsys)] } {
   set bad ""
   set result ""
   catch { set results [exec salgenerator $subsys sal python ] } bad
   puts stdout "$result $bad"
  }
 }
}


if { $argv == "" || [lsearch $argv labview] > -1 } {
 puts stdout  "Generating LabVIEW"
 foreach subsys $EVERYTHING {
  if { [info exists DO($subsys)] } {
   set bad ""
   set result ""
   catch { set results [exec salgenerator $subsys labview ] } bad
   puts stdout "$result $bad"
  }
 }
}


if { $argv == "" || [lsearch $argv lib] > -1 } {
 puts stdout  "Updating libraries"
 foreach subsys $EVERYTHING {
  if { [info exists DO($subsys)] } {
   set bad ""
   set result ""
   catch { set results [exec salgenerator $subsys lib ] } bad
   puts stdout "$result $bad"
  }
 }
}

if { $argv == "" || [lsearch $argv java] > -1 } {
 puts stdout  "Generating Java"
 foreach subsys $EVERYTHING {
  if { [info exists DO($subsys)] } {
   exec rm -fr [set subsys]/java
   set bad ""
   set result ""
   catch { set results [exec salgenerator $subsys sal java ] } bad
   puts stdout "$result $bad"
   set bad ""
   set result ""
   catch { set results [exec salgenerator $subsys maven ] } bad
   puts stdout "$result $bad"

  }
 }
}


if { $argv == "" || [lsearch $argv efd] > -1 } {
 source $env(SAL_DIR)/gengenericefd_array.tcl
 set bad ""
 set result ""
 catch { set results [updateefdschema] } bad
 puts stdout "$result $bad"
}



cd $env(SAL_WORK_DIR)

if { $argv == "" || [lsearch $argv rpm] > -1 } {
 puts stdout  "Updating RPMs"
 foreach subsys $EVERYTHING {
  if { [info exists DO($subsys)] } {
   set bad ""
   set result ""
   catch { set results [exec salgenerator $subsys rpm] } bad
   puts stdout "$result $bad"
  }
 }
 source $env(SAL_DIR)/gensalrpms.tcl
 set bad ""
 set result ""
 catch { set results [generatemetarpm] } bad
 puts stdout "$result $bad"
 set bad ""
 set result ""
 catch { set results [generateATmetarpm] } bad
 puts stdout "$result $bad"
 set bad ""
 set result ""
 catch { set results [generateEFDrpm] } bad
 puts stdout "$result $bad"
}





