//-----------------------------------------------------
// Project Name : Sample_Code
// File Name    : simple_example.v
// Function     : Module to provide a reference output
//                for our compiler
// Description  : This is a detailed explanation use several
//                lines to explain everything. You will forget
//                how smart you where when coding this module
// Coder        : G.Cabo
// References   : https://github.com/jaquerinte/MA_2019.git
//-----------------------------------------------------

//***Headers***
`include "defines.vh"
//***Module***
module simple_example#(
        parameter integer TransAddrSize  = `T_ADDR_SIZE,//Size of translated address
        parameter integer AddrSize  = `ADDR_SIZE        //Size of non translated address 
    )
    (
        input                       clk_i,  //Input clock 
        input                       rst_i,  //Reset active high
        input   [AddrSize-1:0]      addr_i, //Address
        output  [TransAddrSize-1:0] taddr_o,//Translated address
        output                      rdy_o   //Ready
    );
    //***Interal logic generated by compiler***  
    //Module A does: AND current addr_i with previous addr_i
    a #(
        .TransAddrSize   (TransAddrSize),
        .AddrSize        (AddrSize)
    )
    inst_a(
        .rst_i    (rst_i),
        .clk_i    (clk_i),
        .addr_i   (addr_i),
        .taddr_o  (taddr_a_b_int),
        .rdy_o    (rdy_a_d_int)
    );
    //Module B does: OR current addr_i with previous addr_i 
    b #(
        .TransAddrSize  (TransAddrSize),
        .AddrSize       (AddrSize)
    )
    inst_b(
        .rstn_i     (~rst_i),
        .clk_i      (clk_i),
        .addr_i     (addr_i),
        .taddr_i    (taddr_a_b_int),
        .taddr_o    (taddr_o),
        .rdy_o      (rdy_b_d_int)
    );
    //Module C does: rdy_o is high when a n bit counter overflow 
    c #(
        .n   (2)
    )
    inst_c(
        .rst_i  (rst_i),
        .clk_i  (clk_i),
        .rdy_o  (rdy_c_d_int)
    );
    //Module D does: Three way AND gate
    d inst_d(
        .in1_i(rdy_a_d_int),
        .in2_i(rdy_b_d_int),
        .in3_i(rdy_c_d_int),
        .out_o(rdy_o)
    );
    //Internal conexions
    wire [TransAddrSize-1:0] taddr_a_b_int;  // wiring between taddr_o of module A and taddr_i of module B 
    wire rdy_a_d_int;    // wiring between rdy_o of module A and in1_i of module D 
    wire rdy_b_d_int;    // wiring between rdy_o of module B and in2_i of module D 
    wire rdy_c_d_int;    // wiring between rdy_o of module C and in3_i of module D 
    //***Handcrafted Internal logic*** 
    //TODO:No additional internal logic

endmodule
