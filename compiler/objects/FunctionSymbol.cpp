#include "FunctionSymbol.h"
#include <iostream>

FunctionSymbol :: FunctionSymbol()
{
    this -> name = "null";
    this -> function = "";
    this -> description = "";
    this -> code = "";
    this -> projectName = "";
    this -> filename_asociated = "./output/" + name + ".v";
    this -> output_file_data = "";
    this -> projectFolder = "";
}


FunctionSymbol :: FunctionSymbol(string name, string projectName, string projectFolder)
{
    this -> name = name;
    this -> function = "";
    this -> description = "";
    this -> code = "";
    this -> projectName = projectName;
    this -> filename_asociated = "./" + projectFolder + "/" + name + ".v";
    this -> projectFolder = "./" + projectFolder + "/";
    //this -> filename_asociated = "./objects/" + name + ".v";
    this -> output_file_data = "";
}

FunctionSymbol :: FunctionSymbol(const FunctionSymbol &In)
{
    this -> name = In.name;
    this -> function = In.function;
    this -> description = In.description;
    this -> code = In.code;
    this -> projectName = In.projectName;
    this -> filename_asociated = In.filename_asociated;
    //modulos individuales pero no el top
    this -> output_file_data = In.output_file_data;
    this -> v_inoutwires = In.v_inoutwires;
    this -> v_param = In.v_param;
    this -> v_wire = In.v_wire;
    this -> v_instances = In.v_instances;
    this -> projectFolder = In.projectFolder;
}
FunctionSymbol :: ~FunctionSymbol(){}

FunctionSymbol& FunctionSymbol :: operator = (const FunctionSymbol &In)
{
    if(this != &In)
    {
        FunctionSymbol(In);
        return *this;
    }
}


bool FunctionSymbol :: addConnectionFunctionSymbol(string name, int size, string width)
{
    InoutSymbol s(name, size, width);
    for (int i = 0; i < this -> v_inoutwires.size();++i) {
        if (this -> v_inoutwires.at(i).getName() == s.getName() && this -> v_inoutwires.at(i).getType() == s.getType()) { 
            // fail: connection alrady declared
            cout << "CONNECTION ALREADY DECLARED " << s.getName() << endl;
            exit(1);
            //msgError(ERRCONNDEC, nlin, ncol - name.length(), name.c_str());
            return false;
        }
    }
    this -> v_inoutwires.push_back(s);
    return true;

}

int FunctionSymbol :: searchinoutSymbol(string name)
{
    for (int i = 0; i <  this -> v_inoutwires.size();++i) {
        if ( this -> v_inoutwires.at(i).getName() == name) {
            return  i;
        }
    }
    // fail: connection not declared
    //msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
    return -1;
}


int FunctionSymbol :: searchinoutSymbol(string name, int type)
{
    for (int i = 0; i <  this -> v_inoutwires.size();++i) {
        if ( this -> v_inoutwires.at(i).getName() == name) {
            if (v_inoutwires.at(i).getType() == type || v_inoutwires.at(i).getType() == INOUT){
                return  i;
            }
            else{
                return -1;
            }
            
        }
    }
    // fail: connection not declared
    //msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
    return -1;
}

bool FunctionSymbol :: addFunctionSymbolParam(string name)
{
    FunctionSymbolParam s(name);
    for (int i = 0; i < this -> v_param.size();++i) {
        if (this ->  v_param.at(i).getName() == s.getName()) { 
            // fail: Symbol param  already declared
            //msgError(ERRPARAMDEC, nlin, ncol - name.length(), name.c_str());
            return false;
        }
    }
    this -> v_param.push_back(s);
    return true;
}

bool FunctionSymbol :: addFunctionSymbolParam(string name, string value, int type)
{
    FunctionSymbolParam s(name, value, type);
    for (int i = 0; i < this -> v_param.size();++i) {
        if (this ->  v_param.at(i).getName() == s.getName()) { 
            
            // fail: Symbol param  already declared
            //msgError(ERRPARAMDEC, nlin, ncol - name.length(), name.c_str());
            return false;
        }
    }
    this -> v_param.push_back(s);
    return true;
}

