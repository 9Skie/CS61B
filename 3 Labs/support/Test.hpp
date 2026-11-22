#pragma once
#include "Support.hpp"
#include <functional>

namespace test {
struct Failure : std::runtime_error {
    using std::runtime_error::runtime_error;
};
inline void require(bool condition, const char *expression, const char *file, int line) {
    if (!condition)
        throw Failure(std::string(file) + ":" + std::to_string(line) + ": " + expression);
}
using Case = std::pair<std::string, std::function<void()>>;
inline std::vector<Case> &cases() {
    static std::vector<Case> all;
    return all;
}
struct Register {
    Register(std::string name, std::function<void()> fn) {
        cases().emplace_back(name, fn);
    }
};
class Capture {
    std::ostream &stream;
    std::ostringstream buffer;
    std::streambuf *old;

  public:
    explicit Capture(std::ostream &s) : stream(s), old(s.rdbuf(buffer.rdbuf())) {}
    ~Capture() {
        stream.rdbuf(old);
    }
    std::string str() const {
        return buffer.str();
    }
};
inline int run() {
    int failures = 0;
    for (auto &[name, fn] : cases()) {
        try {
            fn();
            std::cout << "PASS " << name << '\n';
        } catch (const std::exception &e) {
            ++failures;
            std::cout << "FAIL " << name << ": " << e.what() << '\n';
        }
    }
    std::cout << cases().size() - failures << '/' << cases().size() << " tests passed\n";
    return failures ? 1 : 0;
}
} // namespace test
#define CHECK(...) test::require(bool((__VA_ARGS__)), #__VA_ARGS__, __FILE__, __LINE__)
#define TEST(name)                                                                                 \
    static void name();                                                                            \
    static test::Register register_##name(#name, name);                                            \
    static void name()
#define CHECK_THROWS_AS(expression, type)                                                          \
    do {                                                                                           \
        bool caught = false;                                                                       \
        try {                                                                                      \
            expression;                                                                            \
        } catch (const type &) {                                                                   \
            caught = true;                                                                         \
        }                                                                                          \
        CHECK(caught);                                                                             \
    } while (false)
#ifdef TEST_MAIN
int main() {
    return test::run();
}
#endif
