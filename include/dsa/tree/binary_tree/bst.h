#pragma once

#include "binary_tree.h"

template<typename T>
class BST : public BinaryTree<T> {
protected:
    BinaryTreeNode<T>* _hot; //查找的最后一个节点的父节点
    Dir _hotc; // 查找的最后一个节点相对于父节点的位置

    //可以简化rotate的3+4子树重构算法
    //参考学堂在线 https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986336?channel=i.area.learn_title
    static BinaryTreeNode<T>* connect34(BinaryTreeNode<T>* a, BinaryTreeNode<T>* b, BinaryTreeNode<T>* c,
                                BinaryTreeNode<T>* T0, BinaryTreeNode<T>* T1, BinaryTreeNode<T>* T2, BinaryTreeNode<T>* T3) {
        T0->connectAsLeftChild(a);
        T1->connectAsRightChild(a);

        T2->connectAsLeftChild(c);
        T3->connectAsRightChild(c);

        a->connectAsLeftChild(b);
        c->connectAsRightChild(b);

        b->detach();

        return b;
    }

    // 根据v->p->g这一局部子树的形状，对其进行旋转重构
    // 适用于AVL、RBT
    BinaryTreeNode<T>* rotateVPG(BinaryTreeNode<T>* v) {
        auto p = v->parent();
        auto g = p->parent();

        auto gg = g->parent(); // 保存g的父节点信息，以及g与其父节点的关系
        auto gdir = g->dirAsChild();
        BinaryTreeNode<T>* r;

        if (p->dirAsChild() == LEFT) {
            if (v->dirAsChild() == LEFT) { // zig-zig形式（右旋）
                r = connect34(v, p, g, v->leftChild(), v->rightChild(), p->rightChild(), g->rightChild());
            } else { // zag-zig形式（左旋+右旋）
                r = connect34(p, v, g, p->leftChild(), v->leftChild(), v->rightChild(), g->rightChild());
            }
        } else {
            if (v->dirAsChild() == RIGHT) { // zag-zag形式（左旋）
                r = connect34(g, p, v, g->leftChild(), p->leftChild(), v->leftChild(), v->rightChild());
            } else { // zig-zag形式（右旋+左旋）
                r = connect34(g, v, p, g->leftChild(), v->leftChild(), v->rightChild(), p->rightChild());
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

    // 返回实际被删除的节点的继任者（注意不一定是v的继任者）
    // _hot指向实际被删除的节点的父节点
    // 该接口的语义有利于简化红黑树的删除操作
    BinaryTreeNode<T>* removeAt(BinaryTreeNode<T>* v) {
        BinaryTreeNode<T> *rm, *succ;
        if (!v->hasRightChild()) {
            rm = v;
            succ = v->leftChild();
        } else if (!v->hasLeftChild()) {
            rm = v;
            succ = v->rightChild();
        } else {
            auto vsucc = successorOf(v);
            v->updateVal(vsucc->val());
            rm = vsucc;
            succ = vsucc->rightChild();
        }

        this->_hot = rm->parent();
        if (!rm->hasParent()) {
            this->_root = succ;
        } else {
            succ->connectAsChild(rm->parent(), rm->dirAsChild());
        }
        delete rm;

        return succ;
    }
public:
    BST() : _hot(nullptr), _hotc(UNKNOWN) {}

    //返回节点v的直接后继
    static BinaryTreeNode<T>* successorOf(BinaryTreeNode<T>* v) {
        //若v存在右子树，那么后继必然在右子树的最左侧
        if (v->hasRightChild()) {
            v = v->rightChild();
            while (v->hasLeftChild()) {
                v = v->leftChild();
            }
            return v;
        }

        //若v不存在右子树，那么后继是“将节点v包含于其左子树中的最低祖先”
        while (v->dirAsChild() == LEFT) {
            v = v->parent();
        }
        return v->parent();
    }

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

        return x;
    }

    virtual bool remove(const T& e) {
        auto x = search(e);
        if (x == nullptr) {
            return false;
        }
        removeAt(x);
        this->_size--;
        return true;
    }
};