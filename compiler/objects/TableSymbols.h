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
	bool addSymbol(string name, int type);
	bool addSymbol(string name, int type, string value,int type_var);
	int shearchSymbol(string name);
	string getTableSymbols();
	bool createDefinitions();
	void printToFile(string projectFolder);
	vector<Symbol> v_symbols;

private:
	string output_file_data;
	bool verilogDefig;
};



#endif