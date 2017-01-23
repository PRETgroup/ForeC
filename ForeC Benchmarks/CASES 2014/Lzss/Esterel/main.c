// Located in: microblaze_0/include/xparameters.h
#include "xparameters.h"
#include "xbasic_types.h"

// Xilinx Microblaze Processor Version Register
#include "pvr.h"

// Hardware counter connected via a direct FSL bus.
#include "counter_dfsl.h"
Counter counter;
#define FSL_COUNTER_ID			2

// #define DEBUG
#include "debug.h"

#include "lzss_config.h"


int main(int argc, char *argv[])
{
	// Initialise and start counting the elapsed cycles for each reaction.
	counterInitialise(counter);
	
	int i;
    int cycle = 0;
    int stop = 0;

	// pvr = Processor Version Register
	unsigned int pvr0;
	getpvr(0, pvr0);
	pvr0 &= MICROBLAZE_PVR0_USER1_MASK;

    if (pvr0 == 0) {
    	xil_printf("%d\n", pvr0);
    	
    	// Master
    } else {
    	// Slave
    	xil_printf("%d\n", pvr0);

        lzss_archiver(1);
    }

    INIT_MODULE();
    while (!stop) {
        input_signal[0].u.set("null");

		// Start counting the elapsed cycles for the current reaction.
		counterStart(counter, FSL_COUNTER_ID);
        i = RUN_MODULE();
	
		// Stop counting the elapsed cycles for the current reaction.
		counterStop(FSL_COUNTER_ID);
		counterRead(counter, FSL_COUNTER_ID);
		counterDifference(counter);
		counterMaximum(counter);
		counterMinimum(counter);
		counterAccumulate(counter);
		    
        if (!i) {
        	stop = 1;
        }
        
        cycle++;
    	xil_printf("Time taken = %d clock cycles\nBCRT = %d\nWCRT = %d\ncycle = %d\n\n", counter.difference, counter.min, counter.max, cycle);
		counterReset(counter);
    }

    xil_printf("Total time taken = %d clock cycles\n", counter.total);

    asm volatile (".long 0x80000001\n");
    return 0;
}
