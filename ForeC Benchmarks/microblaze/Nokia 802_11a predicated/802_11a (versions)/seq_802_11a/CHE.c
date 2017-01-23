/*
This model performs the 802.11a channel estimation in the frequency domain.
Incoming LTS parts are first averaged and then multiplied by the frequency domain LTS values.

It is assumed, that only when burst_start_found is '1' and a valid LTS is found,
data is applied to the input of the channel estimation module for further signal processing.
*/

#include "CHE.h"

void channel_estimation(int input_I[104], int input_Q[104], int output_I[52], int output_Q[52]) {
	// Known transmitted LTS sequence
	int long_pattern[52] = {1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1, 1, 1, 1, 1, 1,-1,-1, 1, 1,-1, 1,-1, 1,-1,-1,-1,-1,-1, 1, 1,-1,-1, 1,-1, 1,-1, 1, 1, 1, 1}; 
	int i; 
	int mean_received_training_symbols_real[52];
	int mean_received_training_symbols_imag[52];

	/* Initial 104 samples corresponds to lts part (2 Long Training Symbols)
	   Calculate average of the 2 LTS */
	for (i = 0; i < 52; i++) /*#52#52*/ {
		mean_received_training_symbols_real[i] = (input_I[i] + input_I[i+52])/2;
		mean_received_training_symbols_imag[i] = (input_Q[i] + input_Q[i+52])/2; 
	}
  
	// Least square estimation = Received sequence * Known_sequence(BPSK)
	for(i = 0; i < 52; i++) /*#52#52*/ {
		output_I[i] = mean_received_training_symbols_real[i] * long_pattern[i];
		output_Q[i] = mean_received_training_symbols_imag[i] * long_pattern[i];
	}
}
