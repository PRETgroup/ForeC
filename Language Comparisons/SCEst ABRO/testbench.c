#include <stdio.h>

#include "ABRO.h"

static const int INPUT_SEQUENCE = 6;
static const int I[INPUT_SEQUENCE][3] = {
//	  A, B, R
	{ 1, 1, 0 },
	{ 1, 1, 0 },
	{ 0, 0, 0 },
	{ 1, 1, 0 },
	{ 1, 1, 1 },
	{ 1, 1, 0 }
};

int main(int argc, char **argv) {   
	// Reset the tick data
	TickData tickData;
	reset(&tickData);
	
	// Prepare the printing of I/O results
	printf("        A B R  O\n");

	for (int i = 0; i < INPUT_SEQUENCE; i++) {
		// Update the inputs
		tickData.A = I[i][0];
		tickData.B = I[i][1];
		tickData.R = I[i][2];
		
		// Perform one reaction
		tick(&tickData);
		
		// Print out the I/O of the reaction
		printf("Tick %d: %d %d %d  %d\n", 
			   i, 
			   tickData.A,
			   tickData.B,
			   tickData.R, 
			   tickData.O);
	}

	return 0;
}
