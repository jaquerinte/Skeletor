typedef struct {
   char *lexeme;
   int nlin,ncol;
   string trad;
   string ph;
} BASETYPE;

#define YYSTYPE BASETYPE

#define ERRLEXIC        1
#define ERRSINT         2
#define ERREOF          3

#define ERRNODEC        4 // ERROR Var not declared 
#define ERRALDEC        5 // ERROR Var already declared
#define ERRFUNODEC      6 // ERROR Module not declared
#define ERRFUNALDEC     7 // ERROR Module already declared



void msgError(int nerror,int nlin,int ncol,const char *s);