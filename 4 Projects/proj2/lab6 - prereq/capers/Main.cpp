#include "CapersRepository.hpp"
#include "gitlet/GitletException.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <vector>

namespace {
void validateNumArgs(const std::vector<std::string>& args, std::size_t expected) {
    if (args.size() != expected) {
        throw gitlet::GitletException("Invalid number of arguments for: " + args[0] + ".");
    }
}
}

// Usage: capers story TEXT | dog NAME BREED AGE | birthday NAME
int main(int argc, char* argv[]) {
    try {
        const std::vector<std::string> args(argv + 1, argv + argc);
        if (args.empty()) throw gitlet::GitletException("Must have at least one argument");
        capers::CapersRepository repository;
        repository.setupPersistence();
        if (args[0] == "story") {
            validateNumArgs(args, 2);
            repository.writeStory(args[1]);
        } else if (args[0] == "dog") {
            validateNumArgs(args, 4);
            // TODO: convert age with std::stoi and call makeDog.
            throw gitlet::NotImplemented("dispatch the dog command");
        } else if (args[0] == "birthday") {
            validateNumArgs(args, 2);
            // TODO: call celebrateBirthday.
            throw gitlet::NotImplemented("dispatch the birthday command");
        } else {
            throw gitlet::GitletException("Unknown command: " + args[0]);
        }
        return 0;
    } catch (const gitlet::GitletException& error) {
        std::cout << error.what() << '\n';
        return 0;
    } catch (const gitlet::NotImplemented& error) {
        std::cerr << error.what() << '\n';
        return 2;
    } catch (const std::exception& error) {
        std::cerr << "Internal error: " << error.what() << '\n';
        return 1;
    }
}
