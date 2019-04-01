#!/bin/bash
rm *.tab.*
rm lex.yy.c
flex  rtl_wiring.l
bison -d rtl_wiring.y
g++ -o rtlcompiler rtl_wiring.tab.c lex.yy.c

