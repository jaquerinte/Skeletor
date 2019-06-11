//-----------------------------------------------------
// Project Name : a.out
//File Name tb_pipeline.v
// Function     : Pipelined processor example to test the tools
// Coder        : G.Cabo
// References   : https://github.com/jaquerinte/MA_2019.git

//***Headers***
`include "defines.vh"
//***Test bench***
module tb_pipeline();
//***Parameters***
    parameter CLK_PERIOD      = 2;
    parameter CLK_HALF_PERIOD = CLK_PERIOD / 2;
    localparam integer AddrSize = `ADDR_SIZE;
//***Signals***
    reg  tb_clk_i ;
    reg tb_rst_i ;
//***Module***
    pipeline #(
        .AddrSize (`ADDR_SIZE)
    )
        dut_pipeline(
        .clk_i         (tb_clk_i ),
        .rst_i         (tb_rst_i )
    );

//***clk_gen***
    initial tb_clk_i = 0;
    always #CLK_HALF_PERIOD tb_clk_i = !tb_clk_i;

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
            $dumpvars(0,dut_pipeline);
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
