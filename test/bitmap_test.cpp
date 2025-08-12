// bitmap_test.cpp
// Created by huhaolong on 2025/8/2 20:53.

#include <vector>
#include "gtest/gtest.h"
#include "dsa/bitmap/bitmap.h"

TEST(BitmapTest, Test) {
    auto b = Bitmap();
    std::vector<int> arr = {0, 1, 2, 99, 256, 500, 888, 889, 1000, 214748364};
    for (int x : arr) {
        b.set(x);
    }
    for (int x : arr) {
        EXPECT_EQ(b.test(x), true);
    }
    b.clear(888);
    EXPECT_EQ(b.test(888), false);
}