CXX := g++

CPPFLAGS := -Iinclude -Itests
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic
DEPFLAGS := -MMD -MP

TARGET := app
BUILD_DIR := build

SOURCES := main.cpp src/fifo.cpp tests/unit_test_fifo.cpp
OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

.PHONY: all run test clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: run

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)
