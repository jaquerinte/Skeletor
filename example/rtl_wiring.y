%token id ninteger nfloat amp blockdefinition
%token opas parl parr pyc coma oprel opmd opasig bral loopfor
%token brar cbl cbr ybool obool nobool opasinc

%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

#include "common.h"

// variables y funciones del A. Léxico
extern int ncol,nlin,findefichero;

extern int yylex();
extern char *yytext;
extern FILE *yyin;

int yyerror(char *s);

%}
%%

SA		: S 	
		{ 
			int tk = yylex();
			if (tk != 0) yyerror("");
			cout << $1.trad << endl; 
		}
	;

Factor   	: id {string pme = $1.lexema; $$.trad = pme;}
			| ninteger {string pme = $1.lexema; $$.trad = pme;}
			| nfloat {string pme = $1.lexema; $$.trad = pme;}
	;
Instr 		: Factor pyc {$$.trad = $1.trad + ":\n";}
			| Func {$$.trad = $1.trad + "\n";}
			| /*epsilon*/ { } 
	;

SInstr		: SInstr Instr {$$.trad = $1.trad + $2.trad;}
			| Instr {$$.trad = $1.trad;}

	;

Block		: cbl SInstr cbr {$$.trad = "¿\n" + $2.trad + "?";}
	;

SAFuncargs	: coma id SAFuncargs {string pme = $2.lexema;$$.trad = "|" + pme + $3.trad;}
			| /*epsilon*/ { } 
	;
SFuncargs 	: id SAFuncargs {string pme = $1.lexema;$$.trad = pme + $2.trad;}
	;
Funcargs	: SFuncargs {$$.trad = $1.trad;}
			| /*epsilon*/ { } 
	;
Func 		: blockdefinition id parl Funcargs parr Block {string pme = $2.lexema;$$.trad = "MODULE " + pme + "(" + $4.trad + ")" + $6.trad ;}
	;
S  			: Func {$$.trad = $1.trad;}
	;

%%

void msgError(int nerror,int nlin,int ncol,const char *s)
{
     if (nerror != ERREOF)
     {
        fprintf(stderr,"Error %d (%d:%d) ",nerror,nlin,ncol);
        switch (nerror) {
         case ERRLEXICO: fprintf(stderr,"caracter '%s' incorrecto\n",s);
            break;
         case ERRSINT: fprintf(stderr,"en '%s'\n",s);
            break;
         case ERRYADECL: fprintf(stderr,"variable '%s' ya declarada\n",s); // done
            break;
         case ERRNODECL: fprintf(stderr,"variable '%s' no declarada\n",s); // done
            break;
         case ERRDIM: fprintf(stderr,"la dimension debe ser mayor que cero\n");
            break;
         case ERRFALTAN: fprintf(stderr,"faltan indices\n");
            break;
         case ERRSOBRAN: fprintf(stderr,"sobran indices\n");
            break;
         case ERR_EXP_ENT: fprintf(stderr,"la expresion entre corchetes debe ser de tipo entero\n"); // done
            break;
         case ERR_EXP_LOG: fprintf(stderr,"la expresion debe ser de tipo logico\n");
            break;
         case ERR_EXDER_LOG: fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo logico\n",s);
            break;
         case ERR_EXDER_ENT: fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo entero\n",s);
            break;
         case ERR_EXDER_RE:fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo real o entero\n",s); // 1 com
            break;        
         case ERR_EXIZQ_LOG:fprintf(stderr,"la expresion a la izquierda de '%s' debe ser de tipo logico\n",s);
            break;       
         case ERR_EXIZQ_RE:fprintf(stderr,"la expresion a la izquierda de '%s' debe ser de tipo real o entero\n",s);
            break;       
         case ERR_NOCABE:fprintf(stderr,"la variable '%s' ya no cabe en memoria\n",s); // done
            break;
         case ERR_MAXVAR:fprintf(stderr,"en la variable '%s', hay demasiadas variables declaradas\n",s); // ?
            break;
         case ERR_MAXTIPOS:fprintf(stderr,"hay demasiados tipos definidos\n"); // ?
            break;
         case ERR_MAXTMP:fprintf(stderr,"no hay espacio para variables temporales\n"); // done
            break;
        }
     }
     else
        fprintf(stderr,"Error al final del fichero\n");
     exit(1);
}


int yyerror(char *s)
{
    extern int findefichero;   //  variable definida en plp5.l que indica si
                               // se ha acabado el fichero
    if (findefichero) 
    {
       msgError(ERREOF,-1,-1,"");
    }
    else
    {  
       msgError(ERRSINT,nlin,ncol-strlen(yytext),yytext);
    }
}

int main(int argc,char *argv[])
{
    FILE *fent;

    if (argc==2)
    {
        fent = fopen(argv[1],"rt");
        if (fent)
        {
            yyin = fent;
            yyparse();
            fclose(fent);
        }
        else
            fprintf(stderr,"No puedo abrir el fichero\n");
    }
    else
        fprintf(stderr,"Uso: ejemplo <nombre de fichero>\n");
}