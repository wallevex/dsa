#pragma once

#include "../bst.h"

template<typename T>
class Splay : public BST<T> {
private:
    //splay双旋操作，将节点v上移至根节点
    //具体参考学堂在线 https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986405?channel=i.area.learn_title
    BinaryTreeNode<T>* splay(BinaryTreeNode<T>* v) {
        while (v->hasParent() && v->parent()->hasParent()) {
            auto p = v->parent();
            auto g = v->parent()->parent();
            auto gg = g->parent(); // 保存g的父节点信息，以及g与其父节点的关系
            auto gdir = g->dirAsChild();

            //1.对节点v做双旋并调用detach将v从树中分开
            if (p->dirAsChild() == LEFT) {
                if (v->dirAsChild() == LEFT) { //zig-zig形式（祖、父节点连续右旋）
                    p->rightChild()->connectAsLeftChild(g);
                    v->rightChild()->connectAsLeftChild(p);
                    g->connectAsRightChild(p);
                    p->connectAsRightChild(v);
                } else { //zig-zag形式（左旋+右旋）
                    v->leftChild()->connectAsRightChild(p);
                    v->rightChild()->connectAsLeftChild(g);
                    p->connectAsLeftChild(v);
                    g->connectAsRightChild(v);
                }
            } else {
                if (v->dirAsChild() == RIGHT) { //zag-zag形式（祖、父节点连续左旋）
                    p->leftChild()->connectAsRightChild(g);
                    v->leftChild()->connectAsRightChild(p);
                    g->connectAsLeftChild(p);
                    p->connectAsLeftChild(v);
                } else { //zag-zig形式（右旋+左旋）
                    v->leftChild()->connectAsRightChild(g);
                    v->rightChild()->connectAsLeftChild(p);
                    g->connectAsLeftChild(v);
                    p->connectAsRightChild(v);
                }
            }
            v->detach();

            //2.将v重新连接到树中（如果v恰好变成了根就需要更改_root）
            if (gg == nullptr) {
                this->_root = v;
            } else {
                v->connectAsChild(gg, gdir);
            }
        }

        //可能需要一次额外的单旋
        if (v->hasParent()) {
            auto p = v->parent();
            if (v->dirAsChild() == LEFT) {
                v->rightChild()->connectAsLeftChild(p);
                p->connectAsRightChild(v);
            } else if (v->dirAsChild() == RIGHT) {
                v->leftChild()->connectAsRightChild(p);
                p->connectAsLeftChild(v);
            }
            v->detach();
        }

        return v;
    }
public:
    // 如果没命中，search会将_hot移至root
    BinaryTreeNode<T>* search(const T& e) override {
        auto x = BST<T>::search(e);
        if (x != nullptr) {
            this->_root = splay(x);
        } else {
            this->_root = splay(this->_hot);
        }
        return this->_root;
    }

    // 新插入的节点需要移至root
    BinaryTreeNode<T>* insert(const T& e) override {
        if (this->empty()) {
            return this->insertRoot(e);
        }

        auto x = search(e);
        //若找到了目标e，根据search的语义e已经被移送至根节点，直接返回即可
        if (e == x->val()) {
            return x;
        }

        //若未找到目标e，根据search的语义_hot会被移至根节点
        // 此时直接将e作为_hot的左孩子或右孩子插入即可
        this->_root = new BinaryTreeNode<T>(e);
        if (e < x->val()) {
            x->leftChild()->connectAsLeftChild(this->_root);
            x->connectAsRightChild(this->_root);
        } else {
            x->rightChild()->connectAsRightChild(this->_root);
            x->connectAsLeftChild(this->_root);
        }

        this->_size++;

        return this->_root;
    }

    bool remove(const T& e) override {
        if (this->empty()) {
            return false;
        }

        auto x = search(e);
        if (e != x->val()) {
            return false;
        }
        this->removeAt(x);
        this->_size--;

        return true;
    }
};