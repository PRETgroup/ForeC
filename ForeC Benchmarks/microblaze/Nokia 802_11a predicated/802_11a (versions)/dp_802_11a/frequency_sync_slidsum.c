// Sliding summation is done over remaining 8 short training symbols (1st two short training symbols are used for delay of auto-correlation

#include "frequency_sync_slidsum.h"


// - Constant definitions
// Threshold value for burst detection criteria
#define burst_threshold          300
// Number of samples which will be used for
#define FreqEstStartSlSum         16
// the error estimation.
#define FreqEstStopSlSum         240


static int freq2_i = 0;
static int freq2_q = 0;
static int freq1_i = 0;
static int freq1_q = 0;
// correl_sum_len = 2*8*16 = 256 (defined in header-file)
static int correlation_1ST_store_real[correl_sum_len];
static int correlation_1ST_store_imag[correl_sum_len];
static int correlation_1ST_store_index;

static int freq_est_phase_out_real_prev = 0;
static int freq_est_phase_out_imag_prev = 0;


void frequency_sync_slidsum (int mk_init, int rx_start,
			     int correlation_1ST_real, int correlation_1ST_imag,
			     int *burst_found_out,
			     int *burst_found_pulse,
			     int *freq_est_phase_out_real, int *freq_est_phase_out_imag,
			     int *freq_est_norm_out, int *freq_est_norm_max_out)
{

  // Variable declaration
  int rx_start_tmp = rx_start;
  int i;
  int freq2_i_tmp, freq2_q_tmp, freq1_i_tmp, freq1_q_tmp, cor_1_i, cor_1_q, temp1_i, temp1_q, temp2_i, temp2_q;

  // Reset or initialization action
  if (mk_init == 0)
    {
      for(i=0;i<(correl_sum_len);i++){
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
      freq2_i_tmp = 0;
      freq2_q_tmp = 0;
      freq1_i_tmp = 0;
      freq1_q_tmp = 0;
      temp1_i = 0;
      temp1_q = 0;
      temp2_i = 0;
      temp2_q = 0;
      i = 0;
      cor_1_i = 0;
      cor_1_q = 0;
      *burst_found_pulse = 0;
    }
  else
    {

      if (rx_start_tmp == 1) {
	*burst_found_out = 0;
	*burst_found_pulse = 1;
	*freq_est_norm_out = 0;
	*freq_est_norm_max_out = 0;
      }  
  
      cor_1_i = correlation_1ST_real;
      cor_1_q = correlation_1ST_imag;

      // Calculate auto-correlation sum for burst detection sliding summation of the single correlation values from last 256 samples
      // 8 STS-sub-sequences * (16 data bins per STS-sub-sequence) * 2 (oversampling-factor) = 256 = correl_sum_len 
      temp1_i = cor_1_i - correlation_1ST_store_real[correlation_1ST_store_index];
      freq1_i += temp1_i;
      temp1_q = cor_1_q - correlation_1ST_store_imag[correlation_1ST_store_index];
      freq1_q += temp1_q; 
      //  if (correlation_1ST_store_index > 76) printf("%4d %4d (%d)\n", temp1_i, temp1_q, correlation_1ST_store_index);
      freq1_i_tmp = freq1_i >> 13;
      freq1_q_tmp = freq1_q >> 13;
   
      // Calculate auto-correlation sum for freq. offset estimation sliding summation of the single correlation values from last 256 samples
      temp2_i = correlation_1ST_store_real[(correlation_1ST_store_index - FreqEstStartSlSum - 1) & 255] - correlation_1ST_store_real[(correlation_1ST_store_index - FreqEstStopSlSum - 1) & 255];
      freq2_i += temp2_i;
      temp2_q = correlation_1ST_store_imag[(correlation_1ST_store_index - FreqEstStartSlSum - 1) & 255] - correlation_1ST_store_imag[(correlation_1ST_store_index - FreqEstStopSlSum - 1) & 255];
      freq2_q += temp2_q;  
      freq2_i_tmp = freq2_i >> 5;
      freq2_q_tmp = freq2_q >> 5;
      //  printf("%4d %4d\n", temp2_i, temp2_q);

      // Shift register for sliding summation:
      correlation_1ST_store_real[correlation_1ST_store_index] = cor_1_i;
      correlation_1ST_store_imag[correlation_1ST_store_index] = cor_1_q;
      correlation_1ST_store_index= ((correlation_1ST_store_index + 1) & 255);
   
      // Norm of auto-correlation of burst detection
      *freq_est_norm_out = (freq1_i_tmp*freq1_i_tmp) + (freq1_q_tmp*freq1_q_tmp);

      // Find start point, when looking for max. in auto-correlation (magn)
      if (*freq_est_norm_out > burst_threshold && *burst_found_out == 0) {
	*burst_found_out = 1;
	*freq_est_norm_max_out = *freq_est_norm_out;
      }

      *freq_est_phase_out_real = freq_est_phase_out_real_prev;
      *freq_est_phase_out_imag = freq_est_phase_out_imag_prev;
      if (*burst_found_out == 1)
	{
	  // Start now looking for new max in freq_est_norm
	  if (*freq_est_norm_out > *freq_est_norm_max_out)
	    {
	      *freq_est_norm_max_out = *freq_est_norm_out;
	      freq_est_phase_out_real_prev = *freq_est_phase_out_real = freq2_i_tmp;
	      freq_est_phase_out_imag_prev = *freq_est_phase_out_imag = freq2_q_tmp;
	      *burst_found_pulse = 0;
	    }
	  else
	    *burst_found_pulse = 1;
	}
      else
	*burst_found_pulse = 0;
    }
}
