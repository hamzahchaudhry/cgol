#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 100
#define MAX_GENERATIONS 100

#define TEST 0

void seed_grid(int *grid);
void print_grid(const int *grid, const int generations);
int *neighbours(const int *grid);
void tick(int *grid);

void test_empty_grid(int *grid);
void test_one_live_cell(int *grid);
void test_block(int *grid);
void test_blinker(int *grid);

int main(void) {
  int generations = 0;
  int *grid = calloc(GRID_SIZE * GRID_SIZE, sizeof(int));

#if TEST
  test_empty_grid(grid);
  test_one_live_cell(grid);
  test_block(grid);
  test_blinker(grid);
  printf("Passed all tests.\n");
#else
  seed_grid(grid);
  print_grid(grid, generations);

  for (int i = 0; i < MAX_GENERATIONS; ++i) {
    tick(grid);
    ++generations;
    print_grid(grid, generations);
  }
#endif
  free(grid);
  return 0;
}

void test_init(int *grid) {
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      int cell = i * GRID_SIZE + j;
      grid[cell] = 0;
    }
  }
}

void test_empty_grid(int *grid) {
  test_init(grid);

  for (int i = 0; i < MAX_GENERATIONS; ++i) {
    tick(grid);

    for (int i = 0; i < GRID_SIZE; ++i) {
      for (int j = 0; j < GRID_SIZE; ++j) {
        int cell = i * GRID_SIZE + j;
        assert(grid[cell] == 0);
      }
    }
  }
}

void test_one_live_cell(int *grid) {
  test_init(grid);

  int live_cell = (GRID_SIZE / 2) * GRID_SIZE + (GRID_SIZE / 2);
  grid[live_cell] = 1;

  for (int i = 0; i < MAX_GENERATIONS; ++i) {
    tick(grid);

    for (int i = 0; i < GRID_SIZE; ++i) {
      for (int j = 0; j < GRID_SIZE; ++j) {
        int cell = i * GRID_SIZE + j;
        assert(grid[cell] == 0);
      }
    }
  }
}

void test_block(int *grid) {
  test_init(grid);

  int cell11 = (GRID_SIZE / 2) * GRID_SIZE + (GRID_SIZE / 2);
  int cell12 = (GRID_SIZE / 2) * GRID_SIZE + ((GRID_SIZE / 2) + 1);
  int cell21 = ((GRID_SIZE / 2) + 1) * GRID_SIZE + (GRID_SIZE / 2);
  int cell22 = ((GRID_SIZE / 2) + 1) * GRID_SIZE + ((GRID_SIZE / 2) + 1);

  grid[cell11] = 1;
  grid[cell12] = 1;
  grid[cell21] = 1;
  grid[cell22] = 1;

  for (int i = 0; i < MAX_GENERATIONS; ++i) {
    tick(grid);

    for (int i = 0; i < GRID_SIZE; ++i) {
      for (int j = 0; j < GRID_SIZE; ++j) {
        int cell = i * GRID_SIZE + j;
        if (cell == cell11 || cell == cell12 || cell == cell21 ||
            cell == cell22) {
          assert(grid[cell] == 1);
        } else {
          assert(grid[cell] == 0);
        }
      }
    }
  }
}

void test_blinker(int *grid) {
  test_init(grid);

  int cell_center = (GRID_SIZE / 2) * GRID_SIZE + (GRID_SIZE / 2);
  int cell_top = ((GRID_SIZE / 2) + 1) * GRID_SIZE + (GRID_SIZE / 2);
  int cell_bot = ((GRID_SIZE / 2) - 1) * GRID_SIZE + (GRID_SIZE / 2);
  int cell_right = (GRID_SIZE / 2) * GRID_SIZE + ((GRID_SIZE / 2) + 1);
  int cell_left = (GRID_SIZE / 2) * GRID_SIZE + ((GRID_SIZE / 2) - 1);

  grid[cell_center] = 1;
  grid[cell_left] = 1;
  grid[cell_right] = 1;

  tick(grid);

  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      int cell = i * GRID_SIZE + j;
      if (cell == cell_center || cell == cell_top || cell == cell_bot) {
        assert(grid[cell] == 1);
      } else {
        assert(grid[cell] == 0);
      }
    }
  }

  tick(grid);

  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      int cell = i * GRID_SIZE + j;
      if (cell == cell_center || cell == cell_left || cell == cell_right) {
        assert(grid[cell] == 1);
      } else {
        assert(grid[cell] == 0);
      }
    }
  }
}

void seed_grid(int *grid) {
  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      int cell = i * GRID_SIZE + j;
      assert(grid[cell] == 0 || grid[cell] == 1);
      grid[cell] = (rand() & 1) ? 1 : 0;
    }
  }
}

void print_grid(const int *grid, const int generations) {
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

// return grid of live neighbours per cell given a grid
// caller frees
int *neighbours(const int *grid) {
  int *ngrid = calloc(GRID_SIZE * GRID_SIZE, sizeof(int));

  if (!ngrid) {
    return NULL;
  }

  for (int i = 0; i < GRID_SIZE; ++i) {
    for (int j = 0; j < GRID_SIZE; ++j) {
      int cell = i * GRID_SIZE + j;
      assert(grid[cell] == 0 || grid[cell] == 1);

      if (((i - 1) >= 0) && ((j - 1) >= 0) && ((j + 1) < GRID_SIZE)) {
        ngrid[cell] += grid[(i - 1) * GRID_SIZE + (j - 1)];
        ngrid[cell] += grid[(i - 1) * GRID_SIZE + j];
        ngrid[cell] += grid[(i - 1) * GRID_SIZE + (j + 1)];
      }

      if (((j - 1) >= 0) && ((j + 1) < GRID_SIZE)) {
        ngrid[cell] += grid[i * GRID_SIZE + (j - 1)];
        ngrid[cell] += grid[i * GRID_SIZE + (j + 1)];
      }

      if (((i + 1) < GRID_SIZE) && ((j - 1) >= 0) && ((j + 1) < GRID_SIZE)) {
        ngrid[cell] += grid[(i + 1) * GRID_SIZE + (j - 1)];
        ngrid[cell] += grid[(i + 1) * GRID_SIZE + j];
        ngrid[cell] += grid[(i + 1) * GRID_SIZE + (j + 1)];
      }

      assert(ngrid[cell] >= 0 && ngrid[cell] <= 8);
    }
  }

  return ngrid;
}

void tick(int *grid) {
  int *ngrid = neighbours(grid);

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

  free(ngrid);
}
