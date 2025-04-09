// sort_tset.cpp
// Created by huhaolong on 2025/4/9 11:17.

#include <vector>
#include "gtest/gtest.h"
#include "dsa/sort/sort.hpp"

TEST(SortTest, QuickSort) {
    std::vector<int> arr = {2, 3, 4, 5, 6, 7, 8, 9, 1};
    quickSort(arr);

    std::vector<int> expect = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(expect, arr);
}

TEST(SortTest, ShellSort) {
    std::vector<int> arr = {11, 4, 14, 3, 10, 0, 15, 1, 9, 6, 8, 7, 13, 2, 12, 5};
    shellSort(arr);

    std::vector<int> expect = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    EXPECT_EQ(expect, arr);
}

TEST(SortTest, TournamentSort) {
    std::vector<int> arr = {10, 9, 20, 6, 12};
    tournamentSort(arr);

    std::vector<int> expect = {6, 9, 10, 12, 20};
    EXPECT_EQ(expect, arr);
}