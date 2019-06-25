vlib decode
vmap work $PWD/decode
vlog +incdir+../../hdl/ ../../hdl/*.v ../../hdl/*.vh tb_decode.v
vmake decode/ > Makefile
vsim