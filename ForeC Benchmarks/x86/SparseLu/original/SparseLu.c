/*
 * Copyright (c) 2008, BSC (Barcelon Supercomputing Center)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY BSC ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <sys/time.h>

#define BS_VALUE 64
#define NB_VALUE 64
static const int BS = BS_VALUE; 
static const int NB = NB_VALUE; 
static const int DOUBLES_PER_LINE = 15;
 
static const int FALSE = 0;
static const int TRUE = 1;

/* Debug control*/
static const int PRINT_VALUES = 0;

typedef double (*p_block_t)[BS_VALUE];

p_block_t A[NB_VALUE][NB_VALUE];
p_block_t origA[NB_VALUE][NB_VALUE];
p_block_t L[NB_VALUE][NB_VALUE];
p_block_t U[NB_VALUE][NB_VALUE];

p_block_t allocate_clean_block(void) {
	p_block_t p = (p_block_t)malloc(BS*BS*sizeof(double));
	if (p != NULL) {
		int i;
		for (i = 0; i < BS; i++) {
			int j;
			for (j = 0; j < BS; j++) {
				p[i][j] = 0.0; 
			}
		}
	} else {
		printf ("OUT OF MEMORY!!!!!!!!!!!!!!!\n");
		exit (-1);
	}
	
	return (p);
}

void print_pointer_structure(const char *s, const p_block_t A[NB][NB]) {	
	printf ("\nStructure for matrix %s\n", s);
	
	int ii;
	for (ii = 0; ii < NB; ii++) {
	
		int jj;
		for (jj = 0; jj < NB; jj++) {
			const p_block_t p =  A[ii][jj];
			
			if (p != NULL) {
				printf ("%p ", p);
			} else {
				printf ("     *      ");
			}
		}
		printf ("\n");
	}
}

void print_structure(const char *s, const p_block_t A[NB][NB]) {	
	printf ("\nStructure for matrix %s\n", s);
	
	int ii;
	for (ii = 0; ii < NB; ii++) {
	
		int jj;
		for (jj = 0; jj < NB; jj++) {
			const p_block_t p =  A[ii][jj];
			
			if (p != NULL) {
				printf ("x");
			} else {
				printf (" ");
			}
		}
		printf ("\n");
	}
}


void print_mat(const char *s, const p_block_t mat[NB][NB]) {
	if (PRINT_VALUES) {
		if (NB < 14) {
			print_pointer_structure (s, mat);
		} else {
			print_structure (s, mat);
		}
		
		printf ("values of matrix %s\n", s);
		
		int maxNB = NB;
		if (NB*BS > DOUBLES_PER_LINE) {
			maxNB = DOUBLES_PER_LINE/BS;
			printf ("very large matrix. Only printing %d blocks\n", maxNB);
		}
		
		int ii;
		for (ii = 0; ii < maxNB; ii++) {
		
			int i;
			for (i = 0; i < BS; i++) {
			
				int jj;
				for (jj = 0; jj < maxNB; jj++) {
					p_block_t p = mat[ii][jj];
					
					int j;
					for (j = 0; j < BS; j++) {
						if (p != NULL) {
							printf ("%.6f ", p[i][j]);
						} else {
							printf ("%.6f ", 0.0);
						}
					}              
				}
				printf ("\n");
			}
		}
	}
}

void genmat(void) {
	int null_entry;
	long int init_val = 1325;
	
	/* structure */
	int ii;
	for (ii = 0; ii < NB; ii++) {
	
		int jj;
		for (jj = 0; jj < NB; jj++) {
			null_entry = FALSE;
			
			if ((ii < jj) && (ii%3 != 0)) {
				null_entry = TRUE;
			}
			
			if ((ii > jj) && (jj%3 != 0)) {
				null_entry = TRUE;
			}
			
			if (ii%2 == 1) {
				null_entry = TRUE;
			}
			
			if (jj%2 == 1) {
				null_entry = TRUE;
			}
			
			if (ii == jj) {
				null_entry = FALSE;
			}
			
			if (ii == (jj-1)) {
				null_entry = FALSE;
			}
			
			if ((ii-1) == jj) {
				null_entry = FALSE; 
			}
			
			if (null_entry == FALSE) {
				A[ii][jj] = allocate_clean_block();
				if (A[ii][jj] == NULL) {
					printf("Out of memory\n");
					exit(1);
				}
			} else {
				A[ii][jj] = NULL;
			}
		}
	}
	
	/* Initialization */ /* preguntar Cela valores razonable */
	for (ii = 0; ii < NB; ii++) {
		int jj;
		for (jj = 0; jj < NB; jj++) {
			p_block_t p = A[ii][jj];
			
			if (p != NULL) {
				int i;
				for (i = 0; i < BS; i++) {
				
					int j;
					for (j = 0; j < BS; j++) {
						init_val = (3125 * init_val) % 65536;
						p[i][j] = 0.0001;
						
						if (ii == jj) {
							if (i == j) {
								p[i][j] = -20000;
							}
							
							if (((i-1) == j) || (i == (j-1))) {
								p[i][j] = 10000;
							}
						}
					}
				}
			}
		}
	}
}

