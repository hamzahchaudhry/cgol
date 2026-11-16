#include "cgol.h"

#include <assert.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void reset_grid(int *g) { memset(g, 0, GRID_SIZE * GRID_SIZE * sizeof(int)); }

void seed_grid(int *grid, int seed) {
  srand(seed);
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      int cell = i * GRID_SIZE + j;
      grid[cell] = (rand() & 1) ? 1 : 0;
    }
  }
}

void print_grid(const int *grid, const int generations) {
  if (system("clear") != 0) {
    err(EXIT_FAILURE, "Failed to clean terminal.\n");
  }

  if (generations == 0) {
    printf("Seed\n");
  } else {
    printf("Generation %d\n", generations);
  }

  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      int cell = i * GRID_SIZE + j;

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

void neighbours(int *ngrid, const int *grid) {
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      int cell = i * GRID_SIZE + j;
      assert(grid[cell] == 0 || grid[cell] == 1);

      ngrid[cell] = 0;

      for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
          if (di == 0 && dj == 0) {
            continue;
          }

          int row = i + di;
          int col = j + dj;

          if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
            ngrid[cell] += grid[row * GRID_SIZE + col];
          }
        }
      }

      assert(ngrid[cell] >= 0 && ngrid[cell] <= 8);
    }
  }
}

void tick(int *ngrid, int *grid) {
  neighbours(ngrid, grid);

  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      int cell = i * GRID_SIZE + j;
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
