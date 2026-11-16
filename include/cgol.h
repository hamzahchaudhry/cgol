#ifndef CGOL_H
#define CGOL_H

#define GRID_SIZE 10
#define MAX_GENERATIONS 10

void reset_grid(int *g);
void seed_grid(int *grid, int seed);
void print_grid(const int *grid, const int generations);
void neighbours(int *ngrid, const int *grid);
void tick(int *ngrid, int *grid);

#endif
