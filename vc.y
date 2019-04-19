%token id ninteger amp moduledefinition intype inttype outtype inouttype definevalue wiretipe
%token opas parl parr pyc coma oprel opmd opasig bral connectwire nyooperator stringtext
%token brar cbl cbr ybool obool nobool opasinc definevalue twopoints mainmodule
%token functionmodule descriptionmodule codermodule referencesmodule booltoken


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
const int REGISTER=2;
const int STRING=3;
const int LOGIC=5;

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
		for (int i = 0; i < v_tipos.size(); ++i) {
			tt_content += "// type:" + to_string(v_tipos.at(i).type) + " tam:" + to_string(v_tipos.at(i).size) 
						+ " baseType:" + to_string(v_tipos.at(i).baseType) + "\n";
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
			ts_content += "// type:" + to_string(v_symbols.at(i).type) + " name:" + v_symbols.at(i).name + " value:" + to_string(v_symbols.at(i).value)"\n";
		}
		ts_content += "////////////////////////////////////////////////////////////////////////////////\n";
		return ts_content;
	}
	string getNewLabel() {
		string etq = "L" + to_string(lastLabel);
		++lastLabel;
		return etq;
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
		s.name = "null"
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

const int IN=1;
const int OUT=2;
const int INOUT=3;

sturct InoutSymbol {
	/* Value definitions*/
	string name;
	int typeconnection;
	string with; // TODO CHECK
};

struct FunctionSymbolParam{
	string name;
	int value;
};

struct FunctionSymbol {
	/* Value definitions*/
	string name;
	vector<InoutSymbol> v_inoutwires;
	vector<FunctionSymbolParam> v_param;
	string filename_asociated;
	string function;
	string description;
	string code;
	string proyectName;
	string references;

	/* Functions */
	bool addConnectionFunctionSymbol(string name,  int type, string with){
		InoutSymbol s;
		s.name = name;
		s.type = type;
		s.with = with;
		for (int i = 0; i < v_inoutwires.size();++i) {
			if (v_inoutwires.at(i).name == s.name) { 
				// fail: connection alrady declared
				msgError(ERRCONNDEC, nlin, ncol - name.length(), name.c_str());
				return false;
			}
		}
		v_inoutwires.push_back(s);
		return true;
	}

	InoutSymbol searchinoutSymbol(string name) {
		InoutSymbol s;
		s.name = "null";
		s.filename_asociated = "";
		for (int i = 0; i < v_funcSymbols.size();++i) {
			if (v_funcSymbols.at(i).name == name) {
				return v_funcSymbols.at(i);
			}
		}
		// fail: connection not declared
		msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
		return s;
	}

	bool addFunctionSymbolParam(string name){
		FunctionSymbolParam s;
		s.name = name;
		for (int i = 0; i < v_param.size();++i) {
			if (v_param.at(i).name == s.name) { 
				// fail: Symbol param  already declared
				msgError(ERRPARAMDEC, nlin, ncol - name.length(), name.c_str());
				return false;
			}
		}
		v_param.push_back(s);
		return true;
	}
	bool addValueFunctionSymbolParam(string name, int value){
		FunctionSymbolParam s;
		s.name = name;
		for (int i = 0; i < v_param.size();++i) {
			if (v_param.at(i).name == s.name) { 
				v_param.at(i).value = value;
				return true;
			}
		}
		// fail: Symbol param  not declared
		msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
		return false;
	}
	FunctionSymbolParam searchFunctionSymbolParam(string name){
		FunctionSymbolParam s;
		s.name = "null";
		s.value = "-1";
		for (int i = 0; i < v_param.size();++i) {
			if (v_param.at(i).name == s.name) { 
				return v_funcSymbols.at(i);
			}
		}
		// fail: Symbol param  not declared
		msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
		return FunctionSymbolParam;
	}
};


struct TableFunctionSymbols {
	/* Value definitions*/
	vector<FunctionSymbol> v_funcSymbols;


	/* Functions */
	string debugTSymbols() {
		string ts_content("");
		ts_content += "// TableFunctionSymbols\n";
		ts_content += "////////////////////////////////////////////////////////////////////////////////\n";
		for (int i = 0; i < v_funcSymbols.size();++i) {
			ts_content += "// name:" + v_funcSymbols.at(i).name + "\n";
		}
		ts_content += "////////////////////////////////////////////////////////////////////////////////\n";
		return ts_content;
	}
	bool addFunctionSymbol(string name){
		FunctionSymbol s;
		s.name = name;
		s.function = "";
		s.description = "";
		s.code = "";
		s.proyectName = proyectName;
		s.references  = "";
		for (int i = 0; i < v_funcSymbols.size();++i) {
			if (v_funcSymbols.at(i).name == s.name) { 
				// fail: func var ya decl
				msgError(ERRFUNALDEC, nlin, ncol - name.length(), name.c_str());
				return false;
			}
		}
		/* Generate File Name */
		s.filename_asociated = s.name + ".v";
		/* add function to vector */
		v_funcSymbols.push_back(s);
		return true;
	}
	FunctionSymbol searchFunctionSymbol(string name) {
		FunctionSymbol s;
		s.name = "null";
		for (int i = 0; i < v_funcSymbols.size();++i) {
			if (v_funcSymbols.at(i).name == name) {
				return v_funcSymbols.at(i);
			}
		}
		// fail: func var no decl
		msgError(ERRFUNODEC, nlin, ncol - name.length(), name.c_str());
		return s;
	}

};

/* Table Symbols */
TableFunctionSymbols tfs;
/* Table Symbols */
/* Global proyect Name */
string proyectName = "a.out";


void createFileModule(string name){
	FunctionSymbol s = tfs.searchFunctionSymbol(name);
	/* create file */
	char buf[0x100];
	snprintf(buf, sizeof(buf), "%s", s.filename_asociated);
	FILE *f = fopen(buf, "w");
	/* Start wriking the file */
	/* Definition top file */
	fprintf(f, "//-----------------------------------------------------\n"); 
	fprintf(f, "// Project Name : %s\n", proyectName);
	if (s.function != ""){
		fprintf(f, "// Function     : $s\n", s.function);
	}
	if (s.description != ""){
		fprintf(f, "// Description  : %s\n", s.function);
	}
	if (s.code != ""){
		fprintf(f, "// Coder        : %s\n", s.function);
	}
	if (s.references != ""){
		fprintf(f, "// References   : %s\n", s.references);
	}
	fprintf(f, "\n");
	fprintf(f, "//***Headers***\n"); 
	fprintf(f, "//***Module***\n");
	/* Defining Module */
	if (s.v_param.size() != 0){
		/* Module has param*/
		fprintf(f, "module %s #(\n", s.name);
		// Loop over param
		for (int i = 0; i < s.v_param.size();++i) {
			if (i == s.v_param.size() -1){
				/* Last parameter */
				fprintf(f, "\t\tparameter integer %s = %d\n", s.v_param.at(i).name, s.v_param.at(i).value);
			}
			else{
				/* Rest parameter */
				fprintf(f, "\t\tparameter integer %s = %d,\n", s.v_param.at(i).name, s.v_param.at(i).value);
			}
		}
		fprintf(f, "\t)\n\t(\n");

	}
	else{
		/* Module has not param*/
		fprintf(f, "module %s (\n", s.name); 
	}
	/* copy the inputs and outputs*/
	for (int i = 0; i < s.v_inoutwires.size();++i) {
		string type = "";
			if (s.v_inoutwires.at(i).typeconnection == IN){
				type = "input";
			}
			else if (s.v_inoutwires.at(i).typeconnection == OUT){
				type = "output";
			}
			else if (s.v_inoutwires.at(i).typeconnection == INOUT){
				type = "inout";
			}
		if (i == s.v_inoutwires.size() -1){
			/* Last INOUT parameter */
			fprintf(f, "\t\t %s %s %s\n", type ,s.v_inoutwires.at(i).with, s.v_inoutwires.at(i).name);
		}
		else{
			/* Rest INOUT parameter */
			fprintf(f, "\t\t %s %s %s,\n", type ,s.v_inoutwires.at(i).with, s.v_inoutwires.at(i).name);
		}
	}
	/* End inputs and outputs */
	fprintf(f, "\t);\n");
	/* Putin some extra coments */
	fprintf(f, "//***Interal logic generated by compiler***  \n");
	fprintf(f, "//***Handcrafted Internal logic*** \n");
	fprintf(f, "//TODO\n");
	/* finish file */
	fprintf(f, "endmodule\n"); 
	fclose(f);
}

/* END FUNCTIONS */
/*Global Helpers*/
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
SIDS            : SIDS id {string pme = $2.lexema; $$.trad = $1.trad + " " + pme;}
				| id {string pme = $1.lexema; $$.trad = pme;}
				| /*epsilon*/ { } 
	;
ModuleTextDefinition : stringtext { string pme = $1.lexema; $$.trad = pme;} // TODO CHECK  HOW IN BISON MAKES THE STRINGS 
				     | Ref {$$.trad = $1.trad;}
	;
ValueDefinition : ninteger  {$$.trad = "";}
				| booltoken {$$.trad = "";}
				| quotes  SIDS id  quotes{$$.trad = "";} // TODO CHECK  HOW IN BISON MAKES THE STRINGS 
	;
SSuperblock : SSuperblock definevalue id  {string pme = $3.lexema; $0.ph = pme;} ValueDefinition {$$.trad = $1.trad + $5.trad;}
			| definevalue id {string pme = $3.lexema; $0.ph = pme;} ValueDefinition{$$.trad = $1.trad;}
			| /*epsilon*/ { } 
	;
/* Function agrupation*/
SFunc 		: SFunc Func {$$.trad = $1.trad + $2.trad;}
			| Func {$$.trad = $1.trad;}
			| /*epsilon*/ { } 
	;
SAFunc      : SFunc MainFunc {$$.tad = $1.trad + $2.trad;}
	;
/* Function */
Func 		: moduledefinition id 
			{
				/*Add module*/
				string pme = $2.lexema;
				tfs.addFunctionSymbol(pme);
				$$.ph = pme;
			} 
			parl SArgs parr Block 
			{
				/* Create file for module*/	
			}
	;
MainFunc    : moduledefinition mainmodule id parl SArgs parr Block {string pme = $3.lexema; $$.trad = "main " + pme + " (" + $5.trad + ")" + $7.trad;}
	;
/* Function args */
SArgs 		: {$$.ph = $0.ph;} SAArgs id 
			{	
				string pme = $3.lexema;
				FunctionSymbol s;
				if($0.ph != "null"){
					s = tfs.searchFunctionSymbol($0.ph);
					s.addFunctionSymbolParam(pme);

				}
			}
			| /*epsilon*/ { } 
	;
SAArgs 		:  id coma {$$.ph = $0.ph;} SAArgs 
				{
					string pme = $1.lexema;
				    FunctionSymbol s;
				    if($0.ph != "null"){
				    	s = tfs.searchFunctionSymbol($0.ph);
						s.addFunctionSymbolParam(pme);
				    }
				}
			|/*epsilon*/ { } 
	;
/* Block definition and instructions base  */
Block 		: cbl {$$.ph = $0.ph;}SInstr cbr  {}
	;
SInstr		: {$$.ph = $0.ph;} SInstr Instr {}
			| {$$.ph = $0.ph;} Instr  	    {}
	;
/* Instruction definition  */
Instr 		: EInstr pyc {$$.trad = $1.trad + ";"}
			| functionmodule ModuleTextDefinition 
				{
					if($0.ph != "null"){
				    	s = tfs.searchFunctionSymbol($0.ph);
				    	if (s.function == ""){
				    		s.function = $2.trad;
				    	}else{
				    		// fail: functionmodule Olreeady defing
							msgError(ERRFUNODEC, nlin, ncol - name.length(), name.c_str());
				    	}
						
				    }
				}
			| descriptionmodule ModuleTextDefinition {
					if($0.ph != "null"){
				    	s = tfs.searchFunctionSymbol($0.ph);
						if (s.description == ""){
				    		s.description = $2.trad;
				    	}else{
				    		// fail: functionmodule Olreeady defing
							msgError(ERRDESCDEFALDEC, nlin, ncol - name.length(), name.c_str());
				    	}
				    }
				}
			| codermodule ModuleTextDefinition {
					if($0.ph != "null"){
				    	s = tfs.searchFunctionSymbol($0.ph);
						if (s.code == ""){
				    		s.code = $2.trad;
				    	}else{
				    		// fail: functionmodule Olreeady defing
							msgError(ERRORCODDEFALDEC, nlin, ncol - name.length(), name.c_str());
				    	}
				    }
				}
			| references ModuleTextDefinition {
					if($0.ph != "null"){
				    	s = tfs.searchFunctionSymbol($0.ph);
						if (s.references == ""){
				    		s.references = $2.trad;
				    	}else{
				    		// fail: functionmodule Olreeady defing
							msgError(ERRORDEFIALDEC, nlin, ncol - name.length(), name.c_str());
				    	}
				    }
				}
			| intype InstrINOUT 
				{
					if($0.ph != "null"){

					}
				} 

	;
EInstr 		: Ref opasig SExpr {$$.trad = $1.trad + " = " + $3.trad;}
			| TipoBase id      {string pme = $2.lexema; $$.trad = $1.trad + pme;}
	;
InstrINOUT  : id {string pme = $1.lexema; $$.trad = pme; $$.size = 0;}
			| bral Expr twopoints Expr brar id {string pme = $6.lexema; $$.trad = pme; $$.size = 0;}
	;
/* Tipos */
TipoBase 	: int {string pme = $1.lexema $$.trad = pme;}

S 		: SSuperblock SAFunc {$$.trad = $1.trad + $2.trad;}
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
         case ERRNODEC: fprintf(stderr, "Variable %s not declared\n",s);
         	break;
         case ERRALDEC: fprintf(stderr, "Variable %s already declared\n",s);
         	break;
          case ERRNODEC: fprintf(stderr, "Module %s not declared\n",s);
         	break;
         case ERRALDEC: fprintf(stderr, "Module %s already declared\n",s);
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
	string output = "
////////////////////////////////////////////////////////////////////////////////\n
//                                                                              \n
//                                 -+ydNMMNdy+-                                 \n
//                             -ohNmy+-.``.:omMmo.                              \n
//                      .:/++hNds:`           +NMMy                             \n 
//                    :mMMMMMNdh`              -NMM+                            \n
//                   .MMMMMMMd`Ns               -MMy                            \n
//                   /MMMMMmo` mm/o   :ymmmhs/.  yMh                            \n
//                   .MMMMMmhhmMmy/  yMMMMMM+yNy sMy                            \n
//                   oMo`-:NMMs-o+` oMMMMMMM+`mM-dMs                            \n
//                  sMN/-.`+yyysys. yMMMmhy/  hs-MM/                            \n
//                `hMdhdmNNmdhs+/-. `+ydmmhyys/ hMN`                            \n
//                yMd````..:/osyhhdddys+/:...` -MMo                             \n
//               sMm.            ```.-::/:.    dMM:                             \n
//              oMN-                          /MMh                              \n
//             +MM/                          `mMN-                              \n
//            -NM+                  -`       yMM/                               \n
//            /MN                  oN/ /+   :MM+                                \n
//            /Mh                 `Nm`-MM` `mMo                   .+ysyy+.      \n
//            +Ms                 /M+ dMo  sMd                  .omm:``/Mh      \n
//            +M+                 dd +Mh` :MM-                `+mNs.   -Ms      \n
//            +M+                -M:-Nm`  dMd   ```.``       :dNy-    -ms`      \n
//            +M+                yy.mN-   NMhoyhhhddddho:` -yNy-    `om+        \n
//            /Ms               .m.hN:    NMy/:-oo:.-/sdNdsmy-    `+mm:         \n
//            -Mm              `h+`Mo     :+`  `+Ns--..-hms-    `/dMy.          \n
//             NM-           `:ys  sy-       -shddmmmNmmMo.    :dMMo`           \n
//             oMh          :s/- .s::N-       .....--:/sdMNs.  -ohds+-`         \n
//             `NM/         .+sN/hmyyy`          `+.    `:dMm:  ```./My         \n
//              +MN/           :yo. .            /y:      `dMN. `+yyso.         \n
//               +NMs`                        -/           :MM/   :ds           \n
//                .sNmo.                     `my           -MM/`   +M-          \n
//          ``      .dMmh+.`                  ++`         `yMmdyyyyds           \n
//          dyo-   `sNs-oNNdy+-.``            .:.       .odd/``.--.`            \n
//          N-:hy.-dd:`:hy-/sdmmdhys+/.`        ++   `/ymh:                     \n
//          yy  /hmo`-yh:     `-:+oymMM+ :hyysso+o/oydd+.                       \n
//          .m/  `.:yd/       .sys++mMo `mm-:/osyyyo:.                          \n
//           -d/./hd/         :MMymNm/  yN-                                     \n
//            `oNd/`          `mMo .`  +N:                                      \n
//              `              -NM:   /N+                                       \n
//                              .dNo.oN+                                        \n
//                                oNNh.                                         \n
//                                                                              \n
////////////////////////////////////////////////////////////////////////////////\n
//					  THE DICKBUT RTL CONNECTION COMPILER				        \n
//				    FOR NOT TO MAKE A DICKBUT RTL CONNECTIONS			        \n
////////////////////////////////////////////////////////////////////////////////\n
";

	return output;
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