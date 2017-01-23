#include "twiddle_mult21.h"
#define twiddle21_size 12

const float twiddle21_re[twiddle21_size] = {
	 1.00000000e+00, 
	 7.07106769e-01, 
	-4.37113883e-08, 
	-7.07106769e-01,
	 1.00000000e+00, 
	 9.23879504e-01, 
	 7.07106769e-01, 
	 3.82683426e-01, 
	 1.00000000e+00, 
	 3.82683426e-01, 
	-7.07106769e-01, 
	-9.23879504e-01
};

const float twiddle21_im[twiddle21_size] = {
	 0.00000000e+00, 
	-7.07106769e-01, 
	-1.00000000e+00, 
	-7.07106769e-01,
	 0.00000000e+00, 
	-3.82683456e-01, 
	-7.07106769e-01, 
	-9.23879504e-01, 
	 0.00000000e+00, 
	-9.23879504e-01, 
	-7.07106769e-01, 
	 3.82683426e-01
};

void twiddle_mult21(int init, int twiddle_ptr, float *data_re_in, float *data_im_in, float *mult_re_out, float *mult_im_out) {
	float data_re_tmp, data_im_tmp;
	float calc1_re, calc1_im;
	float calc2_re, calc2_im;

	int twiddle_ptr_tmp;

	if (init == 0) {
		data_re_tmp = (float)0.0;
		data_im_tmp = (float)0.0;
		calc1_re = (float)0.0;
		calc2_re = (float)0.0;
		calc1_im = (float)0.0;
		calc2_im = (float)0.0;
		twiddle_ptr_tmp = 0;
	} else {
		data_re_tmp = *data_re_in;
		data_im_tmp = *data_im_in;
		if (twiddle_ptr < twiddle21_size) {
			twiddle_ptr_tmp = twiddle_ptr;
		} else {
			twiddle_ptr_tmp = 0;
		}
		calc1_re = data_re_tmp*twiddle21_re[twiddle_ptr_tmp];
		calc2_re = data_im_tmp*twiddle21_im[twiddle_ptr_tmp];

		calc1_im = data_re_tmp*twiddle21_im[twiddle_ptr_tmp];
		calc2_im = data_im_tmp*twiddle21_re[twiddle_ptr_tmp];

		*mult_re_out = calc1_re - calc2_re;
		*mult_im_out = calc1_im + calc2_im;
	}
}

