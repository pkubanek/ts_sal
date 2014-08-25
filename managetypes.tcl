
proc simpletypecode { name type size target } {
global TYPESUBS
   set ltyp [string tolower $type]
   switch $target {
        idl { 
              switch $ltyp {
                        string    -
                        string32  { return " string<32> $name;" }
                        string16  { return " string<16> $name;" }
                        string64  { return " string<64> $name;" }
                        string1k  { return " string<1024> $name;" }
                        byte      -
                        short     -
                        int       -
                        octet     -
                        long      -
                        float     -
                        double    { set s "$ltyp $name"
                                    if { $size > 1 } {
                                       return "$s\[$size\];"
                                    } else {
                                       return "$s;"
                                    }
                                  }
              }
         }   
         c  { 
              switch $ltyp {
                        string    -
                        string32  { return " char $name\[32\];" }
                        string16  { return " char $name\[16\];" }
                        string64  { return " char $name\[64\];" }
                        string1k  { return " char $name\[1024\];" }
                        byte      -
                        octet     -
                        short     -
                        int       -
                        long      -
                        float     -
                        double    { set s "$TYPESUBS($ltyp) $name"
                                    if { $size > 1 } {
                                       return "$s\[$size\];"
                                    } else {
                                       return "$s;"
                                    }
                                  }
              }
         }   
         sql { 
              switch $ltyp {
                        string    -
                        string32  { return "$name char\[32\];" }
                        string16  { return "$name char\[16\];" }
                        string64  { return "$name char\[64\];" }
                        string1k  { return "$name char\[1024\];" }
                        byte      -
                        short     -
                        int       -
                        long      -
                        float     -
                        double    { set s "$name $TYPESUBS($ltyp)"
                                    if { $size > 1 } {
                                       set s ""
                                       set i 0
                                       while { $i < $size } {
                                         incr i 1
                                         set s "$s\n[set name]_$i $TYPESUBS($ltyp);"
                                       }
                                       return "$s"
                                    } else {
                                       return "$s;"
                                    }
                                  }
              }
         }   
   }
}

proc typeidltoc { rec } {
global TYPESUBS VPROPS
   set u ""
   set VPROPS(array) 0
   set VPROPS(string) 0
   set VPROPS(name) ""
   if { [lindex $rec 0] == "unsigned" } {set u "unsigned"; set rec [join [lrange $rec 1 end] " "]}
   if { [llength [split $rec "<"]] > 1 } {
      set s [lindex [split $rec "<>"] 1]
      set VPROPS(dim) $s
      set res "  char	lindex $rec 1]\[$s\]   [join [lrange $rec 2 end]]"
      set VPROPS(name) [string trim [join [lrange $rec 1 end]] ";"]
      set VPROPS(string) 1
   } else {
      if { [llength [split $rec "\["]] > 1 } {
        set s [lindex [split $rec "\[\]"] 1]
        set n [lindex [lindex [split $rec "\[\]"] 0] 1]
        set VPROPS(name) $n
        set VPROPS(array) 1
        set VPROPS(dim) $s
        set res "  [set u] $TYPESUBS([lindex $rec 0]) $n\[$s\];"
      } else {
        set res " [set u] $TYPESUBS([lindex $rec 0]) [join [lrange $rec 1 end]]"
        set VPROPS(name) [string trim [join [lrange $rec 1 end]] ";"]
      }
   }
   return $res
}


proc testsimpletypecode { } {
   foreach case "c idl sql" {
      foreach typ "byte short int long float double string" {
          puts stdout "$case $typ :: [simpletypecode test $typ 1 $case]"
          puts stdout "$case $typ :: [simpletypecode test $typ 16 $case]"
      }
   }
}


