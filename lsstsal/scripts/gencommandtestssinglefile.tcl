proc gencommandtestsinglefilescpp { subsys } {
    # Creates a file that contains tests for all commands of this subsystem

    # CMD_ALIASES: All the commands for the passed subsys eg; abort, enable...
    # CMDS: ??
    global CMD_ALIASES CMDS SAL_WORK_DIR SYSDIC

    set file_writer [open $SAL_WORK_DIR/$subsys/cpp/src/sacpp_[set subsys]_all_commander.cpp w]
    
    addHeader $subsys $file_writer
    addCommands $subsys $file_writer
    exit
}

proc addHeader { subsys file_writer } {
    # Creates the file and adds necessary "# include"'s.

    global CMD_ALIASES CMDS SAL_WORK_DIR SYSDIC    
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

int main (int argc, char *argv\[\])
\{
    int cmdId;
    int timeout=10;
    int status=0;
"

}

proc addCommands { subsys file_writer } {
    # Adds and sends every command for this subsystem

    global CMD_ALIASES CMDS SAL_WORK_DIR SYSDIC

    puts $file_writer "
  // Create the data objects of all the commands"
    foreach alias $CMD_ALIASES($subsys) {
        puts $file_writer "  [set subsys]_command_[set alias]C [set alias]Data;"
    }

    puts $file_writer "
  // Create the SAL Manager for our subsystem
  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);"

    puts $file_writer "  Issue the commands"
    foreach alias $CMD_ALIASES($subsys) {
        puts $file_writer "
  cmdId = mgr.issueCommand_[set alias](&[set alias]Data);
  cout << \"=== command $alias issued = \" << endl;
  status = mgr.waitForCompletion_[set alias](cmdId, timeout);"
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
