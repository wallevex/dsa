// complete_binary_heap_test.cpp
// Created by huhaolong on 2025/4/9 11:15.

#include <vector>
#include "gtest/gtest.h"
#include "dsa/complete_binary_heap/complete_binary_heap.hpp"
#include "dsa/left_heap/left_heap.hpp"

TEST(CompleteBinaryHeapTest, Pop) {
    std::vector<int> seq = {2, 1, 6, 3, 9, 7, 4, 8, 5};
    PriorityQueue<int>* pq = new CompleteBinaryHeap<int>(&seq);

    std::vector<int> popSeq;
    while (!pq->empty()) {
        popSeq.push_back(pq->pop());
    }

    std::vector<int> expect = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    EXPECT_EQ(expect, popSeq);
}

TEST(LeftHeapTest, Pop) {
    std::vector<int> seq = {2, 1, 6, 3, 9, 7, 4, 8, 5};
    PriorityQueue<int>* pq = new LeftHeap<int>();
    for (int x : seq) {
        pq->push(x);
    }

    std::vector<int> popSeq;
    while (!pq->empty()) {
        popSeq.push_back(pq->pop());
    }

    std::vector<int> expect = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    EXPECT_EQ(expect, popSeq);
}