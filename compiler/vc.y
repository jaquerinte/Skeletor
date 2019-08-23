%token id ninteger amp moduledefinition intype inttype outtype inouttype definevalue wiretipe
%token opas parl parr pyc coma oprel opmd opasig bral connectwire nyooperator stringtext
%token brar cbl cbr ybool obool nobool opasinc twopoints mainmodule booltokentrue definevalueverilog
%token functionmodule descriptionmodule codermodule referencesmodule booltoken booltokenfalse verilogtext wireverilogtipe


%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

//#include "common.h"
#include "./objects/TableFunctionSymbols.h"
#include "./objects/TableSymbols.h"

/* Version */
#define VERSION "1.2.1"

/* Return messages */
#define CORRECT_EXECUTION 0
#define WRONG_ARGUMENTS 1

// variables y funciones del A. Léxico
extern int ncol,nlin,endfile;

/* START FUNCTIONS */
const int INTEGER=1;
const int REFERENCE=2;
const int STRING=3;
const int LOGIC=5;


/* Global project Name */
string projectName = "a.out";
string projectFolder = "OUTPUT";
bool db = false;
bool tb = false;
bool itb = false;
bool qtb = true;
bool vtb = false;
string init_output(bool);

struct Type {
    int type;
    int size;
    int baseType;
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
string s2;
string name_function_main;

int yyerror(char *s);

%}

%%
SA      : S     
        { 
            int tk = yylex();
            if (tk != 0) yyerror("");
        }
    ;
/* Base syntax */
ModuleTextDefinition : stringtext { string pme = $1.lexeme; pme.erase(0, 1);pme.erase(pme.size() - 1); $$.trad = pme;}
                     | Ref {
                        int pos = ts.shearchSymbol($1.trad, s1, nlin,ncol);
                        string value = ts.v_symbols.at(pos).getValue_S();
                        $$.trad = value;
                        }
    ;

ValueDefinition : ninteger  {string pme = $1.lexeme; $$.trad = pme; $$.size = INTEGER;}
                | booltoken {string pme = $1.lexeme; $$.trad = pme; $$.size = LOGIC;}
                | stringtext{string pme = $1.lexeme; $$.trad = pme; $$.size = STRING;}
    ;
SSuperblock : SSuperblock SSSuperblockDefine id ValueDefinition {
                        string pme = $3.lexeme;
                        ts.addSymbol(pme,$2.size, $4.trad, $4.size, "null", nlin, ncol);
                        $$.trad = $1.trad;
                        }
            | SSSuperblockDefine id ValueDefinition{string pme = $2.lexeme; ts.addSymbol(pme,$1.size, $3.trad, $3.size, "null", nlin, ncol);$$.trad = $1.trad;}
            | /*epsilon*/ { } 
    ;
SSSuperblockDefine  : definevalue {$$.size = DEFINITION;}
                    | definevalueverilog {$$.size = DEFINITIONVERILOG;} 
    ;
/* Function agrupation*/
SSAFunc     : SSAFunc Func {$$.trad = $1.trad + $2.trad;}
            | Func {$$.trad = $1.trad;}
    ;
SAFunc      : SSAFunc MainFunc {$$.trad = $1.trad + $2.trad;}
    ;
/* Function */
Func        : moduledefinition id 
            {
                /*Add module*/
                string pme = $2.lexeme;
                // fist add symbol
                ts.addSymbol(pme,FUNCTION, "null", nlin, ncol);
                // then add symbol
                tfs.addFunctionSymbol(pme, projectName, projectFolder, nlin, ncol);
                s1 = pme;
                //printf("%s", s1);
                
            } 
            parl SArgs parr  Block 
            {
                /* Create file for module*/
                s1 = "null";
                string pme = $2.lexeme;
                int pos = tfs.searchFunctionSymbol(pme, nlin, ncol);
                tfs.v_funcSymbols.at(pos).createFileModule(ts.createDefinitions());

            }
    ;
MainFunc    : moduledefinition mainmodule id
            {
                /*Add module*/
                string pme = $3.lexeme;
                // fist add symbol
                ts.addSymbol(pme,FUNCTION,"null", nlin, ncol);
                // then add symbol
                tfs.addFunctionSymbol(pme, projectName, projectFolder, nlin, ncol);
                s1 = pme;
                name_function_main = pme;
            }  parl SArgs parr Block
            {
                /* Create file for module*/
                s1 = "null";
                string pme = $3.lexeme;
                int pos = tfs.searchFunctionSymbol(pme, nlin, ncol);
                string base = init_output(db);
                tfs.v_funcSymbols.at(pos).createFileModule(init_output(db), ts.createDefinitions());

                
                

            }
    ;
