proc geneventtestssinglefilejava { subsys } {
    # Creates multiple files which contains an implementation of all the
    # events defined within this subsys.

    puts "events script firing"

    global SAL_WORK_DIR

    # Create the file writers for the sender, logger and makefile.
    set sender_java_file_writer [open $SAL_WORK_DIR/$subsys/java/src/[set subsys]Event_all.java w]
    set logger_java_file_writer [open $SAL_WORK_DIR/$subsys/java/src/[set subsys]Eventlogger_all.java w]
    # set makefile_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testevents w]

    # Insert content into the sender.
    insertEventHeaderJava $subsys $sender_java_file_writer
    insertSendersJava $subsys $sender_java_file_writer

    # Insert content into the logger.
    insertEventHeaderJava $subsys $logger_java_file_writer
    insertLoggersJava $subsys $logger_java_file_writer

    # # Insert content into the makefile.
    # insertEventsMakeFile $subsys $makefile_file_writer

    # # Close all the file writers.
    # close $sender_cpp_file_writer
    # close $logger_cpp_file_writer
    # close $makefile_file_writer

    # # Execute the makefile. 
    # cd $SAL_WORK_DIR/$subsys/cpp/src
    # exec make -f $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testevents
    # cd $SAL_WORK_DIR
    # exit
}

proc insertEventHeaderJava { subsys file_writer } {

    puts $file_writer "/*"
    puts $file_writer "* This file contains the implementation for the [set subsys] single file commander test."
    puts $file_writer "* [set subsys] subsystem generated via gencommandtestssinglefilejava.tcl"
    puts $file_writer "*"
    puts $file_writer " ***/"

    puts $file_writer "package org.lsst.sal.junit.[set subsys];"
    puts $file_writer "import junit.framework.TestCase;"
    puts $file_writer "import [set subsys].*;"
    puts $file_writer "import org.lsst.sal.SAL_[set subsys];\n"
}

proc insertSendersJava { subsys file_writer } {
    
    global SYSDIC EVENT_ALIASES EVTS

    if { [info exists EVENT_ALIASES($subsys)] } {
        if { [info exists SYSDIC($subsys,keyedID)] } {
            set initializer "( (short) 1)"
        } else {
            set initializer "()"
        }
    }

    puts $file_writer "public class [set subsys]Event_allTest extends TestCase \{\n"
    puts $file_writer "    public [set subsys]Event_allTest(String name) \{"
    puts $file_writer "        super(name);"
    puts $file_writer "    \}\n"


    puts $file_writer "    public void test[set subsys]Event_all() \{"
    puts $file_writer "        SAL_[set subsys] mgr = new SAL_[set subsys][set initializer];"
    
    foreach alias $EVENT_ALIASES($subsys) {
        puts $file_writer "        mgr.salEvent(\"[set subsys]_command_[set alias]\");"
    }
    
    puts $file_writer "        int cmdId = 0;"
    puts $file_writer "        int status = 0;"
    puts $file_writer "        int timeout = 3;"
    puts $file_writer "        int count = 0;"

    foreach alias $EVENT_ALIASES($subsys) {
        puts $file_writer "\n        [set subsys].logevent_[set alias] event  = new [set subsys].logevent_[set alias]();"
        
        set revcode [getRevCode [set subsys]_logevent_[set alias] short]
        puts $file_writer "        event.private_revCode = \"[string trim $revcode _]\";"

        set narg 1

        foreach p $EVTS($subsys,$alias,param) {
            set pname [lindex $p 1]
            set ptype [lindex $p 0]
            if { [llength [split $pname "()"]] > 1 } {
                set l 0
                set pspl [split $pname "()"]
                set pname [lindex $pspl 0]
                set pdim  [lindex $pspl 1]
                while { $l < $pdim } {
                    switch $ptype {
                        boolean { puts $file_writer "            event.[set pname]\[$l\] = true;" }
                        double  { puts $file_writer "        event.[set pname]\[$l\] = (double) 1.0;" }
                        int     { puts $file_writer "        event.[set pname]\[$l\] = (int) 1;" }
                        long    { puts $file_writer "        event.[set pname]\[$l\] = (int) 1;" }
                     }
                incr l 1
                }
            } else {
                switch $ptype {
                    boolean { puts $file_writer "        event.[set pname] = true;" }
                    double  { puts $file_writer "        event.[set pname] = (double) 1.0;" }
                    int     { puts $file_writer "        event.[set pname] = (int) 1;" }
                    long    { puts $file_writer "        event.[set pname] = (int) 1;" }
                    string  { puts $file_writer "        event.[set pname] = \"testing\";" }
                }
            }
            incr narg 1
        }
        puts $file_writer "        status = mgr.logEvent_[set alias](event,priority);"
        puts $file_writer "        try \{Thread.sleep(1000);\} catch (InterruptedException e)  \{ e.printStackTrace(); \}"
    }

    puts $file_writer "    /* Remove the DataWriters etc */"
    puts $file_writer "    mgr.salShutdown();"
    puts $file_writer "    \}"
    puts $file_writer "\}"
}

