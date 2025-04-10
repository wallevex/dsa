// lru_cache.cpp
// Created by huhaolong on 2025/4/9 16:59.

#include "dsa/lru/lru_cache.hpp"
#include <algorithm>

LRUCache::LRUCache(int capacity) {
    timeline = new LRUTimeline(capacity);
    cache.reserve(capacity);
    this->capacity = capacity;
    size = 0;
}

int LRUCache::get(int key) {
    if (cache.find(key) != cache.end()) {
        timeline->moveToLast(key);
        return cache[key];
    }

    return -1;
}

void LRUCache::put(int key, int value) {
    // 1. already exists, move to last
    if (cache.find(key) != cache.end()) {
        timeline->moveToLast(key);
        cache[key] = value;
        return;
    }

    // 2. cache is not empty, add to last
    if (size < capacity) {
        timeline->addToLast(key);
        cache[key] = value;
        size++;
        return;
    }

    // 3. cache is full, replace LRU
    int lru = timeline->replaceLRU(key);
    cache.erase(lru);
    cache[key] = value;
}