bool FunctionSymbol :: addValueFunctionSymbolParam(string name, string value)
{
    FunctionSymbolParam s(name);
    for (int i = 0; i < this -> v_param.size();++i) {
        if (this -> v_param.at(i).getName() == s.getName()) { 
            this -> v_param.at(i).setValue(value);
            return true;
        }
    }
    // fail: Symbol param  not declared
    //msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
    return false;
}

void FunctionSymbol :: addValueFunctionSymbolParamPos(int pos, string value)
{
    if (pos < v_param.size()){
        this -> v_param.at(pos).setValue(value);
    }
    
}

FunctionSymbolParam& FunctionSymbol :: searchFunctionSymbolParam(string name)
{
    FunctionSymbolParam s;
    for (int i = 0; i < this -> v_param.size();++i) {
        if (this -> v_param.at(i).getName() == s.getName()) { 
            return this -> v_param.at(i);
        }
    }
    // fail: Symbol param  not declared
    //msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
    return s;
}

bool FunctionSymbol :: addWireConnection(string function_out, string function_in, int pos_out, int pos_in, string width_out, string name_wire, string out_name, string in_name){
    WireSymbol wire(function_out,function_in, pos_out, pos_in,width_out, name_wire, out_name, in_name);
    //cout << "wire " << wire.getFuncionOut() << " " << wire.getFuncionIn() << " " << wire.getInoutSymbolOut().getName() << " " << wire.getInoutSymbolIn().getName();
    this -> v_wire.push_back(wire);
}
/*int FunctionSymbol :: shearchWireConnection(string func, string inout){

    for (int i = 0; i < this -> v_wire.size();++i) {
        if (this -> v_wire.at(i).getName() == name and ) { 
            return this -> v_wire.at(i);
        }
    }
    return -1;
}*/

bool FunctionSymbol :: addInstance(vector<InoutSymbol> v_inoutwires, vector<FunctionSymbolParam> v_param, string name_module, string name_instance){
    InstanceSymbol instance(v_inoutwires,v_param, this -> v_wire, name_module, name_instance);
    this -> v_instances.push_back(instance);
}

int FunctionSymbol :: searchInstance(string name){
    for (int i = 0; i <  this -> v_instances.size();++i) {
        if ( this -> v_instances.at(i).getNameInstance() == name) {
            return  i;
        }
    }
    // fail: instance  not declared
    //msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
    return -1;

}

void FunctionSymbol :: createFileModule()
{
    /* Start wriking the file */
    this -> createFileModuleDefines();
    this -> createFileModuleBase();
}

void FunctionSymbol :: createFileModule(string base, bool verilogDef)
{
    /* Start writting the file */
    this -> output_file_data += base;
    this -> createFileModuleDefines();
    /* DEFINES */
    if (verilogDef){
        this -> output_file_data += "`include \"defines.vh\"\n";
    }

    /* Continue */
    this -> createFileModuleBase();
}

