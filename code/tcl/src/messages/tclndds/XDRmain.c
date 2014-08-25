/* XDRmain.c -- Kurt Schwehr -- Summer 1996

   This is the main control file for parsing XDR data specification files (.x)
   This sets up the environment and opens the files.

   The command line interface is setup to match nddsgen... especially as
   called by the Makefile written by Dan Christian to handle going from
   .x files to the ndds support code.

   This is how nddsgen is called in rovers/src/nddstypes/robot/
   Makefile.  We will not be expecting the "-arch".  If it is there,
   we'll just ignore it.

  nddsgen <filename> [-typename <name>] [-nddstype <type>] [-architecture <arch>]
          <filename> -- File containing XDR description of the type
          <name>     -- Name of the XDR type in <filename>.  Deft <filename>
          <type>     -- Name of  the  NDDS  data  type  that  will  be generated.
          <arch>     -- Architecture for the example makefile.  Def to sun4

  Right now, the program requires that you delete registry_tclndds.[ch] and all 
  the *_tclndds.? files.  Then rerun across the *.x files.  I'm sure this could be 
  greatly improved with a search and replace script... feel free to impliment 
  such a thing if you'd like.

*/

static char rcs_id[] =
  "$Id: XDRmain.c,v 1.5 1998/07/16 16:37:31 mwagner Exp $";

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#ifdef OS_VXWORKS
  #include <errno.h>    /* fexist needs this to test for ENOENT==errno */
#else 
  #include <sys/errno.h>	/* fexist needs this to test for ENOENT==errno */
#endif

#include "XDR.h"

/* Local functions */
static void openTempFiles (void);
static void openOutputFiles (char *outFilePrefix);
static void merge_files ( FILE *coutFile, FILE *houtFile );
static int  write_includes (FILE *coutFile,  char *nddsType, char *includeFileName, char *h_outFileName);

/*** UNHAPPY GLOBAL VARIABLES :( ***/
int yylineno;

FILE *REGfile;	/* Data structure to register */
FILE *T2Nfile;	/* Convert Tcl  -> Ndds */
FILE *N2Tfile;	/* Convert Ndds -> Tcl  */
FILE *houtFile;

static FILE *coutFile;
#if 0
static FILE *routFile;		/* File that registers all data types into a Tcl_HashTable */
static FILE *soutFile;		/* Header to include all of the type includes -> registry_tclndds.h */
#endif

static char h_outFileName[256];
static char *typeName;
static char *nddsType;
static char *archName;
static char *inputFileName;

/* Setup the global file pointers to write code to */
void openTempFiles (void) {
  T2Nfile = fopen ( T2N_FILE_NAME, "w" );
  N2Tfile = fopen ( N2T_FILE_NAME, "w" );

  if (!T2Nfile) { perror ("T2Nfile tmp file not opened");  exit(EXIT_FAILURE); }
  if (!N2Tfile) { perror ("N2Tfile tmp file not opened");  exit(EXIT_FAILURE); }

  return;
}

