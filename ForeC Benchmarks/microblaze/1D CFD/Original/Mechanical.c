#include "oned_cfd.h"
#include <deadline.h>


//enumerate mech type
#define MECH_VALVE 1
#define MECH_PUMP 2

//#define OUTPUT_REG_BASE 	0x00
//#define OUTPUT	(*(volatile float *)(OUTPUT_REG_BASE + 0x00))

/* #define INPUT_REG_BASE		0x08 */
/* #define INPUT1	(*(volatile float *)(INPUT_REG_BASE  + 0x00)) */
/* #define INPUT2	(*(volatile float *)(INPUT_REG_BASE  + 0x04)) */
/* #define INPUT3	(*(volatile float *)(INPUT_REG_BASE  + 0x08)) */
/* #define INPUT4	(*(volatile float *)(INPUT_REG_BASE  + 0x0C)) */


#if MECH_TYPE == MECH_VALVE
float valve_pos[] = {1.000000f, 0.929429f, 0.860600f, 0.793560f, 0.728357f, 0.665045f, 0.603682f, 0.544331f, 0.487064f, 0.431959f, 0.379106f, 0.328603f, 0.280566f, 0.235129f, 0.192450f, 0.152721f, 0.116179f, 0.083131f, 0.053995f, 0.029391f, 0.010391f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 0.000000f};
#endif

#ifndef _FUNCNAME_
#define _FUNCNAME_ main
#endif

int _FUNCNAME_(void)
{
	int i = -1;
	int nsec, sec;
	SET_TIME(CYCLE_PERIOD, 0, nsec, sec);
	while(1)
	{
#if MECH_TYPE == MECH_PUMP
		OTP = 1470900;
#elif MECH_TYPE == MECH_VALVE
		i++;
		OTP = valve_pos[i];
#endif

		DELAY_UNTIL(nsec, sec);
		SET_TIME(CYCLE_PERIOD, 0, nsec, sec);

	}
}
