#pragma once

#include <cstdio>
#include "../bst.h"

template<typename T> class AVL : public BST<T> {
protected:
    static int balanceFactor(BinaryTreeNode<T>* v) {
        return v->leftChild()->height() - v->rightChild()->height();
    }

    static bool isBalanced(BinaryTreeNode<T>* v) {
        auto bf = balanceFactor(v);
        return (-2 < bf) && (bf < 2);
    }

    BinaryTreeNode<T>* rebalance(BinaryTreeNode<T>* g) {
        auto higher = [](BinaryTreeNode<T>* p) -> BinaryTreeNode<T>* {
            return p->leftChild()->height() > p->rightChild()->height() ? p->leftChild() : p->rightChild();
        };
        auto v = higher(higher(g));
        return this->rotateVPG(v);
    }
public:
    BinaryTreeNode<T>* search(const T& e) {
        return BST<T>::search(e);
    }

    BinaryTreeNode<T>* insert(const T& e) override {
        if (this->empty()) {
            return this->insertRoot(e);
        }

        auto x = search(e);
        if (x != nullptr) {
            return x;
        }

        this->_size++;
        x = new BinaryTreeNode<T>(e);
        x->connectAsChild(this->_hot, this->_hotc);

        for (auto g = this->_hot; g != nullptr; g = g->parent()) {
            if (!isBalanced(g)) {
                rebalance(g);
                break; //最低不平衡节点恢复平衡后，祖先节点会自动恢复平衡
            } else {
                this->updateHeight(g);
            }
        }

        return x;
    }

    bool remove(const T& e) override {
        auto x = search(e);
        if (x == nullptr) {
            return false;
        }
        this->removeAt(x);
        this->_size--;

        for (auto g = this->_hot; g != nullptr; g = g->parent()) {
            if (!isBalanced(g)) {
                g = rebalance(g);
            } else {
                this->updateHeight(g);
            }
        }

        return true;
    }
};