// lru_cache.cpp
// Created by huhaolong on 2025/4/9 16:59.

#include "dsa/cache/lru_cache.hpp"

void LRUCache::moveToTimelineEnd(int key) {
    ListNode* pos = cache[key]->pos;
    if (pos == tail) return;

    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;

    tail->next = pos;
    pos->prev = tail;
    pos->next = nullptr;
    tail = pos;
}

LRUCache::LRUCache(int capacity) {
    this->capacity = capacity;
    size = 0;
    cache.reserve(capacity);

    dummy = new ListNode(-1, nullptr, nullptr);
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
    // 1. already exists, move to timeline end.
    if (cache.find(key) != cache.end()) {
        moveToTimelineEnd(key);
        cache[key]->value = value;
        return;
    }

    // 2. cache is not empty, add to timeline end.
    if (size < capacity) {
        auto newTail = new ListNode(key, tail, nullptr);
        tail->next = newTail;
        tail = newTail;
        cache[key] = new LRUCacheBlock(value, tail);
        size++;
        return;
    }

    // 3. cache is full, replace LRU.
    int lru = dummy->next->key;
    moveToTimelineEnd(lru);
    tail->key = key;
    cache[key] = new LRUCacheBlock(value, tail);
    cache.erase(lru);
}