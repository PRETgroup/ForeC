#ifndef MATRIXMULTIPLY_DATA_H
#define MATRIXMULTIPLY_DATA_H

#define MAX_SIZE 80

typedef struct {
    int matrix[MAX_SIZE][MAX_SIZE];
} Matrix;

// void _Matrix(Matrix *left, Matrix *right);
void printOut(Matrix *matrix, int size);
void fillMatrix(Matrix *matrix, int threadId, int size);
void multiply(Matrix *left, Matrix *right, Matrix *result, int threadId, int size);

#endif
