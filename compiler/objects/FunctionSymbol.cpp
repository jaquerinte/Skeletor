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
    this -> projectFolderName = "";
    this -> verilog_dump = "";
    this -> isTop = false;
    this -> functionDesig = new ComponentFunctionSymbol();
}


FunctionSymbol :: FunctionSymbol(string name, string projectName, string projectFolder)
{
    this -> name = name;
    this -> function = "";
    this -> description = "";
    this -> code = "";
    this -> projectName = projectName;
    this -> projectFolderName = "./" + projectFolder + "/";
    this -> filename_asociated = "./" + projectFolder + "/hdl/" + name + ".v";
    this -> projectFolder = "./" + projectFolder + "/hdl/";
    //this -> filename_asociated = "./objects/" + name + ".v";
    this -> output_file_data = "";
    this -> verilog_dump = "";
    this -> isTop = false;
    this -> functionDesig = new ComponentFunctionSymbol();
}
FunctionSymbol :: FunctionSymbol(string name, string projectName, string projectFolder, bool isTop)
{
    this -> name = name;
    this -> function = "";
    this -> description = "";
    this -> code = "";
    this -> projectName = projectName;
    this -> projectFolderName = "./" + projectFolder + "/";
    this -> filename_asociated = "./" + projectFolder + "/hdl/" + name + ".v";
    this -> projectFolder = "./" + projectFolder + "/hdl/";
    //this -> filename_asociated = "./objects/" + name + ".v";
    this -> output_file_data = "";
    this -> verilog_dump = "";
    this -> isTop = isTop;
}

