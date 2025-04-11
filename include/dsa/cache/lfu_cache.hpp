// lfu_cache.hpp
// Created by huhaolong on 2025/4/11 13:03.

#include <unordered_map>
#include "dsa/cache/list.hpp"

struct LFUCacheBlock {
    int value;
    int frequency;
    ListNode* pos;

    LFUCacheBlock(int _value, ListNode* _pos) : value(_value), pos(_pos), frequency(1) {}
};

// https://leetcode.com/problems/lfu-cache/description/
class LFUCache {
private:
    std::unordered_map<int, LFUCacheBlock*> cache;
    int capacity, size;

    std::unordered_map<int, List*> slots;
    int minFrequency;

    ListNode* detach(int key);
    void addToFrequencySlot(int key, ListNode* pos);
    void moveToNextSlot(int key);
public:
    LFUCache(int capacity);

    int get(int key);

    void put(int key, int value);
};