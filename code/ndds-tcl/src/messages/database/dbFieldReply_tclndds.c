/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "dbFieldReply.h"
#include "dbFieldReply_tclndds.h"

int 
Tcl2Ndds_dbFieldReply (dbFieldReply nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (dbFieldReply_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for dbFieldReply.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,dbFieldReply_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->replyStatus);
  sscanf  (argv[count++], "%d", &nddsObj->replyDestination);
  sscanf  (argv[count++], "%d", &nddsObj->targetID  );
  sscanf  (argv[count++], "%d", &nddsObj->fieldName );
  for (i=0; i<250; i++)
      sscanf(argv[count++],"%d",&(nddsObj->int_data[i]));
  sscanf  (argv[count++], "%d", &nddsObj->int_len   );
  for (i=0; i<250; i++)
      sscanf(argv[count++],"%f",&(nddsObj->float_data[i]));
  sscanf  (argv[count++], "%d", &nddsObj->float_len );
  strcpy  (nddsObj->char_data  , argv[count++]);
  sscanf  (argv[count++], "%d", &nddsObj->char_len  );

  return (count);	/* # args used in this struct. */
} /* dbFieldReplyStruct */


int 
Ndds2Tcl_dbFieldReply (dbFieldReply nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->replyStatus);  newValue = Tcl_SetVar2 (interp, "this", "replyStatus", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->replyDestination);  newValue = Tcl_SetVar2 (interp, "this", "replyDestination", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->fieldName );  newValue = Tcl_SetVar2 (interp, "this", "fieldName", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<250; i++) {
    sprintf (tmpStr, "%d ", nddsObj->int_data[i]);
    newValue = Tcl_SetVar2 (interp, "this", "int_data", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->int_len   );  newValue = Tcl_SetVar2 (interp, "this", "int_len", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<250; i++) {
    sprintf (tmpStr, "%f ", nddsObj->float_data[i]);
    newValue = Tcl_SetVar2 (interp, "this", "float_data", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->float_len );  newValue = Tcl_SetVar2 (interp, "this", "float_len", tmpStr, TCL_LEAVE_ERR_MSG);
  for (i=0; i<1500; i++) {
    sprintf (tmpStr, "%d ", nddsObj->char_data[i]);
    newValue = Tcl_SetVar2 (interp, "this", "char_data", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->char_len  );  newValue = Tcl_SetVar2 (interp, "this", "char_len", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* dbFieldReplyStruct */


