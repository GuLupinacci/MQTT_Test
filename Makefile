CC = gcc
WARNINGS= -Wall -Wextra 
CFLAGS = -Iinclude -Ipaho.mqtt.c/src

SRC_DIR = src
OUT_DIR = out
TEST_DIR = test

SRC = $(SRC_DIR)/*.c
LOOP = $(SRC_DIR)/mqtt_pub/*.c
TEST_SRC = $(TEST_DIR)/*/*.c

PROGRAM = $(OUT_DIR)/app_system
BROKER_PUB = $(OUT_DIR)/loop
TEST_PROGRAM = $(OUT_DIR)/tests
LINKER= -lpaho-mqtt3c -ljson-c lwiringPi -lwiringPiDev

define?= -D DISPLAY

LDFLAGS= -Lpaho.mqtt.c/build/src 

LD_PATH= LD_LIBRARY_PATH=paho.mqtt.c/build/src/

.PHONY: all clean test

all: $(PROGRAM) $(BROKER_PUB)

$(PROGRAM): $(SRC) | $(OUT_DIR)
	$(CC) $(CFLAGS) $(define) $^ -o $@  $(LINKER) $(CFLAGS) $(LDFLAGS) $(WARNINGS)

$(BROKER_PUB): $(LOOP) | $(OUT_DIR)
	$(CC) $(CFLAGS)  $^ -o $@  $(LINKER) $(CFLAGS) $(LDFLAGS) $(WARNINGS)

$(TEST_PROGRAM): $(TEST_SRC) | $(OUT_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

run: $(PROGRAM)
	$(LD_PATH) ./$(PROGRAM) & $(LD_PATH) ./$(BROKER_PUB)  


clean:
	rm -rf $(OUT_DIR)
