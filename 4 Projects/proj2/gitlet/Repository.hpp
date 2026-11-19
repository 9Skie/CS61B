#pragma once

#include <filesystem>

namespace gitlet {

// Represents a Gitlet repository. Author: TODO
// TODO: describe responsibilities and document each additional field.
class Repository {
public:
    Repository();

    // Working directory of this invocation, not the executable's directory.
    const std::filesystem::path CWD;
    // All persistent repository data belongs here.
    const std::filesystem::path GITLET_DIR;

    // TODO: design the command methods and your persistence helpers.
};

} // namespace gitlet
