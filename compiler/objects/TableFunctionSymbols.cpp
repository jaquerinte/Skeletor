#include "TableFunctionSymbols.h"

TableFunctionSymbols :: TableFunctionSymbols(){}

TableFunctionSymbols :: ~TableFunctionSymbols(){}

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
int TableFunctionSymbols :: searchFunctionSymbol(string name)
{
	for (int i = 0; i < v_funcSymbols.size();++i) {
		if (v_funcSymbols.at(i).getName() == name) {
			return i;
		}
	}
	// fail: func var no decl
	//msgError(ERRFUNODEC, nlin, ncol - name.length(), name.c_str());
	return 0;
}
void TableFunctionSymbols :: createFiles()
{
	for (int i = 0; i < v_funcSymbols.size();++i) {
		v_funcSymbols.at(i).printToFile();
	}

}