CC = gcc
CFLAGS = -Wall -Wextra -I../include
LDFLAGS = -L../mySimpleComputer -L../myTerm -L../myBigChars -L../myReadKey -L../mySimpleAssembler -lmySimpleComputer -lmyTerm -lmyBigChars -lmyReadKey -lmySimpleAssembler

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = ../console.exe

all: $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

.PHONY: all clean