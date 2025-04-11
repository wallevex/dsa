// lru_cache.hpp
// Created by huhaolong on 2025/4/9 16:59.

#pragma once

#include <unordered_map>

struct LRUListNode {
    int key;
    LRUListNode* prev;
    LRUListNode* next;

    LRUListNode(int _key, LRUListNode* _prev, LRUListNode* _next) : key(_key), prev(_prev), next(_next){}
};

struct CacheBlock {
    int value;
    LRUListNode* pos;

    CacheBlock(int _value, LRUListNode* _pos) : value(_value), pos(_pos) {}
};

// https://leetcode.com/problems/lru-cache/description/
class LRUCache {
private:
    std::unordered_map<int, CacheBlock*> cache;
    int capacity, size;

    LRUListNode* dummy;
    LRUListNode* tail;

    void moveToTimelineEnd(int key);

    void addToTimelineEnd(int key);

    int replaceLRU(int key);
public:
    LRUCache(int capacity);

    int get(int key);

    void put(int key, int value);
};
