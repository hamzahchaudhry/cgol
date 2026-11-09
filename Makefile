CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
DEBUG_FLAGS = -Og -g3 -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all cgol debug test clean

all: cgol debug test

cgol: build/cgol

build/cgol: cgol.c Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -O2 -DTEST=0 $< -o $@

debug: build/cgol_debug

build/cgol_debug: cgol.c Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -DTEST=0 $< -o $@

test: build/cgol_test
	./build/cgol_test

build/cgol_test: cgol.c Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -DTEST=1 $< -o $@

clean:
	rm -rf build
