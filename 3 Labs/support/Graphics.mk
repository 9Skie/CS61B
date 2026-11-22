CXX ?= c++
CXXFLAGS ?= -std=c++17 -O0 -g -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
GRAPHICS_CFLAGS := $(shell pkg-config --cflags sdl3 freetype2 libpng)
GRAPHICS_LIBS := $(shell pkg-config --libs sdl3 freetype2 libpng)
.PHONY: dependencies
dependencies:
	@pkg-config --exists sdl3 freetype2 libpng || { echo 'Install SDL3, FreeType, libpng and pkg-config (see C++ setup instructions).'; exit 1; }
