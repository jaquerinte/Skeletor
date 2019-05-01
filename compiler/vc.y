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

// variables y funciones del A. Léxico
extern int ncol,nlin,endfile;

/* START FUNCTIONS */
const int INTEGER=1;
const int REGISTER=2;
const int STRING=3;
const int LOGIC=5;

/* Global proyect Name */
string proyectName = "a.out";

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

const int IN=1;
const int OUT=2;
const int INOUT=3;

struct InoutSymbol {
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
		s.typeconnection = type;
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
		for (int i = 0; i < v_inoutwires.size();++i) {
			if (v_param.at(i).name == name) {
				return v_inoutwires.at(i);
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
		s.value = -1;
		for (int i = 0; i < v_param.size();++i) {
			if (v_param.at(i).name == s.name) { 
				return v_param.at(i);
			}
		}
		// fail: Symbol param  not declared
		msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
		return s;
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



void createFileModule(string name){
	FunctionSymbol s = tfs.searchFunctionSymbol(name);
	/* create file */
	char buf[0x100];
	snprintf(buf, sizeof(buf), "%s", s.filename_asociated.c_str());
	FILE *f = fopen(buf, "w");
	/* Start wriking the file */
	/* Definition top file */
	fprintf(f, "//-----------------------------------------------------\n"); 
	fprintf(f, "// Project Name : %s\n", proyectName.c_str());
	if (s.function != ""){
		fprintf(f, "// Function     : %s\n", s.function.c_str());
	}
	if (s.description != ""){
		fprintf(f, "// Description  : %s\n", s.description.c_str());
	}
	if (s.code != ""){
		fprintf(f, "// Coder        : %s\n", s.code.c_str());
	}
	if (s.references != ""){
		fprintf(f, "// References   : %s\n", s.references.c_str());
	}
	fprintf(f, "\n");
	fprintf(f, "//***Headers***\n"); 
	fprintf(f, "//***Module***\n");
	/* Defining Module */
	if (s.v_param.size() != 0){
		/* Module has param*/
		fprintf(f, "module %s #(\n", s.name.c_str());
		// Loop over param
		for (int i = 0; i < s.v_param.size();++i) {
			if (i == s.v_param.size() -1){
				/* Last parameter */
				fprintf(f, "\t\tparameter integer %s = %d\n", s.v_param.at(i).name.c_str(), s.v_param.at(i).value);
			}
			else{
				/* Rest parameter */
				fprintf(f, "\t\tparameter integer %s = %d,\n", s.v_param.at(i).name.c_str(), s.v_param.at(i).value);
			}
		}
		fprintf(f, "\t)\n\t(\n");

	}
	else{
		/* Module has not param*/
		fprintf(f, "module %s (\n", s.name.c_str()); 
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
			fprintf(f, "\t\t %s %s %s\n", type ,s.v_inoutwires.at(i).with.c_str(), s.v_inoutwires.at(i).name.c_str());
		}
		else{
			/* Rest INOUT parameter */
			fprintf(f, "\t\t %s %s %s,\n", type ,s.v_inoutwires.at(i).with.c_str(), s.v_inoutwires.at(i).name.c_str());
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
ModuleTextDefinition : stringtext { string pme = $1.lexeme; $$.trad = pme;} // TODO CHECK  HOW IN BISON MAKES THE STRINGS 
				     | Ref {$$.trad = $1.trad;}
	;
ValueDefinition : ninteger  {$$.trad = "";}
				| booltoken {$$.trad = "";}
				| stringtext{$$.trad = "";} // TODO CHECK  HOW IN BISON MAKES THE STRINGS 
	;
SSuperblock : SSuperblock definevalue id  {string pme = $3.lexeme; $0.ph = pme;} ValueDefinition {$$.trad = $1.trad + $5.trad;}
			| definevalue id {string pme = $2.lexeme; $0.ph = pme;} ValueDefinition{$$.trad = $1.trad;}
			| /*epsilon*/ { } 
	;
/* Function agrupation*/
//SFunc 		: SSAFunc {$$.trad = "";}
//			| /*epsilon*/ { } 
//	;
//SSAFunc     : SSAFunc Func {$$.trad = "";}
//			| Func {$$.trad = "";}
//			| /*epsilon*/ { } 
//	;
SAFunc      : Func MainFunc {$$.trad = $1.trad + $2.trad;}
	;
/* Function */
Func 		: moduledefinition id 
			{
				/*Add module*/
				string pme = $2.lexeme;
				tfs.addFunctionSymbol(pme);
				s1 = pme;
				//printf("%s", s1);
			} 
			parl SArgs parr  {} Block 
			{
				/* Create file for module*/	
				string pme = $2.lexeme;
				createFileModule(pme);
			}
	;
MainFunc    : moduledefinition mainmodule id parl SArgs parr Block {string pme = $3.lexeme; $$.trad = "main " + pme + " (" + $5.trad + ")" + $7.trad;}
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
DArgs       :  id SAArgs {
					string pme = $1.lexeme;
				    FunctionSymbol s;
				    //printf("%s", s1);
				    if(s1 != "null"){
				    	s = tfs.searchFunctionSymbol(s1);
						s.addFunctionSymbolParam(pme);
				    }
				}
	;
SAArgs 		:  coma id SAArgs 
				{
					string pme = $1.lexeme;
				    FunctionSymbol s;
				    if(s1 != "null"){
				    	s = tfs.searchFunctionSymbol(s1);
						s.addFunctionSymbolParam(pme);
				    }
				}
			|/*epsilon*/ { } 
	;
/* Block definition and instructions base  */
Block 		: cbl SInstr cbr  {}
	;
SInstr		: SInstr Instr {}
			| Instr  	   {}
	;
/* Instruction definition  */
Instr 		: EInstr pyc {$$.trad = $1.trad + ";";}
			| functionmodule ModuleTextDefinition 
				{
					FunctionSymbol s;
					if(s1 != "null"){
				    	s = tfs.searchFunctionSymbol(s1);
				    	if (s.function == ""){
				    		s.function = $2.trad;
				    	}else{
				    		// fail: functionmodule Olreeady defing
				    		string pme = $1.lexeme;
							msgError(ERRFUNODEC, nlin, ncol, pme.c_str());
				    	}
						
				    }
				}
			| descriptionmodule ModuleTextDefinition {
					FunctionSymbol s;
					if(s1 != "null"){
				    	s = tfs.searchFunctionSymbol(s1);
						if (s.description == ""){
				    		s.description = $2.trad;
				    	}else{
				    		// fail: functionmodule Olreeady defing
				    		string pme = $1.lexeme;
							msgError(ERRDESCDEFALDEC, nlin, ncol, pme.c_str());
				    	}
				    }
				}
			| codermodule ModuleTextDefinition {
				    FunctionSymbol s;
					if(s1 != "null"){
				    	s = tfs.searchFunctionSymbol(s1);
						if (s.code == ""){
				    		s.code = $2.trad;
				    	}else{
				    		// fail: functionmodule Olreeady defing
				    		string pme = $1.lexeme;
							msgError(ERRORCODDEFALDEC, nlin, ncol, pme.c_str());
				    	}
				    }
				}
			| referencesmodule ModuleTextDefinition {
					if(s1 != "null"){
						FunctionSymbol s;
				    	s = tfs.searchFunctionSymbol(s1);
						if (s.references == ""){
				    		s.references = $2.trad;
				    	}else{
				    		// fail: functionmodule Olreeady defing
				    		string pme = $1.lexeme;
							msgError(ERRORDEFIALDEC, nlin, ncol, pme.c_str());
				    	}
				    }
				}
			| intype InstrINOUT 
				{

				}
			| intype id pyc {}
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
			| TipoBase id      {string pme = $2.lexeme; $$.trad = $1.trad + pme;}
	;
InstrINOUT  : id {string pme = $1.lexeme; $$.trad = pme; $$.size = 0;}
			| bral Expr twopoints Expr brar id {string pme = $6.lexeme; $$.trad = pme; $$.size = 0;}
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
TipoBase 	: inttype {string pme = $1.lexeme; $$.trad = pme;}

S 		: SSuperblock SAFunc {$$.trad = $1.trad + $2.trad;}
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