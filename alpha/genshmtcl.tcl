#!/usr/bin/tclsh

set ftcl [open shm_tcl.c w]
set incs [glob shmem-*/*_cache.h]
foreach f $incs {
   if { [file size $f] != 0 } {
      puts $ftcl "#include \"$f\""
   }
}
puts $ftcl "#include \"tcl.h\"

int updateVariables(Tcl_Interp *interp, char *subsysid, int *shmdata_ref)
\{
    char *text;"
set incs [glob shmem-*/shm_tcl_*.c]
foreach f $incs {
   if { [file size $f] != 0 } {
      set fcp [open $f r]
      while { [gets $fcp rec] > -1 } {
         puts $ftcl $rec
      }
      close $fcp
      puts stdout "Added $f to shm_tcl.c"
   }
}

puts $ftcl "
    return TCL_OK;
\}"
close $ftcl


