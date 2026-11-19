# C++17 Gitlet starter. All paths are relative, including paths with spaces.
CXX = c++
CPPFLAGS = -Igitlet
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -g -O0
LDFLAGS =
PYTHON = python3
TESTER_FLAGS =

SOURCES := $(filter-out gitlet/DumpObj.cpp,$(wildcard gitlet/*.cpp))
OBJECTS := $(patsubst gitlet/%.cpp,build/%.o,$(SOURCES))

.PHONY: all default check capers check-capers clean
all: build/gitlet build/dumpobj
default: all

build:
	mkdir -p build

build/%.o: gitlet/%.cpp | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c "$<" -o "$@"

build/gitlet: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o "$@"

build/dumpobj: build/DumpObj.o build/Utils.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o "$@"

# Assignment acceptance tests. These FAIL until you implement Gitlet.
check: all
	$(MAKE) -C testing PYTHON="$(PYTHON)" TESTER_FLAGS="$(TESTER_FLAGS)" check

capers:
	$(MAKE) -C "lab6 - prereq" CXX="$(CXX)" CXXFLAGS="$(CXXFLAGS)" LDFLAGS="$(LDFLAGS)"

check-capers: capers
	$(MAKE) -C "lab6 - prereq" PYTHON="$(PYTHON)" TESTER_FLAGS="$(TESTER_FLAGS)" check

# Only generated build files; never deletes .gitlet or student test directories.
clean:
	rm -rf build
	$(MAKE) -C "lab6 - prereq" clean

-include $(wildcard build/*.d)
