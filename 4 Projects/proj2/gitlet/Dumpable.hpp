#pragma once
#include <ostream>

namespace gitlet {

// Optional interface for YOUR decoded objects; not an automatic serializer.
struct Dumpable {
    virtual ~Dumpable() = default;
    virtual void dump(std::ostream& out) const = 0;
};

} // namespace gitlet
