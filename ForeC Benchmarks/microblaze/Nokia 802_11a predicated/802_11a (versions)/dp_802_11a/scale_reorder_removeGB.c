#include "scale_reorder_removeGB.h"

void scale_reorder_removeGB(float input_I[buffer_len], float input_Q[buffer_len], float FFT_output_scale, int CHE_input_I[104], int CHE_input_Q[104], int payload_output_I[52], int payload_output_Q[52], int CHE_flag)
{
  int j;
  // For 802.11a the data order has to reordered again according to the standard:
  // Also 12 data values of the guard band have to be removed => Only 52 data values out of 64 data values are processed further.
  for(j=0;j<26; j++){
    payload_output_I[j+26] = (int)(FFT_output_scale * input_I[j+1]);
    payload_output_Q[j+26] = (int)(FFT_output_scale * input_Q[j+1]);
    payload_output_I[j] = (int)(FFT_output_scale * input_I[j+38]);
    payload_output_Q[j] = (int)(FFT_output_scale * input_Q[j+38]);
  }

  for(j=0;j<52;j++){
    if (CHE_flag == 1){
      CHE_input_I[j+((CHE_flag-1)*52)] = payload_output_I[j];
      CHE_input_Q[j+((CHE_flag-1)*52)] = payload_output_Q[j];
    }
    if (CHE_flag == 2){
      CHE_input_I[j+((CHE_flag-1)*52)] = payload_output_I[j];
      CHE_input_Q[j+((CHE_flag-1)*52)] = payload_output_Q[j];
    }
  }
}
