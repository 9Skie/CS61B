include ../support/Graphics.mk
CPPFLAGS += -I../support -Isrc $(GRAPHICS_CFLAGS)
.PHONY: all test clean
all: dependencies build/Tetris
build/Draw.o: ../support/Draw.cpp ../support/Draw.hpp ../support/Support.hpp | dependencies
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
build/Movement.o: src/tetris/Movement.cpp $(shell find src -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
build/Tetris: src/tetris/Tetris.cpp build/Draw.o build/Movement.o $(shell find src ../support -name "*.hpp")
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/Draw.o build/Movement.o $(GRAPHICS_LIBS) -o $@
test: all
	@echo "No tests were supplied for this lab. Follow the interactive checks in Instructions.html."
clean:
	rm -rf build

build/Tetris: ../support/Graphics.mk
