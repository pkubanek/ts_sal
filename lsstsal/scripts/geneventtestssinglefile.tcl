proc geneventtestssinglefilescpp { subsys } {
    # Creates multiple files which contains an implementation of all the
    # events defined within this subsys

    global CMD_ALIASES SAL_WORK_DIR

    # Create the file writers for the commander, controller and makefile.
    set sender_cpp_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/sacpp_[set subsys]_all_sender.cpp w]
    set logger_cpp_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/sacpp_[set subsys]_all_logger.cpp w]
    set makefile_file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testevents w]

    # Insert content into the sender
    insertEventHeader $subsys $sender_cpp_file_writer
    insertSenders $subsys $sender_cpp_file_writer

    # Insert content into the logger
    insertEventHeader $subsys $logger_cpp_file_writer
    insertLoggers $subsys $logger_cpp_file_writer

    # Insert content into the makefile.
    insertEventsMakeFile $subsys $makefile_file_writer

    # Close all the file writers.
    close $sender_cpp_file_writer
    close $logger_cpp_file_writer
    close $makefile_file_writer

    # Execute the makefile. 
    # cd $SAL_WORK_DIR/$subsys/cpp/src
    # exec make -f $SAL_WORK_DIR/$subsys/cpp/src/Makefile.sacpp_[set subsys]_all_testcommands
    # exit
}

proc insertEventHeader { subsys file_writer } {

    puts $file_writer "
/*
 * This file contains an implementation of all the events defined within the 
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
#include <stdlib.h>

#include \"example_main.h\"

using namespace DDS;
using namespace [set subsys];"
}

proc insertSenders { subsys file_writer } {

    global EVENT_ALIASES SYSDIC SAL_WORK_DIR

    puts $file_writer "
int main (int argc, char *argv\[\])
\{ 
  int priority = SAL__EVENT_INFO;"

  # Create the SAL manager 
    if { [info exists SYSDIC($subsys,keyedID)] } {
        puts $file_writer "
  // Creating SAL manager
  int [set subsys]ID = 1;
  if (getenv(\"LSST_[string toupper [set subsys]]_ID\") != NULL) \{
    sscanf(getenv(\"LSST_[string toupper [set subsys]]_ID\"),\"%d\",&[set subsys]ID);
  \}
  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);\n"
    } else {
      puts $file_writer "  SAL_[set subsys] mgr = SAL_[set subsys]();"
    }

    # Most work done in this loop
    foreach alias $EVENT_ALIASES($subsys) { 
        puts $file_writer "  [set subsys]_logevent_[set alias]C myData;"
        puts $SAL_WORK_DIR/include/SAL_[set subsys]_logevent_[set alias]Cpub.tmp

        # Open file with code fragment with data, copy this data into cpp file
        set fragment_reader [open $SAL_WORK_DIR/include/SAL_[set subsys]_logevent_[set alias]Cpub.tmp r]
            while { [gets $fragment_reader line] > -1 } {
            puts $file_writer [string range $line 2 1000]
        }
        
        puts $file_writer "  priority = myData.priority;
  mgr.logEvent_[set alias](&myData, priority);
  cout << \"=== Event $alias generated = \" << endl;
  sleep(1);\n"
    }

    puts $file_writer "
  /* Remove the DataWriters etc */
  mgr.salShutdown();

  return 0;
\}"
}

proc insertLoggers { subsys file_writer } {

    global EVENT_ALIASES SAL_WORK_DIR SYSDIC

    puts $file_writer "
/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int test_[set subsys]_all_logger();
\}"

    puts $file_writer "
int test_[set subsys]_all_logger()
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
  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);\n"
    } else {
        puts $file_writer "  SAL_[set subsys] mgr = SAL_[set subsys]();\n"
    }

    foreach alias $EVENT_ALIASES($subsys) {
        puts $file_writer "  mgr.salEventSub(\"[set subsys]_logevent_[set alias]\");"
    }
    puts $file_writer "  cout << \"=== [set subsys] loggers ready \" << endl;"


    foreach alias $EVENT_ALIASES($subsys) {
        puts $file_writer "
  while (1) 
  \{
    [set subsys]_logevent_[set alias]C SALInstance;
    status = mgr.getEvent_[set alias](&SALInstance);
    if (status == SAL__OK) \{
      cout << \"=== Event [set alias] received = \" << endl;"

        set fin [open $SAL_WORK_DIR/include/SAL_[set subsys]_logevent_[set alias]Csub.tmp r]
        while { [gets $fin rec] > -1 } {
            puts $file_writer "      [string trim $rec]"
        }    
        puts $file_writer "      break;\n    \}\n  \}"
    }

    puts $file_writer "
/* Remove the DataWriters etc */
  mgr.salShutdown();
  return 0;
\}

int main (int argc, char *argv\[\])
\{
  return test_[set subsys]_all_controller();
\}"
}

proc insertEventsMakeFile { subsys file_writer } {
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
MAKEFILE      = Makefile.sacpp_[set subsys]_all_testevents // may be not needed
DEPENDENCIES  =
BTARGETDIR    = ./

BIN1           = \$(BTARGETDIR)sacpp_[set subsys]_all_sender
OBJS1          = .obj/SAL_[set subsys].o .obj/sacpp_[set subsys]_all_sender.o
SRC           = ../src/SAL_[set subsys].cpp    sacpp_[set subsys]_all_senderc

BIN2          = \$(BTARGETDIR)sacpp_[set subsys]_all_logger
OBJS2         = .obj/SAL_[set subsys].o .obj/sacpp_[set subsys]_all_logger.o
SRC           = ../src/SAL_[set subsys].cpp    sacpp_[set subsys]_all_loggerc

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

.obj/sacpp_[set subsys]_all_sender.o: ../src/sacpp_[set subsys]_all_sender.cpp
	@\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\"
	\$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_sender.cpp

\$(BIN1): \$(OBJS1)
	@\$(TESTDIRSTART) \"\$(BTARGETDIR)\" \$(TESTDIREND) \$(MKDIR) \"\$(BTARGETDIR)\"
	\$(LINK.cc) \$(OBJS1) \$(LDLIBS) \$(OUTPUT_OPTION)

.obj/sacpp_[set subsys]_all_logger.o: ../src/sacpp_[set subsys]_all_logger.cpp
	@\$(TESTDIRSTART) \".obj/../src\" \$(TESTDIREND) \$(MKDIR) \".obj/../src\"
	\$(COMPILE.cc) \$(EXPORTFLAGS) \$(OUTPUT_OPTION) ../src/sacpp_[set subsys]_all_logger.cpp

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