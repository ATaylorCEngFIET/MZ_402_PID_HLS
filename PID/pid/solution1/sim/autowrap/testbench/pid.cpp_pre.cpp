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