FunctionSymbol :: FunctionSymbol(const FunctionSymbol &In)
{
    this -> name = In.name;
    this -> function = In.function;
    this -> description = In.description;
    this -> code = In.code;
    this -> projectFolderName = In.projectFolderName;
    this -> projectName = In.projectName;
    this -> filename_asociated = In.filename_asociated;
    //modulos individuales pero no el top
    this -> output_file_data = In.output_file_data;
    this -> v_inoutwires = In.v_inoutwires;
    this -> v_param = In.v_param;
    this -> v_wire = In.v_wire;
    this -> v_vwire = In.v_vwire;
    this -> v_instances = In.v_instances;
    this -> projectFolder = In.projectFolder;
    this -> verilog_dump = In.verilog_dump;
    this -> isTop = In.isTop;
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

void FunctionSymbol :: addVerilogDump(const string dump)
{
    // delete first and last simbols
    this -> verilog_dump += dump;

}
bool FunctionSymbol :: addConnectionFunctionSymbol(string name, int size, string width, int nlin,int ncol)
{
    InoutSymbol s(name, size, width);
    for (int i = 0; i < this -> v_inoutwires.size();++i) {
        if (this -> v_inoutwires.at(i).getName() == s.getName() && this -> v_inoutwires.at(i).getType() == s.getType()) { 
            // fail: connection alrady declared
            msgError(ERRCONNDEC, nlin, ncol - name.length(), name.c_str());
            return false;
        }
    }
    this -> v_inoutwires.push_back(s);
    return true;

}

int FunctionSymbol :: searchinoutSymbol(string name, int nlin,int ncol)
{
    for (int i = 0; i <  this -> v_inoutwires.size();++i) {
        if ( this -> v_inoutwires.at(i).getName() == name) {
            return  i;
        }
    }
    // fail: connection not declared
    msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
    return -1;
}


int FunctionSymbol :: searchinoutSymbol(string name, int type, int nlin,int ncol)
{
    for (int i = 0; i <  this -> v_inoutwires.size();++i) {
        if ( this -> v_inoutwires.at(i).getName() == name) {
            if (v_inoutwires.at(i).getType() == type || v_inoutwires.at(i).getType() == INOUT){
                return  i;
            }
            /*else{
                return -1;
            }*/
            
        }
    }
    // fail: connection not declared
    msgError(ERRCONNNODEC, nlin, ncol - name.length(), name.c_str());
    return -1;
}

bool FunctionSymbol :: addFunctionSymbolParam(string name, int nlin,int ncol)
{
    FunctionSymbolParam s(name);
    for (int i = 0; i < this -> v_param.size();++i) {
        if (this ->  v_param.at(i).getName() == s.getName()) { 
            // fail: Symbol param  already declared
            msgError(ERRPARAMDEC, nlin, ncol - name.length(), name.c_str());
            return false;
        }
    }
    this -> v_param.push_back(s);
    return true;
}

bool FunctionSymbol :: addFunctionSymbolParam(string name, string value, int type, int nlin,int ncol)
{
    FunctionSymbolParam s(name, value, type);
    for (int i = 0; i < this -> v_param.size();++i) {
        if (this ->  v_param.at(i).getName() == s.getName()) { 
            
            // fail: Symbol param  already declared
            msgError(ERRPARAMDEC, nlin, ncol - name.length(), name.c_str());
            return false;
        }
    }
    this -> v_param.push_back(s);
    return true;
}

bool FunctionSymbol :: addValueFunctionSymbolParam(string name, string value, int nlin,int ncol)
{
    FunctionSymbolParam s(name);
    for (int i = 0; i < this -> v_param.size();++i) {
        if (this -> v_param.at(i).getName() == s.getName()) { 
            this -> v_param.at(i).setValue(value);
            return true;
        }
    }
    // fail: Symbol param  not declared
    msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
    return false;
}

void FunctionSymbol :: addValueFunctionSymbolParamPos(int pos, string value, int nlin,int ncol)
{
    if (pos < v_param.size()){
        this -> v_param.at(pos).setValue(value);
    }
    else
    msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
}

/*FunctionSymbolParam& FunctionSymbol :: searchFunctionSymbolParam(string name, int nlin,int ncol)
{
    FunctionSymbolParam s;
    for (int i = 0; i < this -> v_param.size();++i) {
        if (this -> v_param.at(i).getName() == s.getName()) { 
            return this -> v_param.at(i);
        }
    }
    // fail: Symbol param  not declared
    msgError(ERRPARAMNODEC, nlin, ncol - name.length(), name.c_str());
    return s;
}*/

bool FunctionSymbol :: addWireConnection(string function_out, string function_in, int pos_out, int pos_in, string width_out, string name_wire, string out_name, string in_name){
    WireSymbol wire(function_out,function_in, pos_out, pos_in,width_out, name_wire, out_name, in_name, true);
    this -> v_wire.push_back(wire);
}

bool FunctionSymbol :: addWireConnection(string function_out, string function_in, int pos_out, int pos_in, string width_out, string name_wire, string out_name, string in_name, bool print){
    WireSymbol wire(function_out,function_in, pos_out, pos_in,width_out, name_wire, out_name, in_name, print);
    this -> v_wire.push_back(wire);
}

bool FunctionSymbol :: addVWireConnection(string width_out, string name_wire){
    VWireSymbol wire(width_out, name_wire);
    this -> v_vwire.push_back(wire);
}

bool FunctionSymbol :: addInstance(vector<InoutSymbol> v_inoutwires, vector<FunctionSymbolParam> v_param, string name_module, string name_instance){
    InstanceSymbol instance(v_inoutwires,v_param, this -> v_wire, name_module, name_instance);
    this -> v_instances.push_back(instance);
}

int FunctionSymbol :: searchInstance(string name, int nlin,int ncol){
    for (int i = 0; i <  this -> v_instances.size();++i) {
        if ( this -> v_instances.at(i).getNameInstance() == name) {
            return  i;
        }
    }
    // fail: instance  not declared
    msgError(ERRINSNOTFOUND, nlin, ncol - name.length(), name.c_str());
    return -1;

}

void FunctionSymbol :: createFileModule(bool verilogDef)
{
    /* Start wriking the file */
    this -> createFileModuleDefines();
     /* DEFINES */
    if (verilogDef){
        this -> output_file_data += "`include \"defines.vh\"\n";
    }
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
    
    /* Add define not define type to none */
    this -> output_file_data +="`default_nettype none\n";
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
    /* Putin some extra coments */
    this -> output_file_data += "//***Internal logic generated by compiler***  \n";
    /* Add Wires */
    for (int i = 0; i < this -> v_wire.size(); ++i){
        if (this -> v_wire.at(i).getPrint()){
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
    }
    if (this -> v_vwire.size() > 0){
        this -> output_file_data += "//***Auxiliar Wires***  \n";
    }
    for (int i = 0; i < this -> v_vwire.size(); ++i){
        string width = "";
        if (v_vwire.at(i).getWidthOut() != ""){
            width = v_vwire.at(i).getWidthOut() + " ";
        }
        this -> output_file_data += tabulate + "wire " + width + v_vwire.at(i).getNameWire() + "; // Auxiliar Wire\n";
    }
    this -> output_file_data +="\n";
    /* Add instances */
    for (int i = 0; i < this -> v_instances.size(); ++i){
        this -> output_file_data += this -> v_instances.at(i).generateInstance();
    }
    this -> output_file_data +="\n";
    /* Putin some extra coments */

    if (this->verilog_dump != ""){
        this ->output_file_data += "//***Dumped Internal logic***";
        this ->output_file_data += this->verilog_dump;
        this -> output_file_data += "\n";

    }
   
    this -> output_file_data += "//***Handcrafted Internal logic*** \n";
    this -> output_file_data += "//TODO\n";
    /* finish file */
    this -> output_file_data += "endmodule\n";
}

void FunctionSymbol :: createRunTest(bool definitions, bool first, bool qtb, bool vtb, bool avb){

    if(first)
    {
        this->createTbFolder();
       if(qtb){
            this->createQuestaSimFolder();
       }
       if (vtb){
            this->createVerilatorFolder();
       }
    }
    if(qtb){
        this->createTbRunQuesta(first);
        this->createTbQuesta(definitions);
    }
    if(vtb){
        this->createTbRunVerilator(first);
        this->createTbVerilator(definitions,avb);
    }
    



}

void FunctionSymbol :: createTbFolder(){
    string output_folder = this -> projectFolderName + "tb";
    if (mkdir(output_folder.c_str(), 0777) == -1) 
        cerr << "Error : " << strerror(errno) << endl; 
}

void FunctionSymbol :: createQuestaSimFolder(){
    string output_folder = this -> projectFolderName + "tb/questa_sim";
    if (mkdir(output_folder.c_str(), 0777) == -1) 
        cerr << "Error : " << strerror(errno) << endl;
}

void FunctionSymbol :: createVerilatorFolder(){
    string output_folder = this -> projectFolderName + "tb/verilator";
    if (mkdir(output_folder.c_str(), 0777) == -1) 
        cerr << "Error : " << strerror(errno) << endl;
}

void FunctionSymbol :: createTbRunVerilator(bool first){
    string output_file = "";
    if (first){
        output_file = this -> projectFolderName + "tb/verilator/runtest.sh";
    }
    else{
        output_file = this -> projectFolderName + "tb/verilator/runtest_" + this->name + ".sh";
    }
    // create file
    string output = "RED='\\033[0;31m'\n";
    output += "NC='\\033[0m' # No Color\n";
    output += "\n";
    output += "echo -e \"${RED} Modify the script if you need to set your verilator path ${NC}\"\n";
    output += "#____________start set path verilator\n";
    output += "#export TOP=/home/bscuser/BSC/lowrisc\n";
    output += "#export VERILATOR_ROOT=$TOP/verilator\n";
    output += "#____________end set path verilator\n";
    output += "rm -rf obj_dir\n";
    output += "verilator -Wall --cc --trace ../../hdl/" + this -> name + ".v -I../../hdl/ --exe tb_" + this -> name + ".cpp -CFLAGS \"-std=c++14\"\n";
    output += "\n";
    output += "cd obj_dir/\n";
    output += "make -f V" + this -> name + ".mk \n";
    output += "cd ../\n";
    output += "./obj_dir/V" + this -> name + "\n";
    output += "gtkwave obj_dir/V" + this -> name + ".vcd  test_" + this->name + ".gtkw\n";
    output += "\n";
    // create file
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", output_file.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, "%s",output.c_str());
    fclose(f);
}

void FunctionSymbol :: createTbRunQuesta(bool first){
    string output_file = "";
    if (first){
        output_file = this -> projectFolderName + "tb/questa_sim/runtest.sh";
    }
    else{
        output_file = this -> projectFolderName + "tb/questa_sim/runtest_" + this->name + ".sh";
    }
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
    fprintf(f, "%s",output.c_str());
    fclose(f);

}
void FunctionSymbol :: createTbVerilator(bool definitions, bool avb){

    string output_file = this -> projectFolderName + "tb/verilator/tb_" + this->name + ".cpp";
    string output = "";
    output += "#include \"V" + this->name + ".h\"\n";
    output += "#include \"verilated.h\"\n";
    output += "#include \"verilated_vcd_c.h\"\n";
    output += "#include <algorithm>\n";
    output += "#include <iostream>\n";
    output += "#define TRACE_DEF true\n";
    output += "\n";
    // add the assertions
    if(avb){
        output += "//#define NDEBUG\n";
        output += "//#define NABORT\n";
        output += "\n";
        output += "/**\n";
        output += "* Custom assertion logic\n";
        output += "* Usage:\n";
        output += "* - define NABORT to continue the execution after a failed assert.\n";
        output += "* - define NDEBUG to disable the assertion logic\n";
        output += "**/";
        output += "\n";
        output += "#if !defined(NDEBUG) && !defined(NABORT)\n";
        output += "  extern char *__progname;\n";
        output += "  #define ASSERT(step,left,operator,right) {\\\n";
        output += "    if(!((left) operator (right))){ \\\n";
        output += "      std::cerr << \"\\033[31m\" << __progname << \": \" << __FILE__ << \":\" << __LINE__ <<\": \" << __PRETTY_FUNCTION__ \\\n";
        output += "      <<\". Assertion \\\'\" << #left << \" \" << #operator << \" \" << #right << \"\\\' failed in Step \" << step << \".\\033[0m\\nLeft Value :\\033[31m[\" \\\n";
        output += "      << (left) << \"]\\033[0m\\nRight Value   :\\033[31m[\" << (right) << \"]\\033[0m\" << std::endl; \\\n";
        output += "      exit(0); \\\n";
        output += "    }\\\n";
        output += "  }\n";
        output += "#elif !defined(NDEBUG) && defined(NABORT)\n";
        output += "  extern char *__progname;\n";
        output += "  #define ASSERT(step,left,operator,right) {\\\n";
        output += "    if(!((left) operator (right))){ \\\n";
        output += "      std::cerr << \"\\033[31m\" << __progname << \": \" << __FILE__ << \":\" << __LINE__ <<\": \" << __PRETTY_FUNCTION__ \\\n";
        output += "      <<\". Assertion \\\'\" << #left << \" \" << #operator << \" \" << #right << \"\\\' failed in Step \" << step << \".\\033[0m\\nLeft Value :\\033[31m[\" \\\n";
        output += "      << (left) << \"]\\033[0m\\nRight Value   :\\033[31m[\" << (right) << \"]\\033[0m\" << std::endl; \\\n";
        output += "    }\\\n";
        output += "  }\n";
        output += "#else\n";
        output += "  #define ASSERT(step,left,operator,right)\n";
        output += "#endif\n";
        output += "/**\n";
        output += "* Custom assertion logic\n";
        output += "**/\n";
        output += "\n";

    }
    output += "//time for waveforms\n";
    output += "vluint64_t main_time =0;//current simulation time\n";
    output += "double sc_time_stamp(){ //called by $time in verilog\n";
    output += "    return main_time;   //converts to double , to match\n";
    output += "}\n";
    output += "// debug function to generate waveforms and clock\n";
    output += "void ticktoc_and_trace(V" + this->name +"* module,VerilatedVcdC* tfp){\n";
    output += "  //waveforms and tick clock\n";
    output += "  if (tfp != NULL){\n";
    output += "  module->eval();\n";
    output += "  module->clk_i = !module->clk_i;\n";
    output += "  module->eval();\n";
    output += "  tfp->dump (main_time);\n";
    output += "  module->eval();\n";
    output += "  main_time++;\n";
    output += "  module->eval();\n";
    output += "  module->clk_i = !module->clk_i;\n";
    output += "  module->eval();\n";
    output += "  tfp->dump (main_time);\n";
    output += "  module->eval();\n";
    output += "  main_time++;\n";
    output += "  module->eval();\n";
    output += "  }else{\n";
    output += "  module->eval();\n";
    output += "  module->clk_i = !module->clk_i;\n";
    output += "  module->eval();\n";
    output += "  module->clk_i = !module->clk_i;\n";
    output += "  module->eval();\n";
    output += " }\n";
    output += "}\n";
    output += "void tick_and_trace(V" + this->name +"* module,VerilatedVcdC* tfp){\n";
    output += "  //waveforms and tick clock\n";
    output += "  if (tfp != NULL){\n";
    output += "  module->eval();\n";
    output += "  module->clk_i = !module->clk_i;\n";
    output += "  module->eval();\n";
    output += "    tfp->dump (main_time);\n";
    output += "  module->eval();\n";
    output += "    main_time++;\n";
    output += "  module->eval();\n";
    output += "  }else{\n";
    output += "  module->eval();\n";
    output += "  module->clk_i = !module->clk_i;\n";
    output += "  module->eval();\n";
    output += "  }\n";
    output += "}\n";
    output += "\n";
    output +="//*** TODO ***\n";
    output += "struct TestCase {\n";
    output += "    const char* name;\n";
    output += "    bool rst_i;\n";
    output += "    uint32_t addr_i;\n";
    output += "};\n";
    output += "\n";
    output +="//*** TODO ***\n";
    output += "TestCase test_cases[] {\n";
    output += "//name            rst addr\n";
    output += "    { \"step0\"       ,0  , 0xFFFF },\n";
    output += "    { \"step1\"       ,0  , 0xFFFF },\n";
    output += "    { \"step2\"       ,0  , 0x11FF },\n";
    output += "    { \"step3\"       ,0  , 0xFF11 },\n";
    output += "};\n";
    output += "\n";
    output += "int main(int argc, char **argv, char **env) {\n";
    output += "  //enable waveforms\n";
    output += "  bool vcdTrace= TRACE_DEF;\n";
    output += "  VerilatedVcdC* tfp =NULL;\n";
    output += "  //declare my module\n";
    output += "  Verilated::commandArgs(argc, argv);\n";
    output += "  V" + this->name +"* DUT = new V" + this->name + ";\n";
    output += "  //enable waveforms\n";
    output += "  if(vcdTrace)\n";
    output += "  {\n";
    output += "    Verilated::traceEverOn(true);\n";
    output += "    tfp= new VerilatedVcdC;\n";
    output += "    DUT->trace(tfp,99);\n";
    output += "    std::string vcdname = argv[0];\n";
    output += "    vcdname += \".vcd\";\n";
    output += "    std::cout << vcdname << std::endl;\n";
    output += "    tfp->open(vcdname.c_str());\n";
    output += "  }\n";
    output += "\n";
    output +="//*** TODO ***\n";
    output += "  //initial reset\n";
    output += "  DUT->rst_i=1;\n";
    output += "  ticktoc_and_trace(DUT,tfp);\n";
    output += "  DUT->rst_i=0;\n";
    output += "  ticktoc_and_trace(DUT,tfp);\n";
    output += " //loop through test cases \n";
    output += " int num_test_cases = sizeof(test_cases)/sizeof(TestCase);\n";
    output += " for(int k = 0; k < num_test_cases; k++) {\n";
    output += "      TestCase *test_case = &test_cases[k];\n";
    output += "      //Feed addres\n";
    output += "      DUT->rst_i=test_case->rst_i;\n";
    output += "      DUT->addr_i=test_case->addr_i;\n";
    output += "      //Advance one cycle\n";
    output += "      ticktoc_and_trace(DUT,tfp);\n";
    output += "  }\n";
    output += "//waveforms\n";
    output += "  if (tfp != NULL){\n";
    output += "    tfp->dump (main_time);\n";
    output += "    main_time++;\n";
    output += "  }\n";
    output += "  tfp->close();\n";
    output += "  DUT->final();\n";
    output += "  delete tfp;\n";
    output += "  delete DUT;\n";
    output += "exit(0);\n";
    output += "}\n";
    output += "\n";

    // cretate file
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", output_file.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, "%s",output.c_str());
    fclose(f);


}

void FunctionSymbol :: createTbQuesta(bool definitions){
    string output_file = this -> projectFolderName + "tb/questa_sim/tb_" + this->name + ".v";
    string output = "";
    output += "//-----------------------------------------------------\n";
    output += "// Project Name : " + this -> projectName + "\n";
    output += "// File Name    : tb_" + this->name + ".v\n";
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
            output += tabulate +"localparam integer " + this -> v_param.at(i).getName() + " = " + value + ";\n";
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
            output += tabulate +  type + " tb_" + this -> v_inoutwires.at(i).getNameVerilog() + ";\n";
           
        }
        else{
            /* Rest INOUT parameter */
            output += tabulate + type + " " + this -> v_inoutwires.at(i).getWidth() + " tb_" + this -> v_inoutwires.at(i).getNameVerilog() + ";\n";
           
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
                output += tabulate + tabulate + "." + this -> v_param.at(i).getName() + " (`" + this -> v_param.at(i).getValue() + ")\n";
            }
            else{
                output += tabulate + tabulate + "." + this -> v_param.at(i).getName() + " (`" + this -> v_param.at(i).getValue() + "),\n";
            }
        }
        output += tabulate + ")" + "\n" + tabulate;
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
    output += tabulate +"//*** TODO ***\n";
    output += tabulate +"//initial tb_clk_i = 0;\n";
    output += tabulate +"//always #CLK_HALF_PERIOD tb_clk_i = !tb_clk_i;\n";
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
    fprintf(f, "%s",output.c_str());
    fclose(f);

}


