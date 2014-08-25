/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "sciMosaic.h"
#include "sciMosaic_tclndds.h"

int 
Tcl2Ndds_sciMosaic (sciMosaic nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (sciMosaic_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for sciMosaic.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,sciMosaic_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->camera    );
  sscanf  (argv[count++], "%d", &nddsObj->resolution);
  sscanf  (argv[count++], "%d", &nddsObj->x         );
  sscanf  (argv[count++], "%d", &nddsObj->y         );
  sscanf  (argv[count++], "%d", &nddsObj->width     );
  sscanf  (argv[count++], "%d", &nddsObj->height    );
  sscanf  (argv[count++], "%f", &nddsObj->panStart  );
  sscanf  (argv[count++], "%f", &nddsObj->tiltStart );
  sscanf  (argv[count++], "%f", &nddsObj->panEnd    );
  sscanf  (argv[count++], "%f", &nddsObj->tiltEnd   );
  sscanf  (argv[count++], "%f", &nddsObj->panStep   );
  sscanf  (argv[count++], "%f", &nddsObj->tiltStep  );

  return (count);	/* # args used in this struct. */
} /* sciMosaicStruct */


int 
Ndds2Tcl_sciMosaic (sciMosaic nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->camera    );  newValue = Tcl_SetVar2 (interp, "this", "camera", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->resolution);  newValue = Tcl_SetVar2 (interp, "this", "resolution", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->x         );  newValue = Tcl_SetVar2 (interp, "this", "x", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->y         );  newValue = Tcl_SetVar2 (interp, "this", "y", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->width     );  newValue = Tcl_SetVar2 (interp, "this", "width", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%d", nddsObj->height    );  newValue = Tcl_SetVar2 (interp, "this", "height", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->panStart  );  newValue = Tcl_SetVar2 (interp, "this", "panStart", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->tiltStart );  newValue = Tcl_SetVar2 (interp, "this", "tiltStart", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->panEnd    );  newValue = Tcl_SetVar2 (interp, "this", "panEnd", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->tiltEnd   );  newValue = Tcl_SetVar2 (interp, "this", "tiltEnd", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->panStep   );  newValue = Tcl_SetVar2 (interp, "this", "panStep", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->tiltStep  );  newValue = Tcl_SetVar2 (interp, "this", "tiltStep", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* sciMosaicStruct */