void FunctionSymbol :: createFileModuleDefines(){
    
    /* Definition top file */
    this -> output_file_data += "//-----------------------------------------------------\n";
    this -> output_file_data += "// Project Name : " + this -> projectName + "\n";

    if (this -> function != ""){
        this -> output_file_data += "// Function     : " + this -> function + "\n";
    }
    if (this -> description != ""){
        this -> output_file_data += "// Description  : " + this -> description + "\n";
    }
    if (this -> code != ""){
        this -> output_file_data += "// Coder        : " + this -> code + "\n";
    }
    if (this -> references != ""){
        this -> output_file_data += "// References   : " + this -> references + "\n";
    }
    this -> output_file_data += "\n";
    this -> output_file_data += "//***Headers***\n";
}
void FunctionSymbol ::createFileModuleBase(){
    this -> output_file_data +="//***Module***\n";
    /* Defining Module */
    if (this -> v_param.size() != 0){
        /* Module has param*/
        this -> output_file_data += "module " + this -> name + " #(\n";
        // Loop over param
        for (int i = 0; i < this -> v_param.size();++i) {
            string value = this -> v_param.at(i).getValue();
            if (v_param.at(i).getType() == 2){
                value = "`" + value;
            }
                            
            if (i == this -> v_param.size() -1){
                /* Last parameter */
                this -> output_file_data += tabulate + tabulate +"parameter integer " + this -> v_param.at(i).getName() + " = " + value + "\n";
            }
            else{
                /* Rest parameter */
                this -> output_file_data += tabulate + tabulate +"parameter integer " + this -> v_param.at(i).getName() + " = " + value + ",\n";
            }
        }
        this -> output_file_data += tabulate + ")\n" + tabulate +"(\n";
    }
    else{
        /* Module has not param*/
        this -> output_file_data += "module " + this -> name + " (\n";
    }
    /* copy the inputs and outputs*/
    for (int i = 0; i < this -> v_inoutwires.size();++i) {
        string type = "";
            if (this -> v_inoutwires.at(i).getType() == IN){
                type = "input ";
            }
            else if (this -> v_inoutwires.at(i).getType() == OUT){
                type = "output";
            }
            else if (this -> v_inoutwires.at(i).getType() == INOUT){
                type = "inout ";
            }
        if (i == this -> v_inoutwires.size() -1){
            /* Last INOUT parameter */
            if(this -> v_inoutwires.at(i).getWidth() == ""){
                this -> output_file_data += tabulate + tabulate + type + " " + this -> v_inoutwires.at(i).getNameVerilog() + "\n";
            }else{
                this -> output_file_data += tabulate + tabulate + type + " " + this -> v_inoutwires.at(i).getWidth() + " " + this -> v_inoutwires.at(i).getNameVerilog() + "\n";
            }
        }
        else{
            /* Rest INOUT parameter */
            if(this -> v_inoutwires.at(i).getWidth() == ""){
                this -> output_file_data += tabulate + tabulate + type + " " + this -> v_inoutwires.at(i).getNameVerilog() + ",\n";
            }else{
                this -> output_file_data += tabulate + tabulate + type + " " + this -> v_inoutwires.at(i).getWidth() + " " + this -> v_inoutwires.at(i).getNameVerilog() + ",\n";
            }
        }
    }
    /* End inputs and outputs */
    this -> output_file_data += tabulate + ");\n\n";


    /* Add Wires */
    for (int i = 0; i < this -> v_wire.size(); ++i){
        int pos_out = v_wire.at(i).getInoutSymbolOut();
        int pos_in = v_wire.at(i).getInoutSymbolIn();
        string width = "";
        if (v_wire.at(i).getWidthOut() != ""){
            width = v_wire.at(i).getWidthOut() + " ";
        }
        this -> output_file_data += tabulate + "wire " + width + v_wire.at(i).getNameWire() + ";";
        this -> output_file_data += " // wiring between " + v_wire.at(i).getNameOut() + " of module " + v_wire.at(i).getFuncionOut() + " and " + v_wire.at(i).getNameIn() + " of module " + v_wire.at(i).getFuncionIn();
        this -> output_file_data += "\n";
    }
    this -> output_file_data +="\n";
    /* Add instances */
    for (int i = 0; i < this -> v_instances.size(); ++i){
        this -> output_file_data += this -> v_instances.at(i).generateInstance();
    }
    this -> output_file_data +="\n";
    /* Putin some extra coments */
    this -> output_file_data += "//***Interal logic generated by compiler***  \n";
    this -> output_file_data += "//***Handcrafted Internal logic*** \n";
    this -> output_file_data += "//TODO\n";
    /* finish file */
    this -> output_file_data += "endmodule\n";
}

void FunctionSymbol :: createRunTest(bool definitions){
	this->createTbFolder();
	this->createQuestaSimFolder();
	this->createTbRun();
	this->createTbVerilog(definitions);



}

void FunctionSymbol :: createTbFolder(){
	string output_folder = this -> projectFolder + "tb";
	if (mkdir(output_folder.c_str(), 0777) == -1) 
		cerr << "Error : " << strerror(errno) << endl; 
}

void FunctionSymbol :: createQuestaSimFolder(){
	string output_folder = this -> projectFolder + "tb/questa_sim";
	if (mkdir(output_folder.c_str(), 0777) == -1) 
		cerr << "Error : " << strerror(errno) << endl;
}

