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
	FunctionSymbolParam(string name, int value);
	FunctionSymbolParam(const FunctionSymbolParam &In);
	~FunctionSymbolParam();
	FunctionSymbolParam& operator = (const FunctionSymbolParam &In);
	// getters
	string getName();
	int getValue();
	void setName(string name);
	void setValue(int value);

private:
	string name;
	int value;
	
};



#endif