//-----------------------------------------------------
// Project Name : a.out
// File Name    : tb_decode.v
// Function     : Decode instructions and operand fetch
// Description  : This is a detailed explanation use several lines to explain everything. You will forget how smart you where when coding this module
// Coder        : G.Cabo

//***Headers***
`include "defines.vh"
//***Test bench***
module tb_decode();
//***Parameters***
    parameter CLK_PERIOD      = 2;
    parameter CLK_HALF_PERIOD = CLK_PERIOD / 2;
    localparam integer AddrSize = 1;
//***Signals***
    reg  tb_rst_i ;
    reg  tb_clk_i ;
    reg [AddrSize - 1 : 0] tb_instruction_i ;
    reg [`BITS_REGFILE - 1 : 0] tb_destination_i ;
    reg [AddrSize - 1 : 0] tb_datareg_i ;
    reg  tb_wreg_i ;
    wire  tb_wreg_o ;
    wire  tb_m2reg_o ;
    wire  tb_wmem_o ;
    wire  tb_aluc_o ;
    wire  tb_aluimm_o ;
    wire [`BITS_REGFILE : 0] tb_destination_o ;
    wire [AddrSize - 1 : 0] tb_op1_o ;
    wire [AddrSize - 1 : 0] tb_op2_o ;
    wire tb_extendedimm_o ;
//***Module***
    decode #(
        .AddrSize (`1)
    )
        dut_decode(
        .rst_i         (tb_rst_i ),
        .clk_i         (tb_clk_i ),
        .instruction_i         (tb_instruction_i ),
        .destination_i         (tb_destination_i ),
        .datareg_i         (tb_datareg_i ),
        .wreg_i         (tb_wreg_i ),
        .wreg_o         (tb_wreg_o ),
        .m2reg_o         (tb_m2reg_o ),
        .wmem_o         (tb_wmem_o ),
        .aluc_o         (tb_aluc_o ),
        .aluimm_o         (tb_aluimm_o ),
        .destination_o         (tb_destination_o ),
        .op1_o         (tb_op1_o ),
        .op2_o         (tb_op2_o ),
        .extendedimm_o         (tb_extendedimm_o )
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
            $dumpvars(0,dut_decode);
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
