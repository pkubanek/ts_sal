#
#  Generate Java jsimd interface for a DDS topic
#

proc add_jsimd_printer { topic fid items } {
  set rec "                            out.println(\"(\""
  foreach i $items { 
     set size [lindex $i 1]
     set type [lindex $i 2]
     if { $size > 1  && ([string range $type 0 5] != "string") } {
        set rec "$rec + Arrays.toString(s.[lindex $i 0]) + \",\""
     } else {
        set rec "$rec + s.[lindex $i 0] + \",\""
     }
  }
  set res "[string trimright $rec " \","] \")\");"
  puts $fid $res
}

proc add_jsimd_simulator { topic fid items } {
  foreach i $items {
    set tname [join [split $topic .] _]
    set name [join [split [lindex $i 0] .] _]
    set size [lindex $i 1]
    set type [lindex $i 2]
    if { [string range $type 0 5] == "string" } {set type "string"}
    switch $type {
       char   { 
                if { $size > 1 } {
                   puts $fid "
            for(j=0; j<$size; j++) \{         
              $tname.$name\[j\] = 0x99;
            \}"
                } else {
                   puts $fid "            $tname.$name = 0x99;"
                }
              }
       boolean { 
                if { $size > 1 } {
                   puts $fid "
            for(j=0; j<$size; j++) \{         
              $tname.$name\[j\] = Boolean.TRUE;
            \}"
                } else {
                   puts $fid "            $tname.$name = Boolean.TRUE;"
                }
              }
       byte   -
       short  -
       int    -
       longlong -
       long   { 
                set q ""
                if { $type == "short" } {set q "(short)"}
                if { $size > 1 } {
                   puts $fid "
            for(j=0; j<$size; j++) \{         
              $tname.$name\[j\] = $q generator.nextInt(250);
            \}"
                } else {
                   puts $fid "            $tname.$name = $q generator.nextInt(250);"
                }
              }
       float  -
       double {
                set q ""
                if { $type == "float" } {set q "(float)"}
                if { $size > 1 } {
                   puts $fid "
            for(j=0; j<$size; j++) \{          
              $tname.$name\[j\] = $q generator.nextDouble();
            \}"
                } else {
                   puts $fid "            $tname.$name = $q generator.nextDouble();"
                }
              }
       string {
                 puts $fid "              $tname.$name = date.toString();"
              }
    }
  }
}

proc jsimd_preprocess { tname } {
  set items [getitemlist $tname]
  foreach template "Publisher Subscriber" {
     set fin [open [set tname]_[set template].java r]
     set fid [open temp.java w]
     while { [gets $fin rec] > -1 } {
        if { [string range $rec 0 16] == "###SAL_DATA_PRINT" } {
           add_jsimd_printer $tname $fid $items
        } else {
           if { [string range $rec 0 14] == "###SAL_DATA_SIM" } {
              add_jsimd_simulator $tname $fid $items
           } else {
              puts $fid $rec
           }
        }
     }
     close $fin
     close $fid
     exec mv temp.java  [set tname]_[set template].java
     puts stdout "Preprocessed [set tname]_[set template].java"
  }
}

proc jsimdmodidl { tname } {
global SAL_DIR SAL_WORK_DIR DDSGEN
  set fin [open $SAL_WORK_DIR/idl-templates/validated/[set tname].idl r]
  set fout [open $SAL_WORK_DIR/simd-java/idlib/src/main/idl/[set tname].idl w]
  puts $fout "module org \{ module opensplice \{ module demo \{"
  puts $fout "  struct sal_[set tname]Type \{"
  gets $fin rec
  while { [gets $fin rec] > -1 } {
     if { [string range $rec 0 6] == "#pragma" } {gets $fin rec}
     if { [lindex $rec 0] == "longlong" } { 
        set rec "  long long [lindex $rec 1]"
     }
     if { [lindex $rec 1] == "longlong" } { 
        set rec "  unsigned long long [lindex $rec 2]"
     }
     puts $fout "  $rec"
puts stdout $rec
  }
  puts $fout "#pragma keylist sal_[set tname]Type
\}; \}; \};
"
  close $fout
  puts stdout "Generated jsimd compatible $SAL_WORK_DIR/simd-java/idlib/src/main/idl/[set tname].idl"
}


proc genjsimdcode { topic } {
global SAL_DIR SAL_WORK_DIR DDSGEN
   set tname [join [split $topic .] _]
   jsimdmodidl $tname
   if { [file exists $SAL_WORK_DIR/simd-java] == 0 } {
      exec mkdir -p $SAL_WORK_DIR/simd-java
      puts stdout "Unpacking SAL jsimd support to $SAL_WORK_DIR/simd-java"
      cd $SAL_WORK_DIR/simd-java
      exec tar -C $SAL_WORK_DIR/simd-java -xzf $SAL_DIR/code/jsimd/saljsimd.tgz
   }
   exec mkdir -p $SAL_WORK_DIR/simd-java/src/main/java/org/opensplice/demo/sal_$tname
   cd $SAL_WORK_DIR/simd-java/src/main/java/org/opensplice/demo/sal_$tname
   exec cp $SAL_DIR/code/jsimd/SALPublisher.java  [set tname]Publisher.java
   exec cp $SAL_DIR/code/jsimd/SALSubscriber.java [set tname]Subscriber.java
   set frep [open /tmp/jsimdrep w]
   puts $frep "
#!/bin/sh
perl -pi -w -e 's/SALTOPIC/$tname/g;' [set tname]Publisher.java
perl -pi -w -e 's/SALTOPIC/$tname/g;' [set tname]Subscriber.java
"
   close $frep
   exec chmod a+x /tmp/jsimdrep
   catch { set result [exec /tmp/jsimdrep] } bad 
   jsimd_preprocess $tname
   set fout [open /tmp/ddsjsimd w]
   puts $fout "#!/bin/sh
source $SAL_DIR/setup.env
cd $SAL_WORK_DIR/simd-java/idlib/src/main/java"
idlpp -S -l java ../[set topic].idl"
   close $fout
   exec chmod a+x /tmp/ddsjsimd
   catch { set result [exec /tmp/ddsjsimd] } bad
   return 0
}

source $SAL_DIR/getitemlist.tcl