/* Function args */
SArgs       : DArgs {$$.trad = "";}
            | /*epsilon*/ { } 
    ;

DArgs       : id SArBlock {
                    string pme = $1.lexeme;
                    
                    //printf("%s", s1);
                    if(s1 != "null"){
                        ts.addSymbol(pme,PARAMETERFUNCTION,$2.trad, INTEGER, s1, nlin, ncol);
                        int pos  = tfs.searchFunctionSymbol(s1, nlin, ncol);
                        if ($2.trad == ""){
                            tfs.v_funcSymbols.at(pos).addFunctionSymbolParam(pme, nlin, ncol);
                        }
                        else{
                            tfs.v_funcSymbols.at(pos).addFunctionSymbolParam(pme, $2.trad, $2.size, nlin, ncol);
                        }
                        
                    }

            }
            | DArgs  coma id SArBlock {
                
                 string pme = $3.lexeme;
                    if(s1 != "null"){
                        ts.addSymbol(pme,PARAMETERFUNCTION,$4.trad, INTEGER, s1, nlin, ncol);
                        int pos  = tfs.searchFunctionSymbol(s1, nlin, ncol);
                        if ($4.trad == ""){
                            tfs.v_funcSymbols.at(pos).addFunctionSymbolParam(pme, nlin, ncol);
                        }
                        else{
                            tfs.v_funcSymbols.at(pos).addFunctionSymbolParam(pme, $4.trad, $4.size, nlin, ncol);
                        }
                    }

            }
    ;
SArBlock    : opasig Expr {
                        
                        if ($2.type == INTEGER){
                            $$.trad = $2.trad;
                            $$.size = $2.size;
                        }
                        else if ($2.type == REFERENCE){
                            int pos = ts.shearchSymbol($2.trad, s1,nlin,ncol);
                            $$.trad = $2.trad;
                            $$.size = $2.size;
                        }
                        
                        
                        }
            | /*epsilon*/ { $$.trad = "";} 
    ;
/* Block definition and instructions base  */
Block       : cbl SInstr cbr  {$$.trad = $2.trad;}
    ;
SInstr      : SInstr Instr {$$.trad = $1.trad + $2.trad;}
            | Instr        {$$.trad = $1.trad;}
    ;
/* Instruction definition  */
/* TODO THINK TO REDO WITH ONLY 2 RULES*/
Instr       : EInstr pyc {$$.trad = $1.trad + ";";}
            | verilogtext {
                 int pos;
                    if(s1 != "null"){
                        pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
                        string pme = $1.lexeme;
                        tfs.v_funcSymbols.at(pos).addVerilogDump(pme);
                    }
            }
            | functionmodule ModuleTextDefinition 
                {
                    int pos;
                    if(s1 != "null"){
                        pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
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
                        pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
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
                        pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
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
                        pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
                        if (tfs.v_funcSymbols.at(pos).getReferences() == ""){
                            tfs.v_funcSymbols.at(pos).setReferences($2.trad);
                        }else{
                            // fail: functionmodule Olreeady defing
                            string pme = $1.lexeme;
                            msgError(ERRORDEFIALDEC, nlin, ncol, pme.c_str());
                        }
                    }
                }
            |/*epsilon*/ { } 

    ;
