RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${RED} Modify the script if you need to set your verilator path ${NC}"
#____________start set path verilator
#export TOP=/home/bscuser/BSC/lowrisc
#export VERILATOR_ROOT=$TOP/verilator
#____________end set path verilator
rm -rf obj_dir 
verilator -Wall --cc --trace ../../hdl/simpleExample.v -I../../hdl/ --exe tb_simpleExample.cpp -CFLAGS "-std=c++14"

cd obj_dir/
make -f VsimpleExample.mk 
cd ../
./obj_dir/VsimpleExample
gtkwave obj_dir/VsimpleExample.vcd  test.gtkw

