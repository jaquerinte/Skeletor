vlib execute
vmap work $PWD/execute
vlog +incdir+../../hdl/ ../../hdl/*.v ../../hdl/*.vh tb_execute.v
vmake execute/ > Makefile
vsim