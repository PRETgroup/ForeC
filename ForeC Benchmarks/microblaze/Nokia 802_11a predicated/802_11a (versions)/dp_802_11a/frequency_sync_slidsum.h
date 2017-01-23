#define correl_sum_len 256          // Length of sliding summation over the correlations

void frequency_sync_slidsum(int mk_init, int rx_start, int correlation_1ST_real, int correlation_1ST_imag, int *burst_found_out, int *burst_found_pulse, int *freq_est_phase_out_real, int *freq_est_phase_out_imag, int *freq_est_norm_out, int *freq_est_norm_max_out);
