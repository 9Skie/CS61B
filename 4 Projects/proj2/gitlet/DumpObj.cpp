#include "Utils.hpp"
#include <exception>
#include <iomanip>
#include <iostream>

// Usage: dumpobj FILE... Prints stored bytes without knowing your object schema.
// Once you design a decoder, you may extend this to call your object's dump().
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: dumpobj FILE...\n";
        return 1;
    }
    try {
        for (int i = 1; i < argc; ++i) {
            const auto bytes = gitlet::utils::readContents(argv[i]);
            std::cout << argv[i] << " (" << std::dec << bytes.size() << " bytes)\n";
            for (std::size_t offset = 0; offset < bytes.size(); offset += 16) {
                std::cout << std::hex << std::setfill('0') << std::setw(8) << offset << "  ";
                for (std::size_t j = 0; j < 16; ++j) {
                    if (offset + j < bytes.size()) {
                        std::cout << std::setw(2)
                                  << static_cast<unsigned>(static_cast<unsigned char>(bytes[offset+j])) << ' ';
                    } else std::cout << "   ";
                }
                std::cout << " |";
                for (std::size_t j = offset; j < bytes.size() && j < offset + 16; ++j) {
                    const auto c = static_cast<unsigned char>(bytes[j]);
                    std::cout << (c >= 32 && c < 127 ? static_cast<char>(c) : '.');
                }
                std::cout << "|\n";
            }
        }
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
