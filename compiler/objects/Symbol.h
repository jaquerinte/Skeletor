#ifndef SYMBOL_H
#define SYMBOL_H

#include <string.h>
#include <string>

using namespace std;

const int DEFINITION=1;//defines of our lenguaje. Worker, project, descriptions 
const int DEFINITIONVERILOG=2;//Defines that are translated to Verilog
const int VARIABE=3;
const int FUNCTION=4;
const int PARAMETERFUNCTION=5;
const int INOUTSYMBOL=6;
const int INSTANCESYMBOL=7;//IDs of instances
const int WIRE=8;//Definition of a wire
const int VWIRE=9;//Definition of a wire

class Symbol
{

public:
	Symbol();
	Symbol(const string name,const int type, const string module);
	Symbol(const string name,const int type, const string value, const int type_var, const string module);
	//Symbol(const string name,const int type, const int value);
	//Symbol(const string name,const int type, const bool value);
	Symbol(const Symbol &In);
	~Symbol();
	Symbol& operator = (const Symbol &In);
	string getName();
	int getType();
	int getTypeVar(); 
	string getValue_S();
	string getModule();
private:
	string name;
	int type;
	int typeVar;
	string value_s;
	string module;
	//int value_i;
	//bool value_b;

	
};



#endif
