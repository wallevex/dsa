#include <bits/stdc++.h>
#include "tree/binary_tree/bst.h"
#include "tree/binary_tree/avl/avl.h"
#include "tree/binary_tree/splay/splay.h"
#include "tree/binary_tree/rbt/rbt.h"
#include "priority_queue/priority_queue.h"
#include "complete_binary_heap/complete_binary_heap.h"
#include "left_heap/left_heap.h"

using namespace std;

void testBST() {
    BST<int> bst;
    int arr[8] = {36, 27, 58, 6, 53, 64, 40, 46};
    for (auto x : arr) {
        bst.insert(x);
    }
    bst.remove(36);

    auto visit = [](BinaryTreeNode<int>* v) {
        if (v->parent() == nullptr) {
            printf("[%d]\n", v->val());
        } else {
            printf("[%d <- %d]\n", v->parent()->val(), v->val());
        }
    };
    printf("after remove 36, traverse level result:\n");
    bst.traverseLevel(visit);
}

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

    avl.remove(4);
    printf("after remove 4, traverse level result:\n");
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
    splay.remove(3);
    printf("after remove 3, splay height is: %d\n", splay.height());
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

void testCompleteBinaryHeap() {
    vector<int> seq = {2, 1, 6, 3, 9, 7, 4, 8, 5};
    PriorityQueue<int>* pq = new CompleteBinaryHeap<int>(&seq);
    while (!pq->empty()) {
        auto x = pq->pop();
        printf("[%d] ", x);
    }
}

void testLeftHeap() {
    vector<int> seq = {2, 1, 6, 3, 9, 7, 4, 8, 5};
    PriorityQueue<int>* pq = new LeftHeap<int>();
    for (auto x : seq) {
        pq->push(x);
    }
    while (!pq->empty()) {
        auto x = pq->pop();
        printf("[%d] ", x);
    }
}

int main() {
    // printf("==================== BST TEST ====================\n");
    // testBST();
    // printf("==================== AVL TEST ====================\n");
    // testAVL();
    // printf("==================== Splay TEST ====================\n");
    // testSplay();
    // printf("==================== Complete Binary Heap TEST ====================\n");
    // testCompleteBinaryHeap();
    printf("==================== Left Heap TEST ====================\n");
    testLeftHeap();
    return 0;
}
