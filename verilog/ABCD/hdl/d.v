//-----------------------------------------------------
// Project Name : Sample_Code
// File Name    : d.v
// Function     : Three way AND gate
// Description  : This is a detailed explanation use several
//                lines to explain everything. You will forget
//                how smart you where when coding this module
// Coder        : G.Cabo
// References   : https://github.com/jaquerinte/MA_2019.git
//-----------------------------------------------------

//***Headers***
//***Module***
module d (
        input in1_i,
        input in2_i,
        input in3_i,
        output out_o
    );
    //***Interal logic generated by compiler***  
    //***Handcrafted Internal logic*** 
    //TODO: out_o must be high when all the inputs are high
    assign out_o = in1_i & in2_i & in3_i;
endmodule


