#pragma once
#include <memory>
#include <stdexcept>
template <class T> class RedBlackTree {
  public:
    struct RBTreeNode;
    using Node = std::shared_ptr<RBTreeNode>;
    struct RBTreeNode {
        const T item;
        bool isBlack;
        Node left, right;
        RBTreeNode(bool black, T value, Node l = nullptr, Node r = nullptr)
            : item(value), isBlack(black), left(l), right(r) {}
    };
    Node root;
    virtual ~RedBlackTree() = default;
    // Flip the color of node and both its children (both children exist).
    virtual void flipColors(Node node) { /* TODO */ }
    // Rotate right and swap the colors of the old and new roots.
    virtual Node rotateRight(Node node) { /* TODO */
        return nullptr;
    }
    // Rotate left and swap the colors of the old and new roots.
    virtual Node rotateLeft(Node node) { /* TODO */
        return nullptr;
    }
    void insert(T item) {
        root = insert(root, item);
        if (!root)
            throw std::logic_error("insert returned a null root");
        root->isBlack = true;
    }

  private:
    bool isRed(Node node) const {
        return node && !node->isBlack;
    }
    Node insert(Node node, T item) {
        // TODO: Insert (return) a new red leaf node.
        // TODO: Handle normal binary search tree insertion.
        // TODO: Rotate left.
        // TODO: Rotate right.
        // TODO: Flip colors.
        return nullptr; // Replace this return statement.
    }
};
