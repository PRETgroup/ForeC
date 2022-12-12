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

static const int MAXINT = 10000;
static const int RANGE = 150;
static const int SIZE = 150 * 4;
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
	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	//- - - -

	printf("Initialising matrices\n");
	
	allocateMatrix(&matrixA);
	allocateMatrix(&matrixB);
	allocateMatrix(&matrixC);
	
	fillMatrix(&matrixA);
	fillMatrix(&matrixB);
	fillMatrix(&matrixC);
	
	int i;
	for (i = 0; i < REPEAT; i++) {
		printf("Iteration %d\n", i);
		
		/* matrix multiplication code here */
		multiplyMatrix(&matrixA, &matrixB, &matrixC, 0);
	}
	
	//- - - -
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