void FunctionSymbol :: createTbRun(){
	string output_file = this -> projectFolder + "tb/questa_sim/runtest.sh";
	// create file
	string output = "vlib " + this -> name + "\n";
	output += "vmap work $PWD/" + this -> name + "\n";
	output += "vlog +incdir+../../hdl/ ../../hdl/*.v ../../hdl/*.vh tb_" + this -> name + ".v" + "\n";
	output += "vmake "+ this -> name +"/ > Makefile" + "\n";
	output += "vsim";
    // create file
	char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", output_file.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, output.c_str());
    fclose(f);

}
void FunctionSymbol :: createTbVerilog(bool definitions){
	string output_file = this -> projectFolder + "tb/questa_sim/tb_" + this->name + ".v";
	string output = "";
	output += "//-----------------------------------------------------\n";
    output += "// Project Name : " + this -> projectName + "\n";
    output += "//File Name tb_" + this->name + ".v\n";
    if (this -> function != ""){
        output += "// Function     : " + this -> function + "\n";
    }
    if (this -> description != ""){
        output += "// Description  : " + this -> description + "\n";
    }
    if (this -> code != ""){
        output += "// Coder        : " + this -> code + "\n";
    }
    if (this -> references != ""){
        output += "// References   : " + this -> references + "\n";
    }
    output += "\n";
    output += "//***Headers***\n";
    // header finish
    // definition
    if (definitions){
    	output += "`include \"defines.vh\"\n";
    }
    output += "//***Test bench***\n";
    // test bench definition
    output += "module tb_" + this -> name + "();\n";
    // parameters
    output += "//***Parameters***\n";
    // defult parameters
    output += tabulate + "parameter CLK_PERIOD      = 2;\n";
    output += tabulate + "parameter CLK_HALF_PERIOD = CLK_PERIOD / 2;\n";
    // custom parameters
    for (int i = 0; i < this -> v_param.size();++i) {
            string value = this -> v_param.at(i).getValue();
            if (v_param.at(i).getType() == 2){
                value = "`" + value;
            }       
            if (i == this -> v_param.size() -1){
                /* Last parameter */
                output += tabulate +"localparam integer " + this -> v_param.at(i).getName() + " = " + value + "\n";
            }
            else{
                /* Rest parameter */
                output += tabulate +"localparam integer " + this -> v_param.at(i).getName() + " = " + value + ",\n";
            }
    }
    // Signals IN and OUTS
    output += "//***Signals***\n";
    for (int i = 0; i < this -> v_inoutwires.size();++i) {
        string type = "";
            if (this -> v_inoutwires.at(i).getType() == IN){
                type = "reg";
            }
            else if (this -> v_inoutwires.at(i).getType() == OUT){
                type = "wire";
            }
            else if (this -> v_inoutwires.at(i).getType() == INOUT){
                type = "reg";
            }
        if (i == this -> v_inoutwires.size() -1){
            /* Last INOUT parameter */
            if(this -> v_inoutwires.at(i).getWidth() == ""){
                output += tabulate +  type + " tb_" + this -> v_inoutwires.at(i).getNameVerilog() + "\n";
            }else{
                output += tabulate +  type + " tb_" + this -> v_inoutwires.at(i).getWidth() + " " + this -> v_inoutwires.at(i).getNameVerilog() + "\n";
            }
        }
        else{
            /* Rest INOUT parameter */
            if(this -> v_inoutwires.at(i).getWidth() == ""){
                output += tabulate + type + " tb_" + this -> v_inoutwires.at(i).getNameVerilog() + ",\n";
            }else{
                output += tabulate + type + " tb_" + this -> v_inoutwires.at(i).getWidth() + " " + this -> v_inoutwires.at(i).getNameVerilog() + ",\n";
            }
        }
    }
    // create Module
    output += "//***Module***\n";
    output += tabulate + this -> name;
    // add parameters
    if (v_param.size() != 0){
        output += " #(\n";
        for (int i = 0; i < this -> v_param.size();++i) {
            if (i == this -> v_param.size() -1){
                output += tabulate + tabulate + "." + this -> v_param.at(i).getName() + " (" + this -> v_param.at(i).getValue() + ")\n";
            }
            else{
                output += tabulate + tabulate + "." + this -> v_param.at(i).getName() + " (" + this -> v_param.at(i).getValue() + "),\n";
            }
        }
        output += tabulate + ");" + "\n" + tabulate;
    }
    else{
        output+= " ";
    }
    output+= tabulate + "dut_" + this -> name + "(\n";
        for (int i = 0; i < this -> v_inoutwires.size();++i) {
            if (i == this -> v_inoutwires.size() -1){
                output += tabulate + tabulate + "." + v_inoutwires.at(i).getNameVerilog() + tabulate + tabulate + "(tb_" + v_inoutwires.at(i).getNameVerilog() + ")\n" ;
            }
            else{
                output += tabulate + tabulate + "." + v_inoutwires.at(i).getNameVerilog() + tabulate + tabulate + "(tb_" + v_inoutwires.at(i).getNameVerilog() + "),\n" ;
            }
        }
    output += tabulate + ");\n\n";
    // end create module
    // create static part
    output += "//***clk_gen***\n";
    output += tabulate +"initial tb_clk_i = 0;\n";
    output += tabulate +"always #CLK_HALF_PERIOD tb_clk_i = !tb_clk_i;\n";
    output += "\n";
    output += "//***task reset_dut***\n";
    output += tabulate +"task reset_dut;\n";
    output += tabulate +tabulate + "begin\n";
    output += tabulate +tabulate + tabulate +"$display(\"*** Toggle reset.\");\n";
    output += tabulate +tabulate + tabulate +"//*** TODO ***\n";
    output += tabulate +tabulate +"end\n";
    output += tabulate +"endtask\n";
    output += "\n";
    output += "//***task init_sim***\n";
    output += tabulate +"task init_sim;\n";
    output += tabulate +tabulate + "begin\n";
    output += tabulate +tabulate + tabulate +"$display(\"*** init sim.\");\n";
    output += tabulate +tabulate + tabulate +"//*** TODO ***\n";
    output += tabulate +tabulate +"end\n";
    output += tabulate +"endtask\n";
    output += "\n";
    output += "//***task init_dump***\n";
    output += tabulate +"task init_dump;\n";
    output += tabulate +tabulate + "begin\n";
    output += tabulate +tabulate + tabulate +"$dumpfile(\"test.vcd\");\n";
    output += tabulate +tabulate + tabulate +"$dumpvars(0,dut_" + this->name +");\n";
    output += tabulate +tabulate +"end\n";
    output += tabulate +"endtask\n";
    output += "\n";
    output += "//***task test_sim***\n";
    output += tabulate +"task test_sim;\n";
    output += tabulate +tabulate + "begin\n";
    output += tabulate +tabulate + tabulate +"$display(\"*** test_sim.\");\n";
    output += tabulate +tabulate + tabulate +"//***Handcrafted test***\n";
    output += tabulate +tabulate +"end\n";
    output += tabulate +"endtask\n";
    output += "\n";
    output += "\n";
    output += "//***init_sim***\n";
    output += tabulate +"initial begin\n";
    output += tabulate +tabulate + "init_sim();\n";
    output += tabulate +tabulate + "init_dump();\n";
    output += tabulate +tabulate + "reset_dut();\n";
    output += tabulate +tabulate + "test_sim();\n";
    output += tabulate +"end\n";
    output += "\n";
    output += "endmodule\n";



    // cretate file
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", output_file.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, output.c_str());
    fclose(f);

}


