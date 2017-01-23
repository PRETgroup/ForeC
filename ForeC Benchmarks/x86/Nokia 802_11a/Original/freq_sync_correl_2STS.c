// Calculates the single delayed auto-correlations (from I,Q) for the freqsyncdet using 2 short training symbols delay.

#include "freq_sync_correl_2STS.h"

#define oversampling_factor 2         // Data oversampling factor 

void freq_sync_correl_2STS(
							// inputs
							const int init, 
							const int input_I, 
							const int input_Q, 

							//outputs
							int *output_I, 
							int *output_Q, 
							int *correlation_1ST_i, 
							int *correlation_1ST_q) {
	
	// Variable declaration
	static int data_store_real[32*oversampling_factor];
	static int data_store_imag[32*oversampling_factor];

	// Reset or initialization action
	if (init == 0) {
		int i;
		for (i = 0; i < (32*oversampling_factor); i++) /*#64#64*/ {
			data_store_real[i] = 0;
			data_store_imag[i] = 0;
		}
	} else {
		int data_in_i1 = input_I / 4; // Divide input data by 4.
		int data_in_q1 = input_Q / 4;

		int data_in_idel1 = data_store_real[32*oversampling_factor-1];
		data_in_idel1 = data_in_idel1 / 4;
		int data_in_qdel1 = data_store_imag[32*oversampling_factor-1];
		data_in_qdel1 = data_in_qdel1 / 4; 

		int correlation_1ST_i_1 = data_in_i1 * data_in_idel1;
		int correlation_1ST_i_2 = data_in_q1 * data_in_qdel1;
		*correlation_1ST_i = correlation_1ST_i_1 + correlation_1ST_i_2;

		int correlation_1ST_q_1 = data_in_q1 * data_in_idel1;
		int correlation_1ST_q_2 = data_in_i1 * data_in_qdel1;
		*correlation_1ST_q = correlation_1ST_q_1 - correlation_1ST_q_2;

		// output data = input data delayed by 20 samples to compensate delay of frequency_sync    
		*output_I = data_store_real[19];
		*output_Q = data_store_imag[19];

		// Shift register for sliding summation:
		int i;
		for (i = (32*oversampling_factor-1); i > 0; i--) /*#63#63*/ {
			data_store_real[i] = data_store_real[i-1];
			data_store_imag[i] = data_store_imag[i-1];
		}
		
		data_store_real[0] = input_I;
		data_store_imag[0] = input_Q; 
	}
}
