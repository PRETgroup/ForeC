#include "timeshift.h"

void timeshift(int init, int data_in_real, int data_in_imag, int *data_out_real, int *data_out_imag)
{
  int static buffer_real[128];
  int static buffer_imag[128];
  int static cnt = 0;
  int j;

    if (cnt < 64){
      // Read in data
      buffer_real[cnt+64] = data_in_real;
      buffer_imag[cnt+64] = data_in_imag;
      // Write out data
      if (cnt < 57){ 
	*data_out_real = buffer_real[cnt+7];
	*data_out_imag = buffer_imag[cnt+7];
      } else {
	*data_out_real = buffer_real[cnt-57];
	*data_out_imag = buffer_imag[cnt-57];
      }
      cnt = cnt + 1;
    } else {
      if ((cnt >= 64) && (cnt <= 127)){
	// Read in data
	buffer_real[cnt-64] = data_in_real;
	buffer_imag[cnt-64] = data_in_imag;
		
	// Write out data
	if (cnt < 121){ 
	  *data_out_real = buffer_real[cnt+7];
	  *data_out_imag = buffer_imag[cnt+7];
	} else {
	  *data_out_real = buffer_real[cnt-57];
	  *data_out_imag = buffer_imag[cnt-57];
	}
	cnt = cnt + 1;

	if (cnt == 128){ 
	  cnt = 0;
	};

      } 
    }
}
