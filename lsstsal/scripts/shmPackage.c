/*! \mainpage shmem access shared library
 *
 * \section intro_sec Introduction
 *
 *  There are two classes of
 * routines. Helper routines , and routines which provide Tcl
 * callable commands. The shared library will typically be stored
 * in /usr/local/gui/lib/shared/libshm.so and is loaded into
 * the Tcl/Tk shell with a "package require shm" command
 *
 *
 */



/*
 * shmPackage.c
 */

#ifndef lint
static char *rcsId="$Id$";
#endif

#include <tcl.h>


static char export_script[]={ " \
	namespace eval ::shm:: { \
		namespace export help setup test1 \
	} " };


static int doTest1(void)
{
  fprintf(stderr, "doTest1\n");

  /*  'x' is temporary check of library load  */

  fprintf(stderr, "shm Version 1.0\n");

  return TCL_OK;
}

/*ARGSUSED*/
static int cmdTest1(ClientData data, Tcl_Interp *interp,
               int argc, char *argv[])
{
  (void) data;
  (void) interp;
  (void) argc;
  (void) argv;

  return doTest1();
}

/*  package code  */

/*!	\fn int shm_Init(Tcl_Interp *interp)
	\brief Setup tcl namespace and initialize the package
*/

int Shm_Init(Tcl_Interp *interp)
{
  Tcl_Namespace *namesp_ptr;

  printf("shm_Init\n");

  Tcl_PkgProvide(interp, "shm", "1.0");

  /*  export namespace  */


  Tcl_Eval(interp, export_script);

  Tcl_CreateObjCommand(interp, "shm::test1", (Tcl_ObjCmdProc *)cmdTest1,
                       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);

  shmAppInit(interp);

  return TCL_OK;
}

/*  dummy  */

int _eprintf()
{
return TCL_OK;
}

