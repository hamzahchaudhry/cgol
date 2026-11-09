# cgol

Conway's Game of Life written in C for funzies.

Starts with a random `GRID_SIZE` x `GRID_SIZE` grid and runs for `MAX_GENERATIONS` generations, updating once per second. `X` represents a live cell and `.` represents a dead cell.

## Configuration

`GRID_SIZE` and `MAX_GENERATIONS` are defined in [`cgol.c`](cgol.c).

## Building

```sh
make cgol
```

## Running

```sh
./build/cgol
```

## Testing

```sh
make test
```

Tests include an empty grid, a single live cell, a 2x2 block in a corner, and a blinker over two generations.
