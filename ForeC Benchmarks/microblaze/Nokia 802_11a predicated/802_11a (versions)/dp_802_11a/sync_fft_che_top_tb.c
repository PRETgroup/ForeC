////////////////////////////////////////////////////////////////////////////////
//
// Module       : sync_fft_che_top_tb.c
//
////////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cplx.h"
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

#define __cordic_instances_ 2
#define __correl_instances_ 2
#define __fts_instances_    2
#define __arctan_instances_ 3

#define __output_
//#undef __output_


int main(int argc, char ** argv)

{
	struct timeval tv_start, tv_end;
	
	int init_modules = 0; // 0 => intitialization/reset, 1 => data processing mode
	int init_modules_s = 0;
	icomplex freq_sync_correl_2STS_output;
	icomplex correlation_1ST;
	int burst_found_out;
	icomplex freq_est_phase_out; 
	int freq_est_norm_out; 
	int freq_est_norm_max_out;
	int angle;
	icomplex data_out_FT;
	int maximum_found;
	int CHE_flag = 0;
	int mk_test = 0;
	int GI_Flag = 0;
	int iter = 0;
	
	// FILE handling variables
	// Open to read
	FILE *file_re_in, *file_im_in;
	file_re_in = fopen("../CCSS_ref_data/rx_real_data.am","r");
	file_im_in = fopen("../CCSS_ref_data/rx_imag_data.am","r");
	
	// open to write
	FILE *freq_sync_correl_2STS_out_I, *freq_sync_correl_2STS_out_Q;
	FILE *FS_single_correl_I, *FS_single_correl_Q;
	FILE *fft_re_reversed, *fft_im_reversed;
	FILE *freq_est_phase_out_I, *freq_est_phase_out_Q;
	FILE *CHE_out_I, *CHE_out_Q; 
	FILE *CHC_out_I, *CHC_out_Q; 
	FILE *fft_re_out, *fft_im_out;
	freq_sync_correl_2STS_out_I = fopen("./plainC_SimOutput/freq_sync_correl_2STS_out_I.am","w");
	freq_sync_correl_2STS_out_Q = fopen("./plainC_SimOutput/freq_sync_correl_2STS_out_Q.am","w");
	FS_single_correl_I = fopen("./plainC_SimOutput/FS_single_correl_I.am","w");
	FS_single_correl_Q = fopen("./plainC_SimOutput/FS_single_correl_Q.am","w");
	fft_re_reversed = fopen("./plainC_SimOutput/fft_reversed_re_out.am","w");
	fft_im_reversed = fopen("./plainC_SimOutput/fft_reversed_im_out.am","w");	
	freq_est_phase_out_I = fopen("./plainC_SimOutput/freq_est_phase_out_I.am","w");
	freq_est_phase_out_Q = fopen("./plainC_SimOutput/freq_est_phase_out_Q.am","w");
	CHE_out_I = fopen("./plainC_SimOutput/CHE_out_I.am","w"); 
	CHE_out_Q = fopen("./plainC_SimOutput/CHE_out_Q.am","w"); 
	CHC_out_I = fopen("./plainC_SimOutput/CHC_out_I.am","w"); 
	CHC_out_Q = fopen("./plainC_SimOutput/CHC_out_Q.am","w");
	fft_re_out = fopen("./plainC_SimOutput/fft_re_out.am","w");
	fft_im_out = fopen("./plainC_SimOutput/fft_im_out.am","w");
	
	icomplex freq_sync_correl_2STS_input;
	int freq_sync_correl_2STS_input_pre_size = 32 * oversampling_factor;
	icomplex freq_sync_correl_2STS_input_pre[freq_sync_correl_2STS_input_pre_size];
	int freq_sync_correl_2STS_input_view_size = 32 * oversampling_factor + 1;
	icomplex freq_sync_correl_2STS_input_view[freq_sync_correl_2STS_input_view_size];
	
	icomplex cordic_out;
	int cordic_out_pre_size = 63 + 120;
	icomplex cordic_out_pre[cordic_out_pre_size];
	
	read_quant_data ();
	
	size_t input_size;
	icomplex *input;
	
	{
		struct stat st;
		int i = 0;
		
		stat ("../CCSS_ref_data/rx_real_data.am", &st);
		input_size = st.st_size / 10;
		input = (icomplex *) malloc (input_size * sizeof (icomplex));
		
		while(!feof(file_re_in) && !feof(file_im_in))
		{
			char re_in[20];
			char im_in[20];
			
			fgets (re_in, 20, file_re_in);
			fgets (im_in, 20, file_im_in);
			
			input[i].re = (int) atof(re_in);
			input[i].im = (int) atof(im_in);
			
			++i;
		}
		input_size = i;
	}
	
	gettimeofday(&tv_start, NULL); 
	
#pragma omp parallel num_threads (1) default (none)			\
private (maximum_found, correlation_1ST,				\
freq_est_norm_max_out, freq_est_norm_out,			\
freq_sync_correl_2STS_output,				\
burst_found_out, 						\
freq_est_phase_out,						\
angle, cordic_out,						\
data_out_FT)							\
firstprivate (file_re_in, file_im_in,					\
init_modules, init_modules_s,				\
CHE_flag, iter, input_size)				\
shared (freq_sync_correl_2STS_out_I,					\
freq_sync_correl_2STS_out_Q,					\
FS_single_correl_I, FS_single_correl_Q,			\
fft_re_reversed, fft_im_reversed,				\
freq_est_phase_out_I, freq_est_phase_out_Q,			\
CHE_out_I, CHE_out_Q, CHC_out_I, CHC_out_Q,			\
fft_re_out, fft_im_out, mk_test, GI_Flag, input)		\
firstprivate (freq_sync_correl_2STS_input, freq_sync_correl_2STS_input_pre_size, \
freq_sync_correl_2STS_input_pre, freq_sync_correl_2STS_input_view, \
freq_sync_correl_2STS_input_view_size,			\
cordic_out_pre_size, cordic_out_pre)
	{
#pragma omp single
		{
			unsigned long long downsampling_flag = 0;
			char re_in[20];
			char im_in[20];
			
			int view_init_modules[2];
			icomplex view_freq_sync_correl_2STS_output[2];
			int view_angle[2];
			
			int burst_found_pulse;
			
			int FTS_burst_found_pulse_view[368];/* 191 PRE plus 64 bursts of 2.  */
			int FTS_view_init_modules[128];     /* 64 bursts of 2.  */
			icomplex FTS_cordic_out_view[247];  /* 63 PRE plus 64 bursts of 1.  */
			
			icomplex FTS_data_out_FT_view[64];
			int FTS_maximum_found_view[64];
			
			int atan_view_init_modules[64];     /* 64 bursts of 1.  */
			icomplex atan_view_freq_est_phase_out[64];
			int atan_view_angle[64];
			int atan_view_angle_shift[64];
			int burst_found_pulse_view[367];
			int angle_shift;
			
			int k;
			
			/* PRE operators ...  */
#pragma omp task output (freq_sync_correl_2STS_input << freq_sync_correl_2STS_input_pre[freq_sync_correl_2STS_input_pre_size])
			{
				int i;
				for (i = 0; i < freq_sync_correl_2STS_input_pre_size; ++i)
				{
					freq_sync_correl_2STS_input_pre[i].re = 0;
					freq_sync_correl_2STS_input_pre[i].im = 0;
				}
			}
#pragma omp task output (cordic_out << cordic_out_pre[cordic_out_pre_size])
			{
				int i;
				for (i = 0; i < cordic_out_pre_size; ++i)
				{
					cordic_out_pre[i].re = 0;
					cordic_out_pre[i].im = 0;
				}
			}
#pragma omp task output (burst_found_pulse << burst_found_pulse_view[303])
			{
				int i;
				for (i = 0; i < 303; ++i)
					burst_found_pulse_view[i] = 0;
			}
			
			
			/* Pipeline ...  */
			for (k = 0; k < input_size; ++k)
			{
#pragma omp task shared (input) firstprivate (init_modules, k) output (freq_sync_correl_2STS_input, init_modules_s)
				{ 
					freq_sync_correl_2STS_input.re = input[k].re;
					freq_sync_correl_2STS_input.im = input[k].im;
					init_modules_s = init_modules;
				}
				
				// Autocorrelation of two STS for burst detection
#pragma omp /* parallel */ task input (freq_sync_correl_2STS_input >> freq_sync_correl_2STS_input_view[1]) \
output (freq_sync_correl_2STS_output, correlation_1ST) num_threads (__correl_instances_)
				{
					freq_sync_correl_2STS (1, freq_sync_correl_2STS_input_view,
										   &freq_sync_correl_2STS_output.re, &freq_sync_correl_2STS_output.im,
										   &correlation_1ST.re, &correlation_1ST.im);
				}
				
				// Sliding Window autocorrelation for burst detection
#pragma omp task input (init_modules_s, correlation_1ST)		\
output (burst_found_pulse, freq_est_phase_out)			\
private (burst_found_out, freq_est_norm_out, freq_est_norm_max_out)
				{
					frequency_sync_slidsum (init_modules_s, 0, correlation_1ST.re, correlation_1ST.im,
											&burst_found_out, &burst_found_pulse,
											&freq_est_phase_out.re, &freq_est_phase_out.im,
											&freq_est_norm_out, &freq_est_norm_max_out);
				}
				
				/* Downsampled filters.  */
				if ((downsampling_flag & 63) == 0)
				{
					// Phase calculation via arctan + Conversion from alpha into angle in radians:
#pragma omp /* parallel */ task input (init_modules_s >> atan_view_init_modules[64], \
freq_est_phase_out >> atan_view_freq_est_phase_out[64]) \
output (angle_shift << atan_view_angle_shift[64]) num_threads (__arctan_instances_)
					arctan (atan_view_init_modules, atan_view_freq_est_phase_out, atan_view_angle_shift);
					
#pragma omp task input (init_modules_s >> atan_view_init_modules[64],	\
angle_shift >> atan_view_angle_shift[64],	\
burst_found_pulse >> burst_found_pulse_view[64]) \
output (angle << atan_view_angle[64])
					steteful_accumulate_angle_shift (atan_view_init_modules, burst_found_pulse_view, atan_view_angle_shift, atan_view_angle);
				}
				
				if ((downsampling_flag & 127) == 0)
				{
					// Fine time synchronization using crosscorrelation
#pragma omp /* parallel */ task input (init_modules_s >> FTS_view_init_modules[128],	\
burst_found_pulse >> FTS_burst_found_pulse_view[128], \
cordic_out >> FTS_cordic_out_view[64]) \
output (data_out_FT << FTS_data_out_FT_view[64], maximum_found << FTS_maximum_found_view[64]) num_threads (__fts_instances_)
					fine_time_sync (FTS_view_init_modules, FTS_burst_found_pulse_view, FTS_cordic_out_view,
									FTS_data_out_FT_view, FTS_maximum_found_view);
				}
				
				if ((downsampling_flag & 1) == 0)
				{
					// Frequency Offset correction via cordic algorithm
#pragma omp /* parallel */ task input (init_modules_s >> view_init_modules[2],	\
freq_sync_correl_2STS_output >> view_freq_sync_correl_2STS_output[2], \
angle >> view_angle[2]) output (cordic_out) num_threads (__cordic_instances_)
					cordic_turn(view_init_modules[0], view_freq_sync_correl_2STS_output[0].re, view_freq_sync_correl_2STS_output[0].im,
								view_angle[0], &cordic_out.re, &cordic_out.im);
					
					
#pragma omp task input (data_out_FT, maximum_found) \
shared (fft_re_reversed, fft_im_reversed, fft_re_out, fft_im_out, CHE_out_I, CHE_out_Q, CHC_out_I, CHC_out_Q, mk_test, CHE_flag, GI_Flag)
					{
						float real_out_demux[64 /* define buffer_len */], imag_out_demux[64 /* define buffer_len */];
						int data_remove_GI_reorder_real[52], data_remove_GI_reorder_imag[52];
						int input_CHE_real[104];
						int input_CHE_imag[104];
						int output_CHE_real[52];
						int output_CHE_imag[52];
						int output_CHC_real[52];
						int output_CHC_imag[52];
						int start, j;
						
						const float FFT_output_scale = 11.0/8.0;
						
						if (maximum_found == 1)
						{
							float re_out;
							float im_out;
							
							// Remove Guard Interval (or better here: Mark guard interval data with a Flag. GI_Flag = '1' = > GI-Data...)
							mark_GI_data (mk_test, &GI_Flag);
							
							// Only "real" data, which is related to GI_Flag = 0 is processed further:
							if (GI_Flag == 0)
							{
								
								mk_test = 1;
								
								fft64 (1, data_out_FT.re, data_out_FT.im, &re_out, &im_out);
								
#ifdef __output_
								fprintf (fft_re_reversed, "%12f\n", re_out);
								fprintf (fft_im_reversed, "%12f\n", im_out);
#endif
								
								// Demultiplexing of the data-stream for multi-stream mode and reordering of FFT output to get linear output.
								mstream_demux1 (1, (float)(re_out), (float)(im_out), &start, real_out_demux, imag_out_demux);
								
								if (iter < 63)
									iter++;
								else
								{
									iter = 0;
									
									scale_reorder_removeGB (real_out_demux, imag_out_demux, FFT_output_scale, input_CHE_real, input_CHE_imag, data_remove_GI_reorder_real, data_remove_GI_reorder_imag, CHE_flag);
									
									if (CHE_flag == 3)
										channel_estimation (input_CHE_real, input_CHE_imag, output_CHE_real, output_CHE_imag);
									
									if (CHE_flag >= 3)
										channel_correction (data_remove_GI_reorder_real, data_remove_GI_reorder_imag, output_CHE_real, output_CHE_imag, output_CHC_real, output_CHC_imag);
									
									
#ifdef __output_
									for (j = 0; j < 64; j++) {
										fprintf (fft_re_out,"%12f\n", real_out_demux[j]);
										fprintf (fft_im_out,"%12f\n", imag_out_demux[j]);
									}
									if (CHE_flag == 3)
										for (j = 0; j < 52; j++)
										{
											fprintf (CHE_out_I, "%d \n", output_CHE_real[j]);
											fprintf (CHE_out_Q, "%d \n", output_CHE_imag[j]);
										}
									if (CHE_flag >= 3)
										for (j = 0; j < 52; j++){
											fprintf (CHC_out_I, "%d \n", (int) (output_CHC_real[j]));
											fprintf (CHC_out_Q, "%d \n", (int) (output_CHC_imag[j]));
										}
#endif
									
									if (CHE_flag < 5)
										CHE_flag++;
									
								}
							}
						}
					}
				}
				
				// Print some data to file:
