//
// Created by huhaolong on 2024/7/20.
//

#pragma once

#include <vector>

// bubbleSort
// selectSort
// insertSort
// mergeSort
// heapSort（Floyd建堆法O(n)+n次pop总共nlog(n)）
// 以上比较熟悉不记录

template <typename T> int partition(std::vector<T>& arr, int lo, int hi) {
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

template <typename T> void _quickSort(std::vector<T>& arr, int lo, int hi) {
    if (hi - lo < 2) return;
    int pivot = partition(arr, lo, hi - 1);
    _quickSort(arr, lo, pivot);
    _quickSort(arr, pivot + 1, hi);
}

template <typename T> void quickSort(std::vector<T>& arr) {
    _quickSort(arr, 0, arr.size());
}

template <typename T> void shellSort(std::vector<T>& arr) {

}