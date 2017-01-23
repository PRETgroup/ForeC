////////////////////////////////////////////
// MPI Life 0.9
// Copyright 2002, David Joiner and
//   The Shodor Education Foundation, Inc.
////////////////////////////////////////////

#ifndef LIFE_DATA_H
#define LIFE_DATA_H

#define LIFE_IMAGE_WIDTH 500
#define LIFE_IMAGE_HEIGHT 500

#define NGRID 24

typedef struct {
    unsigned char grid[NGRID + 2][NGRID + 2];
} Grid;

typedef struct {
    unsigned char msg[NGRID + 2];
} GridMsg;

void _GridMsg(GridMsg *left, GridMsg *right);
double rand_float();
void initialize(int cols, int rows, int seed);
void initialize_grid(Grid *grid);
void send(GridMsg* msg, Grid *grid, int pos);
void recv(GridMsg* msg, Grid *grid, int pos);
void compute(Grid* grid, Grid *next_grid);
void do_step(int rank,int size,int ncols,int nrows,int ** grid,int ** next_grid);

#endif
