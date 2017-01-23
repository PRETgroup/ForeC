// Calculates the single delayed auto-correlations (from I,Q) for the freqsyncdet using 2 short training symbols delay.

#include "freq_sync_correl_2STS.h"

#define oversampling_factor 2         // Data oversampling factor 

void freq_sync_correl_2STS(int init, int input_I, int input_Q, int *output_I, int *output_Q, int *correlation_1ST_i, int *correlation_1ST_q) {
	// Variable declaration
	static int data_store_real[32*oversampling_factor];
	static int data_store_imag[32*oversampling_factor];
	int i;
	int data_in_i1, data_in_q1;
	int data_in_idel1, data_in_qdel1;
	int correlation_1ST_i_1,correlation_1ST_q_1; 
	int correlation_1ST_i_2, correlation_1ST_q_2;

	// Reset or initialization action
	if (init == 0) {
		for (i = 0; i < (32*oversampling_factor); i++) /*#64#64*/ {
			data_store_real[i] = 0;
			data_store_imag[i] = 0;
		}
	} else {
		data_in_i1 = input_I >> 2; // Divide input data by 4.
		data_in_q1 = input_Q >> 2;

		data_in_idel1 = data_store_real[32*oversampling_factor-1];
		data_in_idel1 = data_in_idel1 >> 2;
		data_in_qdel1 = data_store_imag[32*oversampling_factor-1];
		data_in_qdel1 = data_in_qdel1 >> 2; 

		correlation_1ST_i_1 = data_in_i1 * data_in_idel1;
		correlation_1ST_i_2 = data_in_q1 * data_in_qdel1;
		*correlation_1ST_i = correlation_1ST_i_1 + correlation_1ST_i_2;

		correlation_1ST_q_1 = data_in_q1 * data_in_idel1;
		correlation_1ST_q_2 = data_in_i1 * data_in_qdel1;
		*correlation_1ST_q = correlation_1ST_q_1 - correlation_1ST_q_2;

		// output data = input data delayed by 20 samples to compensate delay of frequency_sync    
		*output_I = data_store_real[19];
		*output_Q = data_store_imag[19];

		// Shift register for sliding summation:
		for (i = (32*oversampling_factor-1); i > 0; i--) /*#63#63*/ {
			data_store_real[i] = data_store_real[i-1];
			data_store_imag[i] = data_store_imag[i-1];
		}
		data_store_real[0] = input_I;
		data_store_imag[0] = input_Q; 
	}
}
