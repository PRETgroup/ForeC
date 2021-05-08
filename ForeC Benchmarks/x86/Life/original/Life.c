////////////////////////////////////////////
// MPI Life 0.9
// Copyright 2002, David Joiner and
//   The Shodor Education Foundation, Inc.
////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include <unistd.h>   // So we got the profile for 10 seconds

int blackColor;
int whiteColor;
static const int numXGrayscale = 10;

static const int FALSE = 0;
static const int TRUE = 1;

static const int PIXEL_SIZE = 4 - 1;
static const int RANGE = 25;
static const int ncols = 250;
static const int nrows = 25*4;
static const int LIFE_IMAGE_WIDTH = 250*4;
static const int LIFE_IMAGE_HEIGHT = 25*4*4;

static const int MAX_GENERATIONS = 10000;

struct life_datum {
	int color;
	int x1;
	int y1;
};

struct life_datum** life_data;
int** grid;
int** next_grid;
    
void initialise(const int ncols, const int nrows, int*** grid, int*** next_grid, struct life_datum*** life_data);
void allocate_grid(const int ncols, const int nrows, int*** grid);
void allocate_life_data(const int ncols, const int nrows, struct life_datum*** life_data);
void cleanup_grid(const int ncols, const int nrows, int*** grid);
void cleanup_life_data(const int ncols, const int nrows, struct life_datum*** life_data);
void randomize_grid(const int ncols, const int nrows, int*** grid, const double prob);
double rand_double(void);

void doDraw(void);
void do_step(void);

void random_initByTime(void);

int main(int argc, char* argv[]) {
	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	//- - - -

    random_initByTime();

	initialise(ncols, nrows, &grid, &next_grid, &life_data);

    int done = FALSE;
    int generation = 0;
    while (!done) {
        if (generation++ > MAX_GENERATIONS) {
			done = TRUE;
		}
		
        // output
		doDraw();

        do_step();

		int i;
        for (i = 0; i < ncols+2; i++) {
			int j;
            for (j = 0; j < nrows+2; j++) {
                grid[i][j] = next_grid[i][j];
            }
        }
    }

    cleanup_grid(ncols, nrows, &grid);
    cleanup_grid(ncols, nrows, &next_grid);
	cleanup_life_data(ncols, nrows, &life_data);

	//- - - -
	gettimeofday(&endTime,0);
	long seconds = endTime.tv_sec - startTime.tv_sec;
	int microseconds = endTime.tv_usec - startTime.tv_usec;
	if (microseconds < 0) {
		microseconds += 1000000;
		seconds--;
	}
	
	printf("Runtime: %ld.%.6d\r\n", seconds, microseconds);

	return 0;
}

void do_step(void) {
    // top and bottom we get from current cell.
    // left right and corners we get from neighboring grids.

	// copy left and right
	int i;
	for (i = 0; i <= nrows + 1; i++) {
		grid[0][i] = grid[1][i];
		grid[ncols+1][i] = grid[ncols][i];
	}

    // copy corners
	grid[0][0] = grid[0][nrows];
	grid[0][nrows+1] = grid[0][1];
	grid[ncols+1][0] = grid[ncols+1][nrows];
	grid[ncols+1][nrows+1] = grid[ncols+1][1];

	//copy top and bottom
	for (i = 1; i <= ncols; i++) {
		grid[i][0] = grid[i][nrows];
		grid[i][nrows+1] = grid[i][1];
	}


	//update
	for (i = 1; i <= ncols; i++) {
		int j;
		for (j = 1; j <= nrows; j++) {
			int neighbors = 0;

			int k;
			for (k = i-1; k <= i+1; k++) {

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
}

void initialise(const int ncols, const int nrows, int*** grid, int*** next_grid, struct life_datum*** life_data) {
	allocate_grid(ncols, nrows, grid);
	allocate_grid(ncols, nrows, next_grid);
	allocate_life_data(ncols, nrows, life_data);
	random_initByTime();
	randomize_grid(ncols, nrows, grid, 0.25);
}

void allocate_grid(const int ncols, const int nrows, int*** grid) {
    (*grid) = (int **)malloc((ncols+2) * sizeof(int*));

	int i;
    for (i = 0; i < ncols+2; i++) {
        (*grid)[i] = (int *)malloc((nrows+2) * sizeof(int));

		int j;
		for (j = 0; j < nrows+2; j++) {
            (*grid)[i][j] = 0;
        }
    }
}

void allocate_life_data(const int ncols, const int nrows, struct life_datum*** life_data) {
	(*life_data) = (struct life_datum**)malloc((ncols) * sizeof(struct life_datum*));
	
	int i;
	for (i = 0; i < ncols; i++) {
		(*life_data)[i] = (struct life_datum*)malloc((nrows) * sizeof(struct life_datum));
	}
}

void cleanup_grid(const int ncols, const int nrows, int*** grid) {
	int i;
    for (i = 0; i < ncols+2; i++) {
        free((*grid)[i]);
    }

    free(*grid);
}

void cleanup_life_data(const int ncols, const int nrows, struct life_datum*** life_data) {
	int i;
    for (i = 0; i < ncols; i++) {
        free((*life_data)[i]);
    }
	
    free(*life_data);
}

void randomize_grid(const int ncols, const int nrows, int*** grid, const double prob) {
	int i;
    for (i = 1; i <= ncols; i++) {
		int j;
		for (j = 1; j <= nrows; j++) {
            if (rand_double() < prob) {
                (*grid)[i][j] = 1;
            }
        }
    }
}

double rand_double(void) {
    return (double)rand()/(double)RAND_MAX;
}

void random_initByTime(void) {
    time_t ltime;

    time(&ltime);
    srand((unsigned) ltime);
}

void doDraw(void) {
	int i;
	for (i = 1; i <= ncols; i++) {
		int x1 = (PIXEL_SIZE + 1) * (i - 1);
		
		int j;
		for (j = 1; j <= nrows; j++) {
			int y1 = (PIXEL_SIZE + 1) * (j - 1);
			
			if (grid[i][j] > 0) {
				int life = grid[i][j];
				if (life > numXGrayscale-1) {
					life = numXGrayscale-1;
				}
				life_data[i-1][j-1].color = life;
			} else {
				life_data[i-1][j-1].color = blackColor;
			}
			
			life_data[i-1][j-1].x1 = x1;
			life_data[i-1][j-1].y1 = y1;
		}
	}
}


