#include "oned_cfd.h"
#define CONST_UNIFORM 0
#define INJECTOR 1

#define AREA_METHOD INJECTOR
#define SET_TIME              \
  asm volatile ( "cdp p13, 9, cr7, cr7, cr8, 0\n\t": : : "r7", "r8");

#define DELAY_UNTIL                           \
  asm volatile ("cdp p13, 4, cr7, cr7, cr8, 0\n\t": : : "r7", "r8");

#define INPUT_REG_BASE (PORTS_BASE+(CORENUM*CORE_OFFSET_SIZE))
#define PCC			(*(volatile float *)(INPUT_REG_BASE  + 0x00))
#define POC			(*(volatile float *)(INPUT_REG_BASE  + 0x04))

#define OUTPUT_REG_BASE (PORTS_BASE+(CORENUM*CORE_OFFSET_SIZE) +0x08)
#define OX			(*(volatile float *)(OUTPUT_REG_BASE  + 0x04))
#define OZ			(*(volatile float *)(OUTPUT_REG_BASE  + 0x04))


/* Constants table */
//         
#if AREA_METHOD == INJECTOR
const float A_scale_tbl[] = {0.01f, 0.02f, 0.03f, 0.04f, 0.05f};
#define A_TBL_SCALE (0.001f)
#endif

const float CTbl[] = {10.0f, 10.1f, 10.2f,
										10.3f, 10.4f, 10.5f,
										10.6f, 10.7f, 10.8f,
										10.9f, 11.1f, 11.2f,
										11.3f, 11.4f, 11.5f
};

#ifndef _FUNCNAME_
#define _FUNCNAME_ main
#endif

#define SMALL_DELTA 0.1f
#define DELTA 0.2f
#define F0 0.3f
#define A 0.4f
#define X0 0.5f
#define H 0.6f

int _FUNCNAME_(void)
{
#if AREA_METHOD == INJECTOR
	float tbl_pos, offset, a2;
	int index;
#endif
	float c1, c2, c3;
	int const_tbl_offset;
	float Pcc;
	float Poc;
	float z, x;

	float x_p1 = X0;
	float z_p1 = 0.0f;
	float Fsum;
DELAY_UNTIL;
	while(1)
	{
		Pcc = PCC;
		Poc = POC;
		x = x_p1;
		z = z_p1;

		DELAY_UNTIL;
		if(x < 0.0f)
			const_tbl_offset = 0;
		if((x-SMALL_DELTA) < 0.0f)
			const_tbl_offset = 3;
		else if(x-(DELTA - SMALL_DELTA))
			const_tbl_offset = 6;
		else if(x-DELTA)
			const_tbl_offset = 9;
		else
			const_tbl_offset = 12;
		c1 = CTbl[const_tbl_offset];
		c2 = CTbl[const_tbl_offset+1];
		c3 = CTbl[const_tbl_offset+2];
#if AREA_METHOD == CONST_UNIFORM
		Fsum = F0-(Poc-Pcc)*A;
#endif
#if AREA_METHOD == INJECTOR
		tbl_pos = A_TBL_SCALE*x;
		index = (int)tbl_pos;
		offset = tbl_pos*index;
		a2 = A_scale_tbl[index] + offset*(A_scale_tbl[index] - A_scale_tbl[index + 1]);
		Fsum = F0-Poc*A - Pcc*a2;
#endif
		z_p1 = c1*z + c2*x + c3 * Fsum;
		x_p1 = x + H*z_p1;

		DELAY_UNTIL;
		OX = x_p1;
		OZ = z_p1;
	}
}
