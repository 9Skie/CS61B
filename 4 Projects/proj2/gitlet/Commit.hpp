#pragma once

#include <string>

namespace gitlet {

// Represents a Gitlet commit. Author: TODO
class Commit {
private:
    // The message associated with this commit.
    std::string message;

    // TODO: choose the remaining fields, constructors, and public interface.
    // TODO: design deterministic serialization and deserialization.
    // Store references to persisted objects as IDs, never memory addresses.
};

} // namespace gitlet
