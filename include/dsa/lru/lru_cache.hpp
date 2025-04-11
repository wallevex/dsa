// lru_cache.hpp
// Created by huhaolong on 2025/4/9 16:59.

#pragma once

#include <unordered_map>

struct ListNode {
    int data;
    ListNode* prev;
    ListNode* next;
};

// https://leetcode.com/problems/lru-cache/description/
class LRUCache {
private:
    std::unordered_map<int, int> cache;
    int capacity, size;

    ListNode* dummy;
    ListNode* end;
    std::unordered_map<int, ListNode*> pos;

    void moveToTimelineEnd(int key);

    void addToTimelineEnd(int key);

    int replaceLRU(int key);
public:
    LRUCache(int capacity);

    int get(int key);

    void put(int key, int value);
};
