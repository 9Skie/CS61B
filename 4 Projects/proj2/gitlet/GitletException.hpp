#pragma once

#include <stdexcept>
#include <string>

namespace gitlet {

// A specified user error. Main prints its message and exits normally.
class GitletException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Distinguishes unfinished exercises from legitimate Gitlet output.
class NotImplemented : public std::logic_error {
public:
    explicit NotImplemented(const std::string& task)
        : std::logic_error("TODO: " + task) {}
};

} // namespace gitlet
