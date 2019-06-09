#include "InstanceSymbol.h"
//TODO:Put this in a better place. Set tab format with flags
//style parameters
string tabulate = "    ";

InstanceSymbol :: InstanceSymbol(){
	this -> nameModule = "null";
	this -> nameInstance = "null";
	this -> nameInstanceVerilog = "null";
}
InstanceSymbol :: InstanceSymbol(vector<InoutSymbol> v_inoutwires, vector<FunctionSymbolParam> v_param,vector<WireSymbol> v_wire, string nameModule,string nameInstance){
	this -> nameModule = nameModule;
	this -> nameInstance = nameInstance;
	this -> nameInstanceVerilog = "inst_" + nameInstance;
	this -> v_inoutwires = v_inoutwires;
	this -> v_param = v_param;
	this -> v_wire = v_wire;
}
InstanceSymbol :: InstanceSymbol(const InstanceSymbol &In){
	this -> nameModule = In.nameModule;
	this -> nameInstance = In.nameInstance;
	this -> nameInstanceVerilog = In.nameInstanceVerilog;
	this -> v_inoutwires = In.v_inoutwires;
	this -> v_param = In.v_param;
	this -> v_wire = In.v_wire;
}
InstanceSymbol :: ~InstanceSymbol(){}

InstanceSymbol& InstanceSymbol ::operator = (const InstanceSymbol &In){
	if(this != &In)
    {
		InstanceSymbol(In);
		return *this;
	}
}

bool InstanceSymbol :: addValueFunctionSymbolParam(string name, string value, int nlin, int ncol)
{
	FunctionSymbolParam s(name);
	for (int i = 0; i < this -> v_param.size();++i) {
		if (this -> v_param.at(i).getName() == s.getName()) { 
			this -> v_param.at(i).setValue(value);
			return true;
		}
	}

	// fail: Symbol param  not declared
	msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
	return false;
}
bool InstanceSymbol :: addValueInoutSymbolParam(string name, string value, int type, int nlin, int ncol)
{
	
	for (int i = 0; i < this -> v_inoutwires.size();++i) {
		if (this -> v_inoutwires.at(i).getName() == name && this -> v_inoutwires.at(i).getType() == type) { 
			this -> v_inoutwires.at(i).setValue(value);
			return true;
		}
	}
	// fail: Symbol param  not declared
	msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
	return false;
}

void InstanceSymbol :: addValueFunctionSymbolParamPos(int pos, string value)
{
	if (pos < v_param.size()){
		this -> v_param.at(pos).setValue(value);
	}
	
}
int InstanceSymbol :: searchinoutSymbol(string name, int type, int nlin, int ncol)
{
	for (int i = 0; i <  this -> v_inoutwires.size();++i) {
		if ( this -> v_inoutwires.at(i).getName() == name) {
			if (v_inoutwires.at(i).getType() == type || v_inoutwires.at(i).getType() == INOUT){
				return  i;
			}
			else{
				// fail: connection not declared
				msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
				return -1;
			}
			
		}
	}
	// fail: connection not declared
	msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
	return -1;
}
string InstanceSymbol :: getName(){return this-> nameModule;}
string InstanceSymbol :: getNameInstance(){return this-> nameInstance;}
string InstanceSymbol :: getNameInstanceVerilog(){return this-> nameInstanceVerilog;}
string InstanceSymbol :: generateInstance(){
	string output = "";
	output += tabulate + this -> nameModule;
	// add parameters
	if (v_param.size() != 0){
		output += " #(\n";
		for (int i = 0; i < this -> v_param.size();++i) {
			if (i == this -> v_param.size() -1){
				output += tabulate + tabulate + "." + this -> v_param.at(i).getName() + " (" + this -> v_param.at(i).getValue() + ")\n";
			}
			else{
				output += tabulate + tabulate + "." + this -> v_param.at(i).getName() + " (" + this -> v_param.at(i).getValue() + "),\n";
			}
		}
		output += tabulate + ")" + "\n" + tabulate;
	}
	else{
		output+= " ";
	}
	output+= this -> nameInstanceVerilog + "(\n";
		for (int i = 0; i < this -> v_inoutwires.size();++i) {
			if (i == this -> v_inoutwires.size() -1){
				output += tabulate + tabulate + "." + v_inoutwires.at(i).getNameVerilog() + tabulate + tabulate + "(" + v_inoutwires.at(i).getValue() + ")\n" ;
			}
			else{
				output += tabulate + tabulate + "." + v_inoutwires.at(i).getNameVerilog() + tabulate + tabulate + "(" + v_inoutwires.at(i).getValue() + "),\n" ;
			}
		}
	output += tabulate + ");\n\n";
	return output;
	// add connections
}
