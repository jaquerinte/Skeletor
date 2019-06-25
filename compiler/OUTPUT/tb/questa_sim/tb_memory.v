//-----------------------------------------------------
// Project Name : a.out
// File Name    : tb_memory.v
// Function     : Memory access
// Description  : This is a detailed explanation use several lines to explain everything. You will forget how smart you where when coding this module
// Coder        : G.Cabo

//***Headers***
`include "defines.vh"
//***Test bench***
module tb_memory();
//***Parameters***
    parameter CLK_PERIOD      = 2;
    parameter CLK_HALF_PERIOD = CLK_PERIOD / 2;
    localparam integer AddrSize = 1;
//***Signals***
    reg  tb_rst_i ;
    reg  tb_clk_i ;
    reg  tb_wreg_i ;
    reg  tb_m2reg_i ;
    reg  tb_wmem_i ;
    reg [`BITS_REGFILE : 0] tb_destination_i ;
    reg [AddrSize - 1 : 0] tb_aluresult_i ;
    reg [AddrSize - 1 : 0] tb_op2_i ;
    wire  tb_wreg_o ;
    wire  tb_m2reg_o ;
    wire [`BITS_REGFILE : 0] tb_destination_o ;
    wire [AddrSize - 1 : 0] tb_aluresult_o ;
    wire tb_dmemout_o ;
//***Module***
    memory #(
        .AddrSize (`1)
    )
        dut_memory(
        .rst_i         (tb_rst_i ),
        .clk_i         (tb_clk_i ),
        .wreg_i         (tb_wreg_i ),
        .m2reg_i         (tb_m2reg_i ),
        .wmem_i         (tb_wmem_i ),
        .destination_i         (tb_destination_i ),
        .aluresult_i         (tb_aluresult_i ),
        .op2_i         (tb_op2_i ),
        .wreg_o         (tb_wreg_o ),
        .m2reg_o         (tb_m2reg_o ),
        .destination_o         (tb_destination_o ),
        .aluresult_o         (tb_aluresult_o ),
        .dmemout_o         (tb_dmemout_o )
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
            $dumpvars(0,dut_memory);
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
