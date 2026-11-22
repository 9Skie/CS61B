CXX ?= c++
CXXFLAGS ?= -std=c++17 -O0 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
CPPFLAGS += -I../support -Isrc
.PHONY: all test clean
all: build/InsertRandomSpeedTest build/TestBSTMapExtra build/TestBSTMap
build/InsertRandomSpeedTest: tests/InsertRandomSpeedTest.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/TestBSTMapExtra: tests/TestBSTMapExtra.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/TestBSTMap: tests/TestBSTMap.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
test: all
	@status=0; ./build/TestBSTMapExtra || status=1; ./build/TestBSTMap || status=1; exit $$status
clean:
	rm -rf build