EInstr      : Ref {    
                       string pme = $1.trad; $$.ph = pme;} CallExpresion {$$.trad = $3.trad;}
            | TipoBase Arrayargs id  {
                                string aux = "_";
                                string pme = $3.lexeme;
                                // add symbol
                                int pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
                                ts.addSymbol(pme + aux + $1.trad,INOUTSYMBOL,s1, nlin, ncol);
                                string with = $2.trad ;
                                tfs.v_funcSymbols.at(pos).addConnectionFunctionSymbol(pme,$1.size,with, nlin, ncol);
                                $$.trad = $1.trad + pme;
                                }
            | wireverilogtipe Arrayargs id {
                                string aux = "_w";
                                string pme = $3.lexeme;
                                int pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
                                string with = $2.trad ;
                                ts.addSymbol(pme + aux ,INOUTSYMBOL,s1, nlin, ncol);
                                tfs.v_funcSymbols.at(pos).addVWireConnection(with,pme+aux);
                                }
            | wiretipe Arrayargs Ref connectwire Ref {
                                string var_out = $3.trad;
                                string var_in = $5.trad;
                                // get functionsymbol that stores instantce
                                int pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
                                // decompse the variables.
                                // decompse out var
                                vector<string> out = split_ref(var_out);
                                // decompse in var
                                vector<string> in = split_ref(var_in);
                                // check out function 
                                int pos_base = tfs.v_funcSymbols.at(pos).searchInstance(out[0], nlin, ncol);
                                // check InoutSymbol
                                int out_inout;
                                out_inout = tfs.v_funcSymbols.at(pos).v_instances.at(pos_base).searchinoutSymbol(out[1], OUT, nlin, ncol);
                                int pos_aux = tfs.v_funcSymbols.at(pos).searchInstance(in[0], nlin, ncol);
                                // check InoutSymbol
                                int in_inout;
                                in_inout = tfs.v_funcSymbols.at(pos).v_instances.at(pos_aux).searchinoutSymbol(in[1], IN, nlin, ncol);
                                // all verfiy
                                // add values instance and store wire
                                string name_wire = out[1] + "_" + out[0] + "_" + in[0];
                                // verify the wire if already exists and register if not
                                ts.addSymbol(name_wire,WIRE,s1, nlin, ncol);
                                // create wire.
                                // add and instace out
                                tfs.v_funcSymbols.at(pos).v_instances.at(pos_base).addValueInoutSymbolParam(out[1], name_wire, OUT, nlin,ncol);
                                // add and instace in
                                tfs.v_funcSymbols.at(pos).v_instances.at(pos_aux).addValueInoutSymbolParam(in[1], name_wire, IN, nlin,ncol);
                                // add wire
                                tfs.v_funcSymbols.at(pos).addWireConnection(out[0],in[0],out_inout, in_inout, $2.trad,name_wire, out[1] + "_o", in[1]+ "_i");

                               }
    ;
CallExpresion   :  twopoints id {
                    string pme = $2.lexeme;
                    //int pos = ts.shearchSymbol(pme,s1, nlin,ncol);
                    //if (pos != -1){
                        // TODO chaneg for properly error 
                      //  cout<< "INSTANCE SYMBOL DECLARED"<<endl;
                       // exit(1);
                    //}
                    ts.addSymbol(pme,INSTANCESYMBOL,s1, nlin, ncol);
                    int pos_instance = tfs.searchFunctionSymbol(s1, nlin, ncol);
                    int pos_module = tfs.searchFunctionSymbol($0.ph, nlin, ncol);
                    s2 = pme;
                    tfs.v_funcSymbols.at(pos_instance).addInstance(tfs.v_funcSymbols.at(pos_module).getInoutSymbol(), tfs.v_funcSymbols.at(pos_module).getFunctionSymbolParam(), $0.ph, pme);
                }

                parl CallArgs parr cbl CallConnectors cbr 
                {
                    string pme = $2.lexeme;
                    string pme_name = $0.ph;
                    //ts.addSymbol(pme,INSTANCESYMBOL,s1, nlin, ncol);
                    s2 = "null";

                    //(vector<InoutSymbol> v_inoutwires, vector<FunctionSymbolParam> v_param, string name_module, string name_instance)
                    //tfs.v_funcSymbols.at(pos).addInstance()
                }
    ;
/* Call args */
CallArgs    : DCallArgs {$$.trad = "";}
            | /*epsilon*/ { } 
    ;

