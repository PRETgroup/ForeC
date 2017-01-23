#include "bf2_fifo_stage5.h"


void bf2_fifo_stage5(float *data_i_in, float *data_q_in, float *data_i_out, float *data_q_out) {
	static int nsample= 0;
	int nsample_r;
  
	int fifo_len_tmp;
	const int fifo_len_div2 = 31;
	float data_i_tmp = *data_i_in;
	float data_q_tmp = *data_q_in ;
	static float fifo_i_array[63]= { (float)0.0 };
	static float fifo_q_array[63]= { (float)0.0 };

	static float fifo_i_tmp = (float)0.0;
	static float fifo_q_tmp = (float)0.0;
  
	fifo_len_tmp = fifo_len_div2;

	*data_i_out = fifo_i_tmp;
	*data_q_out = fifo_q_tmp;
  
	if (nsample < 1) {
		nsample_r = 1;
	} else {
		if (nsample > fifo_len_tmp - 2) {
			nsample_r = 0;
		} else {
			nsample_r = nsample + 1;
		}
    }
    
	fifo_i_tmp = fifo_i_array[nsample_r];
	fifo_q_tmp = fifo_q_array[nsample_r];
  
	fifo_i_array[nsample] = data_i_tmp;
	fifo_q_array[nsample] = data_q_tmp;
  
	if (nsample<fifo_len_tmp-1) {
		nsample++;
	} else {
		nsample = 0;
	}
}
