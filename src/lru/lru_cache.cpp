// lru_cache.cpp
// Created by huhaolong on 2025/4/9 16:59.

#include "dsa/lru/lru_cache.hpp"
#include <algorithm>

void LRUCache::moveToTimelineEnd(int key) {
    ListNode* hit = pos[key];
    if (hit == end) return;

    hit->prev->next = hit->next;
    hit->next->prev = hit->prev;

    end->next = hit;
    hit->prev = end;
    hit->next = nullptr;
    end = hit;
}

void LRUCache::addToTimelineEnd(int key) {
    ListNode* newEnd = new(ListNode);
    newEnd->data = key;
    newEnd->next = nullptr;
    end->next = newEnd;
    newEnd->prev = end;
    end = newEnd;
    pos[key] = end;
}

int LRUCache::replaceLRU(int key) {
    int lru = dummy->next->data;
    moveToTimelineEnd(lru);
    end->data = key;
    pos.erase(lru);
    pos[key] = end;
    return lru;
}

LRUCache::LRUCache(int capacity) {
    this->capacity = capacity;
    size = 0;
    cache.reserve(capacity);

    dummy = new(ListNode);
    end = dummy;
    pos.reserve(capacity);
}

int LRUCache::get(int key) {
    if (cache.find(key) != cache.end()) {
        moveToTimelineEnd(key);
        return cache[key];
    }

    return -1;
}

void LRUCache::put(int key, int value) {
    // 1. already exists, move to timeline end
    if (cache.find(key) != cache.end()) {
        moveToTimelineEnd(key);
        cache[key] = value;
        return;
    }

    // 2. cache is not empty, add to timeline end
    if (size < capacity) {
        addToTimelineEnd(key);
        cache[key] = value;
        size++;
        return;
    }

    // 3. cache is full, replace LRU
    int lru = replaceLRU(key);
    cache.erase(lru);
    cache[key] = value;
}