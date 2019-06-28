#ifndef TABLESYMBOLS_H
#define TABLESYMBOLS_H


#include "Symbol.h"
#include <vector>
#include <iostream>
#include "../common.h"
using namespace std;

class TableSymbols
{
	
public:
	TableSymbols();
	~TableSymbols();
	bool addSymbol(string name, int type, string module, int nlin, int ncol);
	bool addSymbol(string name, int type, string value,int type_var, string module, int nlin, int ncol);
	int shearchSymbol(string name, string module, int nlin, int ncol);
	string getTableSymbols();
	bool createDefinitions();
	bool getVerilogDefig();
	void printToFile(string projectFolder);
	vector<Symbol> v_symbols;

private:
	string output_file_data;
	bool verilogDefig;
};



#endif