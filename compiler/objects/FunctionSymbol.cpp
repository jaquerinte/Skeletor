#include "FunctionSymbol.h"
#include <iostream>

FunctionSymbol :: FunctionSymbol()
{
	this -> name = "null";
	this -> function = "";
	this -> description = "";
	this -> code = "";
	this -> projectName = "";
	this -> filename_asociated = "./output/" + name + ".v";
	this -> output_file_data = "";
}


FunctionSymbol :: FunctionSymbol(string name, string projectName, string projectFolder)
{
	this -> name = name;
	this -> function = "";
	this -> description = "";
	this -> code = "";
	this -> projectName = projectName;
	this -> filename_asociated = "./" + projectFolder + "/" + name + ".v";
	//this -> filename_asociated = "./objects/" + name + ".v";
	this -> output_file_data = "";
}

FunctionSymbol :: FunctionSymbol(const FunctionSymbol &In)
{
	this -> name = In.name;
	this -> function = In.function;
	this -> description = In.description;
	this -> code = In.code;
	this -> projectName = In.projectName;
    this -> filename_asociated = In.filename_asociated;
    this -> output_file_data = In.output_file_data;
	this -> v_inoutwires = In.v_inoutwires;
	this -> v_param = In.v_param;
	this -> v_wire = In.v_wire;
}
FunctionSymbol :: ~FunctionSymbol(){}

FunctionSymbol& FunctionSymbol :: operator = (const FunctionSymbol &In)
{
	if(this != &In)
    {
		FunctionSymbol(In);
		return *this;
	}
}


bool FunctionSymbol :: addConnectionFunctionSymbol(string name, int size, string with)
{
	InoutSymbol s(name, size, with);
	for (int i = 0; i < this -> v_inoutwires.size();++i) {
		if (this -> v_inoutwires.at(i).getName() == s.getName()) { 
			// fail: connection alrady declared
			//msgError(ERRCONNDEC, nlin, ncol - name.length(), name.c_str());
			return false;
		}
	}
	this -> v_inoutwires.push_back(s);
	return true;

}

int FunctionSymbol :: searchinoutSymbol(string name)
{
	for (int i = 0; i <  this -> v_inoutwires.size();++i) {
		if ( this -> v_inoutwires.at(i).getName() == name) {
			return  i;
		}
	}
	// fail: connection not declared
	//msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
	return -1;
}


int FunctionSymbol :: searchinoutSymbol(string name, int type)
{
	for (int i = 0; i <  this -> v_inoutwires.size();++i) {
		if ( this -> v_inoutwires.at(i).getName() == name) {
			if (v_inoutwires.at(i).getType() == type || v_inoutwires.at(i).getType() == INOUT){
				return  i;
			}
			else{
				return -1;
			}
			
		}
	}
	// fail: connection not declared
	//msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
	return -1;
}

bool FunctionSymbol :: addFunctionSymbolParam(string name)
{
	FunctionSymbolParam s(name);
	for (int i = 0; i < this -> v_param.size();++i) {
		if (this ->  v_param.at(i).getName() == s.getName()) { 
			// fail: Symbol param  already declared
			//msgError(ERRPARAMDEC, nlin, ncol - name.length(), name.c_str());
			return false;
		}
	}
	this -> v_param.push_back(s);
	return true;
}

bool FunctionSymbol :: addFunctionSymbolParam(string name, string value)
{
	FunctionSymbolParam s(name, value);
	for (int i = 0; i < this -> v_param.size();++i) {
		if (this ->  v_param.at(i).getName() == s.getName()) { 
			// fail: Symbol param  already declared
			//msgError(ERRPARAMDEC, nlin, ncol - name.length(), name.c_str());
			return false;
		}
	}
	this -> v_param.push_back(s);
	return true;
}

bool FunctionSymbol :: addValueFunctionSymbolParam(string name, string value)
{
	FunctionSymbolParam s(name);
	for (int i = 0; i < this -> v_param.size();++i) {
		if (this -> v_param.at(i).getName() == s.getName()) { 
			this -> v_param.at(i).setValue(value);
			return true;
		}
	}
	// fail: Symbol param  not declared
	//msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
	return false;
}

void FunctionSymbol :: addValueFunctionSymbolParamPos(int pos, string value)
{
	if (pos < v_param.size()){
		this -> v_param.at(pos).setValue(value);
	}
	
}

FunctionSymbolParam& FunctionSymbol :: searchFunctionSymbolParam(string name)
{
	FunctionSymbolParam s;
	for (int i = 0; i < this -> v_param.size();++i) {
		if (this -> v_param.at(i).getName() == s.getName()) { 
			return this -> v_param.at(i);
		}
	}
	// fail: Symbol param  not declared
	//msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
	return s;
}

bool FunctionSymbol :: addWireConnection(string function_out, string function_in, int pos_out, int pos_in, string with_out){
	WireSymbol wire(function_out,function_in, pos_out, pos_in,with_out);
	//cout << "wire " << wire.getFuncionOut() << " " << wire.getFuncionIn() << " " << wire.getInoutSymbolOut().getName() << " " << wire.getInoutSymbolIn().getName();
	this -> v_wire.push_back(wire);
}

void FunctionSymbol :: createFileModule()
{
	/* Start wriking the file */
	this -> createFileModuleDefines();
	this -> createFileModuleBase();
}

