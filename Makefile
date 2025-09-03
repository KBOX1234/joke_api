# Compiler
CXX := g++

# Detect OS
ifeq ($(OS),Windows_NT)
  CXXFLAGS += -I./libsodium-win64/include
  LDFLAGS  := -L./libsodium-win64/lib -lsodium -lws2_32
else
  LDFLAGS  := -lsodium
endif

# Build mode (default = debug)
BUILD ?= debug

ifeq ($(BUILD),debug)
  CXXFLAGS += -Wall -Wextra -std=c++17 -Iinclude -g
else ifeq ($(BUILD),release)
  CXXFLAGS += -Wall -Wextra -std=c++17 -Iinclude -O2 -DNDEBUG
endif

# Project name (final executable)
TARGET := main

# Source and build directories
SRC_DIR := src
OBJ_DIR := obj/$(BUILD)

# Collect sources/objects
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Default rule
all: $(TARGET)

# Link objects into final binary
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure obj dir exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Cleanup
clean:
	rm -rf obj $(TARGET)

.PHONY: all clean
