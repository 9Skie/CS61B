#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <initializer_list>
#include <string>
#include <string_view>
#include <vector>

namespace gitlet::utils {

inline constexpr std::size_t UID_LENGTH = 40;

// SHA-1 of exact bytes, including embedded NULs; lowercase hexadecimal.
// Use for assignment object IDs, not passwords or security decisions.
std::string sha1(std::string_view bytes);
std::string sha1(std::initializer_list<std::string_view> pieces);

// std::string owns binary data as well as text. No encoding conversion occurs.
// These functions throw on I/O failure; writeContents does not create parents.
std::string readContents(const std::filesystem::path& file);
std::string readContentsAsString(const std::filesystem::path& file);
void writeContents(const std::filesystem::path& file, std::string_view bytes);
void writeContents(const std::filesystem::path& file,
                   std::initializer_list<std::string_view> pieces);

// Regular filenames in Java's UTF-16 lexicographic order; excludes directories.
// Throws for an invalid DIR or a filename that cannot be converted to UTF-16.
std::vector<std::string> plainFilenamesIn(const std::filesystem::path& dir);

// Only deletes a non-directory whose parent contains a .gitlet directory.
// Returns false if missing or a directory; throws if outside a repository root.
// This is a guard, not a replacement for the spec's untracked-file checks.
bool restrictedDelete(const std::filesystem::path& file);

// Join paths with std::filesystem::path's / operator, e.g. cwd / ".gitlet".

// Small, optional codec primitives. Define your own object field order.
// Integers: 8-byte unsigned big-endian. Strings: byte length, then exact bytes.
class BinaryWriter {
public:
    void writeUint64(std::uint64_t value);
    void writeString(std::string_view value);
    const std::string& bytes() const { return data_; }
private:
    std::string data_;
};

class BinaryReader {
public:
    // Owns its bytes, so it is safe to pass readContents(file) directly.
    explicit BinaryReader(std::string bytes);
    std::uint64_t readUint64();
    std::string readString();
    std::size_t remaining() const;
    void requireEnd() const;
private:
    std::string data_;
    std::size_t position_ = 0;
};

// Optional Java-style convenience functions. These do NOT inspect fields.
// T must implement std::string serialize() const and static T deserialize(...).
template <typename T>
std::string serialize(const T& object) { return object.serialize(); }

template <typename T>
void writeObject(const std::filesystem::path& file, const T& object) {
    writeContents(file, serialize(object));
}

template <typename T>
T readObject(const std::filesystem::path& file) {
    return T::deserialize(readContents(file));
}

} // namespace gitlet::utils
