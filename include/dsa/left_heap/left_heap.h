//
// Created by huhaolong on 2024/7/16.
//

#pragma once

#include "dsa/priority_queue/priority_queue.h"
#include "dsa/tree/binary_tree/binary_tree.h"
#include <algorithm>
#include <cstdio>

template <typename T>
class LeftHeapNode: public BinaryTreeNode<T> {
private:
    int _npl;
public:
    LeftHeapNode(T e, int l = 1) : BinaryTreeNode<T>(e), _npl(l) {}
    int npl() const { return this == nullptr ? 0 : _npl; }
    void updateNpl(int l) { _npl = l; }

    LeftHeapNode<T>* parentMustLH() { return static_cast<LeftHeapNode<T>*>(this->_parent); }
    LeftHeapNode<T>* leftChildMustLH()  { return static_cast<LeftHeapNode<T>*>(this->_lc); }
    LeftHeapNode<T>* rightChildMustLH()  { return static_cast<LeftHeapNode<T>*>(this->_rc); }
};

template <typename T>
class LeftHeap : public PriorityQueue<T> {
private:
	LeftHeapNode<T>* _root;

    static void updateNpl(LeftHeapNode<T>* v) {
        if (!v->hasRightChild()) {
            v->updateNpl(1);
            return;
        }
        v->updateNpl(v->rightChildMustLH()->npl() + 1);
    }

    //左式堆合并算法
    //具体参考学堂在线 https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986806?channel=i.area.learn_title
    static LeftHeapNode<T>* mergeLeftHeapTree(LeftHeapNode<T>* a, LeftHeapNode<T>* b) {
        if (a == nullptr) { return b; }
        if (b == nullptr) { return a; }

        if (a->val() < b->val()) {
            std::swap(a, b);
        }

        auto rc = mergeLeftHeapTree(a->rightChildMustLH(), b);
        rc->connectAsRightChild(a);
        if (a->leftChildMustLH()->npl() < rc->npl()) {
            a->swapChildren();
        }
        updateNpl(a);

        return a;
    }
public:
    LeftHeap() { _root = nullptr; }

    LeftHeap(std::vector<T>* const seq) {
        //TODO 是否可以用Floyd算法建左式堆
    }

    LeftHeap(LeftHeap<T>* a, LeftHeap<T>* b) {
        _root = mergeLeftHeapTree(a->_root, b->_root);
    }

    unsigned int size() const override {
        unsigned int sz = 0;
        auto visit = [&](BinaryTreeNode<T>* v) {
            sz++;
        };
        BinaryTree<T>::traverseLevelFrom(_root, visit);
        return sz;
    }

    bool empty() const override {
        return _root == nullptr;
    }

    void push(const T& e) override {
        _root = mergeLeftHeapTree(_root, new LeftHeapNode<T>(e));
    }

    T pop() override {
        auto lc = _root->leftChildMustLH();
        if (lc != nullptr) lc->detach();
        auto rc = _root->rightChildMustLH();
        if (rc != nullptr) rc->detach();
        auto top = _root->val();
        delete _root;

        _root = mergeLeftHeapTree(lc, rc);

        return top;
    }

    T top() const override {
        return _root->val();
    }
};
