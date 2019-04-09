%token id ninteger amp moduledefinition intype inttype outtype inouttype definevalue
%token opas parl parr pyc coma oprel opmd opasig bral
%token brar cbl cbr ybool obool nobool opasinc definevalue


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
extern int ncol,nlin,endfile;

/* START FUNCTIONS */
const int INTEGER=1;
const int LOGIC=2;

struct Type {
	int type;
	int size;
	int baseType;
};

struct TableTypes {
	vector<Type> v_types;

	string debugTTypes() {
		string tt_content("");
		tt_content += ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		tt_content += "; TableTypes\n";
		tt_content += ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		for (int i = 0; i < v_tipos.size(); ++i) {
			tt_content += "; type:" + to_string(v_tipos.at(i).type) + " tam:" + to_string(v_tipos.at(i).size) 
						+ " baseType:" + to_string(v_tipos.at(i).baseType) + "\n";
		}
		tt_content += ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		return tt_content;
	}
	void add_primitivetype(int ttype, int tsize,int tbase) {		
		Type t;
		t.type = ttype;
		t.size = tsize;
		t.baseType = tbase;
		v_tipos.push_back(t);
   	}

}

/* END FUNCTIONS */
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
/* Base syntax */
SSuperblock : SSuperblock definevalue {$$.trad = $1.trad + $2.trad;}
			| definevalue {$$.trad = $1.trad;}
			| /*epsilon*/ { } 
	;
/* Function agrupation*/
SFunc 		: SFunc Func {$$.trad = $1.trad + $2.trad;}
			| Func {$$.trad = $1.trad;}
			| /*epsilon*/ { } 
	;
/* Function */
Func 		: moduledefinition id parl SArgs parr Block {string pme = $2.lexema; $$.trad = pme + " (" + $4.trad + ")" + $6.trad;}
	;
/* Function args */
SArgs 		: SAArgs TipoBase id {string pme = $3.lexema; $.trad = $1.trad + $2.trad + pme;}
			| /*epsilon*/ { } 
	;
SAArgs 		: TipoBase id coma SAArgs {string pme = $2.lexema; $.trad = $1.trad + pme + "," +$4.trad;}
			|/*epsilon*/ { } 
	;
/* Block definition and instructions base  */
Block 		: cbl SInstr cbr  {$$.trad = "{" + $2.trad + "}";}
	;
SInstr		: SInstr Instr {$$.trad = $1.trad + $2.trad;}
			| Instr  	   {$$.trad = $1.trad;}
	;
/* Instruction definition  */
Instr 		: EInstr pyc {$$.trad = $1.trad + ";"}
	;
EInstr 		: Ref opasig SExpr {$$.trad = $1.trad + " = " + $3.trad;}
			: TipoBase id      {string pme = $2.lexema; $$.trad = $1.trad + pme;}
	;
/* Tipos */
TipoBase 	: int {string pme = $1.lexema $$.trad = pme;}

S 		: SSuperblock SFunc {$$.trad = $1.trad + $2.trad;}
	;

%%

void msgError(int nerror,int nlin,int ncol,const char *s)
{
     if (nerror != ERREOF)
     {
        fprintf(stderr,"Error %d (%d:%d) ",nerror,nlin,ncol);
        switch (nerror) {
         case ERRLEXICO: fprintf(stderr,"character '%s' not correct\n",s);
            break;
         case ERRSINT: fprintf(stderr,"in '%s'\n",s);
            break;
        }
     }
     else
        fprintf(stderr,"Error in end of file\n");
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
            fprintf(stderr,"File can not open\n");
    }
    else
        fprintf(stderr,"Use: example <filename>\n");
}