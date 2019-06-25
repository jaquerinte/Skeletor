vlib fetch
vmap work $PWD/fetch
vlog +incdir+../../hdl/ ../../hdl/*.v ../../hdl/*.vh tb_fetch.v
vmake fetch/ > Makefile
vsim