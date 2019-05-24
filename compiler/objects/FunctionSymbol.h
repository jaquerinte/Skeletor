#ifndef FUNCTIONSYMBOL_H
#define FUNCTIONSYMBOL_H

#include <string.h>
#include <string>
#include <vector>


#include "FunctionSymbolParam.h"
#include "WireSymbol.h"

using namespace std;


class FunctionSymbol
{
public:

	FunctionSymbol();
    FunctionSymbol(string name, string projectName, string projectFolder);
	FunctionSymbol(const FunctionSymbol &In);
	~FunctionSymbol();
	FunctionSymbol& operator = (const FunctionSymbol &In);

	bool addConnectionFunctionSymbol(string name, int size, string with);
	int searchinoutSymbol(string name);
	int searchinoutSymbol(string name, int type);
	bool addFunctionSymbolParam(string name);
	bool addFunctionSymbolParam(string name, string vale, int type);
	bool addValueFunctionSymbolParam(string name, string value);
	void addValueFunctionSymbolParamPos(int pos, string value);
	FunctionSymbolParam& searchFunctionSymbolParam(string name);

	bool addWireConnection(string function_out, string function_in, int out, int in,string with_out);

	void createFileModule();
	void createFileModule(string base, bool verilog_def);
	void printToFile();

	// getters

	string getName();
	string getFilenameAsociated();
	string getFunction();
	string getDescription();
	string getCode();
	string getProjectName();
	string getReferences();
	string getOutputFileData();

	//setters

	void setName(string name);
	void setFunction(string function);
	void setDescription(string description);
	void setCode(string code);
	void setProjectName(string projectName);
	void setReferences(string references);

private:
	void createFileModuleDefines();
	void createFileModuleBase();
	string name;
	vector<InoutSymbol> v_inoutwires;
	vector<FunctionSymbolParam> v_param;
	vector<WireSymbol> v_wire;
	string filename_asociated;
	string function;
	string description;
	string code;
	string projectName;
	string references;
	string output_file_data;
	
};



#endif
