//#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include<omp.h>
//#include <unistd.h>
//#include <pthread.h>
//#include <err.h>

/* Image size */
const int ASIZE = 1000;

#define MAX_ITER_VALUE	(1 << 14)
const int MAX_ITER = MAX_ITER_VALUE;
unsigned cols[MAX_ITER_VALUE + 1];

unsigned mandel_double(double cr, double ci);
void display_double(int size, double xmin, double xmax, double ymin, double ymax);

int main(void) {
    int procNumber = omp_get_max_threads();
    printf("Number of threads: %d\n", procNumber);
    omp_set_num_threads(procNumber);
    
    struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	//- - - -
	
	double xmin = -2;
	double xmax = 1.0;
	double ymin = -1.5;
	double ymax = 1.5;

	display_double(ASIZE, xmin, xmax, ymin, ymax);
	
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

/* The Inner Loop */
unsigned mandel_double(double cr, double ci) {
	double zr = cr, zi = ci;
	double tmp;
	
	unsigned i;
    // Cannot parallelise due to the sequential nature of updating zr for the next iteration.
	for (i = 0; i < MAX_ITER; i++)
	{
		tmp = zr * zr - zi * zi + cr;
		zi *= 2 * zr;
		zi += ci;
		zr = tmp;
		
		if (zr * zr + zi * zi > 4.0) break;
	}

	return i;
}

/* For each point, evaluate its colour */
void display_double(int size, double xmin, double xmax, double ymin, double ymax) {
	int x, y;
	
	double cr, ci;
	
	double xscal = (xmax - xmin) / size;
	double yscal = (ymax - ymin) / size;
	
	unsigned counts;
	#pragma omp parallel for firstprivate(xscal, yscal, xmin, ymin) private(y, x, cr, ci, counts)
	for (y = 0; y < size; y++) {
		for (x = 0; x < size; x++) {
			cr = xmin + x * xscal;
			ci = ymin + y * yscal;

			counts = mandel_double(cr, ci);
		}
	}
    counts = counts;
}

