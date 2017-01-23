#include "oned_cfd.h"
#include <deadline.h>


//enumerate global type
#define AD	0	//Speed of sound (A) times density
#define D		1 //density
#define	INV_AD 2 //Inverst of AD


//#define OUTPUT_REG_BASE 0x00
//#define OUTPUT_GLOBAL (*(volatile float *)(OUTPUT_REG_BASE + 0x00))

#define INPUT_REG_BASE  0x08
#define INPUT1 				(*(volatile float *)(INPUT_REG_BASE + 0x00))
#define INPUT2 				(*(volatile float *)(INPUT_REG_BASE + 0x04))
#define INPUT3 				(*(volatile float *)(INPUT_REG_BASE + 0x08))
#define INPUT4 				(*(volatile float *)(INPUT_REG_BASE + 0x0C))

//int iteration = 0;


#ifndef _FUNCNAME_
#define _FUNCNAME_ main
#endif

int _FUNCNAME_(void)
{
	register float og;
	int nsec, sec;
	SET_TIME(CYCLE_PERIOD, 0, nsec, sec);

	while(1)
	{
	/*Note:  Thiese should be simple 1D lookup tables, but leave them as 
	 * constants for now */
#if 	GLOBAL_TYPE == AD
#define OUTPUT_REG AD_REG
		og = 1.2E+6;
#elif GLOBAL_TYPE == D
#define OUTPUT_REG D_REG
		og = 1000;
#elif GLOBAL_TYPE == INV_AD
#define OUTPUT_REG INV_AD_REG
		og = 8.33333E-7;
#else
#error
#endif
		OUTPUT_REG = og;
		//		iteration++;
    DELAY_UNTIL(nsec, sec);
    SET_TIME(CYCLE_PERIOD, 0, nsec, sec);

	}
}
