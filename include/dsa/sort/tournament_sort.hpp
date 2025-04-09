//
// Created by huhaolong on 2024/7/21.
//

#pragma once

#include <limits>
#include <vector>

static int parentIndexOf(int idx) { return idx == 0 ? -1 : (idx - 1) / 2; }
static int leftChildIndexOf(int idx) { return 2 * idx + 1; }
static int rightChildIndexOf(int idx) { return 2 * idx + 2; }

template <typename T>
struct TournamentTreeNode {
    T data;
    int ref;
};

template <typename T>
int getWinner(std::vector<TournamentTreeNode<T>*> tree, int idx) {
    int m = tree.size() / 2; // winner(inner node) size
    int lci = leftChildIndexOf(idx), rci = rightChildIndexOf(idx);
    int lcr = lci < m ? tree[lci]->ref : lci, rcr = rci < m ? tree[rci]->ref : rci;
    return tree[lcr]->data < tree[rcr]->data ? lcr : rcr;
}

template <typename T>
std::vector<TournamentTreeNode<T>*> buildTournamentTree(std::vector<T>& arr) {
    int n = arr.size();
    int m = n - 1; // winner(inner node) size
    std::vector<TournamentTreeNode<T>*> tree(m + n);
    for (int i = 0; i < n; i++) {
        tree[i + m] = new TournamentTreeNode<T>();
        tree[i + m]->data = arr[i];
    }
    for (int i = m - 1; i >= 0; i--) {
        tree[i] = new TournamentTreeNode<T>();
        tree[i]->ref = getWinner(tree, i);
    }
    return tree;
}

template <typename T>
void updateTournamentTree(std::vector<TournamentTreeNode<T>*> tree, int idx) {
    while (idx >= 0) {
        tree[idx]->ref = getWinner(tree, idx);
        idx = parentIndexOf(idx);
    }
}

// 基于胜者树的锦标赛排序
// 参考以下
// 1、胜者树和败者树的区别: https://blog.csdn.net/haolexiao/article/details/53488314
// 2、OI Wiki的胜者树实现: https://oi-wiki.org/basic/tournament-sort/
// 3、另一种实现: https://www.cnblogs.com/qianye/archive/2012/11/25/2787923.html
template <typename T>
void tournamentSort(std::vector<T>& arr) {
    T inf = std::numeric_limits<T>::max();
    int n = arr.size();
    auto tree = buildTournamentTree(arr);
    for (int i = 0; i < n; i++) {
        int w = tree[0]->ref;
        arr[i] = tree[w]->data;
        // use INF to remove current winner, and rematch along the winning path
        tree[w]->data = inf;
        updateTournamentTree(tree, parentIndexOf(w));
    }
}
