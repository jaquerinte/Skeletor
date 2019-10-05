#ifndef VREGSYMBOL_H
#define VREGSYMBOL_H

#include <string.h>
#include <string>
#include <vector>

using namespace std;
class VWireSymbol
{
public:
	VRegSymbol();
	VRegSymbol(string width_out,string name_wire);
	~VRegSymbol();
	VRegSymbol(const VRegSymbol &In);
	VRegSymbol& operator = (const VRegSymbol &In);

	string getWidthOut();
	string getNameWire();

private:
	string width_out;
	string name_wire;
	
};




#endif