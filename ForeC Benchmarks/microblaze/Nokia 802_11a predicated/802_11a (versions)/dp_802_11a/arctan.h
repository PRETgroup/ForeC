#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define oversampling_factor 2            // Data oversampling factor 

void arctan(int *init, icomplex *input, int *angle_out);

void steteful_accumulate_angle_shift (int *init, int *burst_found_pulse, int *input, int *output);
