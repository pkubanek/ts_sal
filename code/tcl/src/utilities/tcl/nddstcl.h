/* structure to flexibly add NDDS data types into Tcl/Tk */
/* Dan Christian	7-96 */

#ifndef _NDDSTCL_H_
#define _NDDSTCL_H_

typedef void (*NDDS_REGISTER_HANDLER)(void);
typedef void (*NDDS_ALLOCATE_HANDLER)(const char *type, const char *name,
				      void *param);
typedef void (*NDDS_FREE_HANDLER)(void *object,
				  const char *type, const char *name,
				  void *param);
typedef void (*NDDS_FROM_TCL_HANDLER)(void *object, int argc, char *argv[],
				      void *param);

/*typedef void (*NDDS_TO_TCL_HANDLER)(void *object, Tcl_DString *out, void *param);*/
 typedef void (*NDDS_TO_TCL_HANDLER)(void *object, Tcl_Interp *interp, void *param);

typedef struct _NDDS_TYPE_DRIVER {
    char			*type;	/* name of this type */
    NDDS_REGISTER_HANDLER	init; /* register type (needed?) */
    NDDS_ALLOCATE_HANDLER	allocate; /* allocate storage */
    NDDS_FREE_HANDLER		free;	/* free storage */
    NDDS_FROM_TCL_HANDLER	fromTcl; /* fill in structure from argc, argv*/
    void			*fromTclParam; /* parameter for fromTcl */
    NDDS_TO_TCL_HANDLER		toTcl; /* print structure into Dstring */
    void			*toTclParam; /* parameter for toTcl */
} NDDS_TYPE_DRIVER;

#endif /* _NDDSTCL_H_ */
