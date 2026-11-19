#include "Dog.hpp"
#include "gitlet/GitletException.hpp"
#include "gitlet/Utils.hpp"
#include <iostream>
#include <utility>

namespace capers {
Dog::Dog(std::string name, std::string breed, int age)
    : age(age), breed(std::move(breed)), name(std::move(name)) {}

Dog Dog::fromFile(const std::string& /*name*/) {
    // TODO: read bytes and reconstruct the fields; return a Dog by value.
    throw gitlet::NotImplemented("Dog::fromFile");
}

void Dog::saveDog() const {
    // TODO: encode the fields and save under .capers/dogs.
    throw gitlet::NotImplemented("Dog::saveDog");
}

void Dog::haveBirthday() {
    ++age;
    std::cout << toString() << "\nHappy birthday! Woof! Woof!\n";
}

std::string Dog::toString() const {
    return "Woof! My name is " + name + " and I am a " + breed
         + "! I am " + std::to_string(age) + " years old! Woof!";
}
}
