#include <bits/stdc++.h>
#include "tree/binary_tree/bst.h"
#include "tree/binary_tree/avl/avl.h"
#include "tree/binary_tree/splay/splay.h"
#include "tree/binary_tree/rbt/rbt.h"

using namespace std;

int main() {
    // BST<int> tree;
    AVL<int> tree;
    for (int i = 1; i <= 20; i++) {
        tree.insert(i);
    }

    auto visit = [](BinaryTreeNode<int>* v) {
        if (v->parent() == nullptr) {
            printf("[%d]\n", v->val());
        } else {
            printf("[%d <- %d]\n", v->parent()->val(), v->val());
        }
    };
    printf("traverse level result:\n");
    tree.traverseLevel(visit);

    return 0;
}
