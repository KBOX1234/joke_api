# Compiler
CXX := g++

# Detect OS
ifeq ($(OS),Windows_NT)
  LDFLAGS := -lws2_32 -lsodium
else
  LDFLAGS := -lsodium
endif

# Build mode (default = debug)
BUILD ?= debug

ifeq ($(BUILD),debug)
  CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -g
else ifeq ($(BUILD),release)
  CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -O2 -DNDEBUG
endif



# Project name (final executable)
TARGET := main

# Source and build directories (mode-specific obj dir to avoid clashes)
SRC_DIR := src
OBJ_DIR := obj/$(BUILD)

# Collect all .cpp files from src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Turn src/foo.cpp into obj/debug/foo.o or obj/release/foo.o
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default rule
all: $(TARGET)

# Link all objects into the final binary
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile each .cpp into .o inside obj/{debug,release}/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj/ dir if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Cleanup
clean:
	rm -rf obj $(TARGET)

.PHONY: all clean
