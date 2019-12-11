#include "TableSymbols.h"
TableSymbols :: TableSymbols(){
	this -> verilogDefig = false;
	this -> output_file_data = "";
}
TableSymbols :: ~TableSymbols(){}
bool TableSymbols :: addSymbol(string name, int type, string module, int nlin, int ncol)
{
	Symbol s(name,type, module);
	for (int i = 0; i < v_symbols.size();++i) {
		if (v_symbols.at(i).getName() == s.getName()) {

			if (v_symbols.at(i).getModule() == "null")
			{
			// fail: Symbol var ya decl
				msgError(ERRORSIMALDEC, nlin, ncol - name.length(), name.c_str());
				return false;
			}
			else if(v_symbols.at(i).getModule() == module){
				msgError(ERRORSIMALDEC, nlin, ncol - name.length(), name.c_str());
				return false;
			}
			else{
				v_symbols.push_back(s);
				return true;
			}
			
		}
	}
	v_symbols.push_back(s);
	return true;

}
bool TableSymbols :: addSymbol(string name, int type, string value, int type_var, string module, int nlin, int ncol)
{
	Symbol s(name,type,value,type_var, module);
	for (int i = 0; i < v_symbols.size();++i) {
		if (v_symbols.at(i).getName() == s.getName()) { 
			if (v_symbols.at(i).getModule() == "null")
			{
				// fail: Symbol var ya decl
			msgError(ERRORSIMALDEC, nlin, ncol - name.length(), name.c_str());
			
			return false;
			}
			else{
				v_symbols.push_back(s);
				return true;
			}
			
		}
	}
	v_symbols.push_back(s);
	return true;

}
int TableSymbols :: shearchSymbol(string name, string module, int nlin, int ncol)
{
	for (int i = 0; i < v_symbols.size();++i) {
		if (v_symbols.at(i).getName() == name && v_symbols.at(i).getModule() == module) {
			return i;
		}
		else if (v_symbols.at(i).getName() == name && v_symbols.at(i).getModule() == "null"){
			
			return i;
		}
	}
	// fail: Symbol var no decl
	msgError(ERRORSIMBNODEC, nlin, ncol - name.length(), name.c_str());
	return -1;
}

bool TableSymbols :: contains(string name, string module)
{
	for (int i = 0; i < v_symbols.size();++i) {
		if (v_symbols.at(i).getName() == name && v_symbols.at(i).getModule() == module) {
			return true;
		}
		else if (v_symbols.at(i).getName() == name && v_symbols.at(i).getModule() == "null"){
			
			return true;
		}
	}
	return false;
}

bool TableSymbols :: createDefinitions(){
	string verilogVar = "";
	for (int i = 0; i < v_symbols.size();++i) {
		if (v_symbols.at(i).getType() == DEFINITIONVERILOG) { 
			if (!this -> verilogDefig){
				this -> verilogDefig = true;
			}
		}
	}

return this -> verilogDefig;
}

bool TableSymbols :: createDefinitionsTop(){
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
	if (this -> verilogDefig){
		string output_file = projectFolder +"/hdl/defines.vh";
		/* create file */
		char buf[0x100];
		snprintf(buf, sizeof(buf), "%s", output_file.c_str());
		FILE *f = fopen(buf, "w");
		fprintf(f, "%s",this -> output_file_data.c_str());
		fclose(f);
	}

}

bool TableSymbols :: getVerilogDefig(){return this -> verilogDefig;}

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
	         case 5:
	         	type = "PARAMETERFUNCTION";
	         	break;
	         default:
	            type = "UNDEFINED";

      	}
      	string module = "";
      	if (v_symbols.at(i).getModule() == "null"){
      		module = "Global";
      	}
      	else{
      		module = v_symbols.at(i).getModule();
      	}
		out += "// name: " + v_symbols.at(i).getName() + " " + module + " , type: " + type + " value: "+ v_symbols.at(i).getValue_S() + "\n";
	}
	out += "\n";
	return out;
}
