#include "pid.h"

static data_type error_prev =0;
static data_type i_prev=0;

data_type PID (data_type set_point, data_type KP, data_type KI, data_type KD, data_type sample, data_type ts, data_type pmax)
{
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=s_axilite port=sample
#pragma HLS INTERFACE mode=s_axilite port=KD
#pragma HLS INTERFACE mode=s_axilite port=KI
#pragma HLS INTERFACE mode=s_axilite port=KP
#pragma HLS INTERFACE mode=s_axilite port=set_point
#pragma HLS INTERFACE mode=s_axilite port=ts
#pragma HLS INTERFACE mode=s_axilite port=pmax
	data_type error, i, d, p;

	data_type temp;
	data_type op;


	error = set_point - sample;

	p = error * KP;
	i = i_prev + (error  * ts * KI);
	d = KD * ((error - error_prev) / ts);

	op = p+i+d;
	error_prev = error;
	if (op > pmax)  {
		i_prev = i_prev;
		op = pmax;
	}else{
		i_prev = i;
	}


	return op;

}
