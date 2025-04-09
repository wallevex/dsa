// string_match_test.cpp
// Created by huhaolong on 2025/4/9 11:16.

#include <string>
#include "gtest/gtest.h"
#include "dsa/string_match/string_match.hpp"

TEST(KMPTest, BuildNext) {
    //p='HHFBHHFHHFBSHF'
    //优化前p的next数组=[-1, 0, 1, 0, 0, 1, 2, 3, 1, 2, 3, 4, 0, 1]
    //优化后p的next数组=[-1, -1, 1, 0, -1, -1, 1, 3, -1, 1, 0, 4, -1, 1]
    std::string p = "HHFBHHFHHFBSHF";
    auto next = buildNext(p);

    std::vector<int> expect = {-1, -1, 1, 0, -1, -1, 1, 3, -1, 1, 0, 4, -1, 1};
    EXPECT_EQ(expect, next);
}

TEST(KMPTest, Match) {
    std::string t = "000100001";
    std::string p = "00001";

    EXPECT_EQ(4, match_KMP(t, p));
}

TEST(BMTest, Match) {
    std::string t = "ICED RICE PRICE";
    std::string p = "RICE";

    EXPECT_EQ(5, match_BM(t, p));
}