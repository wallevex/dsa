//
// Created by huhaolong on 2024/7/16.
//

#pragma once

#include "dsa/priority_queue/priority_queue.hpp"
#include <vector>
#include <algorithm>
#include <cstdio>

template <typename T>
class CompleteBinaryHeap : public PriorityQueue<T> {
private:
    std::vector<T> _seq;

    static int parentIndexOf(int idx) { return idx == 0 ? -1 : (idx - 1) / 2; }
    static int leftChildIndexOf(int idx) { return 2 * idx + 1; }
    static int rightChildIndexOf(int idx) { return 2 * idx + 2; }

    bool indexInHeap(int idx) const {
        int sz = _seq.size();
        return 0 <= idx && idx < sz;
    }

    bool hasChild(int idx) const {
        return indexInHeap(leftChildIndexOf(idx)) || indexInHeap(rightChildIndexOf(idx));
    }

    int greaterChildIndexOf(int idx) const {
        auto lci = leftChildIndexOf(idx);
        auto rci = rightChildIndexOf(idx);
        if (!indexInHeap(lci)) {
            return -1;
        }
        if (!indexInHeap(rci)) {
            return lci;
        }
        return _seq[lci] > _seq[rci] ? lci : rci;
    }

    int percolateUp(int idx) {
        while (0 < idx) {
            auto pidx = parentIndexOf(idx);
            if (_seq[idx] < _seq[pidx]) {
                break;
            }
            std::swap(_seq[idx], _seq[pidx]);
            idx = pidx;
        }
        return idx;
    }

    int percolateDown(int idx) {
        while (hasChild(idx)) {
            auto cidx = greaterChildIndexOf(idx);
            if (_seq[idx] > _seq[cidx]) {
                break;
            }
            std::swap(_seq[idx], _seq[cidx]);
            idx = cidx;
        }
        return idx;
    }
public:
    CompleteBinaryHeap() { _seq = std::vector<T>(0); }

    CompleteBinaryHeap(std::vector<T>* const seq) {
        _seq = *seq;

        //Floyd建堆算法，时间复杂度为O(n)
        //可以参考学堂在线 https://www.xuetangx.com/learn/THU08091002048/THU08091002048/19318085/video/42986773?channel=i.area.learn_title
        for (int idx = _seq.size() / 2 - 1; 0 <= idx; idx--) {
            percolateDown(idx);
        }
    }

    unsigned int size() const override {
        return _seq.size();
    }

    bool empty() const override {
        return _seq.empty();
    }

    void push(const T& e) override {
        _seq.push_back(e);
        percolateUp(_seq.size() - 1);
    }

    T pop() override {
        auto top = _seq.front();
        _seq.front() = _seq.back();
        _seq.pop_back();
        percolateDown(0);
        return top;
    }

    T top() const override {
        return _seq.front();
    }
};