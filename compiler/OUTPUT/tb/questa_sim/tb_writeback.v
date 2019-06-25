//-----------------------------------------------------
// Project Name : a.out
// File Name    : tb_writeback.v
// Function     : Write back to register file
// Description  : This is a detailed explanation use several lines to explain everything. You will forget how smart you where when coding this module
// Coder        : G.Cabo
// References   : https://github.com/jaquerinte/MA_2019.git

//***Headers***
`include "defines.vh"
//***Test bench***
module tb_writeback();
//***Parameters***
    parameter CLK_PERIOD      = 2;
    parameter CLK_HALF_PERIOD = CLK_PERIOD / 2;
    localparam integer AddrSize = 1;
//***Signals***
    reg  tb_rst_i ;
    reg  tb_clk_i ;
    reg  tb_wreg_i ;
    reg  tb_m2reg_i ;
    reg [AddrSize - 1 : 0] tb_aluresult_i ;
    reg [AddrSize - 1 : 0] tb_dmemout_i ;
    reg [`BITS_REGFILE : 0] tb_destination_i ;
    wire  tb_wreg_o ;
    wire [`BITS_REGFILE : 0] tb_destination_o ;
    wire tb_datareg_o ;
//***Module***
    writeback #(
        .AddrSize (`1)
    )
        dut_writeback(
        .rst_i         (tb_rst_i ),
        .clk_i         (tb_clk_i ),
        .wreg_i         (tb_wreg_i ),
        .m2reg_i         (tb_m2reg_i ),
        .aluresult_i         (tb_aluresult_i ),
        .dmemout_i         (tb_dmemout_i ),
        .destination_i         (tb_destination_i ),
        .wreg_o         (tb_wreg_o ),
        .destination_o         (tb_destination_o ),
        .datareg_o         (tb_datareg_o )
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
            $dumpvars(0,dut_writeback);
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
