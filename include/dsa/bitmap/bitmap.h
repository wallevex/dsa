// bitmap.h
// Created by huhaolong on 2025/8/2 10:07.

#pragma once

#include <vector>
#include <string>

class Bitmap {
private:
    std::vector<char> bitmap;
    int _size;
    void expand(int x) {
        int n = bitmap.size();
        while (8 * n - 1 < x) {
            bitmap.push_back(0x00);
            n++;
        }
    }
public:
    Bitmap() {
        bitmap = std::vector<char>(256, 0x00);
    }
    bool test(int x) {
        expand(x);
        return bitmap[x / 8] & (0x80 >> (x % 8));
    }
    void set(int x) {
        if (test(x)) return;
        expand(x);
        bitmap[x / 8] |= (0x80 >> (x % 8));
        _size++;
    }
    void clear(int x) {
        if (!test(x)) return;
        bitmap[x / 8] ^= (0x80 >> (x % 8));
        _size--;
    }
};