proc transferdata { subsys name type size target {prefix ""} } {
global TYPESIZE TYPEFORMAT
   set ltyp [string tolower $type]
   switch $target {
        ddstocache { 
              switch $ltyp {
                    char   { return "strncpy([set subsys]_ref->$name, [set prefix]instance->$name, $size);" }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {
                              if { $size > 1 } {
                                 set n [expr $TYPESIZE($type) * $size]
                                 return "memcpy([set subsys]_ref->$name,[set prefix]instance->$name, $n);"
                              } else {
                                 return "[set subsys]_ref->$name=[set prefix]instance->$name;"
                              }
                           }
              }
        }
        tcltocache { 
              switch $ltyp {
                    char   { return "       text = (char *)Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$name\", TCL_GLOBAL_ONLY);
       strcpy([set subsys]_ref->$name,text);" 
                           }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {
                              if { $size > 1 } {
                                 set result  "	for (iterator=0;iterator<$size;iterator++) \{
          sprintf(newName,\"$name,%d\",iterator);
	  text = (char *)Tcl_GetVar2(interp, \"SHM[set subsys]\", newName, TCL_GLOBAL_ONLY);
	  sscanf(text,\"$TYPEFORMAT($ltyp)\", &[set subsys]_ref->$name\[iterator\]);
	\}"
                             } else {
                                 set result "       text = (char *)Tcl_GetVar2(interp, \"SHM[set subsys]\", \"$name\", TCL_GLOBAL_ONLY);
       sscanf(text,\"$TYPEFORMAT($ltyp)\", &[set subsys]_ref->$name);"
                              }
                              return $result;
                           }
              }
        }
        tcltest { 
              switch $ltyp {
                    char   { return "set SHM[set subsys]($name) \"LSST test\"" 
                           }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {
                              if { $size > 1 } {
                                 set i 1
                                 scan [expr rand()*100]] $TYPEFORMAT($ltyp) x
                                 set result "set i 0 ; while \{ \$i < $size \} \{ set SHM[set subsys]($name,\$i) \[expr $x+\$i\]; incr i 1\}"
                              } else {
                                 scan [expr rand()*100]] $TYPEFORMAT($ltyp) x
                                 set result "set SHM[set subsys]($name) $x"
                              }
                              return $result;
                           }
              }
        }
        ctest { 
              switch $ltyp {
                    char   { return "	sprintf([set subsys]_ref->$name,\"Sample string %d\",icurrent);" 
                           }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {  set result ""
                              if { $size > 1 } {
                                    set result "$result\n	for (iterator=0;iterator<$size;iterator++) \{
	  [set subsys]_ref->$name\[iterator\] = ($ltyp)(icurrent+iterator);
	\}"
                              } else {
                                 set result "	[set subsys]_ref->$name = ($ltyp)icurrent;"
                              }
                              return $result;
                           }
              }
        }
        ddsfromcache { 
              switch $ltyp {
                    char   { return "strncpy([set prefix]instance->$name, [set subsys]_ref->$name, $size);" }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {
                              if { $size > 1 } {
                                 set n [expr $TYPESIZE($type) * $size]
                                 return "memcpy([set prefix]instance->$name,[set subsys]_ref->$name, $n);"
                              } else {
                                 return "[set prefix]instance->$name=[set subsys]_ref->$name;"
                              }
                           }
              }
        }
        lvfromcache { 
              switch $ltyp {
                    char   { return "ilen = strlen([set subsys]_ref->$name);\n	LStrLen(*$name) = ilen;\n	memcpy(*(char **)$name+4,[set subsys]_ref->$name, ilen);" }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {
                              if { $size > 1 } {
                                 set n [expr $TYPESIZE($type) * $size]
                                 return "LStrLen(*$name) = $n;\n	memcpy(*(char **)$name+4,[set subsys]_ref->$name, $n);"
                              } else {
                                 return "*$name=[set subsys]_ref->$name;"
                              }
                           }
              }
        }
        lvtocache { 
              switch $ltyp {
                    char   { return "strncpy([set subsys]_ref->$name,*(char **)$name+4, $size);" }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {
                              if { $size > 1 } {
                                 set n [expr $TYPESIZE($type) * $size]
                                 return "memcpy([set subsys]_ref->$name,*(char **)$name+4, $n);"
                              } else {
                                 return "[set subsys]_ref->$name = $name;"
                              }
                           }
              }
        }
        tclfromcache { 
              switch $ltyp {
                    char   { return "      Tcl_SetVar2(interp, \"SHM[set subsys]\", \"$name\", [set subsys]_ref->$name, TCL_GLOBAL_ONLY);"
                           }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {
                              if { $size > 1 } {
                                 set result "	for (iterator=0;iterator<$size;iterator++) \{
	  sprintf(newValue,\"$TYPEFORMAT($ltyp)\",[set subsys]_ref->$name\[iterator\]);
          sprintf(newName,\"$name,%d\",iterator);
	  Tcl_SetVar2(interp, \"SHM[set subsys]\", newName, newValue,  TCL_GLOBAL_ONLY);
	\}"
                                 set result "$result\n       sprintf(newValue,\"%d\",$size);
      Tcl_SetVar2(interp, \"SHM[set subsys]\", \"$name,size\", newValue,  TCL_GLOBAL_ONLY);"
                              } else {
                                 set result "      sprintf(newValue,\"$TYPEFORMAT($ltyp)\",[set subsys]_ref->$name);
      Tcl_SetVar2(interp, \"SHM[set subsys]\", \"$name\", newValue,  TCL_GLOBAL_ONLY);"

                              }
                              return $result;
                           }
              }
        }
   }
}

proc testtransferdata { } {
   foreach case "ddstocache ddsfromcache tcltocache tclfromcache tcltest ctest" {
      foreach typ "byte short int long float double char" {
          puts stdout "$case $typ :: [transferdata tcs_kernel_Target test $typ 1 $case]"
          puts stdout "$case $typ :: [transferdata tcs_kernel_Target test $typ 16 $case]"
      }
   }
}

proc lvtypebuilder { base op name type size } {
   set t [string tolower $type]
   if { $t == "char" || $size > 1 } {
      return "$base LStrHandle $name,"
   }
   if { $op == "get" } {
     return "$base $type* $name,"     
   }
   return "$base $type $name,"
}


set TYPESUBS(string) char
set TYPESUBS(byte)   char
set TYPESUBS(octet)  char
set TYPESUBS(int)    long
set TYPESUBS(short)  short
set TYPESUBS(int16)  short
set TYPESUBS(int32)  long
set TYPESUBS(long)   long
set TYPESUBS(float)  float
set TYPESUBS(double) double
set TYPESUBS(unsignedint)    long
set TYPESUBS(unsignedshort)  short
set TYPESUBS(unsignedint16)  short
set TYPESUBS(unsignedint32)  long
set TYPESUBS(unsignedlong)   long

set TYPESIZE(string) 1
set TYPESIZE(char)   1
set TYPESIZE(byte)   1
set TYPESIZE(octet)  1
set TYPESIZE(short)  2
set TYPESIZE(int16)  2
set TYPESIZE(int)    4
set TYPESIZE(int32)  4
set TYPESIZE(long)   4
set TYPESIZE(float)  4
set TYPESIZE(double) 8
set TYPESIZE(int64)  8
set TYPESIZE(unsignedshort)  2
set TYPESIZE(unsignedint16)  2
set TYPESIZE(unsignedint)    4
set TYPESIZE(unsignedint32)  4
set TYPESIZE(unsignedlong)   4

set TYPEFORMAT(byte)   "%d"
set TYPEFORMAT(octet)  "%d"
set TYPEFORMAT(short)  "%d"
set TYPEFORMAT(int16)  "%d"
set TYPEFORMAT(int)    "%d"
set TYPEFORMAT(int32)  "%d"
set TYPEFORMAT(long)   "%ld"
set TYPEFORMAT(float)  "%f"
set TYPEFORMAT(double) "%lf"
set TYPEFORMAT(int64)  "%ld"
set TYPEFORMAT(unsignedshort)  "%d"
set TYPEFORMAT(unsignedint16)  "%d"
set TYPEFORMAT(unsignedint)    "%d"
set TYPEFORMAT(unsignedint32)  "%d"
set TYPEFORMAT(unsignedlong)   "%ld"






