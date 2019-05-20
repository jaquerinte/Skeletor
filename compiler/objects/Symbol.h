#ifndef SYMBOL_H
#define SYMBOL_H

#include <string.h>
#include <string>

using namespace std;

const int DEFINITION=1;
const int DEFINITIONVERILOG=2;
const int VARIABE=3;
const int FUNCTION=4;

class Symbol
{

public:
	Symbol();
	Symbol(const string name,const int type);
	Symbol(const string name,const int type, const string value, const int type_var);
	//Symbol(const string name,const int type, const int value);
	//Symbol(const string name,const int type, const bool value);
	Symbol(const Symbol &In);
	~Symbol();
	Symbol& operator = (const Symbol &In);
	string getName();
	int getType();
	string getValue_S();
private:
	string name;
	int type;
	string value_s;
	//int value_i;
	//bool value_b;

	
};



#endif