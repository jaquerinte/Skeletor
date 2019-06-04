#ifndef FUNCTIONSYMBOLPARAM_H
#define FUNCTIONSYMBOLPARAM_H

#include <string.h>
#include <string>
#include <vector>
using namespace std;


class FunctionSymbolParam
{

public:
	FunctionSymbolParam();
	FunctionSymbolParam(string name);
	FunctionSymbolParam(string name, string value, int type);
	FunctionSymbolParam(const FunctionSymbolParam &In);
	~FunctionSymbolParam();
	FunctionSymbolParam& operator = (const FunctionSymbolParam &In);
	// getters
	string getName();
	string getValue();
	int getType();
	void setName(string name);
	void setValue(string value);

private:
	string name;
	string value;
	int type;
	
};



#endif
