#include "WireSymbol.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stdexcept>

WireSymbol :: WireSymbol(){
	this -> function_out = "";
	this -> function_in = "";
	this -> pos_out = -1;
	this -> pos_in = -1;
	this -> width_out = "";
	this -> name_wire = "";
	this -> out_name = "";
	this -> in_name = "";
	this -> print = true;
	this -> multipleInFunction = false;

}
WireSymbol :: WireSymbol(string function_out, string function_in ,int pos_out, int pos_in, string width_out, string name_wire, string out_name, string in_name, bool print){
	this -> function_out = function_out;
	this -> function_in = function_in;
	this -> pos_out = pos_out;
	this -> pos_in = pos_in;
	this -> width_out = width_out;
	this -> name_wire = name_wire;
	this -> out_name = out_name;
	this -> in_name = in_name;
	this -> print = print;
	this -> multipleInFunction = false;
	this -> functions_in.push_back(tuple<string,string>(function_in, in_name));
}
WireSymbol :: ~WireSymbol(){}
WireSymbol :: WireSymbol(const WireSymbol &In){
	this -> function_out = In.function_out;
	this -> function_in = In.function_in;
	this -> pos_out = In.pos_out;
	this -> pos_in = In.pos_in;
	this -> width_out = In.width_out;
	this -> name_wire = In.name_wire;
	this -> out_name = In.out_name;
	this -> in_name = In.in_name;
	this -> print = In.print;
	this -> functions_in = In.functions_in;
	this -> multipleInFunction = In.multipleInFunction;

}
WireSymbol& WireSymbol :: operator = (const WireSymbol &In){
	if(this != &In)
    {
		WireSymbol(In);
    	return *this;
	}
}
	
void WireSymbol :: addFunctionIn(string functionIn, string inputIn){
	this -> multipleInFunction = !this -> multipleInFunction ? true : this -> multipleInFunction;
	this -> functions_in.push_back(std::tuple<std::string,std::string>(functionIn, inputIn));
}
bool WireSymbol :: isFunctionIn(string functionIn){
	
	for (vector_tuples::const_iterator i = this -> functions_in.begin(); i != functions_in.end(); ++i) {
		if(std::get<0>(*i) == functionIn){
			return true;
		}
	}
	return false;
}
bool WireSymbol :: isFunctionInPortIn(string functionIn, string inputIn){

	for (vector_tuples::const_iterator i = this -> functions_in.begin(); i != functions_in.end(); ++i) {
		if(std::get<0>(*i) == functionIn && std::get<1>(*i) == inputIn){
			return true;
		}
	}
	return false;
	
}

string WireSymbol :: getFuncionOut(){return this -> function_out;}
string WireSymbol :: getFuncionIn(){return this -> function_in;}
int WireSymbol :: getInoutSymbolOut(){return this -> pos_out;}
int WireSymbol :: getInoutSymbolIn(){return this -> pos_in;}
string WireSymbol :: getWidthOut(){return this -> width_out;}
string WireSymbol :: getNameWire(){return this -> name_wire;}
string WireSymbol :: getNameOut(){return this -> out_name;}
string WireSymbol :: getNameIn(){return this -> in_name;}
bool WireSymbol :: getPrint(){return this -> print;}
bool WireSymbol :: getMultiple(){return this -> multipleInFunction;}

