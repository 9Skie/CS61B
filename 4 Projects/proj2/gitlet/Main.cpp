#include "GitletException.hpp"
#include "Repository.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

// Driver for Gitlet. Author: TODO
// Usage: gitlet COMMAND OPERAND...
int main(int argc, char* argv[]) {
    try {
        // Unlike Java's args, argv[0] is the executable name. Exclude it.
        const std::vector<std::string> args(argv + 1, argv + argc);
        if (args.empty()) {
            throw gitlet::GitletException("Please enter a command.");
        }

        gitlet::Repository repository;
        if (args[0] == "init") {
            // TODO: validate operands, then call your repository method.
            throw gitlet::NotImplemented("implement init and its operand checks");
        } else if (args[0] == "add") {
            // TODO: validate operands/repository state, then stage the file.
            throw gitlet::NotImplemented("implement add and its operand checks");
        }
        // TODO: dispatch the remaining commands before this fallback.
        throw gitlet::GitletException("No command with that name exists.");
    } catch (const gitlet::GitletException& error) {
        std::cout << error.what() << '\n';
        return 0; // The assignment expects normal exit for specified errors.
    } catch (const gitlet::NotImplemented& error) {
        std::cerr << error.what() << '\n';
        return 2; // An unfinished exercise must not silently pass a test.
    } catch (const std::exception& error) {
        std::cerr << "Internal error: " << error.what() << '\n';
        return 1;
    }
}
