module fetch(){
    in  clk;
    in  rst;
    in  pc;
    out  nextpc;
    out  instruction;
}

module execute(){
    in  clk;
    in  rst;
    in  wreg;
    in  m2reg;
    in  wmem;
    in  aluc;
    out  wreg;
    out  m2reg;
    out  wmem;
    out [BITS_REGFILE:0] _destination;
    in [AddrSize-1:0] _extendedimm;
    out [AddrSize-1:0] _op2;
}

module writeback(){
    in  clk;
    in  rst;
    in  wreg;
    in  m2reg;
    in [AddrSize-1:0] _aluresult;
    in [AddrSize-1:0] _dmemout;
    in [BITS_REGFILE:0] _destination;
    out  wreg;
    out [BITS_REGFILE:0] _destination;
    out [AddrSize-1:0] _datareg;
}

module memory(){
    in  clk;
    in  rst;
    in  wreg;
    in  m2reg;
    in  wmem;
    in [BITS_REGFILE:0] _destination;
    in [AddrSize-1:0] _aluresult;
    in [AddrSize-1:0] _op2;
    out  wreg;
    out  m2reg;
    out [BITS_REGFILE:0] _destination;
    out [AddrSize-1:0] _aluresult;
    out [AddrSize-1:0] _dmemout;
}

module decode(){
    in  clk;
    in  rst;
    in [AddrSize-1:0] _instruction;
    in [BITS_REGFILE-1:0] _destination;
    in [AddrSize-1:0] _datareg;
    in  wreg;
    out  wreg;
    out  m2reg;
    out  wmem;
    out  aluc;
    out  aluimm;
    out [BITS_REGFILE:0] _destination;
    out [AddrSize-1:0] _op1;
    out [AddrSize-1:0] _op2;
    out [AddrSize-1:0] _extendedimm;
}

module top main(){
    in  rst;
    in  clk;

    fetch:U1(){
        in  rst = in rst,
        in  clk = in clk
    };

    decode:U2(){
        in  rst = in rst,
        in  clk = in clk
    };

    memory:U3(){
        in  rst = in rst,
        in  clk = in clk
    };

    writeback:U5(){
        in  rst = in rst,
        in  clk = in clk
    };

    execute:U4(){
        in  rst = in rst,
        in  clk = in clk
    };

    wire U3.wreg -> U5.wreg;
    wire U4.m2reg -> U3.m2reg;
    wire U4.wreg -> U3.wreg;
    wire U3.m2reg -> U5.m2reg;
    wire U4.wmem -> U3.wmem;
    wire U4.[BITS_REGFILE:0]_destination -> U3.destination;
    wire U3.[AddrSize-1:0]_aluresult -> U4.extendedimm;
    wire U4.[AddrSize-1:0]_op2 -> U3.op2;
    wire U5.[AddrSize-1:0]_datareg -> U2.datareg;
    wire U1.instruction -> U2.instruction;
    wire U4.wmem -> U2.op1;
    wire U2.[AddrSize-1:0]_op2 -> U4.destination;
    wire U2.[AddrSize-1:0]_extendedimm -> U4.extendedimm;
    wire U3.[AddrSize-1:0]_dmemout -> U5.dmemout;
    wire U3.[BITS_REGFILE:0]_destination -> U5.destination;
    wire U3.[AddrSize-1:0]_aluresult -> U5.aluresult;
    wire U5.wreg -> U2.wreg;
    wire U5.[BITS_REGFILE:0]_destination -> U2.destination;
    wire U1.nextpc -> U1.pc;
    wire U2.aluc -> U4.aluc;
    wire U4.wreg -> U2.aluimm;
    wire U2.wreg -> U4.wreg;
    wire U2.wmem -> U4.wmem;
    wire U4.m2reg -> U2.destination;
    wire U2.m2reg -> U4.m2reg;
}
