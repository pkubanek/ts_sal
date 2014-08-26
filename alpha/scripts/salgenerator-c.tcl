
proc gencodesub { fcod typ nam tid } {
   switch $typ {
        byte   { }
        double { puts $fcod "
    result = myInputs->getItem(\"$tid.$nam\",&myDoubleRead);
    printf(\"Completed getItem double : result = %d , value = %lf\\n\\n\",result,myDoubleRead);"
               }
        float  { puts $fcod "
    result = myInputs->getItem(\"$tid.$nam\",&myFloatRead);
    printf(\"Completed getItem float : result = %d , value = %f\\n\\n\",result,myFloatRead);"
               }
        long   -
        int    { puts $fcod "
    result = myInputs->getItem(\"$tid.$nam\",&myIntegerRead);
    printf(\"Completed getItem int : result = %d , value = %d\\n\\n\",result,myIntegerRead);"
               }
        short  { puts $fcod "
    result = myInputs->getItem(\"$tid.$nam\",&myShortRead);
    printf(\"Completed getItem int : result = %d , value = %d\\n\\n\",result,myShortRead);"
               }
        string { puts $fcod "
    result = myInputs->getItem(\"$tid.$nam\",myCharRead);
    printf(\"Completed getItem char : result = %d , value = %s\\n\\n\",result,myCharRead);"
               }        
   }
}


proc gencodepub { fcod typ nam tid } {
   switch $typ {
        byte   { }
        double { puts $fcod "
    myDoubleWrite = 12345.67898765;
    result = myOutputs->putItem(\"$tid.$nam\",myDoubleWrite);
    printf(\"Completed putItem double : result = %d , value = %lf\\n\\n\",result,myDoubleWrite);"
               }
        float  { puts $fcod "
    myFloatWrite = 12345.678;
    result = myOutputs->putItem(\"$tid.$nam\",myFloatWrite);
    printf(\"Completed putItem float : result = %d , value = %f\\n\\n\",result,myFloatWrite);"
               }
        long   -
        int    { puts $fcod "
    myIntegerWrite = -12345;
    result = myOutputs->putItem(\"$tid.$nam\",myIntegerWrite);
    printf(\"Completed putItem int : result = %d , value = %d\\n\\n\",result,myIntegerWrite);"
               }
        short  { puts $fcod "
    myShortWrite = -12345;
    result = myOutputs->putItem(\"$tid.$nam\",&myShortWrite);
    printf(\"Completed putItem int : result = %d , value = %d\\n\\n\",result,myShortWrite);"
               }
        string { puts $fcod "
    strcpy(myCharWrite,\"ok\");
    result = myOutputs->putItem(\"$tid.$nam\",myCharWrite);
    printf(\"Completed putItem char : result = %d , value = %s\\n\\n\",result,myCharWrite);"
               }        
   }
}


set stagingdir /tmp/salgenerator/lsst_SAL_c
set streamdir  /opt/lsst/streams
set salcodedir /opt/lsst/salcode

catch { exec rm -fr $stagingdir }
exec mkdir -p $stagingdir 
set fmak [open $stagingdir/makefile w]
puts $fmak "DEVHOME         = .
INSTALL_DIR     = /opt/lsst/lib
TCLSRC = /opt/lsst/extern/tcl8.3.1/generic
TKSRC = /opt/lsst/extern/tk8.3.1/generic                                   

.KEEP_STATE:
CC =    g++
LD =    g++
SWIG = /opt/lsst/bin/swig

INCDIR          = \$(DEVHOME)
PRIVATEINCDIR   = ./include
LSSTINC          = /opt/lsst/include
CPPFLAGS        = -O2 -g -fpic -DWall -DLINUX -I\$(LSSTINC) -I.
LDFLAGS         = -shared -O2 -g"


set CFILES "svcSAL.h"
set EFILES ""

foreach mw "ace ice ndds tspace test" {
  if { [info exists FormData(mw_$mw)] } {
    puts $fmak "
lsst_services_$mw.so:
        \$(CC) \$(CPPFLAGS) -c svcSAL_template_$mw.cpp
        \$(CC) \$(LDFLAGS) svcSAL_template_$mw.o -o lsst_services_$mw.so

"
    lappend CFILES "svcSAL_template_$mw.cpp"
    lappend EFILES "lsst_services_$mw.so"
    foreach s $SUBS {
      lappend EFILES "[set mw]_subscription"
      puts $fmak "

[set mw]_subscription: lsst_services_$mw.so
        \$(CC) \$(CPPFLAGS) -c $[set mw]_subscription.cpp
        \$(LD) -O2 -g [set mw]_subscription.o lsst_services_$mw.so -o $[set mw]_subscription -lc

"
    }
    foreach s $PUBS {
     lappend EFILES "[set mw]_publishing"
      puts $fmak "

[set mw]_publishing: lsst_services_$mw.so
        \$(CC) \$(CPPFLAGS) -c [set mw]_publishing.cpp
        \$(LD) -O2 -g [set mw]_publishing.o lsst_services_$mw.so -o [set mw]_publishing -lc

"
    }
    foreach s $ISSU {
      lappend EFILES "[set mw]_commanding"
      puts $fmak "

[set mw]_commanding: lsst_services_$mw.so
        \$(CC) \$(CPPFLAGS) -c [set mw]_commanding.cpp
        \$(LD) -O2 -g [set mw]_commanding.o lsst_services_$mw.so -o [set mw]_commanding -lc

"
    }
    foreach s $PROC {
      lappend EFILES "[set mw]_cmdprocessing"
      puts $fmak "

[set mw]_cmcprocessing: lsst_services_$mw.so
        \$(CC) \$(CPPFLAGS) -c [set mw]_cmdprocessing.cpp
        \$(LD) -O2 -g [set mw]_cmdprocessing.o lsst_services_$mw.so -o [set mw]_cmdprocessing -lc

"
    }
  }
}

puts $fmak "
CONFIGTARGETS   = $EFILES

all: \$(CONFIGTARGETS)
"

foreach mw "ace ice ndds tspace test" {
  if { [info exists FormData(mw_$mw)] } {
    exec cp $salcodedir/cstub_[set mw]_subscription.cpp $stagingdir/[set mw]_subscription.cpp
    set fcod [open $stagingdir/[set mw]_subscription.cpp a]
    foreach s $SUBS {
        set fin [open $streamdir/$s.idl r]
        gets $fin rec
        while { [gets $fin rec] > -1 } {
           if { [string length $rec] > 3 } {
              set t [lindex [lindex [split $rec "\<"] 0] 0]
              set n [string trim [lindex $rec 1] ";"]
              puts stdout "$n is type $t"
              gencodesub $fcod $t $n $s
           }
        }
        close $fin
    }
    puts $fcod "

    delete myInputs;

}

"
  }
  close $fcod
}



foreach mw "ace ice ndds tspace test" {
  if { [info exists FormData(mw_$mw)] } {
    exec cp $salcodedir/cstub_[set mw]_publishing.cpp $stagingdir/[set mw]_publishing.cpp
    set fcod [open $stagingdir/[set mw]_publishing.cpp a]
    foreach s $PUBS {
        set fin [open $streamdir/$s.idl r]
        gets $fin rec
        while { [gets $fin rec] > -1 } {
           if { [string length $rec] > 3 } {
              set t [lindex [lindex [split $rec "\<"] 0] 0]
              set n [string trim [lindex $rec 1] ";"]
              puts stdout "$n is type $t"
              gencodepub $fcod $t $n $s
           }
        }
        close $fin
    }
    puts $fcod "

    delete myOutputs;

}

"
  }
  close $fcod
}

puts $fmak "
install: \$(CONFIGTARGETS) FORCE
        cp \$(CONFIGTARGETS) \$(INSTALL_DIR)

clean:
        rm -f tags TAGS .make.state .nse_depinfo *.o *.so

tags:
        ctags \$(LIBSOURCES)

FORCE:

"

close $fmak

cd $stagingdir
foreach f $CFILES {
  exec cp $salcodedir/$f .
}
cd ..
exec tar czf lsst_SAL_c.tar.gz lsst_SAL_c
exec cp lsst_SAL_c.tar.gz /var/www/html/downloads/salcode/.

puts stdout "<P><HR><P>
<H2>Software Abstraction Layer - C++ code</H2>
This archive contains a SAL library and test programs.<P><UL>"
if { $SUBS != "" } {
   puts stdout "Tests subscription for :
<UL>"
   foreach s $SUBS {
      puts stdout "<LI>$s"
   }
   puts stdout "</UL>"
}

if { $PUBS != "" } {
   puts stdout "Tests publishing for :
<UL>"
   foreach s $PUBS {
      puts stdout "<LI>$s"
   }
   puts stdout "</UL>"
}

if { $ISSU != "" } {
   puts stdout "Tests commanding for :
<UL>"
   foreach s $ISSU {
      puts stdout "<LI>$s"
   }
   puts stdout "</UL>"
}

if { $PROC != "" } {
   puts stdout "Tests command processing for :
<UL>"
   foreach s $PROC {
      puts stdout "<LI>$s"
   }
   puts stdout "</UL>"
}

puts stdout "<P><TABLE BORDER=3 CELLPADDING=5 BGCOLOR=LightGreen  WIDTH=400>
<TR><TD>Archive size</TD><TD>[file size /var/www/html/downloads/salcode/lsst_SAL_c.tar.gz] bytes</TD></TR>
<TR><TD>Archive type</TD><TD>Gzip compressed Tar format</TD></TR>
<TR><TD>Language</TD><TD>C++ (GCC compiler compatible)</TD></TR>
<TR><TD>Download link</TD><TD><A HREF=\"downloads/salcode/lsst_SAL_c.tar.gz\">lsst_SAL_c.tar.gz</A></TD></TR>
</TABLE>
<P><HR><P>"





