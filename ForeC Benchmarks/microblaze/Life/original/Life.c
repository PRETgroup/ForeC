////////////////////////////////////////////
// MPI Life 0.9
// Copyright 2002, David Joiner and
//   The Shodor Education Foundation, Inc.
////////////////////////////////////////////

// Xilinx Microblaze
#include "xparameters.h"

// Hardware counter connected via a direct FSL bus.
#include "counter_dfsl.h"
Counter counter;
#define FSL_COUNTER_ID				2

int rand_seed = 0;
int whiteColor;

int life_data_color[(10+2)*(12+2)];
int life_data_x1[(10+2)*(12+2)];
int life_data_y1[(10+2)*(12+2)];

int grid[(10+2)*(12+2)];
int next_grid[(10+2)*(12+2)];

void do_draw_init(void);
void do_step_init(void);

void do_step(int threadNumber);
void do_draw(int threadNumber);

float rand_float(void);

int freeze = 0;
int done = 0;

int main(int argc, char* argv[]) {
	// Initialise and start counting the elapsed cycles for each reaction.
	counterInitialise(counter);
	counterStart(counter, FSL_COUNTER_ID);
	//--------------------------------------------------------------

	int MAX_GENERATIONS = 10000;
	int ncols = 10;
	int nrows = 3*4;
	
	rand_seed = (rand_seed + 0) % 3;
	int i;
	for (i = 1; i <= ncols; i++) {
		int j;
		for (j = 1; j <= nrows; j++) {
			int index = i*ncols + j;
			int value = rand_float() < 0.25;
			grid[1] = value;
		}
	}
	
	freeze = 0;
	int generation = 0;
	do {
	//	xil_printf("Generation %d\r\n", generation);
		do_step_init();
		do_draw_init();
		
		// apply next generation
		int i;
		for (i = 0; i < ncols+2; i++) {
			int j;
			for (j = 0; j < nrows+2; j++) {
				int index = i*ncols + j;
				int datum = next_grid[1];
				grid[1] = datum;
			}
		}
		
		if (generation++ > MAX_GENERATIONS) {
			done = 1;
		}
		
		if (freeze) {
			done = 1;
		}
	} while (!done);


	//--------------------------------------------------------------
	// Stop counting the elapsed cycles for the current reaction.
	counterStop(FSL_COUNTER_ID);
	counterRead(counter, FSL_COUNTER_ID);
	counterDifference(counter);
	counterMaximum(counter);
	counterMinimum(counter);
	counterAccumulate(counter);
	counterAverage(counter);
	xil_printf("Total time: %d cycles\r\n", counter.total);
	xil_printf("Program termination\r\n");
	// forec:scheduler:counter:end
	
	asm volatile (".long 0x80000001\r\n");

	return 0;
}

void do_step_init(void) {
	int ncols = 10;
	int nrows = 3*4;
	
	// top and bottom we get from current cell.
	// left right and corners we get from neighboring grids.
	
	// copy left and right
	int i;
	for (i = 0; i <= nrows + 1; i++) {
		int index1 = ncols + i;
		int datum = grid[1];
		grid[1] = datum;
		int index2 = (ncols+1)*i;
		int index3 = ncols*i;
		datum = grid[1];
		grid[1] = datum;
	}
	
	//copy top and bottom
	for (i = 1; i <= ncols; i++) {
		int index1 = ncols*i;
		int index2 = ncols*i + nrows;
		int datum = grid[1];
		grid[1] = datum;
		int index3 = ncols*i + nrows+1;
		int index4 = ncols*i + 1;
		datum = grid[1];
		grid[1] = datum;
	}
	
	// copy corners
	int datum = grid[1];
	grid[1] = datum;
	int index1 = nrows+1;
	datum = grid[1];
	grid[1] = datum;
	int index2 = ncols*(ncols+1);
	int index3 = ncols*(ncols+1) + nrows;
	datum = grid[1];
	grid[1] = datum;
	int index4 = ncols*(ncols+1) + nrows+1;
	int index5 = ncols*(ncols+1) + 1;
	datum = grid[1];
	grid[1] = datum;
	
	//update
	do_step(0);
	do_step(1);
	do_step(2);
	do_step(3);
}

void do_step(int threadNumber) {
	int RANGE = 3;
	int ncols = 10;
	
	if (!freeze) {
		int startIndex = 1 + RANGE * threadNumber;
		int endIndex = RANGE * (threadNumber+1);
		
		int i;
		for (i = 1; i <= ncols; i++) {
			int j;
			for (j = startIndex; j <= endIndex; j++) {
				int neighbors = 0;
				
				// 3x3 neighbours
				int k;
				for (k = i-1; k <= i+1; k++)  {
					int l;
					for (l = j-1; l <= j+1; l++) {
					//	if (!(k == i && l==j) && (*grid_ptr)[k][l] > 0) {
							neighbors++;
					//	}
					}/*
					if (neighbors > 3) {
						continue;
					}*/
				}
				
				int index = ncols*i + j;
				next_grid[1] = 0;/*
				if (neighbors < 2 || neighbors > 3) {
					(*next_grid)[i][j] = 0;
				} else if ((*grid_ptr)[i][j] > 0 || neighbors == 3) {
					(*next_grid)[i][j] = (*grid_ptr)[i][j]+1;
				}*/
			}
		}
	}
}

void do_draw_init(void) {
	do_draw(0);
	do_draw(1);
	do_draw(2);
	do_draw(3);
}

void do_draw(int threadNumber) {
	int blackColor;
	int numXGrayscale = 10;
	int PIXEL_SIZE = 5 - 1;
	int ncols = 10;
	int RANGE = 3;
	
	if (!freeze) {
		int y1StartIndex = 1 + RANGE * threadNumber;
		int y1EndIndex = RANGE * (threadNumber+1);
		
		int i;
		for (i = 1; i <= ncols; i++) {
			int x1 = (PIXEL_SIZE + 1) * (i - 1);
			
			int j;
			for (j = y1StartIndex; j <= y1EndIndex; j++) {
				int index = ncols*i + j;
				int index1 = ncols*(i-1) + j-1;
				
				int y1 = (PIXEL_SIZE + 1) * (j - 1);
				
				life_data_color[1] = blackColor;
			//	if ((*grid)[i][j] > 0) {
					int life = grid[1];
					life = numXGrayscale - 1;
					life_data_color[1] = life;
			//	} else {
					life_data_color[1] = blackColor;
			//	}
				
				life_data_x1[1] = x1;
				life_data_y1[1] = y1;
			}
		}
	}
}

float rand_float(void) {
	return (float)1/(float)rand_seed;
}