DCallArgs   : Expr DCallArgsExtension{
                string pme = $2.trad;
                $$.trad = "";
                int pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
                if (pme == ""){
                    // made by position
                    $$.ph = "position";
                    // if access a position is the 0 position
                    //cout << "Entro Position" << endl;
                    int pos_instance = tfs.v_funcSymbols.at(pos).searchInstance(s2, nlin, ncol);
                    tfs.v_funcSymbols.at(pos).v_instances.at(pos_instance).addValueFunctionSymbolParamPos(0, $1.trad);
                }else{
                    // asigned by name
                    //cout << "Entro Name" << endl;
                    $$.ph = "name";
                    int pos_instance = tfs.v_funcSymbols.at(pos).searchInstance(s2, nlin, ncol);
                    tfs.v_funcSymbols.at(pos).v_instances.at(pos_instance).addValueFunctionSymbolParam($1.trad, $2.trad, nlin, ncol);
                }
                $$.counter = 1;
            }
            | DCallArgs coma Expr DCallArgsExtension {
                int pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
                $$.trad = "";
                // transition beetween continous by position
                if ($1.ph == "position" && $4.trad == ""){
                    $$.ph = "position";
                }
                // transition beetween position and name
                else if ($1.ph == "position" && $4.trad != ""){
                        $$.ph = "name";
                }
                // transition beetween continous by position
                else if ($1.ph == "name" && $4.trad != ""){
                        $$.ph = "name";
                }
                else{
                    // TODO ERROR positional argument in a name position
                    msgError(ERRINSNOTFOUND, nlin, ncol -  $3.trad.length(),  $3.trad.c_str());
                }
                // process arguments
                if($$.ph == "position"){
                    
                    int pos_instance = tfs.v_funcSymbols.at(pos).searchInstance(s2, nlin, ncol);
                    tfs.v_funcSymbols.at(pos).v_instances.at(pos_instance).addValueFunctionSymbolParamPos($$.counter, $3.trad);
                }
                else{
                    // procces by name 
                    int pos_instance = tfs.v_funcSymbols.at(pos).searchInstance(s2, nlin, ncol);
                    tfs.v_funcSymbols.at(pos).v_instances.at(pos_instance).addValueFunctionSymbolParam($4.trad, $3.trad, nlin, ncol);
                }
                $$.counter = + $1.counter + 1;
            }
    ;

DCallArgsExtension  : opasig Expr {$$.trad = $2.trad;}
                    | /*epsilon*/ { $$.trad = "";} 
    ;

CallConnectors  : DCallArgsConn {$$.trad = $1.trad;}
                | /*epsilon*/ { }
    ;
DCallArgsConn   : TipoBase id opasig DcallArgsAux 
                {
                // TODO ERROR CHECKING THAT ID EXISTS AND TYPES ARE VALID
                int pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
                int pos_instance = tfs.v_funcSymbols.at(pos).searchInstance(s2, nlin, ncol);
                string pme_name = $2.lexeme;
                string pme_value = $4.trad;

                if ($4.ph == "io"){ 
                    int pos_inout = tfs.v_funcSymbols.at(pos).searchinoutSymbol(pme_value, nlin, ncol);
                    
                    string name_verilog = tfs.v_funcSymbols.at(pos).getInoutSymbol().at(pos_inout).getNameVerilog();
                    tfs.v_funcSymbols.at(pos).v_instances.at(pos_instance).addValueInoutSymbolParam(pme_name, name_verilog, $1.size, nlin,ncol);
                }
                else if ($4.ph == "w"){
                    string aux = "_w";
                    tfs.v_funcSymbols.at(pos).v_instances.at(pos_instance).addValueInoutSymbolParam(pme_name, pme_value+aux, $1.size, nlin,ncol);
                }

                }
                | DCallArgsConn coma TipoBase id opasig DcallArgsAux 
                {
                int pos = tfs.searchFunctionSymbol(s1, nlin, ncol);
                int pos_instance = tfs.v_funcSymbols.at(pos).searchInstance(s2, nlin, ncol);
                string pme_name = $4.lexeme;
                string pme_value = $6.trad;

                if ($6.ph == "io"){ 
                    int pos_inout = tfs.v_funcSymbols.at(pos).searchinoutSymbol(pme_value, nlin, ncol);
                    
                    string name_verilog = tfs.v_funcSymbols.at(pos).getInoutSymbol().at(pos_inout).getNameVerilog();
                    tfs.v_funcSymbols.at(pos).v_instances.at(pos_instance).addValueInoutSymbolParam(pme_name, name_verilog, $3.size, nlin,ncol);
                }
                else if ($6.ph == "w"){
                    string aux = "_w";
                    tfs.v_funcSymbols.at(pos).v_instances.at(pos_instance).addValueInoutSymbolParam(pme_name, pme_value+aux, $3.size, nlin,ncol);
                }
                }
    ;
DcallArgsAux  : TipoBase id
              {
                string pme = $2.lexeme;
                $$.trad = pme;
                $$.ph = "io";
              }
              | id
              {
                string pme = $1.lexeme;
                string aux = "_w";
                $$.ph = "w";
                $$.trad = pme;
                // check that the wire exists
                ts.shearchSymbol(pme+aux,s1,nlin,ncol);

              }

    ;

