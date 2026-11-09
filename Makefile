all:
	gcc -ggdb -O0 -fsanitize=address,undefined -fno-omit-frame-pointer -Wall -Wextra -Wpedantic cgol.c -o cgol
