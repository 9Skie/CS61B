CXX ?= c++
CXXFLAGS ?= -std=c++17 -O0 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
CPPFLAGS += -I../support -Isrc
.PHONY: all test clean
all: build/Puzzle build/AdventureGame build/PuzzleTest build/AdventureGameTests
build/Puzzle: src/puzzle/Puzzle.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/AdventureGame: src/adventure/AdventureGame.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/PuzzleTest: tests/puzzle/PuzzleTest.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/AdventureGameTests: tests/adventure/AdventureGameTests.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
test: all
	@status=0; ./build/PuzzleTest || status=1; ./build/AdventureGameTests || status=1; exit $$status
clean:
	rm -rf build
