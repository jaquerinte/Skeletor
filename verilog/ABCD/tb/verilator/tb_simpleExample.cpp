//testbench  is INCOMPLETE, do  not REUSE
#include "VsimpleExample.h"
#include "verilated.h"
//waveform
#include "verilated_vcd_c.h"
#include <algorithm> 
#define TRACE_DEF true 

//time for waveforms
vluint64_t main_time =0;//current simulation time
double sc_time_stamp(){ //called by $time in verilog
    return main_time;   //converts to double , to match
}
// debug function to generate waveforms and clock
// debug function to generate waveforms and clock
void ticktoc_and_trace(VsimpleExample* module,VerilatedVcdC* tfp){
  //waveforms and tick clock
  if (tfp != NULL){
  module->eval();
  module->clk_i = !module->clk_i;
  module->eval();
  tfp->dump (main_time);
  module->eval();
    main_time++;
  module->eval();
  module->clk_i = !module->clk_i;
  module->eval();
    tfp->dump (main_time);
  module->eval();
    main_time++;
  module->eval();
  }else{
  module->eval();
  module->clk_i = !module->clk_i;
  module->eval();
  module->clk_i = !module->clk_i;
  module->eval();
  }
}
void tick_and_trace(VsimpleExample* module,VerilatedVcdC* tfp){
  //waveforms and tick clock
  if (tfp != NULL){
  module->eval();
  module->clk_i = !module->clk_i;
  module->eval();
    tfp->dump (main_time);
  module->eval();
    main_time++;
  module->eval();
  }else{
  module->eval();
  module->clk_i = !module->clk_i;
  module->eval();
  }
}



struct TestCase {
    const char* name;
    bool rst_i;
    uint32_t addr_i;
};

TestCase test_cases[] {
//name            rst addr 
    { "step0"       ,0  , 0xFFFF },
    { "step1"       ,0  , 0xFFFF },
    { "step2"       ,0  , 0x11FF },
    { "step3"       ,0  , 0xFF11 },
};

int main(int argc, char **argv, char **env) {
  //enable waveforms
  bool vcdTrace= TRACE_DEF;
  VerilatedVcdC* tfp =NULL;
  //declare my module
  Verilated::commandArgs(argc, argv);
  VsimpleExample* DUT = new VsimpleExample;
  //enable waveforms
  if(vcdTrace)
  {
    Verilated::traceEverOn(true);
    tfp= new VerilatedVcdC;
    DUT->trace(tfp,99);
    std::string vcdname = argv[0];
    vcdname += ".vcd";
    std::cout << vcdname << std::endl;
    tfp->open(vcdname.c_str());
  }
  
  //initial reset 
  DUT->rst_i=1;
  ticktoc_and_trace(DUT,tfp);
  DUT->rst_i=0;
  ticktoc_and_trace(DUT,tfp);
 //loop through test cases 
 int num_test_cases = sizeof(test_cases)/sizeof(TestCase);
 for(int k = 0; k < num_test_cases; k++) {
      TestCase *test_case = &test_cases[k];
      //Feed addres
      DUT->rst_i=test_case->rst_i;
      DUT->addr_i=test_case->addr_i;
      //Advance one cycle
      ticktoc_and_trace(DUT,tfp);
  }
  //waveforms
  if (tfp != NULL){
    tfp->dump (main_time);
    main_time++;
  }
  tfp->close();
  DUT->final();
  delete tfp;
  delete DUT;
exit(0);
}

