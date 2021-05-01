/* A simple approach to FMradio.
 *
 * The code was addapted from Marco Cornero Aug'06 
 * for Acotes project. This version ensures to have
 * the same result that the stream one for plain C.
 * 
 * Author: David Rodenas-Pico, BSC
 * Creation Date: March 2007
 */


#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define KSMPS 1024
#define FM_MAX       5
#define FM_LIMIT     (65536/2)-1 

#define __avl_proc_  8


/* *********************************************** complex operations   */

typedef struct
{
  float real;
  float imag;
} complex;

#define M_PI   3.14159265358979323846  /* pi */
#define GAIN_LMR  2000

#define complex_conj(s, d)			\
  {						\
    (d)->real = (s)->real;			\
    (d)->imag = -1 * (s)->imag;			\
  }

#define complex_arg(x)				\
  atan2((x)->imag, (x)->real)

#define complex_mul(a, b, d)						\
  {									\
    (d)->real = (a)->real * (b)->real - ((a)->imag * (b)->imag);	\
    (d)->imag = (a)->real * (b)->imag + (a)->imag * (b)->real;		\
  }


/* *********************************************** auxiliar functions   */

short 
dac_cast_trunc_and_normalize_to_short(float f)
{
  short x;
  f = (f / FM_MAX)*FM_LIMIT;
  x = f;
  return x;
}

#if 0
/* *********************************************** file filters         */

void
file_to_stream(FILE* file, stream_t* output)
{
  int i;
  int room;
  float value;

  room= stream_room(output);
  for (i= 0; i < room; i++) {
    if (fread(&value, sizeof(value), 1, file)) {
      stream_push(output, &value);
    }
  }
}

void
stream_to_file(stream_t* input, FILE* file)
{
  int i;
  int count;
  float value;
  short res_int;
  
  count= stream_count(input);
  for (i= 0; i < count; i++)
    {
      stream_pop(input, &value);
      //fwrite(&value, sizeof(value), 1, file);
      res_int= dac_cast_trunc_and_normalize_to_short(value);
      fwrite(&res_int, sizeof(res_int), 1, file);
    }
}
#endif


/* *********************************************** fm_quad_demod        */

typedef struct {
  float history[2];
} fm_quad_demod_filter;

void
fm_quad_demod_init (fm_quad_demod_filter* filter)
{
  filter->history[0]= 0;
  filter->history[1]= 0;
}

void
fm_quad_demod (fm_quad_demod_filter* filter, float i1, float i2, float* result)
{
  complex x_N;
  complex x_N_1;
  complex x_N_1_conj;
  complex y_N;
  float demod, d_gain = 0.5;

  /*
   *
   * y(n) = angle(x(n)*conj(x(n-1))
   *
   */

  /* read two complex data */
  x_N.real = i2; x_N.imag = i1;
  x_N_1.real = filter->history[1]; x_N_1.imag = filter->history[0];
  
  /* compute */
  complex_conj(& x_N_1, & x_N_1_conj);
  complex_mul(& x_N_1_conj, & x_N, & y_N); 
  demod = d_gain * complex_arg(& y_N); 

  filter->history[0]= i1;
  filter->history[1]= i2;

  *result= demod;
}



/* *********************************************** multiply_square      */

void 
multiply_square(float i1, float i2, float* result)
{
  *result= GAIN_LMR * i1 * i2 * i2;
}


/* *********************************************** ntaps_filter         */

typedef struct ntaps_filter_conf
{
  double* coeff;
  int decimation;
  int taps;
  int next;
} ntaps_filter_conf;

#define WIN_HAMMING     0
#define WIN_HANNING     1
#define WIN_BLACKMAN    2

void 
compute_window(unsigned int ntaps, double *taps, unsigned int type)
{
  int n;
  int M = ntaps - 1;    // filter order

  if(type == WIN_HAMMING)
    {
      for (n = 0; n < ntaps; n++)
        taps[n] = 0.54 - 0.46 * cos ((2 * M_PI * n) / M);
    }
  else if(type == WIN_HANNING)
    {
      for (n = 0; n < ntaps; n++)
        taps[n] = 0.5 - 0.5 * cos ((2 * M_PI * n) / M);
    }
  else if(type == WIN_BLACKMAN)
    {
      for (n = 0; n < ntaps; n++)
        taps[n] = 0.42 - 0.50 * cos ((2*M_PI * n) / (M-1)) - 0.08 * cos ((4*M_PI * n) / (M-1));
    }
}

