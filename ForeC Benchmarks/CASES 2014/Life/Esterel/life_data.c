////////////////////////////////////////////
// MPI Life 0.9
// Copyright 2002, David Joiner and
//   The Shodor Education Foundation, Inc.
////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>

#include "life_data.h"

// defaults
int ncols;
int nrows;

char* _Grid_to_text(Grid *grid)
{
    return "Grid";
}

char* _GridMsg_to_text(GridMsg *msg)
{
    return "GridMsg";
}

void _GridMsg(GridMsg *left, GridMsg *right)
{
    int i;
    for (i = 0; i < nrows + 2; i++) {
        left->msg[i] = right->msg[i];
    }
}

double rand_float() {
    return (float) rand() / (float) RAND_MAX;
}

void initialize(int cols, int rows, int seed) {
    ncols = cols;
    nrows = rows;
    srand(seed);
}

void initialize_grid(Grid *grid)
{
    int i, j;
    for (i = 0; i < ncols + 2; i++) {
        for (j = 0; j < nrows + 2; j++) {
        	grid->grid[i][j] = rand_float() < 0.25;
        }
    }
}

void send(GridMsg* msg, Grid *grid, int pos)
{
    int i;
    for (i = 0; i < nrows + 2; i++) {
        msg->msg[i] = grid->grid[pos][i];
    }
}

void recv(GridMsg* msg, Grid *grid, int pos)
{
    int i;
    for (i = 0; i < nrows + 2; i++) {
        grid->grid[pos][i] = msg->msg[i];
    }
}

void compute(Grid *grid, Grid *next_grid)
{
    // copy corners
    grid->grid[0][0] = grid->grid[0][nrows];
    grid->grid[0][nrows+1] = grid->grid[0][1];
    grid->grid[ncols + 1][0] = grid->grid[ncols + 1][nrows];
    grid->grid[ncols + 1][nrows + 1] = grid->grid[ncols + 1][1];

    int i, j;
    //copy top and bottom
    for (i = 1; i <= ncols; i++) {
        grid->grid[i][0] = grid->grid[i][nrows];
        grid->grid[i][nrows + 1] = grid->grid[i][1];
    }

    //update
    for (i = 1; i <= ncols; i++) {
        for (j = 1; j <= nrows; j++) {
            int k, l;
            int neighbors = 0;
            for (k = i - 1; k <= i + 1; k++) {
                for (l = j - 1; l <= j + 1; l++) {
                    if (!(k == i && l == j) && grid->grid[k][l] > 0) {
                        neighbors++;
                    }
                }
                if (neighbors > 3) continue;
            }
            if (neighbors < 2 || neighbors > 3) {
                next_grid->grid[i][j] = 0;
            } else if (grid->grid[i][j] > 0 || neighbors == 3) {
                next_grid->grid[i][j] = grid->grid[i][j] + 1;
            }
        }
    }

    for (i = 0; i < ncols + 2; i++) {
        for (j = 0; j < nrows + 2; j++) {
            grid->grid[i][j] = next_grid->grid[i][j];
        }
    }
}
