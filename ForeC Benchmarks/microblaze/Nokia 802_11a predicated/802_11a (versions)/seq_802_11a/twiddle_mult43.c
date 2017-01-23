#include "twiddle_mult43.h"

#define twiddle43_size 48

const float twiddle43_re[twiddle43_size] = {
	 1.00000000e+00,
	 9.80785251e-01, 
	 9.23879504e-01, 
	 8.31469595e-01, 
	 7.07106769e-01, 
	 5.55570185e-01, 
	 3.82683426e-01, 
	 1.95090234e-01,
	-4.37113883e-08, 
	-1.95090324e-01, 
	-3.82683516e-01, 
	-5.55570364e-01, 
	-7.07106769e-01, 
	-8.31469655e-01, 
	-9.23879623e-01, 
	-9.80785310e-01,
	 1.00000000e+00, 
	 9.95184720e-01, 
	 9.80785251e-01, 
	 9.56940353e-01, 
	 9.23879504e-01, 
	 8.81921232e-01, 
	 8.31469595e-01, 
	 7.73010433e-01,
	 7.07106769e-01, 
	 6.34393275e-01, 
	 5.55570185e-01, 
	 4.71396655e-01, 
	 3.82683426e-01, 
	 2.90284634e-01, 
	 1.95090234e-01,
	 9.80171338e-02,
	 1.00000000e+00, 
	 9.56940353e-01, 
	 8.31469595e-01, 
	 6.34393275e-01, 
	 3.82683426e-01, 
	 9.80171338e-02, 
	-1.95090324e-01, 
	-4.71396834e-01,
	-7.07106769e-01, 
	-8.81921351e-01, 
	-9.80785310e-01, 
	-9.95184720e-01, 
	-9.23879504e-01, 
	-7.73010373e-01, 
	-5.55570006e-01, 
	-2.90284544e-01
};

const float twiddle43_im[twiddle43_size] = {
	 0.00000000e+00, 
	-1.95090324e-01, 
	-3.82683456e-01, 
	-5.55570245e-01, 
	-7.07106769e-01, 
	-8.31469655e-01, 
	-9.23879504e-01, 
	-9.80785310e-01,
	-1.00000000e+00, 
	-9.80785251e-01, 
	-9.23879504e-01, 
	-8.31469536e-01, 
	-7.07106769e-01, 
	-5.55570185e-01, 
	-3.82683277e-01, 
	-1.95090309e-01,
	 0.00000000e+00, 
	-9.80171412e-02, 
	-1.95090324e-01, 
	-2.90284663e-01, 
	-3.82683456e-01, 
	-4.71396744e-01, 
	-5.55570245e-01, 
	-6.34393334e-01,
	-7.07106769e-01, 
	-7.73010433e-01, 
	-8.31469655e-01, 
	-8.81921291e-01, 
	-9.23879504e-01, 
	-9.56940353e-01, 
	-9.80785310e-01, 
	-9.95184720e-01,
	 0.00000000e+00, 
	-2.90284663e-01, 
	-5.55570245e-01, 
	-7.73010433e-01, 
	-9.23879504e-01, 
	-9.95184720e-01, 
	-9.80785251e-01, 
	-8.81921232e-01,
	-7.07106769e-01, 
	-4.71396625e-01, 
	-1.95090309e-01, 
	 9.80172679e-02, 
	 3.82683426e-01, 
	 6.34393394e-01, 
	 8.31469774e-01, 
	 9.56940353e-01
};

void twiddle_mult43(int init, int twiddle_ptr, float *data_re_in, float *data_im_in, float *mult_re_out, float *mult_im_out) {
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
		if (twiddle_ptr < twiddle43_size) {
			twiddle_ptr_tmp = twiddle_ptr;
		} else {
			twiddle_ptr_tmp = 0;
		}
		
		calc1_re = data_re_tmp*twiddle43_re[twiddle_ptr_tmp];
		calc2_re = data_im_tmp*twiddle43_im[twiddle_ptr_tmp];

		calc1_im = data_re_tmp*twiddle43_im[twiddle_ptr_tmp];
		calc2_im = data_im_tmp*twiddle43_re[twiddle_ptr_tmp];

		*mult_re_out = calc1_re - calc2_re;
		*mult_im_out = calc1_im + calc2_im;
	}
}

