include ../../3\ Labs/support/Graphics.mk
SUPPORT = ../../3 Labs/support
CPPFLAGS += -I"$(SUPPORT)" -I. $(GRAPHICS_CFLAGS)
PROGRAMS = Main DemoInputSource BYOWClient BoringWorldDemo RandomWorldDemo HexWorld MemoryGame
.PHONY: all test clean
all: dependencies $(addprefix build/,$(PROGRAMS)) build/BYOWServer.o
build/Draw.o: ../../3\ Labs/support/Draw.cpp ../../3\ Labs/support/Draw.hpp ../../3\ Labs/support/Support.hpp | dependencies
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c "$(SUPPORT)/Draw.cpp" -o $@
build/BYOWServer.o: byow/Networking/BYOWServer.cpp byow/Networking/BYOWServer.hpp byow/Networking/Socket.hpp | dependencies
	@mkdir -p build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c byow/Networking/BYOWServer.cpp -o $@
build/Main: byow/Core/Main.cpp byow/Core/Engine.hpp build/Draw.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/Draw.o $(GRAPHICS_LIBS) -o $@
build/DemoInputSource: byow/InputDemo/DemoInputSource.cpp $(wildcard byow/InputDemo/*.hpp) build/Draw.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/Draw.o $(GRAPHICS_LIBS) -o $@
build/BYOWClient: byow/Networking/BYOWClient.cpp $(wildcard byow/Networking/*.hpp) build/Draw.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< build/Draw.o $(GRAPHICS_LIBS) -o $@
build/BoringWorldDemo: lab12\ -\ prereq/BoringWorldDemo.cpp build/Draw.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "lab12 - prereq/BoringWorldDemo.cpp" build/Draw.o $(GRAPHICS_LIBS) -o $@
build/RandomWorldDemo: lab12\ -\ prereq/RandomWorldDemo.cpp build/Draw.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "lab12 - prereq/RandomWorldDemo.cpp" build/Draw.o $(GRAPHICS_LIBS) -o $@
build/HexWorld: lab12\ -\ prereq/HexWorld.cpp lab12\ -\ prereq/HexWorld.hpp build/Draw.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "lab12 - prereq/HexWorld.cpp" build/Draw.o $(GRAPHICS_LIBS) -o $@
build/MemoryGame: lab13\ -\ prereq/MemoryGame.cpp lab13\ -\ prereq/MemoryGame.hpp build/Draw.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) "lab13 - prereq/MemoryGame.cpp" build/Draw.o $(GRAPHICS_LIBS) -o $@
test: all
	@echo "Implement the exercises, then use the interactive and input-string checks in Instructions.html."
clean:
	rm -rf build

$(addprefix build/,$(PROGRAMS)): $(wildcard byow/Core/*.hpp byow/TileEngine/*.hpp byow/InputDemo/*.hpp) ../../3\ Labs/support/Tiles.hpp ../../3\ Labs/support/RandomUtils.hpp ../../3\ Labs/support/Graphics.mk
