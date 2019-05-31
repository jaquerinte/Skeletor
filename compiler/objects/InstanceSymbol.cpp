#include "InstanceSymbol.h"
InstanceSymbol :: InstanceSymbol(){
	this -> nameModule = "null";
	this -> nameInstance = "null";
}
InstanceSymbol :: InstanceSymbol(vector<InoutSymbol> v_inoutwires, vector<FunctionSymbolParam> v_param,vector<WireSymbol> v_wire, string nameModule,string nameInstance){
	this -> nameModule = nameModule;
	this -> nameInstance = nameInstance;
	this -> v_inoutwires = v_inoutwires;
	this -> v_param = v_param;
	this -> v_wire = v_wire;
}
InstanceSymbol :: InstanceSymbol(const InstanceSymbol &In){
	this -> nameModule = In.nameModule;
	this -> nameInstance = In.nameInstance;
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

string InstanceSymbol ::getName(){return this-> nameModule;}
string InstanceSymbol ::getNameInstance(){return this-> nameInstance;}
string InstanceSymbol ::generateInstance(){
	string output = "";
	output += "\t\t" + this -> nameModule;
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
		output += ")\n\t";
	}
	output+= " " +  this -> nameInstance + "(\n";
		for (int i = 0; i < this -> v_inoutwires.size();++i) {
			if (i == this -> v_inoutwires.size() -1){
				output += "\t\t." + v_inoutwires.at(i).getNameVerilog() + "()\n" ;
			}
			else{
				output += "\t\t." + v_inoutwires.at(i).getNameVerilog() + "(),\n" ;
			}
		}
	output += "\t);\n";
	return output;
	// add connections
}