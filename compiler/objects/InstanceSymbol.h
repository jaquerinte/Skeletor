#ifndef INSTANCESYMBOL_H
#define INSTANCESYMBOL_H

#include <string.h>
#include <string>
#include <vector>


#include "FunctionSymbolParam.h"
#include "WireSymbol.h"

class InstanceSymbol
{
public:
	InstanceSymbol();
	InstanceSymbol(vector<InoutSymbol> v_inoutwires, vector<FunctionSymbolParam> v_param, vector<WireSymbol> v_wire, string nameModule,string nameInstance);
	InstanceSymbol(const InstanceSymbol &In);
	~InstanceSymbol();

	InstanceSymbol& operator = (const InstanceSymbol &In);
	string getName();
	string getNameInstance();
	string generateInstance();

private:
	string nameModule;
	string nameInstance;
	vector<InoutSymbol> v_inoutwires; // of the module to connect
	vector<FunctionSymbolParam> v_param; // of the module to connect
	vector<WireSymbol> v_wire; // of the actual module that is calling
	
};

#endif