#!/usr/bin/env tclsh
#
#  Generate simple pub/sub programs for each data type in cpp and java
#
proc makesaldirs { base name } {
global SAL_WORK_DIR OPTIONS
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> makesaldirs $base $name"}
   exec mkdir -p $SAL_WORK_DIR/[set base]_[set name]/python
   exec mkdir -p $SAL_WORK_DIR/[set base]_[set name]/cpp/src
   exec mkdir -p $SAL_WORK_DIR/[set base]_[set name]/cpp/standalone
   exec mkdir -p $SAL_WORK_DIR/[set base]_[set name]/isocpp
   exec mkdir -p $SAL_WORK_DIR/[set base]_[set name]/java/src/org/lsst/sal
   exec mkdir -p $SAL_WORK_DIR/[set base]_[set name]/java/src/org/lsst/sal/$base/$name
   exec mkdir -p $SAL_WORK_DIR/[set base]/java/src
   exec mkdir -p $SAL_WORK_DIR/[set base]/java/src/org/lsst/sal
   exec mkdir -p $SAL_WORK_DIR/[set base]/cpp/src
   exec mkdir -p $SAL_WORK_DIR/[set base]/isocpp/src
   exec mkdir -p $SAL_WORK_DIR/[set base]_[set name]/java/standalone
   exec touch $SAL_WORK_DIR/[set base]/java/src/.depend.Makefile.saj_[set base]_cmdctl
   exec touch $SAL_WORK_DIR/[set base]/java/src/.depend.Makefile.saj_[set base]_event
   exec touch $SAL_WORK_DIR/[set base]_[set name]/java/standalone/.depend.Makefile.saj_[set base]_[set name]_pub
   exec touch $SAL_WORK_DIR/[set base]_[set name]/java/standalone/.depend.Makefile.saj_[set base]_[set name]_sub
   exec touch $SAL_WORK_DIR/[set base]_[set name]/cpp/standalone/.depend.Makefile.sacpp_[set base]_[set name]_pub
   exec touch $SAL_WORK_DIR/[set base]_[set name]/cpp/standalone/.depend.Makefile.sacpp_[set base]_[set name]_sub
   exec touch $SAL_WORK_DIR/[set base]/cpp/src/.depend.Makefile.sacpp_[set base]_cmd
   exec touch $SAL_WORK_DIR/[set base]/cpp/src/.depend.Makefile.sacpp_[set base]_event
   exec touch $SAL_WORK_DIR/[set base]/cpp/src/.depend.Makefile.sacpp_[set base]_testcommands
   exec touch $SAL_WORK_DIR/[set base]/cpp/src/.depend.Makefile.sacpp_[set base]_testevents
   exec ln -sf $SAL_WORK_DIR/idl-templates/validated/sal/sal_revCoded_$base.idl $SAL_WORK_DIR/$base/cpp/sal_$base.idl
   exec ln -sf $SAL_WORK_DIR/idl-templates/validated/sal/sal_revCoded_$base.idl $SAL_WORK_DIR/$base/isocpp/sal_$base.idl
   exec touch $SAL_WORK_DIR/[set base]/cpp/.depend.Makefile.sacpp_[set base]_types
   exec touch $SAL_WORK_DIR/[set base]/java/.depend.Makefile.saj_[set base]_types
   exec touch $SAL_WORK_DIR/[set base]/isocpp/.depend.Makefile.ISO_Cxx_[set base]_types
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< makesaldirs $base $name"}
}


proc addlvtypes { fhlv } {
  puts $fhlv "
typedef signed char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int int64_t;
typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long int uint64_t;
typedef unsigned char bool_t;
typedef struct \{
	int size;
	bool_t data\[1\];
\} BooleanArray;
typedef BooleanArray** BooleanArrayHdl;


typedef struct \{
	int size;
	int8_t data\[1\];
\} I8Array;
typedef I8Array** I8ArrayHdl;

typedef struct \{
	int size;
	int16_t data\[1\];
\} I16Array;
typedef I16Array** I16ArrayHdl;

typedef struct \{
	int size;
	int data\[1\];
\} I32Array;
typedef I32Array** I32ArrayHdl;

typedef struct \{
	int size;
	int64_t data\[1\];
\} I64Array;
typedef I64Array** I64ArrayHdl;

typedef struct \{
	int size;
	uint8_t data\[1\];
\} U8Array;
typedef U8Array** U8ArrayHdl;

typedef struct \{
	int size;
	uint16_t data\[1\];
\} U16Array;
typedef U16Array** U16ArrayHdl;

typedef struct \{
	int size;
	uint32_t data\[1\];
\} U32Array;
typedef U32Array** U32ArrayHdl;

typedef struct \{
	int size;
	uint64_t data\[1\];
\} U64Array;
typedef U64Array** U64ArrayHdl;

typedef struct \{
	int size;
	float data\[1\];
\} SGLArray;
typedef SGLArray** SGLArrayHdl;

typedef struct \{
	int size;
	double data\[1\];
\} DBLArray;
typedef DBLArray** DBLArrayHdl;

typedef struct \{
	int size;
	char data\[1\];
\} Str;
typedef Str** StrHdl;

typedef struct \{
	int size;
	StrHdl data\[1\];
\} StrArray;
typedef StrArray** StrArrayHdl;
"
}



proc makesalidl { subsys } {
global SAL_DIR SAL_WORK_DIR SYSDIC VPROPS EVENT_ENUM OPTIONS CMD_ALIASES
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> makesalidl $subsys"}
   set all [lsort [glob $SAL_WORK_DIR/idl-templates/validated/[set subsys]_*.idl]]
   exec mkdir -p $SAL_WORK_DIR/idl-templates/validated/sal
   set fout [open $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl w]
   exec mkdir -p $SAL_WORK_DIR/[set subsys]/cpp/src
   catch {
     set prev [glob $SAL_WORK_DIR/include/SAL_[set subsys]*]
     foreach f $prev {exec rm $f}
   }
   set fhdr [open $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys]C.h w]
   set fhlv [open $SAL_WORK_DIR/[set subsys]/cpp/src/SAL_[set subsys]LV.h w]
   addlvtypes $fhlv
   puts $fhdr "
#ifndef _SAL_[set subsys]C_
#define _SAL_[set subsys]C_

#include <string>

