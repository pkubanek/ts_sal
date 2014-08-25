typedef union          yystacktype
                {
		  void			*ptrval;
                  int            	intval;
                  double         	floatval;
                  char           	*stringval;
                  char           	charval;
		} YYSTYPE;
#define	yBOOL	258
#define	CONST	259
#define	DOUBLE	260
#define	FLOAT	261
#define	OPAQUE	262
#define	STRING	263
#define	STRUCT	264
#define	TYPEDEF	265
#define	UNSIGNED	266
#define	yVOID	267
#define	INT	268
#define	SHORT	269
#define	CONSTANT	270
#define	CHAR	271
#define	IDENTIFIER	272
#define	INTCONST	273
#define	LONG	274


extern YYSTYPE yylval;
