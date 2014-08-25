
set SALTYPES(octet) UCHAR
set SALTYPES(short) SHORT
set SALTYPES(unsignedshort) USHORT
set SALTYPES(long) LONG
set SALTYPES(unsignedlong) ULONG 
set SALTYPES(float) FLOAT
set SALTYPES(double) DOUBLE
set SALTYPES(octetarray) UCHAR
set SALTYPES(shortarray) SHORT
set SALTYPES(unsignedshortarray) USHORT
set SALTYPES(longarray) LONG
set SALTYPES(unsignedlongarray) ULONG 
set SALTYPES(floatarray) FLOAT
set SALTYPES(doublearray) DOUBLE

set SALFORMATS(octet) "%d"
set SALFORMATS(short) "%d"
set SALFORMATS(unsignedshort) "%d"
set SALFORMATS(long) "%ld"
set SALFORMATS(unsignedlong) "%ld"
set SALFORMATS(float)  "%lf"
set SALFORMATS(double) "%lf"
set SALFORMATS(octetarray) "%d"
set SALFORMATS(shortarray)  "%d"
set SALFORMATS(unsignedshortarray) "%d"
set SALFORMATS(longarray) "%ld"
set SALFORMATS(unsignedlongarray) "%ld"
set SALFORMATS(floatarray) "%f"
set SALFORMATS(doublearray) "%lf"

proc genallmethods { } {
global SAL_DIR
  set topics [lsort [glob $SAL_DIR/code/simd/svcSAL_*_iid.h]]
  foreach t $topics {
     set id [string range [file tail $t] 7 end]
     set l [expr [string length $id]-7]
     set tname [string range $id 0 $l]
     if { [lindex [split $tname _] end] != "command" && [lindex [split $tname _] end] != "response" } {
       stdlog "Gnerating methods for $tname"
       simdmethods $tname
     }
  }
}

proc addsimdmethods { topic } {
global SAL_WORK_DIR SAL_DIR
  foreach f "svcSAL_[set topic].cpp svcSAL_[set topic]_shm.cpp" {
   set fin [open $SAL_WORK_DIR/ospl-$topic/$f r]
   set fout [open /tmp/[set topic]methods.gen w]
   while { [gets $fin rec] > -1 } {
     if { [string range $rec 0 25] != "// INSERT PERTOPIC_METHODS" } {
        puts $fout $rec
     } else {
        set fi2 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.methods r]
        while { [gets $fi2 r2]  > -1 } {
            puts $fout $r2
        }
        close $fi2
     }
   }
   close $fin
   close $fout
   exec mv /tmp/[set topic]methods.gen $SAL_WORK_DIR/ospl-$topic/$f
  }
}

proc insertgenerated { topic } {
global SAL_WORK_DIR SAL_DIR
   foreach f   "simpletest-[set topic]
         	simpleSHMtest-[set topic]
		[set topic]-shmsub
		[set topic]-shmpub" {
      set fin [open $SAL_WORK_DIR/ospl-$topic/[set f].cpp r]
      set fout [open /tmp/$f.gen w]
      stdlog "Inserting code for $f"
      while { [gets $fin rec] > -1 } {
         if { [string range $rec 0 8] != "// INSERT" } {
            puts $fout $rec
         } else {
            set source [lindex $rec 2]
            switch $source {
              TOPIC_LOCALITEMS {set fi2 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.locals r]}
              COPY_FROM_SHM    {set fi2 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.fromshm r]}
              COPY_TO_SHM      {set fi2 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.toshm r]}
              PUBLISH_SAMPLE   {set fi2 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.setitems r]}
              READ_SAMPLE      {set fi2 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.getitems r]}
            }
            while { [gets $fi2 r2]  > -1 } {
               puts $fout $r2
            }
            close $fi2
        }
      }
      close $fin
      close $fout
      exec mv /tmp/$f.gen $SAL_WORK_DIR/ospl-$topic/[set f].cpp
   }
}


