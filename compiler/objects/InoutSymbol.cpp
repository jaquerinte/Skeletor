#include "InoutSymbol.h"

InoutSymbol :: InoutSymbol()
{
	this -> name = "null";
	this -> typeconnection = -1;
	this -> width = "";
	this -> name_verilog = "";
	this -> value = "";
}
string InoutSymbol :: getPadding(string name)
{
    string padding;
    int size = name.size()+4;//+3 because "_i ","_o " or "_io". +1 beacause of . of instance
    if(size % 4 != 0){
        for(int i=0; i< 4-(size % 4); i++){
            padding.append(" ");
        }
    }
    else{
        padding="";
    }
    return padding;
}

InoutSymbol :: InoutSymbol(const string name,const int typeconnection,const string width) 
{
	this -> name = name;
	this -> typeconnection = typeconnection;
	this -> width = width;
        
	switch(this -> typeconnection){
		case IN:
            this -> name_verilog = this -> name + "_i " + getPadding(name);
            break;
        case OUT:
            this -> name_verilog = this -> name + "_o " + getPadding(name);
            break;
        case INOUT:
            this -> name_verilog = this -> name + "_io" + getPadding(name);
            break;

	}
	this -> value = "";
}
InoutSymbol :: InoutSymbol(const InoutSymbol &In){
	this -> name = In.name ;
	this -> typeconnection = In.typeconnection;
	this -> width = In.width;
	this -> name_verilog = In.name_verilog;
	this -> value = In.value;
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
string InoutSymbol :: getWidth(){return this->width;}
string InoutSymbol :: getValue(){return this -> value;}
void InoutSymbol :: setType(int type){this -> typeconnection = type;}
void InoutSymbol :: setWidth(int width){this -> width = width;}
void InoutSymbol :: setName(string name){
	this -> name = name;
	switch(this -> typeconnection){
		case IN:
            this -> name_verilog = this -> name + "_i " + getPadding(name);
            break;
        case OUT:
            this -> name_verilog = this -> name + "_o " + getPadding(name);
            break;
        case INOUT:
            this -> name_verilog = this -> name + "_io" +  getPadding(name);
            break;

	}
}
void InoutSymbol :: setValue(string value){ this -> value = value;}