void FunctionSymbol :: printToFile()
{
    /* create file */
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", this -> filename_asociated.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, "%s",this -> output_file_data.c_str());
    fclose(f);

}

string FunctionSymbol :: getLibData(){
    string output = "";
    // start definition
    output += "#\n";
    output += "#"+ this->name +"\n";
    output += "#\n";
    // create names
    output += "DEF "+ this->name + " U 0 40 Y Y 1 F N\n";
    output += "F0 \"U\" 0 0 50 H V C CNN\n";
    output += "F1 \"" + this->name + "\" 0 100 50 H V C CNN\n";
    output += "F2 \"\" 0 0 50 H I C CNN\n";
    output += "F3 \"\" 0 0 50 H I C CNN\n";
    // DRAW Face
    output += "DRAW\n";
    // get parameters
    int number_of_inputs = 0;
    int number_of_outpus = 0;
    for (int i = 0; i < this -> v_inoutwires.size();++i) {
        if (this -> v_inoutwires.at(i).getType() == IN){
                number_of_inputs += 1;
        }
        else if (this -> v_inoutwires.at(i).getType() == OUT){
            number_of_outpus += 1;
        }
        else if (this -> v_inoutwires.at(i).getType() == INOUT){
            number_of_outpus += 1;
        }
    }

    int height_module = std::max(DEFAULTMODULEHEIGHT,(CRERANCEINTOP) + std::max(number_of_inputs,number_of_outpus) * DISTANCEBETWEENPINS);
    int width_module = DEFAULTMODULEWIDTH;
    // size of the module
    output += "S 0 " + std::to_string(height_module) + " " + std::to_string(width_module) + " 0 0 1 0 N\n";
    // create object for the 
    this -> functionDesig = new ComponentFunctionSymbol(height_module,width_module);
    // add the connections
    // inputs first
    int aux_position = height_module - CRERANCEINTOP;
    int number_of_pin = 1;
    for (int i = 0; i < this -> v_inoutwires.size();++i) {
        if (this -> v_inoutwires.at(i).getType() == IN){
                output += "X "+ this -> v_inoutwires.at(i).getName() + " " + std::to_string(number_of_pin) +" -"+ std::to_string(PINLENGH) + " " + std::to_string(aux_position) + " 100 R 50 50 1 1 I\n";
                this -> functionDesig->addNewPin(aux_position,IN,LEFT,this -> v_inoutwires.at(i).getName());
                aux_position = aux_position - DISTANCEBETWEENPINS;
                number_of_pin += 1;

        }
        
    }
    // outputs
    aux_position = height_module - CRERANCEINTOP;
    for (int i = 0; i < this -> v_inoutwires.size();++i) {
        if (this -> v_inoutwires.at(i).getType() != IN){
                output += "X "+ this -> v_inoutwires.at(i).getName() + " " + std::to_string(number_of_pin) +" "+ std::to_string(width_module + PINLENGH) +" " + std::to_string(aux_position) + " 100 L 50 50 1 1 O\n";
                this -> functionDesig->addNewPin(aux_position,this -> v_inoutwires.at(i).getType(),RIGHT,this -> v_inoutwires.at(i).getName());
                aux_position = aux_position - DISTANCEBETWEENPINS;
                number_of_pin += 1;
        }
    }
    // finish file
    output += "ENDDRAW\nENDDEF\n";
   



    return output;
}
void FunctionSymbol :: createProjectFile(string projectFolder, string name){
    string output_file = projectFolder + "/kicad/" + name + ".pro";
    string output = "";
    // init creation of default folder
    output += "update=22/05/2015 07:44:53\n";
    output += "version=1\n";
    output += "last_client=kicad\n";
    output += "[general]\n";
    output += "version=1\n";
    output += "RootSch=\n";
    output += "BoardNm=\n";
    output += "[pcbnew]\n";
    output += "version=1\n";
    output += "LastNetListRead=\n";
    output += "UseCmpFile=1\n";
    output += "PadDrill=0.600000000000\n";
    output += "PadDrillOvalY=0.600000000000\n";
    output += "PadSizeH=1.500000000000\n";
    output += "PadSizeV=1.500000000000\n";
    output += "PcbTextSizeV=1.500000000000\n";
    output += "PcbTextSizeH=1.500000000000\n";
    output += "PcbTextThickness=0.300000000000\n";
    output += "ModuleTextSizeV=1.000000000000\n";
    output += "ModuleTextSizeH=1.000000000000\n";
    output += "ModuleTextSizeThickness=0.150000000000\n";
    output += "SolderMaskClearance=0.000000000000\n";
    output += "SolderMaskMinWidth=0.000000000000\n";
    output += "DrawSegmentWidth=0.200000000000\n";
    output += "BoardOutlineThickness=0.100000000000\n";
    output += "ModuleOutlineThickness=0.150000000000\n";
    output += "[cvpcb]\n";
    output += "version=1\n";
    output += "NetIExt=net\n";
    output += "[eeschema]\n";
    output += "version=1\n";
    output += "LibDir=\n";
    output += "[eeschema/libraries]";

    // create file
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", output_file.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, "%s",output.c_str());
    fclose(f);

}


