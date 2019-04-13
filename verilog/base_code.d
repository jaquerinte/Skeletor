

#define T_ADDR_SIZE 32
#define ADDR_SIZE 32
#define N 2

module a (TransAddrSize, AddrSize){
	in clk;
	in rts;
	in [AddrSize -1 : 0] addr;
	out [TransAddrSize-1: 0] taddr;
	out rdy;
}
module b (TransAddrSize, AddrSize){
	in rstn;                           
    in clk;                            
    in [AddrSize-1:0] addr;            
    in [AddrSize-1:0] taddr;            
    out [TransAddrSize-1:0] taddr;      
    out rdy;                            
}

module c(n){
	in rst;
	in clk;
	out rdy;
}

module d(){
	in in1;
	in in2;
	in in3;
	out out1; // no puede ser out porque es una palabra reservada
}

module main simple_example(TransAddrSize = T_ADDR_SIZE, AddrSize = ADDR_SIZE){
	in clk;
	in rts;
	in [AddrSize -1 : 0] addr;
	out [TransAddrSize-1: 0] taddr;
	out rdy;

	wire [TransAddrSize-1:0] simple_example>taddr -> a>taddr;
	wire a>rdy -> d>in1;
	wire b>rdr -> d>in2;
	wire c>rdr -> d>in3;
	
	a(TransAddrSize, AddrSize)[in clk,in rts,in addr]; // no needs to be in order beacuse names match
	b(TransAddrSize, AddrSize)[in rstn=~rts,in clk,in addr,in taddr,out taddr]; // not need to be in orden beacuse use =
	c(N)[in rst, in clk];
	d()[out rdy];

}