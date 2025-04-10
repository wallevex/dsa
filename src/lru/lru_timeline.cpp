// lru_timeline.cpp
// Created by huhaolong on 2025/4/10 15:20.

#include "dsa/lru/lru_timeline.hpp"

LRUTimeline::LRUTimeline(int capacity) {
    dummy = new(ListNode);
    last = dummy;
    pos.reserve(capacity);
}

void LRUTimeline::moveToLast(int key) {
    ListNode* hit = pos[key];
    if (hit == last) return;

    hit->prev->next = hit->next;
    hit->next->prev = hit->prev;

    last->next = hit;
    hit->prev = last;
    hit->next = nullptr;
    last = hit;
}

void LRUTimeline::addToLast(int key) {
    ListNode* newLast = new(ListNode);
    newLast->key = key;
    newLast->next = nullptr;
    last->next = newLast;
    newLast->prev = last;
    last = newLast;
    pos[key] = last;
}

int LRUTimeline::replaceLRU(int key) {
    int lru = dummy->next->key;
    moveToLast(lru);
    last->key = key;
    pos.erase(lru);
    pos[key] = last;
    return lru;
}