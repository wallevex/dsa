#include <bits/stdc++.h>
#include "tree/binary_tree/bst.h"
#include "tree/binary_tree/avl/avl.h"
#include "tree/binary_tree/splay/splay.h"
#include "tree/binary_tree/rbt/rbt.h"

using namespace std;

void testAVL() {
    AVL<int> avl;
    for (int i = 1; i <= 10; i++) {
        avl.insert(i);
    }

    auto visit = [](BinaryTreeNode<int>* v) {
        if (v->parent() == nullptr) {
            printf("[%d]\n", v->val());
        } else {
            printf("[%d <- %d]\n", v->parent()->val(), v->val());
        }
    };
    printf("traverse level result:\n");
    avl.traverseLevel(visit);
}

void testSplay() {
    Splay<int> splay;
    for (int i = 1; i <= 31; i++) {
        splay.insert(i);
    }
    printf("before search, splay height is: %d\n", splay.height());
    splay.search(1);
    printf("after search 1, splay height is: %d\n", splay.height());
    splay.search(3);
    printf("after search 3, splay height is: %d\n", splay.height());
    auto visit = [](BinaryTreeNode<int>* v) {
        if (v->parent() == nullptr) {
            printf("[%d]\n", v->val());
        } else {
            printf("[%d <- %d(%d)]\n", v->parent()->val(), v->val(), v->height());
        }
    };
    printf("traverse level result:\n");
    splay.traverseLevel(visit);
}

int main() {
    // testAVL();
    testSplay();
    return 0;
}
