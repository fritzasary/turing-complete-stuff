CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude -std=c++17 -g



SRC_DIR = src
INC_DIR = include
BUILD_DIR = build


SRCS = main.cpp $(SRC_DIR)/solve.cpp $(SRC_DIR)/tictacfour.cpp
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/solve.o $(BUILD_DIR)/tictacfour.o

# output executable name
TARGET = solve


# Default rule
all: $(TARGET)


$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@



# Compile source files into object files
$(BUILD_DIR)/main.o: main.cpp $(INC_DIR)/solve.h $(INC_DIR)/tictacfour.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

$(BUILD_DIR)/solve.o: $(SRC_DIR)/solve.cpp $(INC_DIR)/solve.h $(INC_DIR)/tictacfour.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/tictacfour.o: $(SRC_DIR)/tictacfour.cpp $(INC_DIR)/tictacfour.h $(INC_DIR)/game.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)
