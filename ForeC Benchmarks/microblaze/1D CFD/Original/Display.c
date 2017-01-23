#include "oned_cfd.h"
#include <deadline.h>

//Assuming it takes one clock to read all I/O registers then our worst case time
//to read them all is the worst case number of input registers and global registers
#define READ_COMPLETE_TIMESTEP (LOCAL_CONST_BASE - INPUT_REG_BASE)

#define INPUT_REG_BASE (PORTS_BASE+(CORENUM*CORE_OFFSET_SIZE))
#define LP			(*(volatile float *)(INPUT_REG_BASE  + 0x00))
#define LQ			(*(volatile float *)(INPUT_REG_BASE  + 0x04))

#define P_OUT			(*(volatile float *)(0xFFFFFFE0))
#define Q_OUT			(*(volatile float *)(0xFFFFFFE4))


#ifndef _FUNCNAME_
#define _FUNCNAME_ main
#endif

int _FUNCNAME_(void)
{
  register float lp, lq;
  int nsec, sec;

  SET_TIME(CYCLE_PERIOD, 0, nsec, sec);

  while(1)
    {

	//Begin external read at start of timestep
	//Read from adjacent processors
	lp = LP; //Left (upstream) pressure
	lq = LQ; //Right (downstream) pressure


    DELAY_UNTIL(nsec, sec);
    SET_TIME(CYCLE_PERIOD, 0, nsec, sec);

    P_OUT = lp;
    Q_OUT = lq;


    }
}


