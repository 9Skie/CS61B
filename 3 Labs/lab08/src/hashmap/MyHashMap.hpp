#pragma once
#include "Map61B.hpp"
#include <list>
#include <deque>
#include <unordered_set>
// Bucket is a standard container template (list, vector, deque, unordered_set).
// Store shared_ptr<Node> so a set bucket compares node identity, not mutable values.
template <class K, class V, template <class...> class Bucket = std::list>
class MyHashMap : public Map61B<K, V> {
  protected:
    struct Node {
        K key;
        std::optional<V> value;
        Node(K k, std::optional<V> v) : key(k), value(v) {}
    };
    using BucketType = Bucket<std::shared_ptr<Node>>;
    // Always call this factory when creating a bucket. Override the container
    // template argument to compare bucket implementations in the timing tests.
    BucketType createBucket() { /* TODO: Return an empty BucketType. */
        throw std::logic_error("TODO: createBucket");
    }

  private:
    std::vector<BucketType> buckets;
    // TODO: Define additional instance variables.
  public:
    MyHashMap() { /* TODO: default capacity 16, load factor 0.75 */ }
    explicit MyHashMap(int initialCapacity) { /* TODO */ }
    MyHashMap(int initialCapacity, double loadFactor) { /* TODO */ }
    // TODO: Implement Map61B using hashing and geometric resizing.
    // Null keys are not supported. Removing entries need not shrink the table.
    void put(const K &key, std::optional<V> value) override {
        throw std::logic_error("TODO: put");
    }
    std::optional<V> get(const K &key) const override {
        throw std::logic_error("TODO: get");
    }
    bool containsKey(const K &key) const override {
        throw std::logic_error("TODO: containsKey");
    }
    int size() const override {
        throw std::logic_error("TODO: size");
    }
    void clear() override {
        throw std::logic_error("TODO: clear");
    }
    std::set<K> keySet() const override {
        throw std::logic_error("Optional keySet");
    }
    std::optional<V> remove(const K &key) override {
        throw std::logic_error("Optional remove");
    }
    std::unique_ptr<typename Map61B<K, V>::Iterator> iterator() const override {
        throw std::logic_error("Optional iterator");
    }
    // Read-only test hook replaces runtime reflection.
    int bucketCount() const {
        return static_cast<int>(buckets.size());
    }
};