proc simdmethods { topic } {
global SAL_DIR SALTPYES
global Ptypes Psizes
   stdlog "Generating interface stubs for $topic"
   catch {unset Ptypes}
   catch {unset Psizes}
   set fin  [open $SAL_DIR/code/include/sal/svcSAL_[set topic]_iid.h r]
   set fout [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.methods w]
   set fo2 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.toshm w]
   set fo3 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.fromshm w]
   set fo4 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.setitems w]
   set fo5 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.getitems w]
   puts $fo5 "		result = salHandle->getSample(SAL__SLOWPOLL);"
   set fo6 [open $SAL_DIR/code/simd/svcSAL_[set topic].cpp.locals w]
   gets $fin rec
   gets $fin rec
   gets $fin rec
   while { [gets $fin rec] > 0 } {
      set props [lindex [split $rec "/"] 2]
      set id [lindex $props 0]
      set Psizes($id) [lindex $props 2]
      if { $Psizes($id) > 1 && [lindex $props 1] != "string" } {
         lappend Ptypes([lindex $props 1]array) $id
      } else {
         lappend Ptypes([lindex $props 1]) $id
      }
   }
   close $fin
   foreach t "octet short unsignedshort long unsignedlong float double string octetarray shortarray unsignedshortarray longarray unsignedlongarray floatarray doublearray" {
      if { [info exists Ptypes($t)] } {
         switch $t {
               string { dostringitems $fout $topic
                        doshmstrings $fo2 $fo3 $fo4 $fo5 string $topic
                        dolocaldefs $fo6 string $topic
               }
               octet -
               short -
               unsignedshort -
               long - 
               unsignedlong - 
               float - 
               double { doscalaritems $fout $t $topic
                        doshmscalars $fo2 $fo3 $fo4 $fo5 $t $topic 
                        dolocaldefs $fo6 $t $topic
               }
               octetarray -
               shortarray -
               unsignedshortarray -
               longarray - 
               unsignedlongarray - 
               floatarray - 
               doublearray { doarrayitems $fout $t $topic
                             doshmarrays $fo2 $fo3 $fo4 $fo5 $t $topic
                             dolocaldefs $fo6 $t $topic array
               }
         }
         doitemsastext $fout $topic
      }
   }
   puts $fo2 "		[set topic]_ref->syncI++;"
   puts $fo3 "		[set topic]_ref->syncO = 1;"
   close $fout
   close $fo2
   close $fo3
   puts $fo4 "		result = salHandle->putSample();"
   close $fo4
   close $fo5
   close $fo6
   return 0
}


