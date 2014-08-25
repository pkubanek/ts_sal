/*
   structure to flexibly add NDDS data types into Tcl/Tk
   Dan Christian	7-96
   Kurt Schwehr		8-96
*/

#ifndef _NDDSTCL_H_
#define _NDDSTCL_H_

 typedef void (*NDDS_REGISTER_HANDLER)	(void);

 typedef void *(*NDDS_ALLOCATE_HANDLER)	(const char *type, const char *name, void *param);

 typedef void (*NDDS_FREE_HANDLER)	(void *object, const char *type, const char *name, void *param);

 typedef int  (*NDDS_FROM_TCL_HANDLER)	(void *object, int argc, char *argv[] /*, void *param*/);

 typedef int  (*NDDS_TO_TCL_HANDLER)	(void *object, Tcl_Interp *interp);

typedef struct _NDDS_TYPE_DRIVER {
    char			*type;		/* name of this type */
    NDDS_REGISTER_HANDLER	init; 		/* register type (needed?) */
    NDDS_ALLOCATE_HANDLER	allocate;	/* allocate storage */
    NDDS_FREE_HANDLER		free;		/* free storage */
    NDDS_FROM_TCL_HANDLER	fromTcl;	/* fill in structure from argc, argv*/
    NDDS_TO_TCL_HANDLER		toTcl;		/* print structure into Dstring */


    /* These 2 probably won't be needed */
    void			*fromTclParam;	/* parameter for fromTcl */
    void			*  toTclParam;	/* parameter for toTcl */
} NDDS_TYPE_DRIVER;



void nddsWishRegisterAllTypes(void);

extern int debug_level;
#define TRACE 4			/* trace mode... when you want a large amount of info */
#ifdef NDEBUG
#   define NddsDebug(n,s)                   /* expand to nothing */
#else
#   define NddsDebug(n,s)   (((n) <= debug_level) ?  printf s :0)
#endif

#endif /* _NDDSTCL_H_ */
