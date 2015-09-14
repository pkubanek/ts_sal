#
#  Generic utility procedures used in SAL suite of programs
#

proc errorexit { msg } {
global SAL_LOG ORIGIN_DIR
  if { [info exists SAL_LOG(fd)] } {
     puts $SAL_LOG(fd) "FATAL ERROR : $msg"
     close $SAL_LOG(fd)
  }
  puts stderr "FATAL ERROR : $msg"
  cd $ORIGIN_DIR
  exit
}

proc stdlog { msg {verbosity 9} } {
global SAL_LOG
  if { [info exists SAL_LOG(fd)] } {
     puts $SAL_LOG(fd) "$msg"
  }
  puts stdout "$msg"
}


