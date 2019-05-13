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
	bool addFunctionSymbol(string name, string projectName, string projectFolder);
	int searchFunctionSymbol(string name);
	void createFiles(string projectFolder);
	vector<FunctionSymbol> v_funcSymbols;
	
};






#endif