using namespace std;
"
   set fbst [open $SAL_WORK_DIR/include/SAL_[set subsys]C.bp w]
   set fbst2 [open $SAL_WORK_DIR/include/SAL_[set subsys]C.bp2 w]
   set fpyb [open $SAL_WORK_DIR/include/SAL_[set subsys]C.pyb w]
   set fpyb2 [open $SAL_WORK_DIR/include/SAL_[set subsys]C.pyb2 w]
   puts $fout "module $subsys \{"
   foreach i $all {
     stdlog "Adding $i to sal_$subsys.idl"
     set fin [open $i r]
     gets $fin rec
     set name [join [lrange [split [file rootname [file tail $i]] _] 1 end] _]
     if { $name != "ackcmd" } {
      set VPROPS(iscommand) 0
      if { [string range $name 0 7] == "command_" } {set VPROPS(iscommand) 1}
      set fcod1 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Cget.tmp w]
      set fcod1b [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]LCget.tmp w]
      set fcod2 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Cput.tmp w]
      set fcod2b [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Cchk.tmp w]
      set fcod3 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Csub.tmp w]
      set fcod4 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Cpub.tmp w]
      set fcod5 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Cargs.tmp w]
      set fcod6 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Cout.tmp w]
      set fcod7 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]shmout.tmp w]
      set fcod8 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]shmin.tmp w]
      set fcod10 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Pargs.tmp w]
      set fcod11 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Ppub.tmp w]
      set fcod12 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]monout.tmp w]
      set fcod13 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]monin.tmp w]
###      set fcod14 [open $SAL_WORK_DIR/include/SAL_[set subsys]_[set name]Jsub.tmp w]
      puts $fout "	struct $name \{"
      puts $fhdr "struct [set subsys]_[set name]C
