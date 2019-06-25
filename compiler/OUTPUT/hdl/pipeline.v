//-----------------------------------------------------
// Project Name : a.out
// Function     : Pipelined processor example to test the tools
// Coder        : G.Cabo
// References   : https://github.com/jaquerinte/MA_2019.git

//***Headers***
`include "defines.vh"
//***Module***
module pipeline #(
        parameter integer AddrSize = `ADDR_SIZE
    )
    (
        input  clk_i ,
        input  rst_i 
    );

//***Interal logic generated by compiler***  
    wire nextpc_IF_IF; // wiring between nextpc_o of module IF and pc_i of module IF
    wire instruction_IF_ID; // wiring between instruction_o of module IF and instruction_i of module ID
    wire wreg_ID_EXE; // wiring between wreg_o of module ID and wreg_i of module EXE
    wire m2reg_ID_EXE; // wiring between m2reg_o of module ID and m2reg_i of module EXE
    wire wmem_ID_EXE; // wiring between wmem_o of module ID and wmem_i of module EXE
    wire aluc_ID_EXE; // wiring between aluc_o of module ID and aluc_i of module EXE
    wire aluimm_ID_EXE; // wiring between aluimm_o of module ID and aluimm_i of module EXE
    wire destination_ID_EXE; // wiring between destination_o of module ID and destination_i of module EXE
    wire op1_ID_EXE; // wiring between op1_o of module ID and op1_i of module EXE
    wire op2_ID_EXE; // wiring between op2_o of module ID and op2_i of module EXE
    wire extendedimm_ID_EXE; // wiring between extendedimm_o of module ID and extendedimm_i of module EXE
    wire wreg_EXE_MEM; // wiring between wreg_o of module EXE and wreg_i of module MEM
    wire m2reg_EXE_MEM; // wiring between m2reg_o of module EXE and m2reg_i of module MEM
    wire wmem_EXE_MEM; // wiring between wmem_o of module EXE and wmem_i of module MEM
    wire destination_EXE_MEM; // wiring between destination_o of module EXE and destination_i of module MEM
    wire aluresult_EXE_MEM; // wiring between aluresult_o of module EXE and aluresult_i of module MEM
    wire op2_EXE_MEM; // wiring between op2_o of module EXE and op2_i of module MEM
    wire wreg_MEM_WB; // wiring between wreg_o of module MEM and wreg_i of module WB
    wire m2reg_MEM_WB; // wiring between m2reg_o of module MEM and m2reg_i of module WB
    wire destination_MEM_WB; // wiring between destination_o of module MEM and destination_i of module WB
    wire dmemout_MEM_WB; // wiring between dmemout_o of module MEM and dmemout_i of module WB
    wire wreg_WB_ID; // wiring between wreg_o of module WB and wreg_i of module ID
    wire destination_WB_ID; // wiring between destination_o of module WB and destination_i of module ID
    wire datareg_WB_ID; // wiring between datareg_o of module WB and datareg_i of module ID

    fetch #(
        .AddrSize (AddrSize)
    )
    inst_IF(
        .rst_i                  (rst_i ),
        .clk_i                  (clk_i ),
        .pc_i                   (nextpc_IF_IF),
        .nextpc_o               (nextpc_IF_IF),
        .instruction_o          (instruction_IF_ID)
    );

    decode #(
        .AddrSize (AddrSize)
    )
    inst_ID(
        .rst_i                  (rst_i ),
        .clk_i                  (clk_i ),
        .instruction_i          (instruction_IF_ID),
        .destination_i          (destination_WB_ID),
        .datareg_i              (datareg_WB_ID),
        .wreg_i                 (wreg_WB_ID),
        .wreg_o                 (wreg_ID_EXE),
        .m2reg_o                (m2reg_ID_EXE),
        .wmem_o                 (wmem_ID_EXE),
        .aluc_o                 (aluc_ID_EXE),
        .aluimm_o               (aluimm_ID_EXE),
        .destination_o          (destination_ID_EXE),
        .op1_o                  (op1_ID_EXE),
        .op2_o                  (op2_ID_EXE),
        .extendedimm_o          (extendedimm_ID_EXE)
    );

    execute #(
        .AddrSize (AddrSize)
    )
    inst_EXE(
        .rst_i                  (rst_i ),
        .clk_i                  (clk_i ),
        .wreg_i                 (wreg_ID_EXE),
        .m2reg_i                (m2reg_ID_EXE),
        .wmem_i                 (wmem_ID_EXE),
        .aluc_i                 (aluc_ID_EXE),
        .aluimm_i               (aluimm_ID_EXE),
        .destination_i          (destination_ID_EXE),
        .op1_i                  (op1_ID_EXE),
        .op2_i                  (op2_ID_EXE),
        .extendedimm_i          (extendedimm_ID_EXE),
        .wreg_o                 (wreg_EXE_MEM),
        .m2reg_o                (m2reg_EXE_MEM),
        .wmem_o                 (wmem_EXE_MEM),
        .destination_o          (destination_EXE_MEM),
        .aluresult_o            (aluresult_EXE_MEM),
        .op2_o                  (op2_EXE_MEM)
    );

    memory #(
        .AddrSize (AddrSize)
    )
    inst_MEM(
        .rst_i                  (rst_i ),
        .clk_i                  (clk_i ),
        .wreg_i                 (wreg_EXE_MEM),
        .m2reg_i                (m2reg_EXE_MEM),
        .wmem_i                 (wmem_EXE_MEM),
        .destination_i          (destination_EXE_MEM),
        .aluresult_i            (aluresult_EXE_MEM),
        .op2_i                  (op2_EXE_MEM),
        .wreg_o                 (wreg_MEM_WB),
        .m2reg_o                (m2reg_MEM_WB),
        .destination_o          (destination_MEM_WB),
        .aluresult_o            (),
        .dmemout_o              (dmemout_MEM_WB)
    );

    writeback #(
        .AddrSize (AddrSize)
    )
    inst_WB(
        .rst_i                  (rst_i ),
        .clk_i                  (clk_i ),
        .wreg_i                 (wreg_MEM_WB),
        .m2reg_i                (m2reg_MEM_WB),
        .aluresult_i            (),
        .dmemout_i              (dmemout_MEM_WB),
        .destination_i          (destination_MEM_WB),
        .wreg_o                 (wreg_WB_ID),
        .destination_o          (destination_WB_ID),
        .datareg_o              (datareg_WB_ID)
    );


//***Handcrafted Internal logic*** 
//TODO
endmodule
