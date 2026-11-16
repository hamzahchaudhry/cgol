# cgol

Conway's Game of Life written in C for funzies.

Starts with a pseudorandom square grid generated from the supplied seed and runs for the supplied number of generations, updating once per second. `X` represents a live cell and `.` represents a dead cell.

## Configuration

Grid size, random seed, and generation count are CLI arguments, in that order. Grid size and generation count must each be between 1 and 1000.

## Building

```sh
make cgol
```

## Running

```sh
./build/cgol 10 42 10
```

This runs a 10 x 10 grid with seed 42 for 10 generations.

## Testing

```sh
make test
```

Tests include an empty grid, a single live cell, a 2x2 block in a corner, and a blinker over two generations.
