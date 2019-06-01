#define T_ADDR_SIZE 32
#define ADDR_SIZE 32
#define GENERALDESCIPTION "This is a detailed explanation use several lines to explain everything. You will forget how smart you where when coding this module"
#define WORKER1 "G.Cabo"
#define GENRALREFERENCE "https://github.com/jaquerinte/MA_2019.git"

module a (TransAddrSize, AddrSize){
	#function "AND current addr_i with previous addr_i"
	#description GENERALDESCIPTION
	#coder  WORKER1
	#references GENRALREFERENCE

	in clk;
	in rts;
	in [AddrSize -1 : 0] addr;
	out [TransAddrSize-1: 0] taddr;
	out rdy;
}
module b (TransAddrSize, AddrSize){
	#function "OR current addr_i with previous addr_i"
	#description GENERALDESCIPTION
	#coder  WORKER1
	#references GENRALREFERENCE

	in rstn;                           
    in clk;                            
    in [AddrSize-1:0] addr;            
    in [AddrSize-1:0] taddr;            
    out [TransAddrSize-1:0] taddr;      
    out rdy;                            
}

module c(n){
	#function "rdy_o is high when a n bit counter overflow "
	#description GENERALDESCIPTION
	#coder  WORKER1
	#references GENRALREFERENCE

	in rst;
	in clk;
	out rdy;
}

module d(){
	#function  "Three way AND gate"
	#description GENERALDESCIPTION
	#coder  WORKER1
	#references GENRALREFERENCE

	in in1;
	in in2;
	in in3;
	out out1; // no puede ser out porque es una palabra reservada
}

module top simple_example(TransAddrSize = T_ADDR_SIZE, AddrSize = ADDR_SIZE){
	#function  "Module to provide a reference output"
	#coder  WORKER1
	#references GENRALREFERENCE

	in clk;
	in rts;
	in [AddrSize -1 : 0] addr;
	out [TransAddrSize-1: 0] taddr;
	out rdy;


	a:x(TransAddrSize, AddrSize){
		in clk = in clk,
		in rts = in rts,
		in addr = in addr
	};

	b:y(TransAddrSize, AddrSize){
		in rstn = in ~rts,
		in clk = in clk,
		in addr = in addr
	};
	c:z(2){
		in rst = in rst,
		in clk = in clk
	};
	d:w(){
		out rdy = out rdy
	};

	wire [TransAddrSize-1:0] y.taddr -> x.taddr;
	wire x.rdy -> w.in1;
	wire y.rdr -> w.in2;
	wire z.rdr -> w.in3;
	
}
