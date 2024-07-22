#pragma once

#include "../bst.h"

typedef enum { RED, BLACK } Color;

template <typename T> class RBTNode : public BinaryTreeNode<T> {
protected:
    Color _color;
    int _bh;
public:
    RBTNode(T e, int h = 0, Color c = RED, int bh = 0) : BinaryTreeNode<T>(e, h), _color(c), _bh(bh) {}
    Color color() const { return this == nullptr ? BLACK : _color; }
    void updateColor(Color c) { _color = c; }
    int blackHeight() const { return this == nullptr ? -1 : _bh; }
    void updateBlackHeight(int bh) { _bh = bh; }

    RBTNode<T>* parent() override { return static_cast<RBTNode<T>*>(this->_parent); }
    RBTNode<T>* leftChild() override { return static_cast<RBTNode<T>*>(this->_lc); }
    RBTNode<T>* rightChild() override { return static_cast<RBTNode<T>*>(this->_rc); }
};

template <typename T> class RBT : public BST<T> {
protected:
    // 解决v->p->g这一局部子树的双红缺陷
    // 参考学堂在线：https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986623?channel=i.area.learn_title
    RBTNode<T>* solveDoubleRed(RBTNode<T>* v) {
        auto p = v->parent();
        auto g = p->parent();
        auto u = p->dirAsChild() == LEFT ? g->rightChild() : g->leftChild();

        if (u->color() == BLACK) {
            int gbh = g->blackHeight();
            RBTNode<T>* r = static_cast<RBTNode<T>*>(this->rotateVPG(v));
            r->updateColor(BLACK); r->updateBlackHeight(gbh);
            r->leftChild()->updateColor(RED); r->leftChild()->updateBlackHeight(gbh - 1);
            r->rightChild()->updateColor(RED); r->rightChild()->updateBlackHeight(gbh - 1);
            return r;
        } else {
            g->updateColor(RED);
            p->updateColor(BLACK); p->updateBlackHeight(p->blackHeight() + 1);
            u->updateColor(BLACK); u->updateBlackHeight(u->blackHeight() + 1);
            return g;
        }
    }
public:
    BinaryTreeNode<T>* search(const T& e) override {
        return BST<T>::search(e);
    }

    BinaryTreeNode<T>* insert(const T& e) override {
        if (this->empty()) {
            this->_size = 1;
            this->_root = new RBTNode<T>(e, 0, BLACK, 1);
            return this->_root;
        }

        auto x = search(e);
        if (x != nullptr) {
            return x;
        }

        this->_size++;
        x = new RBTNode<T>(e);
        x->connectAsChild(this->_hot, this->_hotc);

        RBTNode<T>* v = static_cast<RBTNode<T>*>(x);
        while (v->color() == RED && (v->hasParent() && v->parent()->color() == RED)) {
            v = solveDoubleRed(v);
        }
        if (v->color() == RED && !v->hasParent()) {
            v->updateColor(BLACK);
            v->updateBlackHeight(v->blackHeight() + 1);
        }

        return x;
    }

    bool remove(const T& e) override {
        return false;
    }
};