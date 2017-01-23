#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "barrier.h"

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
unsigned int sum_t0 = 0;
unsigned int sum_t1 = 0;
unsigned int sum_t2 = 0;
unsigned int sum_t3 = 0;

#define GRIDSIZE 128
int matrixA [GRIDSIZE][GRIDSIZE] = {{0}, {0}};
int matrixB [GRIDSIZE][GRIDSIZE] = {{0}, {0}};

volatile int threadCount = 2;	// Main function and housekeeping

// Barrier variable.
barrier_t barr;
barrier_t barr_parent;

// Threads
void *multiplyMatrix0(void *arg);
void *multiplyMatrix1(void *arg);
void *multiplyMatrix2(void *arg);
void *multiplyMatrix3(void *arg);
void *housekeeping(void *arg);

Info t0Info = {FALSE};
Info t1Info = {FALSE};
Info t2Info = {FALSE};
Info t3Info = {FALSE};

void combine(void);
void fillMatrix(void);

int main(void) {
	// Time the execution.
	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);

	// Initialise the barrier objects.
	barrier_init(&barr, NULL, threadCount);
	barrier_init(&barr_parent, NULL, 2);
	
	// Create a housekeeping thread that runs alongside the program.
	pthread_attr_t housekeeping_attr;
	pthread_attr_init(&housekeeping_attr);
	pthread_attr_setdetachstate(&housekeeping_attr, PTHREAD_CREATE_DETACHED);	// Run in a detached state.
	pthread_t housekeeping_thread;
	pthread_create(&housekeeping_thread, &housekeeping_attr, housekeeping, NULL);
	
	//===========================================
	//printf("threadCount: %d (including housekeeping)\n", threadCount);

	printf("Main 1\n");
	//delay();	// Delay to simulate other computations.

	fillMatrix();
	
	int repeat;
	for (repeat = 0; repeat < 10; ++repeat) {
		// par(t0, t1);
		t0Info.state = ALIVE;
		t1Info.state = ALIVE;
		t2Info.state = ALIVE;
		t3Info.state = ALIVE;
		threadCount = 1 + 4;	// Housekeeping thread and the two child threads.
		printf(" ");
		barrier_count(&barr, threadCount);
		// Set the pthread thread attributes.
		pthread_attr_t thread_attr;
		pthread_attr_init(&thread_attr);
		pthread_attr_setdetachstate(&housekeeping_attr, PTHREAD_CREATE_JOINABLE);	// Run in a joinable state.
		// Fork.
		pthread_t threads[4];
		pthread_create(&threads[0], &thread_attr, multiplyMatrix0, NULL);
		pthread_create(&threads[1], &thread_attr, multiplyMatrix1, NULL);
		pthread_create(&threads[2], &thread_attr, multiplyMatrix2, NULL);
		pthread_create(&threads[3], &thread_attr, multiplyMatrix3, NULL);
		// Join.
		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL);
		pthread_join(threads[2], NULL);
		pthread_join(threads[3], NULL);
		// Synchronise with the correct "phase" of the housekeeping thread.
		barrier_wait(&barr_parent);
		printf("Iteration: %d\n", repeat);
	}
	
	sum += sum_t0 + sum_t1 + sum_t2 + sum_t3;

	//printf(" main 2\n");
	//delay();	// Delay to simulate other computations.
	
	//printf("threadCount: %d (including housekeeping)\n", threadCount);

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

void *multiplyMatrix0(void *arg) {
	int i = 0;
	for(i = 0; i < 0.25*GRIDSIZE; i++) {
		int j = 0;
		for(j = 0; j < GRIDSIZE; j++) {
			sum_t0 += (matrixA[i][j])*(matrixB[j][i]);
			// pause;
			t0Info.state = PAUSED;
		//	barrier_wait(&barr); //Barrier at start of the housekeeping function
		//	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs
		}
	}

	// Thread terminates.
	t0Info.state = TERMINATED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	return NULL;
} 

void *multiplyMatrix1(void *arg) {
	int i = 0;
	for(i = 0.25*GRIDSIZE; i < 0.5*GRIDSIZE; i++) {
		int j = 0;
		for(j = 0; j < GRIDSIZE; j++) {
			sum_t1 += (matrixA[i][j])*(matrixB[j][i]);
			// pause;
			t1Info.state = PAUSED;
		//	barrier_wait(&barr); //Barrier at start of the housekeeping function
		//	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs
		}
	}

	// Thread terminates.
	t1Info.state = TERMINATED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	return NULL;
} 

