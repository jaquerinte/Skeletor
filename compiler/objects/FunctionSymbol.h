#ifndef FUNCTIONSYMBOL_H
#define FUNCTIONSYMBOL_H


#include "InstanceSymbol.h"
#include "../common.h"
#include <sys/stat.h> 

using namespace std;


class FunctionSymbol
{
public:

	FunctionSymbol();
    FunctionSymbol(string name, string projectName, string projectFolder);
	FunctionSymbol(const FunctionSymbol &In);
	~FunctionSymbol();
	FunctionSymbol& operator = (const FunctionSymbol &In);

	bool addConnectionFunctionSymbol(string name, int size, string width,int nlin,int ncol);
	int searchinoutSymbol(string name, int nlin,int ncol);
	int searchinoutSymbol(string name, int type,int nlin,int ncol);
	bool addFunctionSymbolParam(string name, int nlin,int ncol);
	bool addFunctionSymbolParam(string name, string vale, int type, int nlin,int ncol);
	bool addValueFunctionSymbolParam(string name, string value,int nlin,int ncol);
	void addValueFunctionSymbolParamPos(int pos, string value, int nlin,int ncol);
	FunctionSymbolParam& searchFunctionSymbolParam(string name, int nlin,int ncol);

	bool addWireConnection(string function_out, string function_in, int pos_out, int pos_in, string width_out, string name_wire, string out_name, string in_name);
	bool addWireConnection(string function_out, string function_in, int pos_out, int pos_in, string width_out, string name_wire, string out_name, string in_name, bool print);
	bool addVWireConnection(string width_out, string name_wire);
	bool addInstance(vector<InoutSymbol> v_inoutwires, vector<FunctionSymbolParam> v_param, string name_module, string name_instance);
	int searchInstance(string name, int nlin,int ncol);
	
	void createFileModule(bool verilogDef);
	void createFileModule(string base, bool verilog_def);
	void createRunTest(bool definitions, bool first, bool qtb, bool vtb, bool avb);
	void printToFile();

    void addVerilogDump(const string dump);

	// getters

	string getName();
	string getFilenameAsociated();
	string getFunction();
	string getDescription();
	string getCode();
	string getProjectName();
	string getReferences();
	string getOutputFileData();
	vector<FunctionSymbolParam> getFunctionSymbolParam();
	vector<InoutSymbol> getInoutSymbol();

	//setters

	void setName(string name);
	void setFunction(string function);
	void setDescription(string description);
	void setCode(string code);
	void setProjectName(string projectName);
	void setReferences(string references);

	vector<InstanceSymbol> v_instances;

private:
	void createTbQuesta(bool definitions);
	void createTbFolder();
    void createQuestaSimFolder();
    void createVerilatorFolder();
    void createTbRunVerilator(bool first);
    void createTbRunQuesta(bool first);
    void createTbVerilator(bool first, bool avb);
	void createFileModuleDefines();
	void createFileModuleBase();
	string name;
	vector<InoutSymbol> v_inoutwires;
	vector<FunctionSymbolParam> v_param;
	vector<WireSymbol> v_wire;
	vector<VWireSymbol> v_vwire;
	string filename_asociated;
	string function;
	string description;
	string code;
	string projectFolderName;
	string projectName;
	string references;
	string output_file_data;
	string projectFolder;
	string verilog_dump;
	
};



#endif
