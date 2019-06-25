vlib memory
vmap work $PWD/memory
vlog +incdir+../../hdl/ ../../hdl/*.v ../../hdl/*.vh tb_memory.v
vmake memory/ > Makefile
vsim