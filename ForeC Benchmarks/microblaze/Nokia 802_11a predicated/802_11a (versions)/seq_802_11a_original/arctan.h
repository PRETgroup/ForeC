#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define oversampling_factor 2            // Data oversampling factor 

void arctan(int init, int data_in_real, int data_in_imag, int burst_found_pulse, int *angle_out);
