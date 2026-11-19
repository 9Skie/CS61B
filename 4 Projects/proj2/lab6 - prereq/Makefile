CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -g -O0
LDFLAGS =
PYTHON = python3
TESTER_FLAGS =
SOURCES := $(wildcard capers/*.cpp)
HEADERS := $(wildcard capers/*.hpp) ../gitlet/Utils.hpp ../gitlet/GitletException.hpp
.PHONY: all default check clean
all: build/capers
default: all
build:
	mkdir -p build
build/capers: $(SOURCES) $(HEADERS) ../gitlet/Utils.cpp | build
	$(CXX) $(CXXFLAGS) -I.. $(SOURCES) ../gitlet/Utils.cpp $(LDFLAGS) -o "$@"
check: all
	$(MAKE) -C testing PYTHON="$(PYTHON)" TESTER_FLAGS="$(TESTER_FLAGS)" check
clean:
	rm -rf build
