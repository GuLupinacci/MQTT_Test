CC = gcc
WARNINGS= -Wall -Wextra 
CFLAGS = -Iinclude -Ipaho.mqtt.c/src

SRC_DIR = src
OUT_DIR = out
TEST_DIR = test

SRC = $(SRC_DIR)/*.c
TEST_SRC = $(TEST_DIR)/display/*.c

PROGRAM = $(OUT_DIR)/app_system
TEST_PROGRAM = $(OUT_DIR)/tests
LINKER= -lpaho-mqtt3c -ljson-c
LDFLAGS= -Lpaho.mqtt.c/build/src 

.PHONY: all clean test

all: $(PROGRAM)

$(PROGRAM): $(SRC) | $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@  $(LINKER) $(CFLAGS) $(LDFLAGS) $(WARNINGS)

$(TEST_PROGRAM): $(TEST_SRC) | $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

run: $(PROGRAM)
	LD_LIBRARY_PATH=paho.mqtt.c/build/src/  ./$(PROGRAM)

clean:
	rm -rf $(OUT_DIR)
