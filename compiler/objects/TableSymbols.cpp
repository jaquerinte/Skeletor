#include "TableSymbols.h"
TableSymbols :: TableSymbols(){}
TableSymbols :: ~TableSymbols(){}
bool TableSymbols :: addSymbol(string name, int type)
{
	Symbol s(name,type);
	for (int i = 0; i < v_symbols.size();++i) {
		if (v_symbols.at(i).getName() == s.getName()) { 
			// fail: Symbol var ya decl
			//msgError(ERRFUNALDEC, nlin, ncol - name.length(), name.c_str());
			return false;
		}
	}
	v_symbols.push_back(s);
	return true;

}
bool TableSymbols :: addSymbol(string name, int type, string value)
{
	Symbol s(name,type,value);
	for (int i = 0; i < v_symbols.size();++i) {
		if (v_symbols.at(i).getName() == s.getName()) { 
			// fail: Symbol var ya decl
			//msgError(ERRFUNALDEC, nlin, ncol - name.length(), name.c_str());
			return false;
		}
	}
	v_symbols.push_back(s);
	return true;

}
int TableSymbols :: shearchSymbol(string name)
{
	for (int i = 0; i < v_symbols.size();++i) {
		if (v_symbols.at(i).getName() == name) { 
			// fail: Symbol var ya decl
			//msgError(ERRFUNALDEC, nlin, ncol - name.length(), name.c_str());
			return i;
		}
	}
	return -1;
}

string TableSymbols :: getTableSymbols()
{
	string out = "//-----------------------------------------------------\n";
	      out += "//                TABLE SYMBOL                       --\n";
	      out += "//-----------------------------------------------------\n";
	string type = "UNDEFINED";
	for (int i = 0; i < v_symbols.size();++i) {

		switch (v_symbols.at(i).getType())
      	{
	         case 1:
	            type = "DEFINITION";
	            break;
	         case 2:
	            type = "VARIABE";
	            break;
	         case 3:
	         	type = "FUNCTION";
	         	break;
	         default:
	            type = "UNDEFINED";

      	}
		out += "// name: " + v_symbols.at(i).getName() + ", type: " + type + "\n";
	}
	return out;
}