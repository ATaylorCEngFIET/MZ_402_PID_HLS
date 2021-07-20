############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project pid
set_top PID
add_files pid.h
add_files pid.cpp
add_files -tb tb_pid.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z007s-clg400-1}
create_clock -period 10 -name default
config_export -format ip_catalog -output C:/HLS/PID/PID.zip -rtl verilog
source "./pid/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design -trace_level port
export_design -rtl verilog -format ip_catalog -output C:/HLS/PID/PID.zip
