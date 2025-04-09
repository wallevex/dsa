// splay_test.cpp
// Created by huhaolong on 2025/4/9 11:15.

#include "gtest/gtest.h"
#include "dsa/binary_tree/splay/splay.h"

TEST(SplayTest, Insert) {
    Splay<int> splay;
    for (int e = 1; e <= 31; e++) {
        splay.insert(e);
    }

    EXPECT_EQ(30, splay.height());
}

TEST(SplayTest, Search) {
    Splay<int> splay;
    for (int e = 1; e <= 31; e++) {
        splay.insert(e);
    }

    splay.search(1);
    EXPECT_EQ(16, splay.height());
    splay.search(3);
    EXPECT_EQ(9, splay.height());
}

TEST(SplayTest, Remove) {
    Splay<int> splay;
    for (int e = 1; e <= 31; e++) {
        splay.insert(e);
    }

    splay.search(1);
    splay.search(3);
    splay.remove(3);
    EXPECT_EQ(9, splay.height());
}
