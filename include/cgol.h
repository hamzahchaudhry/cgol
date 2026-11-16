#ifndef CGOL_H
#define CGOL_H

void reset_grid(int *g, const int size);
void seed_grid(int *grid, const int size, const int seed);
void print_grid(const int *grid, const int size, const int generations);
void neighbours(int *ngrid, const int *grid, const int size);
void tick(int *ngrid, int *grid, const int size);

#endif
