#pragma once

#include <cstdio>
#include "dsa/tree/binary_tree/bst.h"

template<typename T>
class AVLNode : public BinaryTreeNode<T> {
private:
    int _height;
public:
    AVLNode(T e, int h = 0) : BinaryTreeNode<T>(e), _height(h) {}
    // 高度这种涉及到整棵树的全局性信息，计算方法对单个节点而言应该是不可见的
    // 节点只负责直接写覆盖即可
    int height() const { return this == nullptr ? -1 : _height; }
    void updateHeight(int h) { _height = h; }

    AVLNode<T>* parentMustAVL()  { return static_cast<AVLNode<T>*>(this->_parent); }
    AVLNode<T>* leftChildMustAVL()  { return static_cast<AVLNode<T>*>(this->_lc); }
    AVLNode<T>* rightChildMustAVL()  { return static_cast<AVLNode<T>*>(this->_rc); }
};

template<typename T>
class AVL : public BST<T> {
private:
    // 更新单个节点高度
    static void updateHeight(AVLNode<T>* v) {
        auto h = 1 + std::max(v->leftChildMustAVL()->height(), v->rightChildMustAVL()->height());
        v->updateHeight(h);
    }

    // 向上更新祖先节点高度
    static void updateHeightUpwards(AVLNode<T>* v) {
        while (v != nullptr) {
            updateHeight(v);
            v = v->parentMustAVL();
        }
    }

    static int balanceFactor(AVLNode<T>* v) {
        return v->leftChildMustAVL()->height() - v->rightChildMustAVL()->height();
    }

    static bool isBalanced(AVLNode<T>* v) {
        auto bf = balanceFactor(v);
        return (-2 < bf) && (bf < 2);
    }

    AVLNode<T>* rebalance(AVLNode<T>* g) {
        auto higher = [](AVLNode<T>* p) -> AVLNode<T>* {
            return p->leftChildMustAVL()->height() > p->rightChildMustAVL()->height() ? p->leftChildMustAVL() : p->rightChildMustAVL();
        };
        auto v = higher(higher(g));
        auto r = static_cast<AVLNode<T>*>(this->rotateVPG(v));

        updateHeight(r->leftChildMustAVL());
        updateHeight(r->rightChildMustAVL());
        updateHeight(r);

        return r;
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
        x = new AVLNode<T>(e);
        x->connectAsChild(this->_hot, this->_hotc);

        for (auto g = static_cast<AVLNode<T>*>(this->_hot); g != nullptr; g = g->parentMustAVL()) {
            if (!isBalanced(g)) {
                rebalance(g);
                break; //最低不平衡节点恢复平衡后，祖先节点会自动恢复平衡
            } else {
                updateHeight(g);
            }
        }

        return x;
    }

    // TODO 更新高度
    bool remove(const T& e) override {
        auto x = search(e);
        if (x == nullptr) {
            return false;
        }
        this->removeAt(x);
        this->_size--;

        for (auto g = static_cast<AVLNode<T>*>(this->_hot); g != nullptr; g = g->parentMustAVL()) {
            if (!isBalanced(g)) {
                g = rebalance(g);
            } else {
                updateHeight(g);
            }
        }

        return true;
    }
};