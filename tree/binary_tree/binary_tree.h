#pragma once

#include <cstdio>
#include <algorithm>
#include <queue>

typedef enum { UNKNOWN, LEFT, RIGHT } Dir;

// 树节点结构只关注节点的局部信息（比如父节点、左右子节点）和局部操作（比如插入左右子节点）
// 遍历等涉及到整颗树的宏观操作不要放在这
template<typename T> class BinaryTreeNode {
protected:
    T _val;
    BinaryTreeNode<T>* _parent;
    BinaryTreeNode<T>* _lc;
    BinaryTreeNode<T>* _rc;
    int _height;
    int _npl;
public:
    BinaryTreeNode(T e, int h = 0, int l = 1) : _val(e), _parent(nullptr), _lc(nullptr), _rc(nullptr), _height(h), _npl(l) {}

    int height() const {
        if (this == nullptr) { // 特殊处理空节点，很奇怪
            return -1;
        }
        return _height;
    }

    // 高度这种涉及到整棵树的全局性信息，计算方法对单个节点而言应该是不可见的
    // 节点只负责直接写覆盖即可
    void updateHeight(int h) { _height = h; }

    int npl() const {
        if (this == nullptr) {
            return 0;
        }
        return _npl;
    }

    void updateNpl(int l) { _npl = l; }

    T val() const { return _val; }

    void updateVal(T v) { _val = v; }

    BinaryTreeNode<T>* parent() { return _parent; }   

    BinaryTreeNode<T>* leftChild() { return _lc; }

    BinaryTreeNode<T>* rightChild() { return _rc; }

    bool hasParent() const { return _parent != nullptr; }

    bool hasLeftChild() const { return _lc != nullptr; }

    bool hasRightChild() const { return _rc != nullptr; }

    //将当前节点作为左孩子连接到父节点p
    void connectAsLeftChild(BinaryTreeNode<T>* p) {
        if (this == nullptr) { //兼容空节点的情况，暂时先这样虽然很奇怪
            p->_lc = nullptr;
            return;
        }

        _parent = p;
        p->_lc = this;
    }

    //将当前节点作为右孩子连接到父节点p
    void connectAsRightChild(BinaryTreeNode<T>* p) {
        if (this == nullptr) { //兼容空节点的情况，暂时先这样虽然很奇怪
            p->_rc = nullptr;
            return;
        }

        _parent = p;
        p->_rc = this;
    }

    void connectAsChild(BinaryTreeNode<T>*p, Dir dir) {
        if (dir == LEFT) {
            connectAsLeftChild(p);
        } else if (dir == RIGHT) {
            connectAsRightChild(p);
        }
    }

    void swapChildren() {
        std::swap(_lc, _rc);
    }

    // 将当前节点和父节点断开
    void detach() {
        if (_parent == nullptr) {
            return;
        }

        if (this == _parent->_lc) {
            _parent->_lc = nullptr;
        } else if (this == _parent->_lc) {
            _parent->_rc = nullptr;
        }
        _parent = nullptr;
    }

    // 当前节点相对于其父节点的左右方向
    Dir dirAsChild() const {
        if (_parent == nullptr) {
            return UNKNOWN;
        }

        if (this == _parent->_lc) {
            return LEFT;
        } else if (this == _parent->_rc) {
            return RIGHT;
        }

        return UNKNOWN;
    }
};

// 二叉树结构负责整个树宏观的操作，比如更新节点高度、递归删除、遍历等
template<typename T> class BinaryTree {
protected:
    unsigned int _size;
    BinaryTreeNode<T>* _root;

    static int calcHeight(BinaryTreeNode<T>* v) {
        auto lch = (v->leftChild() == nullptr ? -1 : v->leftChild()->height());
        auto rch = (v->rightChild() == nullptr ? -1 : v->rightChild()->height());
        auto h = 1 + std::max(lch, rch);
        return h;
    }

    static void updateHeight(BinaryTreeNode<T>* v) {
        auto h = calcHeight(v);
        v->updateHeight(h);
    }

    // 向上更新祖先节点高度
    static void updateHeightUpwards(BinaryTreeNode<T>* v) {
        while (v != nullptr) {
            updateHeight(v);
            v = v->parent();
        }
    }

    // 递归向下逐个删除节点
    static unsigned int removeFrom(BinaryTreeNode<T>* v) {
        if (v == nullptr) {
            return 0;
        }
        auto n = 1 + removeFrom(v->leftChild()) + removeFrom(v->rightChild());
        // delete v->val();
        delete v;
        return n;
    }

    template <typename VST>
    void traverseLevelFrom(BinaryTreeNode<T>* start, VST& visit) {
        if (start == nullptr) return;
        std::queue<BinaryTreeNode<T>*> q;
        q.push(start);
        while (!q.empty()) {
            auto top = q.front();
            q.pop();
            visit(top);
            if (top->hasLeftChild()) q.push(top->leftChild());
            if (top->hasRightChild()) q.push(top->rightChild());
        }
    }

    template <typename VST>
    void traverseInFrom(BinaryTreeNode<T>* start, VST& visit) {
        if (start == nullptr) return;
        traverseInFrom(start->leftChild(), visit);
        visit(start);
        traverseInFrom(start->rightChild(), visit);
    }
public:
    BinaryTree(BinaryTreeNode<T>* r = nullptr) {
        _root = r;
        if (r == nullptr) {
            _size = 0;
        } else {
            unsigned int sz = 0;
            auto visit = [&](BinaryTreeNode<T>* v) {
                sz++;
            };
            traverseLevelFrom(r, visit);
            _size = sz;
        }
    }
    ~BinaryTree() {
        if (0 < _size) {
            removeSubTree(_root); 
        }
    }

    static bool isRoot(BinaryTreeNode<T>* v) {
        return !v->hasParent();
    }

    static bool isLeaf(BinaryTreeNode<T>* v) {
        return v->leftChild() == nullptr && v->rightChild() == nullptr;
    }

    BinaryTreeNode<T>* root() {
        return _root;
    }

    bool empty() const { return _root == nullptr; }

    unsigned int size() const { return _size; }

    int height() const { return _root->height(); }

    BinaryTreeNode<T>* insertRoot(T const& e) {
        _size = 1;
        _root = new BinaryTreeNode<T>(e);
        return _root;
    }

    // BST需禁用该接口
    BinaryTreeNode<T>* insertLeftChild(T const& e, BinaryTreeNode<T>* x) {
        _size++;
        auto lc = new BinaryTreeNode<T>(e);
        lc->connectAsLeftChild(x);
        updateHeightUpwards(x);
        return lc;
    }

    // BST需禁用该接口
    BinaryTreeNode<T>* insertRightChild(BinaryTreeNode<T>* x, T const& e) {
        _size++;
        auto rc = new BinaryTreeNode<T>(e);
        rc->connectAsRightChild(x);
        updateHeightUpwards(x);
        return rc;
    }

    unsigned int removeSubTree(BinaryTreeNode<T>* v) {
        if (!isRoot(v)) {
            v->detach();
            updateHeightUpwards(v->parent());
        }
        auto n = removeFrom(v);
        _size -= n;
        return n;
    }

    template <typename VST>
    void traverseLevel(VST& visit) { traverseLevelFrom(_root, visit); }

    template <typename VST>
    void traverseIn(VST& visit) { traverseInFrom(_root, visit); }
};