#include "cgol.h"

#include <err.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    errx(EXIT_FAILURE, "usage: %s <seed>", argv[0]);
  }

  int *grid = malloc(GRID_SIZE * GRID_SIZE * sizeof(int));
  int *ngrid = malloc(GRID_SIZE * GRID_SIZE * sizeof(int));

  if (!grid) {
    err(EXIT_FAILURE, "Failed to allocate grid.\n");
  }

  if (!ngrid) {
    free(grid);
    err(EXIT_FAILURE, "Failed to allocate neighbour grid.\n");
  }

  int generations = 0;
  int seed = atoi(argv[1]);
  seed_grid(grid, seed);
  print_grid(grid, generations);
  sleep(1);

  for (int i = 0; i < MAX_GENERATIONS; ++i) {
    tick(ngrid, grid);
    ++generations;
    print_grid(grid, generations);
    sleep(1);
  }

  free(grid);
  free(ngrid);

  return 0;
}
