/*
This model performs the 802.11a channel CORRECTION in the frequency domain.

Conjugate complex multiplication of CHE-output with payload-data.

*/

#include "CHE.h"

void channel_correction(int input_I[52], int input_Q[52], int output_CHE_I[52], int output_CHE_Q[52], int output_CHC_I[52], int output_CHC_Q[52])
{

  long int mult_CHC_I[52];
  long int mult_CHC_Q[52];
  int i;

  for (i=0; i < 52; i++) {  
    mult_CHC_I[i] = input_I[i] * output_CHE_I[i] + input_Q[i] * output_CHE_Q[i];
    mult_CHC_Q[i] = -input_I[i] * output_CHE_Q[i] + input_Q[i] * output_CHE_I[i];
    output_CHC_I[i] = mult_CHC_I[i] >> 10;
    output_CHC_Q[i] = mult_CHC_Q[i] >> 10;
  }
} 
