//-----------------------------------------------------
// Project Name : Sample_Code
// File Name    : a.v
// Function     : AND current addr_i with previous addr_i
// Description  : This is a detailed explanation use several
//                lines to explain everything. You will forget
//                how smart you where when coding this module
// Coder        : G.Cabo
// References   : https://github.com/jaquerinte/MA_2019.git
//-----------------------------------------------------

//***Headers***
//***Module***
module a #(
        parameter integer TransAddrSize  = 32,  //Size of translated address
        parameter integer AddrSize  = 32        //Size of non translated address 
    )
    (
        input rst_i,                          //Active high reset
        input clk_i,                          //Clock
        input [AddrSize-1:0] addr_i,          //Address
        output [TransAddrSize-1:0] taddr_o,   //Translated address
        output rdy_o                          //Ready
    );
    //***Interal logic generated by compiler***  
    //***Handcrafted Internal logic*** 
    //TODO: This module must AND addr_i and the previous addr_i,
    //      this must happen at the positive edge of the clock.
    //      After reset previous value of addr_i must be set to 0.
    //      rdy_0 must be low at reset and one cycle after.
   
    reg [AddrSize-1:0] prev_addr_d; //Input registers are sufixed with d
    reg prev_rst_d;                 //Input registers are sufixed with d
    always@(posedge clk_i) begin
        if(rst_i) begin
            prev_rst_d <= 1;
            prev_addr_d <= 0;
            rdy_o <= 0;
        end
        else if(prev_rst_d) begin
            prev_rst_d <= 0;
            prev_addr_d <= addr_i;
            taddr_o <= prev_addr_d & addr_i;
            rdy_o <= 0; 
        end
        else begin
            prev_addr_d <= addr_i;
            taddr_o <= prev_addr_d & addr_i;
            rdy_o <= 1; 
        end
    end
endmodule
