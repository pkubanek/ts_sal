proc gencommandtestsinglefilescpp { subsys } {
    # Creates a file that contains tests for all commands of this subsystem

    # CMD_ALIASES: All the commands for the passed subsys eg; abort, enable...
    global CMD_ALIASES SAL_WORK_DIR

    # Create the file writers for the commanders, controllers and makefiles.
    set commander_cpp_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/sacpp_[set subsys]_all_commander.cpp w]
    set commander_makefile_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/taco.txt w]
    # set controller_cpp_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/sacpp_[set subsys]_all_controller.cpp w]
    # set controller_makefile_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testcontrollers w]
    
    # Insert content into the commander
    insertHeader $subsys $commander_cpp_file_writer
    insertCommanders $subsys $commander_cpp_file_writer

    # Insert content into the controller
    # insertHeader $subsys $controller_cpp_file_writer
    # insertControllers $subsys $controller_cpp_file_writer

    # Inserts content into the makefiles
    insertCommanderMakeFile $subsys $commander_makefile_file_writer
    # insertControllerMakeFile $subsys $controller_makefile_file_writer
    exit
    # Close all the file writers
    close $commander_cpp_file_writer
    close $commander_makefile_file_writer
    # close $controller_cpp_file_writer
    # close $controller_makefile_file_writer

    exit
}

proc insertHeader { subsys file_writer } {
    # Creates the file and adds necessary "# include"'s.
    global CMD_ALIASES  
    puts $file_writer "
/*
 * This file contains 
 *
 ***/

#include <string>
#include <sstream>
#include <iosteam>
#include <stdlib.h>
#include \"SAL_[set subsys].h\"
#include \"ccpp_sal_[set subsys].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set subsys]

"
}

proc insertCommanders { subsys file_writer } {
    # Adds and sends every command for this subsystem
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
  // Create the SAL Manager for our subsystem
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

proc insertCommanderMakeFile { subsys file_writer } {
    puts $file_writer " 
#----------------------------------------------------------------------------
#       Macros
#----------------------------------------------------------------------------
CFG = Release


// all boilerplate
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
LDFLAGS       = -L\".\" -L\"\$(OSPL_HOME)/lib\" -Wl,-rpath,\$\$ORIGIN -Wl,-rpath,\$\$ORIGIN/\$(OSPL_HOME)/lib -L\"\$(SAL_WORK_DIR)/lib\" // -L say all the places to look for libraries
CCC           = \$(CXX)
MAKEFILE      = Makefile.sacpp_[set subsys]_testcommands // may be not needed
DEPENDENCIES  = 
BTARGETDIR    = ./
// till here


// This actually doesnt need to be dynamic, but we will need another set for the controller
BIN1           = \$(BTARGETDIR)sacpp_[set subsys]_all_commander
OBJS1          = .obj/SAL_[set subsys].o .obj/sacpp_[set subsys]_all_commander.o
SRC           = ../src/SAL_[set subsys].cpp    sacpp_[set subsys]_all_commanderc 

// More boiler plate to keep
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
GENFLAGS      = -g   // This bit  needs to be done dynamically                    // -l says to look for this library within the -L locations
LDLIBS        = -l\"sacpp_[set subsys]_types\$(LIBSUFFIX)\" -l\"dcpssacpp\" -l\"dcpsgapi\" -l\"ddsuser\" -l\"ddskernel\" -l\"ddsserialization\" -l\"ddsconfparser\" -l\"ddsconf\" -l\"ddsdatabase\" -l\"ddsutil\" -l\"ddsos\" -ldl \$(subst lib,-l,\$(sort \$(basename \$(notdir \$(wildcard /usr/lib/librt.so /lib/librt.so))))) -lpthread
// until here

LINK.cc       = \$(LD) \$(LDFLAGS)
EXPORTFLAGS   = 

#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------

// The name of the subsystem here needs to be dynamic. ABd I also need a copy of

all: \$(BIN1) // Need to add the controller target here

            // These subsystem names needs to be dynamic
.obj/sacpp_[set subsys]_all_commander.o: ../src/sacpp_[set subsys]_abort_commander.cpp
    @\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\"
    \$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_abort_commander.cpp

\$(BIN1): \$(OBJS1)
    @\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\"
    \$(LINK.cc) \$(OBJS1) \$(LDLIBS) \$(OUTPUT_OPTION)
// Need another set of the above 2 stanzas for the controller, call it BIN2 and OBJS2. They will look identical to the command, but will be for the controller

// All hardocded boiler plate
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