CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
CPPFLAGS := -Iinclude -MMD -MP

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin
TARGET   := $(BIN_DIR)/programa

TEST_DIR := tests

SRCS	 := $(wildcard $(SRC_DIR)/*.cpp)
OBJS	 := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS	 := $(OBJS:.o=.d)

TEST_SRCS := $(wildcard $(TEST_DIR)/*.cpp)
LIB_SRCS  := $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))

TEST_TARGET := $(BIN_DIR)/testes

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

-include $(DEPS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(LIB_SRCS) $(TEST_SRCS) | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@