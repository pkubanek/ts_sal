#
# Generate SIMD interface for a subsystem topic
#
# To rebuild baseline cmake files 
#  export OSPL_HDE=/opt/OpenSplice/HDE/x86.linux2.6
#  cmake .
#
set SIMD_FILES "CMakeCache.txt cmake_install.cmake CMakeLists.txt Makefile
		svcSAL_TopicId.cpp svcSAL_TopicId.h svcSAL_TopicId.i
		svcSAL_TopicId_shm.cpp svcSAL_TopicId_shm.h
		simpletest-TopicId.cpp TopicId-asub.cpp TopicId-pub.cpp TopicId-sub.cpp
		simpleSHMtest-TopicId.cpp TopicId-shmsub.cpp TopicId-shmpub.cpp 
		svcSAL_TopicId-onlyshm.cpp svcSAL_TopicId-onlyshm.h svcSAL_TopicId-onlyshm.i
		CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.cpp
		CMakeFiles/TopicId-asub.dir/depend.make
		CMakeFiles/TopicId-asub.dir/progress.make
		CMakeFiles/TopicId-asub.dir/CXX.includecache
		CMakeFiles/TopicId-asub.dir/depend.internal
		CMakeFiles/TopicId-asub.dir/link.txt
		CMakeFiles/TopicId-asub.dir/cmake_clean.cmake
		CMakeFiles/TopicId-asub.dir/flags.make
		CMakeFiles/TopicId-asub.dir/build.make
		CMakeFiles/TopicId-asub.dir/DependInfo.cmake
		CMakeFiles/TargetDirectories.txt
		CMakeFiles/CMakeCXXCompiler.cmake
		CMakeFiles/Makefile2
		CMakeFiles/CMakeRuleHashes.txt
		CMakeFiles/progress.marks
		CMakeFiles/cmake.check_cache
		CMakeFiles/CMakeSystem.cmake
		CMakeFiles/CMakeDetermineCompilerABI_C.bin
		CMakeFiles/CMakeCCompiler.cmake
		CMakeFiles/datamodel.dir/depend.make
		CMakeFiles/datamodel.dir/cmake_clean_target.cmake
		CMakeFiles/datamodel.dir/progress.make
		CMakeFiles/datamodel.dir/CXX.includecache
		CMakeFiles/datamodel.dir/depend.internal
		CMakeFiles/datamodel.dir/link.txt
		CMakeFiles/datamodel.dir/cmake_clean.cmake
		CMakeFiles/datamodel.dir/flags.make
		CMakeFiles/datamodel.dir/build.make
		CMakeFiles/datamodel.dir/DependInfo.cmake
		CMakeFiles/CMakeDirectoryInformation.cmake
		CMakeFiles/Makefile.cmake"

set IDLPP_FILES "gen/TopicIdDcps.cpp  gen/TopicIdDcps.h  
		gen/TopicIdDcps_impl.cpp  gen/TopicIdDcps_impl.h
		TopicId-asub.cpp TopicId-pub.cpp TopicId-sub.cpp"

source $SAL_DIR/code/simd/gensimdmethods.tcl

