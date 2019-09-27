//-----------------------------------------------------
// Project Name : Sample_Code
// File Name    : tb_simple_example.sv
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
//***Test bench***
module tb_simpleExample();
//***Parameters***
    parameter CLK_PERIOD      = 2;
    parameter CLK_HALF_PERIOD = CLK_PERIOD / 2;
    localparam integer TransAddrSize  = `T_ADDR_SIZE;//Size of translated address
    localparam integer AddrSize  = `ADDR_SIZE;        //Size of non translated address 

//***Signals***
    reg tb_clk_i;
    reg tb_rst_i;
    reg [AddrSize-1:0] tb_addr_i;
    wire [TransAddrSize-1:0] tb_taddr_o;
    wire tb_rdy_o;

//***Module***
    simpleExample #(
        .TransAddrSize   (TransAddrSize),
        .AddrSize        (AddrSize)
    )
    dut_simpleExample(
        .rst_i    (tb_rst_i),
        .clk_i    (tb_clk_i),
        .addr_i   (tb_addr_i),
        .taddr_o  (tb_taddr_o),
        .rdy_o    (tb_rdy_o)
    );

//***clk_gen***
    initial tb_clk_i = 0;
    always #CLK_HALF_PERIOD tb_clk_i = !tb_clk_i;

//***task reset_dut***
    task reset_dut;
        begin
            $display("*** Toggle reset.");
            tb_rst_i = 0;
            #(100 * CLK_PERIOD);
            tb_rst_i = 1;
        end
    endtask

//***task init_sim***
    task init_sim;
        begin
            $display("*** init sim.");
            tb_clk_i = 0;
            tb_rst_i = 1;
        end
    endtask
//***task init_dump**
    task init_dump;
        begin
            $dumpfile("test.vcd");
            $dumpvars(0,dut_simpleExample);
        end
    endtask

//***task test_sim**
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
