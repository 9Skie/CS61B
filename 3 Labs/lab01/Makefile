CXX ?= c++
CXXFLAGS ?= -std=c++17 -O0 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
CPPFLAGS += -I../support -Isrc
.PHONY: all test clean
all: build/ArithmeticTest build/Arithmetic
build/ArithmeticTest: tests/ArithmeticTest.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/Arithmetic: src/Arithmetic.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
test: all
	@status=0; ./build/ArithmeticTest || status=1; exit $$status
clean:
	rm -rf build
