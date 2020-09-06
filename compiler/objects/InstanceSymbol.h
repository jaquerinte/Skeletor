#ifndef INSTANCESYMBOL_H
#define INSTANCESYMBOL_H

#include <string.h>
#include <string>
#include <vector>


#include "FunctionSymbolParam.h"
#include "../kicatobjects/InstanceComponentFunctionSymbol.h"
#include "../kicatobjects/ComponentLabel.h"
#include "WireSymbol.h"
#include "VWireSymbol.h"
#include "../common.h"


//TODO:Put this in a better place. Set tab format with flags
//style parameters
extern string tabulate;
class InstanceSymbol
{
public:
	InstanceSymbol();
	InstanceSymbol(vector<InoutSymbol> v_inoutwires, vector<FunctionSymbolParam> v_param, vector<WireSymbol> v_wire ,string nameModule,string nameInstance);
	InstanceSymbol(const InstanceSymbol &In);
	~InstanceSymbol();
	string addValueInoutSymbolParam(string name, string value, int type, int nlin, int ncol);
	bool addValueFunctionSymbolParam(string name, string value, int nlin, int ncol);
	void addValueFunctionSymbolParamPos(int pos, string value);
	int searchinoutSymbol(string name, int type, int nlin, int ncol);

	InstanceSymbol& operator = (const InstanceSymbol &In);
	string getName();
	string getNameInstance();
	string generateInstance();
	string generateLabels(std::map<string, ComponentLabel> base, vector<string> values_fullfill, bool isLeaf, bool isTop);
	string getNameInstanceVerilog();
	InstanceComponentFunctionSymbol* instancenDesig;

	vector<WireSymbol> v_wire; // of the actual module that is calling
	vector<InoutSymbol> v_inoutwires; // of the module to connect

private:
	string nameModule;
	string nameInstance;
	string nameInstanceVerilog;
	vector<FunctionSymbolParam> v_param; // of the module to connect
    string currentspace(string a, int max);
    int getmaxNameVerilog();
};

#endif