proc gensimdcode { topic } {
global SIMD_FILES SAL_WORK_DIR OSPL_HDE SIMD_BASE_DIR 
global SAL_CMAKE_DIR SAL_DIR DDSGEN IDLPP_FILES
  exec mkdir -p $SAL_WORK_DIR/ospl-$topic/gen
  exec cp $SAL_WORK_DIR/idl-templates/validated/$topic.idl ospl-$topic/.
  set pcmd [open /tmp/pcmd w]
  puts $pcmd "#!/bin/sh"
  exec tar xzf $SAL_DIR/code/simd/CMakeFiles.tgz -C ./ospl-$topic 
  foreach bfile $SIMD_FILES {
     if { [lindex [split $bfile /] 0] != "CMakeFiles" } {
        exec cp $SAL_DIR/code/simd/$bfile $SAL_WORK_DIR/ospl-$topic/$bfile
     }
     set workdir [join [split [pwd]/ospl-$topic /] "\\/"]
     set simddir [join [split $SIMD_BASE_DIR /] "\\/"]
     set hdedir [join [split $OSPL_HDE /] "\\/"]
     set cmakedir [join [split $SAL_CMAKE_DIR /] "\\/"]
     puts $pcmd "perl -pi -w -e 's/TopicId/$topic/g;' $SAL_WORK_DIR/ospl-$topic/$bfile
perl -pi -w -e 's/SAL_WORK_DIR/$workdir/g;' $SAL_WORK_DIR/ospl-$topic/$bfile
perl -pi -w -e 's/OSPL_HDE/$hdedir/g;' $SAL_WORK_DIR/ospl-$topic/$bfile
perl -pi -w -e 's/SIMD_BASE_DIR/$simddir/g;' $SAL_WORK_DIR/ospl-$topic/$bfile
perl -pi -w -e 's/SAL_CMAKE_DIR/$cmakedir/g;' $SAL_WORK_DIR/ospl-$topic/$bfile"
  }
  close $pcmd
  exec chmod a+x /tmp/pcmd
  catch { set result [exec /tmp/pcmd] } bad
  stdlog "Generating DDS low-level code for $topic"
  cd $SAL_WORK_DIR/ospl-$topic
  set ddscmd [open /tmp/ddscmd w]
  puts $ddscmd "#!/bin/sh
$DDSGEN -d ./gen -S -l c++ [set topic].idl"
  close $ddscmd
  exec chmod a+x /tmp/ddscmd
  set bad 0
  catch { set result [exec /tmp/ddscmd] } bad
  if { $bad != "" } {
     errorexit "DDS generation failed : \n $bad"
  }
  stdlog "Generating simd interface and sample programs"
  set pcmd2 [open /tmp/pcmd2 w]
  puts $pcmd2 "#!/bin/sh"
  foreach bfile $IDLPP_FILES {
      exec cp $SAL_DIR/code/simd/$bfile $bfile
      puts $pcmd2 "perl -pi -w -e 's/TopicId/$topic/g;' $bfile"
  }
  close $pcmd2
  exec chmod a+x /tmp/pcmd2
  exec mv TopicId-asub.cpp $topic-asub.cpp 
  exec mv TopicId-pub.cpp $topic-pub.cpp 
  exec mv TopicId-sub.cpp $topic-sub.cpp
  catch { set result [exec cmake -DCMAKE_BUILD_TYPE=Debug .] } status
  foreach bfile $IDLPP_FILES {
      exec cp $SAL_DIR/code/simd/$bfile $bfile
  }
  fixup_buildmake $topic
  catch { set result [exec /tmp/pcmd2] } bad
  exec mv TopicId-asub.cpp $topic-asub.cpp 
  exec mv TopicId-pub.cpp $topic-pub.cpp 
  exec mv TopicId-sub.cpp $topic-sub.cpp
  exec mv TopicId-shmsub.cpp $topic-shmsub.cpp
  exec mv TopicId-shmpub.cpp $topic-shmpub.cpp
  exec mv svcSAL_TopicId.cpp svcSAL_$topic.cpp
  exec mv svcSAL_TopicId.h svcSAL_$topic.h
  exec mv svcSAL_TopicId.i svcSAL_$topic.i
  exec mv svcSAL_TopicId_shm.cpp svcSAL_[set topic]_shm.cpp
  exec mv svcSAL_TopicId_shm.h svcSAL_[set topic]_shm.h
  exec mv simpletest-TopicId.cpp simpletest-$topic.cpp
  exec mv simpleSHMtest-TopicId.cpp simpleSHMtest-$topic.cpp
  exec mv svcSAL_TopicId-onlyshm.h   svcSAL_[set topic]-onlyshm.h
  exec mv svcSAL_TopicId-onlyshm.i   svcSAL_[set topic]-onlyshm.i
  exec mv svcSAL_TopicId-onlyshm.cpp svcSAL_[set topic]-onlyshm.cpp
  exec mv gen/TopicIdDcps.cpp      gen/[set topic]Dcps.cpp
  exec mv gen/TopicIdDcps.h        gen/[set topic]Dcps.h
  exec mv gen/TopicIdDcps_impl.cpp gen/[set topic]Dcps_impl.cpp
  exec mv gen/TopicIdDcps_impl.h   gen/[set topic]Dcps_impl.h
  set result2 ""
  catch { set result2 [exec make] } status
  set incs [glob *.h gen/*.h]
  foreach i $incs {
     exec cp -v $i $SAL_WORK_DIR/include/$i
  }
  exec mkdir -p $SAL_WORK_DIR/lib
  stdlog "Generating SAL interface code for $topic"
###  simdlibrary $topic
  simdmethods $topic
  addsimdmethods $topic
  insertgenerated $topic
  cd ..
  return "$result\n$result2\n$status"
}

proc fixup_buildmake { topic } {
global OSPL_HDE SAL_WORK_DIR
  set fin [open $SAL_WORK_DIR/ospl-$topic/CMakeFiles/datamodel.dir/build.make r]
  set fout [open /tmp/fixmake w]
  while { [gets $fin rec] > -1 } {
     if { [lindex $rec 0] != "OSPL_HDE/bin/idlpp" } {
        puts $fout $rec
     } else {
        puts $fout "	$OSPL_HDE/bin/idlpp -I$OSPL_HDE/etc/idl -S -l cpp -d gen $topic.idl"
     }
  }
  close $fin
  close $fout
  exec cp /tmp/fixmake $SAL_WORK_DIR/ospl-$topic/CMakeFiles/datamodel.dir/build.make
}

proc checksimd { idldir } {
global IDL_DIR
   set all [lsort [glob $IDL_DIR/*.idl]]
   foreach f  $all {
      stdlog "Processing $f"
      exec cp $f .
      set t [file rootname [file tail $f]]
      set res [gensimdcode $t]
      stdlog "[exec date] : Results $res"
      stdlog "\n-----------------------------------------------------------\n"
   }
}

proc getalltopics { {subsys ""} } {
global IDL_DIR
   set all [lsort [glob $IDL_DIR/$subsys*.idl]]
   foreach f  $all {
      lappend rest [file rootname [file tail $f]]
   }
   return [lsort $rest]
}

proc getsubsystem { topic } {
global SAL_SUBSYSTEMS
   foreach s $SAL_SUBSYSTEMS {
      set l [expr [string length $s] -1]
      if { [string range $topic 0 $l] == $s } {
        return $s
      }
   }
   return ""
}



proc simdlibrary { topic {op r} } {
global IDL_DIR SAL_WORK_DIR SAL_SUBSYSTEMS
   switch $topic {
       all   {
                set tall [getalltopics]
                foreach t $tall {
                   set objs [glob $SAL_WORK_DIR/ospl-$t/CMakeFiles/datamodel.dir/gen/*.o]
                   exec cp $SAL_WORK_DIR/ospl-$t/svcSAL_$t.h $SAL_WORK_DIR/include/.
                   foreach o $objs {
                     exec ar $op $SAL_WORK_DIR/lib/libsal_simd.a $o
                   }
                   stdlog "Updated topic $t in libsal_simd"
                }
                foreach s $SAL_SUBSYSTEMS {
                   catch {exec ar r $SAL_WORK_DIR/lib/libsal_[set s]_simd.a}
                   foreach o $objs {
                     exec ar $op $SAL_WORK_DIR/lib/libsal_[set s]_simd.a $o
                     exec cp $SAL_WORK_DIR/ospl-[set s]/svcSAL_[set s].h $SAL_WORK_DIR/include/.
                   }
                   stdlog "Updated subsystem $s in libsal_[set s]_simd"
                   exec ranlib $SAL_WORK_DIR/lib/libsal_[set s]_simd.a
                }
             }
       default {
                   set s [getsubsystem $topic]
                   exec cp $SAL_WORK_DIR/ospl-[set topic]/svcSAL_[set topic].h $SAL_WORK_DIR/include/.
                   set objs [glob $SAL_WORK_DIR/ospl-$topic/CMakeFiles/datamodel.dir/gen/*.o]
                   foreach o $objs {
                     exec ar $op $SAL_WORK_DIR/lib/libsal_simd.a $o
                     exec ar $op $SAL_WORK_DIR/lib/libsal_[set s]_simd.a $o
                   }
                   exec ranlib $SAL_WORK_DIR/lib/libsal_[set s]_simd.a
                   stdlog "Updated topic $topic in libsal_[set s]_simd"
                   stdlog "Updated topic $topic in libsal_simd"
                   updatevalidtopics $s
                   
             }
   }
   exec ranlib $SAL_WORK_DIR/lib/libsal_simd.a
}


proc makevalidtopics { } {
global SAL_DIR SAL_SUBSYSTEMS SAL_SID
   set fout [open $SAL_DIR/code/simd/svcSAL_validtopics.h w]
   puts $fout "#if !defined(__INCLUDED_SAL_VALIDTOPICS)"
   puts $fout "#define __INCLUDED_SAL_VALIDTOPICS"
   foreach s $SAL_SUBSYSTEMS {
      puts $fout "#include \"svcSAL_[set s]_topics.h\""
      updatevalidtopics $s
   }
   puts $fout "#endif\n"
   close $fout
   set ptcode [lsort [glob $SAL_DIR/code/simd/svcSAL.*_topics]]
   set dest $SAL_DIR/code/simd
   exec cp $dest/svcSAL.cpp.head $dest/svcSAL.cpp
   foreach f $ptcode {
      exec cat $f >> $dest/svcSAL.cpp
   }
   exec cat $dest/svcSAL.cpp.tail >> $dest/svcSAL.cpp
}

proc calcshmid { subsys } {
  set fout [open /tmp/subsys.tmp w]
  puts $fout "$subsys"
  close $fout
  set id [string range [exec md5sum /tmp/subsys.tmp] 0 3]
  return $id
}

proc updatevalidtopics { s } {
global SAL_DIR SAL_SUBSYSTEMS SAL_SID SAL_WORK_DIR
      stdlog "Creating svcSAL.cpp.[set s]_topics"
      stdlog "Creating svcSAL_[set s]_topics.h"
      set fo3 [open $SAL_DIR/code/simd/svcSAL.cpp.[set s]_topics w]
      set fo2 [open $SAL_DIR/code/include/sal/svcSAL_[set s]_topics.h w]
      puts $fo2 "#if !defined(__INCLUDED_SAL_[set s]_TOPICS)"
      puts $fo2 "#define __INCLUDED_SAL_[set s]_TOPICS"
      set topicdirs [lsort [glob $SAL_WORK_DIR/ospl-$s*]]
      foreach t $topicdirs {
         set id [string range [file tail [file root $t]] 5 end]
         puts $fo2 "#include \"svcSAL_[set id]_iid.h\""
         puts $fo2 "#define SAL_SHMEM_KEY_[set id] 0x[calcshmid $id]"
         puts $fo3 "
	    case SAL_IID_$id :
	    	salTopic = ([set id] *)new [set id]();
		result = SAL__OK;
		break;
"
      }
      foreach t $topicdirs {
         set id [string range [file tail [file root $t]] 5 end]
         set mdid [lindex [exec md5sum $t/$id.idl] 0]
         set tid "0x[string range $mdid 26 end]"
         set SAL_SID($id) $tid
         puts $fo2 "#define SAL_SID_$id $tid"
         puts stdout "Done $id"
      }
      puts $fo2 "#endif\n"
      close $fo2
      close $fo3
}



		


