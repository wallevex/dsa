// lru_cache.hpp
// Created by huhaolong on 2025/4/9 16:59.

#pragma once

#include <unordered_map>
#include "dsa/cache/list.hpp"

struct LRUCacheBlock {
    int value;
    ListNode* pos;

    LRUCacheBlock(int _value, ListNode* _pos) : value(_value), pos(_pos) {}
};

// https://leetcode.com/problems/lru-cache/description/
class LRUCache {
private:
    std::unordered_map<int, LRUCacheBlock*> cache;
    int capacity, size;

    ListNode* dummy;
    ListNode* tail;

    void moveToTimelineEnd(int key);
public:
    LRUCache(int capacity);

    int get(int key);

    void put(int key, int value);
};
