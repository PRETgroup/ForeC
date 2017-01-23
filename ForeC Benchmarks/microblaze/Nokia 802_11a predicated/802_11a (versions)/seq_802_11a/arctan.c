// Angle calculation of I/Q-Datapairs using the arctan and
// calculates radians per sample from radians per Long Training Symbol.

#include "arctan.h"

static const long arctanTable[32] = {
	0             ,
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

void arctan(int init, int data_in_real, int data_in_imag, int burst_found_pulse, int *angle_out) { 
	// Constant definitions  
	#define Latency_on  0
	#define cordic_steps_c 11
	#define inter_reg_steps_c 3
	#define coriq0_in_width_c 18
	#define coriq0_out_width_c 2
	#define coriq0_alpha_width_c  11
	#define max_iq_width_c        20
	#define max_angle_width_c     12

	int alpha_out;
	int rad_tmp;  
	static int act_angle;
	int alpha_out_latency[5];	// alpha_out_latency[(cordic_steps_c/inter_reg_steps_c)+2];
	unsigned int ExactInternal, ExactAngle;
	unsigned int LSB_Ang, LSB_OutAng, LSB_Int;
	signed int i, x_i=0, y_i=0, x_i_1, y_i_1, z_i=0, z_i_1;
	signed int INTMAX = 2147483647;
	unsigned int UINTMAX = 4294967295;
	long angle; 
	long xin, yin;
  
	// Init:
	if (init == 0) {
		alpha_out = 0;
		act_angle = 0;
		rad_tmp = 0; 
		*angle_out = 0;
		
		for (i = 0; i < ((cordic_steps_c/inter_reg_steps_c) + 1); i++) /*#4#4*/ {
			alpha_out_latency[i] = 0;
		}
	} else {
		ExactAngle    = UINTMAX - 1048575;	// UINTMAX - (unsigned int) (pow(2.0, 32 - max_angle_width_c) - 1);
		ExactInternal = 1048575 << 12;		//((unsigned int) pow(2.0, max_iq_width_c) - 1) << (32-max_iq_width_c);

		LSB_Ang    = 1 << (32 - max_angle_width_c);
		LSB_Int    = 1 << (32 - max_iq_width_c);
		LSB_OutAng = 1 << (32 - coriq0_alpha_width_c);
 
		/* INPUT PATTERN */
		xin= data_in_real;
		yin= data_in_imag;
 
		/* CALCULATION */
		xin += (xin == -131072);	// (xin == -pow(2, coriq0_in_width_c-1));
		yin += (yin == -131072);	//(yin == -pow(2, coriq0_in_width_c-1));
		
		long x_i_temp0 = (xin << (30 - coriq0_in_width_c));
		long x_i_temp1 = (yin << (30 - coriq0_in_width_c));
		if (x_i_temp0 < 0) {
			x_i_temp0 = -x_i_temp0;
		}
		if (x_i_temp1 < 0) {
			x_i_temp1 = -x_i_temp1;
		}
		x_i = x_i_temp0 + x_i_temp1;	// abs(xin << (30 - coriq0_in_width_c)) + abs(yin << (30 - coriq0_in_width_c));
		
		long y_i_temp0 = (yin << (30 - coriq0_in_width_c));
		long y_i_temp1 = (xin << (30 - coriq0_in_width_c));
		if (y_i_temp0 < 0) {
			y_i_temp0 = -y_i_temp0;
		}
		if (y_i_temp1 < 0) {
			y_i_temp1 = -y_i_temp1;
		}
		y_i = y_i_temp0 - y_i_temp1;	// abs(yin << (30 - coriq0_in_width_c)) - abs(xin << (30 - coriq0_in_width_c));
		
		z_i = 512 << 20;	// ((int) pow(2.0, max_angle_width_c-3)) << (32 - max_angle_width_c);

		/* ***** Computation of Cordic iterations.*/
		for (i = 1; i< cordic_steps_c; i++) /*#11#11*/ {
			if (y_i > 0) {
				x_i_1 = x_i + (((y_i >> (i+i/2)) & ExactInternal)   + ((y_i >> (i+i/2-1)) & LSB_Int));
				y_i_1 = y_i - (((x_i >> (i-i/2)) & ExactInternal)   + ((x_i >> (i-i/2-1)) & LSB_Int));
				z_i_1 = z_i + (((arctanTable[i] >> 2) & ExactAngle) + ((arctanTable[i] >> 1) & LSB_Ang));
			} else {
				x_i_1 = x_i - (((y_i >> (i+i/2)) & ExactInternal)   + ((y_i >> (i+i/2-1)) & LSB_Int));
				y_i_1 = y_i + (((x_i >> (i-i/2)) & ExactInternal)   + ((x_i >> (i-i/2-1)) & LSB_Int));
				z_i_1 = z_i - (((arctanTable[i] >> 2) & ExactAngle) + ((arctanTable[i] >> 1) & LSB_Ang));
			}
			x_i = x_i_1 & ExactInternal;
			y_i = y_i_1 & ExactInternal;
			z_i = z_i_1 & ExactAngle;

			if (i/2 != i*((float)0.5)) {
				y_i = y_i << 1;
			}
		}

 		angle  = (z_i + ((z_i << 1) & LSB_OutAng)) >> (32 - coriq0_alpha_width_c);
 
		if (xin >= 0 && yin < 0) {
			angle = -(angle);
		} else if (xin < 0 && yin >= 0) {
			angle = (INTMAX >> (32 - coriq0_alpha_width_c)) + 1 - angle;
		} else if (xin < 0 && yin < 0) {
			angle = angle - (INTMAX >> (32-coriq0_alpha_width_c)) - 1;
		} else if (xin == 0 && yin == 0) {
			angle = -1;
 		}
 		
		if (angle == 1024) {	// pow(2, coriq0_alpha_width_c-1)
			angle = -angle;
		}
		
		/* OUTPUT PATTER */
		if (Latency_on == 0) {
			alpha_out = (int)(angle);
		} else {
			alpha_out = (int)(alpha_out_latency[0]);
		}

		rad_tmp = -alpha_out;
 
		if (burst_found_pulse == 0) {
			act_angle = 0;
		} 
		act_angle += rad_tmp;
 
		if (act_angle < -65536){
			act_angle = 131072 + act_angle;
		} else if (act_angle > 65535){
			act_angle = -131072 + act_angle;
		}

		*angle_out = act_angle >> 6;

		for (i=1; i < (cordic_steps_c/inter_reg_steps_c) + 2; i++) /*#5#5*/ {
			alpha_out_latency[i-1] = alpha_out_latency[i];
		}
		
		if (cordic_steps_c % inter_reg_steps_c == 0) {
			alpha_out_latency[3] = angle;	// alpha_out_latency[(cordic_steps_c/inter_reg_steps_c)]
		} else {
			alpha_out_latency[4] = angle;	// alpha_out_latency[(cordic_steps_c/inter_reg_steps_c) + 1]
		}
	}
}





