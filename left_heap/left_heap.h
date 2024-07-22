//
// Created by huhaolong on 2024/7/16.
//

#pragma once

#include "../priority_queue/priority_queue.h"
#include "../tree/binary_tree/binary_tree.h"
#include <algorithm>
#include <cstdio>

template <typename T> class LeftHeap : public PriorityQueue<T> {
protected:
	BinaryTree<T>* _tree;

    static void updateNpl(BinaryTreeNode<T>* v) {
        if (!v->hasRightChild()) {
            v->updateNpl(1);
            return;
        }
        v->updateNpl(v->rightChild()->npl() + 1);
    }

    //左式堆合并算法
    //具体参考学堂在线 https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986806?channel=i.area.learn_title
    static BinaryTreeNode<T>* mergeLeftHeapTree(BinaryTreeNode<T>* a, BinaryTreeNode<T>* b) {
        if (a == nullptr) { return b; }
        if (b == nullptr) { return a; }

        if (a->val() < b->val()) {
            std::swap(a, b);
        }

        auto rc = mergeLeftHeapTree(a->rightChild(), b);
        rc->connectAsRightChild(a);
        if (a->leftChild()->npl() < rc->npl()) {
            a->swapChildren();
        }
        updateNpl(a);

        return a;
    }
public:
    LeftHeap() { _tree = new BinaryTree<T>(); }

    LeftHeap(std::vector<T>* const seq) {
        //TODO 是否可以用Floyd算法建左式堆
    }

    LeftHeap(LeftHeap<T>* a, LeftHeap<T>* b) {
        auto c = mergeLeftHeapTree(a->_tree->root(), b->_tree->root());
        _tree = new BinaryTree<T>(c);
    }

    unsigned int size() const override {
        return _tree->size();
    }

    bool empty() const override {
        return _tree->empty();
    }

    void push(const T& e) override {
        auto c = mergeLeftHeapTree(_tree->root(), new BinaryTreeNode<T>(e));
        _tree = new BinaryTree<T>(c);
    }

    T pop() override {
        auto lc = _tree->root()->leftChild();
        if (lc != nullptr) lc->detach();
        auto rc = _tree->root()->rightChild();
        if (rc != nullptr) rc->detach();
        auto top = _tree->root()->val();
        delete _tree->root();

        auto c = mergeLeftHeapTree(lc, rc);
        _tree = new BinaryTree<T>(c);

        return top;
    }

    T top() const override {
        return _tree->root()->val();
    }
};
