// lru_cache.hpp
// Created by huhaolong on 2025/4/9 16:59.

#pragma once

#include <unordered_map>
#include "dsa/lru/lru_timeline.hpp"

// https://leetcode.com/problems/lru-cache/description/
class LRUCache {
private:
    LRUTimeline* timeline;

    std::unordered_map<int, int> cache;
    int capacity, size;
public:
    LRUCache(int capacity);

    int get(int key);

    void put(int key, int value);
};
