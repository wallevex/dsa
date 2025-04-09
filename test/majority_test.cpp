// majority_test.cpp
// Created by huhaolong on 2025/4/9 11:17.

#include <vector>
#include "gtest/gtest.h"
#include "dsa/majority/majority.hpp"

TEST(MajorityTest, Majority) {
    std::vector<int> arr1 = {2,3,3,4,3,3,5,3,1,3,2};
    auto ret1 = majority(arr1);
    EXPECT_EQ(3, ret1.second);

    std::vector<int> arr2 = {2,3,3,4,6,3,6,7,1,3,2};
    auto ret2 = majority(arr2);
    EXPECT_FALSE(ret2.first);
}
