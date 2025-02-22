CC=gcc

CFLAGS = -Wall -Wextra -std=c99 -fsanitize=address -ggdb3 -I/
LDFLAGS = -lm -fsanitize=address
LDIR =
LDLIBS=-lSDL2

SRC = $(wildcard *.c) $(wildcard *.cpp)

OBJ= $(SRC:.c=.o)
DEP= $(SRC:.c=.d)

all: main

main: $(OBJ)

clean:
		$(RM) $(OBJ) $(OBJ_TESTS) $(DEP) $(DEP_TESTS) main
