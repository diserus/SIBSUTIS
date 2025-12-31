BIN_DIR = bin

TARGET = $(BIN_DIR)/pwgen
TEST_TARGET = $(BIN_DIR)/main_test

CC = g++
TEST_CC = g++

CFLAGS = -Ithirdparty/
SRCDIR = src
OBJDIR = obj
TESTDIR = test

MAIN_SRCDIR = $(SRCDIR)/pwgen
LIB_SRCDIR = $(SRCDIR)/libpwgen
TEST_SRCDIR = $(TESTDIR)

OBJ_MAIN_DIR = $(OBJDIR)/src/pwgen
OBJ_LIB_DIR = $(OBJDIR)/src/libpwgen
OBJ_BIN_DIR = $(OBJDIR)/test

SRCS_MAIN = $(wildcard $(MAIN_SRCDIR)/*.cpp)
SRCS_LIB = $(wildcard $(LIB_SRCDIR)/*.cpp)
SRCS_TEST = $(wildcard $(TEST_SRCDIR)/*.cpp)

OBJS_MAIN = $(patsubst $(MAIN_SRCDIR)/%.cpp, $(OBJ_MAIN_DIR)/%.o, $(SRCS_MAIN))
OBJS_LIB = $(patsubst $(LIB_SRCDIR)/%.cpp, $(OBJ_LIB_DIR)/%.o, $(SRCS_LIB))
OBJS_TEST = $(patsubst $(TEST_SRCDIR)/%.cpp, $(OBJ_BIN_DIR)/%.o, $(SRCS_TEST))

DEPS = $(wildcard $(SRCDIR)/*.h)

all: $(TARGET)

$(TARGET): $(OBJS_MAIN) $(OBJS_LIB)
	$(CC) $(OBJS_MAIN) $(OBJS_LIB) -o $(TARGET) $(LDFLAGS)

$(OBJ_MAIN_DIR)/%.o: $(MAIN_SRCDIR)/%.cpp $(DEPS)
	$(CC) -c $< $(CFLAGS) -o $@

$(OBJ_LIB_DIR)/%.o: $(LIB_SRCDIR)/%.cpp $(DEPS)
	$(CC) -c $< $(CFLAGS) -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(OBJS_TEST) $(OBJS_LIB)
	$(TEST_CC) $(OBJS_TEST) $(OBJS_LIB) -o $(TEST_TARGET) $(LDFLAGS)

$(OBJ_BIN_DIR)/%.o: $(TEST_SRCDIR)/%.cpp $(DEPS)
	$(TEST_CC) -c $< $(CFLAGS) -o $@

run-test: test
	./$(TEST_TARGET)
run: all
	./$(TARGET)
clean:
	rm -f $(OBJS_MAIN) $(OBJS_LIB) $(OBJS_TEST) $(TARGET) $(TEST_TARGET)