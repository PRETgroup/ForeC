// Angle calculation of I/Q-Datapairs using the arctan and
// calculates radians per sample from radians per Long Training Symbol.

#include "cplx.h"
#include "arctan.h"

  // Constant definitions  
#define Latency_on             0
#define cordic_steps_c        11
#define inter_reg_steps_c      3
#define coriq0_in_width_c     18
#define coriq0_out_width_c     2
#define coriq0_alpha_width_c  11
#define max_iq_width_c        20
#define max_angle_width_c     12

static const long arctanTable[32] = {0             ,
			 1267733622    , /*(long) (atan2(1.0 ,         2.0) * PI_factor),   1 */
			 669835629     , /*(long) (atan2(1.0 ,         4.0) * PI_factor),   2 */
			 340019024     , /*(long) (atan2(1.0 ,         8.0) * PI_factor),   3 */
			 170669324     , /*(long) (atan2(1.0 ,        16.0) * PI_factor),   4 */
			 85417861      , /*(long) (atan2(1.0 ,        32.0) * PI_factor),   5 */
			 42719353      , /*(long) (atan2(1.0 ,        64.0) * PI_factor),   6 */
			 21360980      , /*(long) (atan2(1.0 ,       128.0) * PI_factor),   7 */
			 10680653      , /*(long) (atan2(1.0 ,       256.0) * PI_factor),   8 */
			 5340347       , /*(long) (atan2(1.0 ,       512.0) * PI_factor),   9 */
			 2670176       , /*(long) (atan2(1.0 ,      1024.0) * PI_factor),  10 */
			 1335088       , /*(long) (atan2(1.0 ,      2048.0) * PI_factor),  11 */
			 667544        , /*(long) (atan2(1.0 ,      4096.0) * PI_factor),  12 */
			 333772        , /*(long) (atan2(1.0 ,      8192.0) * PI_factor),  13 */
			 166886        , /*(long) (atan2(1.0 ,     16384.0) * PI_factor),  14 */
			 83443         , /*(long) (atan2(1.0 ,     32768.0) * PI_factor),  15 */
			 41722         , /*(long) (atan2(1.0 ,     65536.0) * PI_factor),  16 */
			 20861         , /*(long) (atan2(1.0 ,    131072.0) * PI_factor),  17 */
			 10430         , /*(long) (atan2(1.0 ,    262144.0) * PI_factor),  18 */
			 5215          , /*(long) (atan2(1.0 ,    524288.0) * PI_factor),  19 */
			 2608          , /*(long) (atan2(1.0 ,   1048576.0) * PI_factor),  20 */
			 1304          , /*(long) (atan2(1.0 ,   2097152.0) * PI_factor),  21 */
			 652           , /*(long) (atan2(1.0 ,   4194304.0) * PI_factor),  22 */
			 326           , /*(long) (atan2(1.0 ,   8388608.0) * PI_factor),  23 */
			 163           , /*(long) (atan2(1.0 ,  16777216.0) * PI_factor),  24 */
			 81            , /*(long) (atan2(1.0 ,  33554432.0) * PI_factor),  25 */
			 41            , /*(long) (atan2(1.0 ,  67108864.0) * PI_factor),  26 */
			 20            , /*(long) (atan2(1.0 , 134217728.0) * PI_factor),  27 */
			 10            , /*(long) (atan2(1.0 , 268435456.0) * PI_factor),  28 */
			 5             , /*(long) (atan2(1.0 , 536870912.0) * PI_factor),  29 */
			 3             , /*(long) (atan2(1.0 ,1073741824.0) * PI_factor),  30 */
			 1               /*(long) (atan2(1.0 ,2147483648.0) * PI_factor)   31 */
  };

