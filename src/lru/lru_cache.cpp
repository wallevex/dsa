// lru_cache.cpp
// Created by huhaolong on 2025/4/9 16:59.

#include "dsa/lru/lru_cache.hpp"
#include <algorithm>

void LRUCache::moveToTimelineEnd(int key) {
    LRUListNode* hit = cache[key]->pos;
    if (hit == tail) return;

    hit->prev->next = hit->next;
    hit->next->prev = hit->prev;

    tail->next = hit;
    hit->prev = tail;
    hit->next = nullptr;
    tail = hit;
}

void LRUCache::addToTimelineEnd(int key) {
    auto newTail = new LRUListNode(key, tail, nullptr);
    tail->next = newTail;
    tail = newTail;
}

int LRUCache::replaceLRU(int key) {
    int lru = dummy->next->key;
    moveToTimelineEnd(lru);
    tail->key = key;
    return lru;
}

LRUCache::LRUCache(int capacity) {
    this->capacity = capacity;
    size = 0;
    cache.reserve(capacity);

    dummy = new LRUListNode(-1, nullptr, nullptr);
    tail = dummy;
}

int LRUCache::get(int key) {
    if (cache.find(key) != cache.end()) {
        moveToTimelineEnd(key);
        return cache[key]->value;
    }

    return -1;
}

void LRUCache::put(int key, int value) {
    // 1. already exists, move to timeline end
    if (cache.find(key) != cache.end()) {
        moveToTimelineEnd(key);
        cache[key]->value = value;
        return;
    }

    // 2. cache is not empty, add to timeline end
    if (size < capacity) {
        addToTimelineEnd(key);
        cache[key] = new CacheBlock(value, tail);
        size++;
        return;
    }

    // 3. cache is full, replace LRU
    int lru = replaceLRU(key);
    cache[key] = new CacheBlock(value, tail);
    cache.erase(lru);
}