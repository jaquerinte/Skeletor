typedef struct {
   char *lexeme;
   int nlin,ncol;
   string trad;
   string ph;
   int size;

} BASETYPE;

#define YYSTYPE BASETYPE

#define ERRLEXIC        1
#define ERRSINT         2
#define ERREOF          3

/* GENERAL ERRORS */
#define ERRNODEC        4 // ERROR Var not declared 
#define ERRALDEC        5 // ERROR Var already declared
#define ERRFUNODEC      6 // ERROR Module not declared
#define ERRFUNALDEC     7 // ERROR Module already declared

/* MODULE ERRORS */
#define ERRCONNDEC     20 // ERROR Connection already declared
#define ERRCONNNODEC   21 // ERROR Connection not declared
#define ERRPARAMDEC    22 // ERROR Param module already declared
#define ERRPARAMNODEC  23 // ERROR param no declared

/* MODULE DEFINTION ERORS */
#define ERRFUNCDEFALDEC  50  // ERROR Function module definition already define
#define ERRDESCDEFALDEC  51  // ERROR Description module definition already define
#define ERRORCODDEFALDEC 52  // ERROR Coder module definition already define
#define ERRORDEFIALDEC   52  // ERROR References module definition already define

void msgError(int nerror,int nlin,int ncol,const char *s);