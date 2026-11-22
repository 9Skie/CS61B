#pragma once
#include "Support.hpp"
#include <filesystem>
namespace FileUtils {
using course::readFile;
using course::writeFile;
inline bool fileExists(const std::string &filename) {
    return std::filesystem::exists(filename);
}
} // namespace FileUtils
