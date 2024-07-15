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
        auto higher = [](BinaryTreeNode<T>* nd) -> Dir {
            if (nd->leftChild()->height() > nd->leftChild()->height()) {
                return LEFT;
            }
            return RIGHT;
        };

        auto gg = g->parent(); // 保存g的父节点信息，以及g与其父节点的关系
        auto gdir = g->dirAsChild();
        BinaryTreeNode<T>* r;

        if (higher(g) == LEFT) {
            auto p = g->leftChild();
            if (higher(p) == LEFT) { //zig-zig形式（右旋）
                auto v = p->leftChild();
                r = BST<T>::connect34(v, p, g, v->leftChild(), v->rightChild(), p->rightChild(), g->rightChild());
            } else { //zig-zag形式（左旋+右旋）
                auto v = p->rightChild();
                r = BST<T>::connect34(p, v, g, p->leftChild(), v->leftChild(), v->rightChild(), g->rightChild());
            }
        } else {
            auto p = g->rightChild();
            if (higher(p) == RIGHT) { //zag-zag形式（左旋）
                auto v = p->rightChild();
                r = BST<T>::connect34(g, p, v, g->leftChild(), p->leftChild(), v->leftChild(), v->rightChild());
            } else { //zag-zig形式（右旋+左旋）
                auto v = p->leftChild();
                r = BST<T>::connect34(g, v, p, g->leftChild(), v->leftChild(), v->rightChild(), p->rightChild());
            }
        }

        // 将3+4重构后的根节点重新连接回g之前的父节点
        if (gg == nullptr) { //这种情况表明根节点发生了旋转，需要更新根节点
            this->_root = r;
        } else {
            r->connectAsChild(gg, gdir);
        }

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