/* This is the header information needed for dealing with XDR structs */
/* s = Name of the structure */
void startStructFunction (char *s) { 
    int status;

    s = nddsType; /*typeName;*/

    /* struct removed because of typedef */
    fprintf (houtFile,"int Tcl2Ndds_%-15s (%-17s %s, int argc, char  **argv);\n", s, nddsType, nddsObj);
    fprintf (houtFile,"int Ndds2Tcl_%-15s (%-17s %s, Tcl_Interp *interp);\n", s, nddsType, nddsObj);
    fprintf (houtFile,"\n");
    
    fprintf (T2Nfile,"int \nTcl2Ndds_%s (%s %s, int argc, char **argv) {\n",  s, nddsType, nddsObj);
    fprintf (T2Nfile,"  int count = 0;\n");
    fprintf (T2Nfile,"  int i;\n");
    fprintf (T2Nfile,"\n");
    
    fprintf (T2Nfile,"  if (%s_ArgCount != argc) {\n", s);
    fprintf (T2Nfile,"    fprintf (stderr,\"ERROR(tcl2ndds): wrong arg count for %s.\\n\");\n", s);
    fprintf (T2Nfile,"    fprintf (stderr,\"                 got %%d, expected %%d\\n\",argc,%s_ArgCount);\n", s);
    fprintf (T2Nfile,"    return (-1);\n");
    fprintf (T2Nfile,"  }\n\n");
    
    fprintf (N2Tfile,"int \nNdds2Tcl_%s (%s %s, Tcl_Interp *interp) {\n",  s, nddsType, nddsObj);
    fprintf (N2Tfile,"  char tmpStr[256];\n");
    fprintf (N2Tfile,"  int  i;\n");
    fprintf (N2Tfile,"  char *newValue;\n");
    fprintf (N2Tfile,"\n");

    /* Hash Table stuff - we need a hash table to lookup the "type driver" */
#if 0
    /* Define the struct to register in the header (FIX is the header the right place?) */
    fprintf (soutFile,"NDDS_TYPE_DRIVER %sTypeDriver = {\n",s);

    fprintf (soutFile,"\t\"%s\", \n",s);					/* type 	- from command line */
    fprintf (soutFile,"\t(NDDS_REGISTER_HANDLER)  %sNddsRegister, \n",s);	/* init  	- from nddsgen */
    fprintf (soutFile,"\t(NDDS_ALLOCATE_HANDLER)  %sAllocate, \n",s);		/* allocate 	- from nddsgen */
    fprintf (soutFile,"\t(NDDS_FREE_HANDLER)      %sFree, \n",s);		/* free		- from nddsgen */
    fprintf (soutFile,"\t(NDDS_FROM_TCL_HANDLER)  Tcl2Ndds_%s, \n",s);		/* Function to convert from Tcl Strings to Ndds */
    fprintf (soutFile,"\t(NDDS_TO_TCL_HANDLER)    Ndds2Tcl_%s, \n",s);		/* Function to convert from Ndds to Tcl Strings */
    fprintf (soutFile,"\tNULL, \n");						/* fromTclParam */
    fprintf (soutFile,"\tNULL \n");						/* toTclParam */

    fprintf (soutFile,"}; \n");

    fprintf (soutFile,"\n");

  /*status = fprintf (routFile, "    Tcl_CreateHashEntry (typeRegistry, \"%s\", (int *)&%sTypeDriver);\n", s, s);*/
    status = fprintf (routFile, "    hPtr = Tcl_CreateHashEntry (typeRegistry, \"%s\", &new);\n", s);
    status = fprintf (routFile, "    Tcl_SetHashValue (hPtr, &%sTypeDriver);\n", s);
    status = fprintf (routFile, "    %sTypeDriver.init();\n\n", s);

    if (0 > status) {
	perror ("unable to write Tcl_CreateHashEntry to typeRegistry file");
	exit (EXIT_FAILURE);
    }
#endif
    return;
}

/* C code to finish up the function calls for XDR structs */
void endStructFunction (char *s, int argcount) {
  fprintf (T2Nfile, "\n  return (count);\t/* # args used in this struct. */\n");
  fprintf (N2Tfile, "\n  return (1==1);\t/* Return TRUE for now. */\n");
  fprintf (T2Nfile, "} /* %s */\n\n", s);
  fprintf (N2Tfile, "} /* %s */\n\n\n", s);


  fprintf (houtFile, "#define %s_ArgCount %d\n", nddsType/*typeName*/, argcount);

  return;
}

/* merge_files brings together the temporary files that were used to
   help correctly order the output
*/
#define BUFLEN 256
void merge_files ( FILE *coutFile, FILE *houtFile )
{
  char buffer[BUFLEN], *buf;
 
  fclose ( T2Nfile);
  fclose ( N2Tfile);

  T2Nfile  = fopen (T2N_FILE_NAME, "r"); if (! T2Nfile) { perror("T2N C tmp file not opened" );  exit(EXIT_FAILURE);}
  N2Tfile  = fopen (N2T_FILE_NAME, "r"); if (! N2Tfile) { perror("N2T C tmp file not opened" );  exit(EXIT_FAILURE);}

  while ( (buf=fgets(buffer,BUFLEN, T2Nfile)) ) {fputs (buf,coutFile);}  fputs("\n",coutFile);
  while ( (buf=fgets(buffer,BUFLEN, N2Tfile)) ) {fputs (buf,coutFile);}

  fclose ( T2Nfile);
  fclose ( N2Tfile);
  fclose (coutFile);
  fclose (houtFile);

#if 0
  fprintf (routFile,"}\n");

  fclose (routFile);
  fclose (soutFile);
#endif

  remove (T2N_FILE_NAME);
  remove (N2T_FILE_NAME);

  return;
}

