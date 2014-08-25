#!/usr/bin/tclsh
set whereami /home/saluser/tcs_kernel_Target
source $whereami/shmem-tcs_kernel_Target/test_tcs_kernel_Target.tcl 
set id $SHMtcs_kernel_Target(shmid)
set size $SHMtcs_kernel_Target(shmsize)
writeshm tcs_kernel_Target $id $size


