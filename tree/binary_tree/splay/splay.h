#pragma once

#include "tree/binary_tree/bst.h"

template<typename T> class Splay : public BST<T> {
protected:
    BinaryTreeNode<T>* splay(BinaryTreeNode<T>* v) {
        if (v == nullptr) {
            return nullptr;
        }
        return nullptr;
    }
public:
    // 如果没命中，search会将_hot移至root
    BinaryTreeNode<T>* search(const T& e) override {
        auto x = BST<T>::search(e);
        if (x != nullptr) {
            this->_root = splay(x);
        } else {
            this->_root = splay(_hot);
        }
        return this->_root;
    }

    // 新插入的节点会被移至root
    BinaryTreeNode<T>* insert(const T& e) override {
        auto v = BST<T>::insert(e);
        this->_root = splay(v);
        return this->_root;
    }

    bool remove(const T& e) override {
        return false;
    }
};