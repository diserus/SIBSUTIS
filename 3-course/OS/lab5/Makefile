CC = gcc
CFLAGS = -Wall -Wextra -g -fPIC
LDFLAGS = -shared

TARGET = liblist.so
SOURCES = list.c
OBJECTS = $(SOURCES:.c=.o)
MAIN = main
MAIN_SOURCE = main.c

.PHONY: all clean debug

all: $(TARGET) $(MAIN)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(MAIN): $(MAIN_SOURCE) $(TARGET)
	$(CC) $(CFLAGS) -o $@ $(MAIN_SOURCE) -ldl

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
run: all
	./$(MAIN)

clean:
	rm -f $(OBJECTS) $(TARGET) $(MAIN)

debug: CFLAGS += -g -O0
debug: clean all