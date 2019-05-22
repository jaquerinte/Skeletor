#include "FunctionSymbolParam.h"

FunctionSymbolParam :: FunctionSymbolParam()
{
	this -> name = "null";
	this -> value = "-1";
}

FunctionSymbolParam :: FunctionSymbolParam(string name)
{
	this -> name = name;
	this -> value = "-1";
}

FunctionSymbolParam :: FunctionSymbolParam(string name, string value)
{
	this -> name = name;
	this -> value = value;
}

FunctionSymbolParam :: FunctionSymbolParam(const FunctionSymbolParam &In)
{
	this -> name = In.name;
	this -> value = In.value;
}

FunctionSymbolParam ::  ~FunctionSymbolParam(){}

FunctionSymbolParam& FunctionSymbolParam :: operator = (const FunctionSymbolParam &In)
{
	if(this != &In)
    {
		FunctionSymbolParam(In);
    	return *this;
	}
}
// getters
string FunctionSymbolParam :: getName(){return this -> name;}
string FunctionSymbolParam :: getValue(){return this -> value;}
void FunctionSymbolParam :: setName(string name) {this -> name = name;}
void FunctionSymbolParam :: setValue(string value) {this -> value = value;}