#include "cgol.h"

#include <assert.h>
#include <stdio.h>

static void test_empty_grid(int *ngrid, int *grid);
static void test_one_live_cell(int *ngrid, int *grid);
static void test_block(int *ngrid, int *grid);
static void test_blinker(int *ngrid, int *grid);

int main(void) {
  int grid[GRID_SIZE * GRID_SIZE];
  int ngrid[GRID_SIZE * GRID_SIZE];

  test_empty_grid(ngrid, grid);
  test_one_live_cell(ngrid, grid);
  test_block(ngrid, grid);
  test_blinker(ngrid, grid);
  puts("Passed all tests.");

  return 0;
}

static void test_empty_grid(int *ngrid, int *grid) {
  reset_grid(grid);

  for (int i = 0; i < MAX_GENERATIONS; ++i) {
    tick(ngrid, grid);

    for (int i = 0; i < GRID_SIZE; ++i) {
      for (int j = 0; j < GRID_SIZE; ++j) {
        int cell = i * GRID_SIZE + j;
        assert(grid[cell] == 0);
      }
    }
  }
}

static void test_one_live_cell(int *ngrid, int *grid) {
  reset_grid(grid);

  int live_cell = (GRID_SIZE / 2) * GRID_SIZE + (GRID_SIZE / 2);
  grid[live_cell] = 1;

  for (int i = 0; i < MAX_GENERATIONS; ++i) {
    tick(ngrid, grid);

    for (int i = 0; i < GRID_SIZE; ++i) {
      for (int j = 0; j < GRID_SIZE; ++j) {
        int cell = i * GRID_SIZE + j;
        assert(grid[cell] == 0);
      }
    }
  }
}

static void test_block(int *ngrid, int *grid) {
  reset_grid(grid);

  int cell00 = 0;
  int cell01 = 1;
  int cell10 = GRID_SIZE;
  int cell11 = GRID_SIZE + 1;

  grid[cell00] = 1;
  grid[cell01] = 1;
  grid[cell10] = 1;
  grid[cell11] = 1;

  for (int i = 0; i < MAX_GENERATIONS; ++i) {
    tick(ngrid, grid);

    for (int i = 0; i < GRID_SIZE; ++i) {
      for (int j = 0; j < GRID_SIZE; ++j) {
        int cell = i * GRID_SIZE + j;
        if (cell == cell00 || cell == cell01 || cell == cell10 ||
            cell == cell11) {
          assert(grid[cell] == 1);
        } else {
          assert(grid[cell] == 0);
        }
      }
    }
  }
}

static void test_blinker(int *ngrid, int *grid) {
  reset_grid(grid);

  int cell_center = (GRID_SIZE / 2) * GRID_SIZE + (GRID_SIZE / 2);
  int cell_top = ((GRID_SIZE / 2) + 1) * GRID_SIZE + (GRID_SIZE / 2);
  int cell_bot = ((GRID_SIZE / 2) - 1) * GRID_SIZE + (GRID_SIZE / 2);
  int cell_right = (GRID_SIZE / 2) * GRID_SIZE + ((GRID_SIZE / 2) + 1);
  int cell_left = (GRID_SIZE / 2) * GRID_SIZE + ((GRID_SIZE / 2) - 1);

  grid[cell_center] = 1;
  grid[cell_left] = 1;
  grid[cell_right] = 1;

  tick(ngrid, grid);

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

  tick(ngrid, grid);

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
