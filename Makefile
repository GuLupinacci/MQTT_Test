CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRCDIR = src
OBJDIR = out
BINDIR = bin
TESTDIR = test

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
TEST_SRC = $(wildcard $(TESTDIR)/*.c)
TEST_OBJ = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TEST_SRC))

TARGET = $(BINDIR)/app_system
TEST_TARGET = $(BINDIR)/tests

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJ) | $(BINDIR)
    $(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
    $(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): $(OBJ) $(TEST_OBJ) | $(BINDIR)
    $(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.c | $(OBJDIR)
    $(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_TARGET)
    ./$(TEST_TARGET)

clean:
    rm -rf $(OBJDIR) $(BINDIR)