void FunctionSymbol :: CreateSchFile(string projectName, std::map<string, FunctionSymbol*> mapOfLeafsModules){
    string output = "";
    string output_file = projectName + "/kicad/" + this -> name + ".sch";
    // start definition
    // create the basic stuff
    output += "EESchema Schematic File Version 4\n";
    output += "EELAYER 30 0\n";
    output += "EELAYER END\n";
    output += "$Descr A2 11693 8268\n";
    output += "encoding utf-8\n";
    output += "Sheet 1 1\n";
    output += "Title \"\"\n";
    output += "Date \"\"\n";
    output += "Rev \"\"\n";
    output += "Comp \"\"\n";
    output += "Comment1 \"\"\n";
    output += "Comment2 \"\"\n";
    output += "Comment3 \"\"\n";
    output += "Comment4 \"\"\n";
    output += "$EndDescr\n";
    
    for (int i = 0; i < this -> v_instances.size(); ++i){
        // check if the module of the instance is a leaf or have more components
        if(mapOfLeafsModules.at(this -> v_instances.at(i).getName())->isLeaf()){
            // is leaf create component
            this -> v_instances.at(i).instancenDesig = new InstanceComponentFunctionSymbol(XPOSITIONBASE + i * CLEARANCEBETWEENMODULES, YPOSITIONBASE,COMPONENT, i);
            ComponentFunctionSymbol *a = mapOfLeafsModules.at(this -> v_instances.at(i).getName())->functionDesig;
            output += this -> v_instances.at(i).instancenDesig -> generateSchematicDesing(projectName,this -> v_instances.at(i).getName(),this -> v_instances.at(i).getNameInstance(), a);
            
        }
        else {
            // no leaf compononet create sheet
            this -> v_instances.at(i).instancenDesig = new InstanceComponentFunctionSymbol(XPOSITIONBASE + i * CLEARANCEBETWEENMODULES, YPOSITIONBASE,SHEET, i);
            output += this -> v_instances.at(i).instancenDesig -> generateSchematicDesing(projectName,this -> v_instances.at(i).getName(),this -> v_instances.at(i).getNameInstance(),mapOfLeafsModules);
        }
            output += "$EndSheet\n";
    }
    // start creating the lablels
    string aux_label_type = "";
    int labels_input = 0;
    int labels_output = 0;
    for (int i = 0; i < this -> v_inoutwires.size();++i) {
         if (this -> isTop) {
            aux_label_type = "GLabel";
        }else{
            aux_label_type = "HLabel";
        }
        if (this -> v_inoutwires.at(i).getType() == IN){
            output += "Text " + aux_label_type + " " + std::to_string(XLABELBASEINPUT) + " " + std::to_string(YLABELBASE + labels_input*CLEARANCEBETWEENLABELS) + " 0    50   Input ~ 0\n";
            output +=  this -> v_inoutwires.at(i).getName() + "\n";
            labels_input +=1;
        }
        else{
            output += "Text " + aux_label_type + " " + std::to_string(XLABELBASEOUTPUT) + " " + std::to_string(YLABELBASE + labels_output*CLEARANCEBETWEENLABELS) + " 2    50   Output ~ 0\n";
            output +=  this -> v_inoutwires.at(i).getName() + "\n";
            labels_output +=1;
        }  
    }
    // Wires desing
    // loop over all wires
    for (int i = 0; i < this -> v_wire.size(); ++i){
        // get the diferent connections
        // loop over all instances to search for the connection
        int xInitialPos = 0;
        int yInitialPos = 0;
        int xFinalPos = 0;
        int yFinalPos = 0;

        for (int j = 0; j < this -> v_instances.size(); ++j){
            // are leaves
            if (this -> v_instances.at(j).getNameInstance() == this -> v_wire.at(i).getFuncionIn() && mapOfLeafsModules.at(v_instances.at(j).getName())->isLeaf()) {
                // the instance is funtion in
                // now search the position of the pin to the the base x and y
                int xpostionpin = 0;
                for(int w = 0; w < this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.size(); ++w){
                    string type = "";
                    if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == IN){type = "_i";}
                    else if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == OUT){type = "_o";}
                    else if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == INOUT){type = "_io";}
                    
                    if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getName() + type == v_wire.at(i).getNameIn()){
                        // we get the pin extract position
                        xpostionpin = this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getPosition();
                        break;
                    }
                }
                // now we have the x position base on the component so whe need to get base of the componet in orther to get the global position of the pin
                xFinalPos = this -> v_instances.at(j).instancenDesig -> getXBasePosition() - PINLENGH;
                yFinalPos = this -> v_instances.at(j).instancenDesig -> getyBasePosition() - xpostionpin;
            }
            else if (this -> v_instances.at(j).getNameInstance() == this -> v_wire.at(i).getFuncionOut() && mapOfLeafsModules.at(v_instances.at(j).getName())->isLeaf()) {
                // the instance is funtion out
                // now search the position of the pin to the the base x and y
                int xpostionpin = 0;
                for(int w = 0; w < this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.size(); ++w){
                    string type = "";
                    if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == IN){type = "_i";}
                    else if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == OUT){type = "_o";}
                    else if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == INOUT){type = "_io";}

                    if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getName() + type == v_wire.at(i).getNameOut()){
                        // we get the pin extract position
                        xpostionpin = this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getPosition();
                        break;
                    }
                }
                // now we have the x position base on the component so whe need to get base of the componet in orther to get the global position of the pin
                xInitialPos  = this -> v_instances.at(j).instancenDesig -> getXBasePosition() + this -> v_instances.at(j).instancenDesig-> componentDesig ->getWidth() + PINLENGH;
                yInitialPos  = this -> v_instances.at(j).instancenDesig -> getyBasePosition() - xpostionpin;
            }
            // are no leaves
            /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // hierarchy sheets
            else if (this -> v_instances.at(j).getNameInstance() == this -> v_wire.at(i).getFuncionIn() && !mapOfLeafsModules.at(v_instances.at(j).getName())->isLeaf())
            {
                int xpostionpin = 0;
                for(int w = 0; w < this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.size(); ++w){
                    string type = "";
                    if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == IN){type = "_i";}
                    else if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == OUT){type = "_o";}
                    else if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == INOUT){type = "_io";}
                    
                    if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getName() + type == v_wire.at(i).getNameIn()){
                        // we get the pin extract position
                        xpostionpin = this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getPosition();
                        break;
                    }
                }
                // now we have the x position base on the component so whe need to get base of the componet in orther to get the global position of the pin
                xFinalPos = this -> v_instances.at(j).instancenDesig -> getXBasePosition();
                yFinalPos = xpostionpin;
               
            }
            else if (this -> v_instances.at(j).getNameInstance() == this -> v_wire.at(i).getFuncionOut() && !mapOfLeafsModules.at(v_instances.at(j).getName())->isLeaf())
            {
                int xpostionpin = 0;
                for(int w = 0; w < this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.size(); ++w){
                    string type = "";
                    if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == IN){type = "_i";}
                    else if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == OUT){type = "_o";}
                    else if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getType() == INOUT){type = "_io";}

                    if (this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getName() + type == v_wire.at(i).getNameOut()){
                        // we get the pin extract position
                        xpostionpin = this -> v_instances.at(j).instancenDesig -> componentDesig -> v_pins.at(w).getPosition();
                        break;
                    }
                }
                // now we have the x position base on the component so whe need to get base of the componet in orther to get the global position of the pin
                xInitialPos  = this -> v_instances.at(j).instancenDesig -> getXBasePosition() + this -> v_instances.at(j).instancenDesig-> componentDesig ->getWidth();
                yInitialPos  = xpostionpin;
            }
            
            

        }
        //write the wire in the file
        output += "Wire Wire Line\n" + std::to_string(xInitialPos) + " "+ std::to_string(yInitialPos)+ " " + std::to_string(xFinalPos) +" " + std::to_string(yFinalPos) + "\n";

    }
    output += "$EndSCHEMATC";
    // create file sch
    char buf[0x100];
    snprintf(buf, sizeof(buf), "%s", output_file.c_str());
    FILE *f = fopen(buf, "w");
    fprintf(f, "%s",output.c_str());
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
bool   FunctionSymbol :: getIsTop(){return this -> isTop;}
int    FunctionSymbol :: getNumberOfInstances(){return this->v_instances.size();};
bool   FunctionSymbol :: isLeaf(){return this->v_instances.size() == 0 ? true : false;}
vector<FunctionSymbolParam> FunctionSymbol :: getFunctionSymbolParam(){return this -> v_param;}
vector<InoutSymbol> FunctionSymbol :: getInoutSymbol(){return this -> v_inoutwires;}


//setters

void FunctionSymbol :: setName(string name){ this -> name = name;}
void FunctionSymbol :: setFunction(string function) { this -> function = function;}
void FunctionSymbol :: setDescription(string description) { this -> description = description;}
void FunctionSymbol :: setCode(string code) { this -> code = code;}
void FunctionSymbol :: setProjectName(string projectName) { this -> projectName = projectName;}
void FunctionSymbol :: setReferences(string references) { this -> references = references;}
