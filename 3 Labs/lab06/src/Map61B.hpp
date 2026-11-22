#pragma once
#include <memory>
#include <optional>
#include <set>
#include <stdexcept>
#include <vector>
// Derive your implementation from Map61B<K, V>.
// std::nullopt represents a null value, and is also returned for a missing key.
// containsKey distinguishes those two cases.
template <class K, class V> class Map61B {
  public:
    virtual ~Map61B() = default;
    virtual void put(const K &key, std::optional<V> value) = 0;
    virtual std::optional<V> get(const K &key) const = 0;
    virtual bool containsKey(const K &key) const = 0;
    virtual int size() const = 0;
    virtual void clear() = 0;
    // Optional extensions: throw std::logic_error when not implemented.
    virtual std::set<K> keySet() const = 0;
    virtual std::optional<V> remove(const K &key) = 0;
    struct Iterator {
        virtual ~Iterator() = default;
        virtual bool hasNext() const = 0;
        virtual K next() = 0;
    };
    virtual std::unique_ptr<Iterator> iterator() const = 0;
};