int 
compute_ntaps (float sampling_freq,
	       float transition_width,
	       int window_type)
{
  /* Mormalized transition width */
  float delta_f = transition_width / sampling_freq;

  float width_factor[3] = { 3.3, 3.1, 5.5 };

  /* compute number of taps required for given transition width */
  int ntaps = (int) (width_factor[window_type]/ delta_f + 0.5);

  if ((ntaps & 1) == 0)
    ntaps++;

  return ntaps;
}

void 
ntaps_filter_ffd_init(ntaps_filter_conf *conf, 
		      double cutoff_freq, 
		      double transition_band,
		      double gain,
		      int decimation,
		      double sampling_rate, 
		      int window_type)
{
  /* Taken from the GNU software radio .. */

  int n;
  int i;
  unsigned int ntaps;
  double* w;
  int M;
  double fwT0;
  double fmax;

  ntaps = compute_ntaps(sampling_rate, transition_band, window_type);
  conf->coeff = malloc(ntaps * sizeof(double));
  w = malloc(ntaps * sizeof(double));
  conf->taps = ntaps;
  conf->decimation = decimation;

  compute_window(ntaps, w, window_type);

  M = (ntaps - 1) / 2;

  fwT0 = 2 * M_PI * cutoff_freq / sampling_rate;

  for (n=0; n<ntaps; n++)
    conf->coeff[n]=0.0;

  for (n = -M; n <= M; n++) {
    if (n == 0)
      conf->coeff[n + M] = fwT0 / M_PI * w[n + M];
    else
      conf->coeff[n + M] =  sin (n * fwT0) / (n * M_PI) * w[n + M];
  }

  fmax = conf->coeff[0 + M];

  for (n = 1; n <= M; n++)
    fmax += 2 * conf->coeff[n + M];

  gain /= fmax; // normalize

  for (i = 0; i < ntaps; i++)
    conf->coeff[i] *= gain;

  free(w);
}


void
ntaps_filter_ffd (ntaps_filter_conf* conf, int input_size,
		 float *input, float* result)
{
  float sum;
  int i;

  sum = 0.0;
  for (i = 0; i < conf->taps; i++)
    {
      sum += input [i] * conf->coeff[conf->taps - i - 1];
    }

  *result = sum;
}


/* *********************************************** stereo_sum           */

void
stereo_sum(float data_spm, float data_smm, float* left, float* right)
{
  *left = (data_spm+data_smm);
  *right= (data_spm-data_smm);
}


/* *********************************************** subctract            */

void 
subctract(float i1, float i2, float* result)
{
  *result= i1 - i2;
}


/* *********************************************** program options      */

int
read_opts(int argc, char* argv[], 
	  FILE** input_file, 
	  FILE** output_file, 
	  FILE** text_file,
	  int* final_audio_frequency)
{
  char  input_filename[4096];
  char  output_filename[4096];
  char  text_filename[4096];


  /* arguments parsing */
  if ((argc < 1) || (argc > 3)) 
    {
      printf("Usage: fm_rcv [sample_file_name [audio_frequency]]\n");
      return 1;
    }
  if (argc == 1)
    {
      strcpy(input_filename, "input.dat");
    }
  else
    {
      strcpy(input_filename, argv[1]);
    }
  sprintf(output_filename,"%s.raw",argv[0]);
  sprintf(text_filename,"%s.txt",argv[0]);
  if(argc == 3)
    *final_audio_frequency = atoi(argv[2]);


  *input_file= fopen(input_filename, "r");
  if (*input_file == NULL) {
    printf("Cannot open input file %s\n", input_filename);
    return 1;
  }
  *output_file= fopen(output_filename, "w");
  if (*output_file == NULL) {
    printf("Cannot open output file %s\n", output_filename);
    return 1;
  }
  *text_file= fopen(text_filename, "w");
  if (*text_file == NULL) {
    printf("Cannot open output file %s\n", text_filename);
    return 1;
  }

  
  return 0;
}



/* *********************************************** main                 */

