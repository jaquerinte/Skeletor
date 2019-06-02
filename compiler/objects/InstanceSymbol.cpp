#include "InstanceSymbol.h"
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

bool InstanceSymbol :: addValueFunctionSymbolParam(string name, string value)
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
bool InstanceSymbol :: addValueInoutSymbolParam(string name, string value, int type)
{
	
	for (int i = 0; i < this -> v_inoutwires.size();++i) {
		if (this -> v_inoutwires.at(i).getName() == name && this -> v_inoutwires.at(i).getType() == type) { 
			this -> v_inoutwires.at(i).setValue(value);
			return true;
		}
	}
	// fail: Symbol param  not declared
	//msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
	return false;
}

void InstanceSymbol :: addValueFunctionSymbolParamPos(int pos, string value)
{
	if (pos < v_param.size()){
		this -> v_param.at(pos).setValue(value);
	}
	
}
int InstanceSymbol :: searchinoutSymbol(string name, int type)
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
string InstanceSymbol :: getName(){return this-> nameModule;}
string InstanceSymbol :: getNameInstance(){return this-> nameInstance;}
string InstanceSymbol :: getNameInstanceVerilog(){return this-> nameInstanceVerilog;}
string InstanceSymbol :: generateInstance(){
	string output = "";
	output += "\t" + this -> nameModule;
	// add parameters
	if (v_param.size() != 0){
		output += " #(\n";
		for (int i = 0; i < this -> v_param.size();++i) {
			if (i == this -> v_param.size() -1){
				output += "\t\t." + this -> v_param.at(i).getName() + " (" + this -> v_param.at(i).getValue() + ")\n";
			}
			else{
				output += "\t\t." + this -> v_param.at(i).getName() + " (" + this -> v_param.at(i).getValue() + "),\n";
			}
		}
		output += "\t)\n\t";
	}
	else{
		output+= " ";
	}
	output+= this -> nameInstanceVerilog + "(\n";
		for (int i = 0; i < this -> v_inoutwires.size();++i) {
			if (i == this -> v_inoutwires.size() -1){
				output += "\t\t." + v_inoutwires.at(i).getNameVerilog() + "\t\t(" + v_inoutwires.at(i).getValue() + ")\n" ;
			}
			else{
				output += "\t\t." + v_inoutwires.at(i).getNameVerilog() + "\t\t(" + v_inoutwires.at(i).getValue() + "),\n" ;
			}
		}
	output += "\t);\n";
	return output;
	// add connections
}