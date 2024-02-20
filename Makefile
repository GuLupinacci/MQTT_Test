CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = src
OUT_DIR = out
TEST_DIR = test

SRC = $(SRC_DIR)/*.c
TEST_SRC = $(TEST_DIR)/display/*.c

PROGRAM = $(OUT_DIR)/app_system
TEST_PROGRAM = $(OUT_DIR)/tests

.PHONY: all clean test

all: $(PROGRAM)

$(PROGRAM): $(SRC) | $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_PROGRAM): $(TEST_SRC) | $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

clean:
	rm -rf $(OUT_DIR)
