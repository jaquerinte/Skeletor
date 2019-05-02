#include "FunctionSymbolParam.h"

FunctionSymbolParam :: FunctionSymbolParam()
{
	this -> name = "null";
	this -> value = -1;
}

FunctionSymbolParam :: FunctionSymbolParam(string name)
{
	this -> name = name;
	this -> value = -1;
}

FunctionSymbolParam :: FunctionSymbolParam(string name, int value)
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
int FunctionSymbolParam :: getValue(){return this -> value;}
void FunctionSymbolParam :: setName(string name) {this -> name = name;}
void FunctionSymbolParam :: setValue(int value) {this -> value = value;}