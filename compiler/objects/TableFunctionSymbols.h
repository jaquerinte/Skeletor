#ifndef TABLEFUNCTIONSYMBOLS_H
#define TABLEFUNCTIONSYMBOLS_H

#include <string.h>
#include <string>
#include <vector>

#include "FunctionSymbol.h"

using namespace std;

class TableFunctionSymbols
{
public:
	TableFunctionSymbols();
	~TableFunctionSymbols();
	bool addFunctionSymbol(string name, string proyectName);
	int searchFunctionSymbol(string name);
	void createFiles();
	vector<FunctionSymbol> v_funcSymbols;
	
};






#endif