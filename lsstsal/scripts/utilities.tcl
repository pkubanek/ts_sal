#
#  Generic utility procedures used in SAL suite of programs
#

proc errorexit { msg {id -1} } {
global SAL_LOG
  if { [info exists SAL_LOG(fd)] } {
     puts $SAL_LOG(fd) "FATAL ERROR : $msg"
     close $SAL_LOG(fd)
  }
  puts stdout "*******************************************************************************"
  puts stdout "***       ERROR : $msg"
  puts stdout "*******************************************************************************"
  exit $id
}

proc stdlog { msg {verbosity 9} } {
global SAL_LOG
  if { [info exists SAL_LOG(fd)] } {
     puts $SAL_LOG(fd) "$msg"
  }
  puts stdout "$msg"
}

proc cleanup { subsys language } {
global SAL_WORK_DIR SALVERSION OPTIONS
   set res ""
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> cleanup $subsys $language "}
   switch $op {
     all  {
       cleanup $subsys idl
       catch {
         exec rm -fr $SAL_WORK_DIR/[set subsys]
         set direcs [glob $SAL_WORK_DIR/[set subsys]_*]
         foreach i $files { 
            if { [file isdirectory $i] } {
               exec rm -fr $i
            } 
         }
             } res
          }
     cpp  {
       catch {
         set files [glob $SAL_WORK_DIR/[set subsys]*/cpp]
         foreach i $files { exec rm -fr $i }
             } res
          }
     idl  {
       catch {
         set files [glob $SAL_WORK_DIR/idl-templates/[set subsys]*.idl]
         foreach i $files { exec rm -f $i }
         set files [glob $SAL_WORK_DIR/idl-templates/validated/[set subsys]*.idl]
         foreach i $files { exec rm -f $i }
         set files [glob $SAL_WORK_DIR/idl-templates/validated/sal/sal_*[set subsys].idl]
         foreach i $files { exec rm -f $i }
         set files [glob $SAL_WORK_DIR/idl-templates/validated/[set subsys]_*]
         foreach i $files { exec rm -f $i }
         set files [glob $SAL_WORK_DIR/include/SAL_[set subsys]_*.idl]
         foreach i $files { exec rm -f $i }
             } res
          }
     java {
       catch {
         set files [glob $SAL_WORK_DIR/[set subsys]*/java]
         foreach i $files { exec rm -fr $i }
         exec rm -fr $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]
             } res
          }
     labview {
       catch { exec rm -fr [set subsys]/labview } res
             }
     lib {
       catch {
         set files [glob $SAL_WORK_DIR/lib/*[set subsys]*]
         foreach i $files { exec rm -fr $i }
             } res
         }
   }
   if { $res != "" } { errorexit "Failed to cleanup old $subsys files - $res" }
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< cleanup $subsys $language "}
}

proc checkassets { subsys language } {
global SAL_WORK_DIR
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> checkassets $subsys $language "}
   switch $language {
     idl      {
                checkfileasset $SAL_WORK_DIR/idl-templates/validated/sal/sal_revCoded_[set subsys].idl
              }
     cpp      {
                checkfileasset $SAL_WORK_DIR/[set subsys]/cpp/libsacpp_[set subsys]_types.so
                checkfileasset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys].cpp
                checkfileasset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys].h
                checkfileasset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys]C.h
                foreach test "commander controller sender logger publisher subscriber" {
                   checkfileasset $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_[set subsys]_all_[set test]
                }
              }
     java     {
                checkfileasset $SAL_WORK_DIR/[set subsys]/java/saj_[set subsys]_types.jar
                checkfileasset $SAL_WORK_DIR/[set subsys]/java/src/org/lsst/sal/SAL_[set subsys].java
              }
     python   {
                checkfileasset $SAL_WORK_DIR/[set subsys]/cpp/src/SALPY_[set subsys].so
              }
     labview  {
                checkfileasset $SAL_WORK_DIR/[set subsys]/labview/SALLV_[set subsys].so
                checkfileasset $SAL_WORK_DIR/[set subsys]/labview/SALLV_[set subsys]_Monitor
                checkfileasset $SAL_WORK_DIR/[set subsys]/labview/sal_[set subsys].idl
                checkfileasset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys]LV.h
              }
   }
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< checkassets $subsys $language "}
}

proc checkfileasset { fname } {
  if { [file exists $fname] == 0 } { errorexit "Failed to generate $fname" 1 }
  if { [file size $fname] == 0 } { errorexit "Failed to generate $fname - size=0" 1 }
}




