// FFT64
// The outputs of this FFT are bit reversed!!. The reordering function is not implemented here.

#include "fft64.h"

void fft64(int init, float real_in, float imag_in, float *data_i_out, float *data_q_out) {
	float data_i_in;
	float data_q_in;

	int j;

	//  bf2 & FIFO stage5
	static float bf2_fifo_stage5_i= (float)0.0;
	static float bf2_fifo_stage5_q= (float)0.0;
	static float fifo_stage5_i_reg= (float)0.0;
	static float fifo_stage5_q_reg= (float)0.0;
	float bf2_ndiv2_stage5_i;
	float bf2_ndiv2_stage5_q;
	static float bf2_n_stage5_i= (float)0.0;
	static float bf2_n_stage5_q= (float)0.0;
  
	//  bf2 & FIFO stage4
	static float bf2_fifo_stage4_i= (float)0.0;
	static float bf2_fifo_stage4_q= (float)0.0;
	static float fifo_stage4_i_reg= (float)0.0;
	static float fifo_stage4_q_reg= (float)0.0;
	float bf2_ndiv2_stage4_i;
	float bf2_ndiv2_stage4_q;
	static float bf2_n_stage4_i= (float)0.0;
	static float bf2_n_stage4_q= (float)0.0;

	//  bf2 & FIFO stage3
	static float bf2_fifo_stage3_i= (float)0.0;
	static float bf2_fifo_stage3_q= (float)0.0;
	static float fifo_stage3_i_reg= (float)0.0;
	static float fifo_stage3_q_reg= (float)0.0;
	float bf2_ndiv2_stage3_i;
	float bf2_ndiv2_stage3_q;
	static float bf2_n_stage3_i= (float)0.0;
	static float bf2_n_stage3_q= (float)0.0;

	//  bf2 & FIFO stage2
	static float bf2_fifo_stage2_i= (float)0.0;
	static float bf2_fifo_stage2_q= (float)0.0;
	static float fifo_stage2_i_reg= (float)0.0;
	static float fifo_stage2_q_reg= (float)0.0;
	float bf2_ndiv2_stage2_i;
	float bf2_ndiv2_stage2_q;
	static float bf2_n_stage2_i= (float)0.0;
	static float bf2_n_stage2_q= (float)0.0;

	//  bf2 & FIFO stage1
	static float bf2_fifo_stage1_i= (float)0.0;
	static float bf2_fifo_stage1_q= (float)0.0;
	static float fifo_stage1_i_reg= (float)0.0;
	static float fifo_stage1_q_reg= (float)0.0;
	float bf2_ndiv2_stage1_i;
	float bf2_ndiv2_stage1_q;
	static float bf2_n_stage1_i= (float)0.0;
	static float bf2_n_stage1_q= (float)0.0;

	//  bf2 & FIFO stage0
	static float bf2_fifo_stage0_i= (float)0.0;
	static float bf2_fifo_stage0_q= (float)0.0;
	static float fifo_stage0_i_reg= (float)0.0;
	static float fifo_stage0_q_reg= (float)0.0;
	float bf2_ndiv2_stage0_i;
	float bf2_ndiv2_stage0_q;
	static float bf2_n_stage0_i= (float)0.0;
	static float bf2_n_stage0_q= (float)0.0;

	//  multiplier stage
	int twiddle43_ptr;
	int twiddle21_ptr;
	float mult_stage43_i, mult_stage43_q;
	float mult_stage21_i, mult_stage21_q;

	// static variables
	static int cnt_index= 0;
	static int multiple_streams_index= 0;

	int s[6];
  
	if (init == 0) {
		for(j=0;j<6;j++) {
			s[j] = 0;
		}
		twiddle43_ptr = 0;
		twiddle21_ptr = 0;
		data_i_in = 0;
		data_q_in = 0;
		*data_i_out = 0;
		*data_q_out = 0;
		cnt_index = 0;
		multiple_streams_index= 0;
	} else {
		*data_i_out = bf2_n_stage0_i;
		*data_q_out = bf2_n_stage0_q;    
		data_i_in = real_in;
		data_q_in = imag_in;
		twiddle43_ptr  = multiple_streams_index%64;
		twiddle21_ptr  = multiple_streams_index%16;

		if (multiple_streams_index < 63) {
			multiple_streams_index++;
		} else {
			multiple_streams_index = 0;
		}
      
		if (cnt_index%(2) > 0) {
			s[0] = 1;
		} else {
			s[0] = 0;
		}
		if (cnt_index%(4) > 1) {
			s[1] = 1;
		} else {
			s[1] = 0;
		}
		if (cnt_index%(8) > 3) {
			s[2] = 1;
		} else {
			s[2] = 0;
		}
		if (cnt_index%(16) > 7) {
			s[3] = 1;
		} else {
			s[3] = 0;
		}
		if (cnt_index%(32) > 15) {
			s[4] = 1;
		} else {
			s[4] = 0;
		}
		if (cnt_index%(64) > 31) {
			s[5] = 1;
		} else {
			s[5] = 0;
		}

		// stage5, bf2i, fifo=32
		bf2i(s[5], &fifo_stage5_i_reg, &fifo_stage5_q_reg, &data_i_in, &data_q_in, &bf2_ndiv2_stage5_i, &bf2_ndiv2_stage5_q, &bf2_n_stage5_i, &bf2_n_stage5_q);
		bf2_fifo_stage5(&bf2_ndiv2_stage5_i, &bf2_ndiv2_stage5_q, &bf2_fifo_stage5_i, &bf2_fifo_stage5_q);
      
		// stage4, bf2ii
		bf2ii(s[4], s[5], &fifo_stage4_i_reg, &fifo_stage4_q_reg, &bf2_n_stage5_i, &bf2_n_stage5_q, &bf2_ndiv2_stage4_i, &bf2_ndiv2_stage4_q, &bf2_n_stage4_i, &bf2_n_stage4_q);
		bf2_fifo_stage4(&bf2_ndiv2_stage4_i, &bf2_ndiv2_stage4_q, &bf2_fifo_stage4_i,  &bf2_fifo_stage4_q);
      
		// multiplier stage 4-3
		twiddle_mult43(init, twiddle43_ptr, &bf2_n_stage4_i, &bf2_n_stage4_q, &mult_stage43_i, &mult_stage43_q);

		// stage3, bf2i
		bf2i(s[3], &fifo_stage3_i_reg, &fifo_stage3_q_reg, &mult_stage43_i, &mult_stage43_q, &bf2_ndiv2_stage3_i, &bf2_ndiv2_stage3_q, &bf2_n_stage3_i, &bf2_n_stage3_q);
		bf2_fifo_stage3(&bf2_ndiv2_stage3_i, &bf2_ndiv2_stage3_q, &bf2_fifo_stage3_i, &bf2_fifo_stage3_q);

		// stage2, bf2ii
		bf2ii(s[2], s[3], &fifo_stage2_i_reg, &fifo_stage2_q_reg, &bf2_n_stage3_i, &bf2_n_stage3_q, &bf2_ndiv2_stage2_i, &bf2_ndiv2_stage2_q, &bf2_n_stage2_i, &bf2_n_stage2_q);
		bf2_fifo_stage2(&bf2_ndiv2_stage2_i, &bf2_ndiv2_stage2_q, &bf2_fifo_stage2_i,  &bf2_fifo_stage2_q);

		// multiplier stage 2-1
		twiddle_mult21(init, twiddle21_ptr, &bf2_n_stage2_i, &bf2_n_stage2_q, &mult_stage21_i, &mult_stage21_q);

		// stage1, bf2i
		bf2i(s[1], &fifo_stage1_i_reg, &fifo_stage1_q_reg, &mult_stage21_i, &mult_stage21_q, &bf2_ndiv2_stage1_i, &bf2_ndiv2_stage1_q, &bf2_n_stage1_i, &bf2_n_stage1_q);
		bf2_fifo_stage1(&bf2_ndiv2_stage1_i, &bf2_ndiv2_stage1_q, &bf2_fifo_stage1_i, &bf2_fifo_stage1_q);

		// stage0, bf2ii
		bf2ii(s[0], s[1], &fifo_stage0_i_reg, &fifo_stage0_q_reg, &bf2_n_stage1_i, &bf2_n_stage1_q, &bf2_ndiv2_stage0_i, &bf2_ndiv2_stage0_q, &bf2_n_stage0_i, &bf2_n_stage0_q);
		bf2_fifo_stage0(&bf2_ndiv2_stage0_i, &bf2_ndiv2_stage0_q,  &bf2_fifo_stage0_i,  &bf2_fifo_stage0_q);
      
		fifo_stage5_i_reg = bf2_fifo_stage5_i;
		fifo_stage5_q_reg = bf2_fifo_stage5_q;

		fifo_stage4_i_reg = bf2_fifo_stage4_i;
		fifo_stage4_q_reg = bf2_fifo_stage4_q;

		fifo_stage3_i_reg = bf2_fifo_stage3_i;
		fifo_stage3_q_reg = bf2_fifo_stage3_q;

		fifo_stage2_i_reg = bf2_fifo_stage2_i;
		fifo_stage2_q_reg = bf2_fifo_stage2_q;

		fifo_stage1_i_reg = bf2_fifo_stage1_i;
		fifo_stage1_q_reg = bf2_fifo_stage1_q;

		fifo_stage0_i_reg = bf2_fifo_stage0_i;
		fifo_stage0_q_reg = bf2_fifo_stage0_q;
      
		if(cnt_index < 63) {
			cnt_index++;
		} else {
			cnt_index = 0;
		}
    }
}
