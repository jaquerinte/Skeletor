#include "VRegSymbol.h"

VRegSymbol :: VRegSymbol(){
	this -> width_out = "";
	this -> name_wire = "";

}
VRegSymbol :: VRegSymbol(string width_out,string name_wire){

	this -> width_out = width_out;
	this -> name_wire = name_wire;
}
VRegSymbol :: ~VRegSymbol(){}
VRegSymbol :: VRegSymbol(const VRegSymbol &In){
	this -> width_out = In.width_out;
	this -> name_wire = In.name_wire;

}
VRegSymbol& VRegSymbol :: operator = (const VRegSymbol &In){
	if(this != &In)
    {
		VRegSymbol(In);
    	return *this;
	}
}

string VRegSymbol :: getWidthOut(){return this -> width_out;}
string VRegSymbol :: getNameWire(){return this -> name_wire;}
