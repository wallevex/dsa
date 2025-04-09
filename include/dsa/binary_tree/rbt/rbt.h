#pragma once

#include "dsa/binary_tree/bst.h"

typedef enum { RED, BLACK } Color;

template <typename T>
class RBTNode : public BinaryTreeNode<T> {
private:
    Color _color;
    int _bh;
public:
    RBTNode(T e, Color c = RED, int bh = 0) : BinaryTreeNode<T>(e), _color(c), _bh(bh) {}
    Color color() const { return this == nullptr ? BLACK : _color; }
    void updateColor(Color c) { _color = c; }
    int blackHeight() const { return this == nullptr ? 0 : _bh; }
    void updateBlackHeight(int bh) { _bh = bh; }

    RBTNode<T>* parentMustRBT()  { return static_cast<RBTNode<T>*>(this->_parent); }
    RBTNode<T>* leftChildMustRBT()  { return static_cast<RBTNode<T>*>(this->_lc); }
    RBTNode<T>* rightChildMustRBT()  { return static_cast<RBTNode<T>*>(this->_rc); }
};

template <typename T>
class RBT : public BST<T> {
protected:
    // p的子树的黑高度
    static int childBlackHeightOf(RBTNode<T>* p) {
        return p->color() == BLACK ? p->blackHeight() - 1 : p->blackHeight();
    }

    // 接口语义：修复v->p->g这一局部子树的双红问题（v、p都为红色）
    // 接口返回：修复双红问题后的v->p->g局部子树的根
    // 参考学堂在线：https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986623?channel=i.area.learn_title
    RBTNode<T>* repairDoubleRed(RBTNode<T>* v) {
        auto p = v->parentMustRBT();
        auto g = p->parentMustRBT();
        auto u = p->dirAsChild() == LEFT ? g->rightChildMustRBT() : g->leftChildMustRBT();

        if (u->color() == BLACK) { // Case 1
            int gbh = g->blackHeight();
            RBTNode<T>* r = static_cast<RBTNode<T>*>(this->rotateVPG(v));
            r->updateColor(BLACK); r->updateBlackHeight(gbh);
            r->leftChildMustRBT()->updateColor(RED); r->leftChildMustRBT()->updateBlackHeight(gbh - 1);
            r->rightChildMustRBT()->updateColor(RED); r->rightChildMustRBT()->updateBlackHeight(gbh - 1);
            return r;
        }

        // Case 2
        g->updateColor(RED);
        p->updateColor(BLACK); p->updateBlackHeight(p->blackHeight() + 1);
        u->updateColor(BLACK); u->updateBlackHeight(u->blackHeight() + 1);
        return g;
    }

    // 接口语义：递归修复因节点v高度减少1而导致的其父节点p的黑高度失衡问题
    // 如果用迭代去实现，代码会非常恶心，只好用递归了
    // 参考学堂在线：https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986636?channel=i.area.learn_title
    void repairBlackHeight(RBTNode<T>* v, RBTNode<T>* p) { // v可能是空节点
        if (p == nullptr) return; // 只可能是Case 2-B会递归调用到这里，此时v必然为黑色，直接返回即可

        if (v->color() == RED) { // Case 0
            v->updateColor(BLACK); v->updateBlackHeight(v->blackHeight() + 1);
            return;
        }

        auto s = v == p->leftChildMustRBT() ? p->rightChildMustRBT() : p->leftChildMustRBT(); // sibling
        auto siblingBothChildrenBlack = s->leftChildMustRBT()->color() == BLACK && s->rightChildMustRBT()->color() == BLACK;

        if (s->color() == BLACK && !siblingBothChildrenBlack) { // Case 1
            auto t = s->leftChildMustRBT()->color() == RED ? s->leftChildMustRBT() : s->rightChildMustRBT();
            auto pc = p->color(); // 备份p的颜色
            auto pbh = p->blackHeight(); // 备份p的黑高度
            auto cbh = p->color() == BLACK ? pbh - 1 : pbh; // 备份p的子树的黑高度
            RBTNode<T>* r = static_cast<RBTNode<T>*>(this->rotateVPG(t));
            r->updateColor(pc); r->updateBlackHeight(pbh);
            r->leftChildMustRBT()->updateColor(BLACK); r->leftChildMustRBT()->updateBlackHeight(cbh);
            r->rightChildMustRBT()->updateColor(BLACK); r->rightChildMustRBT()->updateBlackHeight(cbh);
            return;
        }
        if (s->color() == BLACK && siblingBothChildrenBlack) {
            s->updateColor(RED); s->updateBlackHeight(s->blackHeight() - 1);
            if (p->color() == RED) { // Case 2-R
                p->updateColor(BLACK);
            } else { // Case 2-B
                p->updateBlackHeight(p->blackHeight() - 1);
                repairBlackHeight(p, p->parentMustRBT());
            }
            return;
        }

        // Case 3: sibling color RED
        p->updateColor(RED);
        s->updateColor(BLACK);
        auto t = s->dirAsChild() == LEFT ? s->leftChildMustRBT() : s->rightChildMustRBT(); // t取与s同侧以实现单旋
        this->rotateVPG(t);
        repairBlackHeight(v, p);
    }
public:
    BinaryTreeNode<T>* search(const T& e) override {
        return BST<T>::search(e);
    }

    BinaryTreeNode<T>* insert(const T& e) override {
        if (this->empty()) {
            this->_size = 1;
            this->_root = new RBTNode<T>(e, BLACK, 1);
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
        while (v->color() == RED && (v->hasParent() && v->parentMustRBT()->color() == RED)) {
            v = repairDoubleRed(v);
        }
        if (v->color() == RED && !v->hasParent()) {
            v->updateColor(BLACK);
            v->updateBlackHeight(v->blackHeight() + 1);
        }

        return x;
    }

    bool remove(const T& e) override {
        auto x = search(e);
        if (x == nullptr) {
            return false;
        }
        auto r = static_cast<RBTNode<T>*>(this->removeAt(x));
        this->_size--;
        if (this->_size == 0) return true;
        auto p = static_cast<RBTNode<T>*>(this->_hot);

        if (p == nullptr) { // 删除的是根节点的情况
            if (r->color() == BLACK) {
                r->updateBlackHeight(r->blackHeight() - 1);
            } else {
                r->updateColor(BLACK);
            }
            return true;
        }

        auto cbh = childBlackHeightOf(p);
        if (r->blackHeight() == cbh) { // 可反推出被删除的节点x的颜色为红色
            return true;
        }

        repairBlackHeight(r, p);

        return true;
    }
};