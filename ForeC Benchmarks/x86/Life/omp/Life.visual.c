////////////////////////////////////////////
// MPI Life 0.9
// Copyright 2002, David Joiner and
//   The Shodor Education Foundation, Inc.
////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

#include <X11/Xlib.h> // Every Xlib program must include this
#include <assert.h>   // I include this to test return values the lazy way
#include <unistd.h>   // So we got the profile for 10 seconds

static const int FALSE = 0;
static const int TRUE = 1;

static const int PIXEL_SIZE = 4 - 1;
static const int RANGE = 25;
static const int ncols = 250;
static const int nrows = 25*4;
static const int LIFE_IMAGE_WIDTH = 250*4;
static const int LIFE_IMAGE_HEIGHT = 25*4*4;

static const int MAX_GENERATIONS = 1000;

void allocate_grid(const int ncols, const int nrows, int*** grid);
void cleanup_grid(const int ncols, const int nrows, int*** grid);
void randomize_grid(const int ncols, const int nrows, int*** grid, const double prob);
double rand_double(void);

void setupWindow(const int ncols, const int nrows);
void doDraw(const int ncols, const int nrows, int*** grid);
void do_step(const int ncols, const int nrows,int*** grid,int*** next_grid);

void random_initByTime(void);

int main(int argc, char* argv[]) {
	int procNumber = 1;
	if (argc == 2) {
		procNumber = *argv[1] - '0';
	}
    
	printf("Number of threads: %d\n", procNumber);
	omp_set_num_threads(procNumber);
    
	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	//- - - -

    random_initByTime();

    int** grid;
    int** next_grid;

    allocate_grid(ncols, nrows, &grid);
    allocate_grid(ncols, nrows, &next_grid);
    randomize_grid(ncols, nrows, &grid, 0.25);

	setupWindow(ncols, nrows);

    int done = FALSE;
    int generation = 0;
    while (!done) {
        if (generation++ > MAX_GENERATIONS) {
			done = TRUE;
		}
		
        // output
		doDraw(ncols, nrows, &grid);

        do_step(ncols, nrows, &grid, &next_grid);

		int i;
        #pragma omp parallel for
        for (i = 0; i < ncols+2; i++) {
			int j;
            for (j = 0; j < nrows+2; j++) {
                grid[i][j] = next_grid[i][j];
            }
        }
    }

    cleanup_grid(ncols, nrows, &grid);
    cleanup_grid(ncols, nrows, &next_grid);

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

void do_step(const int ncols, const int nrows, int*** grid, int*** next_grid) {
    // top and bottom we get from current cell.
    // left right and corners we get from neighboring grids.

	// copy left and right
	int i;
	#pragma omp parallel for
	for (i = 0; i <= nrows + 1; i++) {
		(*grid)[0][i] = (*grid)[1][i];
		(*grid)[ncols+1][i] = (*grid)[ncols][i];
	}

    // copy corners
	(*grid)[0][0] = (*grid)[0][nrows];
	(*grid)[0][nrows+1] = (*grid)[0][1];
	(*grid)[ncols+1][0] = (*grid)[ncols+1][nrows];
	(*grid)[ncols+1][nrows+1] = (*grid)[ncols+1][1];

	//copy top and bottom
	#pragma omp parallel for
	for (i = 1; i <= ncols; i++) {
		(*grid)[i][0] = (*grid)[i][nrows];
		(*grid)[i][nrows+1] = (*grid)[i][1];
	}


	//update
	#pragma omp parallel for
	for (i = 1; i <= ncols; i++) {
		int j;
		for (j = 1; j <= nrows; j++) {
			int neighbors = 0;

			int k;
			for (k = i-1; k <= i+1; k++) {

				int l;
				for (l = j-1; l <= j+1; l++) {
					if (!(k == i && l==j) && (*grid)[k][l] > 0) {
						neighbors++;
					}
				}
				if (neighbors > 3) {
					continue;
				}
			}
			if (neighbors < 2 || neighbors > 3) {
				(*next_grid)[i][j] = 0;
			} else if ((*grid)[i][j] > 0 || neighbors == 3) {
				(*next_grid)[i][j] = (*grid)[i][j]+1;
			}
		}
	}
}

void allocate_grid(const int ncols, const int nrows, int*** grid) {
    (*grid) = (int **)malloc((ncols+2) * sizeof(int*));

	int i;
	#pragma omp parallel for
	for (i = 0; i < ncols+2; i++) {
	(*grid)[i] = (int *)malloc((nrows+2) * sizeof(int));

		int j;
		for (j = 0; j < nrows+2; j++) {
	    (*grid)[i][j] = 0;
	}
	}
}

void cleanup_grid(const int ncols, const int nrows, int*** grid) {
	int i;
	#pragma omp parallel for
	for (i = 0; i < ncols+2; i++) {
	free((*grid)[i]);
	}

	free(*grid);
}

void randomize_grid(const int ncols, const int nrows, int*** grid, const double prob) {
	int i;
	#pragma omp parallel for
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

// X information, at some point this should be cleaned up so
// that it does not use global variables

// setupWindow modified from the tutorial on
// http://tronche.com/gui/x/xlib-tutorial/
// by Christophe Tronche


Display *dpy;
int blackColor;
int whiteColor;
Window w;
GC gc;
Pixmap buffer;
Colormap theColormap;
static const int numXGrayscale = 10;
XColor Xgrayscale[10];

void setupWindow(const int ncols, const int nrows) {
	// Open the display
	dpy = XOpenDisplay(NULL);
	assert(dpy);

	// Get some colors
	blackColor = BlackPixel(dpy, DefaultScreen(dpy));
	whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

	// Create the window
	w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, LIFE_IMAGE_WIDTH, LIFE_IMAGE_HEIGHT, 0, blackColor, blackColor);
	buffer = XCreatePixmap(dpy, DefaultRootWindow(dpy), LIFE_IMAGE_WIDTH, LIFE_IMAGE_HEIGHT, DefaultDepth(dpy, DefaultScreen(dpy)));

	theColormap = XCreateColormap(dpy, DefaultRootWindow(dpy), DefaultVisual(dpy, DefaultScreen(dpy)), AllocNone);

	int i;
    #pragma omp parallel for
	for (i = 0; i < numXGrayscale; i++) {
		int color = (int)((double)i*35535.0/(double)numXGrayscale) + 30000;
		Xgrayscale[i].red = color;
		Xgrayscale[i].green = color;
		Xgrayscale[i].blue = color;
		XAllocColor(dpy, theColormap, &(Xgrayscale[i]));
	}

	// We want to get MapNotify events
	XSelectInput(dpy, w, StructureNotifyMask);

	// "Map" the window (that is, make it appear on the screen)
	XMapWindow(dpy, w);

	// Create a "Graphics Context"
	gc = XCreateGC(dpy, w, 0, NULL);

	// Tell the GC we draw using the white color
	XSetForeground(dpy, gc, whiteColor);

	// Wait for the MapNotify event
	while(TRUE) {
	    XEvent e;
	    XNextEvent(dpy, &e);
	    if (e.type == MapNotify) {
			break;
		}
	}
}

void doDraw(const int ncols, const int nrows, int*** grid) {
    XSetForeground(dpy, gc, blackColor);
    XFillRectangle(dpy, buffer, gc, 0, 0, LIFE_IMAGE_WIDTH, LIFE_IMAGE_HEIGHT);

	int i;
	#pragma omp parallel for
	for (i = 1; i <= ncols; i++) {
		int x1 = (PIXEL_SIZE + 1) * (i-1);
		
		int j;
		for (j = 1; j <= nrows; j++) {
			int y1 = (PIXEL_SIZE + 1) * (j-1);
			
			if ((*grid)[i][j] > 0) {
				int life = (*grid)[i][j];
				if (life > numXGrayscale-1) {
					life = numXGrayscale-1;
				}
				XSetForeground(dpy, gc, Xgrayscale[life].pixel);
			} else {
				XSetForeground(dpy, gc, blackColor);
			}
			
			XFillRectangle(dpy, buffer, gc, x1, y1, PIXEL_SIZE, PIXEL_SIZE);
		}
	}

	XCopyArea(dpy, buffer, w, gc, 0, 0, LIFE_IMAGE_WIDTH, LIFE_IMAGE_HEIGHT, 0, 0);
	XFlush(dpy);
}



