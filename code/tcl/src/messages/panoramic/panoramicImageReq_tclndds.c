/* Standard includes needed... */
#include <tcl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <NDDS.h>


#include "panoramicImageReq.h"
#include "panoramicImageReq_tclndds.h"

int 
Tcl2Ndds_panoramicImageReq (panoramicImageReq nddsObj, int argc, char **argv) {
  int count = 0;
  int i;

  if (panoramicImageReq_ArgCount != argc) {
    fprintf (stderr,"ERROR(tcl2ndds): wrong arg count for panoramicImageReq.\n");
    fprintf (stderr,"                 got %d, expected %d\n",argc,panoramicImageReq_ArgCount);
    return (-1);
  }

  {
    int num;
    sscanf  (argv[count++], "%d", &num);
    nddsObj->data = (char)num;
  }

  return (count);	/* # args used in this struct. */
} /* panoramicImageReqStruct */


int 
Ndds2Tcl_panoramicImageReq (panoramicImageReq nddsObj, Tcl_Interp *interp) {
  char tmpStr[256];
  int  i;
  char *newValue;

  sprintf (tmpStr, "%d", nddsObj->data      );  newValue = Tcl_SetVar2 (interp, "this", "data", tmpStr, TCL_LEAVE_ERR_MSG);

  return (1==1);	/* Return TRUE for now. */
} /* panoramicImageReqStruct */


