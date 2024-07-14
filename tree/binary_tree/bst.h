#pragma once

#include "binary_tree.h"

template<typename T> class BST : public BinaryTree<T> {
protected:
    BinaryTreeNode<T>* _hot; //查找的最后一个节点的父节点
    Dir _hotc; // 查找的最后一个节点相对于父节点的位置

    //可以简化rebalance的3+4子树重构算法
    //参考https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986336?channel=i.area.learn_title
    static BinaryTreeNode<T>* connect34(BinaryTreeNode<T>* a, BinaryTreeNode<T>* b, BinaryTreeNode<T>* c,
                                BinaryTreeNode<T>* T0, BinaryTreeNode<T>* T1, BinaryTreeNode<T>* T2, BinaryTreeNode<T>* T3) {
        T0->connectAsLeftChild(a);
        T1->connectAsRightChild(a);
        BinaryTree<T>::updateHeight(a);

        T2->connectAsLeftChild(c);
        T3->connectAsRightChild(c);
        BinaryTree<T>::updateHeight(c);

        a->connectAsLeftChild(b);
        c->connectAsRightChild(b);
        BinaryTree<T>::updateHeight(b);

        b->detach();

        return b;
    }
public:
    BST() : _hot(nullptr), _hotc(UNKNOWN) {}

    virtual BinaryTreeNode<T>* search(const T& e) {
        auto v = this->_root;
        _hot = nullptr;
        _hotc = UNKNOWN;
        while (v != nullptr) {
            if (e == v->val()) {
                return v;
            }
            _hot = v;
            if (e < v->val()) {
                _hotc = LEFT;
                v = v->leftChild();
            } else {
                _hotc = RIGHT;
                v = v->rightChild();
            }
        }
        return nullptr;
    }

    virtual BinaryTreeNode<T>* insert(const T& e) {
        if (this->_root == nullptr) {
            return this->insertRoot(e);
        }

        auto x = search(e);
        if (x != nullptr) {
            return x;
        }

        this->_size++;
        x = new BinaryTreeNode<T>(e);
        x->connectAsChild(_hot, _hotc);
        this->updateHeightUpwards(x);

        return x;
    }

    virtual bool remove(const T& e) {
        return false;
    }
};