/* Expresion */
Arrayargs   : bral Expr {
                            if($2.type!=INTEGER){
                                msgError(ERRTYPEARGS, nlin, ncol, $2.trad.c_str());
                            }
                        } 
              twopoints Expr    {
                                    if($5.type!=INTEGER){
                                        msgError(ERRTYPEARGS, nlin, ncol, $5.trad.c_str());
                                    }
                                }
              brar {
                    string expr_1 = "";
                    string expr_2 = "";
                    if ($2.ph == to_string(DEFINITIONVERILOG)){
                        expr_1 = "`" + $2.trad;
                    }
                    else{
                        expr_1 = $2.trad;
                    }
                    if($5.ph == to_string(DEFINITIONVERILOG)){
                        expr_2 = "`" + $5.trad;
                    }
                    else{
                         expr_2 = $5.trad;
                    }
                    $$.trad = "[" + expr_1 + " : " + expr_2 + "]";
                    }
            | /*epsilon*/ {$$.trad = "";}
    ;
Expr    :   Econj   { 
                        $$.trad = $1.trad;
                        $$.type = $1.type;
                        $$.size = $1.size;
                        $$.ph = $1.ph;
                    } 
        |   Expr {
                    if($1.type!=LOGIC){
                        msgError(ERRTYPEBOOL, nlin, ncol, $1.trad.c_str());
                    }
                 }obool Econj   {
                                    if($4.type!=LOGIC){
                                        msgError(ERRTYPEBOOL, nlin, ncol, $4.trad.c_str());
                                    }
                                    $$.trad = $1.trad +" "+ $3.lexeme +" "+ $4.trad;
                                    $$.type = LOGIC;
                                    $$.size = LOGIC;
                                    $$.ph = $1.ph;
                                }
    ;
Econj   :   Ecomp { 
                    $$.trad = $1.trad;
                    $$.type = $1.type;
                    $$.size = $1.size;
                    $$.ph = $1.ph;
                  }
        |   Econj   {
                        if($1.type!=LOGIC){
                            msgError(ERRTYPEBOOL, nlin, ncol, $1.trad.c_str());
                        }
                    }ybool Ecomp   {
                                        if($4.type!=LOGIC){
                                            msgError(ERRTYPEBOOL, nlin, ncol, $4.trad.c_str());
                                        }
                                        $$.trad = $1.trad +" "+ $3.lexeme +" "+ $4.trad;
                                        $$.type = LOGIC;
                                        $$.size = LOGIC;
                                        $$.ph = $1.ph;
                                    }
    ;

Ecomp   : Esimple {
                        $$.trad = $1.trad;
                        $$.type = $1.type;
                        $$.size = $1.size;
                        $$.ph = $1.ph;
                  }
        | Esimple oprel Esimple {
                                        if($1.type!=$3.type){//TODO:what happen here with the strings
                                            string pme_1 = $1.lexeme;
                                            string pme_3 = $3.lexeme;
                                            string text = pme_1+ " type is " + to_string($1.type) + ". Does not match type of " + pme_3;
                                            msgError(ERRTYPEMISMATCH, nlin, ncol,text.c_str()); 
                                        }
                                        $$.trad = $1.trad + " " + $2.lexeme + " " + $3.trad;
                                        $$.type = $1.type;
                                    if ($1.size == INTEGER || $3.size == INTEGER){
                                        $$.size = INTEGER;
                                    }else{
                                        $$.size = REFERENCE;
                                    }
                                    $$.ph = $1.ph;
                                }
    ;
Esimple :Term {  
                    $$.trad = $1.trad;
                    $$.type = $1.type;
                    $$.size = $1.size;
                    $$.ph = $1.ph;
                 }
        |   Esimple     {
                            if($1.type!=INTEGER){
                                msgError(ERRTYPEINTEGER, nlin, ncol, $1.trad.c_str());
                            }
                        }
            opas Term   {
                            if($4.type!=INTEGER){
                                msgError(ERRTYPEINTEGER, nlin, ncol, $4.trad.c_str());
                            }
                            $$.trad = $1.trad +" "+ $3.lexeme +" "+ $4.trad;
                            if ($1.size == INTEGER || $4.size == INTEGER){
                                    $$.size = INTEGER;
                                }else{
                                    $$.size = REFERENCE;
                                }
                            
                        }
    ;
