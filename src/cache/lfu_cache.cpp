// lfu_cache.cpp
// Created by huhaolong on 2025/4/11 13:03.

#include "dsa/cache/lfu_cache.hpp"

void LFUCache::addToFrequencySlot(int slot, ListNode* pos) {
    List* list;
    if (slots.find(slot) != slots.end()) {
        list = slots[slot];
    } else {
        list = new List();
        slots[slot] = list;
    }

    list->tail->prev->next = pos; pos->prev = list->tail->prev;
    pos->next = list->tail; list->tail->prev = pos;
}

ListNode* LFUCache::detach(int key) {
    LFUCacheBlock* hit = cache[key];
    ListNode* pos = hit->pos;
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;

    List* list = slots[hit->frequency];
    if (list->empty()) {
        delete(list);
        slots.erase(hit->frequency);

        if (hit->frequency == minFrequency) {
            minFrequency += 1;
        }
    }

    return pos;
}

void LFUCache::moveToNextSlot(int key) {
    LFUCacheBlock* hit = cache[key];
    ListNode* detached = detach(key);
    hit->frequency += 1;
    addToFrequencySlot(hit->frequency, detached);
}

LFUCache::LFUCache(int capacity) {
    this->capacity = capacity;
    size = 0;
    cache.reserve(capacity);
    minFrequency = 0;
}

int LFUCache::get(int key) {
    if (cache.find(key) != cache.end()) {
        moveToNextSlot(key);
        return cache[key]->value;
    }

    return -1;
}

void LFUCache::put(int key, int value) {
    // 1. already exists, move to slot + 1.
    if (cache.find(key) != cache.end()) {
        moveToNextSlot(key);
        cache[key]->value = value;
        return;
    }

    // 2. cache not full, add to slot 1.
    if (size < capacity) {
        auto pos = new ListNode(key, nullptr, nullptr);
        addToFrequencySlot(1, pos);
        minFrequency = 1;
        cache[key] = new LFUCacheBlock(value, pos);
        size++;
        return;
    }

    // 3. cache is full, replace LFU.
    List* list = slots[minFrequency];
    int lfu = list->head->next->key;

    ListNode* detached = detach(lfu);
    detached->key = key;
    addToFrequencySlot(1, detached);
    minFrequency = 1;

    cache[key] = new LFUCacheBlock(value, detached);
    cache.erase(lfu);
}