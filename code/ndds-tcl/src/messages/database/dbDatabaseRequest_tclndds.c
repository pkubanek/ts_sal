/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "dbDatabaseRequest.h"
#include "dbDatabaseRequest_tclndds.h"

int 
Tcl2Ndds_dbDatabaseRequest (dbDatabaseRequest nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (dbDatabaseRequest_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for dbDatabaseRequest.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,dbDatabaseRequest_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->requestSource);
  sscanf  (argv[count++], "%d", &nddsObj->function  );
  sscanf  (argv[count++], "%d", &nddsObj->fieldName );
  sscanf  (argv[count++], "%d", &nddsObj->targetID  );
  sscanf  (argv[count++], "%d", &nddsObj->numResults);
  for (i=0; i<250; i++)
      sscanf(argv[count++],"%d",&(nddsObj->int_data[i]));
  sscanf  (argv[count++], "%d", &nddsObj->int_len   );
  for (i=0; i<250; i++)
      sscanf(argv[count++],"%f",&(nddsObj->float_data[i]));
  sscanf  (argv[count++], "%d", &nddsObj->float_len );
  strcpy  (nddsObj->char_data  , argv[count++]);
  sscanf  (argv[count++], "%d", &nddsObj->char_len  );

  return (count);	/* # args used in this struct. */
} /* dbDatabaseRequestStruct */


int 
Ndds2Tcl_dbDatabaseRequest (dbDatabaseRequest nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->requestSource);  newValue = Tcl_SetVar2 (interp, "this", "requestSource", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->function  );  newValue = Tcl_SetVar2 (interp, "this", "function", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->fieldName );  newValue = Tcl_SetVar2 (interp, "this", "fieldName", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->targetID  );  newValue = Tcl_SetVar2 (interp, "this", "targetID", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->numResults);  newValue = Tcl_SetVar2 (interp, "this", "numResults", tmpStr, TCL_LEAVE_ERR_MSG);
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
} /* dbDatabaseRequestStruct */


