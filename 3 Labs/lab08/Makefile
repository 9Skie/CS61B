CXX ?= c++
CXXFLAGS ?= -std=c++17 -O0 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
CPPFLAGS += -I../support -Isrc
.PHONY: all test clean
all: build/InsertRandomSpeedTest build/BucketsSpeedTest build/InsertInOrderSpeedTest build/TestMyHashMap build/TestMyHashMapBuckets build/TestMyHashMapExtra
build/InsertRandomSpeedTest: tests/speed/InsertRandomSpeedTest.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/BucketsSpeedTest: tests/speed/BucketsSpeedTest.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/InsertInOrderSpeedTest: tests/speed/InsertInOrderSpeedTest.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/TestMyHashMap: tests/hashmap/TestMyHashMap.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/TestMyHashMapBuckets: tests/hashmap/TestMyHashMapBuckets.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
build/TestMyHashMapExtra: tests/hashmap/TestMyHashMapExtra.cpp $(shell find src tests ../support -name "*.hpp")
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
test: all
	@status=0; ./build/TestMyHashMap || status=1; ./build/TestMyHashMapBuckets || status=1; ./build/TestMyHashMapExtra || status=1; exit $$status
clean:
	rm -rf build
