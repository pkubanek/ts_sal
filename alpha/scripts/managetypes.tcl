
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

proc testsimpletypecode { } {
   foreach case "c idl sql" {
      foreach typ "byte short int long float double string" {
          puts stdout "$case $typ :: [simpletypecode test $typ 1 $case]"
          puts stdout "$case $typ :: [simpletypecode test $typ 16 $case]"
      }
   }
}


proc transferdata { subsys name type size target } {
global TYPESIZE
   set ltyp [string tolower $type]
   switch $target {
        tocache { 
              switch $ltyp {
                    char   { return "strncpy([set subsys]_ref->$name, instance->$name, $size);" }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {
                              if { $size > 1 } {
                                 set n [expr $TYPESIZE($type) * $size]
                                 return "memcpy([set subsys]_ref->$name,instance->$name, $n);"
                              } else {
                                 return "[set subsys]_ref->$name=instance->$name;"
                              }
                           }
              }
        }
        fromcache { 
              switch $ltyp {
                    char   { return "strncpy(instance->$name, [set subsys]_ref->$name, $size);" }
                    byte   -
                    short  -
                    int    -
                    long   -
                    float  -
                    double {
                              if { $size > 1 } {
                                 set n [expr $TYPESIZE($type) * $size]
                                 return "memcpy(instance->$name,[set subsys]_ref->$name, $n);"
                              } else {
                                 return "instance->$name=[set subsys]_ref->$name;"
                              }
                           }
              }
        }
   }
}

proc testtransferdata { } {
   foreach case "tocache fromcache" {
      foreach typ "byte short int long float double char" {
          puts stdout "$case $typ :: [transferdata tcs_kernel_Target test $typ 1 $case]"
          puts stdout "$case $typ :: [transferdata tcs_kernel_Target test $typ 16 $case]"
      }
   }
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







