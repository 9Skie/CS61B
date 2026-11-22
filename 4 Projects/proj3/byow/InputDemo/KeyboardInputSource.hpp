#pragma once
#include "InputSource.hpp"
#include "Draw.hpp"
class KeyboardInputSource : public InputSource {
    static constexpr bool PRINT_TYPED_KEYS = false;

  public:
    KeyboardInputSource() {
        Draw::clear(Color::WHITE);
        Draw::setPenColor(Color::BLACK);
        Draw::text(0.3, 0.3, "press m to moo, q to quit");
        Draw::show();
    }
    char getNextKey() override {
        while (Draw::isOpen()) {
            if (Draw::hasNextKeyTyped()) {
                char c = char(std::toupper(static_cast<unsigned char>(Draw::nextKeyTyped())));
                if (PRINT_TYPED_KEYS)
                    std::cout << c;
                return c;
            }
            Draw::pause(1);
        }
        return 'Q';
    }
    bool possibleNextInput() override {
        return Draw::isOpen();
    }
};
