#include "TableFunctionSymbols.h"
#include <bits/stdc++.h> 
#include <iostream> 
#include <sys/stat.h> 
#include <sys/types.h> 

TableFunctionSymbols :: TableFunctionSymbols(){}

TableFunctionSymbols :: ~TableFunctionSymbols(){}

bool TableFunctionSymbols :: addFunctionSymbol(string name, string projectName, string projectFolder)

{
	FunctionSymbol s(name, projectName, projectFolder );
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

//TableFunctionSymbols añadir una nueva carpeta
void TableFunctionSymbols :: createFiles(string projectFolder)
{
	// Creating a directory 
	if (mkdir(projectFolder.c_str(), 0777) == -1) 
		cerr << "Error : " << strerror(errno) << endl; 
	
    for (int i = 0; i < v_funcSymbols.size();++i) {
		//mandarlo a la carpeta
        v_funcSymbols.at(i).printToFile();
	}

}
