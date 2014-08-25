/* Kurt Schwehr - schwehr@artemis.arc.nasa.gov - 7/96 */

#ifndef __XDR_H_
#define __XDR_H_

int  main	(int argc, char *argv[]);
void lexinit	(void);
int  yylex   (void);
int  yyparse (void);
void yyerror (const char *s);	/* Defined in lex.c */

void startStructFunction (char *s);
void   endStructFunction (char *s, int argcount);

#define nddsObj "nddsObj"
#define T2N_FILE_NAME "T2N.c.tmp~"
#define N2T_FILE_NAME "N2T.c.tmp~"

#ifndef TRUE
#define TRUE (1==1)
#endif

#ifndef FALSE
#define FALSE (1!=1)
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE      1
#endif
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS      0
#endif

/*** UNHAPPY GLOBAL VARIABLES :( ***/
extern int yydebug;
extern int yylineno;	/* Created for XDR.  Not declared by bison or flex */

extern FILE *T2Nfile;
extern FILE *N2Tfile;

extern FILE *houtFile;

extern FILE *yyin;

#endif /* __XDR_H_ */
