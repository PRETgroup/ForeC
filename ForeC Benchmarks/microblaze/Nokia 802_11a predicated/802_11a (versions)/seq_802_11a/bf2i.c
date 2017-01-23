#include "bf2i.h"

void bf2i(int s, 
	float *data_n_i_in, float *data_n_q_in, 
	float *data_n_ndiv2_i_in, float *data_n_ndiv2_q_in, 
	float *data_n_ndiv2_i_out, float *data_n_ndiv2_q_out, 
	float *data_n_i_out, float *data_n_q_out) {
	float tmp1_real;
	float tmp1_imag;
	float tmp2_real;
	float tmp2_imag;

	if (s == 1) {
		tmp1_real=*data_n_i_in;
		tmp1_imag=*data_n_q_in;
		tmp2_real=*data_n_ndiv2_i_in;
		tmp2_imag=*data_n_ndiv2_q_in;
		*data_n_i_out=tmp1_real + tmp2_real;
		*data_n_q_out=tmp1_imag + tmp2_imag;
		*data_n_ndiv2_i_out=tmp1_real - tmp2_real;
		*data_n_ndiv2_q_out=tmp1_imag - tmp2_imag;
	} else {
		tmp1_real=*data_n_i_in;
		tmp1_imag=*data_n_q_in;
		tmp2_real=*data_n_ndiv2_i_in;
		tmp2_imag=*data_n_ndiv2_q_in;
		*data_n_ndiv2_i_out=tmp2_real;
		*data_n_ndiv2_q_out=tmp2_imag;
		*data_n_i_out=tmp1_real;
		*data_n_q_out=tmp1_imag;
	}
}
