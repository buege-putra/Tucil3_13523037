# C++ specific variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall
DEBUGFLAGS = -g -O0
SRC_DIR = src
BIN_DIR = bin
TARGET = rush_hour

SRCS = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Build target
build: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(OBJS) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	@rm -rf $(BIN_DIR)/*

# Rebuild target (clean + build)
rebuild: clean build

# Run target
run: build
	./$(BIN_DIR)/$(TARGET) $(ARGS)

# Debug target
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(BIN_DIR)/$(TARGET)

.PHONY: build clean rebuild run debug

-include $(DEPS)
