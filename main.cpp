#include <bits/stdc++.h>
#include "tree/binary_tree/bst.h"
#include "tree/binary_tree/avl/avl.h"
#include "tree/binary_tree/splay/splay.h"
#include "tree/binary_tree/rbt/rbt.h"
#include "priority_queue/priority_queue.h"
#include "complete_binary_heap/complete_binary_heap.h"
#include "left_heap/left_heap.h"
#include "string_match/string_match.h"

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

void testBuildNext() {
    //p='HHFBHHFHHFBSHF'
    //优化前p的next数组=[-1, 0, 1, 0, 0, 1, 2, 3, 1, 2, 3, 4, 0, 1]
    //优化后p的next数组=[-1, -1, 1, 0, -1, -1, 1, 3, -1, 1, 0, 4, -1, 1]
    string p = "HHFBHHFHHFBSHF";
    auto nextv2 = buildNextV2(p);
    for (auto x : nextv2) {
        printf("%d ", x);
    }
}

void testStringMatch_KMP() {
    string t = "000100001";
    string p = "00001";
    printf("found '%s' in '%s' at %d\n", p.c_str(), t.c_str(), match_KMP(t, p));
}

void testStringMatch_BM() {
    string t = "ICED RICE PRICE";
    string p = "RICE";
    printf("found '%s' in '%s' at %d\n", p.c_str(), t.c_str(), match_BM(t, p));
}

int main() {
    // printf("\n==================== BST TEST ====================\n");
    // testBST();
    // printf("\n==================== AVL TEST ====================\n");
    // testAVL();
    // printf("\n==================== Splay TEST ====================\n");
    // testSplay();
    // printf("\n==================== Complete Binary Heap TEST ====================\n");
    // testCompleteBinaryHeap();
    // printf("\n==================== Left Heap TEST ====================\n");
    // testLeftHeap();
    // printf("\n==================== BuildNext TEST ====================\n");
    // testBuildNext();
    // printf("\n==================== KMP TEST ====================\n");
    // testStringMatch_KMP();
    printf("\n==================== BM TEST ====================\n");
    testStringMatch_BM();
    return 0;
}
