#include "Utils.hpp"

#include <algorithm>
#include <array>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace gitlet::utils {
namespace {
std::uint32_t rotateLeft(std::uint32_t value, unsigned bits) {
    return (value << bits) | (value >> (32 - bits));
}
}

std::string sha1(std::string_view input) {
    std::vector<std::uint8_t> data(input.begin(), input.end());
    const auto bitLength = static_cast<std::uint64_t>(data.size()) * 8;
    data.push_back(0x80);
    while (data.size() % 64 != 56) data.push_back(0);
    for (int shift = 56; shift >= 0; shift -= 8) {
        data.push_back(static_cast<std::uint8_t>(bitLength >> shift));
    }
    std::array<std::uint32_t, 5> hash{
        0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0};
    for (std::size_t offset = 0; offset < data.size(); offset += 64) {
        std::array<std::uint32_t, 80> words{};
        for (std::size_t i = 0; i < 16; ++i) {
            for (std::size_t j = 0; j < 4; ++j) {
                words[i] = (words[i] << 8) | data[offset + 4 * i + j];
            }
        }
        for (std::size_t i = 16; i < 80; ++i) {
            words[i] = rotateLeft(words[i-3] ^ words[i-8] ^ words[i-14]
                                 ^ words[i-16], 1);
        }
        auto a = hash[0], b = hash[1], c = hash[2], d = hash[3], e = hash[4];
        for (std::size_t i = 0; i < 80; ++i) {
            std::uint32_t f, k;
            if (i < 20) {
                f = (b & c) | (~b & d); k = 0x5a827999;
            } else if (i < 40) {
                f = b ^ c ^ d; k = 0x6ed9eba1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d); k = 0x8f1bbcdc;
            } else {
                f = b ^ c ^ d; k = 0xca62c1d6;
            }
            const std::uint32_t temp = rotateLeft(a, 5) + f + e + k + words[i];
            e = d; d = c; c = rotateLeft(b, 30); b = a; a = temp;
        }
        hash[0] += a; hash[1] += b; hash[2] += c; hash[3] += d; hash[4] += e;
    }
    std::ostringstream out;
    out << std::hex << std::setfill('0');
    for (auto word : hash) out << std::setw(8) << word;
    return out.str();
}

std::string sha1(std::initializer_list<std::string_view> pieces) {
    std::string bytes;
    for (auto piece : pieces) bytes.append(piece);
    return sha1(bytes);
}

std::string readContents(const std::filesystem::path& file) {
    if (!std::filesystem::is_regular_file(file)) {
        throw std::runtime_error("Not a regular file: " + file.string());
    }
    std::ifstream in(file, std::ios::binary);
    if (!in) throw std::runtime_error("Cannot read: " + file.string());
    std::string bytes((std::istreambuf_iterator<char>(in)), {});
    if (in.bad()) throw std::runtime_error("Read failed: " + file.string());
    return bytes;
}

std::string readContentsAsString(const std::filesystem::path& file) {
    return readContents(file);
}

void writeContents(const std::filesystem::path& file, std::string_view bytes) {
    writeContents(file, {bytes});
}

void writeContents(const std::filesystem::path& file,
                   std::initializer_list<std::string_view> pieces) {
    std::ofstream out(file, std::ios::binary | std::ios::trunc);
    if (!out) throw std::runtime_error("Cannot write: " + file.string());
    for (auto piece : pieces) {
        if (!piece.empty()) {
            out.write(piece.data(), static_cast<std::streamsize>(piece.size()));
        }
    }
    out.close();
    if (!out) throw std::runtime_error("Write failed: " + file.string());
}

std::vector<std::string> plainFilenamesIn(const std::filesystem::path& dir) {
    std::vector<std::string> names;
    for (const auto& entry : std::filesystem::directory_iterator(dir)) {
        if (entry.is_regular_file()) names.push_back(entry.path().filename().string());
    }
    // Java's String.compareTo orders UTF-16 code units, not UTF-8 bytes.
    std::sort(names.begin(), names.end(), [](const auto& a, const auto& b) {
        return std::filesystem::path(a).u16string()
             < std::filesystem::path(b).u16string();
    });
    return names;
}

bool restrictedDelete(const std::filesystem::path& file) {
    const auto path = std::filesystem::absolute(file).lexically_normal();
    if (!std::filesystem::is_directory(path.parent_path() / ".gitlet")) {
        throw std::runtime_error("Not a .gitlet working directory: " + path.string());
    }
    if (std::filesystem::is_directory(path)) return false;
    return std::filesystem::remove(path);
}

void BinaryWriter::writeUint64(std::uint64_t value) {
    for (int shift = 56; shift >= 0; shift -= 8) {
        data_.push_back(static_cast<char>((value >> shift) & 0xff));
    }
}

void BinaryWriter::writeString(std::string_view value) {
    writeUint64(value.size());
    if (!value.empty()) data_.append(value);
}

BinaryReader::BinaryReader(std::string bytes) : data_(std::move(bytes)) {}

std::size_t BinaryReader::remaining() const { return data_.size() - position_; }

std::uint64_t BinaryReader::readUint64() {
    if (remaining() < 8) throw std::runtime_error("Truncated integer in object");
    std::uint64_t value = 0;
    for (int i = 0; i < 8; ++i) {
        value = (value << 8) | static_cast<unsigned char>(data_[position_++]);
    }
    return value;
}

std::string BinaryReader::readString() {
    const auto size = readUint64();
    if (size > remaining()) throw std::runtime_error("Truncated string in object");
    auto result = data_.substr(position_, static_cast<std::size_t>(size));
    position_ += static_cast<std::size_t>(size);
    return result;
}

void BinaryReader::requireEnd() const {
    if (remaining() != 0) throw std::runtime_error("Unexpected trailing object data");
}

} // namespace gitlet::utils
