CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Wpedantic
DEBUG_FLAGS = -Og -g3 -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all cgol debug test clean

all: cgol debug test

cgol: build/cgol

debug: build/cgol_debug

test: build/cgol_test
	./build/cgol_test

build/cgol: src/main.c src/cgol.c include/cgol.h Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -O2 $(filter %.c,$^) -o $@

build/cgol_debug: src/main.c src/cgol.c include/cgol.h Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(filter %.c,$^) -o $@

build/cgol_test: src/test.c src/cgol.c include/cgol.h Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(filter %.c,$^) -o $@

clean:
	rm -rf build
