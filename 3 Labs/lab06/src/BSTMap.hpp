#pragma once
#include "Map61B.hpp"
template <class K, class V> class BSTMap : public Map61B<K, V> {
    // TODO: Design the node type and instance variables for a binary search tree.
  public:
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
    void printInOrder() const {
        throw std::logic_error("TODO: printInOrder");
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
};
