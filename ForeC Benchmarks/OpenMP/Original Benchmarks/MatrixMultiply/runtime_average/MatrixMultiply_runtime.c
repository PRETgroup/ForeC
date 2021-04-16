/*******************************************************************************
 * Copyright (c) 2008 International Business Machines Corp.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors:
 *    Ajith Ramanath            - initial API and implementation
 *    Radhakrishnan Thangamuthu - initial API and implementation
 *    Mike Fulton               - initial API and implementation
 *******************************************************************************/
 
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

/* Monotonic system-wide clock.  */
#undef CLOCK_MONOTONIC
clockid_t CLOCK_MONOTONIC = 1;

static const int MAXINT = 10000;
static const int RANGE = 150;
static const int SIZE = 150 * 4;
static const int THREAD_COUNT = 16;
static const int REPEAT = 10;

int** matrixA;
int** matrixB;
int** matrixC;

void allocateMatrix(int*** matrix);
void fillMatrix(int*** matrix);
void multiplyMatrix(int*** matrixA, int*** matrixB, int*** matrixC, const int startIndex);



/*
 * Name    : run_multi_thread_test()
 * Desc    : Start method for a thread.
 * Args    : args - Thread arguments.
 * Returns : NULL
 */
int main(int argc, char *args[]) {
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

		//printf("Initialising matrices\n");
	
		allocateMatrix(&matrixA);
		allocateMatrix(&matrixB);
		allocateMatrix(&matrixC);
	
		fillMatrix(&matrixA);
		fillMatrix(&matrixB);
		fillMatrix(&matrixC);
	
		int i;
		for (i = 0; i < REPEAT; i++) {
			//printf("Iteration %d\n", i);
		
			/* matrix multiplication code here */
			multiplyMatrix(&matrixA, &matrixB, &matrixC, 0);
		}
	
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

void allocateMatrix(int*** matrix) {
	(*matrix) = (int**)malloc(SIZE * sizeof(int*));
	
	int i;
	for (i = 0; i < SIZE; i++) {
		(*matrix)[i] = (int*)malloc(SIZE * sizeof(int));
	}
}

void fillMatrix(int*** matrix) {
	unsigned int seed = 10000;
	
	int i;
	for (i = 0; i < SIZE; i++) {
		
		int j;
		for (j = 0; j < SIZE; j++) {
			(*matrix)[i][j] = 1 + (int) (MAXINT * (rand_r(&seed) / (RAND_MAX + 1.0)));
		}
	}
}

void multiplyMatrix(int*** matrixA, int*** matrixB, int*** matrixC, const int startIndex) {
	int i;
	for (i = startIndex; i < SIZE; i++) {
		
		int j;
		for (j = 0; j < SIZE; j++) {
			int sum = 0;
			
			int k;
			for (k = 0; k < SIZE; k++) {
				sum += (*matrixA)[i][k] * (*matrixB)[k][j];
			}
			
			(*matrixC)[i][j] = sum;
		}
	}
}
