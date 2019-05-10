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
	bool addSymbol(string name, int type, string value);
	int shearchSymbol(string name);
	string getTableSymbols();
	vector<Symbol> v_symbols;
	
};



#endif