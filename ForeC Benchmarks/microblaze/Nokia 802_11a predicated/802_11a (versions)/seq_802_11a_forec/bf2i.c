#include "bf2i.h"

void bf2i(
			// inputs
			const int s, 
			const float *data_n_i_in, 
			const float *data_n_q_in, 
			const float *data_n_ndiv2_i_in, 
			const float *data_n_ndiv2_q_in, 
			
			// outputs
			float *data_n_ndiv2_i_out, 
			float *data_n_ndiv2_q_out, 
			float *data_n_i_out, 
			float *data_n_q_out) {
	if (s == 1) {
		*data_n_i_out = *data_n_i_in + *data_n_ndiv2_i_in;
		*data_n_q_out = *data_n_q_in + *data_n_ndiv2_q_in;
		*data_n_ndiv2_i_out = *data_n_i_in - *data_n_ndiv2_i_in;
		*data_n_ndiv2_q_out = *data_n_q_in - *data_n_ndiv2_q_in;
	} else {

		*data_n_ndiv2_i_out = *data_n_ndiv2_i_in;
		*data_n_ndiv2_q_out = *data_n_ndiv2_q_in;
		*data_n_i_out = *data_n_i_in;
		*data_n_q_out = *data_n_q_in;
	}
}
