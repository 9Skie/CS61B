#include "CapersRepository.hpp"
#include "gitlet/GitletException.hpp"
#include "gitlet/Utils.hpp"

namespace capers {
void CapersRepository::setupPersistence() {
    // TODO: create .capers and any required files/directories if missing.
    throw gitlet::NotImplemented("CapersRepository::setupPersistence");
}

void CapersRepository::writeStory(const std::string& /*text*/) {
    // TODO: append text + newline to the story on disk and print the whole story.
    throw gitlet::NotImplemented("CapersRepository::writeStory");
}

void CapersRepository::makeDog(const std::string& /*name*/,
                               const std::string& /*breed*/, int /*age*/) {
    // TODO: construct, save, and print the dog.
    throw gitlet::NotImplemented("CapersRepository::makeDog");
}

void CapersRepository::celebrateBirthday(const std::string& /*name*/) {
    // TODO: load, celebrate, and persist the updated dog.
    throw gitlet::NotImplemented("CapersRepository::celebrateBirthday");
}
}
