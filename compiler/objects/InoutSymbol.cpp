#include "InoutSymbol.h"

InoutSymbol :: InoutSymbol()
{
	this -> name = "null";
	this -> typeconnection = -1;
	this -> width = "";
	this -> name_verilog = "";
}

InoutSymbol :: InoutSymbol(const string name,const int typeconnection,const string width) 
{
	this -> name = name;
	this -> typeconnection = typeconnection;
	this -> width = width;
	switch(this -> typeconnection){
		case IN:
            this -> name_verilog = this -> name + "_i";
            break;
        case OUT:
            this -> name_verilog = this -> name + "_o";
            break;
        case INOUT:
            this -> name_verilog = this -> name + "_io";
            break;

	}
}
InoutSymbol :: InoutSymbol(const InoutSymbol &In){
	this -> name = In.name;
	this -> typeconnection = In.typeconnection;
	this -> width = In.width;
	this -> name_verilog = In.name_verilog;
}
InoutSymbol :: ~InoutSymbol(){}
InoutSymbol& InoutSymbol :: operator = (const InoutSymbol &In) {
	
	if(this != &In)
    {
		InoutSymbol(In);
    	return *this;
	}
}

string InoutSymbol :: getName(){return this->name;}
string InoutSymbol :: getNameVerilog(){return this -> name_verilog;}
int InoutSymbol :: getType(){return this->typeconnection;}
string InoutSymbol :: getWith(){return this->width;}
void InoutSymbol :: setType(int type){this -> typeconnection = type;}
void InoutSymbol :: setWith(int width){this -> width = width;}
void InoutSymbol :: setName(string name){
	this -> name = name;
	switch(this -> typeconnection){
		case IN:
            this -> name_verilog = this -> name + "_i";
            break;
        case OUT:
            this -> name_verilog = this -> name + "_o";
            break;
        case INOUT:
            this -> name_verilog = this -> name + "_io";
            break;

	}
}