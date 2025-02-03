CC = gcc
CFLAGS = -Wall -Iinclude
TARGET = ws
SRC_DIR = src
BUILD_DIR = bin
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/conn.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# compile src files in BUILD_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