extern int errno;

/* Does a file exist? */
int fexist (char *fileName);
int fexist (char *fileName) {
    FILE *file;

    file = fopen (fileName, "r");  /* Open for reading, but don't create if no file */

    if (file) {
	fclose (file);
	return (TRUE);
    } else {
	/* See what the problem is. */
	if (ENOENT == errno) {	/* "No such file or directory" */
	    return(FALSE);	/* Okay... file just doesn't exist */
	}
    }
    /* Damn.  Got some other errno that means there is trouble afoot. */
    perror ("fexist check attemp trouble");
    exit (EXIT_FAILURE);

    return (FALSE);	/* NOT REACHED */
}



/* Open the files where we want to place all the C code */
void openOutputFiles (char *outFilePrefix)
{
    char  c_outFileName[256];
#if 0
    char *r_outFileName = "registry_tclndds.c";	/* Build up code to register all types.  Assumes multiple calls to tclndds */
    char *s_outFileName = "registry_tclndds.h";	/* Build up code to register all types.  Assumes multiple calls to tclndds */
    int previousRoutFile = fexist(r_outFileName);	/* We need to write stuff the first time */
#endif

    strcpy (c_outFileName, outFilePrefix);  strcat (c_outFileName, "_tclndds.c");
    strcpy (h_outFileName, outFilePrefix);  strcat (h_outFileName, "_tclndds.h");
    coutFile = fopen (c_outFileName, "w"); if (!coutFile) {perror("coutFile tmp file not opened");exit(EXIT_FAILURE);}
    houtFile = fopen (h_outFileName, "w"); if (!houtFile) {perror("houtFile tmp file not opened");exit(EXIT_FAILURE);}

#if 0
    soutFile = fopen (s_outFileName, "a"); if (!soutFile) {perror("registry_tclndds.h not opened");exit(EXIT_FAILURE);}
    fprintf (soutFile,"#include \"%s.h\"\n", outFilePrefix);	/* These are the 2 #includes needed in nddsWish.c */
    fprintf (soutFile,"#include \"%s\"\n",    h_outFileName);

    if (!previousRoutFile) {
	printf ("Creating new typeRegistry file.\n");
	routFile = fopen (r_outFileName, "a"); if (!routFile) {perror("routFile tmp file not opened");exit(EXIT_FAILURE);}
	fprintf (routFile, "void NddsWishRegisterAllTypes (void) {\n");
	fprintf (routFile, "    int new;\n");
	fprintf (routFile, "    Tcl_HashEntry *hPtr;\n\n");
	fprintf (routFile, "    Tcl_InitHashTable (typeRegistry, TCL_STRING_KEYS);\n\n");
    } else {
	/* typeRegistry file already exists.  So strip the "}\n" at the tail of the file */
	int problem;
	char c;

	/* r+ => open for update (reading and writing) */
	routFile = fopen (r_outFileName, "r+"); if (!routFile) {perror("routFile tmp file not opened");exit(EXIT_FAILURE);}

	problem = fseek (routFile, -2, SEEK_END);

	if (problem) {
	    perror ("Couldn't seek to (end - 2) of the existing typeRegistry file");
	    exit (EXIT_FAILURE);
	}

	c = fgetc (routFile);

	if ( '}' != c ) {
	    printf ("The end of the typeRegistry file should be a \"}\n\".");
	    printf ("WARNING: Assuming no '}' at the end of NddsWishRegisterAllTypes().\n");

	    /* Assume the user knows what they are doing.  Don't overwrite anything. */
	    problem = fseek (routFile, 0, SEEK_END);
	    if (problem) {
		perror ("Could not seek to end of existing typeRegistry file");
		exit (EXIT_FAILURE);
	    }
	} else {
	    /* Life is good so seek to the '}' to overwrite it */
	    /* Switching back and forth between input/output requires interviening fseek */
	    problem = fseek (routFile, -2, SEEK_END);
	}	
	
    }
#endif
    
    return;
}

