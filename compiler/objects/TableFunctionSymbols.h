#ifndef TABLEFUNCTIONSYMBOLS_H
#define TABLEFUNCTIONSYMBOLS_H

#include <string.h>
#include <string>
#include <vector>

#include "FunctionSymbol.h"
#include "../common.h"

using namespace std;

class TableFunctionSymbols
{
public:
	TableFunctionSymbols();
	~TableFunctionSymbols();
	bool addFunctionSymbol(string name, string projectName, string projectFolder, int nlin,int ncol);
	bool addTopFunctionSymbol(string name, string projectName, string projectFolder, int nlin,int ncol);
	int searchFunctionSymbol(string name, int nlin,int ncol);
	void createFiles(string projectFolder);
	void createFilesKicat(string projectFolder);
	vector<FunctionSymbol> v_funcSymbols;
	
};






#endif
