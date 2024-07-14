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

    void rebalance(BinaryTreeNode<T>* g) {
        auto higher = [](BinaryTreeNode<T>* nd) -> Dir {
            if (nd->leftChild()->height() > nd->leftChild()->height()) {
                return LEFT;
            }
            return RIGHT;
        };

        auto parent = g->parent(); // 保存g的父节点信息，以及g与其父节点的关系
        auto childDir = BinaryTreeNode<T>::dirAsChild(g);
        BinaryTreeNode<T>* child;

        if (higher(g) == LEFT) {
            auto p = g->leftChild();
            if (higher(p) == LEFT) { //zig-zig形式（右旋）
                auto v = p->leftChild();
                child = BST<T>::connect34(v, p, g, v->leftChild(), v->rightChild(), p->rightChild(), g->rightChild());
            } else { //zig-zag形式（左旋+右旋）
                auto v = p->rightChild();
                child = BST<T>::connect34(p, v, g, p->leftChild(), v->leftChild(), v->rightChild(), g->rightChild());
            }
        } else {
            auto p = g->rightChild();
            if (higher(p) == RIGHT) { //zag-zag形式（左旋）
                auto v = p->rightChild();
                child = BST<T>::connect34(g, p, v, g->leftChild(), p->leftChild(), v->leftChild(), v->rightChild());
            } else { //zag-zig形式（右旋+左旋）
                auto v = p->leftChild();
                child = BST<T>::connect34(g, v, p, g->leftChild(), v->leftChild(), v->rightChild(), p->rightChild());
            }
        }

        // 将3+4重构后的根节点重新连接回g之前的父节点
        if (childDir == UNDEFINED) { //这种情况表明根节点发生了旋转
            child->detach();
            this->_root = child;
        } else if (childDir == LEFT) {
            child->connectAsLeftChild(parent);
        } else {
            child->connectAsRightChild(parent);
        }
    }
public:
    // BinaryTreeNode<T>* search(const T& e) {
    // }

    BinaryTreeNode<T>* insert(const T& e) override {
        if (this->_root == nullptr) {
            return this->insertRoot(e);
        }

        auto x = this->search(e);
        if (x != nullptr) {
            return x;
        }

        if (this->_hotc == LEFT) {
            this->_size++;
            x = new BinaryTreeNode<T>(e);
            x->connectAsLeftChild(this->_hot);
        } else {
            this->_size++;
            x = new BinaryTreeNode<T>(e);
            x->connectAsRightChild(this->_hot);
        }

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
        return false;
    }
};