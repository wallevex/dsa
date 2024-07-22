#include <bits/stdc++.h>
#include "tree/binary_tree/bst.h"
#include "tree/binary_tree/avl/avl.h"
#include "tree/binary_tree/splay/splay.h"
#include "tree/binary_tree/rbt/rbt.h"
#include "tree/btree/btree.h"
#include "priority_queue/priority_queue.h"
#include "complete_binary_heap/complete_binary_heap.h"
#include "left_heap/left_heap.h"
#include "string_match/string_match.h"
#include "majority/majority.h"
#include "select/quick_select.h"
#include "sort/sort.h"

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
    for (int e = 1; e <= 10; e++) {
        avl.insert(e);
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
    for (int e = 1; e <= 31; e++) {
        splay.insert(e);
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

void testRBT() {
    RBT<int> rbt;
    for (int e = 0; e <= 8; e++) {
        rbt.insert(e);
    }
    auto visit = [](BinaryTreeNode<int>* v) {
        RBTNode<int>* vv = static_cast<RBTNode<int>*>(v);
        char c = vv->color() == BLACK ? 'B' : 'R';
        if (vv->parent() == nullptr) {
            printf("[%d%c%d]\n", vv->val(), c, vv->blackHeight());
        } else {
            printf("[%d <- %d%c%d]\n", vv->parent()->val(), vv->val(), c, vv->blackHeight());
        }
    };
    printf("traverse level result:\n");
    rbt.traverseLevel(visit);
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

void testMajority() {
    vector<int> arr = {2,3,3,4,3,3,5,3,1,3,2};
    auto ret = majority(arr);
    if (ret.first == false) {
        printf("majority not exists\n");
    } else {
        printf("majority is %d\n", ret.second);
    }
}

void testQuickSelect() {
    vector<int> arr = {9, 8, 5, 3, 1, 6, 2, 7, 4, 5};
    int k = 6;
    auto x = quickSelect(arr, k);
    printf("arr[%d]=%d\n", k, x);
}

void testSort() {
    vector<int> arr = {2, 3, 4, 5, 6, 7, 8, 9, 1};
    quickSort(arr);
    for (auto x : arr) {
        printf("%d ", x);
    }

    printf("\n");
    vector<int> arr2 = {11, 4, 14, 3, 10, 0, 15, 1, 9, 6, 8, 7, 13, 2, 12, 5};
    shellSort(arr2);
    for (auto x : arr2) {
        printf("%d ", x);
    }

    printf("\n");
    vector<int> arr3 = {10, 9, 20, 6, 12};
    tournamentSort(arr3);
    for (auto x : arr3) {
        printf("%d ", x);
    }
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
    printf("\n==================== RBT TEST ====================\n");
    testRBT();
    // // printf("\n==================== BuildNext TEST ====================\n");
    // // testBuildNext();
    // // printf("\n==================== KMP TEST ====================\n");
    // // testStringMatch_KMP();
    // // printf("\n==================== BM TEST ====================\n");
    // // testStringMatch_BM();
    // // printf("\n==================== Majority TEST ====================\n");
    // // testMajority();
    // // printf("\n==================== Quick Select TEST ====================\n");
    // // testQuickSelect();
    // printf("\n==================== Sort TEST ====================\n");
    // testSort();
    return 0;
}
