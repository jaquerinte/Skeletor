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



void msgError(int nerror,int nlin,int ncol,const char *s);