Term    :   Factor {$$.trad = $1.trad;
                    $$.type = $1.type;
                    $$.size = $1.size;
                    $$.ph = $1.ph;} 
        |   Term{
                    if($1.type!=INTEGER){
                        msgError(ERRTYPEINTEGER, nlin, ncol, $1.trad.c_str());
                    }
                } opmd Factor    {
                                    if($4.type!=INTEGER){
                                        msgError(ERRTYPEINTEGER, nlin, ncol, $4.trad.c_str());
                                    }
                                    $$.trad = $1.trad + $3.lexeme + $4.trad;
                                    $$.type = INTEGER;
                                    if ($1.size == INTEGER || $4.size == INTEGER){
                                        $$.size = INTEGER;
                                    }else{
                                        $$.size = REFERENCE;
                                    }
                                    $$.ph = $1.ph;
                                }
    ;
Factor  : Ref   {
                    int pos = ts.shearchSymbol($1.trad, s1, nlin,ncol);
                    int type = ts.v_symbols.at(pos).getType();
                    int type_v = ts.v_symbols.at(pos).getTypeVar();
                    switch(type){
                    case(DEFINITION)://DEFINITION=1
                        $$.trad = ts.v_symbols.at(pos).getValue_S();
                        break;
                    case(DEFINITIONVERILOG)://DEFINITIONVERILOG=2
                        $$.trad = ts.v_symbols.at(pos).getName();
                        break;
                    case(PARAMETERFUNCTION)://PARAMETERFUNCTION=5
                        $$.trad = ts.v_symbols.at(pos).getName();
                        break;
                    case(INSTANCESYMBOL)://INSTANCESYMBOL=7
                        $$.trad = ts.v_symbols.at(pos).getName();
                        break;
                    default: //VARIABE=3 FUNCTION=4 or someting else
                        msgError(ERRNEEDDEF, nlin, ncol, $1.trad.c_str());
                        break;
                    }
                    $$.type=type_v;
                    $$.ph = to_string(type);
                    $$.size = REFERENCE;
                }
        | ninteger  {
                        string pme = $1.lexeme;
                        $$.type=INTEGER;
                        $$.trad=pme;
                        $$.size = INTEGER;
                    }
        | parl Expr parr {  $$.trad="(" + $2.trad + ")";}
        | nobool Factor     {
                                if($2.type!=5){
                                    msgError(ERRFUNODEC, nlin, ncol, $2.trad.c_str());
                                }
                                $$.trad = "!" + $2.trad;
                                $$.type = $2.type;
                            }
        | booltokentrue     {
                                $$.type=LOGIC;
                                $$.trad="false";
                            }
        | booltokenfalse    {
                                $$.type=LOGIC;
                                $$.trad="true";
                            }
    ;
Ref     :   id {string pme = $1.lexeme; $$.trad = pme;}
    ;
/* Tipos */
TipoBase    : intype {$$.trad = "i"; $$.size = IN;}
            | outtype {$$.trad = "o";$$.size = OUT;} 
            | inouttype {$$.trad = "io";$$.size = INOUT;}
    ;

