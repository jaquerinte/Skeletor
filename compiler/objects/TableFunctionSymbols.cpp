#include "TableFunctionSymbols.h"
#include <bits/stdc++.h> 
#include <iostream> 
#include <sys/stat.h> 
#include <sys/types.h> 

// auxiliar functions
void createSymLibTable(string projectFolder);
// init definition

TableFunctionSymbols :: TableFunctionSymbols(){}

TableFunctionSymbols :: ~TableFunctionSymbols(){}

bool TableFunctionSymbols :: addFunctionSymbol(string name, string projectName, string projectFolder,int nlin,int ncol)

{
	FunctionSymbol s(name, projectName, projectFolder );
	for (int i = 0; i < v_funcSymbols.size();++i) {
		if (v_funcSymbols.at(i).getName() == s.getName()) { 
			// fail: func var ya decl
			msgError(ERRFUNALDEC, nlin, ncol - name.length(), name.c_str());
			return false;
		}
	}
	v_funcSymbols.push_back(s);
	return true;
}
bool TableFunctionSymbols :: addTopFunctionSymbol(string name, string projectName, string projectFolder,int nlin,int ncol)

{
	FunctionSymbol s(name, projectName, projectFolder, true);
	for (int i = 0; i < v_funcSymbols.size();++i) {
		if (v_funcSymbols.at(i).getName() == s.getName()) { 
			// fail: func var ya decl
			msgError(ERRFUNALDEC, nlin, ncol - name.length(), name.c_str());
			return false;
		}
	}
	v_funcSymbols.push_back(s);
	return true;
}

int TableFunctionSymbols :: searchFunctionSymbol(string name,int nlin,int ncol)
{
	for (int i = 0; i < v_funcSymbols.size();++i) {
		if (v_funcSymbols.at(i).getName() == name) {
			return i;
		}
	}
	// fail: func var no decl
	msgError(ERRFUNODEC, nlin, ncol - name.length(), name.c_str());
	return 0;
}

//TableFunctionSymbols añadir una nueva carpeta
void TableFunctionSymbols :: createFiles(string projectFolder)
{
	// Creating a directory 
	if (mkdir(projectFolder.c_str(), 0777) == -1){
		cerr << "Error : " << strerror(errno) << endl; 
    }   
    string temp = projectFolder +"/hdl";
	if (mkdir(temp.c_str(), 0777) == -1)
		cerr << "Error : " << strerror(errno) << endl; 
   

    for (int i = 0; i < v_funcSymbols.size();++i) {
		//mandarlo a la carpeta
        v_funcSymbols.at(i).printToFile();
	}

}

// create the folder for the kicatProject
void TableFunctionSymbols :: createFilesKicat(string projectFolder)
{	
	string output_file_lib = projectFolder + "/kicad/" + projectFolder + ".lib";
	string output_lib = "";
	string temp = projectFolder +"/kicad";
	if (mkdir(temp.c_str(), 0777) == -1){
		cerr << "Error : " << strerror(errno) << endl;
	}
	// frirst create the miscelaneous files
	// sym-lib-table
	createSymLibTable(projectFolder);
	//.lib
	// inital data for the file
	output_lib += "EESchema-LIBRARY Version 2.4\n#encoding utf-8\n";
	for (int i = 0; i < v_funcSymbols.size();++i) {
		//mandarlo a la carpeta
        output_lib += v_funcSymbols.at(i).getLibData();
	}
	// end file
	output_lib +="#\n#End Library";
	// create file lib
	char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", output_file_lib.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, "%s",output_lib.c_str());
    fclose(f);
	
	//create a list of functions symbols that have
	std::map<string, FunctionSymbol*> mapOfLeafsModules;

	for(int i = 0; i < v_funcSymbols.size();++i){
		mapOfLeafsModules.insert({v_funcSymbols.at(i).getName(), &v_funcSymbols.at(i) });
	}
	//create sch files TODO only top now
	for (int i = 0; i < v_funcSymbols.size();++i) {
		
		if(!v_funcSymbols.at(i).isLeaf()){
			if(v_funcSymbols.at(i).getIsTop()) {
				// top module
				v_funcSymbols.at(i).CreateSchFile(projectFolder,mapOfLeafsModules);
				// create .pro file
				v_funcSymbols.at(i).createProjectFile(projectFolder, v_funcSymbols.at(i).getName() + "_top");
			}
			else {
				// not top modules
				v_funcSymbols.at(i).CreateSchFile(projectFolder,mapOfLeafsModules);
				// create .pro file
				v_funcSymbols.at(i).createProjectFile(projectFolder, v_funcSymbols.at(i).getName());
			}
		}

	}
	

}

// create the sym-lib-table

void createSymLibTable(string projectFolder){
	string output_file = projectFolder + "/kicad/sym-lib-table";
	string output = "";
	output += "(sym_lib_table\n";
	output += "  (lib (name "+ projectFolder + ")(type Legacy)(uri ${KIPRJMOD}/" + projectFolder + ".lib)(options \"\")(descr \"\"))\n";
	output += ")";
	// create file
	char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", output_file.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, "%s",output.c_str());
    fclose(f);

}