#ifdef __output_
#pragma omp task input (freq_sync_correl_2STS_output, correlation_1ST,	freq_est_phase_out) \
shared (freq_sync_correl_2STS_out_I, freq_sync_correl_2STS_out_Q, FS_single_correl_I, FS_single_correl_Q, freq_est_phase_out_I, freq_est_phase_out_Q)
				{
					fprintf(freq_sync_correl_2STS_out_I,"%d\n", freq_sync_correl_2STS_output.re);
					fprintf(freq_sync_correl_2STS_out_Q,"%d\n", freq_sync_correl_2STS_output.im);
					fprintf(FS_single_correl_I,"%d\n", correlation_1ST.re);
					fprintf(FS_single_correl_Q,"%d\n", correlation_1ST.im);
					fprintf(freq_est_phase_out_I,"%d\n", freq_est_phase_out.re);
					fprintf(freq_est_phase_out_Q,"%d\n", freq_est_phase_out.im);
				}
#endif
				
				
				downsampling_flag++;
				init_modules = 1;
			}
		}
	}
	
	gettimeofday(&tv_end, NULL); 
	
	long time = (tv_end.tv_sec - tv_start.tv_sec) * 1000000 + (tv_end.tv_usec - tv_start.tv_usec);
	printf ("Time: %3.6fs\n", ((float) time) / 1000000.0);
	
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
