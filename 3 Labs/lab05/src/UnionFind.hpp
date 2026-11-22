#pragma once
#include <stdexcept>
class UnionFind {
    // TODO: Instance variables.
  public:
    // Initially, all N items are in disjoint sets.
    explicit UnionFind(int N) { /* TODO */ }
    // Returns the size of the set containing v.
    int sizeOf(int v) { /* TODO */
        return -1;
    }
    // Returns v's parent, or its negative set size if v is a root.
    int parent(int v) { /* TODO */
        return -1;
    }
    bool connected(int v1, int v2) { /* TODO */
        return false;
    }
    // Find the root with path compression. Throw std::invalid_argument for invalid items.
    int find(int v) { /* TODO */
        return -1;
    }
    // Union by size. Break ties by attaching v1's root to v2's root.
    // Self-unions and already connected pairs should not change the structure.
    // The name is unite because union is a reserved C++ keyword.
    void unite(int v1, int v2) { /* TODO */ }
};
