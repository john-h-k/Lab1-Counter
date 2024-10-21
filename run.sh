#!/bin/zsh

name="$1"

rm -rf obj_dir
rm -f "$name.vcd"

verilator -Wall --cc --trace "$name.sv" --exe "${name}_tb.cpp"

make -j -C obj_dir/ -f "V$name.mk" "V$name"

./obj_dir/"V$name"
