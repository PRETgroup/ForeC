#include "bf2_fifo_stage0.h"

void bf2_fifo_stage0(
						// inputs
						const float *data_i_in, 
						const float *data_q_in, 
						
						// outputs 
						float *data_i_out, 
						float *data_q_out) {
	*data_i_out = *data_i_in;
	*data_q_out = *data_q_in;
}

