%token id ninteger amp moduledefinition intype inttype outtype inouttype definevalue wiretipe
%token opas parl parr pyc coma oprel opmd opasig bral connectwire nyooperator stringtext
%token brar cbl cbr ybool obool nobool opasinc twopoints mainmodule booltokentrue
%token functionmodule descriptionmodule codermodule referencesmodule booltoken booltokenfalse


%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

#include "common.h"
#include "./objects/TableFunctionSymbols.h"

/* Return messages */
#define CORRECT_EXECUTION 0
#define WRONG_ARGUMENTS 1

// variables y funciones del A. Léxico
extern int ncol,nlin,endfile;

/* START FUNCTIONS */
const int INTEGER=1;
const int REGISTER=2;
const int STRING=3;
const int LOGIC=5;

/* Global project Name */
string projectName = "a.out";
string projectFolder = "OUTPUT";
string init_output();

struct Type {
	int type;
	int size;
	int baseType;
};

struct TableTypes {
	vector<Type> v_types;

	string debugTTypes() {
		string tt_content("");
		tt_content += "////////////////////////////////////////////////////////////////////////////////\n";
		tt_content += "// TableTypes\n";
		tt_content += "////////////////////////////////////////////////////////////////////////////////\n";
		for (int i = 0; i < v_types.size(); ++i) {
			tt_content += "// type:" + to_string(v_types.at(i).type) + " tam:" + to_string(v_types.at(i).size) 
						+ " baseType:" + to_string(v_types.at(i).baseType) + "\n";
		}
		tt_content += "////////////////////////////////////////////////////////////////////////////////\n";
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
		Type t;
		t.type = _type;
		t.size = tsize;
		t.baseType = tbase;
		v_types.push_back(t);
		return _type;
   	}
   	Type search(int type) {
		Type t;
		t.type = -1;
		t.baseType = -1;
		t.size = -1;
				
		for (int i = 0; i < v_types.size(); ++i) {
			if (v_types.at(i).type == type) {
				return v_types.at(i);
			}
		}
		return t;
	}
	int getTotalSize(int type){
		int auxType = type; 
		int size = 1;
		while (auxType >= LOGIC){
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
		return _type > LOGIC; 
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
	vector<Symbol> v_symbols;
	int lastLabel;

	string debugTSymbols() {
		string ts_content("");
		ts_content += "// TableSymbols\n";
		ts_content += "////////////////////////////////////////////////////////////////////////////////\n";
		for (int i = 0; i < v_symbols.size();++i) {
			ts_content += "// type:" + to_string(v_symbols.at(i).type) + " name:" + v_symbols.at(i).name + " value:" + to_string(v_symbols.at(i).value)+ "\n";
		}
		ts_content += "////////////////////////////////////////////////////////////////////////////////\n";
		return ts_content;
	}
	bool addSymbol(string name, int type){
		Symbol s;
		s.type = type;
		s.name = name;
		for (int i = 0; i < v_symbols.size();++i) {
			if (v_symbols.at(i).name == s.name) { 
				// fail: var ya decl
				msgError(ERRALDEC, nlin, ncol - name.length(), name.c_str());
				return false;
			}
		}
		v_symbols.push_back(s);
		return true;
	}
	Symbol searchSymbol(string name) {
		Symbol s;
		s.type = -1;
		s.value = -1;
		s.name = "null";
		for (int i = 0; i < v_symbols.size();++i) {
			if (v_symbols.at(i).name == name) {
				return v_symbols.at(i);
			}
		}
		// fail: var no decl
		msgError(ERRNODEC, nlin, ncol - name.length(), name.c_str());
		return s;
	}
};

/* Table Symbols */
TableSymbols ts;
/* Table Symbols */

/* Table Symbols */
TableFunctionSymbols tfs;
/* Table Symbols */

/* END FUNCTIONS */
/*Global Helpers*/
extern int yylex();
extern char *yytext;
extern FILE *yyin;

string s1;

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
ModuleTextDefinition : stringtext { string pme = $1.lexeme; $$.trad = pme;}
				     | Ref {$$.trad = $1.trad;}
	;

ValueDefinition : ninteger  {string pme = $1.lexeme; $$.trad = pme; $$.size = INTEGER;}
				| booltoken {string pme = $1.lexeme; $$.trad = pme; $$.size = LOGIC;}
				| stringtext{string pme = $1.lexeme; $$.trad = pme; $$.size = STRING;}
	;
SSuperblock : SSuperblock definevalue id ValueDefinition {$$.trad = "";}
			| definevalue id {string pme = $2.lexeme; $0.ph = pme;} ValueDefinition{$$.trad = $1.trad;}
			| /*epsilon*/ { } 
	;
/* Function agrupation*/
SSAFunc     : SSAFunc Func {$$.trad = $1.trad + $2.trad;}
			| Func {$$.trad = $1.trad;}
	;
SAFunc      : SSAFunc MainFunc {$$.trad = $1.trad + $2.trad;}
	;
/* Function */
Func 		: moduledefinition id 
			{
				/*Add module*/
				string pme = $2.lexeme;
				tfs.addFunctionSymbol(pme, projectName, projectFolder);
				s1 = pme;
				//printf("%s", s1);
			} 
			parl SArgs parr  Block 
			{
				/* Create file for module*/
				s1 = "null";
				string pme = $2.lexeme;
				int pos = tfs.searchFunctionSymbol(pme);
				tfs.v_funcSymbols.at(pos).createFileModule();

			}
	;
MainFunc    : moduledefinition mainmodule id
			{
				/*Add module*/
				string pme = $3.lexeme;
				tfs.addFunctionSymbol(pme, projectName, projectFolder);
				int pos = tfs.searchFunctionSymbol(pme);
				s1 = pme;
			}  parl SArgs parr Block
			{
				/* Create file for module*/
				s1 = "null";
				string pme = $3.lexeme;
				int pos = tfs.searchFunctionSymbol(pme);
				string base = init_output();
				tfs.v_funcSymbols.at(pos).createFileModule(base);

			}
	;
/* Function args */
SArgs       : DArgs {$$.trad = "";}
/*SArgs 		: { id SAArgs
			{	
				string pme = $3.lexeme;
				FunctionSymbol s;
				if($0.ph != "null"){
					s = tfs.searchFunctionSymbol($0.ph);
					s.addFunctionSymbolParam(pme);

				}
			}*/
			| /*epsilon*/ { } 
	;
DArgs       :  id SArBlock SAArgs {
					string pme = $1.lexeme;
				    
				    //printf("%s", s1);
				    if(s1 != "null"){
				    	int pos  = tfs.searchFunctionSymbol(s1);
				    	tfs.v_funcSymbols.at(pos).addFunctionSymbolParam(pme);
				    }
				}
	;
SAArgs 		:  coma id SArBlock SAArgs 
				{
					string pme = $2.lexeme;
				    FunctionSymbol s;//not used can be removed
				    if(s1 != "null"){
				    	int pos  = tfs.searchFunctionSymbol(s1);
				    	tfs.v_funcSymbols.at(pos).addFunctionSymbolParam(pme);
				    }
				}
			|/*epsilon*/ { } 
	;
SArBlock    : opasig id {string pme = $2.lexeme; $$.trad = pme;}
			| /*epsilon*/ { $$.trad = "";} 
	;
/* Block definition and instructions base  */
Block 		: cbl SInstr cbr  {$$.trad = $2.trad;}
	;
SInstr		: SInstr Instr {$$.trad = $1.trad + $2.trad;}
			| Instr  	   {$$.trad = $1.trad;}
	;
/* Instruction definition  */
Instr 		: EInstr pyc {$$.trad = $1.trad + ";";}
			| functionmodule ModuleTextDefinition 
				{
					int pos;
					if(s1 != "null"){
				    	pos = tfs.searchFunctionSymbol(s1);
				    	if (tfs.v_funcSymbols.at(pos).getFunction() == ""){
				    		tfs.v_funcSymbols.at(pos).setFunction($2.trad);
				    	}else{
				    		// fail: functionmodule Olreeady defing
				    		string pme = $1.lexeme;
							msgError(ERRFUNODEC, nlin, ncol, pme.c_str());
				    	}
						
				    }
				}
			| descriptionmodule ModuleTextDefinition {
					int pos;
					if(s1 != "null"){
				    	pos = tfs.searchFunctionSymbol(s1);
						if (tfs.v_funcSymbols.at(pos).getDescription() == ""){
				    		tfs.v_funcSymbols.at(pos).setDescription($2.trad);
				    	}else{
				    		// fail: functionmodule Olreeady defing
				    		string pme = $1.lexeme;
							msgError(ERRDESCDEFALDEC, nlin, ncol, pme.c_str());
				    	}
				    }
				}
			| codermodule ModuleTextDefinition {
				    int pos;
					if(s1 != "null"){
				    	pos = tfs.searchFunctionSymbol(s1);
						if (tfs.v_funcSymbols.at(pos).getCode() == ""){
				    		tfs.v_funcSymbols.at(pos).setCode($2.trad);
				    	}else{
				    		// fail: functionmodule Olreeady defing
				    		string pme = $1.lexeme;
							msgError(ERRORCODDEFALDEC, nlin, ncol, pme.c_str());
				    	}
				    }
				}
			| referencesmodule ModuleTextDefinition {
					if(s1 != "null"){
						int pos;
				    	pos = tfs.searchFunctionSymbol(s1);
						if (tfs.v_funcSymbols.at(pos).getReferences() == ""){
				    		tfs.v_funcSymbols.at(pos).setReferences($2.trad);
				    	}else{
				    		// fail: functionmodule Olreeady defing
				    		string pme = $1.lexeme;
							msgError(ERRORDEFIALDEC, nlin, ncol, pme.c_str());
				    	}
				    }
				}
			| intype id pyc { }
			/*| inttype id pyc {
				FunctionSymbol s;
				if(s1 != "null"){
					    string pme = $2.lexeme;
						s = tfs.searchFunctionSymbol(s1);
						string a = "";
						s.addConnectionFunctionSymbol(pme, IN,"");
					}
				}*/
			|/*epsilon*/ { } 

	;
EInstr 		: Ref opasig Expr {$$.trad = $1.trad + " = " + $3.trad;}
			| TipoBase id      {
								string pme = $2.lexeme; 
								$$.trad = $1.trad + pme;
								int pos = tfs.searchFunctionSymbol(s1);
								InoutSymbol con (pme ,$1.size,"");
								tfs.v_funcSymbols.at(pos).addConnectionFunctionSymbol(con);
								}
	;
/*InstrINOUT  : id {string pme = $1.lexeme; $$.trad = pme; $$.size = 0;}
			| bral Expr twopoints Expr brar id {string pme = $6.lexeme; $$.trad = pme; $$.size = 0;}*/
	;
/* Expresion */
Expr	:	Econj {} 
		|	Expr obool Econj{}
	;
Econj	:	Ecomp {}
		|	Econj ybool Ecomp {}
	;

Ecomp 	: Esimple {}
		| Esimple oprel	Esimple {}
	;
Esimple	:	opas Term {}
		|	Term {}
		|	Esimple opas Term {}
	;
Term	:	Factor {}	
		|	Term opmd Factor {}
	;
Factor	: Ref {}
		| ninteger 	{}
		| parl Expr parr {}
		| nobool Factor	{}
		| booltokentrue {}
		| booltokenfalse {}
	;
Ref		:	id {}
		|	Ref bral Esimple brar {}
	;
/* Tipos */
TipoBase 	: inttype {$$.size = IN;}
			| outtype {$$.size = OUT;} 
			| inouttype {$$.size = INOUT;} 
	;

S 		: SSuperblock SAFunc {$$.trad = $1.trad + $2.trad; tfs.createFiles(projectFolder);}
	;

%%

void msgError(int nerror,int nlin,int ncol,const char *s)
{
     if (nerror != ERREOF)
     {
        fprintf(stderr,"Error %d (%d:%d) ",nerror,nlin,ncol);
        switch (nerror) {
         case ERRLEXIC: fprintf(stderr,"character '%s' not correct\n",s);
            break;
         case ERRSINT: fprintf(stderr,"in '%s'\n",s);
            break;
         case ERRNODEC: fprintf(stderr, "Variable %s not declared\n",s);
         	break;
         case ERRALDEC: fprintf(stderr, "Variable %s already declared\n",s);
         	break;
          case ERRFUNODEC: fprintf(stderr, "Module %s not declared\n",s);
         	break;
         case ERRFUNALDEC: fprintf(stderr, "Module %s already declared\n",s);
         	break;
        }
     }
     else
        fprintf(stderr,"Error in end of file\n");
     exit(1);
}


int yyerror(char *s)
{
    extern int endfile;   //  variable definida en plp5.l que indica si
                               // se ha acabado el fichero
    if (endfile) 
    {
       msgError(ERREOF,-1,-1,"");
    }
    else
    {  
       msgError(ERRSINT,nlin,ncol-strlen(yytext),yytext);
    }
}
string init_output(){
	
string output = "////////////////////////////////////////////////////////////////////////////////\n"+
std::string("////////////////////////////////////////////////////////////////////////////////\n")+
std::string("//					  THE         RTL CONNECTION COMPILER				         \n")+
std::string("//				    FOR NOT TO MAKE A         RTL CONNECTIONS			         \n")+
std::string("////////////////////////////////////////////////////////////////////////////////\n");

	return output;
}

void print_usage(void)
{
    printf("Use: verilog_connector <filename>\n");
    printf("-h, --help, help        Print this message\n");
    printf("-d                      Output directory name\n");
    printf("-n                      Set project name\n");
}
int arguments_handler(int argc, char ** argv){
    string str1 ;
    for(unsigned int args = 2; args < argc; ++args)
    {
        switch (argv[args][1]) {
            //directory name
            case 'd':
                str1.clear();
                str1.append(argv[args+1]);
                args++;
                projectFolder.clear();
                projectFolder.append(str1);
                break; 
            //project name
            case 'n' :
                str1.clear();
                str1.append(argv[args+1]);
                args++;
                projectName.clear();
                projectName.append(str1);
                break; 
            //default
            default:
                printf("argc %d \n", argc);
                printf("argv %c \n", argv[args][1]);
                printf("WRONG_ARGUMENTS\n");
                print_usage();
                return 1;
        }
    }
    return 0;
}

int main(int argc,char *argv[])
{
    FILE *fent;
    
    //Check if Help flag
    for(int i=0; i<argc; ++i){
        if(!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help")){
            print_usage();
            return(CORRECT_EXECUTION);
        }
    }
    //check if arguments are valid
    if (arguments_handler(argc,argv)) {
        printf("WRONG_ARGUMENTS\n");
        return(WRONG_ARGUMENTS);
    }

    if (argc>=2)
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
    else{
        fprintf(stderr,"Use: example <filename>\n");
        return(WRONG_ARGUMENTS);
    }        
}



