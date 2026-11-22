#pragma once
#include "Map61B.hpp"
// Supplied linked-list map used in the timing experiments.
template <class K, class V> class ULLMap : public Map61B<K, V> {
    struct Entry {
        K key;
        std::optional<V> val;
        std::shared_ptr<Entry> next;
        Entry(K k, std::optional<V> v, std::shared_ptr<Entry> n) : key(k), val(v), next(n) {}
        Entry *get(const K &k) {
            if (k == key)
                return this;
            if (!next)
                return nullptr;
            return next->get(k);
        }
    };
    std::shared_ptr<Entry> list;
    int count = 0;
    struct ULLMapIter : Map61B<K, V>::Iterator {
        std::shared_ptr<Entry> cur;
        explicit ULLMapIter(std::shared_ptr<Entry> head) : cur(head) {}
        bool hasNext() const override {
            return bool(cur);
        }
        K next() override {
            if (!cur)
                throw std::out_of_range("Iterator exhausted");
            K key = cur->key;
            cur = cur->next;
            return key;
        }
    };

  public:
    std::optional<V> get(const K &key) const override {
        auto *entry = list ? list->get(key) : nullptr;
        return entry ? entry->val : std::nullopt;
    }
    int size() const override {
        return count;
    }
    void clear() override {
        count = 0;
        list.reset();
    }
    void put(const K &key, std::optional<V> value) override {
        if (list) {
            auto *entry = list->get(key);
            if (!entry) {
                list = std::make_shared<Entry>(key, value, list);
                ++count;
            } else
                entry->val = value;
        } else {
            list = std::make_shared<Entry>(key, value, list);
            ++count;
        }
    }
    bool containsKey(const K &key) const override {
        return list && list->get(key);
    }
    std::unique_ptr<typename Map61B<K, V>::Iterator> iterator() const override {
        return std::make_unique<ULLMapIter>(list);
    }
    std::optional<V> remove(const K &) override {
        throw std::logic_error("Optional remove not implemented");
    }
    std::set<K> keySet() const override {
        throw std::logic_error("Optional keySet not implemented");
    }
};
