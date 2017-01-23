// Fine time estimation: Finds exact start of Long TS1 (after Long GI)

#include "fine_time_sync.h"



// Constant definitions: 
#define Searchwin_length       120
#define time_corr_long_thresh 2000

static int data_store_real[buffer_depth];
static int data_store_imag[buffer_depth];
static int data_store_index;
static int data_quant_real[64];
static int data_quant_imag[64];
static int data_quant_index;
static int data_quant_trs_real[64];
static int data_quant_trs_imag[64];
static int fine_time_est_int;
static int fine_time_est_new;
static int FTS_count;
static int difference_in_fine_time_est;
static int maximum;
static int maximum_new;
static int maximum_found;
static int downsampling_flag;

void fine_time_sync_init(int * maximum_found_out)
{
  int i;

  for(i=0;i<buffer_depth;i++){
    data_store_real[i] = 0.0;
    data_store_imag[i] = 0.0;
  }
  data_store_index= 0;
  
  for(i=0;i<64;i++){
    data_quant_real[i] = 0.0;
    data_quant_imag[i] = 0.0;
    data_quant_trs_real[i] = 0.0;
    data_quant_trs_imag[i] = 0.0;
  }
  data_quant_index= 0;

   downsampling_flag = 1;

   fine_time_est_int = 0;
   fine_time_est_new = 0;

   FTS_count = 0;

   float re_max, im_max;
    
   re_max = 0.0;
   im_max = 0.0;

   // File handling
   FILE *data_quant_trs_i, *data_quant_trs_q;
  char quant_re[20];
  char quant_im[20];
   data_quant_trs_i = fopen("../CCSS_ref_data/data_quant_trs_i.am","r");
   data_quant_trs_q = fopen("../CCSS_ref_data/data_quant_trs_q.am","r");
   for(i=0;i<64;i++){
     fgets(quant_re, 20, data_quant_trs_i);
     data_quant_trs_real[i] = atoi(quant_re);      
     fgets(quant_im, 20, data_quant_trs_q);
     data_quant_trs_imag[i] = atoi(quant_im);  
   }  
   // closing input files 
   fclose(data_quant_trs_i);
   fclose(data_quant_trs_q);      

   *maximum_found_out = 0;

}

void fine_time_sync(int init, 
		    int burst_start_found, 
		    int data_in_real, int data_in_imag, 
		    int * data_out_real, int * data_out_imag, 
		    int *  maximum_found_out)
{

  int j;
  int data_in_sign_re;
  int data_in_sign_im;
  int time_corr_long_re_1;
  int time_corr_long_re_2;
  int time_corr_long_im_1;
  int time_corr_long_im_2;
  int time_corr_long_re;
  int time_corr_long_im;
  int time_corr_long_norm;



 // Initialization
 if (init == 0){

 } else {

   // 2-times Downsampling of input data ("data_in_real/imag" and of    
   if (downsampling_flag == 0){

  // delay data by 32+RxTimingOffset samples (after LongGI, start of LTS1)
   if (maximum_found == 1){
     *data_out_real = (int)(data_store_real[data_store_index]);
     *data_out_imag = (int)(data_store_imag[data_store_index]);
     *maximum_found_out = 1;
   } else{
     *data_out_real = 0; 
     *data_out_imag = 0;
     *maximum_found_out = 0;
   }
   data_store_real[data_store_index] = data_in_real;
   data_store_imag[data_store_index] = data_in_imag;
   data_store_index= (data_store_index + 1) % buffer_depth;

  if (data_in_real > 0) {
    data_in_sign_re = 1;
  } else if (data_in_real < 0) {
    data_in_sign_re = -1;
  } else {
    data_in_sign_re = 0;
  }
  if (data_in_imag > 0) {
    data_in_sign_im = 1;
  } else if (data_in_imag < 0) {
    data_in_sign_im = -1;
  } else {
    data_in_sign_im = 0;
  }

  data_quant_real[data_quant_index]= data_in_sign_re;
  data_quant_imag[data_quant_index]= data_in_sign_im;
  data_quant_index= (data_quant_index + 1) & 63;
  
  time_corr_long_re = 0;
  time_corr_long_im = 0;
  for( j=0; j<64; j++){
    time_corr_long_re_1 = (int)(data_quant_real[(data_quant_index + j) & 63] * data_quant_trs_real[j]);
    time_corr_long_re_2 = (int)(data_quant_imag[(data_quant_index + j) & 63] * data_quant_trs_imag[j]);
    time_corr_long_re += time_corr_long_re_1 + time_corr_long_re_2;
    time_corr_long_im_1 = (int)(data_quant_imag[(data_quant_index + j) & 63] * data_quant_trs_real[j]);
    time_corr_long_im_2 = (int)(data_quant_real[(data_quant_index + j) & 63] * data_quant_trs_imag[j]);
    time_corr_long_im += time_corr_long_im_1 - time_corr_long_im_2;
  }    
  time_corr_long_norm = ((abs(time_corr_long_re)>>2) * (abs(time_corr_long_re)>>2) + (abs(time_corr_long_im)>>2)*(abs(time_corr_long_im)>>2));
 
  if (burst_start_found == 0){
    FTS_count = 0;
    maximum = time_corr_long_thresh;
    fine_time_est_int = 0;
    maximum_found = 0;
    //xxx*burst_start_pulse = 0;
    //xxx*FPE_reset_pulse = 0; 
  } else {
    if (FTS_count < Searchwin_length){
             
      // Storing the two maximum LTS peak values.
      if (time_corr_long_norm >= maximum) {
	maximum_new = time_corr_long_norm;
	// store maximum estimation value index
	fine_time_est_new = FTS_count;
	// This variable looks for the distance between the two maximas:
	difference_in_fine_time_est = fine_time_est_new - fine_time_est_int;
  
	if ((difference_in_fine_time_est < 60 || difference_in_fine_time_est > 68) || maximum_found == 0) {    
	  fine_time_est_int = fine_time_est_new;
	  //*burst_start_pulse = 1;
	  maximum_found = 1;
	  //xxx*FPE_reset_pulse = 0;
	} else {
	  //*burst_start_pulse = 0;
	  //xxx*FPE_reset_pulse = 0;
	}
      } else {
	//*burst_start_pulse = 0;
	//xxx*FPE_reset_pulse = 0;
      }
      
      if (FTS_count == Searchwin_length-1) {
	if (maximum_found == 0) {
	  printf ("\n fine_time_sync : no maximum found with cross-correlation > " + time_corr_long_thresh);
	  printf (" (false edge detection in FPE) ");
	} else {
	  //printf("Frequency_sync was succesfully !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
	}
      }
      FTS_count += 1;
      // Debug:
      //printf("FTS_count: %d\n", FTS_count);
       
    } else {
      // FTS_count = Searchwin_length && burst_found = 1
      //*burst_start_pulse = 0;
      // In case of a false edge detection (no cross-correlation > threshold found in FTS) => reset FPE using port "*FPE_reset_pulse"
      //xxx*FPE_reset_pulse = 0;
    }  
  } 
  downsampling_flag = 1;
   } else {
     downsampling_flag = 0;
   }
   
 }
}
