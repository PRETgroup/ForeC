//#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
//#include <unistd.h>
//#include <pthread.h>
//#include <err.h>

/* Monotonic system-wide clock.  */
#undef CLOCK_MONOTONIC
clockid_t CLOCK_MONOTONIC = 1;

/* Image size */
const int ASIZE = 1000;

#define MAX_ITER_VALUE	(1 << 14)
const int MAX_ITER = MAX_ITER_VALUE;
unsigned cols[MAX_ITER_VALUE + 1];

unsigned mandel_double(double cr, double ci);
void display_double(int size, double xmin, double xmax, double ymin, double ymax);

int main(void) {
	struct timespec ts_start;
	struct timespec ts_end;
	//- - - -

	int NUM_TO_AVERAGE;
	printf("Number of iterations to average: ");
	scanf("%d", &NUM_TO_AVERAGE);

	float summation = 0;
	int i;
	for(i = 0; i < NUM_TO_AVERAGE; i++) {

		clock_gettime(CLOCK_MONOTONIC, &ts_start);

		double xmin = -2;
		double xmax = 1.0;
		double ymin = -1.5;
		double ymax = 1.5;

		display_double(ASIZE, xmin, xmax, ymin, ymax);
	
		clock_gettime(CLOCK_MONOTONIC, &ts_end);

		long seconds = ts_end.tv_sec - ts_start.tv_sec;
		int nanoseconds = ts_end.tv_nsec - ts_start.tv_nsec;
		if(nanoseconds < 0) {
			nanoseconds += 1000000000;
			seconds--;
		}

		float microseconds = (float)nanoseconds/1000000000;
		float runtime = (float)seconds + microseconds;

		summation += runtime;

		printf("Runtime = %f \n", runtime);
		printf("------######--------\n");
	}
	
	float average = summation/NUM_TO_AVERAGE;
	printf("\nAverage runtime = %f\n\n", average);
	
	return 0;
}

/* The Inner Loop */
unsigned mandel_double(double cr, double ci) {
	double zr = cr, zi = ci;
	double tmp;
	
	unsigned i;
	
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
	for (y = 0; y < size; y++) {
		for (x = 0; x < size; x++) {
			cr = xmin + x * xscal;
			ci = ymin + y * yscal;
			
			counts = mandel_double(cr, ci);
		}
	}
}

