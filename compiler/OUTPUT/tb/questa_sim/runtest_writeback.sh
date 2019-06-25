vlib writeback
vmap work $PWD/writeback
vlog +incdir+../../hdl/ ../../hdl/*.v ../../hdl/*.vh tb_writeback.v
vmake writeback/ > Makefile
vsim