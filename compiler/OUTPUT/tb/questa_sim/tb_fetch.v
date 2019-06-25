//-----------------------------------------------------
// Project Name : a.out
// File Name    : tb_fetch.v
// Function     : Fetch instructions
// Description  : This is a detailed explanation use several lines to explain everything. You will forget how smart you where when coding this module
// Coder        : G.Cabo

//***Headers***
`include "defines.vh"
//***Test bench***
module tb_fetch();
//***Parameters***
    parameter CLK_PERIOD      = 2;
    parameter CLK_HALF_PERIOD = CLK_PERIOD / 2;
    localparam integer AddrSize = 1;
//***Signals***
    reg  tb_rst_i ;
    reg  tb_clk_i ;
    reg [AddrSize - 1 : 0] tb_pc_i ;
    wire [AddrSize - 1 : 0] tb_nextpc_o ;
    wire tb_instruction_o ;
//***Module***
    fetch #(
        .AddrSize (`1)
    )
        dut_fetch(
        .rst_i         (tb_rst_i ),
        .clk_i         (tb_clk_i ),
        .pc_i         (tb_pc_i ),
        .nextpc_o         (tb_nextpc_o ),
        .instruction_o         (tb_instruction_o )
    );

//***clk_gen***
    //*** TODO ***
    //initial tb_clk_i = 0;
    //always #CLK_HALF_PERIOD tb_clk_i = !tb_clk_i;

//***task reset_dut***
    task reset_dut;
        begin
            $display("*** Toggle reset.");
            //*** TODO ***
        end
    endtask

//***task init_sim***
    task init_sim;
        begin
            $display("*** init sim.");
            //*** TODO ***
        end
    endtask

//***task init_dump***
    task init_dump;
        begin
            $dumpfile("test.vcd");
            $dumpvars(0,dut_fetch);
        end
    endtask

//***task test_sim***
    task test_sim;
        begin
            $display("*** test_sim.");
            //***Handcrafted test***
        end
    endtask


//***init_sim***
    initial begin
        init_sim();
        init_dump();
        reset_dut();
        test_sim();
    end

endmodule
