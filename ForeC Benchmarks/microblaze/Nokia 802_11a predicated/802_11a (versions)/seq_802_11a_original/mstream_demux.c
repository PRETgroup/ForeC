#include "mstream_demux.h"

void mstream_demux(int init, float InData_re, float InData_im, int *start, float OutData_re[buffer_len], float OutData_im[buffer_len])
{
  int i;
  static int counter;
  static int count_mod3;
  int fft_pos;
  static int inv_index;
  int init_tmp;
  
  float re_int;
  float im_int;
  static float array_re[buffer_len];
  static float array_im[buffer_len];
  int index_int;
  int m_int;
  static int inv_int;
  static int mux_cnt;
  static int start_flag;
  int start_tmp;
  
  init_tmp = init;
  
  if (init_tmp == 0)
    {
      fft_pos = 0;
      start_flag = 0;
      for (i=0;i<buffer_len;i++)
	{
	  array_re[i] = 0;
	  array_im[i] = 0;
	}
      counter = 0;
      count_mod3 = 0;
      inv_index = 0;
      inv_int = 0;
      mux_cnt = 0;
    }
  else
    {     
      fft_pos = count_mod3*64 + counter;
      re_int = InData_re;
      im_int = InData_im;
      
      index_int = inv_int+mux_cnt;
      array_re[index_int] = re_int;
      array_im[index_int] = im_int;
      
      mux_cnt = 0;
      if (mux_cnt == 0)
	{
	  m_int = 64>>1;
	  if (inv_int < 63)
	    {
	      while (m_int>=2 && inv_int>=m_int)
		{
		  inv_int -= m_int;
		  m_int >>= 1;
		}
	      inv_int += m_int;	      
	    }
	  else
	    {
	      inv_int = 0;
	    }
        }
      
      count_mod3 = 0;
      if (counter < 63)
	{
	  counter++;
	  start_flag = 0;
	}
      else
	{
	  counter = 0;
	  start_flag = 1;
	}
      if (start_flag == 1)
	{
	  start_tmp = 1;
	  *start = start_tmp;
	  for (i=0;i<64;i++)
	    {
	      OutData_re[i] = array_re[i];
	      OutData_im[i] = array_im[i];
	    }
	}
      else
	{
	  start_tmp = 0;
	  *start = start_tmp;
	}
    } 
}

