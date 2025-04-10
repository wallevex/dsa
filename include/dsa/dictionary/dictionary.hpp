// dictionary.hpp
// Created by huhaolong on 2025/4/9 13:58.

#pragma once

template <typename K, typename V>
class Dictionary {
public:
    virtual unsigned int size() const = 0;
    virtual bool put(K, V) = 0;
    virtual V* get(K) = 0;
    virtual bool remove(K) = 0;
};