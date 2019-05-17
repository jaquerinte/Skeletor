#include "WireSymbol.h"

WireSymbol :: WireSymbol(){
	this -> function_out = "";
	this -> function_in = "";
	this -> in = InoutSymbol();
	this -> out = InoutSymbol();

}
WireSymbol :: WireSymbol(string function_out, string function_in ,InoutSymbol &out, InoutSymbol &in): out(out), in(in){
	this -> function_out = function_out;
	this -> function_in = function_in;
	//this -> out = out;
	//this -> in = in;
}
WireSymbol :: ~WireSymbol(){}
WireSymbol :: WireSymbol(const WireSymbol &In): out(In.out), in(In.in){
	this -> function_out = In.function_out;
	this -> function_in = In.function_in;
	//this -> out = In.out;
	//this -> in = In.in;

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
InoutSymbol& WireSymbol :: getInoutSymbolOut(){return this -> out;}
InoutSymbol& WireSymbol :: getInoutSymbolIn(){return this -> in;}

