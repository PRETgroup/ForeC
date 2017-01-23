#include "bf2_fifo_stage1.h"

void bf2_fifo_stage1(float *data_i_in, float *data_q_in, float *data_i_out, float *data_q_out) {
#ifndef DRODENAS
	static int nsample;
	int fifo_len_tmp;
	const int fifo_len_div2 = 1;
	float data_i_tmp = *data_i_in;
	float data_q_tmp = *data_q_in ;
	static float fifo_i_array[3];
	static float fifo_q_array[3];

	fifo_len_tmp = fifo_len_div2;
    
	*data_i_out=fifo_i_array[nsample];
	*data_q_out=fifo_q_array[nsample];
	
	fifo_i_array[nsample] = data_i_tmp;
	fifo_q_array[nsample] = data_q_tmp;
	
	if (nsample< fifo_len_tmp - 1) {
		nsample++;
	} else {
		nsample = 0;
    }
#else
	static float data_i_history= (float)0.0;
	static float data_q_history= (float)0.0;
	*data_i_out= data_i_history;
	*data_q_out= data_q_history;
	data_i_history= *data_i_in;
	data_q_history= *data_q_in;
#endif
}