proc insertLoggersJava { subsys file_writer } {

    global SYSDIC EVENT_ALIASES EVTS SAL_WORK_DIR

    if { [info exists EVENT_ALIASES($subsys)] } {
        if { [info exists SYSDIC($subsys,keyedID)] } {
            set initializer "( (short) 1)"
        } else {
            set initializer "()"
        }
    }

    puts $file_writer "public class [set subsys]EventLogger_allTest extends TestCase \{\n"
    puts $file_writer "    public [set subsys]EventLogger_allTest(String name) \{"
    puts $file_writer "        super(name);"
    puts $file_writer "    \}\n"


    puts $file_writer "    public void test[set subsys]EventLogger_all() \{"
    puts $file_writer "        SAL_[set subsys] evt = new SAL_[set subsys][set initializer];"
    
    foreach alias $EVENT_ALIASES($subsys) {
        puts $file_writer "        mgr.salEvent(\"[set subsys]_command_[set alias]\");"
    }
    
    puts $file_writer "        int status = SAL_Scheduler.SAL__OK;"
    puts $file_writer "        int timeout = 3;"
    puts $file_writer "        boolean finished = false;"

    foreach alias $EVENT_ALIASES($subsys) {
        puts $file_writer "\n        [set subsys].logevent_[set alias] evt  = new [set subsys].logevent_[set alias]();"
        
        puts $file_writer "        while (!finished) \{"
        puts $file_writer "            status = evt.getEvent_[set alias](event);"
        puts $file_writer "            if (status == SAL_[set subsys].SAL__OK) \{"
        puts $file_writer "                System.out.println(\"=== Event Logged : \" + event);"
            if { [file exists $SAL_WORK_DIR/include/SAL_[set subsys]_logevent_[set alias]Jsub.tmp] } {
                set fjsub [open $SAL_WORK_DIR/include/SAL_[set subsys]_logevent_[set alias]Jsub.tmp r]
                while { [gets $fjsub rec] > -1 } {
                    puts $fcmd $rec
                }
                close $fjsub
            }
        puts $file_writer "                finished = true;"
        puts $file_writer "            \}"
        puts $file_writer "            count++;"
        puts $file_writer "            if ( count > 9 ) \{"
        puts $file_writer "                finished=true;"
        puts $file_writer "            \}"
        puts $file_writer "            try \{Thread.sleep(100);\} catch (InterruptedException e)  \{ e.printStackTrace(); \}"
        puts $file_writer "        \}"
    }


    puts $file_writer "    /* Remove the DataWriters etc */"
    puts $file_writer "    evt.salShutdown();"
    puts $file_writer "    \}"
    puts $file_writer "\}"
}

