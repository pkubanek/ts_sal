

proc genericcmdevt { subsys } {
global SAL_DIR SAL_WORK_DIR SYSDIC
   set fout [open $SAL_WORK_DIR/$subsys/cpp/src/[set subsys]Commander.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the '[set subsys]Commander' executable.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include \"SAL_[set subsys].h\"
#include \"ccpp_sal_[set subsys].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set subsys];

/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int [set subsys]Commander(char *device, char *property, char *action, char *value, char *modifiers);
\}


int [set subsys]Commander(unsigned int timeout ,char *device, char *property, char *action, char *value, char *modifiers)
\{
  salReturn status = SAL__OK;
  int cmdId;

  os_time delay_1s = \{ 1, 0 \};

  // Initialize"
   if { [info exists SYSDIC($subsys,keyedID)] } {
      puts $fout "
  int [set subsys]ID = 1;
  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);"
   } else {
      puts $fout "  SAL_[set subsys] mgr = SAL_[set subsys]();"
   }
   puts $fout "
  cmd.salCommand();

  [set subsys]::command command; /* Example on Stack */
  command.private_revCode = DDS::string_dup(\"LSST TEST COMMAND\");
  command.device = DDS::string_dup(device);
  command.property = DDS::string_dup(property);
  command.action = DDS::string_dup(action);
  command.value = DDS::string_dup(value);
  command.modifiers = DDS::string_dup(modifiers);
  cmdId = cmd.issueCommand(command);

  os_nanoSleep(delay_1s);
  status = cmd.waitForCompletion(cmdId, timeout);

  /* Remove the DataWriters etc */
  cmd.salShutdown();

  return status;
\}



int main (int argc, char *argv\[\])
\{
  unsigned int timeout = 0;

  if (argc > 1) \{
     sscanf(argv\[1\],\"%d\",&timeout);
  \}
  return [set subsys]Commander (timeout, argv\[2\], argv\[3\], argv\[4\], argv\[5\], argv\[6\]);
\}
"
   close $fout
   set fout [open $SAL_WORK_DIR/$subsys/cpp/src/[set subsys]Controller.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the '[set subsys]Controller' executable.
 *
 ***/
#include <string>
#include <sstream>
#include <iostream>
#include \"SAL_[set subsys].h\"
#include \"ccpp_sal_[set subsys].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set subsys];

/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int [set subsys]Controller(int timeout);
\}


int [set subsys]Controller(int timeout)
\{
  salReturn status = SAL__OK;
  int cmdId;

  os_time delay = \{ timeout, 0 \};
  os_time delay_2ms = \{ 0, 2000000 \};

  // Initialize"
   if { [info exists SYSDIC($subsys,keyedID)] } {
      puts $fout "
  int [set subsys]ID = 1;
  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);"
   } else {
      puts $fout "  SAL_[set subsys] mgr = SAL_[set subsys]();"
   }
   puts $fout "
  cmd.salProcessor();

  [set subsys]::commandSeq command; /* Example on Stack */
  while (1) \{

     cmdId = cmd.acceptCommand(command);
     if (cmdId > 0) \{
       if (timeout > 0) \{
          cmd.ackCommand(cmdId, SAL__CMD_INPROGRESS, timeout, \"Ack : OK\");
          os_nanoSleep(delay);
       \}       
       cmd.ackCommand(cmdId, SAL__CMD_COMPLETE, 0, \"Done : OK\");
     \}
     os_nanoSleep(delay_2ms);
  \}

  /* Remove the DataWriters etc */
  cmd.salShutdown();

  return status;
\}


int main (int argc, char *argv\[\])
\{
  int timeout = 0;

  if (argc > 1) \{
     sscanf(argv\[1\],\"%d\",&timeout);
  \}
 
  return [set subsys]Controller (timeout);
\}

"
   close $fout
   set fout [open $SAL_WORK_DIR/$subsys/cpp/src/[set subsys]Event.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the '[set subsys]_Event' executable.
 *
 ***/

#include <string>
#include <sstream>
#include <iostream>
#include \"SAL_[set subsys].h\"
#include \"ccpp_sal_[set subsys].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set subsys];

/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int [set subsys]_Event(char *alias , char *message);
\}

int [set subsys]_Event(char *alias, char *message)
\{
  
  int priority = SAL__EVENT_INFO;
"
   if { [info exists SYSDIC($subsys,keyedID)] } {
      puts $fout "
  int [set subsys]ID = 1;
  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);"
   } else {
      puts $fout "  SAL_[set subsys] mgr = SAL_[set subsys]();"
   }
   puts $fout "
  // generate event
  mgr.logEvent(message, priority);
  cout << \"=== Event \" << alias << \" generated = \" << message << endl;

  /* Remove the DataWriters etc */
  mgr.salShutdown();

  return 0;
\}


int main (int argc, char *argv\[\])
\{
  if (argc < 3) \{
     cout << \"A alias + message text is required at a minimum\" << endl;
     exit(1);
  \}
  return [set subsys]_Event (argv\[1\], argv\[2\]);
\}
"
   close $fout
   set fout [open $SAL_WORK_DIR/$subsys/cpp/src/[set subsys]EventLogger.cpp w]
   puts $fout "
/*
 * This file contains the implementation for the '[set subsys]_EventLogger' executable.
 *
 ***/


#include <string>
#include <sstream>
#include <iostream>
#include \"SAL_[set subsys].h\"
#include \"ccpp_sal_[set subsys].h\"
#include \"os.h\"
using namespace DDS;
using namespace [set subsys];

/* entry point exported and demangled so symbol can be found in shared library */
extern \"C\"
\{
  OS_API_EXPORT
  int [set subsys]_EventLogger(char *topic_name);
\}


int [set subsys]_EventLogger(char *topic_name)
\{
  os_time delay_2ms = \{ 0, 2000000 \};
  [set subsys]_logeventC SALInstance;
"
   if { [info exists SYSDIC($subsys,keyedID)] } {
      puts $fout "
  int [set subsys]ID = 1;
  SAL_[set subsys] mgr = SAL_[set subsys]([set subsys]ID);"
   } else {
      puts $fout "  SAL_[set subsys] mgr = SAL_[set subsys]();"
   }
   puts $fout "
  cout << \"=== \[EventLog\] Ready ...\" << endl;

  bool closed = false;
  ReturnCode_t status =  - 1;
  int count = 0;
  while (1)
  \{
    status = mgr.getEventC(&SALInstance);
    if (status == SAL__OK) \{
        cout << \"=== message = \" + SALInstance.message << endl;
    \}
    os_nanoSleep(delay_2ms);
    ++count;
  \}

  os_nanoSleep(delay_2ms);

  //cleanup
  mgr.salShutdown();

  return 0;
\}

int main (int argc, char *argv\[\])
\{
  return [set subsys]_EventLogger(\"[set subsys]_logevent\");
\}
"
   close $fout
}


