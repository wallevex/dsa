//
// Created by huhaolong on 2024/7/20.
//

#pragma once

#include <vector>
#include <utility>

// 众数的减治求解法，时间复杂度为O(n)
// 参考学堂在线 https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42987133?channel=i.area.learn_title
template <typename T> std::pair<bool, T> majority(std::vector<T> arr) {
    int n = arr.size();
    T candidate;
    for (int i = 0, diff = 0; i < n; i++) {
        if (diff == 0) {
            candidate = arr[i];
            diff = 1;
        } else {
            diff += (arr[i] == candidate ? 1 : -1);
        }
    }

    int c = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == candidate) {
            c += 1;
        }
    }

    if (2 * c > n) {
        return std::make_pair(true, candidate);
    }
    return std::make_pair(false, candidate);
}
