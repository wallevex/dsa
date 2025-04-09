// rbt_test.cpp
// Created by huhaolong on 2025/4/9 11:16.

#include <vector>
#include "gtest/gtest.h"
#include "dsa/binary_tree/rbt/rbt.h"

TEST(RBTTest, Insert) {
    RBT<int> rbt;
    for (int e = 0; e <= 8; e++) {
        rbt.insert(e);
    }

    std::vector<std::pair<int, int>> edges;
    auto visit = [&](BinaryTreeNode<int>* v) {
        RBTNode<int>* x = static_cast<RBTNode<int>*>(v);
        if (v->hasParent()) {
            std::pair<int, int> edge = std::make_pair(x->parent()->val(), x->val());
            edges.push_back(edge);
        }
    };
    rbt.traverseLevel(visit);

    std::vector<std::pair<int, int>> expect = {
            {3, 1},
            {3, 5},
            {1, 0},
            {1, 2},
            {5, 4},
            {5, 7},
            {7, 6},
            {7, 8},
    };
    EXPECT_EQ(expect, edges);
}


TEST(RBTTest, Remove) {
    RBT<int> rbt;
    for (int e = 0; e <= 8; e++) {
        rbt.insert(e);
    }
    rbt.remove(3);

    std::vector<std::pair<int, int>> edges;
    auto visit = [&](BinaryTreeNode<int>* v) {
        RBTNode<int>* x = static_cast<RBTNode<int>*>(v);
        if (v->hasParent()) {
            std::pair<int, int> edge = std::make_pair(x->parent()->val(), x->val());
            edges.push_back(edge);
        }
    };
    rbt.traverseLevel(visit);

    std::vector<std::pair<int, int>> expect = {
            {4, 1},
            {4, 6},
            {1, 0},
            {1, 2},
            {6, 5},
            {6, 7},
            {7, 8},
    };
    EXPECT_EQ(expect, edges);
}