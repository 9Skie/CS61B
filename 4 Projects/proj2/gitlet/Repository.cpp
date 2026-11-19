#include "Repository.hpp"

namespace gitlet {

Repository::Repository()
    : CWD(std::filesystem::current_path()), GITLET_DIR(CWD / ".gitlet") {}

// TODO: implement your repository operations here.

} // namespace gitlet
