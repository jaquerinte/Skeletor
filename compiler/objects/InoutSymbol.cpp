#include "InoutSymbol.h"

InoutSymbol :: InoutSymbol()
{
	this -> name = "null";
	this -> typeconnection = -1;
	this -> width = "";
}

InoutSymbol :: InoutSymbol(const string name,const int typeconnection,const string width) 
{
	this -> name = name;
	this -> typeconnection = typeconnection;
	this -> width = width;
}
InoutSymbol :: InoutSymbol(const InoutSymbol &In){
	this -> name = In.name;
	this -> typeconnection = In.typeconnection;
	this -> width = In.width;
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
int InoutSymbol :: getType(){return this->typeconnection;}
string InoutSymbol :: getWith(){return this->width;}
void InoutSymbol :: setName(string name){this -> name = name;}
void InoutSymbol :: setType(int type){this -> typeconnection = type;}
void InoutSymbol :: setWith(int width){this -> width = width;}