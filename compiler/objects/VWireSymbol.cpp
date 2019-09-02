#include "VWireSymbol.h"

VWireSymbol :: VWireSymbol(){
	this -> width_out = "";
	this -> name_wire = "";

}
VWireSymbol :: VWireSymbol(string width_out,string name_wire){

	this -> width_out = width_out;
	this -> name_wire = name_wire;
}
VWireSymbol :: ~VWireSymbol(){}
VWireSymbol :: VWireSymbol(const VWireSymbol &In){
	this -> width_out = In.width_out;
	this -> name_wire = In.name_wire;

}
VWireSymbol& VWireSymbol :: operator = (const VWireSymbol &In){
	if(this != &In)
    {
		VWireSymbol(In);
    	return *this;
	}
}

string VWireSymbol :: getWidthOut(){return this -> width_out;}
string VWireSymbol :: getNameWire(){return this -> name_wire;}
