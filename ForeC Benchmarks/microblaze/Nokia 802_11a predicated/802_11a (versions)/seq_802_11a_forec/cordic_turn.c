// Cordic (derotation) algorithm

#include "cordic_turn.h"

#define InLen_frac_bits 0 // number of fractional bits in InLen
#define Latency_on 0 // switch on Latency as it is in vhdl-model 1=On 0=Off
#define OutLen 12 // precision of result
#define Stages 12 // number of cordic stages
#define InLen 10 // width of input signals
#define FS_on 1 // FS_on for output MUX
#define AngLen 11 // width of input angle
#define IntAngLen 16 // internal width of angle
#define IntXYLen 12 // internal width of x,y
#define IntRegStages 3 // number of cordic stages between two register stages
#define fs_out_scale 6

static long arc_tan_array_c[31] = {
	1267733622,
	669835629,
	340019024,
	170669324,
	85417861,
	42719353,
	21360980,
	10680653,
	5340347,
	2670176,
	1335088,
	667544,
	333772,
	166886,
	83443,
	41722,
	20861,
	10430,
	5215,
	2608,
	1304,
	652,
	326,
	163,
	81,
	41,
	20,
	10,
	5,
	3,
	1
};

void cordic_turn(
					// inputs
					const int init, 
					const int xin, 
					const int yin, 
					const int angle, 
					
					// outputs
					int *res_output_x, 
					int *res_output_y) {
	// Initialization
	if (init == 0) {

	} else {
		// INPUT PATTERN 
		long x_in_reg = (long)(xin * 1);	// (long)(xin * pow(2.0, (double) InLen_frac_bits));
		long y_in_reg = (long)(yin * 1);	// (long)(yin * pow(2.0, (double) InLen_frac_bits));
		long angle_in_reg = (long)(angle);
  
		// CALCULATION
		int msb_reg = (int)(angle_in_reg >> (AngLen - 3)) & 7;
  
  		long z_reg;
		if(((angle_in_reg >> (AngLen - 3)) & 1) == 1) {
			z_reg = -1;
		} else {
			z_reg = 0;
		}
		
		z_reg = z_reg << (AngLen - 2) | (angle_in_reg & ((long) (512 /*pow(2.0, (double) (AngLen - 2) )*/) - 1));
		z_reg = z_reg << (IntAngLen - AngLen);
  
		long x_temp = x_in_reg << (IntXYLen - InLen);
		long y_temp = y_in_reg << (IntXYLen - InLen);
  
		// --------------------------------------------------------------------- 
		// -- Evaluate first three MSB's of input angle and do a pre-rotation)   
		// --------------------------------------------------------------------- 
  		long x_reg, y_reg;
		if (msb_reg == 0 || msb_reg == 7) {
			// angle in [-1/4 Pi; 1/4 Pi] 
			x_reg = x_temp;
			y_reg = y_temp;
		} else if (msb_reg == 5 || msb_reg == 6) {
			// angle in [-3/4 Pi;-1/4 Pi] 
			x_reg = y_temp;
			y_reg = -x_temp;
		} else if (msb_reg == 3 || msb_reg == 4) {
			// angle in [ 3/4 Pi; PI],[-Pi;-3/4 Pi]
			x_reg = -x_temp;
			y_reg = -y_temp;
		} else {
			// angle in [ 1/4 Pi; 3/4 Pi]
			x_reg = -y_temp;
			y_reg = x_temp;
		}
  
		// -------------------------------------------------------------------
		// --  Cordic - Algorithm                                             
		// -------------------------------------------------------------------
  		int i;
		for(i = 1; i < Stages; i++) /*#12#12*/ {
			if(z_reg < 0){
				x_temp = x_reg + (y_reg >> (i)) + ((y_reg >> (i-1)) & 1);
				y_temp = y_reg - (x_reg >> (i)) - ((x_reg >> (i-1)) & 1);
				z_reg  = z_reg + (arc_tan_array_c[i-1] >> (34 - IntAngLen)) + ((arc_tan_array_c[i-1] >> (33 - IntAngLen)) & 1);
			} else {
				x_temp = x_reg - (y_reg >> (i)) - ((y_reg >> (i-1)) & 1);
				y_temp = y_reg + (x_reg >> (i)) + ((x_reg >> (i-1)) & 1);
				z_reg  = z_reg - (arc_tan_array_c[i-1] >> (34 - IntAngLen)) - ((arc_tan_array_c[i-1] >> (33 - IntAngLen)) & 1);
			}
			x_reg = x_temp;
			y_reg = y_temp;
		}
  
		// OUTPUT PATTER
		long res_x_latency[6];	// res_x_latency[(Stages/IntRegStages)+2];
		long res_y_latency[6];	// res_y_latency[(Stages/IntRegStages)+2];
		float res_x;
		float res_y;
		if (Latency_on == 0) {
			res_x = (float) (x_reg >> (IntXYLen - OutLen + 2)) / (float)1; // pow(2.0, (double) InLen_frac_bits);
			res_y = (float) (y_reg >> (IntXYLen - OutLen + 2)) / (float)1; // pow(2.0, (double) InLen_frac_bits);
		} else {
			res_x = (float) (res_x_latency[0] >> (IntXYLen - OutLen + 2)) / (float)1; // pow(2.0, (double) InLen_frac_bits);
			res_y = (float) (res_y_latency[0] >> (IntXYLen - OutLen + 2)) / (float)1; // pow(2.0, (double) InLen_frac_bits);
		}

		int res_out_x = (int)(res_x);
		int res_out_y = (int)(res_y);

		// Output MUX:
		// If FS_on == true  => frequency corrected data muxed to the output
		// If FS_on == false => cordic input data is only bypassed to the output without any correction
		if (FS_on == 1) {
			*res_output_x = (res_out_x * fs_out_scale)/16; // >> 4;
			*res_output_y = (res_out_y * fs_out_scale)/16; // >> 4;
		} else {
			*res_output_x = xin;
			*res_output_y = yin;
		}
  
		for (i = 1; i < (Stages/IntRegStages) + 2; i++) /*#6#6*/ {
			res_x_latency[i-1] = res_x_latency[i];
			res_y_latency[i-1] = res_y_latency[i];
		}
		
		if (Stages % IntRegStages == 0) {
			res_x_latency[4] = x_reg;	// res_x_latency[(Stages/IntRegStages)]
			res_y_latency[4] = y_reg;	// res_y_latency[(Stages/IntRegStages)]
		} else {
			res_x_latency[5] = x_reg;	// res_x_latency[(Stages/IntRegStages) + 1]
			res_y_latency[5] = y_reg;	// res_y_latency[(Stages/IntRegStages) + 1]
		}
	}
}



