#include "bf2_fifo_stage0.h"

void bf2_fifo_stage0(float *data_i_in, float *data_q_in, float *data_i_out, float *data_q_out)
{
  float data_i_tmp = *data_i_in;
  float data_q_tmp = *data_q_in;
  //static float fifo_i_array[1];
  //static float fifo_q_array[1];

  *data_i_out = data_i_tmp;
  *data_q_out = data_q_tmp;
    
  //fifo_i_array[0] = data_i_tmp;
  //fifo_q_array[0] = data_q_tmp;
}

