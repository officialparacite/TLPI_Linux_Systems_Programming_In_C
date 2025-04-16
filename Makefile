# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./include -I./lib/include

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Final executable
TARGET = $(BUILD_DIR)/copy

# Default target
all: $(TARGET)

# Link object files to create the binary
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file to a .o file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

.PHONY: all clean
