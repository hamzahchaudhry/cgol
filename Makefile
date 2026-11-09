all:
	gcc -O2 cgol.c -o cgol

debug:
	gcc -ggdb -O0 -fsanitize=address,undefined -fno-omit-frame-pointer -Wall -Wextra -Wpedantic cgol.c -o cgol_debug
