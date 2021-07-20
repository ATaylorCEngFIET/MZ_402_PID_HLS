// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2021.1 (64-bit)
// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// ==============================================================
# 1 "C:/HLS/PID/pid.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "C:/HLS/PID/pid.cpp"
# 1 "C:/HLS/PID/pid.h" 1
typedef float data_type;
data_type PID (data_type set_point, data_type KP, data_type KI, data_type KD, data_type sample);
# 2 "C:/HLS/PID/pid.cpp" 2

static data_type error_prev;
static data_type i_prev;

data_type PID (data_type set_point, data_type KP, data_type KI, data_type KD, data_type sample)
{
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=s_axilite port=sample
#pragma HLS INTERFACE mode=s_axilite port=KD
#pragma HLS INTERFACE mode=s_axilite port=KI
#pragma HLS INTERFACE mode=s_axilite port=KP
#pragma HLS INTERFACE mode=s_axilite port=set_point
 data_type error, i, d, p;


 data_type temp;
 data_type op;


 error = set_point - sample;
 p = error;
 i = (error + i_prev) ;
 d = (error - error_prev) ;


 op = (KP*p)+(KI*i)+(KD*d);
 error_prev = error;
 i_prev = i;
 return op;

}
#ifndef HLS_FASTSIM
#ifdef __cplusplus
extern "C"
#endif
float apatb_PID_ir(float, float, float, float, float);
#ifdef __cplusplus
extern "C"
#endif
float PID_hw_stub(float set_point, float KP, float KI, float KD, float sample){
float _ret = PID(set_point, KP, KI, KD, sample);
return _ret;
}
#ifdef __cplusplus
extern "C"
#endif
float apatb_PID_sw(float set_point, float KP, float KI, float KD, float sample){
float _ret = apatb_PID_ir(set_point, KP, KI, KD, sample);
return _ret;
}
#endif
# 32 "C:/HLS/PID/pid.cpp"

