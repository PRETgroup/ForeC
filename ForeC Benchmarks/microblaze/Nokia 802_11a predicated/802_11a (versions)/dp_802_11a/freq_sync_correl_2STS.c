// Calculates the single delayed auto-correlations (from I,Q) for the freqsyncdet using 2 short training symbols delay.

#include "cplx.h"
#include "freq_sync_correl_2STS.h"

void
freq_sync_correl_2STS (int init, icomplex *input,
		       int *output_I, int *output_Q,
		       int *correlation_1ST_i, int *correlation_1ST_q)
{
  // Variable declaration
  int i;
  int data_in_i1, data_in_q1;
  int data_in_idel1, data_in_qdel1;
  int correlation_1ST_i_1,correlation_1ST_q_1; 
  int correlation_1ST_i_2, correlation_1ST_q_2;

  // Reset or initialization action
  if (init != 0)
    {
      data_in_i1 = input[64].re >> 2; // Divide input data by 4.
      data_in_q1 = input[64].im >> 2;

      data_in_idel1 = input[0].re;
      data_in_idel1 = data_in_idel1 >> 2;
      data_in_qdel1 = input[0].im;
      data_in_qdel1 = data_in_qdel1 >> 2; 
  
      correlation_1ST_i_1 = data_in_i1 * data_in_idel1;
      correlation_1ST_i_2 = data_in_q1 * data_in_qdel1;
      *correlation_1ST_i = correlation_1ST_i_1 + correlation_1ST_i_2;
  
      correlation_1ST_q_1 = data_in_q1 * data_in_idel1;
      correlation_1ST_q_2 = data_in_i1 * data_in_qdel1;
      *correlation_1ST_q = correlation_1ST_q_1 - correlation_1ST_q_2;

      // output data = input data delayed by 20 samples to compensate delay of frequency_sync
      *output_I = input[44].re;
      *output_Q = input[44].im;
    }
}
