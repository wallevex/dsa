//
// Created by huhaolong on 2024/7/22.
//

#pragma once

#include <vector>

template <typename T> class BTreeNode {
protected:
    BTreeNode<T>* _parent;
    std::vector<T> _vals;
    std::vector<BTreeNode<T>*> _children;
public:
    BTreeNode<T>* parent() { return _parent; }
    std::vector<T> vals() { return _vals; }
    std::vector<BTreeNode<T>*> children() { return _children; }
};

template <typename T> class BTree {
protected:
    unsigned int _size;
    unsigned int _m;
    BTreeNode<T>* _root;
public:
    BTree(int m = 3) : _m(m), _size(0) { _root = new BTreeNode<T>(); }
    ~BTree() { }

    BTreeNode<T>* root() { return _root; }
    unsigned int size() const { return _size; }
    unsigned int order() const { return _m; }
    bool empty() const { return _root == nullptr; }

    BinaryTreeNode<T>* search(const T& e) {
        // TODO
        return nullptr;
    }

    bool insert(const T& e) {
        // TODO
        return false;
    }

    bool remove(const T& e) {
        // TODO
        return false;
    }
};
