#pragma once
// Input-source demonstration by Josh Hug.
struct InputSource {
    virtual ~InputSource() = default;
    virtual char getNextKey() = 0;
    virtual bool possibleNextInput() = 0;
};
