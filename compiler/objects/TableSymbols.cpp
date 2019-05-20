#include "TableSymbols.h"
TableSymbols :: TableSymbols(){
	this -> verilogDefig = false;
	this -> output_file_data = "";
}
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
bool TableSymbols :: addSymbol(string name, int type, string value, int type_var)
{
	Symbol s(name,type,value,type_var);
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

bool TableSymbols :: createDefinitions(){
	string verilogVar = "";
	for (int i = 0; i < v_symbols.size();++i) {
		if (v_symbols.at(i).getType() == DEFINITIONVERILOG) { 
			if (!this -> verilogDefig){
				this -> verilogDefig = true;
			}
			verilogVar += "`define " +  v_symbols.at(i).getName() + " " + v_symbols.at(i).getValue_S() + "\n";
		}
	}
	if (this -> verilogDefig){
		this -> output_file_data += "//-------------------------------------------------\n";
		this -> output_file_data += "// Generated defines                               \n";
		this -> output_file_data += "//-------------------------------------------------\n\n";
		this -> output_file_data += verilogVar;
	}

return this -> verilogDefig;
}

void TableSymbols :: printToFile(string projectFolder)
{
	string output_file = projectFolder +"/defines.vh";
	/* create file */
	char buf[0x100];
	snprintf(buf, sizeof(buf), "%s", output_file.c_str());
	FILE *f = fopen(buf, "w");
	fprintf(f, this -> output_file_data.c_str());
	fclose(f);

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
	            type = "DEFINITIONVERILOG";
	            break;
	         case 3:
	         	type = "VARIABE";
	         	break;
	         case 4:
	         	type = "FUNCTION";
	         	break;
	         default:
	            type = "UNDEFINED";

      	}
		out += "// name: " + v_symbols.at(i).getName() + ", type: " + type + " value: "+ v_symbols.at(i).getValue_S() + "\n";
	}
	return out;
}