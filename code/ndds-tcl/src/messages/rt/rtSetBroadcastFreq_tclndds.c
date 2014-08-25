/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "rtSetBroadcastFreq.h"
#include "rtSetBroadcastFreq_tclndds.h"

int 
Tcl2Ndds_rtSetBroadcastFreq (rtSetBroadcastFreq nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (rtSetBroadcastFreq_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for rtSetBroadcastFreq.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,rtSetBroadcastFreq_ArgCount);
    return (-1);
  }

  sscanf  (argv[count++], "%d", &nddsObj->sourceId  );
  sscanf  (argv[count++], "%f", &nddsObj->freq      );

  return (count);	/* # args used in this struct. */
} /* rtSetBroadcastFreqStruct */


int 
Ndds2Tcl_rtSetBroadcastFreq (rtSetBroadcastFreq nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->sourceId  );  newValue = Tcl_SetVar2 (interp, "this", "sourceId", tmpStr, TCL_LEAVE_ERR_MSG);
  sprintf (tmpStr, "%f", nddsObj->freq      );  newValue = Tcl_SetVar2 (interp, "this", "freq", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* rtSetBroadcastFreqStruct */


