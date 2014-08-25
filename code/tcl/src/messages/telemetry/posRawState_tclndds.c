/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "posRawState.h"
#include "posRawState_tclndds.h"

int 
Tcl2Ndds_posRawState (posRawState nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (posRawState_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for posRawState.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,posRawState_ArgCount);
    return (-1);
  }

  for (i=0; i<100; i++)
      sscanf(argv[count++],"%f",&(nddsObj->kalmanGain[i]));
  for (i=0; i<9; i++)
      sscanf(argv[count++],"%f",&(nddsObj->gpsPosCovar[i]));
  for (i=0; i<9; i++)
      sscanf(argv[count++],"%f",&(nddsObj->gpsRotCovar[i]));
  for (i=0; i<9; i++)
      sscanf(argv[count++],"%f",&(nddsObj->compassRotCovar[i]));
  for (i=0; i<9; i++)
      sscanf(argv[count++],"%f",&(nddsObj->imuRotCovar[i]));
  for (i=0; i<9; i++)
      sscanf(argv[count++],"%f",&(nddsObj->imuPosCovar[i]));
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* posRawStateStruct */


int 
Ndds2Tcl_posRawState (posRawState nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  for (i=0; i<100; i++) {
    sprintf (tmpStr, "%f ", nddsObj->kalmanGain[i]);
    newValue = Tcl_SetVar2 (interp, "this", "kalmanGain", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<9; i++) {
    sprintf (tmpStr, "%f ", nddsObj->gpsPosCovar[i]);
    newValue = Tcl_SetVar2 (interp, "this", "gpsPosCovar", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<9; i++) {
    sprintf (tmpStr, "%f ", nddsObj->gpsRotCovar[i]);
    newValue = Tcl_SetVar2 (interp, "this", "gpsRotCovar", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<9; i++) {
    sprintf (tmpStr, "%f ", nddsObj->compassRotCovar[i]);
    newValue = Tcl_SetVar2 (interp, "this", "compassRotCovar", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<9; i++) {
    sprintf (tmpStr, "%f ", nddsObj->imuRotCovar[i]);
    newValue = Tcl_SetVar2 (interp, "this", "imuRotCovar", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  for (i=0; i<9; i++) {
    sprintf (tmpStr, "%f ", nddsObj->imuPosCovar[i]);
    newValue = Tcl_SetVar2 (interp, "this", "imuPosCovar", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* posRawStateStruct */


