proc gencommandtestsinglefilescpp { subsys } {
    # Creates multiple files which contains an implementation of all the
    # commands defined within this subsys.

    global CMD_ALIASES SAL_WORK_DIR

    # Create the file writers for the commander, controller and makefile.
    set commander_cpp_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/sacpp_[set subsys]_all_commander.cpp w]
    set controller_cpp_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/sacpp_[set subsys]_all_controller.cpp w]
    set makefile_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testcommands w]

    # Insert content into the commander.
    insertHeader $subsys $commander_cpp_file_writer
    insertCommanders $subsys $commander_cpp_file_writer

    # Insert content into the controller.
    insertHeader $subsys $controller_cpp_file_writer
    insertControllers $subsys $controller_cpp_file_writer

    # Insert content into the makefile.
    insertMakeFile $subsys $makefile_file_writer

    # Close all the file writers.
    close $commander_cpp_file_writer
    close $controller_cpp_file_writer
    close $makefile_file_writer

    # Execute the makefile. 
    cd $SAL_WORK_DIR/$subsys/cpp/src
    exec make -f $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testcommands

}

proc insertHeader { subsys file_writer } {

    puts $file_writer "
/*
 * This file contains an implementation of all the commands defined within the 
 * [set subsys] subsystem.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include \"SAL_[set subsys].h\"
#include \"ccpp_sal_[set subsys].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set subsys];"
}

proc insertCommanders { subsys file_writer } {

    global CMD_ALIASES

    puts $file_writer "
int main (int argc, char *argv\[\])
\{
  int cmdId;
  int timeout=10;
  int status=0;"

    puts $file_writer "
  // Create the data objects of all the commands"
    foreach alias $CMD_ALIASES($subsys) {
        puts $file_writer "  [set subsys]_command_[set alias]C [set alias]Data;"
    }

    puts $file_writer "
  int [set subsys]ID = 1;
  if (getenv(\"LSST_[string toupper [set subsys]]_ID\") != NULL) \{
    sscanf(getenv(\"LSST_[string toupper [set subsys]]_ID\"), \"&d\", &[set subsys]ID);
  \}
  // Create the SAL Manager for this subsystem
  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);"

    foreach alias $CMD_ALIASES($subsys) {
       puts $file_writer "
  cmdId = mgr.issueCommand_[set alias](&[set alias]Data);
  cout << \"=== command $alias issued = \" << endl;
  status = mgr.waitForCompletion_[set alias](cmdId, timeout);
  cout << status << endl;"
    }

    puts $file_writer "
  // Remove the DataWriters and shutdown
  mgr.salShutdown();
  if (status != SAL__CMD_COMPLETE) \{
    exit(1);
  \}
  exit(0);
\}
"
}

proc insertMakeFile { subsys file_writer } {
    puts $file_writer "
#----------------------------------------------------------------------------
#       Macros
#----------------------------------------------------------------------------
CFG = Release

ifeq (\$(CFG), Release)
CC            = gcc
CXX           = g++
LD            = \$(CXX) \$(CCFLAGS) \$(CPPFLAGS)
AR            = ar
PICFLAGS      = -fPIC
CPPFLAGS      = \$(PICFLAGS) \$(GENFLAGS) -g \$(SAL_CPPFLAGS) -D_REENTRANT -Wall -I\".\" -I\"\$(OSPL_HOME)/examples/include\" -I\"\$(OSPL_HOME)/examples\" -I\"\$(OSPL_HOME)/include\" -I\"\$(OSPL_HOME)/include/sys\" -I\"\$(OSPL_HOME)/include/dcps/C++/SACPP\" -I../../[set subsys]/cpp/src -I\"\$(SAL_HOME)/include\" -I.. -I\"\$(SAL_WORK_DIR)/include\" -Wno-write-strings -DSAL_SUBSYSTEM_ID_IS_KEYED
OBJEXT        = .o
OUTPUT_OPTION = -o \"\$@\"
COMPILE.c     = \$(CC) \$(CFLAGS) \$(CPPFLAGS) -c
COMPILE.cc    = \$(CXX) \$(CCFLAGS) \$(CPPFLAGS) -c
LDFLAGS       = -L\".\" -L\"\$(OSPL_HOME)/lib\" -Wl,-rpath,\$\$ORIGIN -Wl,-rpath,\$\$ORIGIN/\$(OSPL_HOME)/lib -L\"\$(SAL_WORK_DIR)/lib\"
CCC           = \$(CXX)
MAKEFILE      = Makefile.sacpp_[set subsys]_testcommands // may be not needed
DEPENDENCIES  =
BTARGETDIR    = ./

BIN1           = \$(BTARGETDIR)sacpp_[set subsys]_all_commander
OBJS1          = .obj/SAL_[set subsys].o .obj/sacpp_[set subsys]_all_commander.o
SRC           = ../src/SAL_[set subsys].cpp    sacpp_[set subsys]_all_commanderc

BIN2          = \$(BTARGETDIR)sacpp_[set subsys]_all_controller
OBJS2         = .obj/SAL_[set subsys].o .obj/sacpp_[set subsys]_all_controller.o
SRC           = ../src/SAL_[set subsys].cpp    sacpp_[set subsys]_all_controllerc

CAT           = cat
MV            = mv -f
RM            = rm -rf
CP            = cp -p
NUL           = /dev/null
MKDIR         = mkdir -p
TESTDIRSTART  = test -d
TESTDIREND    = ||
TOUCH         = touch
EXEEXT        =
LIBPREFIX     = lib
LIBSUFFIX     =
GENFLAGS      = -g
LDLIBS        = -l\"sacpp_[set subsys]_types\$(LIBSUFFIX)\" -l\"dcpssacpp\" -l\"dcpsgapi\" -l\"ddsuser\" -l\"ddskernel\" -l\"ddsserialization\" -l\"ddsconfparser\" -l\"ddsconf\" -l\"ddsdatabase\" -l\"ddsutil\" -l\"ddsos\" -ldl \$(subst lib,-l,\$(sort \$(basename \$(notdir \$(wildcard /usr/lib/librt.so /lib/librt.so))))) -lpthread
LINK.cc       = \$(LD) \$(LDFLAGS)
EXPORTFLAGS   =
endif

#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------

all: \$(BIN1) \$(BIN2)

.obj/sacpp_[set subsys]_all_commander.o: ../src/sacpp_[set subsys]_all_commander.cpp
	@\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\"
	\$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_commander.cpp

\$(BIN1): \$(OBJS1)
	@\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\"
	\$(LINK.cc) \$(OBJS1) \$(LDLIBS) \$(OUTPUT_OPTION)

.obj/sacpp_[set subsys]_all_controller.o: ../src/sacpp_[set subsys]_all_controller.cpp
	@\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\"
	\$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_controller.cpp

\$(BIN2): \$(OBJS2)
	@\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\"
	\$(LINK.cc) \$(OBJS2) \$(LDLIBS) \$(OUTPUT_OPTION)

generated: \$(GENERATED_DIRTY)
	@-:

clean:
	-\$(RM) \$(OBJS)

realclean: clean
	-\$(RM) \$(BIN)
	-\$(RM) .obj/

check-syntax:
	\$(COMPILE.cc) \$(EXPORTFLAGS) -Wall -Wextra -pedantic -fsyntax-only \$(CHK_SOURCES)

#----------------------------------------------------------------------------
#       Dependencies
#----------------------------------------------------------------------------

\$(DEPENDENCIES):
	@\$(TOUCH) \$(DEPENDENCIES)

depend:
	-VDIR=.obj/ \$(MPC_ROOT)/depgen.pl  \$(CFLAGS) \$(CCFLAGS) \$(CPPFLAGS) -f \$(DEPENDENCIES) \$(SRC) 2> \$(NUL)

include \$(DEPENDENCIES)
"
}

proc insertControllers { subsys file_writer } {

    global CMD_ALIASES SAL_WORK_DIR SYSDIC

    puts $file_writer "
/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int test_[set subsys]_all_controller();
\}

int test_[set subsys]_all_controller()
\{
  os_time delay_10ms = \{ 0, 10000000 \};
  int cmdId = -1;
  int timeout = 1;"
    if { [info exists SYSDIC($subsys,keyedID)] } {
        puts $file_writer "
  int [set subsys]ID = 1;
  if (getenv(\"LSST_[string toupper [set subsys]]_ID\") != NULL) \{
     sscanf(getenv(\"LSST_[string toupper [set subsys]]_ID\"),\"%d\",&[set subsys]ID);
  \}
  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);"
    } else {
        puts $file_writer "  SAL_[set subsys] mgr = SAL_[set subsys]();"
    }

    foreach alias $CMD_ALIASES($subsys) {
        puts $file_writer "  mgr.salProcessor(\"[set subsys]_command_[set alias]\");"
    }
    puts $file_writer "  cout << \"=== [set subsys] controllers ready \" << endl;"

    foreach alias $CMD_ALIASES($subsys) {
        puts $file_writer "
  while (1) 
  \{
    [set subsys]_command_[set alias]C SALInstance;
    cmdId = mgr.acceptCommand_[set alias](&SALInstance);
    if (cmdId > 0) \{
      cout << \"=== command [set alias] received = \" << endl;"

        set fin [open $SAL_WORK_DIR/include/SAL_[set subsys]_command_[set alias]Csub.tmp r]
            while { [gets $fin rec] > -1 } {
                puts $file_writer "  $rec"
            }
                close $fin
            puts $file_writer "
      if (timeout > 0) \{
        mgr.ackCommand_[set alias](cmdId, SAL__CMD_INPROGRESS, 0, \"Ack : OK\");
        os_nanoSleep(delay_10ms);
      \}
      mgr.ackCommand_[set alias](cmdId, SAL__CMD_COMPLETE, 0, \"Done : OK\");
      break;
    \}
    os_nanoSleep(delay_10ms);
  \}"
    }

    puts $file_writer "
/* Remove the DataWriters etc */
  mgr.salShutdown();
  return 0;
\}

int main (int argc, char *argv\[\])\{
    return test_[set subsys]_all_controller();
\}"
}
