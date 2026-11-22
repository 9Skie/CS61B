CXX ?= c++
CXXFLAGS ?= -std=c++17 -O0 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
CPPFLAGS += -I../support -Isrc
.PHONY: all test clean
all: build/BombMain build/BombTest
build/BombMain: src/bomb/BombMain.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/BombTest: tests/bomb/BombTest.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
test: all
	@status=0; ./build/BombTest || status=1; exit $$status
clean:
	rm -rf build
