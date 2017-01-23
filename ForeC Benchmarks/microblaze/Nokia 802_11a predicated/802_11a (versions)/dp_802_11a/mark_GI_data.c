#include "mark_GI_data.h"

void mark_GI_data (int init, int *GI_Flag)
{
static int cnt_16;
static int cnt_64;
static int cnt_128;

 if (init == 0){
   cnt_128 = 0;
   cnt_64 = 0;
   cnt_16 = 0;
   *GI_Flag = 0;
 } else {
   // For LTS1 and LTS2:
   if (cnt_128 < 127){
     cnt_128 = cnt_128 + 1;
     *GI_Flag = 0;
   } else {
     // For GI:
     if ((cnt_16 < 16) && (cnt_64 == 0)){
       *GI_Flag = 1;
       cnt_16 = cnt_16 + 1;
     } else {
       // For data:
       if (cnt_64 < 63){
	 *GI_Flag = 0;
	 cnt_64 = cnt_64 + 1;
       } else {
	 cnt_64 = 0;
	 cnt_16 = 0;
       }
     }
   }
 }
}