proc insertEventsMakeFileJava { subsys file_writer } {
    puts $file_writer "#----------------------------------------------------------------------------"
    puts $file_writer "#       Macros"
    puts $file_writer "#----------------------------------------------------------------------------"
    puts $file_writer "CFG = Release"

    puts $file_writer "ifeq (\$(CFG), Release)"
    puts $file_writer "CC            = gcc"
    puts $file_writer "CXX           = g++"
    puts $file_writer "LD            = \$(CXX) \$(CCFLAGS) \$(CPPFLAGS)"
    puts $file_writer "AR            = ar"
    puts $file_writer "PICFLAGS      = -fPIC"
    puts $file_writer "CPPFLAGS      = \$(PICFLAGS) \$(GENFLAGS) -g \$(SAL_CPPFLAGS) -D_REENTRANT -Wall -I\".\" -I\"\$(OSPL_HOME)/examples/include\" -I\"\$(OSPL_HOME)/examples\" -I\"\$(OSPL_HOME)/include\" -I\"\$(OSPL_HOME)/include/sys\" -I\"\$(OSPL_HOME)/include/dcps/C++/SACPP\" -I../../[set subsys]/cpp/src -I\"\$(SAL_HOME)/include\" -I.. -I\"\$(SAL_WORK_DIR)/include\" -Wno-write-strings -DSAL_SUBSYSTEM_ID_IS_KEYED"
    puts $file_writer "OBJEXT        = .o"
    puts $file_writer "OUTPUT_OPTION = -o \"\$@\""
    puts $file_writer "COMPILE.c     = \$(CC) \$(CFLAGS) \$(CPPFLAGS) -c"
    puts $file_writer "COMPILE.cc    = \$(CXX) \$(CCFLAGS) \$(CPPFLAGS) -c"
    puts $file_writer "LDFLAGS       = -L\".\" -L\"\$(OSPL_HOME)/lib\" -Wl,-rpath,\$\$ORIGIN -Wl,-rpath,\$\$ORIGIN/\$(OSPL_HOME)/lib -L\"\$(SAL_WORK_DIR)/lib\""
    puts $file_writer "CCC           = \$(CXX)"
    puts $file_writer "MAKEFILE      = Makefile.sacpp_[set subsys]_all_testevents // may be not needed"
    puts $file_writer "DEPENDENCIES  ="
    puts $file_writer "BTARGETDIR    = ./"

    puts $file_writer "BIN1           = \$(BTARGETDIR)sacpp_[set subsys]_all_sender"
    puts $file_writer "OBJS1          = .obj/SAL_[set subsys].o .obj/sacpp_[set subsys]_all_sender.o"
    puts $file_writer "SRC           = ../src/SAL_[set subsys].cpp    sacpp_[set subsys]_all_senderc"

    puts $file_writer "BIN2          = \$(BTARGETDIR)sacpp_[set subsys]_all_logger"
    puts $file_writer "OBJS2         = .obj/SAL_[set subsys].o .obj/sacpp_[set subsys]_all_logger.o"
    puts $file_writer "SRC           = ../src/SAL_[set subsys].cpp    sacpp_[set subsys]_all_loggerc"

    puts $file_writer "CAT           = cat"
    puts $file_writer "MV            = mv -f"
    puts $file_writer "RM            = rm -rf"
    puts $file_writer "CP            = cp -p"
    puts $file_writer "NUL           = /dev/null"
    puts $file_writer "MKDIR         = mkdir -p"
    puts $file_writer "TESTDIRSTART  = test -d"
    puts $file_writer "TESTDIREND    = ||"
    puts $file_writer "TOUCH         = touch"
    puts $file_writer "EXEEXT        ="
    puts $file_writer "LIBPREFIX     = lib"
    puts $file_writer "LIBSUFFIX     ="
    puts $file_writer "GENFLAGS      = -g"
    puts $file_writer "LDLIBS        = -l\"sacpp_[set subsys]_types\$(LIBSUFFIX)\" -l\"dcpssacpp\" -l\"dcpsgapi\" -l\"ddsuser\" -l\"ddskernel\" -l\"ddsserialization\" -l\"ddsconfparser\" -l\"ddsconf\" -l\"ddsdatabase\" -l\"ddsutil\" -l\"ddsos\" -ldl \$(subst lib,-l,\$(sort \$(basename \$(notdir \$(wildcard /usr/lib/librt.so /lib/librt.so))))) -lpthread"
    puts $file_writer "LINK.cc       = \$(LD) \$(LDFLAGS)"
    puts $file_writer "EXPORTFLAGS   ="
    puts $file_writer "endif"

    puts $file_writer "#----------------------------------------------------------------------------"
    puts $file_writer "#       Local targets"
    puts $file_writer "#----------------------------------------------------------------------------"

    puts $file_writer "all: \$(BIN1) \$(BIN2)"

    puts $file_writer ".obj/sacpp_[set subsys]_all_sender.o: ../src/sacpp_[set subsys]_all_sender.cpp"
    puts $file_writer "	@\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\""
    puts $file_writer "	\$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_sender.cpp"

    puts $file_writer "\$(BIN1): \$(OBJS1)"
    puts $file_writer "	@\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\""
    puts $file_writer "	\$(LINK.cc) \$(OBJS1) \$(LDLIBS) \$(OUTPUT_OPTION)"

    puts $file_writer ".obj/sacpp_[set subsys]_all_logger.o: ../src/sacpp_[set subsys]_all_logger.cpp"
    puts $file_writer "	@\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\""
    puts $file_writer "	\$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_logger.cpp"

    puts $file_writer "\$(BIN2): \$(OBJS2)"
    puts $file_writer "	@\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\""
    puts $file_writer "	\$(LINK.cc) \$(OBJS2) \$(LDLIBS) \$(OUTPUT_OPTION)"

    puts $file_writer "generated: \$(GENERATED_DIRTY)"
    puts $file_writer "	@-:"

    puts $file_writer "clean:"
    puts $file_writer "	-\$(RM) \$(OBJS)"

    puts $file_writer "realclean: clean"
    puts $file_writer "	-\$(RM) \$(BIN)"
    puts $file_writer "	-\$(RM) .obj/"

    puts $file_writer "check-syntax:"
    puts $file_writer "	\$(COMPILE.cc) \$(EXPORTFLAGS) -Wall -Wextra -pedantic -fsyntax-only \$(CHK_SOURCES)"

    puts $file_writer "#----------------------------------------------------------------------------"
    puts $file_writer "#       Dependencies"
    puts $file_writer "#----------------------------------------------------------------------------"

    puts $file_writer "\$(DEPENDENCIES):"
    puts $file_writer "	@\$(TOUCH) \$(DEPENDENCIES)"

    puts $file_writer "depend:"
    puts $file_writer "	-VDIR=.obj/ \$(MPC_ROOT)/depgen.pl  \$(CFLAGS) \$(CCFLAGS) \$(CPPFLAGS) -f \$(DEPENDENCIES) \$(SRC) 2> \$(NUL)"

    puts $file_writer "include \$(DEPENDENCIES)"
}
