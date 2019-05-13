%token id ninteger amp moduledefinition intype inttype outtype inouttype definevalue wiretipe
%token opas parl parr pyc coma oprel opmd opasig bral connectwire nyooperator stringtext
%token brar cbl cbr ybool obool nobool opasinc twopoints mainmodule booltokentrue definevalueverilog
%token functionmodule descriptionmodule codermodule referencesmodule booltoken booltokenfalse


%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

#include "common.h"
#include "./objects/TableFunctionSymbols.h"
#include "./objects/TableSymbols.h"

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

/* Auxiliary Function */
vector<std::string> split_ref(string value){
	istringstream iss(value);
	std::vector<std::string> tokens;
	std::string token;
	while (std::getline(iss, token, '.')) {
	    if (!token.empty())
	        tokens.push_back(token);
	}
return  tokens;
}
/*  Auxiliary Function */

/* Tabla Types */
TableTypes tt;
/* Tabla Types */

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
		}
	;
/* Base syntax */
ModuleTextDefinition : stringtext { string pme = $1.lexeme; pme.erase(0, 1);pme.erase(pme.size() - 1); $$.trad = pme;}
				     | Ref {
				     	int pos = ts.shearchSymbol($1.trad);
				     	string value = ts.v_symbols.at(pos).getValue_S();
				     	// TODO ERASE 
				     	//cout<<"name "<<ts.v_symbols.at(pos).getName() << " type "<< ts.v_symbols.at(pos).getType() << " value " << value << endl;
				     	$$.trad = value;
				    	}
	;

ValueDefinition : ninteger  {string pme = $1.lexeme; $$.trad = pme; $$.size = INTEGER;}
				| booltoken {string pme = $1.lexeme; $$.trad = pme; $$.size = LOGIC;}
				| stringtext{string pme = $1.lexeme; $$.trad = pme; $$.size = STRING;}
	;
SSuperblock : SSuperblock SSSuperblockDefine id ValueDefinition {
						string pme = $3.lexeme;
						ts.addSymbol(pme,$2.size, $4.trad);
						$$.trad = $1.trad;
						}
			| SSSuperblockDefine id ValueDefinition{string pme = $2.lexeme; ts.addSymbol(pme,$1.size, $3.trad);$$.trad = $1.trad;}
			| /*epsilon*/ { } 
	;
