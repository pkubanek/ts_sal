/*
   Kurt Schwehr 7/96 -- XDR file parser for IMG

   604-6081, schwehr@cs.stanford.edu, schwehr@artemis.arc.nasa.gov

   BNF grammar from the IRIX Network Programming Guide
*/

%{ /* C code section */

#define YYERROR_VERBOSE 1
#define YYDEBUG 1

#ifdef OS_VXWORKS
  #include <vxWorks.h>
  #include <sysLib.h>
  #include <vme.h>
  #include <stdioLib.h>
#else /* anything that isn't vxWorks */
  #include <stdlib.h>	/* For malloc */
  #include <stdio.h>
#endif /* OS_VXWORKS */

#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "XDR.h"

static char rcs_id[] =
  "$Id: XDR.y,v 1.8 1998/07/16 16:37:30 mwagner Exp $";

#ifndef IRIX
void __yy_memcpy (char *to, char *from, int count);
#endif

static int argcount=0;

%} /* End C code section */

%start specification

%union          yystacktype
                {
		  void			*ptrval;
                  int            	intval;
                  double         	floatval;
                  char           	*stringval;
                  char           	charval;
		}

/* Reserved words */
%token	yBOOL      /*CASE*/ CONST   /* DEFAULT*/
%token	DOUBLE    /*ENUM*/ FLOAT   /* HYPER*/
%token	OPAQUE  STRING STRUCT  /* SWITCH */
%token	TYPEDEF   /*UNION*/UNSIGNED   yVOID

/* Things added by Kurt... not in IRIX specification */
%token	INT SHORT
%token	CONSTANT
%token  CHAR
%token	<stringval> IDENTIFIER
%token  <intval> INTCONST
%token	LONG

%type <stringval> type
%type <intval> optUnsigned

    /* -------------------------------------------------------------------- */
%%  /* ------------  Begin the rule section of the yacc/bison file -------- */
    /* -------------------------------------------------------------------- */
/* opt == optional */
specification	:	specification definition { assert (rcs_id); /* Avoid a warning */ }
		|	/* Empty */
		;
definition	:	type_def | constant_def ;

type_def	:	TYPEDEF decl        ';'
		|	STRUCT  IDENTIFIER  
			   { startStructFunction($2); argcount = 0; }
			       struct ';'
			   {   endStructFunction($2, argcount); }
		;

constant_def	:	CONST IDENTIFIER '=' CONSTANT ';' /* FIX: need code to handle constants for later use. */ ;