void FunctionSymbol :: createFileModule(string base, bool verilogDef)
{
	/* Start wriking the file */
	this -> output_file_data += base;
	this -> createFileModuleDefines();
	/* DEFINES */
	if (verilogDef){
		this -> output_file_data += "`include \"defines.vh\"\n";
	}

	/* Continue */
	this -> createFileModuleBase();
}

void FunctionSymbol :: createFileModuleDefines(){
	
	/* Definition top file */
	this -> output_file_data += "//-----------------------------------------------------\n";
	this -> output_file_data += "// Project Name : " + this -> projectName + "\n";

	if (this -> function != ""){
		this -> output_file_data += "// Function     : " + this -> function + "\n";
	}
	if (this -> description != ""){
		this -> output_file_data += "// Description  : " + this -> description + "\n";
	}
	if (this -> code != ""){
		this -> output_file_data += "// Coder        : " + this -> code + "\n";
	}
	if (this -> references != ""){
		this -> output_file_data += "// References   : " + this -> references + "\n";
	}
	this -> output_file_data += "\n";
	this -> output_file_data += "//***Headers***\n";
}
void FunctionSymbol ::createFileModuleBase(){
	this -> output_file_data +="//***Module***\n";
	/* Defining Module */
	if (this -> v_param.size() != 0){
		/* Module has param*/
		this -> output_file_data += "module " + this -> name + " #(\n";
		// Loop over param
		for (int i = 0; i < this -> v_param.size();++i) {
			if (i == this -> v_param.size() -1){
				/* Last parameter */
				this -> output_file_data += "\t\tparameter integer " + this -> v_param.at(i).getName() + " = " + this -> v_param.at(i).getValue() + "\n";
			}
			else{
				/* Rest parameter */
				this -> output_file_data += "\t\tparameter integer " + this -> v_param.at(i).getName() + " = " + this -> v_param.at(i).getValue() + ",\n";
			}
		}
		this -> output_file_data += "\t)\n\t(\n";
	}
	else{
		/* Module has not param*/
		this -> output_file_data += "module " + this -> name + " (\n";
	}
	/* copy the inputs and outputs*/
	for (int i = 0; i < this -> v_inoutwires.size();++i) {
		string type = "";
			if (this -> v_inoutwires.at(i).getType() == IN){
				type = "input";
			}
			else if (this -> v_inoutwires.at(i).getType() == OUT){
				type = "output";
			}
			else if (this -> v_inoutwires.at(i).getType() == INOUT){
				type = "inout";
			}
		if (i == this -> v_inoutwires.size() -1){
			/* Last INOUT parameter */
			this -> output_file_data += "\t\t " + type + " " + this -> v_inoutwires.at(i).getWith() + " " + this -> v_inoutwires.at(i).getNameVerilog() + "\n";
		}
		else{
			/* Rest INOUT parameter */
			this -> output_file_data += "\t\t " + type + " " + this -> v_inoutwires.at(i).getWith() + " " + this -> v_inoutwires.at(i).getNameVerilog() + ",\n";
		}
	}
	/* End inputs and outputs */
	this -> output_file_data += "\t);\n";

	/* Add Wires */
	for (int i = 0; i < this -> v_wire.size(); ++i){
		int pos_out = v_wire.at(i).getInoutSymbolOut();
		int pos_in = v_wire.at(i).getInoutSymbolIn();
		string with = "";
		if (v_wire.at(i).getWithOut() != ""){
			with = v_wire.at(i).getWithOut() + " ";
		}
		this -> output_file_data += "\t wire " + with + v_inoutwires.at(pos_out).getName() + "_" + v_wire.at(i).getFuncionOut() + "_" + v_wire.at(i).getFuncionIn() + ";";
		this -> output_file_data += " // wiring between " + v_inoutwires.at(pos_out).getNameVerilog() + " of module " + v_wire.at(i).getFuncionOut() + " and " + v_inoutwires.at(pos_in).getNameVerilog() + " of module " + v_wire.at(i).getFuncionIn();
		this -> output_file_data += "\n";
	}

	/* Putin some extra coments */
	this -> output_file_data += "//***Interal logic generated by compiler***  \n";
	this -> output_file_data += "//***Handcrafted Internal logic*** \n";
	this -> output_file_data += "//TODO\n";
	/* finish file */
	this -> output_file_data += "endmodule\n";
}

void FunctionSymbol :: printToFile()
{
	/* create file */
	char buf[0x100];
	snprintf(buf, sizeof(buf), "%s", this -> filename_asociated.c_str());
	FILE *f = fopen(buf, "w");
	fprintf(f, this -> output_file_data.c_str());
	fclose(f);

}

string FunctionSymbol :: getName(){return this -> name;}
string FunctionSymbol :: getFilenameAsociated(){return this -> filename_asociated;}
string FunctionSymbol :: getFunction() {return this -> function;}
string FunctionSymbol :: getDescription() {return this -> description;}
string FunctionSymbol :: getCode() {return this -> code;}
string FunctionSymbol :: getProjectName() {return this -> projectName;}
string FunctionSymbol :: getReferences() {return this -> references;}
string FunctionSymbol :: getOutputFileData() {return this -> output_file_data;};

//setters

void FunctionSymbol :: setName(string name){ this -> name = name;}
void FunctionSymbol :: setFunction(string function) { this -> function = function;}
void FunctionSymbol :: setDescription(string description) { this -> description = description;}
void FunctionSymbol :: setCode(string code) { this -> code = code;}
void FunctionSymbol :: setProjectName(string projectName) { this -> projectName = projectName;}
void FunctionSymbol :: setReferences(string references) { this -> references = references;}
