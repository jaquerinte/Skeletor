#include "TableFunctionSymbols.h"

bool TableFunctionSymbols :: addFunctionSymbol(string name, string proyectName)
{
	FunctionSymbol s(name,proyectName);
	for (int i = 0; i < v_funcSymbols.size();++i) {
		if (v_funcSymbols.at(i).getName() == s.getName()) { 
			// fail: func var ya decl
			//msgError(ERRFUNALDEC, nlin, ncol - name.length(), name.c_str());
			return false;
		}
	}
	v_funcSymbols.push_back(s);
	return true;
}
FunctionSymbol& TableFunctionSymbols :: searchFunctionSymbol(string name)
{
	FunctionSymbol s;
	for (int i = 0; i < v_funcSymbols.size();++i) {
		if (v_funcSymbols.at(i).getName() == name) {
			return v_funcSymbols.at(i);
		}
	}
	// fail: func var no decl
	//msgError(ERRFUNODEC, nlin, ncol - name.length(), name.c_str());
	return s;
}