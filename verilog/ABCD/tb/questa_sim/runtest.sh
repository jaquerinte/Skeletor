vlib simpleExample
vmap work $PWD/simpleExample
vlog +incdir+../../hdl/ ../../hdl/*.v ../../hdl/*.vh tb_simpleExample.v
vmake simpleExample/ > Makefile
vsim
#gtkwave test.vcd 