decl		:	type IDENTIFIER
			{
			  if ( 0 == strcmp ($1,"c") ) {
			      /* This is the ugly acception for the "char" type */
			      fprintf (T2Nfile,"  {\n    int num;\n    sscanf  (argv[count++], \"%%d\", &num);\n");
			      fprintf (T2Nfile,"    %s->%s = (char)num;\n  }\n", nddsObj, $2);
			      fprintf (N2Tfile,"  sprintf (tmpStr, \"%%d\", %s->%-10s);",        nddsObj, $2);
			  } else {
			      fprintf (T2Nfile,"  sscanf  (argv[count++], \"%%%s\", &%s->%-10s);\n", $1, nddsObj, $2);
			      fprintf (N2Tfile,"  sprintf (tmpStr, \"%%%s\", %s->%-10s);",        $1, nddsObj, $2);
			  }
			  fprintf (N2Tfile,"  newValue = Tcl_SetVar2 (interp, \"this\", \"%s\", tmpStr, TCL_LEAVE_ERR_MSG);\n",$2);
			  argcount++;
			}

                |       type IDENTIFIER '<' '>' 
			{
			  /* Variable sized arrays */
			  /* FIX: does not handle chars the same way as other types. */
			  fprintf (N2Tfile,"  for (i=0; i<%s->%s.%s_len; i++) {\n", nddsObj, $2, $2);
			  /* Space required after %s to make a list: */
			  if ( 0 == strcmp ($1,"c") ) {
			      /* This is the ugly acception for the "char" type */
			      fprintf (N2Tfile,"    sprintf (tmpStr, \"%%d \", %s->%s.%s_val[i]);\n",nddsObj,$2, $2);
			  } else {
			      fprintf (N2Tfile,"    sprintf (tmpStr, \"%%%s \", %s->%s.%s_val[i]);\n",$1,nddsObj,$2, $2);
			  }
			  fprintf (N2Tfile,"    newValue = Tcl_SetVar2 (interp, \"this\", \"%s\", ", $2);
			  fprintf (N2Tfile,"tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);\n");
			  fprintf (N2Tfile,"  }\n");


#if 0
			  fprintf (N2Tfile,"  for (i=0; i<%s->%s.%s_len; i++) {\n", nddsObj, $2, $2);
			  fprintf (N2Tfile,"    sprintf (tmpStr, \"%%%s\", %s->%s.%s_val[i]);\n",$1,nddsObj,$2,$2);
			  fprintf (N2Tfile,"    Tcl_DStringAppendElement (tclDStrPtr,tmpStr);\n");
			  fprintf (N2Tfile,"  }\n");
#endif
			  if ('c'==$1[0]) fprintf (N2Tfile,"    %s->%s.%s_val[i] = '\\0';\n", nddsObj, $2, $2);

			  fprintf (T2Nfile,"  for (i=0; i<%s->%s.%s_len; i++)\n", nddsObj, $2, $2);
			  fprintf (T2Nfile,"      sscanf(argv[count++],\"%%%s\",&(%s->%s.%s_val[i]));\n",$1,nddsObj,$2,$2);
			  if ('c'==$1[0]) fprintf (T2Nfile,"    %s->%s.%s_val[i] = '\\0';\n", nddsObj, $2, $2);
			  argcount++;
			}
                |       type IDENTIFIER '[' INTCONST ']' 	/* Fixed sized arrays */
			{
			  fprintf (N2Tfile,"  for (i=0; i<%d; i++) {\n", $4);
			  /* Space required after %s to make a list: */
			  if ( 0 == strcmp ($1,"c") ) {
			      /* This is the ugly acception for the "char" type */
			      fprintf (N2Tfile,"    sprintf (tmpStr, \"%%d \", %s->%s[i]);\n",nddsObj,$2);
			  } else {
			      fprintf (N2Tfile,"    sprintf (tmpStr, \"%%%s \", %s->%s[i]);\n",$1,nddsObj,$2);
			  }
			  fprintf (N2Tfile,"    newValue = Tcl_SetVar2 (interp, \"this\", \"%s\", ", $2);
			  fprintf (N2Tfile,"tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);\n");
			  fprintf (N2Tfile,"  }\n");
#if 0
			  fprintf (N2Tfile,"  for (i=0; i<%d; i++) {\n", $4);
			  fprintf (N2Tfile,"    sprintf (tmpStr, \"%%%s\", %s->%s[i]);\n",$1,nddsObj,$2);
			  fprintf (N2Tfile,"    Tcl_DStringAppendElement (tclDStrPtr,tmpStr);\n");
			  fprintf (N2Tfile,"  }\n");
#endif


			  /* Finish off an array of characters (string) */
			  /* FIX: Is this really necessary?  -Kurt */
			  /*if ('c'==$1[0]) fprintf (N2Tfile,"    %s->%s[i] = '\\0';\n", nddsObj, $2);*/

			  /* fixed length  (char[x]) are special */
			  if ('c'==$1[0]) {
			      /* \0 provided by user: */
			      fprintf (T2Nfile,"  strcpy  (%s->%-10s , argv[count++]);\n",nddsObj,$2);
			      argcount ++;	/* Only one argument. */ 
			  } else {
			      fprintf (T2Nfile,"  for (i=0; i<%d; i++)\n", $4);
			      fprintf (T2Nfile,"      sscanf(argv[count++],\"%%%s\",&(%s->%s[i]));\n",$1,nddsObj,$2);
			      argcount += $4;
			  }
			}
		|	STRING IDENTIFIER '<' '>' 
			{
			  /* Strings become (char *) */

			  fprintf (N2Tfile,"  sprintf (tmpStr, \"%%s\", %s->%-10s);",nddsObj,$2);
			  fprintf (N2Tfile,"    newValue = Tcl_SetVar2 (interp, \"this\", \"%s\", ", $2);
			  fprintf (N2Tfile,"tmpStr,TCL_APPEND_VALUE | TCL_LEAVE_ERR_MSG);\n");
			  fprintf (T2Nfile,"  strcpy  (%s->%-10s , argv[count++]);\n",nddsObj,$2);
#if 0
			  fprintf (N2Tfile,"  sprintf (tmpStr, \"%%s\", %s->%-10s);",nddsObj,$2);
			  fprintf (N2Tfile,"  Tcl_DStringAppendElement (tclDStrPtr,tmpStr); \n");
			  fprintf (T2Nfile,"  strcpy  (%s->%-10s , argv[count++]);\n",nddsObj,$2);
#endif
			  argcount++;
			}
		|	yVOID
		;
type		:	optUnsigned LONG	{  $$ = ( $1 /*unsigned*/)?"ld":"ld"; }
		|	optUnsigned INT		{  $$ = ( $1 /*unsigned*/)? "u": "d"; }
		|	optUnsigned SHORT	{  $$ = ( $1 /*unsigned*/)?"hu":"hd"; }
		|	FLOAT	{  $$ = "f"; }
		|	DOUBLE	{  $$ = "lf"; }
		|	yBOOL	{  $$ = "d"; }
		|	OPAQUE	{  $$ = "c"; }	/* OPAQUES are just packed chars right now. Take less space than char */
				/* WARNING: char changed from 'c' to 'd'.  Tcl is not great with strings */
				/* WARNING: there might be a better way to handle this. */
		|	optUnsigned CHAR	{  $$ = ( $1 /*unsigned*/)? "c": "c"; }  /* FIX: deal with unsigned? */
		|	struct	{  $$ = "?"; printf (" lookupStruct()->FIX:not implimented\n"); }
		;
struct		:	'{'  declList            '}' ;
declList	:	declList decl ';'
		|	         decl ';'
		;
optUnsigned     :       UNSIGNED { $$ = TRUE;} | /* Empty */ { $$ = FALSE; } ;
%%
/* C code section */
