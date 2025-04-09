// select_test.cpp
// Created by huhaolong on 2025/4/9 11:17.

#include <vector>
#include "gtest/gtest.h"
#include "dsa/select/quick_select.hpp"

TEST(SelectTest, QuickSelect) {
    std::vector<int> arr = {9, 8, 5, 3, 1, 6, 10, 2, 7, 4, 10};

    EXPECT_EQ(1, quickSelect(arr, 0));
    EXPECT_EQ(2, quickSelect(arr, 1));
    EXPECT_EQ(3, quickSelect(arr, 2));
    EXPECT_EQ(4, quickSelect(arr, 3));
    EXPECT_EQ(5, quickSelect(arr, 4));
    EXPECT_EQ(6, quickSelect(arr, 5));
    EXPECT_EQ(7, quickSelect(arr, 6));
    EXPECT_EQ(8, quickSelect(arr, 7));
    EXPECT_EQ(9, quickSelect(arr, 8));
    EXPECT_EQ(10, quickSelect(arr, 9));
    EXPECT_EQ(10, quickSelect(arr, 10));
}