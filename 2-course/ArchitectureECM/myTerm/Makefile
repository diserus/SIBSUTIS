CC = gcc
CFLAGS = -Wall -Wextra -I../include
LIB = libmyTerm.a

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB)

.PHONY: all clean