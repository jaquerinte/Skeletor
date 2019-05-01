#ifndef FUNCTIONSYMBOL_H
#define FUNCTIONSYMBOL_H

#include <string.h>
#include <string>
#include <vector>

#include "InoutSymbol.h"
#include "FunctionSymbolParam.h"

using namespace std;

class FunctionSymbol
{
public:

	FunctionSymbol();
	FunctionSymbol(string name, string proyectName);
	FunctionSymbol(const FunctionSymbol &In);
	~FunctionSymbol();
	FunctionSymbol& operator = (const FunctionSymbol &In);

	InoutSymbol searchinoutSymbol(string name);
	bool addConnectionFunctionSymbol(string name,  int type, string with);
	bool addFunctionSymbolParam(string name);
	bool addValueFunctionSymbolParam(string name, int value);
	FunctionSymbolParam searchFunctionSymbolParam(string name);

private:
	string name;
	vector<InoutSymbol> v_inoutwires;
	vector<FunctionSymbolParam> v_param;
	string filename_asociated;
	string function;
	string description;
	string code;
	string proyectName;
	string references;
	string output_file_data;
	
};



#endif