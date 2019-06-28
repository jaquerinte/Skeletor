vlib pipeline
vmap work $PWD/pipeline
vlog +incdir+../../hdl/ ../../hdl/*.v ../../hdl/*.vh tb_pipeline.v
vmake pipeline/ > Makefile
vsim