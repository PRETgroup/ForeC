////////////////////////////////////////////
// ForeC Life
// Based on:
//   Copyright 2002, David Joiner and
//   The Shodor Education Foundation, Inc.
////////////////////////////////////////////

// Xilinx Microblaze
#include "stdlib.h"
#include "stdio.h"

// Hardware counter connected via a direct FSL bus.
#include "counter_dfsl.h"
Counter counter;
#define FSL_COUNTER_ID			2

int blackColor;

struct life_datum {
	int color;
	int x1;
	int y1;
};

struct life_datum life_data[96+2][24+2];

int grid[96+2][24+2];

int next_grid[96+2][24+2];

void initialise(void);
void randomize_grid(const float prob);
float rand_float(void);
void random_initByTime(void);

int main(int argc, char **argv) {
	// Initialise and start counting the elapsed cycles for each reaction.
	counterInitialise(counter);
	counterStart(counter, FSL_COUNTER_ID);

	int ncols = 96;
	int nrows = 6*4;

	int MAX_GENERATIONS = 2;
    int generation = 0;
    
    initialise();
    
	while (generation++ < MAX_GENERATIONS) {
		// left right and corners we get from neighboring grids.
		// copy left and right
		int i;
		for (i = 0; i <= nrows + 1; i++) {
			grid[0][i] = grid[1][i];
			grid[ncols+1][i] = grid[ncols][i];
		}

		// top and bottom we get from current cell.
		//copy top and bottom
		for (i = 1; i <= ncols; i++) {
			grid[i][0] = grid[i][nrows];
			grid[i][nrows+1] = grid[i][1];
		}
		
		// copy corners
		grid[0][0] = grid[0][nrows];
		grid[0][nrows+1] = grid[0][1];
		grid[ncols+1][0] = grid[ncols+1][nrows];
		grid[ncols+1][nrows+1] = grid[ncols+1][1];

		for (i = 1; i <= ncols; i++) {
			int j;
			for (j = 0; j <= 24; j++) {
				int neighbors = 0;

				// 3x3 neighbours
				int k;
				for (k = i-1; k <= i+1; k++)  {
					int l;
					for (l = j-1; l <= j+1; l++) {
						if (!(k == i && l==j) && grid[k][l] > 0) {
							neighbors++;
						}
					}
					if (neighbors > 3) {
						continue;
					}
				}

				if (neighbors < 2 || neighbors > 3) {
					next_grid[i][j] = 0;
				} else if (grid[i][j] > 0 || neighbors == 3) {
					next_grid[i][j] = grid[i][j]+1;
				}
			}
		}

		// apply next generation
		for (i = 0; i < ncols + 2; i++) {
			int j;
			for (j = 0; j <= 24; j++) {
				grid[i][j] = next_grid[i][j];
			}
		}
	}
	
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
	
	asm volatile (".long 0x80000001\r\n");
	return 0;
}

void initialise(void) {
	srand(0x0);
	randomize_grid(0.25);
}

void randomize_grid(const float prob) {
	int i;
    for (i = 1; i <= 96; i++) {
		int j;
		for (j = 0; j <= 24; j++) {
        	grid[i][j] = rand_float() < prob;
        }
    }
}

float rand_float(void) {
    return (float)rand()/(float)RAND_MAX;
}
