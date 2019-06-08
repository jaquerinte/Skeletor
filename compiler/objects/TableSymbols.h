#ifndef TABLESYMBOLS_H
#define TABLESYMBOLS_H


#include "Symbol.h"
#include <vector>
#include <iostream>
using namespace std;

class TableSymbols
{
	
public:
	TableSymbols();
	~TableSymbols();
	bool addSymbol(string name, int type, string module);
	bool addSymbol(string name, int type, string value,int type_var, string module);
	int shearchSymbol(string name, string module);
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