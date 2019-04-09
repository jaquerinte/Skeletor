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
		v_types.push_back(t);
   	}

   	int registerType(int tsize,int tbase) {
   		int _type = v_types.at(v_types.size() - 1).type + 1;
		Tipo t;
		t.type = _type;
		t.size = tsize;
		t.baseType = tbase;
		v_types.push_back(t);
		return _type;
   	}
   	Type search(int type) {
		Tipo t;
		t.type = -1;
		t.baseType = -1;
		t.size = -1;
				
		for (int i = 0; i < v_tipos.size(); ++i) {
			if (v_types.at(i).type == type) {
				return v_types.at(i);
			}
		}
		return t;
	}
	int getTotalSize(int type){
		int auxType = type; 
		int size = 1;
		while (auxType >= LOGICO){
			size = size * getSize(auxType);
			auxType = baseType(auxType);
		}
		return size;
	}

	int getSizeBaseType(int type) {
		int bt(baseType(type));
		return getSize(bt);
	}

	int getSize(int type) {		
		for (int i = 0; i < v_types.size(); ++i) {
			if (v_types.at(i).type == type) {
				return v_types.at(i).size;
			}
		}
		return -1;
	}

	int baseType(int type) {
		for (int i = 0; i < v_types.size(); ++i) {
			if (v_types.at(i).type == type) {
				return v_types.at(i).baseType;
			}
		}
		return -1;
	}
	
	bool isBase(int type) {
		for (int i = 0; i < v_types.size(); ++i) {
			if (v_types.at(i).type == type) {
				if (v_types.at(i).baseType == 0) {
					return true;
				} else {
					return false;
				}
			}
		}
		return false;
	}

	bool isArray(int _type) {
		return _type > LOGICO; 
	}

};

/* Tabla Types */
TableTypes tt;
/* Tabla Types */

struct Symbol {
	int type;
	string name;
	int value;
};

struct TableSymbols {
	vector<Simbolo> v_symbols;

	string debugTSymbols() {
		string ts_content("");
		ts_content += "; TableSymbols\n";
		ts_content += ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		for (int i = 0; i < v_simbolos.size();++i) {
			ts_content += "; type:" + to_string(v_simbolos.at(i).type) + " nombre:" + v_simbolos.at(i).name + "\n";
		}
		ts_content += ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		return ts_content;
	}

};

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
string init_output(){
	string output = "//////////////////////////////////////////\n";
		  output += "//                                        \n";
		  output += "//                  `....``               \n";
		  output += "//           -/shmNNNmmNNNmdy+:`          \n";
		  output += "//       `/yNNMMdo:.`````-/yNMMNh+.       \n";
		  output += "//     `omMMMMh-`           `oNMMMNy-     \n";
		  output += "//    :mMMMMM+                -mMMMMNs`   \n";
		  output += "//   /NMMMMM+                  .NMMMMMy   \n";
		  output += "//  .NMMMMMh                    /MMMMMMo  \n";
		  output += "//  sMMMMMM:                     dMMMMMN  \n";
		  output += "//  dMMMMMM                      sMMMMMM. \n";
		  output += "//  dMMMMMN                      oMMMMMM. \n";
		  output += "//  oMMMMMM`                     yMMMMMN  \n";
		  output += "//  `NMMMMM/                    `NMMMMM+  \n";
		  output += "//   :NMMMMm`                   sMMMMMy   \n";
		  output += "//    :mMMMMh`                 +MMMMNo    \n";
		  output += "//     `omMMMd:`             .sMMMNy-     \n";
		  output += "//`-     `/ymNMd+.        `/yNMNh+.     `.\n";
		  output += "//.N:`      `-/hMN        sMm+:.      `.hs\n";
		  output += "//.MMdysooooooosMM.       hMmooooooosyhNMo\n";
		  output += "//`MMMMMMMMMMMMMMM:       NMMMMMMMMMMMMMMo\n";
		  output += "// NNNNNNNNNNNNNNN/       NNNNNNNNNNNNNNN+\n";
		  output += "// `..............        ............... \n";
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