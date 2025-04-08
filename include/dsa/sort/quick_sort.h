//
// Created by huhaolong on 2024/7/21.
//

#pragma once

#include <vector>

template <typename T>
int partition(std::vector<T>& arr, int lo, int hi) {
    int pivot = arr[lo];
    while (lo < hi) {
        while ((lo < hi) && (pivot <= arr[hi])) { hi--; }
        arr[lo] = arr[hi];
        while ((lo < hi) && (arr[lo] <= pivot)) { lo++; }
        arr[hi] = arr[lo];
    }
    arr[lo] = pivot;
    return lo;
}

template <typename T>
void _quickSort(std::vector<T>& arr, int lo, int hi) {
    if (hi - lo < 2) return;
    int pivot = partition(arr, lo, hi - 1);
    _quickSort(arr, lo, pivot);
    _quickSort(arr, pivot + 1, hi);
}

template <typename T>
void quickSort(std::vector<T>& arr) {
    _quickSort(arr, 0, arr.size());
}
