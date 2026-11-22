#pragma once
#include "Bomb.hpp"
struct BombMain {
    static void answers(int phase = 2) {
        // TODO: Find the correct passwords using debugging techniques.
        Bomb b;
        if (phase >= 0)
            b.phase0("Figure this out. I wonder where the phases are defined...");
        if (phase >= 1)
            b.phase1(nullptr); // Figure this out too.
        if (phase >= 2)
            b.phase2("Figure this out. I wonder where the phases are defined...");
    }
};
