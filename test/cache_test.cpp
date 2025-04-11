// cache_test.cpp
// Created by huhaolong on 2025/4/11 17:08.

#include "gtest/gtest.h"
#include "dsa/cache/cache.hpp"
#include <vector>

TEST(CacheTest, LRU) {
    LRUCache c(2);
    std::vector<int> res;

    c.put(1, 1);
    c.put(2, 2);
    res.push_back(c.get(1));
    c.put(3,3);
    res.push_back(c.get(2));
    c.put(4, 4);
    res.push_back(c.get(1));
    res.push_back(c.get(3));
    res.push_back(c.get(4));

    std::vector<int> expect = {1, -1, -1, 3, 4};
    EXPECT_EQ(expect, res);
}

TEST(CacheTest, LFU) {
    LFUCache c(2);
    std::vector<int> res;

    c.put(1, 1);
    c.put(2, 2);
    res.push_back(c.get(1));
    c.put(3,3);
    res.push_back(c.get(2));
    res.push_back(c.get(3));
    c.put(4, 4);
    res.push_back(c.get(1));
    res.push_back(c.get(3));
    res.push_back(c.get(4));

    std::vector<int> expect = {1, -1, 3, -1, 3, 4};
    EXPECT_EQ(expect, res);
}