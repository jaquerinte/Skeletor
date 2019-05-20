#include "WireSymbol.h"

WireSymbol :: WireSymbol(){
	this -> function_out = "";
	this -> function_in = "";
	this -> pos_out = -1;
	this -> pos_in = -1;

}
WireSymbol :: WireSymbol(string function_out, string function_in ,int pos_out, int pos_in){
	this -> function_out = function_out;
	this -> function_in = function_in;
	this -> pos_out = pos_out;
	this -> pos_in = pos_in;
}
WireSymbol :: ~WireSymbol(){}
WireSymbol :: WireSymbol(const WireSymbol &In){
	this -> function_out = In.function_out;
	this -> function_in = In.function_in;
	this -> pos_out = In.pos_out;
	this -> pos_in = In.pos_in;

}
WireSymbol& WireSymbol :: operator = (const WireSymbol &In){
	if(this != &In)
    {
		WireSymbol(In);
    	return *this;
	}
}

string WireSymbol :: getFuncionOut(){return this -> function_out;}
string WireSymbol :: getFuncionIn(){return this -> function_in;}
int WireSymbol :: getInoutSymbolOut(){return this -> pos_out;}
int WireSymbol :: getInoutSymbolIn(){return this -> pos_in;}