int write_includes (FILE *coutFile,  char *nddsType, char *includeFileName, char *h_outFileName)
{
  fprintf (coutFile,"/* Standard includes needed... */\n");
  fprintf (coutFile,"#include <tcl.h>\n");
  fprintf (coutFile,"#include <string.h>\n");
  fprintf (coutFile,"#include <stdio.h>\n");
  fprintf (coutFile,"#include <string.h>\n");
  fprintf (coutFile,"#include <NDDS.h>\n");
  fprintf (coutFile,"\n");

/*fprintf (coutFile,"#include "nddswish.h"\n");*/
  fprintf (coutFile,"\n");

  strcpy (includeFileName,nddsType);
  strcat (includeFileName,".h");
  fprintf (coutFile,"#include \"%s\"\n", includeFileName);
  fprintf (coutFile,"#include \"%s\"\n", h_outFileName  );
  fprintf (coutFile,"\n");

  return (TRUE);
}

int
main(int argc, char *argv[]) {
    char includeFileName[256];
    int count;

    assert (rcs_id);

    T2Nfile = NULL;
    N2Tfile = NULL;

    inputFileName = NULL;
    archName = NULL;

    yydebug = 0;

    /* Parse the command line */
    if (argc<6) {
	fprintf(stderr,"ERROR: too few command line arguments\n");
	fprintf(stderr,"%s USAGE: <xdrFile> -nddstype <type> -typename <name>\n",argv[0]);
	exit(EXIT_FAILURE);
    }
    inputFileName = strdup (argv[1]);
    for (count=2; count < argc; count++) {
	/* FIX: Strange bailout if structure.  Could be handled much better! */
	if (0==strcasecmp(argv[count],"-nddstype")) {
	    count++;
	    if (count < argc) {
		nddsType = strdup(argv[count]);
		fprintf (stderr,"\tnddstype = %s\n", nddsType);
	    } else {printf ("ERROR: Argument expected for -nddstype flag.\n");exit(EXIT_FAILURE);}
	    continue;	/* Go to top of for loop */
	}
	if (0==strcasecmp(argv[count],"-typename")) {
	    count++;
	    if (count < argc) {
		typeName = strdup(argv[count]);
		fprintf (stderr,"\ttypename = %s\n",typeName);
	    } else {printf ("ERROR: Argument expected for -typename flag.\n");exit(EXIT_FAILURE);}
	    continue;	/* Go to top of for loop */
	}
	if (0==strcasecmp(argv[count],"-arch")) {
	    count++;
	    if (count < argc) {
		archName = strdup(argv[count]);
		fprintf (stderr,"\tarchname = %s\n",    archName);
	    } else {printf ("ERROR: Argument expected for -arch flag.\n");    exit(EXIT_FAILURE);}
	    continue;	/* Go to top of for loop */
	}
    }

    /* Did we get all the command line parameters we need? */
    if (!nddsType) {fprintf(stderr,"ERROR:   nddsType not specified.\n"); exit(EXIT_FAILURE);}
    if (!typeName) {fprintf(stderr,"ERROR:   typeName not specified.\n"); exit(EXIT_FAILURE);}
    if (!archName) {fprintf(stderr,"WARNING: archName not specified.\n"); archName =  "None";}

    openOutputFiles (nddsType);
    openTempFiles ();
    lexinit ();
    write_includes (coutFile,  nddsType, includeFileName, h_outFileName);

    yyin = fopen (inputFileName,"r"); /* Open the XDR .x file */

    if (!yyin) {
	perror("Could not open input file\n");
	exit (EXIT_FAILURE);
    }

    /* Parse the XDR file and do all the hard work. */
    if (0!=yyparse ()) {
	fprintf (stderr,"ERROR: Parse failed\n");
	exit(EXIT_FAILURE);
    }

    /* Mostly done, so now clean up */

    merge_files (coutFile, houtFile); /* Deal with the temporary files we built */

    fprintf (stderr, "\t%s: code successfully generated.\n", argv[0]);
    exit(EXIT_SUCCESS);
} /* main() */
