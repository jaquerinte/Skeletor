#ifndef WIRESYMBOL_H
#define WIRESYMBOL_H

#include <string.h>
#include <string>
#include <vector>
#include "InoutSymbol.h"

using namespace std;
class WireSymbol
{
public:
	WireSymbol();
	WireSymbol(string function_out, string function_in ,int pos_out, int pos_in, string width_out,string name_wire, string out_name, string in_name);
	~WireSymbol();
	WireSymbol(const WireSymbol &In);
	WireSymbol& operator = (const WireSymbol &In);

	string getFuncionOut();
	string getFuncionIn();
	int getInoutSymbolOut();
	int getInoutSymbolIn();
	string getWidthOut();
	string getNameWire();
	string getNameOut();
    string getNameIn();

private:
	string function_out;
	string function_in;
	int pos_out;
	int pos_in;
	string width_out;
	string name_wire;
	string in_name;
	string out_name;
	
};




#endif
