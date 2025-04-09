// avl_test.cpp
// Created by huhaolong on 2025/4/9 11:14.

#include <vector>
#include "gtest/gtest.h"
#include "dsa/binary_tree/avl/avl.h"

TEST(AVLTest, Insert) {
    AVL<int> avl;
    for (int e = 1; e <= 9; e++) {
        avl.insert(e);
    }

    std::vector<std::pair<int, int>> edges;
    auto visit = [&](BinaryTreeNode<int>* v) {
        AVLNode<int>* x = static_cast<AVLNode<int>*>(v);
        if (v->hasParent()) {
            std::pair<int, int> edge = std::make_pair(x->parent()->val(), x->val());
            edges.push_back(edge);
        }
    };
    avl.traverseLevel(visit);

    std::vector<std::pair<int, int>> expect = {
            {4, 2},
            {4, 6},
            {2, 1},
            {2, 3},
            {6, 5},
            {6, 8},
            {8, 7},
            {8, 9}
    };
    EXPECT_EQ(expect, edges);
}

TEST(AVLTest, Remove) {
    AVL<int> avl;
    for (int e = 1; e <= 9; e++) {
        avl.insert(e);
    }
    avl.remove(4);

    std::vector<std::pair<int, int>> edges;
    auto visit = [&](BinaryTreeNode<int>* v) {
        AVLNode<int>* x = static_cast<AVLNode<int>*>(v);
        if (v->hasParent()) {
            std::pair<int, int> edge = std::make_pair(x->parent()->val(), x->val());
            edges.push_back(edge);
        }
    };
    avl.traverseLevel(visit);

    std::vector<std::pair<int, int>> expect = {
            {5, 2},
            {5, 8},
            {2, 1},
            {2, 3},
            {8, 6},
            {8, 9},
            {6, 7},
    };
    EXPECT_EQ(expect, edges);
}