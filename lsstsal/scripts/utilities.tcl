#
#  Generic utility procedures used in SAL suite of programs
#
set TDEPTH 0

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
global SAL_LOG TDEPTH
  if { [string range $msg 0 10] == "###TRACE>>>" } { incr TDEPTH 2 }
  if { [string range $msg 0 10] == "###TRACE<<<" } { incr TDEPTH -2 }
  if { [info exists SAL_LOG(fd)] } {
     puts $SAL_LOG(fd) "[string repeat "#" $TDEPTH]$msg"
  }
  puts stdout "[string repeat "#" $TDEPTH]$msg"
}

proc clearAssets { subsys language } {
global SAL_WORK_DIR SALVERSION OPTIONS
   set res ""
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> clearAssets $subsys $language "}
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
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< clearAssets $subsys $language "}
}

proc checkAssets { subsys language } {
global SAL_WORK_DIR OPTIONS CMD_ALIASES EVENT_ALIASES TLM_ALIASES
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> checkAssets $subsys $language "}
   switch $language {
     idl      {
                checkFileAsset $SAL_WORK_DIR/idl-templates/validated/sal/sal_revCoded_[set subsys].idl
              }
     cpp      {
                checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/libsacpp_[set subsys]_types.so
                checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys].cpp
                checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys].h
                checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys]C.h
                if { [info exists CMD_ALIASES($subsys)] } {
                   checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_[set subsys]_all_commander
                   checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_[set subsys]_all_controller
                }
                if { [info exists EVENT_ALIASES($subsys)] } {
                   checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_[set subsys]_all_sender
                   checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_[set subsys]_all_logger
                }
                if { [info exists TLM_ALIASES($subsys)] } {
                   checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_[set subsys]_all_publisher
                   checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/sacpp_[set subsys]_all_subscriber
                }
              }
     java     {
                checkFileAsset $SAL_WORK_DIR/[set subsys]/java/saj_[set subsys]_types.jar
                checkFileAsset $SAL_WORK_DIR/[set subsys]/java/src/org/lsst/sal/SAL_[set subsys].java
              }
     python   {
                checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/SALPY_[set subsys].so
              }
     labview  {
                checkFileAsset $SAL_WORK_DIR/[set subsys]/labview/SALLV_[set subsys].so
                checkFileAsset $SAL_WORK_DIR/[set subsys]/labview/SALLV_[set subsys]_Monitor
                checkFileAsset $SAL_WORK_DIR/[set subsys]/labview/sal_[set subsys].idl
                checkFileAsset $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys]LV.h
              }
   }
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< checkAssets $subsys $language "}
}

proc checkFileAsset { fname } {
  if { [file exists $fname] == 0 } { errorexit "Failed to generate $fname" 1 }
  if { [file size $fname] == 0 } { errorexit "Failed to generate $fname - size=0" 1 }
}

proc getAlias { topic } {
   set stopic [split $topic "_"]
   if { [lindex $stopic 1] != "command" && [lindex $stopic 1] != "logevent" } {
      set alias [join [lrange $stopic 1 end] _]
   } else {
      set alias [join [lrange $stopic 2 end] _]
   }
}





