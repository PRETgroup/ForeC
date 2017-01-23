// Computes C = A*B, where A, B, and C are square matrices.

#include <stdio.h>

#include "MatrixMultiply_data.h"

#define NUMBER_OF_FILL_THREADS 4
#define NUMBER_OF_MULTIPLY_THREADS 8

void fillMatrix(Matrix *matrix, int threadId, int size) {
	int startRow = threadId * size / NUMBER_OF_FILL_THREADS;
	int range = size / NUMBER_OF_FILL_THREADS;

	int i;
	for (i = startRow; i < (startRow + range); i++) {

		int j;
		for (j = 0; j < size; j++) {
            matrix->matrix[i][j] = j;
		}
	}
}

void multiply(Matrix *left, Matrix *right, Matrix *result, int threadId, int size) {
	int startRow = threadId * size / NUMBER_OF_MULTIPLY_THREADS;
	int range = size / NUMBER_OF_MULTIPLY_THREADS;

	int i;
	for (i = startRow; i < (startRow + range); i++) {

		int j;
		for(j = 0; j < size; j++) {
            result->matrix[i][j] = 0;
			int k;
			for(k = 0; k < size; k++) {
                result->matrix[i][j] += left->matrix[i][k] * right->matrix[k][j];
			}
		}
	}
}

void printOut(Matrix* matrix, int size) {
	int i;
	for (i = 0; i < size; i++) {

		int j;
		for (j = 0; j < size; j++) {
			printf("%d ", matrix->matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

