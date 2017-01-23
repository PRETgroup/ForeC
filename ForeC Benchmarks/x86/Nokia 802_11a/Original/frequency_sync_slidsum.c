// Sliding summation is done over remaining 8 short training symbols (1st two short training symbols are used for delay of auto-correlation

#include "frequency_sync_slidsum.h"

// correl_sum_len = 2*8*16 = 256 (defined in header-file)
#define correl_sum_len 256          // Length of sliding summation over the correlations

// - Constant definitions       
// Threshold value for burst detection criteria
#define burst_threshold          300
// Number of samples which will be used for
#define FreqEstStartSlSum        16
// the error estimation. 
#define FreqEstStopSlSum         240


static int freq2_i = 0;
static int freq2_q = 0;
static int freq1_i = 0;
static int freq1_q = 0;

static int correlation_1ST_store_real[correl_sum_len]; 
static int correlation_1ST_store_imag[correl_sum_len]; 
static int correlation_1ST_store_index;
static int burst_found_pulse_64d[64]; // For 32-cycle delay (2 times oversampled)
static int burst_found_pulse_64d_index;


void frequency_sync_slidsum(
							// inputs							
							const int mk_init, 
							const int rx_start, 
							const int correlation_1ST_real, 
							const int correlation_1ST_imag, 
							
							//outputs
							int *burst_found_out, 
							int *burst_found_pulse_out, 
							int *burst_found_pulse_out_for_FT, 
							int *freq_est_phase_out_real, 
							int *freq_est_phase_out_imag, 
							int *freq_est_norm_out, 
							int *freq_est_norm_max_out) {
	// Reset or initialization action
	if (mk_init == 0) {
		int i;
		for (i = 0; i < (correl_sum_len); i++) /*#256#256*/ {
			correlation_1ST_store_real[i] = 0;
			correlation_1ST_store_imag[i] = 0;
		}
		
		correlation_1ST_store_index= 0;
		*burst_found_out = 0;
		*freq_est_norm_out = 0;
		*freq_est_norm_max_out = 0;
		freq2_i = 0;
		freq2_q = 0;
		freq1_i = 0;
		freq1_q = 0;
		*freq_est_phase_out_real = 0;
		*freq_est_phase_out_imag = 0;
		*burst_found_pulse_out = 0;    
		
		for(i = 0; i < 64; i++) /*#64#64*/ {
			burst_found_pulse_64d[i] = 0;
		}
		burst_found_pulse_64d_index = 0;
	} else {
		if (rx_start == 1) {
			*burst_found_out = 0;
			*burst_found_pulse_out = 1;
			*freq_est_norm_out = 0;
			*freq_est_norm_max_out = 0;
		}  
		
		// Calculate auto-correlation sum for burst detection sliding summation of the single correlation values from last 256 samples
		// 8 STS-sub-sequences * (16 data bins per STS-sub-sequence) * 2 (oversampling-factor) = 256 = correl_sum_len 
		const int temp1_i = correlation_1ST_real - correlation_1ST_store_real[correlation_1ST_store_index];
		freq1_i += temp1_i;
		const int temp1_q = correlation_1ST_imag - correlation_1ST_store_imag[correlation_1ST_store_index];
		freq1_q += temp1_q; 
   
		// Calculate auto-correlation sum for freq. offset estimation sliding summation of the single correlation values from last 256 samples
		const int temp2_i = correlation_1ST_store_real[(correlation_1ST_store_index - FreqEstStartSlSum - 1) & 255] - correlation_1ST_store_real[(correlation_1ST_store_index - FreqEstStopSlSum - 1) & 255];
		freq2_i += temp2_i;
		const int temp2_q = correlation_1ST_store_imag[(correlation_1ST_store_index - FreqEstStartSlSum - 1) & 255] - correlation_1ST_store_imag[(correlation_1ST_store_index - FreqEstStopSlSum - 1) & 255];
		freq2_q += temp2_q;  

		// Shift register for sliding summation:
		correlation_1ST_store_real[correlation_1ST_store_index] = correlation_1ST_real;
		correlation_1ST_store_imag[correlation_1ST_store_index] = correlation_1ST_imag;
		correlation_1ST_store_index= ((correlation_1ST_store_index + 1) & 255);
   
		// Norm of auto-correlation of burst detection
		const int freq1_i_tmp = freq1_i / 8192;
		const int freq1_q_tmp = freq1_q / 8192;
		*freq_est_norm_out = (freq1_i_tmp*freq1_i_tmp) + (freq1_q_tmp*freq1_q_tmp);

		// Find start point, when looking for max. in auto-correlation (magn)
		if (*freq_est_norm_out > burst_threshold && *burst_found_out == 0) {
			*burst_found_out = 1;
			*freq_est_norm_max_out = *freq_est_norm_out;
		}

		if (*burst_found_out == 1) {
			// Start now looking for new max in freq_est_norm
			if (*freq_est_norm_out > *freq_est_norm_max_out) {
				*freq_est_norm_max_out = *freq_est_norm_out;
				*freq_est_phase_out_real = freq2_i / 32;
				*freq_est_phase_out_imag = freq2_q / 32;
				*burst_found_pulse_out = 0;
			} else {
				*burst_found_pulse_out = 1;
			}    
		} else {
			*burst_found_pulse_out = 0;
		}

		// shift register for delay chain
		burst_found_pulse_64d[burst_found_pulse_64d_index] = *burst_found_pulse_out;
		burst_found_pulse_64d_index= (burst_found_pulse_64d_index + 1) & 63;
	}
	
	*burst_found_pulse_out_for_FT = burst_found_pulse_64d[burst_found_pulse_64d_index];
}


