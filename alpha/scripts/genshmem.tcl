#!/usr/bin/tclsh
set subsys $argv
puts stdout "Generating code for subsystem $argv"

proc doddsgen { subsys } {
   puts stdout "Generating DDS classes"
   exec rtiddsgen -language C -example i86Linux2.6gcc3.4.3 $subsys.idl
   puts stdout "Parsing generated code"
   parsepub $subsys
   generatetester $subsys
   parsemakefile $subsys
}

proc calcshmid { subsys } {
  set fout [open /tmp/subsys.tmp w]
  puts $fout "$subsys"
  close $fout
  set id [string range [exec md5sum /tmp/subsys.tmp] 0 3]
  return $id
}


proc addshmemcode { subsys fid } {
global VPROPS TYPESIZE
  set fput [open [set subsys]_putstub.txt w]
  set fget [open [set subsys]_getstub.txt w]
  puts $fid "
   int [set subsys]_shmsize;
   int lshmid;
   int [set subsys]_shmid = 0x[calcshmid $subsys];
   [set subsys]_cache *[set subsys]_ref;
   [set subsys]_shmsize = sizeof(struct [set subsys]_cache);
   lshmid = shmget([set subsys]_shmid, [set subsys]_shmsize , IPC_CREAT|0666);
   [set subsys]_ref  = ([set subsys]_cache *) shmat(lshmid, NULL, 0);

   while ([set subsys]_ref->syncO > -1 ) \{
     while ([set subsys]_ref->syncO == 0) \{
        svcSAL_sleep(1);  
     \}

     count++;
"
  set fin [open [set subsys]_cache.h r]
  gets $fin rec
  gets $fin rec
  gets $fin rec
  while { [gets $fin rec] > -1 } {
     set v [string trim [lindex $rec 1] ";"]
     if { [llength [split $v "\[\]"]] > 1 } {
        set l [expr [lindex [split $v "\[\]"] 1] * $TYPESIZE([lindex $rec 0]) ]
        set v [lindex [split $v "\[\]"] 0]
     } else {
        set l 1
     }
     if { $v != "syncO" } {
       puts $fid "	[transferdata $subsys $v [lindex $rec 0] $l fromcache]"
       puts $fput "	[transferdata $subsys $v [lindex $rec 0] $l fromcache]"
       puts $fput "
        printf(\"Writing [set subsys], count %d\\n\", count);
        
        /* Write data */
        [set subsys]_retcode = [set subsys]DataWriter_write(
            [set subsys]_writer, [set subsys]_instance, &[set subsys]_instance_handle);
        if ([set subsys]_retcode != DDS_RETCODE_OK) \{
            printf(\"write error %d\\n\", [set subsys]_retcode);
        [set subsys]_ref->syncO = 0;
        \}"
       puts $fget "	[transferdata $subsys $v [lindex $rec 0] $l tocache]"
     }
  }
  puts $fid "
        printf(\"Writing [set subsys], count %d\\n\", count);
        
        /* Write data */
        retcode = [set subsys]DataWriter_write(
            [set subsys]_writer, instance, &instance_handle);
        if (retcode != DDS_RETCODE_OK) \{
            printf(\"write error %d\\n\", retcode);
        \}

        NDDS_Utility_sleep(&send_period);
        [set subsys]_ref->syncO = 0;
    \}
"
  close $fput
  close $fget
}

proc shcoder { subsys } {
global SHC TOPICPROPS
  set fcod [open shmem_[set subsys].h w]
  puts $fcod $SHC(genericshmem.h)
  close $fcod
  set fcod [open shmem_[set subsys]_server.cpp w]
  puts $fcod $SHC(genericshmem.cpp)
  close $fcod
  set fcod [open test_shmem_[set subsys].cpp w]
  puts $fcod $SHC(genericshclient.cpp)
  close $fcod
  exec g++ -shared -g shmem_[set subsys]_server.cpp -o libshm_[set subsys]_server.so -lstdc++
  exec gcc -g test_shmem_[set subsys].cpp -o shm_test1 -lpthread -L. -lshm_[set subsys]_server
}


proc generatetester { subsys } {
  set fout [open [set subsys]_shmem_tester.c w]
  puts $fout "
/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from [set subsys].idl using \"genshmem\".
  The genshmem tool is part of the LSST SAL middleware stack
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include \"[set subsys]_cache.h\"

int main(int argc, char *argv\[\])
\{
   int [set subsys]_shmsize;
   int lshmid;
   int icount=0;
   int [set subsys]_shmid = 0x[calcshmid $subsys];
   [set subsys]_cache *[set subsys]_ref;
   [set subsys]_shmsize = sizeof(struct [set subsys]_cache);
   lshmid = shmget([set subsys]_shmid, [set subsys]_shmsize , IPC_CREAT|0666);
   [set subsys]_ref  = ([set subsys]_cache *) shmat(lshmid, NULL, 0);
 
"
  set fin [open [set subsys]_cache.h r]
  gets $fin rec
  gets $fin rec
  while { [gets $fin rec] > -1 } {
     set v [string trim [lindex $rec 1] ";"]
     if { $v != "syncO" } {
       switch [lindex $rec 0] {
         byte -
         short -
         int - 
         long -
         float - 
         double { puts $fout "   [set subsys]_ref->$v++;" }
         char { set cv [lindex [split $v "\[\]"] 0]
                puts $fout "   icount++;
   sprintf([set subsys]_ref->$cv,\"Sample string %d\",icount);" }
       }
     }
  }
  puts $fout "   [set subsys]_ref->syncO = 1;
   return(0);
\}
"  
  close $fout
}

  
proc generatetcllib { subsys } {
global LVERSION
  set fout [open shm_tcl_[set subsys].c w]
  set fo2  [open shmrd_tcl_[set subsys].c w]
  set ftst [open test_[set subsys].tcl w]
  puts $ftst "set SHM[set subsys](shmid) 0x[calcshmid $subsys]"
  set sval [lindex [exec grep "size_t [set subsys]_shmsize =" shmem_[set subsys]_server.cpp] 3]
  puts $ftst "set SHM[set subsys](shmsize) [string trim $sval ";"]"
  puts $ftst "load /home/shared/lsst/lib/libshm.so"
  puts $fout "
    if (strcmp(subsysid,\"$subsys\") == 0) \{
       [set subsys]_cache *[set subsys]_ref;
       [set subsys]_ref = ([set subsys]_cache *)shmdata_ref;
"
  puts $fo2 "int shm_tcl_get_$subsys ( Tcl_Interp *interp, char *subsysid, int *shmdata_ref ) \{
    char newValue\[128\];
    [set subsys]_cache *[set subsys]_ref;
    [set subsys]_ref = ([set subsys]_cache *)shmdata_ref;

    if ( [set subsys]_ref->syncI ) \{
"
  set fin [open [set subsys]_cache.h r]
  gets $fin rec
  gets $fin rec
  while { [gets $fin rec] > -1 } {
     set v [string trim [lindex $rec 1] ";"]
     if { $v != "syncO" } {
       set v [lindex [split $v "\[\]"] 0]
       switch [lindex $rec 0] {
         byte - 
         short - 
         int  { puts $fout "
       text = (char *)Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
       sscanf(text,\"%d\", &[set subsys]_ref->$v);"
                puts $ftst "set SHM[set subsys]($v) 1"
                puts $fo2 "
      sprintf(newValue,\"%d\",[set subsys]_ref->$v);
      Tcl_SetVar2(interp, \"SHM[set subsys]\", \"$v\", newValue,  TCL_GLOBAL_ONLY);"
              }
         long { puts $fout "
       text = (char *)Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
       sscanf(text,\"%ld\", &[set subsys]_ref->$v);"
                puts $ftst "set SHM[set subsys]($v) 1.2"
                puts $fo2 "
      sprintf(newValue,\"%ld\",[set subsys]_ref->$v);
      Tcl_SetVar2(interp, \"SHM[set subsys]\", \"$v\", newValue,  TCL_GLOBAL_ONLY);"
              }
         float { puts $fout "
       text = (char *)Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
       sscanf(text,\"%f\", &[set subsys]_ref->$v);"
                puts $ftst "set SHM[set subsys]($v) 1.23"
                puts $fo2 "
      sprintf(newValue,\"%f\",[set subsys]_ref->$v);
      Tcl_SetVar2(interp, \"SHM[set subsys]\", \"$v\", newValue, TCL_GLOBAL_ONLY);"
             }
         double { puts $fout "
       text = (char *)Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
       sscanf(text,\"%lf\", &[set subsys]_ref->$v);"
                puts $ftst "set SHM[set subsys]($v) 1.234"
                puts $fo2 "
      sprintf(newValue,\"%lf\",[set subsys]_ref->$v);
      Tcl_SetVar2(interp, \"SHM[set subsys]\", \"$v\", newValue, TCL_GLOBAL_ONLY);"
              }
         char { puts $fout "
       text = (char *)Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
       strcpy([set subsys]_ref->$v,text);"
                puts $ftst "set SHM[set subsys]($v) \"test $v\""
                puts $fo2 "
      Tcl_SetVar2(interp, \"SHM[set subsys]\", \"$v\", [set subsys]_ref->$v, TCL_GLOBAL_ONLY);"
             }
       }
     }
  }
  puts $fout "      [set subsys]_ref->syncO = 1;
    \}"
  puts $fo2 "  \}
  return TCL__OK;
\}"
  close $fout
  close $fo2
  close $ftst
  set ftst [open test_singleshot.tcl w]
  puts $ftst "#!/usr/bin/tclsh

source /home/shared/lsst/tests/shmem/shmem-[set subsys]/test_[set subsys].tcl 
set id \$SHM[set subsys](shmid)
set size \$SHM[set subsys](shmsize)
writeshm [set subsys] \$id \$size

"
  close $ftst
  exec chmod 755 test_singleshot.tcl
  set ftst [open startpubsub w]
  puts $ftst "#!/bin/sh
xterm -e /home/shared/lsst/tests/shmem/shmem-[set subsys]/objs/$LVERSION/[set subsys]_shmem_publisher &
xterm -e /home/shared/lsst/tests/shmem/shmem-[set subsys]/objs/$LVERSION/[set subsys]_subscriber &
echo \"Use /home/shared/lsst/tests/shmem/shmem-[set subsys]/test_singleshot.tcl to test\"
"
  close $ftst
  exec chmod 755 startpubsub
}


proc parsepub { subsys } {
global NDDS_VERSION NDDSPUBLOOPSIZE
  set fin  [open [set subsys]_publisher.c r]
  set fout [open [set subsys]_shmem_publisher.c w]
  while { [gets $fin rec] > -1 } {
     if { [lindex [split $rec "\""] 1] == "[set subsys]Support.h" } {
       puts $fout $rec
       puts $fout "#include <sys/shm.h>"
       puts $fout "#include \"[set subsys]_cache.h\""
     } else {
        if { [string trim $rec] == "/* Main loop */" } {
           addshmemcode $subsys $fout
           set i $NDDSPUBLOOPSIZE($NDDS_VERSION)
           while { $i > 0 } {gets $fin rec ; incr i -1}
        } else {
           puts $fout $rec
        }
     }
  }
  close $fin
  close $fout
}

proc parsemakefile { subsys } {
  set mf [glob makefile*i86Linux2.6gcc3.4.3]
  set fin [open $mf r]
  set fout [open makefile w]
  while { [gets $fin rec] > -1 } {
    if { [string range $rec 0 3] != "EXEC" } {
       puts $fout $rec
    } else {
       puts $fout "EXEC          = [set subsys]_subscriber \\
		[set subsys]_publisher \\
		[set subsys]_shmem_publisher \\
		[set subsys]_shmem_tester"
    }
  }
  close $fin 
  close $fout
}

set scriptdir /usr/local/scripts/tcl
set includedir /usr/local/scripts/include
source $scriptdir/managetypes.tcl


set NDDS_VERSION 4.2e
set NDDSPUBLOOPSIZE(4.2e) 17
set LVERSION i86Linux2.6gcc3.4.3
set basedir .

source revCodes.tcl
set workdir $basedir/shmem-$subsys
exec mkdir -p $workdir
exec cp $subsys.idl $workdir/.
set fin [open $subsys.idl r]
set fout [open $workdir/[set subsys]_cache.h w]
set TOPICPROPS($subsys) "  int syncI;"
set TOPICPROPS(bytesize) 4
puts $fout "typedef struct [set subsys]_cache \{"
puts $fout "  int cppDummy;"
puts $fout "  int syncI;"
gets $fin rec
while { [gets $fin rec] > -1 } {
   if { [llength [split $rec "/"]] > 1 } {
      set rec [lindex [split $rec "/"] 0]
   }
   if { $rec != "\};" } {
     if { [llength [split [lindex $rec 0] "<>"]] > 1 } {
      set t [lindex [split [lindex $rec 0] "<>"] 0]
      set v [string trim [lindex $rec 1] ";"]
      set l [lindex [split $rec "<>"] 1]
      set VPROPS($v) $l
      incr TOPICPROPS(bytesize) [expr $TYPESIZE($t)*$l]
      puts $fout "  $TYPESUBS($t) $v\[$l\];"
      set TOPICPROPS($subsys) "$TOPICPROPS($subsys)\n  $TYPESUBS($t) $v\[$l\];"
     } else {
      if { [llength [split [lindex $rec 1] "\[\]"]] > 1 } {
         set l [lindex [split [lindex $rec 1] "\[\]"] 1]
         set v [lindex [split [lindex $rec 1] "\[\]"] 0]
      } else {
         set l 1
         set v [string trim [lindex $rec 1] ";"]
      }
      set VPROPS($v) $l
      set t [lindex $rec 0]
      set r [string trim [lrange $rec 1 end] "\{\}"]
      puts $fout "  $TYPESUBS($t) $r"
      set TOPICPROPS($subsys) "$TOPICPROPS($subsys)\n  $TYPESUBS($t) $r"
      incr TOPICPROPS(bytesize) [expr $TYPESIZE($t)*$l]
     }
   }
}
puts $fout "  int syncO;"
puts $fout "\} [set subsys]_cache;"
close $fin
close $fout

set TOPICPROPS($subsys) "$TOPICPROPS($subsys)\n  int syncO;"
incr TOPICPROPS(bytesize) 4
exec cp $workdir/[set subsys]_cache.h $includedir/.

puts stdout "Processing topic $subsys"
source $scriptdir/genericshmem.h.tcl
source $scriptdir/genericshmem.cpp.tcl
source $scriptdir/genericshclient.cpp.tcl
cd $workdir
doddsgen $subsys
shcoder $subsys
generatetcllib $subsys

