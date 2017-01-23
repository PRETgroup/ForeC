// Computes C = A*B, where A, B, and C are square matrices.

// Hardware counter connected via a direct FSL bus.
#include "counter_dfsl.h"
Counter counter;
#define FSL_COUNTER_ID			2

#include <stdio.h>

int SIZE = 80;
int NumberOfFillThreads = 4;
int NumberOfMultiplyThreads = 8;

int A[80][80] = {{0}};
int B[80][80] = {{0}};
int C[80][80] = {{0}};

void fillMatrix(int (*A)[80][80], int threadId, int SIZE);
void multiply(int (*A)[80][80], int (*B)[80][80], int (*C)[80][80], int threadId, int SIZE);
void printOut(int (*A)[80][80], int SIZE);

int main(int argc, char **argv) {
	// Initialise and start counting the elapsed cycles for each reaction.
	counterInitialise(counter);
	counterStart(counter, FSL_COUNTER_ID);
	
	// Fill matrix A, one quarter at a time.
	fillMatrix(&A, 0, SIZE);
	fillMatrix(&A, 1, SIZE);
	fillMatrix(&A, 2, SIZE);
	fillMatrix(&A, 3, SIZE);
	
	// Fill matrix B, one quarter at a time.
	fillMatrix(&B, 0, SIZE);
	fillMatrix(&B, 1, SIZE);
	fillMatrix(&B, 2, SIZE);
	fillMatrix(&B, 3, SIZE);
	
	// Calculate the resultant matrix, one quarter at a time.
	multiply(&A, &B, &C, 0, SIZE);
	multiply(&A, &B, &C, 1, SIZE);
	multiply(&A, &B, &C, 2, SIZE);
	multiply(&A, &B, &C, 3, SIZE);
	multiply(&A, &B, &C, 4, SIZE);
	multiply(&A, &B, &C, 5, SIZE);
	multiply(&A, &B, &C, 6, SIZE);
	multiply(&A, &B, &C, 7, SIZE);
	
//	print(&A, SIZE);
//	print(&B, SIZE);
//	print(&C, SIZE);

	// Stop counting the elapsed cycles for the current reaction.
	counterStop(FSL_COUNTER_ID);
	counterRead(counter, FSL_COUNTER_ID);
	counterDifference(counter);
	counterMaximum(counter);
	counterMinimum(counter);
	counterAccumulate(counter);
	counterAverage(counter);
	xil_printf("Total time: %d cycles\r\n", counter.total);
	xil_printf("Program termination\r\n");
	
	asm volatile (".long 0x80000001\r\n");
	return 0;
}

void fillMatrix(int (*A)[80][80], int threadId, int SIZE) {
	int startRow = threadId * SIZE / NumberOfFillThreads;
	int range = SIZE / NumberOfFillThreads;
	
	int i;
	for (i = startRow; i < (startRow + range); i++) {
		
		int j;
		for (j = 0; j < SIZE; j++) {
			(*A)[i][j] = j;
		}
	}
}

void multiply(int (*A)[80][80], int (*B)[80][80], int (*C)[80][80], int threadId, int SIZE) {
	int startRow = threadId * SIZE / NumberOfMultiplyThreads;
	int range = SIZE / NumberOfMultiplyThreads;

	int i;
	for (i = startRow; i < (startRow + range); i++) {
	
		int j;
		for(j = 0; j < SIZE; j++) {
		
			(*C)[i][j] = 0;
			int k;
			for(k = 0; k < SIZE; k++) {
				(*C)[i][j] += (*A)[i][k] * (*B)[k][j];
			}
		}
	}
}

void printOut(int (*A)[80][80], int SIZE) {
	int i;
	for (i = 0; i < SIZE; i++) {
		
		int j;
		for (j = 0; j < SIZE; j++) {
			xil_printf("%d ", (*A)[i][j]);
		}
		xil_printf("\n");
	}
	xil_printf("\n");
}

