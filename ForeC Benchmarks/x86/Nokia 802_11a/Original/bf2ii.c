#include "bf2ii.h"

void bf2ii(
			// inputs 
			const int s, 
			const int t, 
			const float *data_n_i_in, 
			const float *data_n_q_in, 
			const float *data_n_ndiv2_i_in, 
			const float *data_n_ndiv2_q_in,
			
			// outputs
			float *data_n_ndiv2_i_out, 
			float *data_n_ndiv2_q_out, 
			float *data_n_i_out, 
			float *data_n_q_out) {
	if (s == 0) { 
		// shifting
		*data_n_ndiv2_i_out = *data_n_ndiv2_i_in;
		*data_n_ndiv2_q_out = *data_n_ndiv2_q_in;
		*data_n_i_out = *data_n_i_in;
		*data_n_q_out = *data_n_q_in;
	} else {
		// caculating
		float tmp2_real, tmp2_imag;
		if (t == 0) {
			// swap
			tmp2_real = *data_n_ndiv2_q_in;
			tmp2_imag = -*data_n_ndiv2_i_in;
		} else { 
			// no swap
			tmp2_real = *data_n_ndiv2_i_in;
			tmp2_imag = *data_n_ndiv2_q_in;
		}
		
		*data_n_i_out = *data_n_i_in + tmp2_real;
		*data_n_q_out = *data_n_q_in + tmp2_imag;
		*data_n_ndiv2_i_out = *data_n_i_in - tmp2_real;
		*data_n_ndiv2_q_out = *data_n_q_in - tmp2_imag;
	}
}
