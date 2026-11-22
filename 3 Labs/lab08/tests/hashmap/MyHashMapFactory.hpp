#pragma once
#include "hashmap/MyHashMap.hpp"
// std::stack intentionally hides iteration. This vector-backed stack bucket
// keeps iteration available, as required by the bucket contract.
template <class T, class Alloc = std::allocator<T>>
class StackBucket : public std::vector<T, Alloc> {
  public:
    using std::vector<T, Alloc>::vector;
};
template <class K, class V, template <class...> class Bucket>
MyHashMap<K, V, Bucket> createBucketedMap() {
    return {};
}