void FunctionSymbol :: printToFile()
{
    /* create file */
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", this -> filename_asociated.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, this -> output_file_data.c_str());
    fclose(f);

}

string FunctionSymbol :: getName(){return this -> name;}
string FunctionSymbol :: getFilenameAsociated(){return this -> filename_asociated;}
string FunctionSymbol :: getFunction() {return this -> function;}
string FunctionSymbol :: getDescription() {return this -> description;}
string FunctionSymbol :: getCode() {return this -> code;}
string FunctionSymbol :: getProjectName() {return this -> projectName;}
string FunctionSymbol :: getReferences() {return this -> references;}
string FunctionSymbol :: getOutputFileData() {return this -> output_file_data;}
vector<FunctionSymbolParam> FunctionSymbol :: getFunctionSymbolParam(){return this -> v_param;}
vector<InoutSymbol> FunctionSymbol :: getInoutSymbol(){return this -> v_inoutwires;}

//setters

void FunctionSymbol :: setName(string name){ this -> name = name;}
void FunctionSymbol :: setFunction(string function) { this -> function = function;}
void FunctionSymbol :: setDescription(string description) { this -> description = description;}
void FunctionSymbol :: setCode(string code) { this -> code = code;}
void FunctionSymbol :: setProjectName(string projectName) { this -> projectName = projectName;}
void FunctionSymbol :: setReferences(string references) { this -> references = references;}
