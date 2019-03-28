proc gencommandtestssinglefilejava { subsys } {
    # Creates multiple files which contains an implementation of all the
    # commands defined within this subsys.

    global SAL_WORK_DIR

    puts "commands script firing"

    # Create the file writers for the commander and controller.
    set commander_java_file_writer [open $SAL_WORK_DIR/$subsys/java/src/[set subsys]_all_commander.java w]
    # set controller_cpp_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/sacpp_[set subsys]_all_controller.cpp w]
    # set makefile_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testcommands w]

    # Insert content into the commander.
    insertCommandHeaderJava $subsys $commander_java_file_writer
    insertCommandersJava $subsys $commander_java_file_writer

    # # Insert content into the controller.
    # insertCommandHeader $subsys $controller_cpp_file_writer
    # insertControllers $subsys $controller_cpp_file_writer

    # # Insert content into the makefile.
    # insertMakeFile $subsys $makefile_file_writer

    # # Close all the file writers.
    # close $commander_cpp_file_writer
    # close $controller_cpp_file_writer
    # close $makefile_file_writer

    # # Execute the makefile. 
    # cd $SAL_WORK_DIR/$subsys/cpp/src
    # exec make -f $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testcommands
    # cd $SAL_WORK_DIR

    exit
}

proc insertCommandHeaderJava { subsys file_writer } {

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

proc insertCommandersJava { subsys file_writer } {

    global SYSDIC CMD_ALIASES CMDS

    if { [info exists CMD_ALIASES($subsys)] } {
        if { [info exists SYSDIC($subsys,keyedID)] } {
            set initializer "( (short) 1)"
        } else {
            set initializer "()"
        }
    }



    puts $file_writer "public class [set subsys]Commander_All_Test extends TestCase \{\n"
    puts $file_writer "    public [set subsys]Commander_All_Test(String name) \{"
    puts $file_writer "        super(name);"
    puts $file_writer "    \}\n"


    puts $file_writer "    public void test[set subsys]Commander_All() \{"
    puts $file_writer "        SAL_[set subsys] mgr = new SAL_[set subsys][set initializer];"
    foreach alias $CMD_ALIASES($subsys) {
        puts $file_writer "        mgr.salCommand(\"[set subsys]_command_[set alias]\");"
    }

    puts $file_writer "        int count = 0;"
    puts $file_writer "        int cmdId = 0;"
    puts $file_writer "        int status = 0;"
    puts $file_writer "        timeout = 3;"


    foreach alias $CMD_ALIASES($subsys) {
        puts $file_writer "\n        [set subsys].command_[set alias] command  = new [set subsys].command_[set alias]();"
        
        set revcode [getRevCode [set subsys]_command_[set alias] short]
        puts $file_writer "        command.private_revCode = \"[string trim $revcode _]\";"
        set cpars $CMDS($subsys,$alias)
        puts $file_writer "        command.device   = \"[lindex $cpars 0]\";"
        puts $file_writer "        command.property = \"[lindex $cpars 1]\";"
        puts $file_writer "        command.action   = \"[lindex $cpars 2]\";"

        set narg 1

        foreach p $CMDS($subsys,$alias,param) {
            set pname [lindex $p 1]
            set ptype [lindex $p 0]
            if { [llength [split $pname "()"]] > 1 } {
                set l 0
                set pspl [split $pname "()"]
                set pname [lindex $pspl 0]
                set pdim  [lindex $pspl 1]
                while { $l < $pdim } {
                    switch $ptype {
                        boolean { puts $file_writer "        command.[set pname]\[$l\] = true;" }
                        double  { puts $file_writer "        command.[set pname]\[$l\] = (double) 1.0;" }
                        int     { puts $file_writer "        command.[set pname]\[$l\] = (int) 1;" }
                        long    { puts $file_writer "        command.[set pname]\[$l\] = (int) 1;" }
                    }
                    l 1
                }
            } else {
                switch $ptype {
                    boolean { puts $file_writer "        command.[set pname] = true;" }
                    double  { puts $file_writer "        command.[set pname] = (double) 1.0;" }
                    int     { puts $file_writer "        command.[set pname] = (int) 1;" }
                    long    { puts $file_writer "        command.[set pname] = (int) 1;" }
                    string  { puts $file_writer "        command.[set pname] = \"testing\";" }
                }
            }
            incr narg 1
        }

        puts $file_writer "        cmdId = mgr.issueCommand_[set alias](command);"

        puts $file_writer "        try \{Thread.sleep(1000);\} catch (InterruptedException e)  \{ e.printStackTrace(); \}"
        puts $file_writer "        status = mgr.waitForCompletion_[set alias](cmdId, timeout);"        
    
    }

    puts $file_writer "    /* Remove the DataWriters etc */"
    puts $file_writer "    mgr.salShutdown();"
    puts $file_writer "    \}"
    puts $file_writer "\}"

    # foreach alias $CMD_ALIASES($subsys) {
    #     puts $file_writer "  mgr.salCommand(\"[set subsys]_command_[set alias]\");"
    # }
    # puts $file_writer "  cout << \"=== [set subsys] controllers ready \" << endl;"




    # foreach alias $CMD_ALIASES($subsys) {
    #     puts $file_writer "  \{"
    #     puts $file_writer "    int cmdId;"
    #     puts $file_writer "    int timeout=10;"
    #     puts $file_writer "    int status=0;"
    #     puts $file_writer "    [set subsys]_command_[set alias]C myData;"
        
    #     puts $file_writer "    cmdId = mgr.issueCommand_[set alias](&myData);"
    #     puts $file_writer "    cout << \"=== command $alias issued = \" << endl;"
    #     puts $file_writer "    status = mgr.waitForCompletion_[set alias](cmdId, timeout);"
    #     puts $file_writer "    cout << status << endl;"
    #     puts $file_writer "  \}\n"
    # }
    # puts $file_writer "  mgr.salShutdown();"
    # puts $file_writer "  exit(0);"
    # puts $file_writer "\}"
}

proc insertControllers { subsys file_writer } {

    global SYSDIC SAL_WORK_DIR CMD_ALIASES 

    puts $file_writer "/* entry point exported and demangled so symbol can be found in shared library */"
    puts $file_writer "extern \"C\""
    puts $file_writer "\{"
    puts $file_writer "  OS_API_EXPORT"
    puts $file_writer "  int test_[set subsys]_all_controller();"
    puts $file_writer "\}"

    puts $file_writer "int test_[set subsys]_all_controller()"
    puts $file_writer "\{"
    puts $file_writer "  os_time delay_10ms = \{ 0, 10000000 \};"
    puts $file_writer "  int cmdId = -1;"
    puts $file_writer "  int timeout = 1;"

    if { [info exists SYSDIC($subsys,keyedID)] } {
        puts $file_writer "  int [set subsys]ID = 1;"
        puts $file_writer "  if (getenv(\"LSST_[string toupper [set subsys]]_ID\") != NULL) \{"
        puts $file_writer "    sscanf(getenv(\"LSST_[string toupper [set subsys]]_ID\"),\"%d\",&[set subsys]ID);"
        puts $file_writer "  \}"
        puts $file_writer "  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);\n"
    } else {
        puts $file_writer "  SAL_[set subsys] mgr = SAL_[set subsys]();"
    }

    foreach alias $CMD_ALIASES($subsys) {
        puts $file_writer "  mgr.salProcessor(\"[set subsys]_command_[set alias]\");"
    }
    puts $file_writer "  cout << \"=== [set subsys] controllers ready \" << endl;"

    foreach alias $CMD_ALIASES($subsys) {
        puts $file_writer "  while (1)" 
        puts $file_writer "  \{"
        puts $file_writer "    [set subsys]_command_[set alias]C SALInstance;"
        puts $file_writer "    cmdId = mgr.acceptCommand_[set alias](&SALInstance);"
        puts $file_writer "    if (cmdId > 0) \{"
        puts $file_writer "      cout << \"=== command [set alias] received = \" << endl;"

        set fragment_reader [open $SAL_WORK_DIR/include/SAL_[set subsys]_command_[set alias]Csub.tmp r]
        while { [gets $fragment_reader line] > -1 } {
            puts $file_writer "  $line"
        }
        close $fragment_reader

        puts $file_writer "      if (timeout > 0) \{"
        puts $file_writer "        mgr.ackCommand_[set alias](cmdId, SAL__CMD_INPROGRESS, 0, \"Ack : OK\");"
        puts $file_writer "        os_nanoSleep(delay_10ms);"
        puts $file_writer "      \}"
        puts $file_writer "      mgr.ackCommand_[set alias](cmdId, SAL__CMD_COMPLETE, 0, \"Done : OK\");"
        puts $file_writer "      break;"
        puts $file_writer "    \}"
        puts $file_writer "    os_nanoSleep(delay_10ms);"
        puts $file_writer "  \}"
    }

    puts $file_writer "/* Remove the DataWriters etc */"
    puts $file_writer "  mgr.salShutdown();"
    puts $file_writer "  return 0;"
    puts $file_writer "\}"

    puts $file_writer "int main (int argc, char *argv\[\])\{"
    puts $file_writer "    return test_[set subsys]_all_controller();"
    puts $file_writer "\}"
}

proc insertMakeFile { subsys file_writer } {
    
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
    puts $file_writer "MAKEFILE      = Makefile.sacpp_[set subsys]_testcommands // may be not needed"
    puts $file_writer "DEPENDENCIES  ="
    puts $file_writer "BTARGETDIR    = ./"

    puts $file_writer "BIN1           = \$(BTARGETDIR)sacpp_[set subsys]_all_commander"
    puts $file_writer "OBJS1          = .obj/SAL_[set subsys].o .obj/sacpp_[set subsys]_all_commander.o"
    puts $file_writer "SRC           = ../src/SAL_[set subsys].cpp    sacpp_[set subsys]_all_commanderc"

    puts $file_writer "BIN2          = \$(BTARGETDIR)sacpp_[set subsys]_all_controller"
    puts $file_writer "OBJS2         = .obj/SAL_[set subsys].o .obj/sacpp_[set subsys]_all_controller.o"
    puts $file_writer "SRC           = ../src/SAL_[set subsys].cpp    sacpp_[set subsys]_all_controllerc"

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

    puts $file_writer ".obj/sacpp_[set subsys]_all_commander.o: ../src/sacpp_[set subsys]_all_commander.cpp"
    puts $file_writer "	@\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\""
    puts $file_writer "	\$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_commander.cpp"

    puts $file_writer "\$(BIN1): \$(OBJS1)"
    puts $file_writer "	@\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\""
    puts $file_writer "	\$(LINK.cc) \$(OBJS1) \$(LDLIBS) \$(OUTPUT_OPTION)"

    puts $file_writer ".obj/sacpp_[set subsys]_all_controller.o: ../src/sacpp_[set subsys]_all_controller.cpp"
    puts $file_writer "	@\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\""
    puts $file_writer "	\$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_controller.cpp"

    puts $file_writer "\$(BIN2): \$(OBJS2)"
    puts $file_writer "	@\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\""
    puts $file_writer "	\$(LINK.cc) \$(OBJS2) \$(LDLIBS) \$(OUTPUT_OPTION)"

    puts $file_writer "generated: \$(GENERATED_DIRTY)"
	puts $file_writer "@-:"

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