void arctan (int *init, icomplex *input, int *angle_out)
{ 
  //  double coriq0_in_frac_bits = 0.0;
  unsigned int ExactInternal, ExactAngle;
  unsigned int LSB_Ang, LSB_OutAng, LSB_Int;
  signed int i, x_i=0, y_i=0, x_i_1, y_i_1, z_i=0, z_i_1;
  signed int INTMAX = 2147483647;
  unsigned int UINTMAX = 4294967295;
  long angle; 
  long xin, yin;
  
  int iter;

  long tmp_alpha = pow(2, coriq0_alpha_width_c-1);
  long tmp_width = -pow(2, coriq0_in_width_c-1);
  int tmp_max_angle = (int) pow(2.0, max_angle_width_c-3);

  ExactAngle    = UINTMAX - (unsigned int) (pow(2.0, 32-max_angle_width_c) - 1);
  ExactInternal = ((unsigned int) pow(2.0, max_iq_width_c) - 1) << (32-max_iq_width_c);

  LSB_Ang    = 1 << (32 - max_angle_width_c);
  LSB_Int    = 1 << (32 - max_iq_width_c);
  LSB_OutAng = 1 << (32 - coriq0_alpha_width_c);

  /* Search for a reset point or the initialization point (whichever
     comes first).  */
  for (iter = 0; iter < 64; ++iter)
    {


    }

  for (iter = 0; iter < 64; ++iter)
    {
      if (init[iter] == 0)
	{
	  angle_out[iter] = 0;
	}
      else
	{
 
	  /* INPUT PATTERN */
	  xin = input[iter].re;
	  yin = input[iter].im;
 
	  /* CALCULATION */
	  if (xin == tmp_width) xin++;
	  if (yin == tmp_width) yin++;
	  x_i = abs(xin << (30 - coriq0_in_width_c)) + abs(yin << (30 - coriq0_in_width_c));
	  y_i = abs(yin << (30 - coriq0_in_width_c)) - abs(xin << (30 - coriq0_in_width_c));
	  z_i = tmp_max_angle << (32 - max_angle_width_c);

	  /* ***** Computation of Cordic iterations.*/
	  for (i=1; i<cordic_steps_c; i++)
	    {
	      if (y_i > 0)
		{
		  x_i_1 = x_i + (((y_i>>(i+i/2)) & ExactInternal)   + ((y_i>>(i+i/2-1)) & LSB_Int));
		  y_i_1 = y_i - (((x_i>>(i-i/2)) & ExactInternal)   + ((x_i>>(i-i/2-1)) & LSB_Int));
		  z_i_1 = z_i + (((arctanTable[i]>>2) & ExactAngle) + ((arctanTable[i]>>1) & LSB_Ang));
		}
	      else
		{
		  x_i_1 = x_i - (((y_i>>(i+i/2)) & ExactInternal)   + ((y_i>>(i+i/2-1)) & LSB_Int));
		  y_i_1 = y_i + (((x_i>>(i-i/2)) & ExactInternal)   + ((x_i>>(i-i/2-1)) & LSB_Int));
		  z_i_1 = z_i - (((arctanTable[i]>>2) & ExactAngle) + ((arctanTable[i]>>1) & LSB_Ang));
		}
	      x_i = x_i_1 & ExactInternal;
	      y_i = y_i_1 & ExactInternal;
	      z_i = z_i_1 & ExactAngle;
     
	      if (i/2 != i*0.5)
		y_i = y_i<<1;
	    }

	  angle  = (z_i + ((z_i<<1) & LSB_OutAng)) >> (32 - coriq0_alpha_width_c);
 
	  if (xin >= 0 && yin < 0) 
	    angle = -(angle);
	  else if (xin < 0 && yin >= 0) 
	    angle = (INTMAX >> (32 - coriq0_alpha_width_c)) + 1 - angle;
	  else if (xin < 0 && yin < 0)
	    angle = angle - (INTMAX >> (32-coriq0_alpha_width_c)) - 1;
	  else if (xin == 0 && yin == 0)
	    angle = -1;
 
	  if (angle == tmp_alpha)
	    angle = -angle;
 
	  angle_out[iter] = -angle;
 	}
    }
}


void
steteful_accumulate_angle_shift (int *init, int *burst_found_pulse, int *input, int *output)
{
  static int act_angle;
  int iter;

  for (iter = 0; iter < 64; ++iter)
    {
      if (init[iter] == 0)
	{
	  act_angle = 0;
	  output[iter] = 0;
	}
      else
	{
	  if (burst_found_pulse[iter + 303] == 0)
	    act_angle = 0;

	  /* OUTPUT PATTER */
	  act_angle += input[iter];
 
	  if (act_angle < -65536)
	    act_angle = 131072 + act_angle;
	  else if (act_angle > 65535)
	    act_angle = -131072 + act_angle;
 
	  if (oversampling_factor == 1)
	    output[iter] = act_angle >> 5;
	  else if (oversampling_factor == 2)
	    output[iter] = act_angle >> 6;
	  else if (oversampling_factor == 4)
	    output[iter] = act_angle >> 7;
	  //printf ("%d\n", angle_out[iter]);
	}
    }
}
