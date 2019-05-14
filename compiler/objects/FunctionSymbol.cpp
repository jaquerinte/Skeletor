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

InoutSymbol& FunctionSymbol :: searchinoutSymbol(string name)
{
	InoutSymbol s;
	for (int i = 0; i <  this -> v_inoutwires.size();++i) {
		if ( this -> v_inoutwires.at(i).getName() == name) {
			return  this -> v_inoutwires.at(i);
		}
	}
	// fail: connection not declared
	//msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
	return s;
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

bool FunctionSymbol :: addValueFunctionSymbolParam(string name, int value)
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

bool FunctionSymbol :: addWireConnection(string function_in, InoutSymbol out, InoutSymbol in){
	WireSymbol wire(function_in, out, in);
	this -> v_wire.push_back(wire);
}


void FunctionSymbol :: createFileModule()
{
	/* Start wriking the file */
	/* Definition top file */
	this -> output_file_data = "//-----------------------------------------------------\n";
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
	this -> output_file_data +="//***Module***\n";
	/* Defining Module */
	if (this -> v_param.size() != 0){
		/* Module has param*/
		this -> output_file_data += "module " + this -> name + " #(\n";
		// Loop over param
		for (int i = 0; i < this -> v_param.size();++i) {
			if (i == this -> v_param.size() -1){
				/* Last parameter */
				this -> output_file_data += "\t\tparameter integer " + this -> v_param.at(i).getName() + " = " + to_string(this -> v_param.at(i).getValue()) + "\n";
			}
			else{
				/* Rest parameter */
				this -> output_file_data += "\t\tparameter integer " + this -> v_param.at(i).getName() + " = " + to_string(this -> v_param.at(i).getValue()) + ",\n";
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
	/* Putin some extra coments */
	this -> output_file_data += "//***Interal logic generated by compiler***  \n";
	this -> output_file_data += "//***Handcrafted Internal logic*** \n";
	this -> output_file_data += "//TODO\n";
	/* finish file */
	this -> output_file_data += "endmodule\n";
}

void FunctionSymbol :: createFileModule(string base)
{
	/* Start wriking the file */
	this -> output_file_data = base;
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
	this -> output_file_data +="//***Module***\n";
	/* Defining Module */
	if (this -> v_param.size() != 0){
		/* Module has param*/
		this -> output_file_data += "module " + this -> name + " #(\n";
		// Loop over param
		for (int i = 0; i < this -> v_param.size();++i) {
			if (i == this -> v_param.size() -1){
				/* Last parameter */
				this -> output_file_data += "\t\tparameter integer " + this -> v_param.at(i).getName() + " = " + to_string(this -> v_param.at(i).getValue()) + "\n";
			}
			else{
				/* Rest parameter */
				this -> output_file_data += "\t\tparameter integer " + this -> v_param.at(i).getName() + " = " + to_string(this -> v_param.at(i).getValue()) + ",\n";
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
			this -> output_file_data += "\t\t " + type + " " + this -> v_inoutwires.at(i).getWith() + " " + this -> v_inoutwires.at(i).getNameVerilog(); + "\n";
		}
		else{
			/* Rest INOUT parameter */
			this -> output_file_data += "\t\t " + type + " " + this -> v_inoutwires.at(i).getWith() + " " + this -> v_inoutwires.at(i).getNameVerilog(); + ",\n";
		}
	}
	/* End inputs and outputs */
	this -> output_file_data += "\t);\n";
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
