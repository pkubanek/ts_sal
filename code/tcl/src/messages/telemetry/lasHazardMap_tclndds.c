/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "lasHazardMap.h"
#include "lasHazardMap_tclndds.h"

int 
Tcl2Ndds_lasHazardMap (lasHazardMap nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (lasHazardMap_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for lasHazardMap.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,lasHazardMap_ArgCount);
    return (-1);
  }

  for (i=0; i<361; i++)
      sscanf(argv[count++],"%d",&(nddsObj->depthMap[i]));
  sscanf  (argv[count++], "%d", &nddsObj->enable    );
  sscanf  (argv[count++], "%d", &nddsObj->detect    );
  sscanf  (argv[count++], "%u", &nddsObj->msecs     );
  sscanf  (argv[count++], "%u", &nddsObj->week      );

  return (count);	/* # args used in this struct. */
} /* lasHazardMapStruct */


int 
Ndds2Tcl_lasHazardMap (lasHazardMap nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  for (i=0; i<361; i++) {
    sprintf (tmpStr, "%d ", nddsObj->depthMap[i]);
    newValue = Tcl_SetVar2 (interp, "this", "depthMap", tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);
  }
  sprintf (tmpStr, "%d", nddsObj->enable    );  newValue = Tcl_SetVar2 (interp, "this", "enable", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->detect    );  newValue = Tcl_SetVar2 (interp, "this", "detect", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->msecs     );  newValue = Tcl_SetVar2 (interp, "this", "msecs", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%u", nddsObj->week      );  newValue = Tcl_SetVar2 (interp, "this", "week", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* lasHazardMapStruct */


