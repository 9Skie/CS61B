#pragma once
#include <filesystem>
#include <string>

namespace capers {
// Canine Capers persistence exercise. Author: TODO
class CapersRepository {
public:
    const std::filesystem::path CWD = std::filesystem::current_path();
    // TODO: define the metadata path, and document your directory layout.

    void setupPersistence();
    void writeStory(const std::string& text);
    void makeDog(const std::string& name, const std::string& breed, int age);
    void celebrateBirthday(const std::string& name);
};
}
