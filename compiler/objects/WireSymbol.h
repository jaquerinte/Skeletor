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
	WireSymbol(string function_in, InoutSymbol out, InoutSymbol in);
	~WireSymbol();
	WireSymbol(const WireSymbol &In);
	WireSymbol& operator = (const WireSymbol &In);
private:
	string function_in;
	InoutSymbol out;
	InoutSymbol in;
	
};




#endif