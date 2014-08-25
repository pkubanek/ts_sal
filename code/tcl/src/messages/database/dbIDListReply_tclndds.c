/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "dbIDListReply.h"
#include "dbIDListReply_tclndds.h"

int 
Tcl2Ndds_dbIDListReply (dbIDListReply nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (dbIDListReply_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for dbIDListReply.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,dbIDListReply_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->replyStatus);
  sscanf  (argv[count++], "%d", &nddsObj->replyDestination);
  for (i=0; i<1000; i++)
      sscanf(argv[count++],"%d",&(nddsObj->targetIDs[i]));
  sscanf  (argv[count++], "%d", &nddsObj->numTargetIDs);

  return (count);	/* # args used in this struct. */
} /* dbIDListReplyStruct */


int 
Ndds2Tcl_dbIDListReply (dbIDListReply nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->replyStatus);  newValue = Tcl_SetVar2 (interp, "this", "replyStatus", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->replyDestination);  newValue = Tcl_SetVar2 (interp, "this", "replyDestination", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<1000; i++) {
    sprintf (tmpStr, "%d ", nddsObj->targetIDs[i]);
    newValue = Tcl_SetVar2 (interp, "this", "targetIDs", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->numTargetIDs);  newValue = Tcl_SetVar2 (interp, "this", "numTargetIDs", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* dbIDListReplyStruct */


