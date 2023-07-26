# Makefile for STM C++ project

# Directories
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin

# Compiler and compiler flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -O2

# Source file and target name
SRC := $(wildcard $(SRC_DIR)/*.cpp)
TARGET := $(BIN_DIR)/STM

# Object files
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ -lsqlite3

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR) $(BIN_DIR)

