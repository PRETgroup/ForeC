////////////////////////////////////////////////////////////////////////////////
//
// Module       : sync_fft_che_top_tb.c
//
////////////////////////////////////////////////////////////////////////////////

#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>

#include "freq_sync_correl_2STS.h"
#include "frequency_sync_slidsum.h"
#include "arctan.h"
#include "cordic_turn.h"
#include "fine_time_sync.h"
#include "fft64.h"
#include "mstream_demux.h"
#include "mark_GI_data.h"
#include "scale_reorder_removeGB.h"
#include "CHE.h"

#define buffer_len 64

#define __output_

typedef struct icomplex {
	int re;
	int im;
} icomplex;

typedef struct fcomplex {
	float re;
	float im;
} fcomplex;

int main(int argc, char ** argv) {
	// FILE handling variables
	// Open to read
	FILE *file_re_in, *file_im_in;
	file_re_in = fopen("../CCSS_ref_data/rx_real_data.am","r");
	file_im_in = fopen("../CCSS_ref_data/rx_imag_data.am","r");

	// open to write
	FILE *freq_sync_correl_2STS_out_I, *freq_sync_correl_2STS_out_Q;
	freq_sync_correl_2STS_out_I = fopen("./plainC_SimOutput/freq_sync_correl_2STS_out_I.am","w");
	freq_sync_correl_2STS_out_Q = fopen("./plainC_SimOutput/freq_sync_correl_2STS_out_Q.am","w");
	
	FILE *FS_single_correl_I, *FS_single_correl_Q;
	FS_single_correl_I = fopen("./plainC_SimOutput/FS_single_correl_I.am","w");
	FS_single_correl_Q = fopen("./plainC_SimOutput/FS_single_correl_Q.am","w");
	
	FILE *fft_re_reversed, *fft_im_reversed;
	fft_re_reversed = fopen("./plainC_SimOutput/fft_reversed_re_out.am","w");
	fft_im_reversed = fopen("./plainC_SimOutput/fft_reversed_im_out.am","w");

	FILE *freq_est_phase_out_I, *freq_est_phase_out_Q;
	freq_est_phase_out_I = fopen("./plainC_SimOutput/freq_est_phase_out_I.am","w");
	freq_est_phase_out_Q = fopen("./plainC_SimOutput/freq_est_phase_out_Q.am","w");

	FILE *CHE_out_I, *CHE_out_Q; 
	CHE_out_I = fopen("./plainC_SimOutput/CHE_out_I.am","w"); 
	CHE_out_Q = fopen("./plainC_SimOutput/CHE_out_Q.am","w"); 

	FILE *CHC_out_I, *CHC_out_Q; 
	CHC_out_I = fopen("./plainC_SimOutput/CHC_out_I.am","w"); 
	CHC_out_Q = fopen("./plainC_SimOutput/CHC_out_Q.am","w");

	FILE *fft_re_out, *fft_im_out;
	fft_re_out = fopen("./plainC_SimOutput/fft_re_out.am","w");
	fft_im_out = fopen("./plainC_SimOutput/fft_im_out.am","w");

	int input_size;
	icomplex *input;
	{
		struct stat st;
		stat ("../CCSS_ref_data/rx_real_data.am", &st);
		input_size = st.st_size / 10;
		input = (icomplex *) malloc (input_size * sizeof (icomplex));

		input_size = 0;
		while(!feof(file_re_in) && !feof(file_im_in)) {
			char re_in[20];
			char im_in[20];

			fgets (re_in, 20, file_re_in);
			fgets (im_in, 20, file_im_in);

			input[input_size].re = (int) atof(re_in);
			input[input_size].im = (int) atof(im_in);

			input_size++;
		}
	}
	
	int init_modules = 0; // 0 => intitialization/reset, 1 => data processing mode
	int CHE_flag = 0;
	int downsampling_flag = 0;
	int mk_test = 0;
	int GI_Flag = 0;

	int i = 0;

	int maximum_found;
	fine_time_sync_init(&maximum_found);

	// Signal processing part:
	int k = 0;
	for (k = 0; k < input_size; ++k) {
		// READ in input data for synchronization:
		fcomplex freq_sync_correl_2STS_input;
		freq_sync_correl_2STS_input.re = input[k].re;
		freq_sync_correl_2STS_input.im = input[k].im;

		// Autocorrelation of two STS for burst detection
		icomplex freq_sync_correl_2STS_output;
		icomplex correlation_1ST;
		freq_sync_correl_2STS(
			// inputs
			1, 
			(int)(freq_sync_correl_2STS_input.re), 
			(int)(freq_sync_correl_2STS_input.im), 
			// outputs
			&freq_sync_correl_2STS_output.re, 
			&freq_sync_correl_2STS_output.im, 
			&correlation_1ST.re, 
			&correlation_1ST.im
		);

		// Sliding Window autocorrelation for burst detection
		int rx_start = 0;
		int burst_found_out;
		int burst_found_pulse_out;
		int burst_found_pulse_for_FT; 
		icomplex freq_est_phase_out; 
		int freq_est_norm_out; 
		int freq_est_norm_max_out;
		frequency_sync_slidsum(	
			// inputs
			init_modules, 
			rx_start, 
			correlation_1ST.re, 
			correlation_1ST.im, 
			//outputs
			&burst_found_out, 			// unused
			&burst_found_pulse_out, 
			&burst_found_pulse_for_FT, 
			&freq_est_phase_out.re, 
			&freq_est_phase_out.im, 
			&freq_est_norm_out, 		// unused
			&freq_est_norm_max_out		// unused
		);

		// Phase calculation via arctan + Conversion from alpha into angle in radians:
		int angle;
		arctan(
			// inputs
			init_modules, 
			freq_est_phase_out.re, 
			freq_est_phase_out.im, 
			burst_found_pulse_out, 
			//output
			&angle
		);

		// Frequency Offset correction via cordic algorithm
		icomplex cordic_out;
		cordic_turn(
			// inputs
			init_modules, 
			freq_sync_correl_2STS_output.re, 
			freq_sync_correl_2STS_output.im, 
			angle, 
			// outputs
			&cordic_out.re, 
			&cordic_out.im
		);

		// Fine time synchronization using crosscorrelation
		icomplex data_out_FT;
		fine_time_sync(
			// inputs
			init_modules,
			burst_found_pulse_for_FT, 
			cordic_out.re, 
			cordic_out.im, 
			//outputs
			&data_out_FT.re, 
			&data_out_FT.im, 
			&maximum_found
		);

		// Print some data to file:
#ifdef __output_
		fprintf(freq_sync_correl_2STS_out_I,"%d\n", freq_sync_correl_2STS_output.re);
		fprintf(freq_sync_correl_2STS_out_Q,"%d\n", freq_sync_correl_2STS_output.im);
		fprintf(FS_single_correl_I,"%d\n", correlation_1ST.re);
		fprintf(FS_single_correl_Q,"%d\n", correlation_1ST.im);
		fprintf(freq_est_phase_out_I,"%d\n", freq_est_phase_out.re);
		fprintf(freq_est_phase_out_Q,"%d\n", freq_est_phase_out.im);
#endif
      
		// downsampling 2:1
		if (downsampling_flag == 0) {
			if (maximum_found == 1) {
				// Remove Guard Interval (or better here: Mark guard interval data with a Flag. GI_Flag = '1' = > GI-Data...)
				mark_GI_data(
					// input 
					mk_test,
					//output 
					&GI_Flag
				);

				// Only "real" data, which is related to GI_Flag = 0 is processed further:
				if (GI_Flag == 0) {
					mk_test = 1;
					float re_out;
					float im_out;
					fft64(
						// inputs
						1, 
						data_out_FT.re, 
						data_out_FT.im, 
						// outputs
						&re_out, 
						&im_out
					);

#ifdef __output_
					fprintf(fft_re_reversed,"%12f\n", re_out);
					fprintf(fft_im_reversed,"%12f\n", im_out);
#endif

					// Demultiplexing of the data-stream for multi-stream mode and reordering of FFT output to get linear output.
					int start_out;
					float real_out_demux[buffer_len];
					float imag_out_demux[buffer_len];
					mstream_demux(
						// inputs
						1, 
						(float)(re_out), 
						(float)(im_out),
						// outputs 
						&start_out, 		// unused
						real_out_demux, 
						imag_out_demux
					);

					if (i < 63) {
						i++;
					} else {
						// reseting i
						i = 0;

						// Scale FFT output data, reorder data and remove the guard band (12 subcarriers):
						float FFT_output_scale = ((float)11.0)/((float)8.0);
						int input_CHE_real[104];
						int input_CHE_imag[104];
						int data_remove_GI_reorder_real[52];
						int data_remove_GI_reorder_imag[52];
						scale_reorder_removeGB(
							// inputs
							real_out_demux, 
							imag_out_demux, 
							FFT_output_scale, 
							CHE_flag,
							// outputs
							input_CHE_real, 
							input_CHE_imag, 
							data_remove_GI_reorder_real, 
							data_remove_GI_reorder_imag
						);	  

						int output_CHE_real[52];
						int output_CHE_imag[52];
						int output_CHC_real[52];
						int output_CHC_imag[52];
						if (CHE_flag == 3) {
							// Channel estimation (CHE):
							channel_estimation(
								// inputs
								input_CHE_real, 
								input_CHE_imag, 
								// outputs
								output_CHE_real, 
								output_CHE_imag
							);
						}
				
						if (CHE_flag >= 3) {
							// Channel correction (CHC):
							channel_correction(
								// inputs 
								data_remove_GI_reorder_real, 
								data_remove_GI_reorder_imag, 
								output_CHE_real, 
								output_CHE_imag, 
								// outputs
								output_CHC_real, 
								output_CHC_imag
							);
						}

#ifdef __output_
						// Print our reordered FFT output, which  is now linear and not bit-reversed anymore.
						int j;
						for (j = 0; j < 64; j++) /*#64#64*/ {
							fprintf(fft_re_out,"%12f\n", real_out_demux[j]);
							fprintf(fft_im_out,"%12f\n", imag_out_demux[j]);
						}
						
						if (CHE_flag == 3) {
							// Print CHE output data into file
							for(j = 0; j < 52; j++) /*#52#52*/ {
								fprintf(CHE_out_I,"%d \n",output_CHE_real[j]) ;
								fprintf(CHE_out_Q,"%d \n",output_CHE_imag[j]) ;
							}
						}
				
						if (CHE_flag >= 3) {
							// Print CHC output data into file
							for (j = 0; j < 52; j++) /*#52#52*/ {
								fprintf(CHC_out_I,"%d \n",(int)(output_CHC_real[j])) ;
								fprintf(CHC_out_Q,"%d \n",(int)(output_CHC_imag[j])) ;
							}
						}
#endif

						// incrementing CHE_flag
						if (CHE_flag < 5) {
							CHE_flag++;
						}
					}
				}
			}
			
			downsampling_flag = 1;
		} else {
			downsampling_flag = 0;
		}
		
		init_modules = 1;
	}

	// closing files
	fclose(file_re_in);
	fclose(file_im_in);

	fclose(freq_sync_correl_2STS_out_I);
	fclose(freq_sync_correl_2STS_out_Q);
	fclose(FS_single_correl_I);
	fclose(FS_single_correl_Q);
	fclose(fft_re_reversed);
	fclose(fft_im_reversed);
	fclose(fft_re_out);
	fclose(fft_im_out);
	fclose(freq_est_phase_out_I);
	fclose(freq_est_phase_out_Q);
	fclose(CHC_out_I);
	fclose(CHC_out_Q);

	fclose(CHE_out_I);
	fclose(CHE_out_Q);

	return 0;
}
