// Fine time estimation: Finds exact start of Long TS1 (after Long GI)

#include "cplx.h"
#include "fine_time_sync.h"



// Constant definitions: 
#define Searchwin_length       120
#define time_corr_long_thresh 2000

/* Const static data.  */
static int data_quant_trs_real[64];
static int data_quant_trs_imag[64];

void
read_quant_data ()
{
  FILE *data_quant_trs_i, *data_quant_trs_q;
  char quant_re[20];
  char quant_im[20];
  int i;

  data_quant_trs_i = fopen("../CCSS_ref_data/data_quant_trs_i.am","r");
  data_quant_trs_q = fopen("../CCSS_ref_data/data_quant_trs_q.am","r");

  for(i = 0; i < 64; i++)
    {
      fgets (quant_re, 20, data_quant_trs_i);
      data_quant_trs_real[i] = atoi(quant_re);      
      fgets (quant_im, 20, data_quant_trs_q);
      data_quant_trs_imag[i] = atoi(quant_im);  
    }
  fclose (data_quant_trs_i);
  fclose (data_quant_trs_q);
}

static inline int
get_sign (int x)
{
  return x > 0 ? 1 : (x < 0 ? -1 : 0);
}


void fine_time_sync(int *init,
		    int *burst_start_found,
		    icomplex *input,
		    icomplex *output,
		    int *maximum_found_out)
{
  int fine_time_est_int;
  int FTS_count;
  int maximum;
  int maximum_found;
  int i;

  /* Find either last reset point or whether there is anything left to
     do.  If we can't find a reset point, we get the values pre-set
     here.  */
  maximum_found = 1;
  FTS_count = Searchwin_length;
  for (i = 0; i < Searchwin_length; i++)
    {
      int ii = i << 1;
      if (burst_start_found[240 - ii] == 0)
	{
	  int k;

	  /* Recompute proper values starting here (this will
	     duplicate some work ...).  */
	  FTS_count = 0;
	  maximum = time_corr_long_thresh;
	  fine_time_est_int = 0;
	  maximum_found = 0;

	  for (k = 0; k < i; ++k)
	    {
	      int time_corr_long_re = 0;
	      int time_corr_long_im = 0;
	      int time_corr_long_norm;
	      int j;

	      for (j = 0; j < 64; j++)
		{
		  int time_corr_long_re_1;
		  int time_corr_long_re_2;
		  int time_corr_long_im_1;
		  int time_corr_long_im_2;
		  int sign_re = get_sign (input[120 - (i - k) + j].re);
		  int sign_im = get_sign (input[120 - (i - k) + j].im);

		  time_corr_long_re_1 = sign_re * data_quant_trs_real[j];
		  time_corr_long_re_2 = sign_im * data_quant_trs_imag[j];
		  time_corr_long_re += time_corr_long_re_1 + time_corr_long_re_2;
		  time_corr_long_im_1 = sign_im * data_quant_trs_real[j];
		  time_corr_long_im_2 = sign_re * data_quant_trs_imag[j];
		  time_corr_long_im += time_corr_long_im_1 - time_corr_long_im_2;
		}
	      time_corr_long_norm = ((abs(time_corr_long_re)>>2) * (abs(time_corr_long_re)>>2) + (abs(time_corr_long_im)>>2)*(abs(time_corr_long_im)>>2));

	      if (time_corr_long_norm >= maximum)
		{
		  int difference_in_fine_time_est = FTS_count - fine_time_est_int;

		  if ((difference_in_fine_time_est < 60 || difference_in_fine_time_est > 68) || maximum_found == 0)
		    {
		      fine_time_est_int = FTS_count;
		      maximum_found = 1;
		    }
		}
      	      FTS_count += 1;
	    }
	  break;
	}
    }

  for (i = 0; i < 64; ++i)
    {
      int ii = i << 1;
      if (init[ii] == 0)
	{
	  fine_time_est_int = 0;
	  FTS_count = 0;    

	  maximum_found_out[i] = 0;
	}
      else
	{
	  if (maximum_found == 1)
	    {
	      output[i].re = input[146 + i].re;
	      output[i].im = input[146 + i].im;
	      maximum_found_out[i] = 1;
	    }
	  else
	    {
	      output[i].re = 0; 
	      output[i].im = 0;
	      maximum_found_out[i] = 0;
	    }
 
	  if (burst_start_found[240 + ii] == 0)
	    {
	      FTS_count = 0;
	      maximum = time_corr_long_thresh;
	      fine_time_est_int = 0;
	      maximum_found = 0;
	    }
	  else if (FTS_count < Searchwin_length)
	    {
	      int time_corr_long_re = 0;
	      int time_corr_long_im = 0;
	      int time_corr_long_norm;
	      int j;

	      for (j = 0; j < 64; j++)
		{
		  int time_corr_long_re_1;
		  int time_corr_long_re_2;
		  int time_corr_long_im_1;
		  int time_corr_long_im_2;
		  int sign_re = get_sign (input[120 + j + i].re);
		  int sign_im = get_sign (input[120 + j + i].im);

		  time_corr_long_re_1 = sign_re * data_quant_trs_real[j];
		  time_corr_long_re_2 = sign_im * data_quant_trs_imag[j];
		  time_corr_long_re += time_corr_long_re_1 + time_corr_long_re_2;
		  time_corr_long_im_1 = sign_im * data_quant_trs_real[j];
		  time_corr_long_im_2 = sign_re * data_quant_trs_imag[j];
		  time_corr_long_im += time_corr_long_im_1 - time_corr_long_im_2;
		}
	      time_corr_long_norm = ((abs(time_corr_long_re)>>2) * (abs(time_corr_long_re)>>2) + (abs(time_corr_long_im)>>2)*(abs(time_corr_long_im)>>2));

	      if (time_corr_long_norm >= maximum)
		{
		  int difference_in_fine_time_est = FTS_count - fine_time_est_int;

		  if ((difference_in_fine_time_est < 60 || difference_in_fine_time_est > 68) || maximum_found == 0)
		    {
		      fine_time_est_int = FTS_count;
		      maximum_found = 1;
		    }
		}
      
	      if (FTS_count == Searchwin_length - 1)
		{
		  if (maximum_found == 0) {
		    printf ("\n fine_time_sync : no maximum found with cross-correlation > %d", time_corr_long_thresh);
		    printf (" (false edge detection in FPE) \n");
		  }
		}
	      FTS_count += 1;
	    }
	}
    }
}
