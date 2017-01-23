/*
This model performs the 802.11a channel estimation in the frequency domain.
Incoming LTS parts are first averaged and then multiplied by the frequency domain LTS values.

It is assumed, that only when burst_start_found is '1' and a valid LTS is found,
data is applied to the input of the channel estimation module for further signal processing.
*/

#include "CHE.h"

void channel_estimation(
						// inputs 
						const int input_I[104], 
						const int input_Q[104], 
						
						// outputs
						int output_I[52], 
						int output_Q[52]) {
	// Known transmitted LTS sequence
	const int long_pattern[52] = {1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1,-1,-1, 1, 1,-1,-1, 1,-1, 1,-1, 1, 1, 1, 1}; 

	/* Initial 104 samples corresponds to lts part (2 Long Training Symbols)
	   Calculate average of the 2 LTS */
	// Least square estimation = Received sequence * Known_sequence(BPSK)
	int i;
	for (i = 0; i < 52; i++) /*#52#52*/ {
		output_I[i] = (input_I[i] + input_I[i+52])/2 * long_pattern[i];
		output_Q[i] = (input_Q[i] + input_Q[i+52])/2 * long_pattern[i];
	}
}
