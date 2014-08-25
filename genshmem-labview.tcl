
proc dolvgen { sublist {publist ""} } {
global SAL_DIR SALVERSION SAL_DIR SAL_WORK_DIR
   set topiclist [lsort -unique "$sublist $publist"]
   exec mkdir -p $SAL_WORK_DIR/labview
   set subsys [lindex [split [lindex $topiclist 0] _] 0]
   set incs [glob $SAL_DIR/code/labview/*.h]
   foreach i $incs {exec cp $i $SAL_WORK_DIR/labview/.}
   exec cp $SAL_DIR/code/labview/makefile.lvsal $SAL_WORK_DIR/labview/.
   set fin [open $SAL_DIR/code/labview/svcSAL_commLib.h.template r]
   set fout [open $SAL_WORK_DIR/labview/svcSAL_commLib.h w]
   while { [gets $fin rec] > -1 } {
      if { [string range $rec 0 8] == "###INSERT" } {
         replacelvcode $topiclist [lindex $rec 1] $fout
      } else {
         puts $fout $rec
      }
   }
   close $fin
   close $fout
   set fin [open $SAL_DIR/code/labview/svcSAL_commLib.c.template r]
   set fout [open $SAL_WORK_DIR/labview/svcSAL_commLib.c w]
   while { [gets $fin rec] > -1 } {
      if { [string range $rec 0 8] == "###INSERT" } {
         replacelvcode $topiclist [lindex $rec 1] $fout
      } else {
         puts $fout $rec
      }
   }
   close $fin
   close $fout
}

proc replacelvcode { topiclist op fid } {
global SAL_WORK_DIR
  switch $op {
     includes {
               puts $fid "#include \"svcSAL.h\""
               foreach t $topiclist {
                 puts $fid "#include \"[set t]_cache.h\""
               }
     }
     prototypes {
                 foreach t $topiclist {
                    puts $fid "
extern int LVcomm_get_i[set t](int fd);
extern int LVcomm_send_e[set t](int fd);
extern int LVcomm_close_[set t](int fd);"
                    set fpi [open $SAL_WORK_DIR/shmem-[set t]/[set t]_lvprostub.txt r]
                    gets $fpi rec ; puts $fid "extern $rec"
                    gets $fpi rec ; puts $fid "extern $rec"
                    close $fpi
                 }
     }
     readwrite {
                 foreach t $topiclist {
                    set fpi [open $SAL_WORK_DIR/shmem-[set t]/[set t]_lvprostub.txt r]
                    gets $fpi rec
                    puts $fid [string trim $rec " ;"]
                    puts $fid "\{\n	int ilen=0;"
                    set fpro [open $SAL_WORK_DIR/shmem-[set t]/[set t]_lvgetstub.txt r]
                    puts $fid "
	[set t]_cache *[set t]_ref;
	[set t]_ref = ([set t]_cache *)LV_serial\[fd\].shm_ptr;"
                    while { [gets $fpro rec] > -1 } {
                       puts $fid $rec
                    }
                    puts $fid "	[set t]_ref->syncI = 0;\n	return(0);\n\}\n\n"
                    close $fpro
                    gets $fpi rec
                    puts $fid [string trim $rec " ;"]
                    puts $fid "\{\n"
                    set fpro [open $SAL_WORK_DIR/shmem-[set t]/[set t]_lvputstub.txt r]
                    puts $fid "
	[set t]_cache *[set t]_ref;
	[set t]_ref = ([set t]_cache *)LV_serial\[fd\].shm_ptr;"
                    while { [gets $fpro rec] > -1 } {
                       puts $fid $rec
                    }
                    puts $fid "	[set t]_ref->syncO = 1;\n	return(0);\n\}\n\n"
                    close $fpro
                    puts $fid "
int LVcomm_get_i[set t](int fd)
\{
        sem_post(&(LV_serial\[fd\].sem_read));
        return(0);
\}
int LVcomm_send_e[set t](int fd)
\{
	if (LV_serial\[fd\].ew.status == LVTRUE)
		return(-1);
	return(0);
\}
int LVcomm_close_[set t](int fd)
\{
	LV_serial\[fd\].shm_ptr = NULL;
	sem_post(&(LV_serial\[fd\].sem_read));
	sem_post(&(LV_serial\[fd\].sem_write));
	return(0);
\}
"
                 }
     }
  }
}


