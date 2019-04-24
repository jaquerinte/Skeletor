#!/bin/bash
rm *.tab.*
rm lex.yy.c
flex  vc.l
bison -d vc.y
g++ -o verilog_connector vc.tab.c lex.yy.c

