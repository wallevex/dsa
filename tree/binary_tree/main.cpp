#include <bits/stdc++.h>
#include "bst.h"
#include "avl/avl.h"

using namespace std;

int main() {
    // BST<int> tree;
    AVL<int> tree;
    for (int i = 1; i <= 13; i++) {
        tree.insert(i);
        printf("after insert %d, tree height is %d\n", i, tree.height());
    }

    auto visit = [&](BinaryTreeNode<int>* v) {
        if (v->parent() == nullptr) {
            printf("[%d]\n", v->val(), v->height());
        } else {
            printf("[%d <- %d]\n", v->parent()->val(), v->val());
        }
    };
    tree.traverseLevel(visit);
    return 0;
}
