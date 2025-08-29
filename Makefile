# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -g

# Project name (final executable)
TARGET := main

# Source and build directories
SRC_DIR := src
OBJ_DIR := obj

# Collect all .cpp files from src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Turn src/foo.cpp into obj/foo.o
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default rule
all: $(TARGET)

# Link all objects into the final binary
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Compile each .cpp into .o inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj/ dir if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Cleanup
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
