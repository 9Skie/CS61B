#pragma once
#include "byow/TileEngine/TERenderer.hpp"
class Engine {
    TERenderer ter;

  public:
    static constexpr int WIDTH = 80, HEIGHT = 30;
    // TODO: Handle a fresh world, main menu and all keyboard inputs.
    void interactWithKeyboard() {}
    // Process input exactly as if typed, without opening a window.
    // Example: n123sss:q saves; lww then matches n123sssww.
    // ':q' saves and stops processing; 'l' restores the saved state.
    World interactWithInputString(const std::string &input) {
        // TODO: Run the engine from input and return the final tile grid.
        // See byow/InputDemo for interchangeable input sources.
        World finalWorldFrame;
        return finalWorldFrame;
    }
};