\{"
      puts $fhlv "typedef struct [set subsys]_[set name]LV \{"
      puts $fbst "   bp::class_<[set subsys]_[set name]C>(\"[set subsys]_[set name]C\")"
      puts $fpyb "   py::class_<[set subsys]_[set name]C>(m,\"[set subsys]_[set name]C\")
      .def(py::init<>())"
      if {[string range $name 0 7] != "command_" && [string range $name 0 8] != "logevent_"}  {
        puts $fbst2 "
  .def(\"getSample_[set name]\" ,  &::SAL_[set subsys]::getSample_[set name] )
  .def(\"getNextSample_[set name]\" ,  &::SAL_[set subsys]::getNextSample_[set name] )
  .def(\"flushSamples_[set name]\" ,  &::SAL_[set subsys]::flushSamples_[set name] )
  .def(\"putSample_[set name]\" ,  &::SAL_[set subsys]::putSample_[set name] )"
        puts $fpyb2 "
  .def(\"getSample_[set name]\" ,  &SAL_[set subsys]::getSample_[set name] )
  .def(\"getNextSample_[set name]\" ,  &SAL_[set subsys]::getNextSample_[set name] )
  .def(\"getLastSample_[set name]\" ,  &SAL_[set subsys]::getLastSample_[set name] )
  .def(\"flushSamples_[set name]\" ,  &SAL_[set subsys]::flushSamples_[set name] )
  .def(\"putSample_[set name]\" ,  &SAL_[set subsys]::putSample_[set name] )"
      }
      if {[string range $name 0 8] == "logevent_"}  {
        puts $fbst2 "
  .def(\"flushSamples_[set name]\" ,  &::SAL_[set subsys]::flushSamples_[set name] )"
        puts $fpyb2 "
  .def(\"flushSamples_[set name]\" ,  &SAL_[set subsys]::flushSamples_[set name] )
  .def(\"getSample_[set name]\" ,  &SAL_[set subsys]::getSample_[set name] )
  .def(\"getLastSample_[set name]\" ,  &SAL_[set subsys]::getLastSample_[set name] )
  .def(\"getNextSample_[set name]\" ,  &SAL_[set subsys]::getNextSample_[set name] )"
      }
      if { [info exists SYSDIC($subsys,keyedID)] } {
          puts $fout "	  long	[set subsys]ID;"
      }
      set argidx 1
      while { [gets $fin rec] > -1 } {
         if { $OPTIONS(verbose) } { stdlog "### processing $i : $rec" }
         if { [lindex $rec 0] == "#pragma" } {
            if { [info exists SYSDIC($subsys,keyedID)] } {
               puts $fout "	#pragma keylist $name [set subsys]ID"
            } else {
               puts $fout "	#pragma keylist $name"
            }
            puts $fhdr "
#ifdef SAL_DEBUG_CSTRUCTS
  [set subsys]_[set name]C()  \{ std::cout << \"[set subsys]_[set name]C()\"  << std::endl; \}
  ~[set subsys]_[set name]C() \{ std::cout << \"~[set subsys]_[set name]C()\"  << std::endl; \}
#endif
\};
"
           puts $fhlv "\} [set subsys]_[set name]_Ctl;"
           puts $fbst "      ;"
           puts $fpyb "      ;"
         } else {
            puts $fout "	$rec"
            if { [lindex $rec 0] != "const" } {
             if { [string range [lindex $rec 1] 0 7] != "private_" && [llength $rec] > 1 } {
               puts $fhdr [typeidltoc $rec]
               if { $VPROPS(iscommand) } {
                  if { [lsearch "device property action itemValue" $VPROPS(name)] < 0 } {
                     puts $fhlv [typeidltolv $rec]
                  }
               } else {
                  puts $fhlv [typeidltolv $rec]
               }
               set VPROPS(idx) $argidx
               set VPROPS(base) $subsys
               set VPROPS(topic) "[set subsys]_[set name]"
               updatecfragments $fcod1 $fcod1b $fcod2 $fcod2b $fcod3 $fcod4 $fcod5 $fcod6 $fcod7 $fcod8 $fcod10 $fcod11 $fcod12 $fcod13
               set vname $VPROPS(name)
               if { $VPROPS(array) } {
                  puts $fbst "      .add_property(\"$vname\", make_array(&[set subsys]_[set name]C::$vname))"
                  puts $fpyb "      .def_property_readonly(\"$vname\", make_array(&[set subsys]_[set name]C::$vname))"
               } else {
                  puts $fbst "      .def_readwrite(\"$vname\", &[set subsys]_[set name]C::$vname)"
                  puts $fpyb "      .def_readwrite(\"$vname\", &[set subsys]_[set name]C::$vname)"
               }
               if { $VPROPS(array) } {
                 incr argidx $VPROPS(dim)
               } else {
                 incr argidx 1
               }
             }
            } else {
             set v [split [lindex $rec 2] =]
             puts $fpyb "	m.attr(\"[lindex $v 0]\") = [lindex $v 1]"
             set ename [string range $name 9 end]
             if { [info exists EVENT_ENUM($ename)] && [info exists enumdone($ename)] == 0 } {
              foreach e $EVENT_ENUM($ename) {
                set vname [lindex [split $e :] 0]
                set cnst [lindex [split $$e :] 1]
                foreach id [split $cnst ,] {
                   set sid [string trim $id]
###                   puts $fcod3 "    if (SALInstance.[set vname] == [set subsys]::[set ename]_[set sid]) cout << \"    $vname : [set sid]\" << endl;"
###                   puts $fcod14 "                if (event.[set vname] == [set subsys].[set ename]_[set sid].value) System.out.println(\"    $vname : [set sid]\");"
                }
              }
              set enumdone($ename) 1
             }
            }
         }
      }
      close $fin
      close $fcod1
      close $fcod1b
      close $fcod2
      close $fcod2b
      close $fcod3
      close $fcod4
      close $fcod5
      close $fcod6
      close $fcod7
      close $fcod8
      close $fcod10
      close $fcod11
      close $fcod12
      close $fcod13
###      close $fcod14
    }
   }
   if { [info exists CMD_ALIASES($subsys)] } {
     if { [info exists SYSDIC($subsys,keyedID)] } {
        genkeyedidl $fout $subsys
     } else {
        gennonkeyedidl $fout
     }
     genackcmdincl $subsys $fhdr $fhlv
###     puts $fpyb2 "  .def(\"flushSamples_ackcmd\" ,  &SAL_[set subsys]::flushSamples_ackcmd )"
   }
   puts $fout "\};
"
   puts $fhdr "
#endif
"
   close $fout
   close $fhdr
   close $fhlv
   close $fbst
   close $fbst2
   close $fpyb
   close $fpyb2
   updateRevCodes $subsys
   activeRevCodes $subsys
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< makesalidl $subsys"}
   return $SAL_WORK_DIR/idl-templates/validated/sal/sal_$subsys.idl
}

proc updatecfragments { fcod1 fcod1b fcod2 fcod2b fcod3 fcod4 fcod5 fcod6 fcod7 fcod8 fcod10 fcod11 fcod12 fcod13 } {
global VPROPS TYPEFORMAT
   set idx $VPROPS(idx)
   if { $VPROPS(array) } {
      puts $fcod1 "    for (int iseq=0;iseq<$VPROPS(dim);iseq++) \{data->$VPROPS(name)\[iseq\] = Instances\[j\].$VPROPS(name)\[iseq\];\}"
      puts $fcod1 "    for (int iseq=0;iseq<$VPROPS(dim);iseq++) \{lastSample_[set VPROPS(topic)].$VPROPS(name)\[iseq\] = Instances\[j\].$VPROPS(name)\[iseq\];\}"
      puts $fcod1b "    for (int iseq=0;iseq<$VPROPS(dim);iseq++) \{data->$VPROPS(name)\[iseq\] = lastSample_[set VPROPS(topic)].$VPROPS(name)\[iseq\];\}"
      puts $fcod2 "    for (int iseq=0;iseq<$VPROPS(dim);iseq++) \{Instance.$VPROPS(name)\[iseq\] = data->$VPROPS(name)\[iseq\];\}"
      puts $fcod3 "       cout << \"    $VPROPS(name) : \" << SALInstance.$VPROPS(name)\[0\] << endl;"
      puts $fcod4 "    for (int i=0;i<$VPROPS(dim);i++)\{myData.$VPROPS(name)\[i\] = i+iseq;\}"
      puts $fcod6 "       cout << \"    $VPROPS(name) : \" << data->$VPROPS(name)\[0\] << endl;"
      puts $fcod7 "
           int $VPROPS(name)Size = (*(data->$VPROPS(name)))->size ;
           for (int i=0;i<$VPROPS(dim) && i<$VPROPS(name)Size;i++)\{[set VPROPS(base)]_memIO->client\[LVClient\].shmemOutgoing_[set VPROPS(topic)].$VPROPS(name)\[i\] = (*(data->$VPROPS(name)))->data\[i\];\}"
      puts $fcod8 "
           int $VPROPS(name)Size = $VPROPS(dim);
           (*(data->$VPROPS(name)))->size = $VPROPS(name)Size;
           for (int i=0;i<$VPROPS(dim);i++)\{(*(data->$VPROPS(name)))->data\[i\] = [set VPROPS(base)]_memIO->client\[LVClient\].shmemIncoming_[set VPROPS(topic)].$VPROPS(name)\[i\];\}"
      puts $fcod11 "for i in range(0,$VPROPS(dim)):
  myData.$VPROPS(name)\[i\]=i"
      puts $fcod12 "    for (int i=0;i<$VPROPS(dim);i++) \{Outgoing_[set VPROPS(topic)]->$VPROPS(name)\[i\]=[set VPROPS(base)]_memIO->client\[LVClient\].shmemOutgoing_[set VPROPS(topic)].$VPROPS(name)\[i\];\}"
      puts $fcod13 "    for (int i=0;i<$VPROPS(dim);i++) \{[set VPROPS(base)]_memIO->client\[LVClient\].shmemIncoming_[set VPROPS(topic)].$VPROPS(name)\[i\]=Incoming_[set VPROPS(topic)]->$VPROPS(name)\[i\];\}"
      set idlim [expr $idx + $VPROPS(dim)]
      set myidx 0
      while { $idx < $idlim } {

        if { $VPROPS(int) }  {
           if { $VPROPS(long) || $VPROPS(longlong) } {
              if { $VPROPS(long) } {
                 puts $fcod5 "    sscanf(argv\[$idx\], \"%ld\", &myData.$VPROPS(name)\[$myidx\]);"
              }
              puts $fcod10 "myData.$VPROPS(name)\[$myidx\] = long(sys.argv\[$idx\])"
           } else {
              if { $VPROPS(short) } {
                 puts $fcod5 "    sscanf(argv\[$idx\], \"%hd\", &myData.$VPROPS(name)\[$myidx\]);"
              } else {
                 if { $VPROPS(byte) } {
                    puts $fcod5 "    sscanf(argv\[$idx\], \"%hhu\", &myData.$VPROPS(name)\[$myidx\]);"
                 } else {
                    puts $fcod5 "    sscanf(argv\[$idx\], \"%d\", &myData.$VPROPS(name)\[$myidx\]);"
                 }
              }
              puts $fcod10 "myData.$VPROPS(name)\[$myidx\] = int(sys.argv\[$idx\])"
           }
        } else {
           if { $VPROPS(double) } {
              puts $fcod5 "    sscanf(argv\[$idx\], \"%lf\", &myData.$VPROPS(name)\[$myidx\]);"
           } else {
              puts $fcod5 "    sscanf(argv\[$idx\], \"%f\", &myData.$VPROPS(name)\[$myidx\]);"
           }
           puts $fcod10 "myData.$VPROPS(name)\[$myidx\] = float(sys.argv\[$idx\])"
        }
        incr idx 1
        incr myidx 1
      }
   } else {
      if { $VPROPS(string) } {
         puts $fcod1 "    data->$VPROPS(name)=Instances\[j\].$VPROPS(name).m_ptr;"
         puts $fcod1 "    lastSample_[set VPROPS(topic)].$VPROPS(name)=Instances\[j\].$VPROPS(name).m_ptr;"
         puts $fcod1b "   data->$VPROPS(name) = lastSample_[set VPROPS(topic)].$VPROPS(name);"
         puts $fcod2b "    if ( data->$VPROPS(name).length() > $VPROPS(dim) ) \{
       throw std::length_error(\"Item $VPROPS(name) exceeds string length\");
    \}"
         puts $fcod2 "    Instance.$VPROPS(name) = DDS::string_dup(data->$VPROPS(name).c_str());"
         puts $fcod3 "    cout << \"    $VPROPS(name) : \" << SALInstance.$VPROPS(name) << endl;"
         puts $fcod4 "    myData.$VPROPS(name)=\"LSST\";"
         puts $fcod5 "    myData.$VPROPS(name)=argv\[$idx\];"
         puts $fcod6 "    cout << \"    $VPROPS(name) : \" << data->$VPROPS(name) << endl;"
         if { [lsearch "device property action itemValue" $VPROPS(name)] < 0 } {
              puts $fcod7 "
           int $VPROPS(name)Size = (*(data->$VPROPS(name)))->size ;
           int i[set VPROPS(name)];
           for (i[set VPROPS(name)]=0;i[set VPROPS(name)]<$VPROPS(dim)-1 && i[set VPROPS(name)]<$VPROPS(name)Size;i[set VPROPS(name)]++)\{[set VPROPS(base)]_memIO->client\[LVClient\].[set VPROPS(topic)]LV_$VPROPS(name)_bufferOut\[i[set VPROPS(name)]\] = (*(data->$VPROPS(name)))->data\[i[set VPROPS(name)]\];\}
           [set VPROPS(base)]_memIO->client\[LVClient\].[set VPROPS(topic)]LV_$VPROPS(name)_bufferOut\[i[set VPROPS(name)]\] = 0;"
               puts $fcod8 "
           int $VPROPS(name)Size = strlen([set VPROPS(base)]_memIO->client\[LVClient\].[set VPROPS(topic)]LV_$VPROPS(name)_bufferIn);
           NumericArrayResize(5, 1, (UHandle*)(&(data->$VPROPS(name))), $VPROPS(name)Size);
           (*(data->$VPROPS(name)))->size = $VPROPS(name)Size;
           for (int i=0;i<$VPROPS(name)Size;i++)\{(*(data->$VPROPS(name)))->data\[i\] = [set VPROPS(base)]_memIO->client\[LVClient\].[set VPROPS(topic)]LV_$VPROPS(name)_bufferIn\[i\];\}"
         }
         puts $fcod10 "myData.$VPROPS(name)=sys.argv\[$idx\]"
         puts $fcod11 "myData.$VPROPS(name)=\"LSST\""
         if { [lsearch "device property action itemValue" $VPROPS(name)] < 0 } {
               puts $fcod12 "             Outgoing_[set VPROPS(topic)]->[set VPROPS(name)]=[set VPROPS(base)]_memIO->client\[LVClient\].[set VPROPS(topic)]LV_[set VPROPS(name)]_bufferOut;"
               puts $fcod13 "             strcpy([set VPROPS(base)]_memIO->client\[LVClient\].[set VPROPS(topic)]LV_[set VPROPS(name)]_bufferIn,Incoming_[set VPROPS(topic)]->[set VPROPS(name)].c_str());"
         }
      } else {
         puts $fcod1 "    data->$VPROPS(name) = Instances\[j\].$VPROPS(name);"
         puts $fcod1 "    lastSample_[set VPROPS(topic)].$VPROPS(name) = Instances\[j\].$VPROPS(name);"
         puts $fcod1b "   data->$VPROPS(name) = lastSample_[set VPROPS(topic)].$VPROPS(name);"
         puts $fcod2 "    Instance.$VPROPS(name) = data->$VPROPS(name);"
         puts $fcod3 "    cout << \"    $VPROPS(name) : \" << SALInstance.$VPROPS(name) << endl;"
         puts $fcod6 "    cout << \"    $VPROPS(name) : \" << data->$VPROPS(name) << endl;"
         puts $fcod7 "           [set VPROPS(base)]_memIO->client\[LVClient\].shmemOutgoing_[set VPROPS(topic)].$VPROPS(name) = data->$VPROPS(name);"
         puts $fcod8 "           data->$VPROPS(name) = [set VPROPS(base)]_memIO->client\[LVClient\].shmemIncoming_[set VPROPS(topic)].$VPROPS(name);"
         puts $fcod12 "           Outgoing_[set VPROPS(topic)]->$VPROPS(name)=[set VPROPS(base)]_memIO->client\[LVClient\].shmemOutgoing_[set VPROPS(topic)].$VPROPS(name);"
         puts $fcod13 "           [set VPROPS(base)]_memIO->client\[LVClient\].shmemIncoming_[set VPROPS(topic)].$VPROPS(name)=Incoming_[set VPROPS(topic)]->$VPROPS(name);"
         if { $VPROPS(int) } {
          puts $fcod11 "myData.$VPROPS(name) = 1";
          if { $VPROPS(long) || $VPROPS(longlong) } {
            puts $fcod4 "    myData.$VPROPS(name) = 1;";
            if { $VPROPS(long) } {
               puts $fcod5 "    sscanf(argv\[$idx\], \"%ld\", &myData.$VPROPS(name));"
            }
            puts $fcod10 "myData.$VPROPS(name)=long(sys.argv\[$idx\])"
          } else {
            puts $fcod4 "    myData.$VPROPS(name) = 1;";
            if { $VPROPS(short) } {
               puts $fcod5 "    sscanf(argv\[$idx\], \"%hd\", &myData.$VPROPS(name));"
            } else {
               if { $VPROPS(byte) } {
                  puts $fcod5 "    sscanf(argv\[$idx\], \"%hhu\", &myData.$VPROPS(name));"
               } else {
                  puts $fcod5 "    sscanf(argv\[$idx\], \"%d\", &myData.$VPROPS(name));"
               }
            }
            puts $fcod10 "myData.$VPROPS(name)=int(sys.argv\[$idx\])"
          }
         } else {
          puts $fcod11 "myData.$VPROPS(name) = 1.0";
          puts $fcod10 "myData.$VPROPS(name)=float(sys.argv\[$idx\])"
          if { $VPROPS(double) } {
            puts $fcod4 "    myData.$VPROPS(name) = 1.0;";
            puts $fcod5 "    sscanf(argv\[$idx\], \"%lf\", &myData.$VPROPS(name));"
          } else {
            puts $fcod4 "    myData.$VPROPS(name) = 1.0;";
            puts $fcod5 "    sscanf(argv\[$idx\], \"%f\", &myData.$VPROPS(name));"
          }
         }
      }
   }
}

proc gennonkeyedidl { fout } {
global OPTIONS
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> gennonkeyedidl $fout"}
     puts $fout "	struct ackcmd \{
      string<8>	private_revCode;
      double		private_sndStamp;
      double		private_rcvStamp;
      long		private_origin;
      long 		private_host;
      long		private_seqNum;
      long 		ack;
      long 		error;
      string<256>	result;
      long		host;
      long		origin;
      long		cmdtype;
      double		timeout;
	\};
	#pragma keylist ackcmd"
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< gennonkeyedidl $fout"}
}

proc genkeyedidl { fout base } {
global SAL_WORK_DIR OPTIONS
     if { $OPTIONS(verbose) } {stdlog "###TRACE>>> genkeyedidl $fout $base"}
     puts $fout "	struct ackcmd \{
      string<8>	private_revCode;
      double		private_sndStamp;
      double		private_rcvStamp;
      long		private_origin;
      long 		private_host;
      long		private_seqNum;
      long	[set base]ID;
      long 		ack;
      long 		error;
      string<256>	result;
      long		host;
      long		origin;
      long		cmdtype;
      double		timeout;
	\};
	#pragma keylist ackcmd [set base]ID"
     if { $OPTIONS(verbose) } {stdlog "###TRACE<<< genkeyedidl $fout $base"}
}


proc genackcmdincl { subsys fhdr fhlv } {
global OPTIONS
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> genackcmdincl $subsys $fhdr $fhlv "}
   puts $fhdr "
struct [set subsys]_ackcmdC
\{
      int 		ack;
      int 		error;
      std::string	result;
      long		host;
      long		origin;
      long		cmdtype;
      double		timeout;
\};
"
   puts $fhlv "
typedef struct [set subsys]_ackcmdLV
\{
      int       cmdSeqNum;
      int 	ack;
      int 	error;
      StrHdl	result; /* 256 */
\} [set subsys]_ackcmd_Ctl;
typedef struct [set subsys]_waitCompleteLV
\{
      int       cmdSeqNum;
      unsigned int timeout;
\} [set subsys]_waitComplete_Ctl;
"
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< genackcmdincl $subsys $fhdr $fhlv "}
}



proc makesalcmdevt { base lang } {
global SAL_DIR SAL_WORK_DIR SYSDIC ONEPYTHON DONE_CMDEVT OPTIONS
      if { $OPTIONS(verbose) } {stdlog "###TRACE>>> makesalcmdevt $base $lang "}
      stdlog "Processing $base Types, Commands, and Events in $SAL_WORK_DIR"
      cd $SAL_WORK_DIR
      set frep [open /tmp/sreplace4.sal w]
      puts $frep "#!/bin/sh"
      if { $lang == "cpp" } {
        exec cp $SAL_DIR/code/templates/Makefile.sacpp_SAL_types.template [set base]/cpp/Makefile.sacpp_[set base]_types
        puts $frep "perl -pi -w -e 's/SALDATA.idl/sal_[set base].idl/g;' [set base]/cpp/Makefile.sacpp_[set base]_types"
###        puts $frep "perl -pi -w -e 's/SALDATA.idl/[file tail $idlfile]/g;' [set base]/cpp/Makefile.sacpp_[set base]_types"
        puts $frep "perl -pi -w -e 's/SALData/sal_[set base]/g;' [set base]/cpp/Makefile.sacpp_[set base]_types"
        puts $frep "perl -pi -w -e 's/sacpp_SAL_types/sacpp_[set base]_types/g;' [set base]/cpp/Makefile.sacpp_[set base]_types"
        exec cp $SAL_DIR/code/templates/Makefile.sacpp_SAL_testcommands.template [set base]/cpp/src/Makefile.sacpp_[set base]_testcommands
        puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' [set base]/cpp/src/Makefile.sacpp_[set base]_testcommands"
        puts $frep "perl -pi -w -e 's/SALSubsys/[set base]/g;' [set base]/cpp/src/Makefile.sacpp_[set base]_testcommands"
        puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' [set base]/cpp/src/Makefile.sacpp_[set base]_testcommands"
        if { [info exists SYSDIC($base,keyedID)] } {
            puts $frep "perl -pi -w -e 's/#-DSAL_SUBSYSTEM/-DSAL_SUBSYSTEM/g;' [set base]/cpp/src/Makefile.sacpp_[set base]_testcommands"
        }
        exec cp $SAL_DIR/code/templates/Makefile.sacpp_SAL_testevents.template [set base]/cpp/src/Makefile.sacpp_[set base]_testevents
        puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' [set base]/cpp/src/Makefile.sacpp_[set base]_testevents"
        puts $frep "perl -pi -w -e 's/SALSubsys/[set base]/g;' [set base]/cpp/src/Makefile.sacpp_[set base]_testevents"
        puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' [set base]/cpp/src/Makefile.sacpp_[set base]_testevents"
        if { [info exists SYSDIC($base,keyedID)] } {
            puts $frep "perl -pi -w -e 's/#-DSAL_SUBSYSTEM/-DSAL_SUBSYSTEM/g;' [set base]/cpp/src/Makefile.sacpp_[set base]_testevents"
        }
      }
      if { $lang == "java" } {
        exec cp $SAL_DIR/code/templates/Makefile.saj_SAL_types.template [set base]/java/Makefile.saj_[set base]_types
        puts $frep "perl -pi -w -e 's/SALDATA.idl/sal_[set base].idl/g;' [set base]/java/Makefile.saj_[set base]_types"
#        puts $frep "perl -pi -w -e 's/SALDATA.idl/[file tail $idlfile]/g;' [set base]/java/Makefile.saj_[set base]_types"
        puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' [set base]/java/Makefile.saj_[set base]_types"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' [set base]/java/Makefile.saj_[set base]_types"
      }
      close $frep
      exec chmod 755 /tmp/sreplace4.sal
      catch { set result [exec /tmp/sreplace4.sal] } bad
      if { $bad != "" } {stdlog $bad}
      if { $lang == "python" } {
         makepythoncmdevt $base
      }
      if { $OPTIONS(verbose) } {stdlog "###TRACE<<< makesalcmdevt $base $lang "}
}

proc makepythoncmdevt { base } {
global SAL_DIR SAL_WORK_DIR SYSDIC ONEPYTHON DONE_CMDEVT OPTIONS
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> makepythoncmdevt $base"}
   set bad "" ; set result "none"
   stdlog "Generating Python bindings"
   catch { set result [genpythonbinding $base] } bad
   if { $result == "none" } {stdlog $bad}
   if { $OPTIONS(verbose) } {stdlog $result}
   set bad "" ; set result "none"
   stdlog "Generating python shared library"
   catch { set result [salpythonshlibgen $base] } bad
   if { $result == "none" } {stdlog $bad}
   if { $OPTIONS(verbose) } {stdlog $result}
   stdlog "Generating python command tests"
   catch { set result [gencommandtestspython $base] } bad
   if { $result == "none" } {stdlog $bad}
   if { $OPTIONS(verbose) } {stdlog $result}
   stdlog "Generating python event tests"
   catch { set result [geneventtestspython $base] } bad
   if { $result == "none" } {stdlog $bad}
   if { $OPTIONS(verbose) } {stdlog $result}
   stdlog "Generating python telemetry tests"
   catch { set result [gentelemetrytestspython $base] } bad
   if { $result == "none" } {stdlog $bad}
   if { $OPTIONS(verbose) } {stdlog $result}
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< makepythoncmdevt $base"}
}



proc makesalcode { idlfile base name lang } {
global SAL_DIR SAL_WORK_DIR SYSDIC ONEPYTHON DONE_CMDEVT OPTIONS CMD_ALIASES
      if { $OPTIONS(verbose) } {stdlog "###TRACE>>> makesalcode $idlfile $base $name $lang"}
      stdlog "Processing $base $name in $SAL_WORK_DIR"
      cd $SAL_WORK_DIR
      catch {makesaldirs $base $name}
      set id [set base]_[set name]
      set frep [open /tmp/sreplace.sal w]
      puts $frep "#!/bin/sh"
      if { $lang == "cpp" } {
        exec cp $SAL_DIR/code/templates/Makefile-cpp.template [set id]/cpp/standalone/Makefile
        puts $frep "perl -pi -w -e 's/sacpp_SAL_types/sacpp_[set base]_types/g;' [set id]/cpp/standalone/Makefile"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/cpp/standalone/Makefile"
        exec cp $SAL_DIR/code/templates/Makefile.sacpp_SAL_types.template [set base]/cpp/Makefile.sacpp_[set base]_types
        puts $frep "perl -pi -w -e 's/SALDATA.idl/[file tail $idlfile]/g;' [set base]/cpp/Makefile.sacpp_[set base]_types"
        puts $frep "perl -pi -w -e 's/SALData/sal_[set base]/g;' [set base]/cpp/Makefile.sacpp_[set base]_types"
        puts $frep "perl -pi -w -e 's/sacpp_SAL_types/sacpp_[set base]_types/g;' [set base]/cpp/Makefile.sacpp_[set base]_types"
        if { $name != "notused" } {
          exec cp $SAL_DIR/code/templates/Makefile.sacpp_SAL_sub.template [set id]/cpp/standalone/Makefile.sacpp_[set id]_sub
          puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_sub"
          puts $frep "perl -pi -w -e 's/SALSubsys/[set base]/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_sub"
          puts $frep "perl -pi -w -e 's/SALData/[set id]/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_sub"
          if { [info exists SYSDIC($base,keyedID)] } {
            puts $frep "perl -pi -w -e 's/#-DSAL_SUBSYSTEM/-DSAL_SUBSYSTEM/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_sub"
          }
          exec cp $SAL_DIR/code/templates/Makefile.sacpp_SAL_pub.template [set id]/cpp/standalone/Makefile.sacpp_[set id]_pub
          puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_pub"
          puts $frep "perl -pi -w -e 's/SALSubsys/[set base]/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_pub"
          puts $frep "perl -pi -w -e 's/SALData/[set id]/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_pub"
          if { [info exists SYSDIC($base,keyedID)] } {
            puts $frep "perl -pi -w -e 's/#-DSAL_SUBSYSTEM/-DSAL_SUBSYSTEM/g;' [set id]/cpp/standalone/Makefile.sacpp_[set id]_pub"
          }
        }
        if { $name != "notused" } {
          modpubsubexamples $id
          puts $frep "perl -pi -w -e 's/SALTopic/[set name]/g;' [set id]/cpp/src/[set id]DataPublisher.cpp"
          puts $frep "perl -pi -w -e 's/SALNAMESTRING/[set base]_[set name]/g;' [set id]/cpp/src/[set id]DataPublisher.cpp"
          puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/cpp/src/[set id]DataPublisher.cpp"
          puts $frep "perl -pi -w -e 's/SALTopic/[set name]/g;' [set id]/cpp/src/[set id]DataSubscriber.cpp"
          puts $frep "perl -pi -w -e 's/SALNAMESTRING/[set base]_[set name]/g;' [set id]/cpp/src/[set id]DataSubscriber.cpp"
          puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/cpp/src/[set id]DataSubscriber.cpp"
        }
      }
      if { $lang == "java"}  {
        exec cp $SAL_DIR/code/templates/Makefile-java.template [set id]/java/standalone/Makefile
        puts $frep "perl -pi -w -e 's/saj_SAL_types/saj_[set base]_types/g;' [set id]/java/standalone/Makefile"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/java/standalone/Makefile"
        exec cp $SAL_DIR/code/templates/Makefile.saj_SAL_types.template [set base]/java/Makefile.saj_[set base]_types
        puts $frep "perl -pi -w -e 's/SALDATA.idl/[file tail $idlfile]/g;' [set base]/java/Makefile.saj_[set base]_types"
        puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' [set base]/java/Makefile.saj_[set base]_types"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set base]_/g;' [set base]/java/Makefile.saj_[set base]_types"
        exec cp $SAL_DIR/code/templates/Makefile-java.template [set id]/java/Makefile
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/java/Makefile"
        if { $name != "notused" } {
          exec cp $SAL_DIR/code/templates/Makefile.saj_SAL_pub.template [set id]/java/standalone/Makefile.saj_[set id]_pub
          puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/java/standalone/Makefile.saj_[set id]_pub"
          puts $frep "perl -pi -w -e 's/SALTopic/[set id]/g;' [set id]/java/standalone/Makefile.saj_[set id]_pub"
          puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' [set id]/java/standalone/Makefile.saj_[set id]_pub"
          exec cp $SAL_DIR/code/templates/Makefile.saj_SAL_sub.template [set id]/java/standalone/Makefile.saj_[set id]_sub
          puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/java/standalone/Makefile.saj_[set id]_sub"
          puts $frep "perl -pi -w -e 's/SALTopic/[set id]/g;' [set id]/java/standalone/Makefile.saj_[set id]_sub"
          puts $frep "perl -pi -w -e 's/SALData/[set base]/g;' [set id]/java/standalone/Makefile.saj_[set id]_sub"
          exec cp $SAL_DIR/code/templates/SALTopicDataPublisher.java.template [set id]/java/src/[set id]DataPublisher.java
          if { [info exists SYSDIC($base,keyedID)] } {
            puts $frep "perl -pi -w -e 's/SALSUBSYSID/aKey/g;' [set id]/java/src/[set id]DataPublisher.java"
          } else {
            puts $frep "perl -pi -w -e 's/SALSUBSYSID//g;' [set id]/java/src/[set id]DataPublisher.java"
          }
          puts $frep "perl -pi -w -e 's/SALTopic/[set name]/g;' [set id]/java/src/[set id]DataPublisher.java"
          puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/java/src/[set id]DataPublisher.java"
          puts $frep "perl -pi -w -e 's/SALNAMESTRING/[set id]/g;' [set id]/java/src/[set id]DataPublisher.java"
          exec cp $SAL_DIR/code/templates/SALTopicDataSubscriber.java.template [set id]/java/src/[set id]DataSubscriber.java
          if { [info exists SYSDIC($base,keyedID)] } {
            puts $frep "perl -pi -w -e 's/SALSUBSYSID/aKey/g;' [set id]/java/src/[set id]DataSubscriber.java"
          } else {
            puts $frep "perl -pi -w -e 's/SALSUBSYSID//g;' [set id]/java/src/[set id]DataSubscriber.java"
          }
          puts $frep "perl -pi -w -e 's/SALTopic/[set name]/g;' [set id]/java/src/[set id]DataSubscriber.java"
          puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/java/src/[set id]DataSubscriber.java"
          puts $frep "perl -pi -w -e 's/SALNAMESTRING/[set id]/g;' [set id]/java/src/[set id]DataSubscriber.java"
        }
        exec cp $SAL_DIR/code/templates/ErrorHandler.java [set id]/java/src/ErrorHandler.java
        exec cp $SAL_DIR/code/templates/ErrorHandler.java [set base]/java/src/ErrorHandler.java
        exec cp $SAL_DIR/code/templates/runsample.template [set id]/java/standalone/[set id].run
        puts $frep "perl -pi -w -e 's/SALTopic/[set id]/g;' [set id]/java/standalone/[set id].run"
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/java/standalone/[set id].run"
        puts $frep "perl -pi -w -e 's/_SAL_/_[set id]_/g;' [set id]/java/standalone/[set id].run"
      }
      if { $lang == "PyDDS" } {
        exec cp $SAL_DIR/code/templates/SALTopicPublisher.py.template [set id]/python/[set id]Publisher.py
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/python/[set id]Publisher.py"
        puts $frep "perl -pi -w -e 's/SALTopic/$name/g;' [set id]/python/[set id]Publisher.py"
        puts $frep "perl -pi -w -e 's/SALDATA.idl/[file tail $idlfile]/g;' [set id]/python/[set id]Publisher.py"
        exec cp $SAL_DIR/code/templates/SALTopicSubscriber.py.template [set id]/python/[set id]Subscriber.py
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/python/[set id]Subscriber.py"
        puts $frep "perl -pi -w -e 's/SALTopic/$name/g;' [set id]/python/[set id]Subscriber.py"
        puts $frep "perl -pi -w -e 's/SALDATA.idl/[file tail $idlfile]/g;' [set id]/python/[set id]Subscriber.py"
      }
      close $frep
      exec chmod 755 /tmp/sreplace.sal
      catch { set result [exec /tmp/sreplace.sal] } bad
      if { $bad != "" } {stdlog $bad}
##      if { $name != "notused" } {
        stdlog "calling addSALDDStypes $idlfile $id $lang"
        addSALDDStypes $idlfile $id $lang $base
        stdlog "done addSALDDStypes $idlfile $id $lang"
##      }
      if { $lang == "cpp" } {
        set frep [open /tmp/sreplace2.sal w]
        puts $frep "#!/bin/sh"
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set base]/cpp/src/SAL_[set base].h"
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set base]/cpp/src/SAL_[set base].cpp"
        if { [info exists CMD_ALIASES($base)] } {
          set revcode [getRevCode [set base]_ackcmd short]
          puts $frep "perl -pi -w -e 's/SALResponse/$base\:\:ackcmd[set revcode]/g;' [set base]/cpp/src/SAL_[set base].cpp"
        }
        close $frep
        exec chmod 755 /tmp/sreplace2.sal
        catch { set result [exec /tmp/sreplace2.sal] } bad
        stdlog "done sreplace2 $idlfile $id $lang"
      }
      if { $lang == "java" } {
        set frep [open /tmp/sreplace2.sal w]
        puts $frep "#!/bin/sh"
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set id]/java/src/org/lsst/sal/SAL_[set base].java"
        puts $frep "perl -pi -w -e 's/SALData/$base/g;' [set base]/java/src/org/lsst/sal/SAL_[set base].java"
        if { [info exists CMD_ALIASES($base)] } {
          set revcode [getRevCode [set base]_ackcmd short]
          puts $frep "perl -pi -w -e 's/SALResponse/ackcmd[set revcode]/g;' [set id]/java/src/org/lsst/sal/SAL_[set base].java"
          puts $frep "perl -pi -w -e 's/SALResponse/ackcmd[set revcode]/g;' [set base]/java/src/org/lsst/sal/SAL_[set base].java"
        }
        close $frep
        exec chmod 755 /tmp/sreplace2.sal
        catch { set result [exec /tmp/sreplace2.sal] } bad
      }
      stdlog "calling salidlgen $base $lang"
      salidlgen $base $lang
      stdlog "done salidlgen $base $lang"
      if { $lang == "cpp" } {
         set incfiles [glob [set base]/cpp/*.h]
         stdlog "Updating include files : $incfiles"
####         catch { foreach i $incfiles {  exec cp $i $SAL_DIR/include/. } }
         exec cp [set base]/cpp/libsacpp_[set base]_types.so $SAL_WORK_DIR/lib/.
         exec ln -sf $SAL_WORK_DIR/[set base]/cpp/src/SAL_[set base].cpp $SAL_WORK_DIR/[set id]/cpp/src/.
         exec ln -sf $SAL_WORK_DIR/[set base]/cpp/src/SAL_[set base].h $SAL_WORK_DIR/[set id]/cpp/src/.
         salcpptestgen $base $id
      }
      if { $lang == "java" } {
         exec cp [set base]/java/saj_[set base]_types.jar $SAL_WORK_DIR/lib/.
         saljavaclassgen $base $id
      }
      if { $OPTIONS(verbose) } {stdlog "###TRACE<<< makesalcode $idlfile $base $name $lang"}
}


proc unittest { } {
global SAL_WORK_DIR
      makesalidl tcs
      makesalcode $SAL_WORK_DIR/idl-templates/validated/sal/sal_tcs.idl tcs kernel_TrackingTarget cpp
      makesalcode $SAL_WORK_DIR/idl-templates/validated/sal/sal_tcs.idl tcs kernel_TrackingTarget java
      makesalcode $SAL_WORK_DIR/idl-templates/validated/sal/sal_tcs.idl tcs kernel_TrackingTarget isocpp
      makesalcode $SAL_WORK_DIR/idl-templates/validated/sal/sal_tcs.idl tcs kernel_TrackingTarget python
}


proc salfullgen { } {
global SAL_WORK_DIR OPTIONS
  set atypes [lsort [glob $SAL_WORK_DIR/idl-templates/validated/sal/*.idl]]
  foreach i $atypes {
    set base [lindex [exec grep module $i] 1]
    set ptypes [split [exec grep pragma $i] \n]
    foreach j $ptypes {
      set name [lindex $j 2]
      makesalcode $idlfile $base $name cpp
      salidlgen cpp
      makesalcode $idlfile $base $name java
      salidlgen java
      makesalcode $idlfile $base $name isocpp
      salidlgen isocpp
      makesalcode $idlfile $base $name python
    }
  }
}

proc salidlgen { base lang } {
global SAL_WORK_DIR OPTIONS ONEDDSGEN
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> salidlgen $base $lang"}
   if { $lang != "python" } {
     if { $ONEDDSGEN == 0 } {
       cd $SAL_WORK_DIR/$base/$lang
       stdlog "Generating $lang type support for $base"
       if { $lang == "cpp" }     {catch { set result [exec make -f Makefile.sacpp_[set base]_types] } bad; stdlog $bad}
       if { $lang == "java"}     {
          modidlforjava $base
          catch { set result [exec make -f Makefile.saj_[set base]_types] } bad
          stdlog $bad
       }
       stdlog "idl : $result"
       cd $SAL_WORK_DIR
       set ONEDDSGEN 1
     }
   }
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< salidlgen $base $lang"}
}



proc salpythonshlibgen { base } {
global SAL_WORK_DIR OPTIONS
   if { $OPTIONS(verbose) } {stdlog "###TRACE>>> salpythonshlibgen $base"}
   cd $SAL_WORK_DIR/$base/cpp/src
   stdlog "Generating Python SAL support for $base"
   exec touch .depend.Makefile.sacpp_[set base]_python
   catch { set result [exec make -f Makefile.sacpp_[set base]_python] } bad
   if { $bad != "" } {stdlog $bad}
   stdlog "python : Done SALPY_[set base].so"
   if { $OPTIONS(verbose) } {stdlog "###TRACE<<< salpythonshlibgen $base"}
}


proc saljavaclassgen { base id } {
global SAL_WORK_DIR OPTIONS
 if { $OPTIONS(verbose) } {stdlog "###TRACE>>> saljavaclassgen $base $id"}
 if { $OPTIONS(fastest) == 0 } {
  if { $id != "[set base]_notused" } {
   cd $SAL_WORK_DIR/$id/java/standalone
   catch { set result [exec make -f Makefile.saj_[set id]_pub] } bad
   catch {stdlog "result = $result"}
   catch {stdlog "$bad"}
   stdlog "javac : Done Publisher"
   catch { set result [exec make -f Makefile.saj_[set id]_sub] } bad
   catch {stdlog "result = $result"}
   catch {stdlog "$bad"}
   stdlog "javac : Done Subscriber"
   cd $SAL_WORK_DIR
  }
 }
 if { $OPTIONS(verbose) } {stdlog "###TRACE<<< saljavaclassgen $base $id"}
}

proc salcpptestgen { base id } {
global SAL_WORK_DIR OPTIONS DONE_CMDEVT
  if { $OPTIONS(verbose) } {stdlog "###TRACE>>> salcpptestgen $base $id"}
  if { $OPTIONS(fastest) == 0 } {
    if { $id != "[set base]_notused" } {
     stdlog "Generating cpp test programs for $id"
     cd $SAL_WORK_DIR/$id/cpp/standalone
     catch { set result [exec make -f Makefile.sacpp_[set id]_sub] } bad
     catch {stdlog "result = $result"}
     catch {stdlog "$bad"}
     stdlog "cpp : Done Subscriber"
     catch { set result [exec make -f Makefile.sacpp_[set id]_pub] } bad
     catch {stdlog "result = $result"}
     catch {stdlog "$bad"}
     stdlog "cpp : Done Publisher"
    }
  }
  if { $DONE_CMDEVT == 0 } {
   cd $SAL_WORK_DIR/$base/cpp/src
   catch { exec make -f Makefile.sacpp_[set base]_testcommands all } bad
   catch {stdlog "result = $result"}
   catch {stdlog "$bad"}
   stdlog "cpp : Done Commander"
   catch { exec make -f Makefile.sacpp_[set base]_testevents all } bad
   catch {stdlog "result = $result"}
   catch {stdlog "$bad"}
   stdlog "cpp : Done Event/Logger"
   set DONE_CMDEVT 1
   cd $SAL_WORK_DIR
  }
  if { $OPTIONS(verbose) } {stdlog "###TRACE<<< salcpptestgen $base $id"}
}

source $SAL_DIR/add_system_dictionary.tcl
source $SAL_DIR/gensalgetput.tcl
if { [info exists env(PYTHON_BUILD_VERSION)] } {
  if { [lindex [split $env(PYTHON_BUILD_VERSION) .] 0] == 2} {
    stdlog "Enabling Boost::Python bindings for python 2.x"
    source $env(SAL_DIR)/gensimplepython.tcl
  } else {
    stdlog "Enabling pybind11 bindings for python 3+"
    source $env(SAL_DIR)/gensimplepybind11.tcl
  }
}
source $SAL_DIR/managetypes.tcl
source $SAL_DIR/activaterevcodes.tcl
