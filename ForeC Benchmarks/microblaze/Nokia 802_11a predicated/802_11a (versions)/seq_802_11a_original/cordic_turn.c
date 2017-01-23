// Cordic (derotation) algorithm

#include "cordic_turn.h"

void cordic_turn(int init, int xin, int yin, int angle, int *res_output_x, int *res_output_y)
{
  int FS_on = 1; // FS_on for output MUX
  int Latency_on = 0; // switch on Latency as it is in vhdl-model 1=On 0=Off
  int InLen = 10; // width of input signals
  int InLen_frac_bits = 0; // number of fractional bits in InLen
  int OutLen = 12; // precision of result
  int Stages = 12; // number of cordic stages
  int AngLen = 11; // width of input angle
  int IntAngLen = 16; // internal width of angle
  int IntXYLen = 12; // internal width of x,y
  int IntRegStages = 3; // number of cordic stages between two register stages
  long arc_tan_array_c[31] = 
    {1267733622,669835629,340019024,170669324,85417861,42719353,21360980
     ,10680653,5340347,2670176,1335088,667544,333772,166886,83443
     ,41722,20861,10430,5215,2608,1304,652,326,163,81,41,20,10,5,3,1};
  int fs_out_scale = 6;
  
  long res_x_latency[(Stages/IntRegStages)+2];
  long res_y_latency[(Stages/IntRegStages)+2];
  int i;
  int msb_reg;
  long x_in_reg, y_in_reg, angle_in_reg;
  long x_reg, y_reg, z_reg, x_temp, y_temp;
  float res_x;
  float res_y;
  int res_out_x;
  int res_out_y;

  // Initialization
  if (init == 0){
    for(i=0;i<((Stages/IntRegStages) + 1);i++){
      res_x_latency[i] = 0;
      res_y_latency[i] = 0;
    }
  }else{
  
  // INPUT PATTERN 
  x_in_reg = (long)(xin * pow(2.0, (double) InLen_frac_bits));
  y_in_reg = (long)(yin * pow(2.0, (double) InLen_frac_bits));
  angle_in_reg = (long)(angle);
  
  // CALCULATION
  msb_reg = (int)(angle_in_reg >> (AngLen - 3)) & 7;
  
  if(((angle_in_reg >> (AngLen - 3)) & 1) == 1) {
   z_reg = -1;
  } else {
   z_reg = 0;
  }
  z_reg = z_reg << (AngLen -2) | (angle_in_reg & ((long) (pow(2.0, (double) (AngLen - 2) )) - 1));
  z_reg = z_reg << (IntAngLen - AngLen);
  
  x_temp = x_in_reg << (IntXYLen - InLen);
  y_temp = y_in_reg << (IntXYLen - InLen);
  
  // --------------------------------------------------------------------- 
  // -- Evaluate first three MSB's of input angle and do a pre-rotation)   
  // --------------------------------------------------------------------- 
  
  switch (msb_reg) {
  case 0 : case 7 :
   // angle in [-1/4 Pi; 1/4 Pi] 
   x_reg = x_temp;
   y_reg = y_temp;
   break;
  case 5 : case 6 :
   // angle in [-3/4 Pi;-1/4 Pi] 
   x_reg = y_temp;
   y_reg = -x_temp;
   break;
  case 3 : case 4:
   // angle in [ 3/4 Pi; PI],[-Pi;-3/4 Pi]
   x_reg = -x_temp;
   y_reg = -y_temp;
   break;
  default :
   // angle in [ 1/4 Pi; 3/4 Pi]
   x_reg = -y_temp;
   y_reg = x_temp;
  }
  
  // -------------------------------------------------------------------
  // --  Cordic - Algorithm                                             
  // -------------------------------------------------------------------
  
  for(i=1;i<Stages;i++){
   if(z_reg < 0){
    x_temp = x_reg + (y_reg >> (i)) + ((y_reg >> (i-1)) & 1);
    y_temp = y_reg - (x_reg >> (i)) - ((x_reg >> (i-1)) & 1);
    z_reg  = z_reg + (arc_tan_array_c[i-1] >> (34 - IntAngLen))
                   + ((arc_tan_array_c[i-1] >> (33 - IntAngLen)) & 1);
   } else {
    x_temp = x_reg - (y_reg >> (i)) - ((y_reg >> (i-1)) & 1);
    y_temp = y_reg + (x_reg >> (i)) + ((x_reg >> (i-1)) & 1);
    z_reg  = z_reg - (arc_tan_array_c[i-1] >> (34 - IntAngLen))
                   - ((arc_tan_array_c[i-1] >> (33 - IntAngLen)) & 1);
   }
   x_reg = x_temp;
   y_reg = y_temp;
  }
  
  // OUTPUT PATTER
  if(Latency_on == 0){
   res_x = (float) (x_reg >> (IntXYLen - OutLen + 2)) / pow(2.0, (double) InLen_frac_bits);
   res_y = (float) (y_reg >> (IntXYLen - OutLen + 2)) / pow(2.0, (double) InLen_frac_bits);
  } else {
   res_x = (float) (res_x_latency[0] >> (IntXYLen - OutLen + 2)) / pow(2.0, (double) InLen_frac_bits);
   res_y = (float) (res_y_latency[0] >> (IntXYLen - OutLen + 2)) / pow(2.0, (double) InLen_frac_bits);
  }

  res_out_x = (int)(res_x);
  res_out_y = (int)(res_y);

  // Output MUX:
  // If FS_on == true  => frequency corrected data muxed to the output
  // If FS_on == false => cordic input data is only bypassed to the output without any correction
  if (FS_on == 1){
    *res_output_x = (res_out_x * fs_out_scale)/16; // >> 4;
    *res_output_y = (res_out_y * fs_out_scale)/16; // >> 4;
  }else{
    *res_output_x = xin;
    *res_output_y = yin;
  }
  
  for(i=1;i<(Stages/IntRegStages) + 2;i++){
   res_x_latency[i-1] = res_x_latency[i];
   res_y_latency[i-1] = res_y_latency[i];
  }
  if(Stages%IntRegStages == 0){
   res_x_latency[(Stages/IntRegStages)] = x_reg;
   res_y_latency[(Stages/IntRegStages)] = y_reg;
  } else {
   res_x_latency[(Stages/IntRegStages) + 1] = x_reg;
   res_y_latency[(Stages/IntRegStages) + 1] = y_reg;
  }
 }
}
