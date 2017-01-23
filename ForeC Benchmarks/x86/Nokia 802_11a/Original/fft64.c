// FFT64
// The outputs of this FFT are bit reversed!!. The reordering function is not implemented here.

#include "fft64.h"

void fft64(
			// inputs
			const int init, 
			const float real_in, 
			const float imag_in, 
			
			// outputs
			float *data_i_out, 
			float *data_q_out) {
	//  bf2 & FIFO stage5
	static float bf2_fifo_stage5_i= (float)0.0;
	static float bf2_fifo_stage5_q= (float)0.0;
	static float fifo_stage5_i_reg= (float)0.0;
	static float fifo_stage5_q_reg= (float)0.0;
	static float bf2_n_stage5_i= (float)0.0;
	static float bf2_n_stage5_q= (float)0.0;
  
	//  bf2 & FIFO stage4
	static float bf2_fifo_stage4_i= (float)0.0;
	static float bf2_fifo_stage4_q= (float)0.0;
	static float fifo_stage4_i_reg= (float)0.0;
	static float fifo_stage4_q_reg= (float)0.0;
	static float bf2_n_stage4_i= (float)0.0;
	static float bf2_n_stage4_q= (float)0.0;

	//  bf2 & FIFO stage3
	static float bf2_fifo_stage3_i= (float)0.0;
	static float bf2_fifo_stage3_q= (float)0.0;
	static float fifo_stage3_i_reg= (float)0.0;
	static float fifo_stage3_q_reg= (float)0.0;
	static float bf2_n_stage3_i= (float)0.0;
	static float bf2_n_stage3_q= (float)0.0;

	//  bf2 & FIFO stage2
	static float bf2_fifo_stage2_i= (float)0.0;
	static float bf2_fifo_stage2_q= (float)0.0;
	static float fifo_stage2_i_reg= (float)0.0;
	static float fifo_stage2_q_reg= (float)0.0;
	static float bf2_n_stage2_i= (float)0.0;
	static float bf2_n_stage2_q= (float)0.0;

	//  bf2 & FIFO stage1
	static float bf2_fifo_stage1_i= (float)0.0;
	static float bf2_fifo_stage1_q= (float)0.0;
	static float fifo_stage1_i_reg= (float)0.0;
	static float fifo_stage1_q_reg= (float)0.0;
	static float bf2_n_stage1_i= (float)0.0;
	static float bf2_n_stage1_q= (float)0.0;

	//  bf2 & FIFO stage0
	static float bf2_fifo_stage0_i= (float)0.0;
	static float bf2_fifo_stage0_q= (float)0.0;
	static float fifo_stage0_i_reg= (float)0.0;
	static float fifo_stage0_q_reg= (float)0.0;
	static float bf2_n_stage0_i= (float)0.0;
	static float bf2_n_stage0_q= (float)0.0;

	// static variables
	static int cnt_index = 0;
	static int multiple_streams_index = 0;

	if (init == 0) {
		*data_i_out = 0;
		*data_q_out = 0;
		cnt_index = 0;
		multiple_streams_index = 0;
	} else {
		*data_i_out = bf2_n_stage0_i;
		*data_q_out = bf2_n_stage0_q;
      
		int s[6];
		s[0] = (cnt_index % 2 > 0);
		s[1] = (cnt_index % 4 > 1);
		s[2] = (cnt_index % 8 > 3);
		s[3] = (cnt_index % 16 > 7);
		s[4] = (cnt_index % 32 > 15);
		s[5] = (cnt_index % 64 > 31);

		// stage5, bf2i, fifo=32
		float bf2_ndiv2_stage5_i;
		float bf2_ndiv2_stage5_q;
		bf2i(
			// inputs
			s[5], 
			&fifo_stage5_i_reg, 
			&fifo_stage5_q_reg, 
			&real_in, 
			&imag_in, 
			// outputs 
			&bf2_ndiv2_stage5_i, 
			&bf2_ndiv2_stage5_q, 
			&bf2_n_stage5_i, 
			&bf2_n_stage5_q
		);
		bf2_fifo_stage5(
			// inputs
			&bf2_ndiv2_stage5_i, 
			&bf2_ndiv2_stage5_q, 
			// outputs
			&bf2_fifo_stage5_i, 
			&bf2_fifo_stage5_q
		);
		fifo_stage5_i_reg = bf2_fifo_stage5_i;
		fifo_stage5_q_reg = bf2_fifo_stage5_q;
      
		// stage4, bf2ii
		float bf2_ndiv2_stage4_i;
		float bf2_ndiv2_stage4_q;
		bf2ii(
			// inputs 
			s[4], 
			s[5], 
			&fifo_stage4_i_reg, 
			&fifo_stage4_q_reg, 
			&bf2_n_stage5_i, 
			&bf2_n_stage5_q, 
			// outputs
			&bf2_ndiv2_stage4_i, 
			&bf2_ndiv2_stage4_q, 
			&bf2_n_stage4_i, 
			&bf2_n_stage4_q
		);
		bf2_fifo_stage4(
			// inputs
			&bf2_ndiv2_stage4_i, 
			&bf2_ndiv2_stage4_q, 
			// outputs
			&bf2_fifo_stage4_i,  
			&bf2_fifo_stage4_q
		);
		fifo_stage4_i_reg = bf2_fifo_stage4_i;
		fifo_stage4_q_reg = bf2_fifo_stage4_q;
      
		// multiplier stage 4-3
		float mult_stage43_i, mult_stage43_q;
		int twiddle43_ptr = multiple_streams_index % 64;
		twiddle_mult43(
			// inputs 
			init, 
			twiddle43_ptr, 
			&bf2_n_stage4_i, 
			&bf2_n_stage4_q, 
			// outputs
			&mult_stage43_i, 
			&mult_stage43_q
		);

		// stage3, bf2i
		float bf2_ndiv2_stage3_i;
		float bf2_ndiv2_stage3_q;
		bf2i(
			// inputs
			s[3], 
			&fifo_stage3_i_reg, 
			&fifo_stage3_q_reg, 
			&mult_stage43_i, 
			&mult_stage43_q, 
			// outputs
			&bf2_ndiv2_stage3_i, 
			&bf2_ndiv2_stage3_q, 
			&bf2_n_stage3_i, 
			&bf2_n_stage3_q
		);
		bf2_fifo_stage3(
			// inputs
			&bf2_ndiv2_stage3_i, 
			&bf2_ndiv2_stage3_q,
			// outputs 
			&bf2_fifo_stage3_i, 
			&bf2_fifo_stage3_q
		);
		fifo_stage3_i_reg = bf2_fifo_stage3_i;
		fifo_stage3_q_reg = bf2_fifo_stage3_q;

		// stage2, bf2ii
		float bf2_ndiv2_stage2_i;
		float bf2_ndiv2_stage2_q;
		bf2ii(
			// inputs
			s[2], 
			s[3], 
			&fifo_stage2_i_reg, 
			&fifo_stage2_q_reg, 
			&bf2_n_stage3_i, 
			&bf2_n_stage3_q, 
			// outputs
			&bf2_ndiv2_stage2_i, 
			&bf2_ndiv2_stage2_q, 
			&bf2_n_stage2_i, 
			&bf2_n_stage2_q
		);
		bf2_fifo_stage2(
			// inputs
			&bf2_ndiv2_stage2_i, 
			&bf2_ndiv2_stage2_q, 
			// outputs
			&bf2_fifo_stage2_i,  
			&bf2_fifo_stage2_q
		);
		fifo_stage2_i_reg = bf2_fifo_stage2_i;
		fifo_stage2_q_reg = bf2_fifo_stage2_q;

		// multiplier stage 2-1
		float mult_stage21_i, mult_stage21_q;
		int twiddle21_ptr = multiple_streams_index % 16;
		twiddle_mult21(
			// inputs
			init, 
			twiddle21_ptr, 
			&bf2_n_stage2_i, 
			&bf2_n_stage2_q, 
			// outputs
			&mult_stage21_i, 
			&mult_stage21_q
		);

		// stage1, bf2i
		float bf2_ndiv2_stage1_i;
		float bf2_ndiv2_stage1_q;
		bf2i(
			// inputs
			s[1], 
			&fifo_stage1_i_reg, 
			&fifo_stage1_q_reg, 
			&mult_stage21_i, 
			&mult_stage21_q, 
			// outputs
			&bf2_ndiv2_stage1_i, 
			&bf2_ndiv2_stage1_q, 
			&bf2_n_stage1_i, 
			&bf2_n_stage1_q
		);
		bf2_fifo_stage1(
			// inputs
			&bf2_ndiv2_stage1_i, 
			&bf2_ndiv2_stage1_q, 
			// outputs
			&bf2_fifo_stage1_i, 
			&bf2_fifo_stage1_q
		);
		fifo_stage1_i_reg = bf2_fifo_stage1_i;
		fifo_stage1_q_reg = bf2_fifo_stage1_q;

		// stage0, bf2ii
		float bf2_ndiv2_stage0_i;
		float bf2_ndiv2_stage0_q;
		bf2ii(
			// inputs
			s[0], 
			s[1], 
			&fifo_stage0_i_reg, 
			&fifo_stage0_q_reg, 
			&bf2_n_stage1_i, 
			&bf2_n_stage1_q, 
			// outputs
			&bf2_ndiv2_stage0_i, 
			&bf2_ndiv2_stage0_q, 
			&bf2_n_stage0_i, 
			&bf2_n_stage0_q
		);
		bf2_fifo_stage0(
			// inputs
			&bf2_ndiv2_stage0_i, 
			&bf2_ndiv2_stage0_q,  
			// outputs
			&bf2_fifo_stage0_i,  
			&bf2_fifo_stage0_q
		);
		fifo_stage0_i_reg = bf2_fifo_stage0_i;
		fifo_stage0_q_reg = bf2_fifo_stage0_q;
      
		if (multiple_streams_index < 63) {
			multiple_streams_index++;
		} else {
			multiple_streams_index = 0;
		}

		if(cnt_index < 63) {
			cnt_index++;
		} else {
			cnt_index = 0;
		}
    }
}
