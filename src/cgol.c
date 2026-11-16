#include "cgol.h"

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void reset_grid(int *g, const int size) { memset(g, 0, size * size * sizeof(int)); }

void seed_grid(int *grid, const int size, const int seed) {
  srand(seed);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      int cell = i * size + j;
      grid[cell] = (rand() & 1) ? 1 : 0;
    }
  }
}

void print_grid(const int *grid, const int size, const int generations) {
  if (system("clear") != 0) {
    errx(EXIT_FAILURE, "Failed to clear terminal.");
  }

  if (generations == 0) {
    printf("Seed\n");
  } else {
    printf("Generation %d\n", generations);
  }

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      int cell = i * size + j;

      assert(grid[cell] == 0 || grid[cell] == 1);

      if (grid[cell]) {
        printf("X ");
      } else {
        printf(". ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

void neighbours(int *ngrid, const int *grid, const int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      int cell = i * size + j;
      assert(grid[cell] == 0 || grid[cell] == 1);

      ngrid[cell] = 0;

      for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
          if (di == 0 && dj == 0) {
            continue;
          }

          int row = i + di;
          int col = j + dj;

          if (row >= 0 && row < size && col >= 0 && col < size) {
            ngrid[cell] += grid[row * size + col];
          }
        }
      }

      assert(ngrid[cell] >= 0 && ngrid[cell] <= 8);
    }
  }
}

void tick(int *ngrid, int *grid, const int size) {
  neighbours(ngrid, grid, size);

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      int cell = i * size + j;
      assert(grid[cell] == 0 || grid[cell] == 1);
      int live = grid[cell];
      int n = ngrid[cell];

      if (live) {
        if (n < 2) {
          grid[cell] = 0;
        } else if (n > 3) {
          grid[cell] = 0;
        } else if (n == 2 || n == 3) {
          grid[cell] = 1;
        }
      } else {
        if (n == 3) {
          grid[cell] = 1;
        }
      }
    }
  }
}
