include ../support/Graphics.mk
CPPFLAGS += -I../support -Isrc $(GRAPHICS_CFLAGS)
.PHONY: all test clean
all: dependencies build/GameOfLifeTests build/BoringWorldDemo build/RandomWorldDemo build/GameOfLife
build/Draw.o: ../support/Draw.cpp ../support/Draw.hpp ../support/Support.hpp | dependencies
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
build/GameOfLifeTests: tests/GameOfLifeTests.cpp build/Draw.o $(shell find src ../support -name "*.hpp")
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/Draw.o $(GRAPHICS_LIBS) -o $@
build/BoringWorldDemo: src/gameoflife/BoringWorldDemo.cpp build/Draw.o $(shell find src ../support -name "*.hpp")
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/Draw.o $(GRAPHICS_LIBS) -o $@
build/RandomWorldDemo: src/gameoflife/RandomWorldDemo.cpp build/Draw.o $(shell find src ../support -name "*.hpp")
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/Draw.o $(GRAPHICS_LIBS) -o $@
build/GameOfLife: src/gameoflife/GameOfLife.cpp build/Draw.o $(shell find src ../support -name "*.hpp")
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/Draw.o $(GRAPHICS_LIBS) -o $@
test: all
	./build/GameOfLifeTests
clean:
	rm -rf build

build/GameOfLife build/GameOfLifeTests build/BoringWorldDemo build/RandomWorldDemo: ../support/Graphics.mk
