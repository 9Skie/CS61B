#pragma once
#include <string>

namespace capers {
// Author: TODO. Choose the file location and serialization format yourself.
class Dog {
public:
    Dog(std::string name, std::string breed, int age);
    static Dog fromFile(const std::string& name);
    void saveDog() const;
    void haveBirthday();
    std::string toString() const;

    // TODO: optionally add serialize()/deserialize() for Utils' templates.
private:
    int age;
    std::string breed;
    std::string name;
};
}
