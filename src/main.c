#include "cgol.h"

#include <err.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    errx(EXIT_FAILURE, "usage: %s <size> <seed>.", argv[0]);
  }

  int size = atoi(argv[1]);
  if (size < 1 || size > 1000) {
    errx(EXIT_FAILURE, "Size must be between 1 and 1000.");
  }

  int *grid = malloc(size * size * sizeof(int));
  int *ngrid = malloc(size * size * sizeof(int));

  if (!grid) {
    err(EXIT_FAILURE, "Failed to allocate grid.");
  }

  if (!ngrid) {
    free(grid);
    err(EXIT_FAILURE, "Failed to allocate neighbour grid.");
  }

  int generations = 0;

  int seed = atoi(argv[2]);
  seed_grid(grid, size, seed);

  print_grid(grid, size, generations);
  sleep(1);

  for (int i = 0; i < MAX_GENERATIONS; ++i) {
    tick(ngrid, grid, size);
    ++generations;
    print_grid(grid, size, generations);
    sleep(1);
  }

  free(grid);
  free(ngrid);

  return 0;
}
