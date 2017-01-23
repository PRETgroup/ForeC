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

unsigned int x = 0;
unsigned int y = 0;

volatile int threadCount = 2;	// Main function and housekeeping

// Barrier variable.
barrier_t barr;
barrier_t barr_parent;

// Threads
void *t0(void *arg);
void *t1(void *arg);
void *housekeeping(void *arg);

Info t0Info = {FALSE};
Info t1Info = {FALSE};

void combine(void);
void delay (void);

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
	printf("threadCount: %d (including housekeeping)\n", threadCount);

	printf(" main 1\n");
	delay();	// Delay to simulate other computations.

	while (1) {
		// par(t0, t1);
		t0Info.state = ALIVE;
		t1Info.state = ALIVE;
		threadCount = 1 + 2;	// Housekeeping thread and the two child threads.
		barrier_count(&barr, threadCount);
		// Set the pthread thread attributes.
		pthread_attr_t thread_attr;
		pthread_attr_init(&thread_attr);
		pthread_attr_setdetachstate(&housekeeping_attr, PTHREAD_CREATE_JOINABLE);	// Run in a joinable state.
		// Fork.
		pthread_t threads[2];
		pthread_create(&threads[0], &thread_attr, t0, NULL);
		pthread_create(&threads[1], &thread_attr, t1, NULL);
		// Join.
		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL);
		// Synchronise with the correct "phase" of the housekeeping thread.
		barrier_wait(&barr_parent);
	}

	printf(" main 2\n");
	delay();	// Delay to simulate other computations.
	
	printf("threadCount: %d (including housekeeping)\n", threadCount);


	//===========================================
	gettimeofday(&endTime, 0);
	long seconds = endTime.tv_sec - startTime.tv_sec;
	int microseconds = endTime.tv_usec - startTime.tv_usec;
	if (microseconds < 0) {
		microseconds += 1000000;
		seconds--;
	}
	
	printf("Runtime: %ld.%.6d\r\n", seconds, microseconds);
	return 0;
}

void *t0(void *arg) {
	x = 1;
	delay();	// Delay to simulate other computations.
	
	// pause;
	t0Info.state = PAUSED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs
	
	x = 2;
	delay();	// Delay to simulate other computations.
	
	// pause;
	t0Info.state = PAUSED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs

	x = 3;
	delay();	// Delay to simulate other computations.

	// pause;
	t0Info.state = PAUSED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs

	x = 4;
	delay();	// Delay to simulate other computations.

	// pause;
	t0Info.state = PAUSED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs

	x = 5;
	delay();	// Delay to simulate other computations.

	// Thread terminates.
	t0Info.state = TERMINATED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	return NULL;
} 

void *t1(void *arg) {
	y = 1;
	delay();	// Delay to simulate other computations.
	
	// pause;
	t1Info.state = PAUSED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs

	y = 2;
	delay();	// Delay to simulate other computations.
	
	// pause;
	t1Info.state = PAUSED;
	barrier_wait(&barr); //Barrier at start of the housekeeping function
	barrier_wait(&barr); //Barrier at end of HK function, threads wait while HK function runs

	y = 3;
	delay();	// Delay to simulate other computations.

	// Thread terminates.
	t1Info.state = TERMINATED;
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
		
		// Debug messages.
		if (t0Info.state != FALSE) {
			printf("  t0 %d\n", x);
		}
		if (t1Info.state != FALSE) {
			printf("  t1 %d\n", y);
		}
		
		// Check if this is the end of a global tick.
		if (t0Info.state == PAUSED || t1Info.state == PAUSED) {
			// Some threads have not terminated.
			printf("threadCount: %d (including housekeeping)\n", threadCount);
			
			// Combine local copies of shared variables.
			if (threadCount > 1) {
				combine();
			}
		} else {
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
		
		// Update the barrier object with the updated thread count.
		barrier_count(&barr, threadCount);
		
		if (t0Info.state == ALIVE || t1Info.state == ALIVE) {
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
	
}

void delay(void) {
	// Do a random amount of computation.
	int i = (rand() % 10) * 5000000;
	for (; i; --i);
}


