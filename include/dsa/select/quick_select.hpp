//
// Created by huhaolong on 2024/7/20.
//

#pragma once

#include <vector>
#include <cstdio>

template <typename T> T quickSelect(std::vector<T> arr, int k) {
    int lo = 0, hi = arr.size() - 1;
    while (lo < hi) {
        int i = lo, j = hi;
        int pivot = arr[i];
        while (i < j) {
            while ((i < j) && (pivot <= arr[j])) { j--; }
            arr[i] = arr[j];
            while ((i < j) && (arr[i] <= pivot)) { i++; }
            arr[j] = arr[i];
        }
        arr[i] = pivot;
        if (i == k) {
            return pivot;
        }
        if (k < i) {
            hi = i - 1;
        } else {
            lo = i + 1;
        }
    }
    return arr[lo];
}


