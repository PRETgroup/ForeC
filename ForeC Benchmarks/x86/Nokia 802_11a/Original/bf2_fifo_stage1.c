#include "bf2_fifo_stage1.h"

#define fifo_len_div2 1

void bf2_fifo_stage1(
						// inputs
						const float *data_i_in, 
						const float *data_q_in, 
						
						// outputs
						float *data_i_out, 
						float *data_q_out) {
	static int nsample;
	static float fifo_i_array[3];
	static float fifo_q_array[3];

	*data_i_out = fifo_i_array[nsample];
	*data_q_out = fifo_q_array[nsample];
	
	fifo_i_array[nsample] = *data_i_in;
	fifo_q_array[nsample] = *data_q_in;
	
	if (nsample < fifo_len_div2 - 1) {
		nsample++;
	} else {
		nsample = 0;
    }
}