proc doitemsastext { fout topic } {
global Ptypes Psizes SALFORMATS
  puts $fout "
       svcRTN sal[set topic]::setItemStr ( svcIID itemId , svcCHAR *textValue)
	\{
	    svcRTN result = SAL__NOT_DEFINED;
	    
	    switch (itemid) \{"
  foreach t [array names Ptypes] {
     switch $t {
               octet -
               short -
               unsignedshort -
               long - 
               unsignedlong - 
               float - 
               double {
                       foreach i [lsort $Ptypes($t)] {
                          puts $fout "
                 case SAL_IID_[set topic]_[set i] :
                      sscanf(textValue,\"$SALFORMATS($t)\",\&data.$i);
                      result = SAL__OK;
                      break;"
                       }
                }        
     } 
  }
  puts $fout "
	    \}
	    return result;
	\}"
  puts $fout "
       svcRTN sal[set topic]::getItemStr ( svcIID itemId , svcCHAR *textValue)
	\{
	    svcRTN result = SAL__NOT_DEFINED;
	    
	    switch (itemid) \{"
  foreach t [array names Ptypes] {
     switch $t {
               octet -
               short -
               unsignedshort -
               long - 
               unsignedlong - 
               float - 
               double {
                       foreach i [lsort $Ptypes($t)] {
                          puts $fout "
                 case SAL_IID_[set topic]_[set i] :
                      sprintf(textValue,\"$SALFORMATS($t)\",data.$i);
                      result = SAL__OK;
                      break;"
                       }
               }        
     } 
  }
  puts $fout "
	    \}
	    return result;
	\}"
}


proc dostringitems { fout topic } {
global Ptypes Psizes
  puts $fout "
	svcRTN sal[set topic]::getItem ( svcIID itemId , (svcCHAR *)value )
	\{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (itemId) \{
	    
"
  foreach i [lsort $Ptypes(string)] {
    puts $fout "
                 case SAL_IID_[set topic]_[set i] :
                      strncpy(value, data.$i, $Psizes($i));
                      result = SAL__OK;
                      break;
"
  }
  puts $fout "
	    \}
	    return result;
	\}
	
"
  puts $fout "
	svcRTN sal[set topic]::setItem ( svcIID itemId , (svcCHAR *)value )
	\{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (itemId) \{
	    
"
  foreach i [lsort $Ptypes(string)] {
    puts $fout "
                 case SAL_IID_[set topic]_[set i] :
                      strncpy(data.$i, value, $Psizes($i));
                      result = SAL__OK;
                      break;
"
  }
  puts $fout "
	    \}
	    return result;
	\}
	
"
}

proc doshmscalars { fo2 fo3 fo4 fo5 type topic } {
global SALTYPES Ptypes Psizes
#puts stdout "doshmcalars $type $topic"
  foreach i [lsort $Ptypes($type)] {
    puts $fo2 "		[set topic]_ref->$i = samples\[i\].$i;"
    puts $fo3 "		d.$i = [set topic]_ref->$i;"
    puts $fo4 "		result = salHandle->setitem(SAL_IID_[set topic]_[set i], $i);"
    puts $fo5 "		result = salHandle->getitem(SAL_IID_[set topic]_[set i], $i);"
  }
}

proc doshmarrays { fo2 fo3 fo4 fo5 type topic } {
global SALTYPES Ptypes Psizes
#puts stdout "doshmarrays $type $topic"
  foreach i [lsort $Ptypes($type)] {
    puts $fo2 "		for (unsigned int count=0; count<$Psizes($i); count++) \{"
    puts $fo2 "			[set topic]_ref->$i\[count\] = samples\[i\].$i\[count\];"
    puts $fo2 "		\}"
    puts $fo3 "		for (unsigned int count=0; count<$Psizes($i); count++) \{"
    puts $fo3 "			d.$i\[count\] = [set topic]_ref->$i\[count\];"
    puts $fo3 "		\}"
    puts $fo4 "		result = salHandle->setitem(SAL_IID_[set topic]_[set i], $i, $Psizes($i));"
    puts $fo5 "		result = salHandle->getitem(SAL_IID_[set topic]_[set i], $i, $Psizes($i));"
  }
}

proc doshmstrings { fo2 fo3 fo4 fo5 type topic } {
global SALTYPES Ptypes Psizes
#puts stdout "doshmstrings $type $topic"
  foreach i [lsort $Ptypes($type)] {
    puts $fo2 "		strncpy([set topic]_ref->$i,samples\[i\].$i,$Psizes($i));"
    puts $fo3 "		strncpy(d.$i,[set topic]_ref->$i,$Psizes($i));"
    puts $fo4 "		result = salHandle->setitem(SAL_IID_[set topic]_[set i], $i);"
    puts $fo5 "		result = salHandle->getitem(SAL_IID_[set topic]_[set i], $i);"
  }
}

proc dolocaldefs { fo6 type topic {dim ""} } {
global SALTYPES Ptypes Psizes
#puts stdout "dolocaldefs $type $topic"
  foreach i [lsort $Ptypes($type)] {
     if { $type == "string" } {
        puts $fo6 "	char	\[$Psizes($i)\];"
     } else {
       if { $dim == "array" } {
          puts $fo6 "	svc$SALTYPES($type)	$i\[$Psizes($i)\];"
       } else {
         puts $fo6 "	svc$SALTYPES($type)	$i;"
       }
     }
  }  
}



proc doscalaritems { fout type topic } {
global SALTYPES Ptypes Psizes
  puts $fout "
	svcRTN sal[set topic]::getItem ( svcIID itemId , svc$SALTYPES($type) \&value )
	\{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (itemId) \{"
  foreach i [lsort $Ptypes($type)] {
    puts $fout "
                 case SAL_IID_[set topic]_[set i] :
                      value = data.$i;
                      result = SAL__OK;
                      break;"
  }
  puts $fout "
	    \}
	    return result;
	\}
	
"
  puts $fout "
	svcRTN sal[set topic]::setItem ( svcIID itemId , svc$SALTYPES($type) \&value )
	\{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (itemId) \{"
  foreach i [lsort $Ptypes($type)] {
     puts $fout "
                 case SAL_IID_[set topic]_[set i] :
                      data.$i = value;
                      result = SAL__OK;
                      break;"
     }
     puts $fout "
	    \}
	    return result;
	\}
	
"
}


proc doarrayitems { fout type topic } {
global SALTYPES Ptypes Psizes
  puts $fout "
	svcRTN sal[set topic]::getItem ( svcIID itemId , svc$SALTYPES($type) \&value, svcUINT size)
	\{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (itemId) \{"
  foreach i [lsort $Ptypes($type)] {
    puts $fout "
                 case SAL_IID_[set topic]_[set i] :
                      if \{ size > $Psizes($i) \} \{return SAL__INDEX_OUT_OF_RANGE;\}
                      for (unsigned int count=0; count<size; count++) \{
                        value\[count\] = data.$i\[count\];
                      \}
                      result = SAL__OK;
                      break;"
  }
  puts $fout "
	    \}
	    return result;
	\}"
  puts $fout "
 	svcRTN sal[set topic]::setItem ( svcIID itemId , svc$SALTYPES($type) \&value , svcUINT size)
	\{
	    svcRTN result = SAL__NOT_DEFINED;
	    switch (itemId) \{"
  foreach i [lsort $Ptypes($type)] {
    puts $fout "
                 case SAL_IID_[set topic]_[set i] :
                      if \{ size > $Psizes($i) \} \{return SAL__INDEX_OUT_OF_RANGE;\}
                      for (unsigned int count=0; count<size; count++) \{
                        data.$i\[count\] = value\[count\];
                      \}
                      result = SAL__OK;
                      break;"
  }
  puts $fout "
	    \}
	    return result;
	\}"
}




