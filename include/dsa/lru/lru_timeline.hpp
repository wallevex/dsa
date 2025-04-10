// lru_timeline.hpp
// Created by huhaolong on 2025/4/10 15:20.

#pragma once

#include <unordered_map>

struct ListNode {
    int key;
    ListNode* prev;
    ListNode* next;
};

class LRUTimeline {
private:
    ListNode* dummy;
    ListNode* last;
    std::unordered_map<int, ListNode*> pos;
public:
    LRUTimeline(int capacity);

    void moveToLast(int key);

    void addToLast(int key);

    int replaceLRU(int key);
};