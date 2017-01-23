#include "mstream_demux.h"

#define buffer_len 64

void mstream_demux(
					// inputs
					const int init, 
					const float InData_re,
					const float InData_im,
					
					// outputs
					int *start, 
					float OutData_re[buffer_len], 
					float OutData_im[buffer_len]) {
	static int counter;
	static float array_re[buffer_len];
	static float array_im[buffer_len];
	static int inv_int;
	static int mux_cnt;
  
	if (init == 0) {
		int i;
		for (i = 0; i < buffer_len; i++) /*#64#64*/ {
			array_re[i] = (float)0.0;
			array_im[i] = (float)0.0;
		}
		
		counter = 0;
		inv_int = 0;
		mux_cnt = 0;
	} else {
		int index_int = inv_int + mux_cnt;
		array_re[index_int] = InData_re;
		array_im[index_int] = InData_im;


		int m_int = 64 / 2;	// 32
		if (inv_int < 63) {
			while (m_int >= 2 && inv_int >= m_int) /*#0#5*/ {
				inv_int -= m_int;
				m_int = m_int / 2;
			}
			inv_int += m_int;	      
		} else {
			inv_int = 0;
		}

		if (counter < 63) {
			counter++;
			*start = 0;
		} else {
			counter = 0;
			*start = 1;
			
			int i;
			for (i = 0; i < 64; i++) /*#64#64*/ {
				OutData_re[i] = array_re[i];
				OutData_im[i] = array_im[i];
			}
		}
	} 
}

