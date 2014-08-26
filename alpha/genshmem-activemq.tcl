#!/usr/bin/tclsh
set subsys $argv
puts stdout "Generating activeMQ code for subsystem $argv"

proc doamqgen { subsys } {
   puts stdout "Generating activeMQ classes"
   puts stdout "Parsing generated code"
   parsepub $subsys
   parsesb $subsys
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


proc addshmemcodepub { subsys fid } {
global VPROPS
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
  gets $fin rec
  while { [gets $fin rec] > -1 } {
     set v [string trim [lindex $rec 1] ";"]
     if { $v != "syncO" } {
       switch [lindex $rec 0] {
         byte   { puts $fid "	mapMessage->setByte( \"$v\", [set subsys]_ref->$v );" }
         short  { puts $fid "	mapMessage->setShort( \"$v\", [set subsys]_ref->$v );" }
         int    { puts $fid "	mapMessage->setInt( \"$v\", [set subsys]_ref->$v );" }
         long   { puts $fid "	mapMessage->setLong( \"$v\", [set subsys]_ref->$v );" }
         float  { puts $fid "	mapMessage->setFloat( \"$v\", [set subsys]_ref->$v );" } 
         double { puts $fid "	mapMessage->setDouble( \"$v\", [set subsys]_ref->$v );" } 
         char   { set cv [lindex [split $v "\[\]"] 0]
                  puts $fid "	strncpy(stringValue,[set subsys]_ref->$cv,$VPROPS($cv));"
                  puts $fid "	mapMessage->setString(  \"$v\", stringValue);"
                }
       }
     }
  }
  puts $fid "
        printf(\"Writing [set subsys], count %d\\n\", count);
        
        /* Write data */
        [set topic]_producer->send( mapMessage );
        Thread::sleep( 100 );
        [set subsys]_ref->syncO = 0;
    \}
"
}

proc addshmemcodesub { subsys fid } {
global VPROPS
  puts $fid "
   int [set subsys]_shmsize;
   int lshmid;
   int [set subsys]_shmid = 0x[calcshmid $subsys];
   [set subsys]_cache *[set subsys]_ref;
   [set subsys]_shmsize = sizeof(struct [set subsys]_cache);
   lshmid = shmget([set subsys]_shmid, [set subsys]_shmsize , IPC_CREAT|0666);
   [set subsys]_ref  = ([set subsys]_cache *) shmat(lshmid, NULL, 0);
   int ok=1;
   while (ok) \{
     cms::Message* message = [set topic]_consumer->receive( 1500 );
     if ( message != NULL ) \{
        cms::MapMessage* recvMapMessage = dynamic_cast<MapMessage*>( message );
        if ( recvMapMessage != NULL ) \{
"
  set fin [open [set subsys]_cache.h r]
  gets $fin rec
  gets $fin rec
  gets $fin rec
  gets $fin rec
  while { [gets $fin rec] > -1 } {
     set v [string trim [lindex $rec 1] ";"]
     if { $v != "syncO" } {
       switch [lindex $rec 0] {
         byte   { puts $fid "	[set subsys]_ref->$v = recvMapMessage->getByte ( \"$v\" );" }
         short  { puts $fid "	[set subsys]_ref->$v = recvMapMessage->getShort ( \"$v\" );" }
         int    { puts $fid "	[set subsys]_ref->$v = recvMapMessage->getInt ( \"$v\" );" }
         long   { puts $fid "	[set subsys]_ref->$v = recvMapMessage->getLong ( \"$v\" );" }
         float  { puts $fid "	[set subsys]_ref->$v = recvMapMessage->getFloat ( \"$v\" );" }
         double { puts $fid "	[set subsys]_ref->$v = recvMapMessage->getDouble ( \"$v\" );" }
         char   { set cv [lindex [split $v "\[\]"] 0]
                  puts $fid "	stringValue = recvMapMessage->getString ( \"$v\" );"
                  puts $fid "	strncpy([set subsys]_ref->$cv,stringValue,$VPROPS($cv));"
                }
       }
     }
  }
  puts $fid "    \}\n    delete message;\n  \} else \{\n     ok = 0;\n  \}\n\}"
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
  set ftst [open test_[set subsys].tcl w]
  puts $ftst "set SHM[set subsys](shmid) 0x[calcshmid $subsys]"
  set sval [lindex [exec grep "size_t [set subsys]_shmsize =" shmem_[set subsys]_server.cpp] 3]
  puts $ftst "set SHM[set subsys](shmsize) [string trim $sval ";"]"
  puts $ftst "load /home/shared/lsst/lib/libshm.so"
  puts $fout "
    if (strcmp(subsysid,\"$subsys\") == 0) {
       [set subsys]_cache *[set subsys]_ref;
       [set subsys]_ref = ([set subsys]_cache *)shmdata_ref;
"
  set fin [open [set subsys]_cache.h r]
  gets $fin rec
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
      text = Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
      sscanf(text,\"%d\", &[set subsys]_ref->$v);"
                puts $ftst "set SHM[set subsys]($v) 1"
              }
         long { puts $fout "
      text = Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
      sscanf(text,\"%ld\", &[set subsys]_ref->$v);"
                puts $ftst "set SHM[set subsys]($v) 1.2"
              }
         float { puts $fout "
      text = Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
      sscanf(text,\"%f\", &[set subsys]_ref->$v);"
                puts $ftst "set SHM[set subsys]($v) 1.23"
              }
         double { puts $fout "
      text = Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
      sscanf(text,\"%lf\", &[set subsys]_ref->$v);"
                puts $ftst "set SHM[set subsys]($v) 1.234"
              }
         char { puts $fout "
      text = Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$v\", TCL_GLOBAL_ONLY);
      strcpy([set subsys]_ref->$v,text);"
                puts $ftst "set SHM[set subsys]($v) \"test $v\""
             }
       }
     }
  }
    puts $fout "      [set subsys]_ref->syncO = 1;
    }"
  close $fout
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
global SHC
  set fout [open [set subsys]_activeMQ_publisher.c w]
  puts $fout $SHC(activemqshpub1.cpp)
  addshmemcodepub $subsys $fout
  puts $fout $SHC(activemqshpub2.cpp)
  close $fin
  close $fout
}

proc parsesub { subsys } {
global SHC
  set fout [open [set subsys]_activeMQ_subscriber.c w]
  puts $fout $SHC(activemqshsub1.cpp)
  addshmemcodesub $subsys $fout
  puts $fout $SHC(activemqshsub2.cpp)
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



set basedir .
set scriptdir /usr/local/scripts/tcl
set includedir /usr/local/scripts/include
source $scriptdir/managetypes.tcl


source $basedir/revCodes.tcl
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
      puts $fout $rec
      set t [lindex $rec 0]
      set TOPICPROPS($subsys) "$TOPICPROPS($subsys)\n$rec"
      incr TOPICPROPS(bytesize) $TYPESIZE($t)
     }
   }
}
puts $fout "  int syncO;"
puts $fout "\} [set subsys]_cache;"
close $fin
close $fout

set TOPICPROPS($subsys) "$TOPICPROPS($subsys)\n  int syncO;"
incr TOPICPROPS(bytesize) 4

puts stdout "Processing topic $subsys"
source $basedir/genericshmem.h.tcl
source $basedir/genericshmem.cpp.tcl
source $basedir/activemqclient.cpp.tcl
cd $workdir
doamqgen $subsys
shcoder $subsys
generatetcllib $subsys

