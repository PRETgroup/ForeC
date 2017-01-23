/*
This model performs the 802.11a channel CORRECTION in the frequency domain.

Conjugate complex multiplication of CHE-output with payload-data.

*/

#include "CHE.h"

void channel_correction(
						// inputs
						const int input_I[52], 
						const int input_Q[52], 
						const int output_CHE_I[52], 
						const int output_CHE_Q[52], 
						
						// outputs
						int output_CHC_I[52], 
						int output_CHC_Q[52]) {
	int i;
	for (i = 0; i < 52; i++) /*#52#52*/ {  
		long int mult_CHC_I = input_I[i] * output_CHE_I[i] + input_Q[i] * output_CHE_Q[i];
		long int mult_CHC_Q = -input_I[i] * output_CHE_Q[i] + input_Q[i] * output_CHE_I[i];
		output_CHC_I[i] = mult_CHC_I / 1024;
		output_CHC_Q[i] = mult_CHC_Q / 1024;
	}
} 
