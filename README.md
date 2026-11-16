# cgol

Conway's Game of Life written in C for funzies.

Starts with a pseudorandom square grid generated from the supplied seed and runs for `MAX_GENERATIONS` generations, updating once per second. `X` represents a live cell and `.` represents a dead cell.

## Configuration

Grid size and random seed are CLI arguments. Grid size must be between 1 and 1000.

`MAX_GENERATIONS` is defined in [`include/cgol.h`](include/cgol.h).

## Building

```sh
make cgol
```

## Running

```sh
./build/cgol 10 42
```

This runs a 10 x 10 grid with seed 42.

## Testing

```sh
make test
```

Tests include an empty grid, a single live cell, a 2x2 block in a corner, and a blinker over two generations.