S       : SSuperblock SAFunc {$$.trad = $1.trad + $2.trad;
                                tfs.createFiles(projectFolder);
                                ts.printToFile(projectFolder);
                                if(tb && !itb){
                                    int pos = tfs.searchFunctionSymbol(name_function_main, nlin, ncol);
                                    tfs.v_funcSymbols.at(pos).createRunTest(ts.getVerilogDefig(),true,qtb,vtb);
                                }
                                else if(tb && itb){
                                    int pos = tfs.searchFunctionSymbol(name_function_main, nlin, ncol);
                                    tfs.v_funcSymbols.at(pos).createRunTest(ts.getVerilogDefig(),true,qtb,vtb);
                                    for (int i = 0; i <tfs.v_funcSymbols.size();++i) {
                                        if (i != pos ){
                                            tfs.v_funcSymbols.at(i).createRunTest(ts.getVerilogDefig(),false,qtb,vtb);
                                        }                   
                                    }
                                }
                            }
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
        /* GENERAL ERRORS */
         case ERRNODEC: fprintf(stderr, "Variable %s not declared\n",s);
            break;
         case ERRALDEC: fprintf(stderr, "Variable %s already declared\n",s);
            break;
          case ERRFUNODEC: fprintf(stderr, "Module %s not declared\n",s);
            break;
         case ERRFUNALDEC: fprintf(stderr, "Module %s already declared\n",s);
            break;
         case ERRNEEDBOOL: fprintf(stderr, "Bool required but %s founded\n",s);
            break;
         case ERRNEEDDEF: fprintf(stderr, "DEFINITION or DEFINITIONVERILOG needed but %s founded\n",s);
            break;
         case ERRORSIMALDEC: fprintf(stderr, "Simbol %s already defined\n",s);
            break;     
         case ERRORSIMBNODEC: fprintf(stderr, "Simbol %s not defined\n",s);
            break;
        /* MODULE ERRORS */
         case ERRCONNDEC: fprintf(stderr, "Connection %s already declared\n",s);
            break;
         case ERRCONNNODEC: fprintf(stderr, "Connection %s not declared\n",s);
            break;
         case ERRPARAMDEC: fprintf(stderr, "Param module %s already declared\n",s);
            break;
         case ERRPARAMNODEC: fprintf(stderr, "Param module %s not declared\n",s);
            break;
        /* MODULE DEFINTION ERRORS */
         case ERRFUNCDEFALDEC: fprintf(stderr, "Function module definition %s already declared\n",s);
            break;
         case ERRDESCDEFALDEC: fprintf(stderr, "Description module definition %s already declared\n",s);
            break;
         case ERRORCODDEFALDEC: fprintf(stderr, "Coder module definition %s already declared\n",s);
            break;
         case ERRORDEFIALDEC: fprintf(stderr, "References module definition %s already declared\n",s);
            break;
        /* MODULE SIGNAL ERRORS */
         case ERRTYPEARGS: fprintf(stderr, "%s ilegal type for port size\n",s);
            break;
         case ERRTYPEBOOL: fprintf(stderr, "%s ilegal type for bool operation\n",s);
            break;
         case ERRTYPEINTEGER: fprintf(stderr, "%s ilegal type for integer operation\n",s);
            break;
         case ERRTYPEMISMATCH: fprintf(stderr, "%s Logic comparation of different types\n",s);
            break;
        /* INSTANCE ERROR */
        case ERRINSNOTFOUND: fprintf(stderr, "Instance %s not declared\n",s);
            break;
        /* ARGUMENTS ERROR */
        case ERRARGUMENTPOSNONAME: fprintf(stderr, "positional argument %s in a name position argument\n",s);
            break;
        /* DEFAULT */
        default: fprintf(stderr, "Undefined error in  %s\n",s);
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
string init_output(bool a){
    string output;
    if (a){    
        output = "////////////////////////////////////////////////////////////////////////////////\n"+
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
        std::string("//                   THE DICKBUT RTL CONNECTION COMPILER                        \n")+
        std::string("//                 FOR NOT TO MAKE A DICKBUT RTL CONNECTIONS                    \n")+
        std::string("////////////////////////////////////////////////////////////////////////////////\n");
    }
    else{
        output ="";
    }
return output;
}

void print_usage(void)
{
    printf("Use: verilog_connector <filename>\n");
    printf("-h, --help, help        Print this message\n");
    printf("-V  --version           Print Version and exits\n");
    printf("-d                      Output directory name\n");
    printf("-n                      Set project name\n");
    printf("-t -q                   Make top test bench for questasim \n");
    printf("-t -v                   Make top test bench for verilator\n");
    printf("-t -q -i                Make top and individual test benches for questasim \n");
    printf("-t -v -i                Make top and individual test benches for verilator\n");
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
            //Ivan need this
            case 'Y' :
                db = true;
                break;
            case 't' :
                tb = true;
                break;
            case 'i' :
                itb = true;
                break;
            case 'v' :
                qtb = true;
                break;
            case 'q' :
                vtb = true;
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
    //Check if Verion flag
    for(int i=0; i<argc; ++i){
        if(!strcmp(argv[i],"-V") || !strcmp(argv[i],"--version")){
            printf("Skeletor version: %s", VERSION);
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
        else{
            fprintf(stderr,"File can not open\n");
            print_usage();
        }
    }
    else{
        fprintf(stderr,"Use: example <filename>\n");
        return(WRONG_ARGUMENTS);
    }        
}