SSSuperblockDefine	: definevalue {$$.size = DEFINITION;}
				   	| definevalueverilog {$$.size = DEFINITIONVERILOG;} 
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
				// fist add symbol
				ts.addSymbol(pme,FUNCTION);
				// then add symbol
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
				// fist add symbol
				ts.addSymbol(pme,FUNCTION);
				// then add symbol
				tfs.addFunctionSymbol(pme, projectName, projectFolder);
				s1 = pme;
			}  parl SArgs parr Block
			{
				/* Create file for module*/
				s1 = "null";
				string pme = $3.lexeme;
				int pos = tfs.searchFunctionSymbol(pme);
				string base = init_output();
				tfs.v_funcSymbols.at(pos).createFileModule("");

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
/* TODO THINK TO REDO WITH ONLY 2 RULES*/
Instr 		//: EInstr pyc {$$.trad = $1.trad + ";";}
			: functionmodule ModuleTextDefinition 
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
			| Ref opasig Expr pyc{$$.trad = $1.trad + " = " + $3.trad;}
			| TipoBase id pyc     {
								cout<<"ENTRO TIPO"<<endl;
								string pme = $2.lexeme; 
								$$.trad = $1.trad + pme;
								int pos = tfs.searchFunctionSymbol(s1);
								InoutSymbol con (pme ,$1.size,"");
								string with = "";
								tfs.v_funcSymbols.at(pos).addConnectionFunctionSymbol(pme,$1.size,with);
								}
			| wiretipe Ref connectwire Ref {
											string var_out = $2.trad;
											string var_in = $4.trad;
											// decompse the variables.
											// decompse out var
											vector<string> out = split_ref(var_out);
											// decompse in var
											vector<string> in = split_ref(var_in);
											// check out function 
											int pos = tfs.searchFunctionSymbol(out[0]);
											if (pos == -1){ 
												// error 
											}
											// check InoutSymbol
											InoutSymbol out_inout;
											out_inout= tfs.v_funcSymbols.at(pos).searchinoutSymbol(out[1]);
											if (out_inout.getName() == "null"){
												//error 
											}
											pos = tfs.searchFunctionSymbol(in[0]);
											if (pos == -1){ 
												// error 
											}
											// check InoutSymbol
											InoutSymbol in_inout;
											in_inout = tfs.v_funcSymbols.at(pos).searchinoutSymbol(in[1]);
											if (in_inout.getName() == "null"){
												//error 
											}
											// all verfiy
											// create wire. 



										   }
			|/*epsilon*/ { } 

	;
/*EInstr 		: Ref opasig Expr {$$.trad = $1.trad + " = " + $3.trad;}
			| TipoBase id      {
								cout<<"ENTRO TIPO"<<endl;
								string pme = $2.lexeme; 
								$$.trad = $1.trad + pme;
								int pos = tfs.searchFunctionSymbol(s1);
								InoutSymbol con (pme ,$1.size,"");
								string with = "";
								tfs.v_funcSymbols.at(pos).addConnectionFunctionSymbol(pme,$1.size,with);
								}
			| wiretipe Ref connectwire Ref {
											string var_out = $2.trad;
											string var_in = $4.trad;
											// decompse the variables.
											// decompse out var
											vector<string> out = split_ref(var_out);
											// decompse in var
											vector<string> in = split_ref(var_in);
											// check out function 
											int pos = tfs.searchFunctionSymbol(out[0]);
											if (pos == -1){ 
												// error 
											}
											// check InoutSymbol
											InoutSymbol out_inout;
											out_inout= tfs.v_funcSymbols.at(pos).searchinoutSymbol(out[1]);
											if (out_inout.getName() == "null"){
												//error 
											}
											pos = tfs.searchFunctionSymbol(in[0]);
											if (pos == -1){ 
												// error 
											}
											// check InoutSymbol
											InoutSymbol in_inout;
											in_inout = tfs.v_funcSymbols.at(pos).searchinoutSymbol(in[1]);
											if (in_inout.getName() == "null"){
												//error 
											}
											// all verfiy
											// create wire. 



										   }
	;*/
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
Ref		:	id {string pme = $1.lexeme; $$.trad = pme;}
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
std::string("//                                                                              \n")+
std::string("//                                 -+ydNMMNdy+-                                 \n")+
std::string("//                             -ohNmy+-.``.:omMmo.                              \n")+
std::string("//                      .:/++hNds:`           +NMMy                             \n")+
std::string("//                    :mMMMMMNdh`              -NMM+                            \n")+
std::string("//                   .MMMMMMMd`Ns               -MMy                            \n")+
std::string("//                   /MMMMMmo` mm/o   :ymmmhs/.  yMh                            \n")+
std::string("//                   .MMMMMmhhmMmy/  yMMMMMM+yNy sMy                            \n")+
std::string("//                   oMo`-:NMMs-o+` oMMMMMMM+`mM-dMs                            \n")+
std::string("//                  sMN/-.`+yyysys. yMMMmhy/  hs-MM/                            \n")+
std::string("//                `hMdhdmNNmdhs+/-. `+ydmmhyys/ hMN`                            \n")+
std::string("//                yMd````..:/osyhhdddys+/:...` -MMo                             \n")+
std::string("//               sMm.            ```.-::/:.    dMM:                             \n")+
std::string("//              oMN-                          /MMh                              \n")+
std::string("//             +MM/                          `mMN-                              \n")+
std::string("//            -NM+                  -`       yMM/                               \n")+
std::string("//            /MN                  oN/ /+   :MM+                                \n")+
std::string("//            /Mh                 `Nm`-MM` `mMo                   .+ysyy+.      \n")+
std::string("//            +Ms                 /M+ dMo  sMd                  .omm:``/Mh      \n")+
std::string("//            +M+                 dd +Mh` :MM-                `+mNs.   -Ms      \n")+
std::string("//            +M+                -M:-Nm`  dMd   ```.``       :dNy-    -ms`      \n")+
std::string("//            +M+                yy.mN-   NMhoyhhhddddho:` -yNy-    `om+        \n")+
std::string("//            /Ms               .m.hN:    NMy/:-oo:.-/sdNdsmy-    `+mm:         \n")+
std::string("//            -Mm              `h+`Mo     :+`  `+Ns--..-hms-    `/dMy.          \n")+
std::string("//             NM-           `:ys  sy-       -shddmmmNmmMo.    :dMMo`           \n")+
std::string("//             oMh          :s/- .s::N-       .....--:/sdMNs.  -ohds+-`         \n")+
std::string("//             `NM/         .+sN/hmyyy`          `+.    `:dMm:  ```./My         \n")+
std::string("//              +MN/           :yo. .            /y:      `dMN. `+yyso.         \n")+
std::string("//               +NMs`                        -/           :MM/   :ds           \n")+
std::string("//                .sNmo.                     `my           -MM/`   +M-          \n")+
std::string("//          ``      .dMmh+.`                  ++`         `yMmdyyyyds           \n")+
std::string("//          dyo-   `sNs-oNNdy+-.``            .:.       .odd/``.--.`            \n")+
std::string("//          N-:hy.-dd:`:hy-/sdmmdhys+/.`        ++   `/ymh:                     \n")+
std::string("//          yy  /hmo`-yh:     `-:+oymMM+ :hyysso+o/oydd+.                       \n")+
std::string("//          .m/  `.:yd/       .sys++mMo `mm-:/osyyyo:.                          \n")+
std::string("//           -d/./hd/         :MMymNm/  yN-                                     \n")+
std::string("//            `oNd/`          `mMo .`  +N:                                      \n")+
std::string("//              `              -NM:   /N+                                       \n")+
std::string("//                              .dNo.oN+                                        \n")+
std::string("//                                oNNh.                                         \n")+
std::string("//                                                                              \n")+
std::string("////////////////////////////////////////////////////////////////////////////////\n")+
std::string("//					  THE DICKBUT RTL CONNECTION COMPILER				         \n")+
std::string("//				    FOR NOT TO MAKE A DICKBUT RTL CONNECTIONS			         \n")+
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



