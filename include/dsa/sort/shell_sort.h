//
// Created by huhaolong on 2024/7/21.
//

#pragma once

#include <vector>

// 效率分析参考学堂在线 https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42987208?channel=i.area.learn_title
template <typename T>
void shellSort(std::vector<T>& arr) {
    int n = arr.size();
    for (int d = 0x7FFFFFFF; 0 < d; d >>= 1) { // Papernov-Stasevic序列 {1, 3, 7, 15, ..., 2^k - 1, ...}
        for (int i = d; i < n; i++) {
            T x = arr[i];
            int j = i;
            while ((j - d >= 0) && (arr[j - d] > x)) {
                arr[j] = arr[j - d];
                j -= d;
            }
            arr[j] = x;
        }
    }
}
