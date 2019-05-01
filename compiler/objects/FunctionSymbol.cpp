#include "FunctionSymbol.h"


FunctionSymbol :: FunctionSymbol()
{
	this -> name = "null";
	this -> function = "";
	this -> description = "";
	this -> code = "";
	this -> proyectName = "";
	this -> filename_asociated = name + ".v";
	this -> output_file_data = "";
}


FunctionSymbol :: FunctionSymbol(string name, string proyectName)
{
	this -> name = name;
	this -> function = "";
	this -> description = "";
	this -> code = "";
	this -> proyectName = proyectName;
	this -> filename_asociated = name + ".v";
	this -> output_file_data = "";
}

FunctionSymbol :: FunctionSymbol(const FunctionSymbol &In)
{
	this -> name = In.name;
	this -> function = In.function;
	this -> description = In.description;
	this -> code = In.code;
	this -> proyectName = In.proyectName;
	this -> filename_asociated = In.filename_asociated;
	this -> output_file_data = In.output_file_data;
}

FunctionSymbol& FunctionSymbol :: operator = (const FunctionSymbol &In)
{
	if(this != &In)
    {
		FunctionSymbol(In);
		return *this;
	}
}