void are_blocks_equal(const p_block_t ref_block, const p_block_t to_comp, double *mse) {
	*mse = 0.0;
	
	int i;
	for (i = 0; i < BS; i++) {
	
		int j;
		for (j = 0; j < BS; j++) {
			const double diff = ref_block[i][j] - to_comp[i][j];
			*mse += diff*diff;
		}
	}
}

void compare_mat(const p_block_t X[NB][NB], const p_block_t Y[NB][NB]) {
	double sq_error[NB][NB];
	int some_difference = FALSE;
	
	const p_block_t Zero_block = allocate_clean_block();
	
	int ii;
	for (ii = 0; ii < NB; ii++) {
	
		int jj;
		for (jj = 0; jj < NB; jj++) {
			if (X[ii][jj] == NULL) {
				if (Y[ii][jj] == NULL) {
					sq_error[ii][jj] = 0.0f;
				} else {
					are_blocks_equal(Zero_block, Y[ii][jj], &sq_error[ii][jj]);
				}
			} else {
				are_blocks_equal(X[ii][jj], Y[ii][jj], &sq_error[ii][jj]);
			}
		}
	}
	
	/* Alternative to put wait on */
	printf ("\nComparison of matrices at %p and %p\n", X, Y);
	for (ii = 0; ii < NB; ii++) {
	
		int jj;
		for (jj = 0; jj < NB; jj++) {
			if (sq_error[ii][jj] > 0.0000001L) {
				printf ("block [%d, %d]: detected mse = %.20lf\n", ii, jj, sq_error[ii][jj]);
				some_difference = TRUE;
				exit(1);
			}
		}
	}
	
	if (some_difference == FALSE) {
		printf ("matrices are identical\n");
	}
}

void lu0(p_block_t diag) {	
	int k;
	for (k = 0; k < BS; k++) {
		int i;
		for (i = k + 1; i < BS; i++) {
			diag[i][k] = diag[i][k] / diag[k][k];
			
			int j;
			for (j = k + 1; j < BS; j++) {
				diag[i][j] -= diag[i][k] * diag[k][j];
			}
		}
	}
	
}

void bdiv(const p_block_t diag, p_block_t row) {
	int i;
	for (i = 0; i < BS; i++) {
		
		int k;
		for (k = 0; k < BS; k++) {
			row[i][k] = row[i][k] / diag[k][k];
			
			int j;
			for (j = k + 1; j < BS; j++) {
				row[i][j] -= row[i][k]*diag[k][j];
			}
		}
	}
}

void bmod(const p_block_t row, const p_block_t col, p_block_t inner) {
	int i;
	for (i = 0; i < BS; i++) {
		
		int j;
		for (j = 0; j < BS; j++) {

			int k;
			for (k = 0; k < BS; k++) {
				inner[i][j] -= row[i][k]*col[k][j];
			}
		}
	}
}

