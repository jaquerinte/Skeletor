#ifndef VWIRESYMBOL_H
#define VWIRESYMBOL_H

#include <string.h>
#include <string>
#include <vector>

using namespace std;
class VWireSymbol
{
public:
	VWireSymbol();
	VWireSymbol(string width_out,string name_wire);
	~VWireSymbol();
	VWireSymbol(const VWireSymbol &In);
	VWireSymbol& operator = (const VWireSymbol &In);

	string getWidthOut();
	string getNameWire();

private:
	string width_out;
	string name_wire;
	
};




#endif