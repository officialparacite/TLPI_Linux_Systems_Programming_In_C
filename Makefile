# Simple C Project Makefile

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS =

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/program

# Default target
all: directories $(EXECUTABLE)

# Create necessary directories
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Link object files to create the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean directories
