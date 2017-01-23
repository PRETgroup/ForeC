#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

typedef enum {
	FALSE = 0,
	TRUE = 1,
	
	ALIVE,
	PAUSED,
	SUSPENDED,
	TERMINATED
} Status;

typedef struct {
	int state;
} Info;

static const int MAXINT = 10000;
unsigned int sum = 0;

#define GRIDSIZE 128
int matrixA [GRIDSIZE][GRIDSIZE] = {{0}, {0}};
int matrixB [GRIDSIZE][GRIDSIZE] = {{0}, {0}};

volatile int threadCount = 5;	// Main function and housekeeping

// Barrier variable.
pthread_barrier_t barr;
pthread_barrier_t barr_parent;

// Threads
void multiplyMatrix0();
void multiplyMatrix1();
void multiplyMatrix2();
void multiplyMatrix3();
void fillMatrix(void);

int main(void) {
	// Time the execution.
	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	
	printf("Main 1\n");
	
	fillMatrix();
	
	#pragma omp parllel for shared(sum)
	{		
		int i;
		for(i=0;i<10;i++) {
			printf(" Iteration %d\n", i);
			multiplyMatrix0();
			multiplyMatrix1();
			multiplyMatrix2();
			multiplyMatrix3();
		//	printf("%d\n", sum);
		}
	}
	
	//===========================================
	gettimeofday(&endTime, 0);
	long seconds = endTime.tv_sec - startTime.tv_sec;
	int microseconds = endTime.tv_usec - startTime.tv_usec;
	if (microseconds < 0) {
		microseconds += 1000000;
		seconds--;
	}
	
	printf("Sum: %d\n", sum);
	printf("Runtime: %ld.%.6d\r\n", seconds, microseconds);
	return 0;
}

void multiplyMatrix0() {
	int i = 0;
	for(i = 0; i < 0.25*GRIDSIZE; i++) {
		int j = 0;
		for(j = 0; j < GRIDSIZE; j++) {
			sum+= (matrixA[i][j])*(matrixB[j][i]);
		}
	}
} 

void multiplyMatrix1() {
	int i = 0;
	for(i = 0.25*GRIDSIZE; i < 0.5*GRIDSIZE; i++) {
		int j = 0;
		for(j = 0; j < GRIDSIZE; j++) {
			sum+= (matrixA[i][j])*(matrixB[j][i]);
		}
	}
} 

void multiplyMatrix2() {
	int i = 0;
	for(i = 0.5*GRIDSIZE; i < 0.75*GRIDSIZE; i++) {
		int j = 0;
		for(j = 0; j < GRIDSIZE; j++) {
			sum+= (matrixA[i][j])*(matrixB[j][i]);
		}
	}
} 

void multiplyMatrix3() {
	int i = 0;
	for(i = 0.75*GRIDSIZE; i < GRIDSIZE; i++) {
		int j = 0;
		for(j = 0; j < GRIDSIZE; j++) {
			sum+= (matrixA[i][j])*(matrixB[j][i]);
		}
	}
} 



void fillMatrix(void) {
	unsigned int seed = 10000;

	int i;
	for (i = 0; i < GRIDSIZE; i++) {
		int j;
		for (j = 0; j < GRIDSIZE; j++) {
			matrixA[i][j] = 2;
			matrixB[i][j] = 2;
		}
	}
}


