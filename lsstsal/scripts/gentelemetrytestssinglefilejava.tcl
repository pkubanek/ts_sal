proc gentelemetrytestssinglefilejava { subsys } {
    # Creates multiple files which contains an implementation of all the
    # events defined within this subsys.

    puts "telemetry script firing"

    global SAL_WORK_DIR

    # Create the file writers for the sender, logger and makefile.
    set publisher_java_file_writer [open $SAL_WORK_DIR/$subsys/java/src/[set subsys]Publisher_all.java w]
    set subscriber_java_file_writer [open $SAL_WORK_DIR/$subsys/java/src/[set subsys]Subscriber_all.java w]
    # set makefile_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testevents w]

    # Insert content into the publisher.
    insertTelemetryHeaderJava $subsys $publisher_java_file_writer
    insertPublishersJava $subsys $publisher_java_file_writer

    # Insert content into the logger.
    insertTelemetryHeaderJava $subsys $subscriber_java_file_writer
    insertSubscribersJava $subsys $subscriber_java_file_writer

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
}

proc insertTelemetryHeaderJava { subsys file_writer } {

    puts $file_writer "/*"
    puts $file_writer "* This file contains the implementation for the [set subsys] single file commander test."
    puts $file_writer "* [set subsys] subsystem generated via gencommandtestssinglefilejava.tcl"
    puts $file_writer "*"
    puts $file_writer " ***/"

    puts $file_writer "import [set subsys].*;"
    puts $file_writer "import org.lsst.sal.SAL_[set subsys];\n"
}

proc insertPublishersJava { subsys file_writer } {

    global SYSDIC TLM_ALIASES

    puts $file_writer "public class [set subsys]Publisher_all \{\n"
    puts $file_writer "    public static void main(String[] args) \{"
    puts $file_writer "        short aKey = 1;"
    puts $file_writer "        SAL_Scheduler mgr = new SAL_Scheduler(aKey);"

    foreach alias $TLM_ALIASES($subsys) {
        puts $file_writer "        mgr.salTelemetryPub(\"[set subsys]_[set alias]\");"
    }

    foreach alias $TLM_ALIASES($subsys) {
        puts $file_writer "\n        \{"
        puts $file_writer "            int count = 1;"
        puts $file_writer "            [set subsys].[set alias] theTopicInstance  = new [set subsys].[set alias]();"

        puts $file_writer "            while (count < 6) {"
        puts $file_writer "                mgr.putSample(theTopicInstance);"
        puts $file_writer "                System.out.println(\"=== \[[set alias]\] message sent\" + count);"
        puts $file_writer "                ++count;"
        puts $file_writer "                try {"
        puts $file_writer "                Thread.sleep(1000);"
        puts $file_writer "                } catch (InterruptedException e) {"
        puts $file_writer "                }"
        puts $file_writer "            }"
        puts $file_writer "        \}"
    }
    puts $file_writer "        mgr.salShutdown();"
    puts $file_writer "    \}"
    puts $file_writer "\}"

}

proc insertSubscribersJava { subsys file_writer } {

    global SYSDIC TLM_ALIASES

    puts $file_writer "public class [set subsys]Subscriber_all \{\n"
    puts $file_writer "    public static void main(String[] args) \{"
    puts $file_writer "        short aKey = 1;"
    puts $file_writer "        SAL_Scheduler mgr = new SAL_Scheduler(aKey);"

    foreach alias $TLM_ALIASES($subsys) {
        puts $file_writer "        mgr.salTelemetrySub(\"[set subsys]_[set alias]\");"
    }

    foreach alias $TLM_ALIASES($subsys) {
        puts $file_writer "\n        \{"
        puts $file_writer "            [set subsys].[set alias] SALInstance = new [set subsys].[set alias]();"
        puts $file_writer "            int samples = 0;"
        puts $file_writer "            samples = mgr.flushSamples(SALInstance);"
        puts $file_writer "            System.out.println(\"=== \[[set alias] Subscriber\] Ready ...\");"
        puts $file_writer "            boolean terminate = false;"
        puts $file_writer "            int count = 0;"
        puts $file_writer "            int iloop = 0;"
        puts $file_writer "            while (iloop < 200) \{ // We dont want the example to run indefinitely"
        puts $file_writer "                iloop++;"
        puts $file_writer "                samples = mgr.getSample(SALInstance);"
        puts $file_writer "                if (samples == SAL_Scheduler.SAL__OK) \{"
        puts $file_writer "                    count++;"
        puts $file_writer "                    System.out.println(\"=== \[[set alias] Subscriber\] samples\" + SALInstance.private_sndStamp);"
        puts $file_writer "                    System.out.println(\"=== \[[set alias] Subscriber\] message received :\" + count);"
        puts $file_writer "                \}"
        puts $file_writer "                try \{"
        puts $file_writer "                    Thread.sleep(10);"
        puts $file_writer "                \}"
        puts $file_writer "                catch(InterruptedException ie) \{"
        puts $file_writer "                    // nothing to do"
        puts $file_writer "                \}"  
        puts $file_writer "            \}"
        puts $file_writer "        \}"
    }
    puts $file_writer "    mgr.salShutdown();"
    puts $file_writer "  \}"
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
    puts $file_writer " @\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\""
    puts $file_writer " \$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_sender.cpp"

    puts $file_writer "\$(BIN1): \$(OBJS1)"
    puts $file_writer " @\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\""
    puts $file_writer " \$(LINK.cc) \$(OBJS1) \$(LDLIBS) \$(OUTPUT_OPTION)"

    puts $file_writer ".obj/sacpp_[set subsys]_all_logger.o: ../src/sacpp_[set subsys]_all_logger.cpp"
    puts $file_writer " @\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\""
    puts $file_writer " \$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_logger.cpp"

    puts $file_writer "\$(BIN2): \$(OBJS2)"
    puts $file_writer " @\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\""
    puts $file_writer " \$(LINK.cc) \$(OBJS2) \$(LDLIBS) \$(OUTPUT_OPTION)"

    puts $file_writer "generated: \$(GENERATED_DIRTY)"
    puts $file_writer " @-:"

    puts $file_writer "clean:"
    puts $file_writer " -\$(RM) \$(OBJS)"

    puts $file_writer "realclean: clean"
    puts $file_writer " -\$(RM) \$(BIN)"
    puts $file_writer " -\$(RM) .obj/"

    puts $file_writer "check-syntax:"
    puts $file_writer " \$(COMPILE.cc) \$(EXPORTFLAGS) -Wall -Wextra -pedantic -fsyntax-only \$(CHK_SOURCES)"

    puts $file_writer "#----------------------------------------------------------------------------"
    puts $file_writer "#       Dependencies"
    puts $file_writer "#----------------------------------------------------------------------------"

    puts $file_writer "\$(DEPENDENCIES):"
    puts $file_writer " @\$(TOUCH) \$(DEPENDENCIES)"

    puts $file_writer "depend:"
    puts $file_writer " -VDIR=.obj/ \$(MPC_ROOT)/depgen.pl  \$(CFLAGS) \$(CCFLAGS) \$(CPPFLAGS) -f \$(DEPENDENCIES) \$(SRC) 2> \$(NUL)"

    puts $file_writer "include \$(DEPENDENCIES)"
}
