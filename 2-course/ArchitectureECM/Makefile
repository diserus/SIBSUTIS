CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -LmySimpleComputer -LmyTerm -LmyBigChars -LmyReadKey -lmySimpleComputer -lmyTerm -lmyBigChars -lmyReadKey 

SUBDIRS = mySimpleComputer myTerm myBigChars myReadKey 

# Font utility definitions
FONT_UTIL_EXEC = font_util.exe
FONT_UTIL_SRC = console/font.c
FONT_UTIL_OBJ = $(FONT_UTIL_SRC:.c=.o)

# Console application definitions (excluding font utility source)
CONSOLE_EXEC = console.exe
CONSOLE_SRC = $(filter-out $(FONT_UTIL_SRC), $(wildcard console/*.c))
CONSOLE_OBJ = $(CONSOLE_SRC:.c=.o)

# Simple Assembler definitions
SAT_EXEC = sat.exe
SAT_SRC = $(wildcard simpleassembler/*.c)
SAT_OBJ = $(SAT_SRC:.c=.o)

all: $(SUBDIRS) $(CONSOLE_EXEC) $(FONT_UTIL_EXEC) $(SAT_EXEC)

$(SUBDIRS):
	$(MAKE) -C $@

console/%.o: console/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(CONSOLE_EXEC): $(SUBDIRS) $(CONSOLE_OBJ)
	$(CC) $(CONSOLE_OBJ) -o $@ $(LDFLAGS)

$(FONT_UTIL_EXEC): $(SUBDIRS) $(FONT_UTIL_OBJ)
	$(CC) $(FONT_UTIL_OBJ) -o $@ $(LDFLAGS)

simpleassembler/%.o: simpleassembler/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SAT_EXEC): $(SUBDIRS) $(SAT_OBJ)
	$(CC) $(SAT_OBJ) -o $@ $(LDFLAGS)

run: all
	./$(FONT_UTIL_EXEC)
	./$(CONSOLE_EXEC)

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(MAKE) -C console clean
	rm -f $(CONSOLE_EXEC) $(FONT_UTIL_EXEC) $(SAT_EXEC) $(SAT_OBJ)

# Ensure all libraries are built before the console and assembler
.PHONY: all clean run $(FONT_UTIL_EXEC) $(SAT_EXEC) $(SUBDIRS)