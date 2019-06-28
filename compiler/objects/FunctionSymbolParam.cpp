#include "FunctionSymbolParam.h"

FunctionSymbolParam :: FunctionSymbolParam()
{
	this -> name = "null";
	this -> value = "1";
	this -> type = 0;
}

FunctionSymbolParam :: FunctionSymbolParam(string name)
{
	this -> name = name;
	this -> value = "1";
	this -> type = 0;
}
FunctionSymbolParam :: FunctionSymbolParam(string name, string value, int type)
{
	this -> name = name;
	this -> value = value;
	this -> type = type;
}

FunctionSymbolParam :: FunctionSymbolParam(const FunctionSymbolParam &In)
{
	this -> name = In.name;
	this -> value = In.value;
	this -> type = In.type;
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
int FunctionSymbolParam :: getType(){return this -> type;}
void FunctionSymbolParam :: setName(string name) {this -> name = name;}
void FunctionSymbolParam :: setValue(string value) {this -> value = value;}