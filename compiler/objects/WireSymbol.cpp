#include "WireSymbol.h"

WireSymbol :: WireSymbol(){
	this -> function_in = "";
	this -> in = InoutSymbol();
	this -> out = InoutSymbol();

}
WireSymbol ::WireSymbol(string function_in, InoutSymbol out, InoutSymbol in){
	this -> function_in = function_in;
	this -> out = out;
	this -> in = in;
}
WireSymbol ::~WireSymbol(){}
WireSymbol ::WireSymbol(const WireSymbol &In){
	this -> function_in = In.function_in;
	this -> out = In.out;
	this -> in = In.in;

}
WireSymbol& WireSymbol ::operator = (const WireSymbol &In){
	if(this != &In)
    {
		WireSymbol(In);
    	return *this;
	}
}