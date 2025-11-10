CXX = g++
CXXFLAGS = -g -O0 -Wall -std=c++17 -fPIC $(shell python3 -m pybind11 --includes) -Iinclude -Isrc -Itests
LDFLAGS = -lcrypto -lsqlite3
PY_LDFLAGS = $(shell python3-config --ldflags)

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build

# Common sources
SRCS = $(SRC_DIR)/utils.cpp $(SRC_DIR)/solve.cpp $(SRC_DIR)/tictacfour.cpp $(SRC_DIR)/tictacthree.cpp
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Targets
SOLVER_SO = solver$(shell python3-config --extension-suffix)
MAIN_EXE = solve
TEST_EXE = test_solver

.PHONY: all python native test clean

# Default: build everything
all: python native

# -------------------------
# Python extension module
# -------------------------
python: $(SOLVER_SO)

$(SOLVER_SO): $(SRCS) bindings.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -DBUILD_PYTHON -shared $(SRCS) bindings.cpp -o $(SOLVER_SO) $(LDFLAGS) $(PY_LDFLAGS)

# -------------------------
# Native C++ executable
# -------------------------
native: $(MAIN_EXE)

$(MAIN_EXE): $(OBJS) main.cpp
	$(CXX) $(CXXFLAGS) $(OBJS) main.cpp -o $(MAIN_EXE) $(LDFLAGS)

# Generic compile rule: .cpp -> build/.../.o
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -------------------------
# Unit Tests
# -------------------------
test: $(TEST_EXE)

$(TEST_EXE): $(BUILD_DIR)/src/utils.o $(BUILD_DIR)/src/solve.o $(BUILD_DIR)/src/tictacfour.o $(BUILD_DIR)/src/tictacthree.o
	$(CXX) -g -O0 -Wall -std=c++17 \
	-Iinclude \
	tests/catch_amalgamated.cpp tests/tt4_cases.cpp \
	$(BUILD_DIR)/src/utils.o $(BUILD_DIR)/src/solve.o $(BUILD_DIR)/src/tictacfour.o $(BUILD_DIR)/src/tictacthree.o \
	-o $(TEST_EXE) $(LDFLAGS)

# -------------------------
# Clean everything
# -------------------------
clean:
	rm -rf $(BUILD_DIR) $(SOLVER_SO) $(MAIN_EXE) $(TEST_EXE)