void block_mpy_add(const p_block_t a, const p_block_t b, p_block_t c) {	
	int i;
	for (i = 0; i < BS; i++) {
		
		int j;
		for (j = 0; j < BS; j++) {
			
			int k;
			for (k = 0; k < BS; k++) {
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
}

void fwd(const p_block_t diag, p_block_t col) {
	int j;
	for (j = 0; j < BS; j++) {
		
		int k;
		for (k = 0; k < BS; k++) { 
			
			int i;
			for (i = k + 1; i < BS; i++) {
				col[i][j] -= diag[i][k]*col[k][j];
			}
		}
	}
}

void split_block(const p_block_t A, p_block_t L, p_block_t U) {
	int i;
	for (i = 0; i < BS; i++) {
		
		int j;
		for (j = 0; j < BS; j++) {
			if (i == j) {
				L[i][j] = 1.0;
				U[i][j] = A[i][j];
			} else if (i > j) {
				L[i][j] = A[i][j];
				U[i][j] = 0.0;
			} else {
				L[i][j] = 0.0;
				U[i][j] = A[i][j];
			}
		}
	}
}

void copy_block(const p_block_t Src, p_block_t Dst) {
	int i;
	for (i = 0; i < BS; i++) {
	
		int j;
		for (j = 0; j < BS; j++) { 
			Dst[i][j] = Src[i][j];
		}
	}
}

void clean_block(p_block_t Dst) {
	int i;
	for (i = 0; i < BS; i++) {
	
		int j;
		for (j = 0; j < BS; j++) {
			Dst[i][j] = 0.0;
		}
	}
}

void LU(p_block_t A[NB][NB]) {	
	int kk;
	for (kk = 0; kk < NB; kk++) {
		lu0(A[kk][kk]);
		
		int jj;
		for (jj = kk + 1; jj < NB; jj++) {
			if (A[kk][jj] != NULL) {
				fwd(A[kk][kk], A[kk][jj]);
			}
		}
		
		int ii;
		for (ii = kk + 1; ii < NB; ii++) {
			if (A[ii][kk] != NULL) {
				bdiv(A[kk][kk], A[ii][kk]);
			}
		}
		
		for (ii = kk + 1; ii < NB; ii++) {
			if (A[ii][kk] != NULL) {
				for (jj = kk + 1; jj < NB; jj++) {
					if (A[kk][jj] != NULL) {
						if (A[ii][jj] == NULL) {
							A[ii][jj] = allocate_clean_block();
						}
						bmod(A[ii][kk], A[kk][jj], A[ii][jj]);
					}
				}
			}
		}
	}
}

void split_mat(const p_block_t LU[NB][NB], p_block_t L[NB][NB], p_block_t U[NB][NB]) {
	p_block_t block;
	
	int ii;
	for (ii = 0; ii < NB; ii++) {

		int jj;
		for (jj = 0; jj < NB; jj++){
			if (ii == jj) {
				// split diagonal block
				L[ii][ii] = allocate_clean_block(); 
				U[ii][ii] = allocate_clean_block(); 
				split_block(LU[ii][ii], L[ii][ii], U[ii][ii]);
			} else {
				// copy non diagonal block to ...
				if (LU[ii][jj] != NULL) {
					block = allocate_clean_block(); 
					copy_block(LU[ii][jj], block);
				} else {
					block = NULL;
				}
				
				if (ii > jj) {
					// ...either L ...
					L[ii][jj] = block;
					U[ii][jj] = NULL;
				} else {
					// ... or U
					L[ii][jj] = NULL;
					U[ii][jj] = block;
				}
			}
		}
	}
}

void copy_mat(const p_block_t Src[NB][NB], p_block_t Dst[NB][NB]) {	
	int ii;
	for (ii = 0; ii < NB; ii++) {
		
		int jj;
		for (jj = 0; jj < NB; jj++) {
			if (Src[ii][jj] != NULL) {
				p_block_t block = allocate_clean_block();
				copy_block(Src[ii][jj], block);
				Dst[ii][jj] = block;
			} else {
				Dst[ii][jj] = NULL;
			}
		}
	}
}

void clean_mat(p_block_t Src[NB][NB]) {
	int ii;
	for (ii = 0; ii < NB; ii++) {
	
		int jj;
		for (jj = 0; jj < NB; jj++) {
			if (Src[ii][jj] != NULL) {
				clean_block(Src[ii][jj]);
			}
		}
	}
}

/* C = A*B */
void sparse_matmult(p_block_t A[NB][NB], p_block_t B[NB][NB], p_block_t C[NB][NB]) {
	int ii;
	for (ii = 0; ii < NB; ii++) {

		int jj;
		for (jj = 0; jj < NB; jj++) {

			int kk;
			for (kk = 0; kk < NB; kk++) {
				if ((A[ii][kk] != NULL) && (B[kk][jj] !=NULL )) {
					if (C[ii][jj] == NULL) {
						C[ii][jj] = allocate_clean_block();
					}
					block_mpy_add (A[ii][kk], B[kk][jj], C[ii][jj]);
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {
	struct timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	//- - - - -
	
	genmat();
	print_mat("A", (const p_block_t(*)[NB_VALUE])A);
	
	copy_mat((const p_block_t(*)[NB_VALUE])A, origA); 
	print_mat("reference A", (const p_block_t(*)[NB_VALUE])origA);
	
	LU(A);
	print_mat("A = LxU", (const p_block_t(*)[NB_VALUE])A);
	
	split_mat((const p_block_t(*)[NB_VALUE])A, L, U);
	print_mat("L", (const p_block_t(*)[NB_VALUE])L);
	print_mat("U", (const p_block_t(*)[NB_VALUE])U);
	
	clean_mat(A);
	print_mat("Zero A", (const p_block_t(*)[NB_VALUE])A);
	
	sparse_matmult(L, U, A); 
	print_mat("LxU", (const p_block_t(*)[NB_VALUE])A);
	compare_mat((const p_block_t(*)[NB_VALUE])origA, (const p_block_t(*)[NB_VALUE])A);
	
	//- - - - -
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