int 
main(int argc, char* argv[])
{
  ntaps_filter_conf lp_2_conf;
  ntaps_filter_conf lp_11_conf, lp_12_conf;
  ntaps_filter_conf lp_21_conf, lp_22_conf;
  ntaps_filter_conf lp_3_conf;
  fm_quad_demod_filter fm_qd_conf;

  int final_audio_frequency = 64*KSMPS;
  float input_rate = 512 * KSMPS;

  float inout_ratio;

  FILE* input_file;
  FILE* output_file;
  FILE* text_file;

  float read_buffer[16];

  float band_2;
  float band_3;
  float band_11;
  float band_12;
  float resume_1;
  float band_21;
  float band_22;
  float resume_2;

  float output1, output2;
  short output_short[2];

  int i=0;
  int maxtaps = 0;
  int maxtaps_minus_one;

  if (read_opts(argc, argv,&input_file,&output_file,&text_file, &final_audio_frequency))
    {
      return 1;
    }

  inout_ratio = ((int) input_rate)/final_audio_frequency;

  ntaps_filter_ffd_init(&lp_2_conf,  15000, 4000, 0.5, inout_ratio, input_rate, WIN_HANNING);
  ntaps_filter_ffd_init(&lp_11_conf, 53000, 4000, 1,   1,           input_rate, WIN_HANNING);
  ntaps_filter_ffd_init(&lp_12_conf, 23000, 4000, 1,   1,           input_rate, WIN_HANNING);
  ntaps_filter_ffd_init(&lp_21_conf, 21000, 2000, 1,   1,           input_rate, WIN_HANNING);
  ntaps_filter_ffd_init(&lp_22_conf, 17000, 2000, 1,   1,           input_rate, WIN_HANNING);
  ntaps_filter_ffd_init(&lp_3_conf,  15000, 4000, 1.0, inout_ratio, input_rate, WIN_HANNING);
  fm_quad_demod_init (&fm_qd_conf);

  if (maxtaps < lp_11_conf.taps) maxtaps = lp_11_conf.taps;
  if (maxtaps < lp_12_conf.taps) maxtaps = lp_12_conf.taps;
  if (maxtaps < lp_21_conf.taps) maxtaps = lp_21_conf.taps;
  if (maxtaps < lp_22_conf.taps) maxtaps = lp_22_conf.taps;
  if (maxtaps < lp_2_conf.taps) maxtaps = lp_2_conf.taps;
  maxtaps_minus_one = maxtaps - 1;

  float ffd_buffer;
  float fm_qd_buffer;
  int iter = 0;
  float view8[8];

  int maxtaps_plus_seven = maxtaps + 7;

  int diff_11 = maxtaps - lp_11_conf.taps;
  int diff_12 = maxtaps - lp_12_conf.taps;
  int diff_21 = maxtaps - lp_21_conf.taps;
  int diff_22 = maxtaps - lp_22_conf.taps;
  int diff_2 = maxtaps_plus_seven - lp_2_conf.taps;

  float view_11[maxtaps];
  float view_12[maxtaps];
  float view_21[maxtaps];
  float view_22[maxtaps];
  float view_2[maxtaps_plus_seven];
  float view_3[lp_3_conf.taps];
  int lp_3_taps_minus_eight = lp_3_conf.taps - 8;

  float fm_qd_buffer_pre[maxtaps];


#pragma omp parallel num_threads (1) default (none)			\
  shared (lp_3_taps_minus_eight, maxtaps, maxtaps_minus_one, maxtaps_plus_seven, view_11, view_12, view_21, view_22, view_2, view_3) \
  shared (diff_11, diff_12, diff_21, diff_22, diff_2, view8, iter, ffd_buffer, fm_qd_buffer, fm_qd_buffer_pre) \
  shared (input_file, output_file, text_file, lp_2_conf, lp_11_conf, lp_12_conf, lp_21_conf, lp_22_conf, lp_3_conf, fm_qd_conf) \
  private (read_buffer, band_2, band_3, band_11, band_12, resume_1, band_21, band_22, resume_2, output1, output2, output_short, i)
  {
#pragma omp single
    {

  /* Implement pre operations (add enough zeros at beginning of
     stream).  */
#pragma omp task output (fm_qd_buffer << fm_qd_buffer_pre[maxtaps_minus_one]) private (i)
      for (i = 0; i < maxtaps_minus_one; ++i)
	fm_qd_buffer_pre[i] = 0;

#pragma omp task output (ffd_buffer << view_3[lp_3_taps_minus_eight]) private (i)
      for (i = 0; i < lp_3_taps_minus_eight; ++i)
	view_3[i] = 0;


      while ((16 == fread (read_buffer, sizeof(float), 16, input_file)))
	{

#pragma omp task firstprivate (read_buffer) output (fm_qd_buffer << view8[8]) shared (fm_qd_conf) private (i)
	  for (i = 0; i < 8; i++)
	    fm_quad_demod (&fm_qd_conf, read_buffer[2*i], read_buffer[2*i + 1], &view8[i]);

	  for (i = 0; i < 8; i++)
	    {
#pragma omp task input (fm_qd_buffer >> view_11[1]) output (band_11)	\
  shared (lp_11_conf, diff_11) num_threads (3)
	      ntaps_filter_ffd (&lp_11_conf, 1, &view_11[diff_11], &band_11);

#pragma omp task input (fm_qd_buffer >> view_12[1]) output (band_12)	\
  shared (lp_12_conf, diff_12) num_threads (3)
	      ntaps_filter_ffd (&lp_12_conf, 1, &view_12[diff_12], &band_12);


#pragma omp task input (fm_qd_buffer >> view_21[1]) output (band_21)	\
  shared (lp_21_conf, diff_21) num_threads (6)
	      ntaps_filter_ffd (&lp_21_conf, 1, &view_21[diff_21], &band_21);

#pragma omp task input (fm_qd_buffer >> view_22[1]) output (band_22)	\
  shared (lp_22_conf, diff_22) num_threads (6)
	      ntaps_filter_ffd (&lp_22_conf, 1, &view_22[diff_22], &band_22);


#pragma omp task input (band_11, band_12, band_21, band_22) output (ffd_buffer)	\
  private (resume_1, resume_2)
	      {
		subctract (band_11, band_12, &resume_1);
		subctract (band_21, band_22, &resume_2);
		multiply_square (resume_1, resume_2, &ffd_buffer);
	      }
	    }

#if __avl_proc_ > 8
#if __avl_proc_ > 16
#pragma omp task input (fm_qd_buffer >> view_2[8]) output (band_2)	\
  shared (lp_2_conf, diff_2)
	  ntaps_filter_ffd (&lp_2_conf, 8, &view_2[diff_2], &band_2);

#pragma omp task input (ffd_buffer >> view_3[8]) output (band_3)	\
  shared (lp_3_conf)
	  ntaps_filter_ffd (&lp_3_conf, 8, view_3, &band_3);
#else
#pragma omp task input (fm_qd_buffer >> view_2[8], ffd_buffer >> view_3[8]) \
  output (band_2, band_3)						\
  shared (lp_2_conf, lp_3_conf, diff_2)
	  {
	    ntaps_filter_ffd (&lp_2_conf, 8, &view_2[diff_2], &band_2);
	    ntaps_filter_ffd (&lp_3_conf, 8, view_3, &band_3);
	  }
#endif
#pragma omp task input (band_2, band_3)					\
  shared (output_file, text_file) private (output_short, output1, output2)
	  {
	    stereo_sum (band_2, band_3, &output1, &output2);
	    output_short[0] = dac_cast_trunc_and_normalize_to_short (output1);
	    output_short[1] = dac_cast_trunc_and_normalize_to_short (output2);
	    fwrite (output_short, sizeof(short), 2, output_file);
	    //fprintf (text_file, "%-10.5f %-10.5f\n", output1, output2);
	    //fprintf (text_file, "%-10.5f %-10.5f \t %10d %10d\n", output1, output2, output_short[0], output_short[1]);
	  }
#else
#pragma omp task input (fm_qd_buffer >> view_2[8], ffd_buffer >> view_3[8]) \
  shared (output_file, text_file, lp_2_conf, lp_3_conf, diff_2)		\
  private (output_short, output1, output2, band_2, band_3)
	  {
	    ntaps_filter_ffd (&lp_2_conf, 8, &view_2[diff_2], &band_2);
	    ntaps_filter_ffd (&lp_3_conf, 8, view_3, &band_3);
	    stereo_sum (band_2, band_3, &output1, &output2);
	    output_short[0] = dac_cast_trunc_and_normalize_to_short (output1);
	    output_short[1] = dac_cast_trunc_and_normalize_to_short (output2);
	    fwrite (output_short, sizeof(short), 2, output_file);
	    //fprintf (text_file, "%-10.5f %-10.5f\n", output1, output2);
	    //fprintf (text_file, "%-10.5f %-10.5f \t %10d %10d\n", output1, output2, output_short[0], output_short[1]);
	  }

#endif
	  ++iter;
	}
    }
  }
  fclose (input_file);
  fclose (output_file);
  fclose (text_file);

  return 0;
}
