typedef struct {
   char *lexema;
   int nlin,ncol;
   string trad;
   string ph;
   int tipo;
   int dir;
   int size;
} MYTYPE;

#define YYSTYPE MYTYPE

#define ERRLEXICO       1
#define ERRSINT         2
#define ERREOF          3

#define ERRYADECL       4
#define ERRNODECL       5
#define ERRDIM          6
#define ERRFALTAN       7
#define ERRSOBRAN       8
#define ERR_EXP_ENT     9
#define ERR_EXP_LOG    10
#define ERR_EXDER_LOG  11
#define ERR_EXDER_ENT  12
#define ERR_EXDER_RE   13
#define ERR_EXIZQ_LOG  14
#define ERR_EXIZQ_RE   15

#define ERR_NOCABE     16
#define ERR_MAXVAR     17
#define ERR_MAXTIPOS   18
#define ERR_MAXTMP     19

void msgError(int nerror,int nlin,int ncol,const char *s);