void *multiplyMatrix2(void *arg) {
	int i = 0;
	for(i = 0.5*GRIDSIZE; i < 0.75*GRIDSIZE; i++) {
		int j = 0;
		for(j = 0; j < GRIDSIZE; j++) {
			sum_t2 += (matrixA[i][j])*(matrixB[j][i]);
			// pause;
			t2Info.state = PAUSED;
		//	barrier_wait(&barr); //Barrier at start of the housekeeping function
		//	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs
		}
	}

	// Thread terminates.
	t2Info.state = TERMINATED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	return NULL;
} 

void *multiplyMatrix3(void *arg) {
	int i = 0;
	for(i = 0.75*GRIDSIZE; i < GRIDSIZE; i++) {
		int j = 0;
		for(j = 0; j < GRIDSIZE; j++) {
			sum_t3 += (matrixA[i][j])*(matrixB[j][i]);
			// pause;
			t3Info.state = PAUSED;
		//	barrier_wait(&barr); //Barrier at start of the housekeeping function
		//	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs
		}
	}

	// Thread terminates.
	t3Info.state = TERMINATED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	return NULL;
} 

void *housekeeping(void *arg) {
	// Run while the main function hasn't terminated. When the main
	// function terminates, this detached thread will be automatically
	// terminated.
	while (1) {
		// Wait for each thread to pause.
		barrier_wait(&barr);
		
		// Decrement the threadCount if a thread has terminated.
		threadCount = threadCount - (t0Info.state == TERMINATED);
		threadCount = threadCount - (t1Info.state == TERMINATED);
		threadCount = threadCount - (t2Info.state == TERMINATED);
		threadCount = threadCount - (t3Info.state == TERMINATED);
		
		// Debug messages.
		/*if (t0Info.state != FALSE) {
			printf("  t0 %d\n", x);
		}
		if (t1Info.state != FALSE) {
			printf("  t1 %d\n", y);
		}*/
		
		// Check if this is the end of a global tick.
		if (t0Info.state == PAUSED || t1Info.state == PAUSED || t2Info.state == PAUSED || t3Info.state == PAUSED) {
			// Some threads have not terminated.
		//	printf("threadCount: %d (including housekeeping)\n", threadCount);
			
			// Combine local copies of shared variables.
			if (threadCount > 1) {
				combine();
			}
		} else {
		//	printf("threadCount: %d (including housekeeping)\n", threadCount);
			
			// All threads have terminated.
			threadCount = 1 + 1;	// Housekeeing and the parent thread.
		}
		
		// Update the thread states.
		if (t0Info.state == TERMINATED) {
			t0Info.state = FALSE;
		} else if (t0Info.state == PAUSED) {
			t0Info.state = ALIVE;
		}
		if (t1Info.state == TERMINATED) {
			t1Info.state = FALSE;
		} else if (t1Info.state == PAUSED) {
			t1Info.state = ALIVE;
		}
		if (t2Info.state == TERMINATED) {
			t2Info.state = FALSE;
		} else if (t2Info.state == PAUSED) {
			t2Info.state = ALIVE;
		}
		if (t3Info.state == TERMINATED) {
			t3Info.state = FALSE;
		} else if (t3Info.state == PAUSED) {
			t3Info.state = ALIVE;
		}
		
		// Update the barrier object with the updated thread count.
		barrier_count(&barr, threadCount);
		
		if (t0Info.state == ALIVE || t1Info.state == ALIVE || t2Info.state == ALIVE || t3Info.state == ALIVE) {
			// Let the remaining threads proceed to the next global tick.
			barrier_wait(&barr);
		} else {
			// All threads have terminated.
			// Let the parent thread proceed.
			barrier_wait(&barr_parent);
		}
	}
	
	return NULL;
}

void combine(void) {
	sum += sum_t0 + sum_t1 + sum_t2 + sum_t3;
	//printf("Sum: %d\n", sum);
}

void fillMatrix(void) {
	unsigned int seed = 10000;

	int i;
	for (i = 0; i < GRIDSIZE; i++) {
		int j;
		for (j = 0; j < GRIDSIZE; j++) {
			//matrixA[i][j] = 1 + (int) (MAXINT * (rand_r(&seed) / (RAND_MAX + 1.0)));
			//matrixB[i][j] = 1 + (int) (MAXINT * (rand_r(&seed) / (RAND_MAX + 1.0)));
			matrixA[i][j] = 2;
			matrixB[i][j] = 2;
		}
	}
}


